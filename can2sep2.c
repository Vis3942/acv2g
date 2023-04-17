#include <sys/select.h>
#include <fcntl.h>
#include <time.h>
#include <sys/timerfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

#include "can.h"
#include "usock_utils.h"
#include "usock_server.h"
#include "utils.h"
#include "usock_proto.h"
#include "task_queue.h"
#include "ss_proto.h"

#define MAX(x,y) ((x) > (y)? (x) : (y))

#define DER_INFO_NOT_AVAILABLE 0x07
#define CHARGE_AT_100PC 0x08  // 0x04 //0x08 // charge rate is -100% => charging
#define CHARGE_AT_25PC 0x09 // 0x05 //0x09
#define CHARGE_NOT_ALLOWED_SEP2_0PC 0x0a  //0x06 //  0x0D // CHARGING not allowed
#define DISCHARGE_AT_100PC 0x0b //   0x07 //0x0B
#define CHARGE_NOT_ALLOWED 0x0d //0x06 //0x0D // still looking for TMS

#define OBC_STATUS_CAPABLE_DER 12
#define OBC_STATUS_VEHICLE_READY_DISCHARGE 13
#define OBC_STATUS_VEHICLE_TERMINATING_DER 14

#define MAX_CHARGE_RATE_READ_ID     0x01
#define MAX_DISCHARGE_RATE_READ_ID  0x02
#define CURRENT_SOC_READ_ID         0x03
#define TARGET_SOC_READ_ID          0x04
#define TIME_CHARGE_NEEDED_READ_ID  0x05
#define MAX_CHARGE_DURATION_READ_ID 0x06
#define AVAILABILITY_SECS_READ_ID   0x07

#define NUMBER_READ_IDS  0x07 // this will change if read ids are added or deleted

#define SERVER_STATUS_WRITE_ID      0x8001
#define CHARGE_PERCENT_WRITE_ID     0x8002
#define DURATION_SECS_WRITE_ID      0x8003
#define TIME_2_EVENT_SECS_WRITE_ID  0X8004

#define NUMBER_WRITE_IDS   0x04 // this will change if write ids are added or deleted

//#define PRINT_CAN_IDS 1

//#define BATTERY_CAPACITY_KWH 30

// need for SCE: BEGIN
int32_t server_status; // 0=> not found, 1 => found, 2 => searching, -1 => just initialized
int32_t prev_server_status; // 0=> not found, 1 => found, 2 => searching, -1 => just initialized

int32_t der_mode; // from HCP over CAN 0 => not opted, 1 => opted
int32_t prev_der_mode; // from HCP over CAN 0 => not opted, 1 => opted

int32_t hcp_sw_ver;
int32_t hcp_sw_ver_recvd = 0;
int32_t pmin_kW;
int32_t max_Wh;
int32_t max_Wh_recvd = 0; // 0 => not recvd; 1 => recvd max_Wh
int32_t energy_request_now_Wh;
int32_t current_power_source;
int32_t battery_status; 
time_t changed_time;
int32_t minimum_charging_duration_secs;
int32_t estimated_charge_remaining;
int32_t reserve_charge_percent;
int32_t current_neg_limit_amps;
int32_t reserve_percent;
int32_t obc_max_fwd_pwr_w;
int32_t obc_current_charging_pwr_w;
int32_t obc_max_rvr_pwr_w;
int32_t obc_esstat;
int32_t obc_pilotfreq_type;
int32_t obc_dcca;
int32_t evcc_es; // 1 => true 0 => false
// need for SCE: END

int32_t charge_percent; // 0=> do not charge/ di0scharge, -100 charge at 100%, -25 charge at 25%, 100 discharge at 100%
int32_t duration_secs; // convert to mins before sending on can BUS
int32_t time_to_event_start_secs;
int32_t time_left_der_mins; 

int32_t prev_charge_percent; // 0=> do not charge/ discharge, -100 charge at 100%, -25 charge at 25%, 100 discharge at 100%
int32_t prev_duration_secs; // convert to mins before sending on can BUS
int32_t prev_time_to_event_start_secs;
int32_t prev_time_left_der_mins; 

int32_t max_charge_rate;
int32_t max_discharge_rate;
float current_soc;
float target_soc = 98.0f;
int32_t time_charge_is_neeeded_duration_secs;
int32_t max_charge_duration_secs;
int32_t availability_duration_secs; // to be computed based on current_soc and Batt capacity
time_t reading_time;

