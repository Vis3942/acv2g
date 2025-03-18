#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#include "utils.h"

char * app_name = "CAN2SEP2 App";

int console_logf_init = 0;

int number_log_messages = 0;
int number_data_messages = 0;
char * can_data_filename = "/tmp/can_data.csv";
int proto_timer_seconds = 5;
int32_t evcc_es=0; // 1 => true 0 => false
int override_power_status = -1;
int override_max_forward_power = -1;
int override_charge_power_now = -1;

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
  console_log("App: %s -- Version: %04x d | compiled: %s\n", app_name, VERSION,  __DATE__);
}

uint32_t convertBytesToUint32BigEndian(unsigned char *bytes, int start_idx)
{
  uint32_t result = 0;
  result |= ((uint32_t) bytes[start_idx]) << 24;
  result |= ((uint32_t) bytes[start_idx+1]) << 16;
  result |= ((uint32_t) bytes[start_idx+2]) << 8;
  result |= ((uint32_t) bytes[start_idx+3]);
  return result;
}

time_t getCurrentTime()
{
  time_t secs = time(NULL);
  return secs;
}

void displayTime() 
{
  // time_t rawtime;
  // struct tm *timeinfo;
  // char buffer[80];

  // time(&rawtime);
  // timeinfo = localtime(&rawtime);

  // strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S");
  // fprintf(stdout, "%s.%03d", buffer, milliseconds)
  fprintf(stdout, "[%lu] ", (unsigned long)time(NULL));
}

int bytesToInt(char* bytes, int start_idx)
{
  int result = 0;
  // debug
  fprintf(stdout, "bytesToInt 0x%02x, 0x%02x, 0x%02x, 0x%02x\n", bytes[start_idx], bytes[start_idx + 1],
        bytes[start_idx+2], bytes[start_idx+3]);
  result |= bytes[start_idx  + 3] << 24;
  result |= bytes[start_idx  + 2] << 16;
  result |= bytes[start_idx  + 1] << 8;
  result |= bytes[start_idx];
  return result;
}


void init_can_data_csv()
{
  FILE *fpt;

  fpt = fopen(can_data_filename, "w");

  if (fpt != NULL)
  {
    fprintf(fpt, "id, data0, data1, data2, data3, data4, data5, data6, data7, timestamp\n");
    fclose(fpt);
  }
}

void write_can_data_csv(int id, char*data)
{
  FILE *fpt;

  if (number_data_messages > MAX_NUM_DATA_MESSAGES)
  {
    return;
  }


  fpt = fopen(can_data_filename, "a");

  if (fpt != NULL)
  {
    number_data_messages ++;
    fprintf(fpt, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %u\n",
      id, data[0], data[1], data[2], data[3], data[4], 
      data[5], data[6], data[7], (unsigned)time(NULL));
    fclose(fpt);
  }

}

int startsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

#define DELIM_PARAM "="
void read_parameters_from_file(char * param_file_name)
{
  // default values if not specified in file
  proto_timer_seconds = 5;
  FILE *file = fopen (param_file_name, "r");
  size_t tmpst;
  if (file != NULL)
  {
    char line[1024];
    while(fgets(line, sizeof(line), file) != NULL)
    {
      char *cfline;
      cfline = strstr((char *)line,DELIM_PARAM);
      cfline = cfline + strlen(DELIM_PARAM);
      if (startsWith(line, "proto_timer_seconds"))
      {
        tmpst = strlen(cfline);
        cfline[tmpst] = '\0';
        proto_timer_seconds = atoi(cfline);
      }
      else if (startsWith(line, "override_power_status"))
      {
        tmpst = strlen(cfline);
        cfline[tmpst] = '\0';
        override_power_status = atoi(cfline);
      }
      else if (startsWith(line, "override_max_forward_power"))
      {
        tmpst = strlen(cfline);
        cfline[tmpst] = '\0';
        override_max_forward_power = atoi(cfline);
      }
      else if (startsWith(line, "override_charge_power_now"))
      {
        tmpst = strlen(cfline);
        cfline[tmpst] = '\0';
        override_charge_power_now = atoi(cfline);
      }

    } // End while
    fclose(file);
    // debug
    fprintf(stdout, "Params from %s\n", param_file_name);
    fprintf(stdout, "proto timer secs = %d \n", 
        proto_timer_seconds);
    fprintf(stdout, "override power status = %d \n", 
        override_power_status);
    fprintf(stdout, "override max forward power = %d \n",
        override_max_forward_power);
    fprintf(stdout, "override charge power now = %d \n",
        override_charge_power_now); 
  } 
  else 
  {
    fprintf(stdout, "Unable to locate %s file. Using default values.\n", param_file_name);
  } // End if file
}

void charArrayToHexString(const char *input, size_t length, char *output, size_t output_max_len) {
    static const char hexDigits[] = "0123456789ABCDEF";

    // Ensure the output buffer is large enough
    if (output == NULL || length * 2 + 1 > output_max_len) { 
        fprintf(stderr, "Output buffer is too small or NULL.\n");
        return;
    }

    for (size_t i = 0; i < length; i++) {
        unsigned char byte = (unsigned char)input[i];
        output[i * 2]     = hexDigits[(byte >> 4) & 0x0F]; // High nibble
        output[i * 2 + 1] = hexDigits[byte & 0x0F];        // Low nibble
    }

    output[length * 2] = '\0'; // Null-terminate the hex string
}