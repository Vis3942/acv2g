#ifndef SS_PROTO_CAN_H
#define SS_PROTO_CAN_H

#define MAX_SS_TX_RX_BUF_SIZE 1024
// SSP => SunSpec Proto
#define SSP_IDLE_STATE 0x00
#define SSP_COMMAND_STATE 0x01
#define SSP_RESPONSE_STATE 0x02
#define SSP_ERROR_STATE 0xFF

#define SSP_CAN_TX_ID 0x30D
#define SSP_CAN_RX_ID 0x30E

#define SSP_CAN_TIMEOUT_MILLIS 200
#define SSP_CAN_MAX_RETRIES 0x03
#define SSP_ERROR_MAX_COUNT 25

// extern variables
extern unsigned char ss_tx_buf[MAX_SS_TX_RX_BUF_SIZE];
extern int curr_ss_tx_len;
extern unsigned char ss_rx_buf[MAX_SS_TX_RX_BUF_SIZE]; 
extern int curr_ss_rx_len;


void update_can_tx_idx();
void send_ss_can_message();
void set_ack_transmit();
unsigned char get_current_state();
void start_ss_can_proto();
void recv_ss_can_message(char* data);


#endif // SS_PROTO_CAN_H