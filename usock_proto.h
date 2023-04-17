#ifndef USOCK_PROTO_H
#define USOCK_PROTO_H

#include <stdint.h>

#define CAN2SEP_SERVER_STATUS_ID 0x801
#define CAN2SEP_DER_SETTINGS_T_ID  0x802
#define CAN2SEP_DER_DEFAULT_DERC_T_ID 0x803
#define CAN2SEP_FREQ_DROOP_T_ID 0x804
#define CAN2SEP_DER_CURVE_T_ID 0x805


extern char recv_buf[1024];
void send_message(void * send_buf, int send_buf_len, uint32_t message_type);
uint32_t process_recv_message(char* rd_buf, int rd_buf_len);
void test_server_send_dera_ind();
void test_client_send_derc_ind();



#endif // USOCK_PROTO_H