int obc_event_status;

int test_can_messages = 0;
int reverse_power_flow_flag;
int reverse_power_flow_percent;
int test_timer_seconds = 5;
int test_timerfd;

void usock_message()
{
  // implement the protocol between the kitu sep 2 client and can2sep app
  // read data sequence begins with 0xFFFF being sent by the client
  uint16_t data_u16_cmd;
  uint16_t tmp_u16;
  int n;
  int ii;
  int read_ids_count;
  n = recv(conn_usock_fd, &data_u16_cmd, sizeof(data_u16_cmd), 0);
  //printf("unix socket: recv %d bytes\n", n);
  if ( (n < 0) || (n == 0) )
  {
    if (n < 0) perror("recv");
    close_usock();
    return;
  }

  //printf("first data cmd = %x, sts = %d \n", data_u16_cmd, n);
  if (data_u16_cmd == 0xFFFF)
  {
    // start read sequence (from client perspective)
    // read sequence is from client perspective 
    // write number of items 
    // loop number of items
    //      write item id
    //      write item value

    // write num items
    tmp_u16 = (uint16_t)NUMBER_READ_IDS;
    n = send(conn_usock_fd, &tmp_u16, sizeof(uint16_t), 0);
    //printf("sending = %d, bytes, value = %d \n", n, tmp_u16);
    if (n < 0)
    {
      perror("send");
      close_usock();
      return;
    }
    for (ii=1; ii <= NUMBER_READ_IDS; ii++)
    {
      // send id
      tmp_u16 = (uint16_t) ii;
      n = send(conn_usock_fd, &tmp_u16, sizeof(uint16_t), 0);
      if (n < 0)
      {
        perror("send");
        close_usock();
        return;
      }
      //fprintf(stdout, "write bytes %d \n", n);
      //printf("succ sent id %d \n", ii);
      // send val corresponding to id
      switch (ii)
      {
        case (int)MAX_CHARGE_RATE_READ_ID:
          n = send(conn_usock_fd, &max_charge_rate, sizeof(int32_t), 0);
          if (n < 0)
          {
            perror("send");
            close_usock();
            return;
          }
          //fprintf(stdout, "write bytes %d \n", n);
          break;
        case (int)MAX_DISCHARGE_RATE_READ_ID:
          n = send(conn_usock_fd, &max_discharge_rate , sizeof(int32_t), 0);
          if (n < 0)
          {
            perror("send");
            close_usock();
            return;
          }
          //fprintf(stdout, "write bytes %d \n", n);
          break;

        case (int)CURRENT_SOC_READ_ID:
          n = send(conn_usock_fd, &current_soc , sizeof(float), 0);
          if (n < 0)
          {
            perror("send");
            close_usock();
            return;
          }
          //fprintf(stdout, "write bytes %d \n", n);
          break;

        case (int)TARGET_SOC_READ_ID:
          n = send(conn_usock_fd, &target_soc , sizeof(float), 0);
          if (n < 0)
          {
            perror("send");
            close_usock();
            return;
          }
          //fprintf(stdout, "write bytes %d \n", n);
          break;

        case (int) TIME_CHARGE_NEEDED_READ_ID:
          n = send(conn_usock_fd, &time_charge_is_neeeded_duration_secs , sizeof(int32_t), 0);
          if (n < 0)
          {
            perror("send");
            close_usock();
            return;
          }
          //fprintf(stdout, "write bytes %d \n", n);
          break;

        case (int) MAX_CHARGE_DURATION_READ_ID:
          n = send(conn_usock_fd, &max_charge_duration_secs , sizeof(int32_t), 0);
          if (n < 0)
          {
            perror("send");
            close_usock();
            return;
          }
          //fprintf(stdout, "write bytes %d \n", n);
          break;

        case (int) AVAILABILITY_SECS_READ_ID:
          n = send(conn_usock_fd, &availability_duration_secs , sizeof(int32_t), 0);
          if (n < 0)
          {
            perror("send");
            close_usock();
            return;
          }
          //fprintf(stdout, "write bytes %d \n", n);
          break;
      }
      //printf("end of switch for sending value %d \n", ii);
    }
  }

  // write data sequence begins with 0x7FFF being 
  n = recv(conn_usock_fd, &data_u16_cmd, sizeof(data_u16_cmd), 0);
  //printf("unix socket: recv %d bytes\n", n);
  //printf("second data cmd = %x, sts = %x \n", data_u16_cmd, n);
  if ( (n < 0) || (n == 0) )
  {
    if (n < 0) perror("recv");
    close_usock();
    return;
  }

  if (data_u16_cmd == 0x7FFF)
  {
    // start write sequence (from client perspective)
    // write sequence is from client perspective
    // read number of items 
    // loop number of items
    //      read item id
    //      read item value

    // read number of items
    n = recv(conn_usock_fd, &tmp_u16, sizeof(tmp_u16), 0);
    if ( (n < 0) || (n == 0) )
    {
      if (n < 0) perror("recv");
      close_usock();
      return;
    }
    //printf("number of rd ids recv = %d, bytes, value = %d \n", n, tmp_u16);
    read_ids_count = (int) tmp_u16;
    for (ii=1; ii <= read_ids_count; ii++)
    {
      // read id of data
      n = recv(conn_usock_fd, &tmp_u16, sizeof(tmp_u16), 0);
      if ( (n < 0) || (n == 0) )
      {
        if (n < 0) perror("recv");
        close_usock();
        return;
      }
      //printf("id: read %d bytes, value %x \n", n, tmp_u16);
      // read data corresponding to id of data
      switch (tmp_u16)
      {
        case (uint16_t)SERVER_STATUS_WRITE_ID:
          n = recv(conn_usock_fd, &server_status, sizeof(int32_t), 0);
          //printf("server status write id called, val = %d, sts = %x\n", server_status, n);
          if ( (n < 0) || (n == 0) )
          {
            if (n < 0) perror("recv");
            close_usock();
            return;
          }
          break;

        case (uint16_t)CHARGE_PERCENT_WRITE_ID:
          n = recv(conn_usock_fd, &charge_percent, sizeof(int32_t), 0);
          //printf("charge pc write id called, val = %d, sts = %x \n", charge_percent, n);
          if ( (n < 0) || (n == 0) )
          {
            if (n < 0) perror("recv");
            close_usock();
            return;
          }
          break;

        case (uint16_t)DURATION_SECS_WRITE_ID:
          n = recv(conn_usock_fd, &duration_secs, sizeof(int32_t), 0);
          //printf("duration secs write id called, val = %d, sts = %x \n", duration_secs, n);
          if ( (n < 0) || (n == 0) )
          {
            if (n < 0) perror("recv");
            close_usock();
            return;
          }
          break;

        case (uint16_t)TIME_2_EVENT_SECS_WRITE_ID:
          n = recv(conn_usock_fd, &time_to_event_start_secs, sizeof(int32_t), 0);
          //printf("time 2 event secs write id called, val = %d, sts = %x \n", time_to_event_start_secs, n);
          if ( (n < 0) || (n == 0) )
          {
            if (n < 0) perror("recv");
            close_usock();
            return;
          }
          break;

      }
    }
  }

  if (
    (prev_server_status != server_status) || (prev_charge_percent != charge_percent) ||
    (prev_duration_secs != duration_secs) || 
    (prev_time_to_event_start_secs != time_to_event_start_secs)
  ) 
  {
    if (prev_server_status != server_status)
    {
      prev_server_status = server_status;
    }
    if (prev_charge_percent != charge_percent)
    {
      prev_charge_percent = charge_percent;
    }
    if (prev_duration_secs != duration_secs)
    {
      prev_duration_secs = duration_secs;
    }
    if (prev_time_to_event_start_secs != time_to_event_start_secs)
    {
      prev_time_to_event_start_secs = time_to_event_start_secs;
    }

    fprintf(stdout, "server status = %d, charge_percent = %d, \n duration_secs=%d, time_to_event_start_secs = %d \n", 
      server_status, charge_percent, duration_secs, time_to_event_start_secs);

    console_log("server status = %d, charge_percent = %d, \n duration_secs=%d, time_to_event_start_secs = %d \n", 
      server_status, charge_percent, duration_secs, time_to_event_start_secs);
  }
}


