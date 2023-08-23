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
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>


#include "usock_utils.h"
#include "usock_server.h"
#include "utils.h"
#include "usock_proto.h"
#include "task_queue.h"
#include "ss_proto.h"
#include "ss_proto_can.h"
#include "loc_can.h"

//#define MAX(x,y) ((x) > (y)? (x) : (y))

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
int test_sep2_mirror_usock = 0;
int test_ss_proto_can = 0;
int test_ss_proto_id = -1;
int test_ev_param_post_usock = 0;
int test_custom_ss_model_read = 0;
//extern int test_ss_model_num = 0;
//extern int test_ss_model_start_addr = -1;
//extern int test_ss_model_regs_read_count = 0;
int test_der_function = 0;
int test_der_avail = -1; // default not available
int test_der_wsetpct = 0;

int test_ss_curve_data = 0;
int test_ss_curve_type = -1;

int reverse_power_flow_flag;
int reverse_power_flow_percent;
int proto_timer_seconds = 5;
int test_timer_seconds = 5;
int test_timerfd;
int proto_timerfd; // for sunspec profile proto impl

int usock_init_done = 0; // 1 if done
int timers_init_done = 0; // 1 if done

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
  //double tmpdbl;
  int tmpi;
  int16_t tmp16_t;
  int send_to_hcp = 0;
  char data[8];
  // debug
  //fprintf(stdout, "id recv %d\n", id);
  switch (id) 
  {
  case 0x30A: // HCP_DER_MSG_01
#ifdef PRINT_CAN_IDS
  fprintf(stdout,"can id 0x30A: HCP_DER_MSG_01 \n");
  fprintf(stdout,"Tx %d [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d]\n", id, data_recv[0], 
    data_recv[1], data_recv[2], data_recv[3], data_recv[4], 
    data_recv[5], data_recv[6], data_recv[7]);

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
    tmpi = tmpi + ( data_recv[6] << 1 );
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
  
  case SSP_CAN_RX_ID:
    recv_ss_can_message(data_recv);
    send_to_hcp = 0;
    break;

  default:
    // do nothing 
    send_to_hcp = 0;
    break;
  }
#ifdef PRINT_CAN_IDS
  fprintf(stdout,"Rx %d [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d]\n", id, data_recv[0], 
    data_recv[1], data_recv[2], data_recv[3], data_recv[4], 
    data_recv[5], data_recv[6], data_recv[7]);
#endif

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

    if (comm_status)
    {
      data[0] = data[0] | 0x20; // no LOC
    }
    else 
    {
      data[0] = data[0] | 0x40; // LOC
    }

    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    can_transmit((int)0x30F, data, 8);
    usleep(5000);
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = (uint8_t)get_ss_proto_task_id(); // ss proto task id
    data[7] = (uint8_t)get_current_state(); // ss proto can state
    can_transmit((int)0x329, data, 8);
  }
}


