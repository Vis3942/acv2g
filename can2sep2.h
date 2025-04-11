#ifndef CAN2SEP2_H
#define CAN2SEP2_H

#include <stdint.h>
#include <stdbool.h>

#define UNDEFINED_MODE 0
#define V2G_MODE  1
#define V2H_MODE  2


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

extern bool v2h_transition;
extern bool v2g_transition;
extern uint8_t vehicle_mode; // need for SCE: 1 => v2g, 2=> v2h, 0 => undefined

void init_ssproto();
void init_ssproto_v2h();
#endif // CAN2SEP2_H