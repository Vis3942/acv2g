#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "utils.h"

char * app_name = "CAN2SEP2 App";

int console_logf_init = 0;

int number_log_messages = 0;

int console_log(char *message,...)
{
    // console_file_name is initialized in timer_task_init; Make sure timer_task_init is called
    FILE * log_fp;
    va_list arglist;
    time_t now;
    struct tm *tm_now;
    char buffer[80];

    number_log_messages ++;
    if (console_logf_init == 0)
    {
      console_logf_init = 1;
      log_fp = fopen("/tmp/can_log.txt","w");
    }
    else 
    {
      if (number_log_messages >= 25000)
      {
        number_log_messages = 0;
        log_fp = fopen("/tmp/can_log.txt","w");
      }
      else
      {
        log_fp = fopen("/tmp/can_log.txt","a+");
      }
    }

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


void version () {
  fprintf(stdout, "App: %s -- Version: %04x d | compiled: %s\n", app_name, VERSION,  __DATE__);
  console_log(stdout, "App: %s -- Version: %04x d | compiled: %s\n", app_name, VERSION,  __DATE__);
}

uint32_t convertBytesToUint32BigEndian(unsigned char *bytes, int start_idx)
{
  uint32_t result = 0;
  result |= ((uint32_t) bytes[start_idx]) << 24;
  result |= ((uint32_t) bytes[start_idx+1]) << 16;
  result |= ((uint32_t) bytes[start_idx+2]) << 8;
  result |= ((uint32_t) bytes[start_idx+3]);
}

time_t getCurrentTime()
{
  time_t secs = time(NULL);
  return secs;
}