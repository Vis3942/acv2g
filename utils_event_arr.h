#ifndef UTILS_EVENT_ARR_H
#define UTILS_EVENT_ARR_H

#include <stdint.h>
#include <math.h>

#define NODE_EVENT_TYPE_NONE  0x00
#define NODE_EVENT_TYPE_FIXEDW  0x01
#define NODE_EVENT_TYPE_MAXLIMW  0x02
#define NODE_EVENT_TYPE_TARGETW  0x03

int addEvent(const char *str, uint8_t loc_sts, int64_t loc_start_time, uint32_t loc_duration, int32_t loc_value, uint8_t loc_event_type);
int getStatusForEvent(const char *str);
int updateStatusForEvent(const char *str, uint8_t loc_event_status);
void freeEventList();
void printEventList();
int setEventActive(const char * str);
int isEventActive(const char * str);
int clearEventActive(const char * str);
int removeEvent(const char *str);
int ComputeActivePowerPercent();
uint8_t fixedWEventExists();

#endif