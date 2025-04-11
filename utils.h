#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

// version definition => byte major version.byte minor version 
#define VERSION 0x0107 // version 1.7
// 1.6 add functionality in V2H mode to set permitted to discharge as true and 
//      skip waiting for all curves download for POWER STATUS with PEVInfo to be sent
// 1.5 add override power status if specified in can_settings.txt file
// 1.1 AND 1.2 SUPPORT LOGGGING CAN DATA TO CSV FILE ()
// 1.3 ADD TIMESTAMP to end of can data log in csv file 
#define ISMN_MF_MODEL "A142C4Pacifica15.5kWVersion21301" // do not use this use what is read from OBCM
#define VIN_NUM_MF_SERNUM "2C4RC1N73JR116150"
#define VIN_NUM_LEN 17
#define J3072_CERTIFIED_DATE 1679156280 // 3-18-2023 9:18:00 PST
#define MANUFACTURER "Stellantis"
#define MANUFACTURER_LEN 10
#define MAX_NUM_DATA_MESSAGES 500000

extern int proto_timer_seconds;
extern int32_t evcc_es; // 1 => true 0 => false
extern int override_power_status;
extern int override_max_forward_power;
extern int override_charge_power_now;


int console_log(char *message,...);
void version();
uint32_t convertBytesToUint32BigEndian(unsigned char *bytes, int start_idx);
time_t getCurrentTime();
void displayTime();
int bytesToInt(char* bytes, int start_idx);
void init_can_data_csv();
void write_can_data_csv(int id, char*data);
void read_parameters_from_file(char * param_file_name);
void charArrayToHexString(const char *input, size_t length, char *output, size_t output_max_len);

#endif // UTILS_H



