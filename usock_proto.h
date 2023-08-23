#ifndef USOCK_PROTO_H
#define USOCK_PROTO_H

#include <stdint.h>
#include <stdbool.h>

#define CAN2SEP_SERVER_STATUS_ID 0x801
#define CAN2SEP_DER_SETTINGS_T_ID  0x802
#define CAN2SEP_DER_DEFAULT_DERC_T_ID 0x803
#define CAN2SEP_FREQ_DROOP_T_ID 0x804
#define CAN2SEP_DER_CURVE_T_ID 0x805
#define CAN2SEP_DER_DERC_IND_T_ID 0x806
#define CAN2SEP_EVSE_COMMUNICATION_STATUS_ID 0x807 // 1=> IS COMMUNICATING, 0 => LOST COMMUNCATIONS


#define DEFAULT_MMR_DESCRIPTION    "Stellantis PEV Data"

extern char recv_buf[2048];
void send_message(char * send_buf, int send_buf_len, uint32_t message_type);
void process_recv_message(char* rd_buf, int rd_buf_len);
void test_server_send_dera_ind();
void test_client_send_derc_ind();
void send_mmr_setup(int typeof_req);
void send_dercapability_ind();
void send_deviceinfo_req();
void send_mup_req();
void send_mmr_setup_or_data(int typeof_req, bool sendReading);
void send_power_status_req();
void send_der_availabilit_req();
void send_der_status_req();
void send_dersettings_req();
void test_mirror_usock();
void test_ev_params_post_usock();
extern int sent_on_usock;


#endif // USOCK_PROTO_H