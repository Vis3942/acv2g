#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "can2sep2_proxy.h"

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


static char log_file_name[32];
static char console_file_name[64];
static char unix_sock_tms_path[128];

int32_t server_status; // 0=> not found, 1 => found, 2 => searching, -1 => just initialized
int32_t charge_percent; // 0=> do not charge/ discharge, -100 charge at 100%, -25 charge at 25%, 100 discharge at 100%
int32_t duration_secs; // convert to mins before sending on can BUS
int32_t time_to_event_start_secs;
//int32_t time_left_der_mins; 

int32_t max_charge_rate;
int32_t max_discharge_rate;
float current_soc;
float target_soc = 98.0f;
int32_t time_charge_is_neeeded;
int32_t max_charge_duration_secs;
int32_t availability_duration_secs; 
int32_t reserve_percentage = 65;

int log_data(char *message,...)
{
    FILE * log_fp;
    va_list arglist;
    time_t now;
    struct tm *tm_now;
    char buffer[80];

    log_fp = fopen(log_file_name,"a+");
    if (log_fp == NULL)
        return 0;
    now = time(NULL);
    tm_now = localtime(&now);
    strftime (buffer, 80, "[%Y-%m-%d %H:%M:%S]", tm_now);
    fprintf(log_fp,"%s",buffer);
    va_start(arglist,message);
    vfprintf(log_fp,message,arglist);
    va_end(arglist);
    //fprintf(log_fp," \n");
    fclose(log_fp);
    return 1;
}

int console_log(char *message,...)
{
    // console_file_name is initialized in timer_task_init; Make sure timer_task_init is called
    FILE * log_fp;
    va_list arglist;
    time_t now;
    struct tm *tm_now;
    char buffer[80];

    log_fp = fopen(console_file_name,"a+");
    if (log_fp == NULL)
        return 0;
    now = time(NULL);
    tm_now = localtime(&now);
    strftime (buffer, 80, "[%Y-%m-%d %H:%M:%S]", tm_now);
    fprintf(log_fp,"%s",buffer);
    va_start(arglist,message);
    vfprintf(log_fp,message,arglist);
    va_end(arglist);
    //fprintf(log_fp," \n");
    fclose(log_fp);
    return 1;
}

void can2sep2_init_filenames()
{
    struct tm *tmp_time;
    time_t now;
    now = time(NULL);
    tmp_time = localtime(&now);
    strftime(log_file_name, 32, "./CAN2SEP2proxy_%Y_%m_%d_%H_%M.log", tmp_time);
    strftime(console_file_name, 64,  "./CAN2SEP2proxy_print_out_%Y_%m_%d_%H_%M.txt", tmp_time);
}

void can2sep2_task_init()
{
    can2sep2_init_filenames();
    strncpy(unix_sock_tms_path, "/tmp/can2sep2", 128);

    server_status = 0;
    charge_percent = 0;
    duration_secs = 0;
    time_to_event_start_secs = 0x00FFFFFF;

}


#define UNIX_SOCK_UNCONNECTED 0x00
#define UNIX_SOCK_CONNECTED 0x01
#define UNIX_SOCK_ERROR     0x02
int unix_sock_fd;
int unix_sock_status;

void close_usock()
{
  if (unix_sock_fd > 0)
  {
    close(unix_sock_fd);
    unix_sock_fd = 0;
  }
}