void disp_can_message(int id, char*data_recv){
      fprintf(stdout,"can id %4x:  \n", id);
      fprintf(stdout," bytes : %2x %2x %2x %2x %2x %2x %2x %2x\n", 
          data_recv[0], data_recv[1], data_recv[2], data_recv[3],
          data_recv[4], data_recv[5], data_recv[6], data_recv[7]);
      console_log("can [%4x]: %2x %2x %2x %2x %2x %2x %2x %2x \n", 
          id,
          data_recv[0], data_recv[1], data_recv[2], data_recv[3],
          data_recv[4], data_recv[5], data_recv[6], data_recv[7]);


}

void can_message (int id, char *data_recv) {
  //int i, soc, capacity; uint32_t charge_rate; uint64_t average = 0;
  double tmpdbl;
  int tmpi;
  int16_t tmp16_t;
  int send_to_hcp = 0;
  char data[8];
  switch (id) 
  {
  case 0x30A: // HCP_DER_MSG_01
#ifdef PRINT_CAN_IDS
    fprintf(stdout,"can id 0x30A: HCP_DER_MSG_01 \n");
#endif
    der_mode = ( (data_recv[4] & 0xC0) >> 2 );
    hcp_sw_ver = (data_recv[4] & 0x3F);
    hcp_sw_ver_recvd = 1;
    tmpi = data_recv[3];
    if ( (tmpi < -100) || (tmpi > 100) )
    {
      tmpi = 0; // default value of 0kW
    }
    pmin_kW = tmpi * 0.1; // resolution
    tmpi = data_recv[2];
    if ( (tmpi < 0) || (tmpi > 192) )
    {
      // default is maximum value for this demonstration
      tmpi = 192;
    }
    time_charge_is_neeeded_duration_secs = tmpi * 15 * 60;
    max_Wh = data_recv[0] << 8;
    max_Wh = max_Wh + data_recv[1];
    max_Wh_recvd = 1; // to indicate to send DERSettings to SEP2 client
    send_to_hcp = 1;
    break;
    
  case 0x30B:
#ifdef PRINT_CAN_IDS
    fprintf(stdout,"can id 0x30B: HCP_DER_MSG_02 \n");
#endif
    energy_request_now_Wh = data_recv[0] << 8;
    energy_request_now_Wh = energy_request_now_Wh + data_recv[1];
    target_soc = (data_recv[2] & 0xFE) >> 1;
    availability_duration_secs = (data_recv[2] & 0x01) << 16;
    availability_duration_secs = availability_duration_secs + (data_recv[3]  << 8);
    availability_duration_secs = availability_duration_secs + data_recv[4];
    current_power_source = ( data_recv[5] & 0xE0 ) >> 5;
    battery_status = (data_recv[5] & 0x1C) >> 2;
    tmpi =  (data_recv[5] &0x03) << 9;
    tmpi = tmpi + data_recv[6] << 1;
    if ( (data_recv[7] & 0x80) == 0x80)
    {
      tmpi = tmpi + 1;
    }
    if ( (tmpi < 0) || (tmpi > 1440) )
    {
      tmpi = 1440; 
    }
    minimum_charging_duration_secs = tmpi * 60; 
    estimated_charge_remaining = (data_recv[7] & 0x0FE);
    reading_time = getCurrentTime();
    changed_time = reading_time;
    send_to_hcp = 1;
    break;

  case 0x30C: //HCP_DER_MSG_03
#ifdef PRINT_CAN_IDS
    fprintf(stdout,"can id 0x30C: HCP_DER_MSG_03 \n");
#endif
    reserve_charge_percent = ( data_recv[0] & 0xFE) >> 1;
    max_charge_duration_secs = ( data_recv[0] & 0x01 ) << 16;
    max_charge_duration_secs = max_charge_duration_secs + (data_recv[1] << 8);
    max_charge_duration_secs = max_charge_duration_secs + data_recv[2];
    tmpi = ( data_recv[3] & 0x03 ) << 8;
    tmpi = tmpi + data_recv[4];
    if ( (tmpi < 0) || (tmpi > 1023) )
    {
      tmpi = 1023;
    }
    current_neg_limit_amps = -0.1 * tmpi;
    reserve_percent = data_recv[5] & 0x7F;
    current_soc = data_recv[6] & 0x7F; 
    send_to_hcp = 1;
    break;

  case 0x326: // OBC_DER_MSG_01
#ifdef PRINT_CAN_IDS
    fprintf(stdout,"can id 0x326: OBC_DER_MSG_01\n");
#endif
    obc_max_fwd_pwr_w = data_recv[0] << 8;
    obc_max_fwd_pwr_w = obc_max_fwd_pwr_w + data_recv[1];
    tmp16_t = data_recv[2] << 8;
    tmp16_t = tmp16_t + data_recv[3];
    obc_current_charging_pwr_w = (int32_t) tmp16_t * 0.5;
    obc_max_rvr_pwr_w = data_recv[4] << 8;
    obc_max_rvr_pwr_w = obc_max_fwd_pwr_w + data_recv[5];
    obc_esstat = (data_recv[6] & 0xC0) >> 6;
    obc_pilotfreq_type = (data_recv[6] & 0x30) >> 4;
    obc_dcca = (data_recv[6] & 0x0C) >> 2;
    send_to_hcp = 0;
    break;
  
  default:
    // do nothing 
    send_to_hcp = 0;
    break;
  }

  if (send_to_hcp == 1) 
  {
    if (server_status == 1) 
    {
      data[0] = (1 << 4);
    }
    else 
    {
      data[0] = 0;
    }
    if (evcc_es == 1)
    {
      data[0] = (data[0] | 0x80);
    }
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    can_transmit(0x30F, data, 8);
  }
}