void message_received (int x) {
  struct can_frame frame;
  struct timeval timeout = {0};
  fd_set rfds, wfds;
  int nfds;
  ssize_t s;
  uint64_t exp_count;

  int tmpmax;
  if (usock_init_done == 1)
  {
    tmpmax = MAX(can_socket, srv2cli_usock_fd);
    tmpmax = MAX(tmpmax, conn_srv2cli_usock_fd);
    tmpmax = MAX(tmpmax, cli2srv_usock_fd);
    tmpmax = MAX(tmpmax, conn_cli2srv_usock_fd);
  }
  else 
  {
    tmpmax = can_socket;
  }

  if (timers_init_done)
  {
    tmpmax = MAX(tmpmax, proto_timerfd);
    if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock)) 
    {
      tmpmax = MAX(tmpmax, test_timerfd);
    }
  }
  nfds = tmpmax+1;

  FD_ZERO (&rfds); FD_ZERO (&wfds);
  FD_SET (can_socket, &rfds);
  if (usock_init_done == 1)
  {
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
  }
  if (timers_init_done)
  {
    FD_SET(proto_timerfd, &rfds);
    if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock) )
    {
      FD_SET(test_timerfd, &rfds);
    }
  }
  // debug
  //fprintf(stdout, "in message received \n");
  if (select (nfds, &rfds, NULL, NULL, &timeout) > 0) {
  // if (select (nfds, &rfds, NULL, NULL, NULL) > 0) {

    //debug
    //fprintf(stdout," in select call with io recv \n");
    if (FD_ISSET (can_socket, &rfds)) {
      // debug 
      //fprintf(stdout, "can socket read next \n");
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

    if (usock_init_done == 1)
    {
      if (FD_ISSET (cli2srv_usock_fd, &rfds)) 
      {
        fprintf(stdout, "usock client2server accepts \n");
        usock_client2server_accept();
      }

      if (FD_ISSET (srv2cli_usock_fd, &rfds))
      {
        fprintf(stdout, "usock server2cleint accepts \n");
        usock_server2client_accept();
      }

      if (conn_cli2srv_usock_fd > 0)
      {
        fprintf(stdout, "read message client2server \n");
        if (FD_ISSET (conn_cli2srv_usock_fd, &rfds)) usock_client2server_read_message();
      }
    }

    if (timers_init_done)
    {
      // conn_srv2cli_usock_fd is only for writing messages
      if (FD_ISSET (proto_timerfd, &rfds))
      {
        fprintf(stdout, "proto timer triggered \n");
        s = read(proto_timerfd, &exp_count, sizeof(uint64_t));
        if (s != sizeof(uint64_t))
        {
          perror("read timerfd:");
          return;
        }
        else 
        {
          //debug
          ss_proto_task();
        }
      }

      if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock) )
      {
        if (FD_ISSET (test_timerfd, &rfds)) 
        {
          // debug 
          fprintf(stdout, "timer id triggered \n");

          s = read(test_timerfd, &exp_count, sizeof(uint64_t));
          if (s != sizeof(uint64_t))
          {
            perror("read timerfd:");
            return;
          }
          else 
          {
            //debug
            fprintf(stdout, "test timerfd fired \n");
          }
          if (test_can_messages)
          {
            send_test_can_messages();
          }
          else if (test_sep2_mirror_usock)
          {
            test_mirror_usock();
          }
          else if (test_ev_param_post_usock)
          {
            test_ev_params_post_usock();
          }
        }
      }
    }

  }
}

void print_options()
{
  printf("can2sep [options]\n");
  printf("\t -t <time interrval>; send test can messages periodically at time interval\n");
  printf("\t -m <time interval>; test setup and sending of 2030.5 mirror setup and periodic send messages\n");
  printf("\t -c <app id for read regs>; test sunspec can proto, perform read based on app identifier\n");
  printf("\t -e <time interval>; send ev parameters after specified time interval\n");
  printf("\t -s <sunspec model>; specify sunspec model to read from as integer \n");
  printf("\t -a <model start addr>; specify start address to read from model as int \n");
  printf("\t -b <number of regs to read>; specify number of regs to read as int \n");
  printf("\t -d <0 no der, 1 der present, specify -p for wsetpct>\n");
  printf("\t -p <wset pct can be +ve or -ve >\n");
  printf("\t -q <send curves to OBCM 0 => for default volt-var curve; others values reserved>\n");
  printf("\t -h: print this help info\n");
  exit(EXIT_SUCCESS);
}

void signal_init () {
  struct sigaction action;
  // struct sigevent event;
  // struct itimerspec expire;
  //signal (SIGPIPE, SIG_IGN); 
  action.sa_handler = message_received;
  action.sa_flags = 0;
  if (sigaction (SIGIO, &action, NULL) < 0)
    fprintf(stdout,"sigaction: %d\n", errno);
  // enable SIGIO signaling for new messages
  }

// update this array if the defines SSP_X_X_.... changes
int read_ss_ids[] = {
  2,3,4,5,6,8,51, 56,60,64, 
  70, 74, 80, 84, 90, 94, 100, 104,
  110, 114, 120, 124, 141, 142, 152, 153, 160
};
int read_ss_ids_length = 27;
int is_identifier_read_only(int app_ss_identifier)
{
  int ii;
  for (ii=0; ii<read_ss_ids_length; ii++)
  {
    if (read_ss_ids[ii] == app_ss_identifier)
    {
      return 1;
    }
  }
  return 0;
}