int us_comms_init()
{
    struct sockaddr_un remote;
    size_t len;
    
    if (unix_sock_fd > 0)
    {
        close(unix_sock_fd);
        unix_sock_fd = 0;
    }

    // return 0 if succ else return errno
    if ((unix_sock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return errno;
    }

    console_log("Trying to connect...%s\n", unix_sock_tms_path);

    remote.sun_family = AF_UNIX;
    //strcpy(remote.sun_path, SOCK_PATH);
    strcpy(remote.sun_path, unix_sock_tms_path);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(unix_sock_fd, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        return errno;
    }
    console_log("Connected.\n");
    return 0;
}

int us_communications()
{
    // return errno if failed to init/ send/ recv data
    // return 0 if succ
    int sts;
    uint16_t data_u16_cmd;
    uint16_t tmp_u16;
    uint16_t write_ids_count;  
    int n, ii;

    //console_log("prev: unix sock sts %d\n", unix_sock_status);    
    if (unix_sock_status != UNIX_SOCK_CONNECTED)
    {
        sts = us_comms_init();
        if (sts == 0)
        {
            unix_sock_status = UNIX_SOCK_CONNECTED;
            return 0;
        }
        else
        {
            unix_sock_status = 0;
            return sts;
        }
    }
    // debug
    console_log("unix sock sts %d, socket file descriptor %d \n", unix_sock_status, unix_sock_fd);    
    if ( (unix_sock_status == UNIX_SOCK_CONNECTED) && (unix_sock_fd > 0) )
    {
        tmp_u16 = 0xFFFF;
        if (send(unix_sock_fd, &tmp_u16, sizeof(uint16_t), 0) == -1)
        {
            unix_sock_status = UNIX_SOCK_ERROR;
            perror("Send");
            return errno;
        }
        // read number of write ids
        n = recv(unix_sock_fd, &tmp_u16, sizeof(tmp_u16), 0);
        if ( (n < 0) || (n == 0) )
        {
            if (n < 0) perror("recv");
            unix_sock_status = UNIX_SOCK_ERROR;
            return errno;
        }
        write_ids_count = (int)tmp_u16;
        for (ii=1; ii <= write_ids_count; ii++)
        {
            // read id
            n = recv(unix_sock_fd, &tmp_u16, sizeof(tmp_u16), 0);
            if ( (n < 0) || (n == 0) )
            {
                if (n < 0) perror("recv");
                unix_sock_status = UNIX_SOCK_ERROR;
                return errno;
            }
            // read value corresponding to id
            switch(tmp_u16)
            {
                case (uint16_t)MAX_CHARGE_RATE_READ_ID:
                    n = recv(unix_sock_fd, &max_charge_rate, sizeof(int32_t), 0);
                    if ( (n < 0) || (n == 0) )
                    {
                        if (n < 0) perror("recv");
                        close_usock();
                        return errno;
                    }
                break;

                case (uint16_t)MAX_DISCHARGE_RATE_READ_ID:
                    n = recv(unix_sock_fd, &max_discharge_rate, sizeof(int32_t), 0);
                    if ( (n < 0) || (n == 0) )
                    {
                        if (n < 0) perror("recv");
                        close_usock();
                        return errno;
                    }
                break;

                case (uint16_t)CURRENT_SOC_READ_ID:
                    n = recv(unix_sock_fd, &current_soc, sizeof(float), 0);
                    if ( (n < 0) || (n == 0) )
                    {
                        if (n < 0) perror("recv");
                        close_usock();
                        return errno;
                    }
                break;

                case (uint16_t)TARGET_SOC_READ_ID:
                    n = recv(unix_sock_fd, &target_soc, sizeof(float), 0);
                    if ( (n < 0) || (n == 0) )
                    {
                        if (n < 0) perror("recv");
                        close_usock();
                        return errno;
                    }
                break;

                case (uint16_t)TIME_CHARGE_NEEDED_READ_ID:
                    n = recv(unix_sock_fd, &time_charge_is_neeeded, sizeof(int32_t), 0);
                    if ( (n < 0) || (n == 0) )
                    {
                        if (n < 0) perror("recv");
                        close_usock();
                        return errno;
                    }
                break;

                case (uint16_t)MAX_CHARGE_DURATION_READ_ID:
                    n = recv(unix_sock_fd, &max_charge_duration_secs, sizeof(int32_t), 0);
                    if ( (n < 0) || (n == 0) )
                    {
                        if (n < 0) perror("recv");
                        close_usock();
                        return errno;
                    }
                break;

                case (uint16_t)AVAILABILITY_SECS_READ_ID:
                    n = recv(unix_sock_fd, &availability_duration_secs, sizeof(int32_t), 0);
                    if ( (n < 0) || (n == 0) )
                    {
                        if (n < 0) perror("recv");
                        close_usock();
                        return errno;
                    }
                break;
            }
        }
        tmp_u16 = 0x7FFF;
        if (send(unix_sock_fd, &tmp_u16, sizeof(uint16_t), 0) == -1)
        {
            unix_sock_status = UNIX_SOCK_ERROR;
            perror("Send");
            return errno;
        }
        //fprintf(stdout, "sending second cmd %x, num bytes %d \n", tmp_u16, n);

        tmp_u16 = (uint16_t) NUMBER_WRITE_IDS;
        if (send(unix_sock_fd, &tmp_u16, sizeof(uint16_t), 0) == -1)
        {
            unix_sock_status = UNIX_SOCK_ERROR;
            perror("Send");
            return errno;
        }
        //fprintf(stdout, "sending write id count %x, num bytes %d \n", tmp_u16, n);
        
        for (ii=1; ii<=(uint16_t) NUMBER_WRITE_IDS; ii++)
        {
            // write the ids
            tmp_u16 = (uint16_t)( ii + 0x8000 );
            if (send(unix_sock_fd, &tmp_u16, sizeof(uint16_t), 0) == -1)
            {
                unix_sock_status = UNIX_SOCK_ERROR;
                perror("Send");
                return errno;
            }
            //fprintf(stdout, "Write id %x, num bytes = %d \n", tmp_u16, n);
            // write values corresponding to ids
            switch(ii + 0x8000)
            {
                case (int)SERVER_STATUS_WRITE_ID:
                    n = send(unix_sock_fd, &server_status , sizeof(int32_t), 0);
                    if (n < 0)
                    {
                        perror("send");
                        close_usock();
                        return errno;
                    }
                    //fprintf(stdout, "Write value %x, num bytes = %d \n", server_status, n);
                break;

                case (int)CHARGE_PERCENT_WRITE_ID:
                    n = send(unix_sock_fd, &charge_percent , sizeof(int32_t), 0);
                    if (n < 0)
                    {
                        perror("send");
                        close_usock();
                        return errno;
                    }
                    //fprintf(stdout, "Write value %x, num bytes = %d \n", charge_percent, n);
                break;
                
                case (int)DURATION_SECS_WRITE_ID:
                    n = send(unix_sock_fd, &duration_secs , sizeof(int32_t), 0);
                    if (n < 0)
                    {
                        perror("send");
                        close_usock();
                        return errno;
                    }
                    //fprintf(stdout, "Write value %x, num bytes = %d \n", duration_secs, n);
               break;

                case (int)TIME_2_EVENT_SECS_WRITE_ID:
                    n = send(unix_sock_fd, &time_to_event_start_secs , sizeof(int32_t), 0);
                    if (n < 0)
                    {
                        perror("send");
                        close_usock();
                        return errno;
                    }
                    //fprintf(stdout, "Write value %x, num bytes = %d \n", time_to_event_start_secs, n);
                break;
            }
        }
    }
    //fprintf(stdout, "\n\n xxxx ----- xxxx ----- xxxxx ----- xxxxx \n\n");
    return 0;
}

void can2sep2_task_func()
{
    us_communications();
}