void message_received (int x) {
  struct can_frame frame;
  struct timeval timeout = {0};
  fd_set rfds, wfds;
  int nfds;

  int tmpmax;
  tmpmax = MAX(can_socket, srv2cli_usock_fd);
  tmpmax = MAX(tmpmax, conn_srv2cli_usock_fd);
  tmpmax = MAX(tmpmax, cli2srv_usock_fd);
  tmpmax = MAX(tmpmax, conn_cli2srv_usock_fd);
  if (test_can_messages) 
  {
    tmpmax = MAX(tmpmax, test_timerfd);
  }
  nfds = tmpmax;

  FD_ZERO (&rfds); FD_ZERO (&wfds);
  FD_SET (can_socket, &rfds);
  FD_SET (cli2srv_usock_fd, &rfds);
  if (conn_cli2srv_usock_fd > 0)
  {
    FD_SET (conn_cli2srv_usock_fd, &rfds);
  }
  FD_SET(srv2cli_usock_fd, &rfds);
  if (conn_srv2cli_usock_fd > 0)
  {
    FD_SET (conn_srv2cli_usock_fd, &rfds);
  }
  if (test_can_messages)
  {
    FD_SET(test_timerfd, &rfds);
  }
  //printf("in message received \n");
  if (select (nfds, &rfds, NULL, NULL, &timeout) > 0) {
    //fprintf(stdout," in select call with io recv \n");
    if (FD_ISSET (can_socket, &rfds)) {
      while (read(can_socket, &frame, sizeof(struct can_frame)) >= 0) {
        if (frame.can_id & CAN_ERR_FLAG) {
            fprintf(stdout,"can error frame\n"); continue;
        }
        if (test_can_messages)
        {
          disp_can_message(frame.can_id & CAN_EFF_MASK, (char *)frame.data);
        }
        else 
        {
          can_message (frame.can_id & CAN_EFF_MASK, (char *)frame.data);
        }
      }
    }

    if (FD_ISSET (cli2srv_usock_fd, &rfds)) 
    {
      usock_client2server_accept();
    }

    if (FD_ISSET (srv2cli_usock_fd, &rfds))
    {
      usock_server2client_accept()
    }

    if (conn_cli2srv_usock_fd > 0)
    {
      if (FD_ISSET (conn_cli2srv_usock_fd, &rfds)) usock_client2server_read_message();
    }

    // conn_srv2cli_usock_fd is only for writing messages

    if (test_can_messages)
    {
      if (FD_ISSET (test_timerfd, &rfds)) send_test_can_messages();
    }

  }
}



