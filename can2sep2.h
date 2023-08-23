#ifndef CAN2SEP2_H
#define CAN2SEP2_H

#include <stdint.h>

extern int32_t max_Wh;
extern int32_t max_Wh_recvd; // 0 => not recvd; 1 => recvd max_Wh
extern int32_t hcp_sw_ver;
extern int32_t hcp_sw_ver_recvd;
extern int32_t battery_status;
extern time_t changed_time;
extern int32_t current_power_source;
extern int32_t estimated_charge_remaining;
extern int32_t energy_request_now_Wh;
extern int32_t minimum_charging_duration_secs;
extern float current_soc;
extern float target_soc;
extern int32_t time_charge_is_neeeded_duration_secs;
extern int32_t availability_duration_secs;
extern int32_t max_charge_duration_secs;
extern time_t reading_time;
extern int32_t reserve_charge_percent;
extern int32_t reserve_percent;
extern int32_t obc_max_fwd_pwr_w; // maps to maxForwardPower in PEVInfo
extern int32_t obc_current_charging_pwr_w; // maps to chargingPowerNow in PEVInfo


#endif // CAN2SEP2_H