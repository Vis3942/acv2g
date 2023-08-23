#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// version definition => byte major version.byte minor version 
#define VERSION 0x0100 // version 1.0
#define ISMN_MF_MODEL "A142C4Pacifica15.5kWVersion21301" // do not use this use what is read from OBCM
#define VIN_NUM_MF_SERNUM "2C4RC1N73JR116150"
#define VIN_NUM_LEN 17
#define J3072_CERTIFIED_DATE 1679156280 // 3-18-2023 9:18:00 PST
#define MANUFACTURER "Stellantis"
#define MANUFACTURER_LEN 10


int console_log(char *message,...);
void version();
uint32_t convertBytesToUint32BigEndian(unsigned char *bytes, int start_idx);
time_t getCurrentTime();
void displayTime();

#endif // UTILS_H