void signal_init () {
  struct sigaction action;
  struct sigevent event;
  struct itimerspec expire;
  signal (SIGPIPE, SIG_IGN); 
  action.sa_handler = message_received;
  action.sa_flags = 0;
  if (sigaction (SIGIO, &action, NULL) < 0)
    fprintf(stdout,"sigaction: %d\n", errno);
  // enable SIGIO signaling for new messages
  }

void parse_options (int argc, char **argv) {
  int arg;
  while ((arg = getopt (argc, argv, "rt:")) != -1)
  {
    switch (arg){
      case 'r':
        // Detected the 't' option, mark a flag to indicate
          reverse_power_flow_flag = 1;
          reverse_power_flow_percent = atoi(optarg);
          printf("rpf flag set, value set to %d\n", reverse_power_flow_percent);
        break;
      case 't':
          test_can_messages = 1;
          test_timer_seconds = atoi(optarg);
        break;
      case '?':
        // Encountered an unknown or improperly formatted flag,
        // deal with these appropriately.
        //
        // getopt() populates the flag character into the 'optopt' 
        // global.
        if (optopt == 's')
        {
          reverse_power_flow_flag = 1;
          reverse_power_flow_percent = 50;
          fprintf(stdout,"rpf flag set, default %d\n", reverse_power_flow_percent);
        }
        else if (optopt == 't' )
        {
          test_can_messages = 1;
          test_timer_seconds = 10;
        }
        else
        {
          fprintf(stdout,"Unknown flag '%c'. Ignoring it", optopt);
        }
        break;
      default:
        //Hit some unexpected case - quit.
        exit(EXIT_FAILURE);
    }
  }
}