void parse_options (int argc, char **argv) {
  int arg;
  while ((arg = getopt (argc, argv, "r:t:m:hce:s:a:b:d:p:q:")) != -1)
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
      case 'h':
        print_options();
        break;
      case 'm':
        test_sep2_mirror_usock = 1;
        test_timer_seconds = atoi(optarg);
        break;
      case 'c':
        test_ss_proto_can = 1;
        test_ss_proto_id = atoi(optarg);
        if (!is_identifier_read_only(test_ss_proto_id))
        {
          fprintf(stdout, "provided app identifier is not a read defaulting to READ_703_ALL\n");
          test_ss_proto_id = SSP_2_3_READ_703_ALL;
        }
        enqueue(test_ss_proto_id);
        break;
      case 'e':
        test_ev_param_post_usock = 1;
        test_timer_seconds = atoi(optarg);
        break;
      case 's':
        test_custom_ss_model_read = 1;
        test_ss_model_num = atoi(optarg);
        break;
      case 'a':
        test_custom_ss_model_read = 1;
        test_ss_model_start_addr = atoi(optarg);
        break;
      case 'b':
        test_custom_ss_model_read = 1;
        test_ss_model_regs_read_count = atoi(optarg);
        break;
      case 'd':
        test_der_function = 1;
        test_der_avail = atoi(optarg);
        if (test_der_avail > 1)
        {
          test_der_avail = 1;
        }
        else if (test_der_avail < 0)
        {
          test_der_avail = 0;
        }
        break;
      case 'p':
        test_der_wsetpct = atoi(optarg);
        break;
      case 'q':
        test_ss_curve_data = 1;
        test_ss_curve_type = atoi(optarg);
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
        print_options();
        exit(EXIT_FAILURE);
    }
  }
  if (test_custom_ss_model_read == 1)
  {
    if ( (test_ss_model_num > 0) && 
          (test_ss_model_start_addr > -1) && 
          (test_ss_model_regs_read_count > 0) 
        )
    {
      enqueue(SSP_TEST_READ_CUSTOM_MODEL);

    }
    else 
    {
      fprintf(stdout, "Invalid options for custom ss model read; require options s, a, b \n");
      fprintf(stdout, "model num = %d, start addr = %d, num regs to read = %d \n",
        test_ss_model_num, test_ss_model_start_addr, test_ss_model_regs_read_count);
      print_options(EXIT_FAILURE);
    }
  }
  else if (test_der_function == 1)
  {
    if ( (test_der_avail == 1) && (test_der_wsetpct != 0) )
    {
      // setup parameters for the test
      server_status = test_der_avail;
      comm_status = 1;
      evcc_es = 1;        
      ES = 1;
      wset_pct_704 = test_der_wsetpct;
      wset_pct_ena_704 = 1;

      enqueue(SSP_5_2_WRITE_703_ES);
      enqueue(SSP_DER_WRITE_704_PARAMS); 
      enqueue(SSP_DER_WRITE_704_ENABLE);   
    }
    else if (test_der_avail == 0)
    {
        evcc_es = 0;
        ES = 0;
        wset_pct_704 = 0;
        comm_status = 0;
        wset_pct_ena_704 = 0;
        
      enqueue(SSP_5_2_WRITE_703_ES);
      enqueue(SSP_DER_WRITE_704_PARAMS);    
      enqueue(SSP_DER_WRITE_704_ENABLE);   
    }
    else 
    {
      //discard options and exit
      fprintf(stdout, "invalid options for DER setup\n");
      fprintf(stdout, "require der avail value (given: %d), and wsetpct (given %d) \n",
        test_der_avail, test_der_wsetpct);
      exit(EXIT_FAILURE);
    }
  }
  else if (test_ss_curve_data == 1)
  {
    if (test_ss_curve_type != 0)
    {
      fprintf("supported curve types are [0] => voltvar curve, type specified %d. Exit App\n", test_ss_curve_type);
      exit(EXIT_FAILURE);
    }
    else 
    {
      volt_var_points_count = 4;
      volt_var_curve_received = 1;
      setVRef = (short)208;
      v_sf_705 = (short) setVRef;
      vamax_702 = (short)660;
      volt_var_x[0] = 0.920*setVRef;
      volt_var_y[0] = 0.30*vamax_702;
      volt_var_x[1] = 0.967*setVRef;
      volt_var_y[1] = 0;
      volt_var_x[2] = 1.033*setVRef;
      volt_var_y[2] = 0;
      volt_var_x[3] = -0.30*vamax_702;
      volt_var_y[3] = 0.30*vamax_702;
      enqueue(SSP_2_2_READ_702_CONFIG_INFO);
      enqueue(SSP_3_READ_705_SF);
      enqueue(SSP_3_WRITE_705_PARAMS_1);
      enqueue(SSP_3_WRITE_705_PARAMS_2);
      enqueue(SSP_3_WRITE_705_CURVE_DATA);
      enqueue(SSP_3_WRITE_705_CURVE_VERIFY_REQ);
      enqueue(SSP_3_READ_705_CURVE_VERIFY_RESP);
      enqueue(SSP_3_WRITE_705_CURVE_ENABLE);
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
  test_sep2_mirror_usock = 0;
  srand(time(NULL));
  // console_logf_init = 0;
  // number_log_messages = 0;

  init_queue();
  init_queue_2();

}

void init_ssproto()
{
  if ( (!test_ss_proto_can) && (!test_custom_ss_model_read) && 
       (!test_der_avail) && (!test_ss_curve_data) 
     ) 
  {
    enqueue(SSP_1_0_RECEIVED_DERSETTINGS);
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
    enqueue(SSP_DER_READ_704_SF);
  }

}

void setup_proto_timerfd()
{
  struct itimerspec new_value;
  struct timespec now;

  if (clock_gettime(CLOCK_REALTIME, &now) == -1)
      perror("clock_gettime");

  new_value.it_value.tv_sec = now.tv_sec + proto_timer_seconds;
  new_value.it_value.tv_nsec = now.tv_nsec;
  new_value.it_interval.tv_sec = proto_timer_seconds;
  new_value.it_interval.tv_nsec = 0;
  proto_timerfd = timerfd_create(CLOCK_REALTIME, 0);
  //proto_timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
  if (proto_timerfd == -1)
  {
    perror("timerfd_create");
    exit(EXIT_FAILURE);
  }

  // set it to non-blocking
  if (fcntl(proto_timerfd, F_SETFL, O_NONBLOCK))
  {
    perror("non-blocking-setup-error");
    exit(EXIT_FAILURE);
  }

  if (timerfd_settime(proto_timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
  {
    perror("timerfd_settime");
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "timerfd setup for SSProto \n");

}


void setup_timerfd_for_test() 
{
  struct itimerspec new_value;
  struct timespec now;

  if (clock_gettime(CLOCK_REALTIME, &now) == -1)
      perror("clock_gettime");

  new_value.it_value.tv_sec = now.tv_sec + test_timer_seconds;
  new_value.it_value.tv_nsec = now.tv_nsec;
  new_value.it_interval.tv_sec = test_timer_seconds;
  new_value.it_interval.tv_nsec = 0;
  test_timerfd = timerfd_create(CLOCK_REALTIME, 0);
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
  fprintf(stdout, "timerfd setup for test \n");

}

int main (int argc, char **argv) {
  version ();
  init_data();
  // options (argc-1, argv+1);
  parse_options(argc, argv);
  signal_init ();
  can_open ();
  init_ssproto();
  if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock))
  {
    //send_test_can();
    setup_timerfd_for_test();
  }
  setup_proto_timerfd();
  timers_init_done=1;
  //send_VIN();
  usock_init();
  usock_init_done = 1;  
  register_process_messages_callback(process_recv_message);

  //signal_init();
  while (1) pause ();
  
  // fprintf(stdout, "before message_received loop \n");
  // while (1) 
  // {
  //   // fprintf(stdout, "before calling message_received \n");
  //   message_received(27); // 27 just a random value, to be compatible with earlier signature, not used
  //   // sleep(5);
  // }

  return 0;
}
