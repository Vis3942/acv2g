#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "ss_proto_can.h"
#include "ss_proto.h"
#include "can.h"
#include "utils.h"

unsigned char current_state = 0;

unsigned char ss_tx_buf[MAX_SS_TX_RX_BUF_SIZE];
int curr_ss_tx_idx = 0;
int curr_ss_tx_len = 0;
int curr_ss_tx_serial_number = 0;
unsigned char recv_ack = 0; // if 1 recv_ack is true 0 => false


unsigned char can_tx_buf[8];
unsigned char can_rx_buf[8];

unsigned char ss_rx_buf[MAX_SS_TX_RX_BUF_SIZE]; 
int curr_ss_rx_len = 0;
int curr_ss_rx_serial_number = 0;

short retransmit_count = 0;
uint64_t can_transmit_millis;
short error_state_count = 0;

/**
 * @return milliseconds
 */
uint64_t get_now_time() {
  struct timespec spec;
  if (clock_gettime(1, &spec) == -1) { /* 1 is CLOCK_MONOTONIC */
    return 0;
  }
  return spec.tv_sec * 1000 + spec.tv_nsec / 1e6;
}

void check_response_timeout()
{
  uint64_t now_millis;
  int tmp_elapsed;
  if (current_state == SSP_COMMAND_STATE) 
  {
    now_millis = get_now_time();
    if ( (can_transmit_millis > 0) && (now_millis > 0) )
    {
      tmp_elapsed = now_millis - can_transmit_millis;
      if (tmp_elapsed > SSP_CAN_TIMEOUT_MILLIS ) 
      {
        retransmit_count ++;
        if (retransmit_count > SSP_CAN_MAX_RETRIES)
        {
          current_state = SSP_ERROR_STATE;
          error_state_count = 0;
          can_transmit_millis = get_now_time();
        }
        else 
        {
          current_state = SSP_COMMAND_STATE;
          curr_ss_tx_idx = 0;
          curr_ss_tx_serial_number = 0;
          send_ss_can_message();
        }
      }
    }
  }
  else if (current_state == SSP_ERROR_STATE) 
  {
    error_state_count++;
    if (error_state_count > SSP_ERROR_MAX_COUNT)
    {
      //current_state = SSP_COMMAND_STATE;
      //curr_ss_tx_idx = 0;
      //curr_ss_tx_serial_number = 0;
      //send_ss_can_message();
      current_state = SSP_IDLE_STATE; // GO TO THE NEXT COMMAND FAILED RETRY ATTEMPTS
    }
  }
}

/*
 * This function is to be called after a successful transmit and ack bit is set
 * Then call send_ss_can_message to send the next frame
 */
void update_can_tx_idx()
{
  curr_ss_tx_idx += 6;
  curr_ss_tx_serial_number ++;
  if (curr_ss_tx_idx >= curr_ss_tx_len) 
  {
    current_state = SSP_RESPONSE_STATE;
    curr_ss_rx_len = 0;
    curr_ss_rx_serial_number = 0;
  }
}

/*
 * After receiving the CAN message, copy the data into the can_tx_buf.
 *    then call this function. This function will set the ACK bit to 1, and 
 *    transmit on CAN bus
 */
void set_ack_transmit()
{
  can_tx_buf[1] = (unsigned char) (can_tx_buf[1] | (1 << 7)); // set ack bit
  can_transmit (SSP_CAN_TX_ID, (char*)can_tx_buf, 8);
}

void recv_ss_can_message(char* data)
{
  int tmp_ser_num = -1;
  if ( (current_state == SSP_COMMAND_STATE) || (current_state == SSP_ERROR_STATE) )
  {
    tmp_ser_num = (int) (data[1] & 0x1F);
    if (tmp_ser_num == curr_ss_tx_serial_number) 
    {
      if ( (data[1] & 0x80) == 0x80) // ack bit is set, send next frame or go to RESPONSE_STATE
      {
        if ( (data[1] & 0x40) == 0x40) // last frame bit is set
        {
          current_state = SSP_RESPONSE_STATE;
          curr_ss_rx_serial_number = 0;
          curr_ss_rx_len = 0;
        }
        else
        {
          curr_ss_tx_serial_number++;
          curr_ss_tx_idx += 6;        
          send_ss_can_message();
        }
      }
    }
  }
  else if (current_state == SSP_RESPONSE_STATE) 
  {
    tmp_ser_num = (int) (data[1] & 0x1F);
    // expecting serial number is curr_ss_rx_serial_num
    if ( (curr_ss_rx_len + 6) >= MAX_SS_TX_RX_BUF_SIZE ) {
      //printf("INSUFFICIENT MEMORY TO PROCESS Rx message. Aborting processing. \n");
      //printf("curr rx pos %d, max available index %d \n", MAX_SS_TX_RX_BUF_SIZE);
      console_log("INSUFFICIENT MEMORY TO PROCESS Rx message. Aborting processing. \n");
      console_log("curr rx pos %d, max available index %d \n", MAX_SS_TX_RX_BUF_SIZE);
      return;
    }
    if (curr_ss_rx_serial_number == tmp_ser_num) 
    {
      memcpy(can_tx_buf, data, 8);
      memcpy(&ss_rx_buf[curr_ss_rx_len], &can_tx_buf[2], 6);
      curr_ss_rx_len += 6;
      curr_ss_rx_serial_number ++;
      if ( (data[1] & 0x40) == 0x40 ) {
        // last frame process data if it is a read command
        process_recv_message_ssproto();
        current_state = SSP_IDLE_STATE;
      }
      set_ack_transmit();
    }
  }
}

void send_ss_can_message() 
{
  int ii;
  recv_ack = 0; // clear any previous ack
  memset(can_tx_buf, 0, 8); // clear any prev data
  can_tx_buf[0] = 0x10;
  can_tx_buf[1] = 0x1F & curr_ss_tx_serial_number;
  if ( (curr_ss_tx_idx + 6) >= curr_ss_tx_len )
  {
    can_tx_buf[1] = can_tx_buf[1] | (1 << 6); // last frame flag is set
  }
  ii = 0;
  while ( ( (curr_ss_tx_idx + ii ) < curr_ss_tx_len ) && (ii < 6) )
  {
    can_tx_buf[2+ii] = ss_tx_buf[curr_ss_tx_idx + ii];
    ii++;
  }
  can_transmit_millis = get_now_time();
  can_transmit (SSP_CAN_TX_ID, (char *)can_tx_buf, 8);
  write_can_data_csv((int)SSP_CAN_TX_ID, (char *)can_tx_buf);
 
}

/*
 * Populate the ss_tx_buf with the SunSpec Modbus message
 *    and set the curr_ss_tx_len to the length of the modbus message to be sent.
 *    Then call this function to start the transmission of ss_tx_buf over CAN
 */
void start_ss_can_proto()
{
  if (current_state == SSP_IDLE_STATE) 
  {
    current_state = SSP_COMMAND_STATE;
    curr_ss_tx_idx = 0;
    curr_ss_tx_serial_number=0;
    send_ss_can_message();
  }
  else 
  {
    console_log("ss can proto is in %d state: Cannot start proto \n", current_state);
  }
}

unsigned char get_current_state()
{
  return current_state;
}