// char *get_arg (int argc, char **argv, char *name) {
//   int i;
//   for (i = 0; i < argc; i += 2)
//     if (strcmp (argv[i], name) == 0 && i+1 < argc)
//       return argv[i+1];
//   return NULL;
// }


// void options (int argc, char **argv) {
//   char *arg;
//   if ((arg = get_arg (argc, argv, "-sendcantest"))) {
//     test_can_messages = atoi (arg);
//     printf ("send can test is %d \n", test_can_messages);
//   }
//   else
//   {
//     test_can_messages = 0;
//   }

// }


void init_data()
{
  server_status = -1;
  prev_server_status = 0;
  duration_secs = 0;
  prev_duration_secs = -1;
  charge_percent = 0;
  prev_charge_percent = -500;
  time_to_event_start_secs = 0x00FFFFFF;
  prev_time_to_event_start_secs = 0;
  test_can_messages = 0;
  reverse_power_flow_flag = 0;
  reverse_power_flow_percent = 0;
  srand(time(NULL));
  // console_logf_init = 0;
  // number_log_messages = 0;

  init_queue();
  enqueue(SSP_2_0_READ_702_SF);
  enqueue(SSP_2_1A_READ_702_NAMEPLATE_PART1);
  enqueue(SSP_2_1B_READ_702_NAMEPLATE_PART2);
  enqueue(SSP_2_2_READ_702_CONFIG_INFO);
  enqueue(SSP_2_3_READ_703_ALL);
  enqueue(SSP_2_4_RECEIVED_WHMAX);
  enqueue(SSP_2_5_READ_001_PARAMS);
  enqueue(SSP_2_6_RECEIVED_HCP_SW_VERSION);
  enqueue(SSP_3_RECEIVED_DEFAULT_DERCONTROL);
  enqueue(SSP_4_1_WRITE_MUP_SETUP);
  enqueue(SSP_4_2_READ_701_SF);
  enqueue(SSP_4_3_READ_701_ACTYPE);
  enqueue(SSP_4_4_WRITE_ACTIVE_POWER_MMR_SETUP);
  enqueue(SSP_4_5_WRITE_REACTIVE_POWER_MMR_SETUP);
  enqueue(SSP_4_6_WRITE_VOLTAGE_MMR_SETUP);
  enqueue(SSP_4_7_WRITE_FREQUENCY_MMR_SETUP);
  enqueue(SSP_5_1_RECEIVED_DEFAULT_DERCONTROL);
  enqueue(SSP_6_1_READ_701_REPORT_VALUE);
  init_queue_2();

}

void setup_timerfd_for_cantest() 
{
  struct itimerspec new_value;
  new_value.it_value.tv_sec = test_timer_seconds;
  new_value.it_value.tv_nsec = 0;
  test_timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
  if (test_timerfd == -1)
  {
    perror("timerfd_create");
    exit(EXIT_FAILURE);
  }

  // set it to non-blocking
  if (fcntl(test_timerfd, F_SETFL, O_NONBLOCK))
  {
    perror("non-blocking-setup-error");
    exit(EXIT_FAILURE);
  }

  if (timerfd_settime(test_timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
  {
    perror("timerfd_settime");
    exit(EXIT_FAILURE);
  }
  
}

int main (int argc, char **argv) {
  version ();
  init_data();
  // options (argc-1, argv+1);
  parse_options(argc, argv);
  signal_init ();
  can_open ();
  if (test_can_messages)
  {
    //send_test_can();
    setup_timerfd_for_cantest();
  }
  //send_VIN();
  usock_init();
  register_process_messages_callback(process_recv_message);
  while (1) pause ();
  return 0;
}
