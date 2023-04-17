#ifndef SS_PROTO_H
#define SS_PROTO_H

#define SSP_READ_REGISTER 0x01
#define SSP_WRITE_REGISTER 0x0F

// all tasks in the sequence to be added to queue
#define SSP_RECEIVED_DERSETTINGS 0x01
#define SSP_2_0_READ_702_SF 0x02 // read all scale factors
#define SSP_2_1A_READ_702_NAMEPLATE_PART1 0x03 // read regs 2,3,4,5,6 in model 702
#define SSP_2_1B_READ_702_NAMEPLATE_PART2 0x04 // read regs 20, 21, 22, 23 in model 702
#define SSP_2_2_READ_702_CONFIG_INFO 0x05 // read regs 26 to 40; ignore those that are not required
#define SSP_2_3_READ_703_ALL 0x06 // read all data from regs 3 to 18; ignore those not required
#define SSP_2_4_RECEIVED_WHMAX 0x07 // if WhMax received on CAN, convert and write DERSettings to client
#define SSP_2_5_READ_001_PARAMS 0x08 // read model version from model 001 
#define SSP_2_6_RECEIVED_HCP_SW_VERSION 0x09 // RECV HCP SW version before sending DeviceInformation to SEP2 client (no separate task id for this)                      
#define SSP_3_RECEIVED_DEFAULT_DERCONTROL 50 //write to model 703 regs 3 to 13,  for 11 RndTms use previous value read

// steps to perform when app receives Volt-Var DERCurve from SEP2 client
// this data goes to model 705
#define SSP_3_READ_705_SF 51
#define SSP_3_WRITE_705_PARAMS_1 52
#define SSP_3_WRITE_705_PARAMS_2 53
#define SSP_3_WRITE_705_CURVE_DATA 54
#define SSP_3_WRITE_705_CURVE_VERIFY_REQ 55
#define SSP_3_READ_705_CURVE_VERIFY_RESP 56
#define SSP_3_WRITE_705_CURVE_ENABLE 57


// steps to perform when app receives Volt-Watt DERCurve from SEP2 client
// this data goes to model 706
#define SSP_3_READ_706_SF 60
#define SSP_3_WRITE_706_PARAMS 61
#define SSP_3_WRITE_706_CURVE_DATA 62
#define SSP_3_WRITE_706_CURVE_VERIFY_REQ 63
#define SSP_3_READ_706_CURVE_VERIFY_RESP 64
#define SSP_3_WRITE_706_CURVE_ENABLE 65

// steps to perform when app receives opModLVRTMustTrip DERCurve from SEP2 client
// this data goes to model 707
#define SSP_3_READ_707_SF 70
#define SSP_3_WRITE_707_PARAMS 71
#define SSP_3_WRITE_707_CURVE_DATA 72
#define SSP_3_WRITE_707_CURVE_VERIFY_REQ 73
#define SSP_3_READ_707_CURVE_VERIFY_RESP 74
#define SSP_3_WRITE_707_CURVE_ENABLE 75

// steps to perform when app receives opModHVRTMustTrip DERCurve from SEP2 client
// this data goes to model 708
#define SSP_3_READ_708_SF 80
#define SSP_3_WRITE_708_PARAMS 81
#define SSP_3_WRITE_708_CURVE_DATA 82
#define SSP_3_WRITE_708_CURVE_VERIFY_REQ 83
#define SSP_3_READ_708_CURVE_VERIFY_RESP 84
#define SSP_3_WRITE_708_CURVE_ENABLE 85

// steps to perform when app receives opModLFRMustTrip DERCurve from SEP2 client
// this data goes to model 709
#define SSP_3_READ_709_SF 90
#define SSP_3_WRITE_709_PARAMS 91
#define SSP_3_WRITE_709_CURVE_DATA 92
#define SSP_3_WRITE_709_CURVE_VERIFY_REQ 93
#define SSP_3_READ_709_CURVE_VERIFY_RESP 94
#define SSP_3_WRITE_709_CURVE_ENABLE 95

// steps to perform when app receives opModHFRMustTrip DERCurve from SEP2 client
// this data goes to model 710
#define SSP_3_READ_710_SF 100
#define SSP_3_WRITE_710_PARAMS 101
#define SSP_3_WRITE_710_CURVE_DATA 102
#define SSP_3_WRITE_710_CURVE_VERIFY_REQ 103
#define SSP_3_READ_710_CURVE_VERIFY_RESP 104
#define SSP_3_WRITE_710_CURVE_ENABLE 105

// steps to perform when app receives opModFreqDroop DERCurve from SEP2 client
// this data goes to model 711
#define SSP_3_READ_711_SF 110
#define SSP_3_WRITE_711_PARAMS 111
#define SSP_3_WRITE_711_CURVE_DATA 112
#define SSP_3_WRITE_711_CURVE_VERIFY_REQ 113
#define SSP_3_READ_711_CURVE_VERIFY_RESP 114
#define SSP_3_WRITE_711_CURVE_ENABLE 115

// steps to perform when app receives opModwATTvAR DERCurve from SEP2 client
// this data goes to model 712
#define SSP_3_READ_712_SF 120
#define SSP_3_WRITE_712_PARAMS 121
#define SSP_3_WRITE_712_CURVE_DATA 122
#define SSP_3_WRITE_712_CURVE_VERIFY_REQ 123
#define SSP_3_READ_712_CURVE_VERIFY_RESP 124
#define SSP_3_WRITE_712_CURVE_ENABLE 125

#define SSP_4_1_WRITE_MUP_SETUP 140
#define SSP_4_2_READ_701_SF 141
#define SSP_4_3_READ_701_ACTYPE 142
#define SSP_4_4_WRITE_ACTIVE_POWER_MMR_SETUP 143
#define SSP_4_5_WRITE_REACTIVE_POWER_MMR_SETUP 144
#define SSP_4_6_WRITE_VOLTAGE_MMR_SETUP 145
#define SSP_4_7_WRITE_FREQUENCY_MMR_SETUP 146

#define SSP_5_1_RECEIVED_DEFAULT_DERCONTROL 150
#define SSP_6_1_READ_701_REPORT_VALUE 151
#define SSP_6_2_READ_701_STATUS_VALUE 152
// KEEP TRACK OF WHEN THE LAST ActivePower, ReactivePower, Voltage, Freq was sent. 
// If within postRate (default 15 secs), send it 
//     else simply set it back to the queue


#define READ_REG_CAN_CODE 0x67
#define WRITE_REG_CAN_CODE 0x6A

#define READ_NONE 0x00
#define READ_702_SF 0x01

#define NUM_POINTS_CURVE 10

#define NUM_MODEL_CHARS 16
#define NUM_VERSION_CHARS 8

// extern vars

// DERSettings vars
extern short setMaxW; // setMaxWValue and setMaxWMultiplier to convert
extern unsigned short setMaxChargeRateW; // value and multiplier
extern short setMaxVar; // value and multiplier
extern short setMaxVarNeg; // value and multipler
extern unsigned short setVNom; // value and multiplier
extern unsigned short setVRef ; // value and multipler
extern unsigned short setVRefOfs; // value and multiplier
extern unsigned short setMaxV; // value and multipler
extern unsigned short setMinV; // value and multipler
extern int64_t updated_time_dersett; 

extern short w_sf_702;
extern short pf_sf_702;
extern short va_sf_702;
extern short var_sf_702;
extern short v_sf_702;
extern short a_sf_702;
extern short s_sf_702;

extern unsigned short w_max_rtg_702;
extern unsigned short w_ovr_ext_rtg_702;
extern unsigned short w_ovr_ext_rtg_pf_702;
extern unsigned short w_und_ext_rtg_702;
extern unsigned short w_und_ext_rtg_pf_702;

extern unsigned short react_suscept_rtg_702;
extern unsigned short nor_op_cat_rtg_702;
extern unsigned short abn_op_cat_rtg_702;
extern uint32_t ctrl_modes_702;
extern uint32_t sep2_conv_ctrl_modes_702;

extern short wmax_702;
extern short vamax_702;
extern short wcha_rte_max_702;
extern short vacha_rte_max_702;
extern short wchar_rte_max_702;
extern short var_max_inj_702;
extern short var_max_abs_702;
extern short vnom_702;
extern short vmax_702;
extern short vmin_702;

extern bool ES ; // default_derc.base.opmodenergize
extern uint32_t ESHzHi ; // default_derc.setESHighFreq
extern short ESVHi ; // default_derc.setESHighVolt
extern uint32_t ESHzLo ; // default_derc.setESLowFreq
extern short ESVLo ; // default_derc.setESLowVolt
extern uint32_t ESDlyTms ; //  default_derc.setESDelay
extern uint32_t ESRmpTms ; // default_derc.setESRampTms
extern short v_sf_703;
extern short hz_sf_703;
extern int default_derc_received;                         

extern char model_str_001[NUM_MODEL_CHARS+1]; // +1 for zero char at end
extern char version_str_001[NUM_VERSION_CHARS+1]; // +1 for zero char at end


extern uint32_t DbOf ; 
extern uint32_t DbUf ;
extern uint16_t KOf ;
extern uint16_t KUf ;
extern uint16_t RspTms ; //  opModFReqDroop.openLoopTms
extern int freq_droop_curve_received; // valie is 1 if received
extern int freq_droop_curve_verify; // 0 => still evaluating, 1 => complete (success), 2 => failed


extern int volt_var_curve_received; // valie is 1 if received
extern int volt_var_points_count ;
extern float volt_var_x[NUM_POINTS_CURVE];
extern float volt_var_y[NUM_POINTS_CURVE];
extern int volt_var_curve_verify;

extern int watt_var_curve_received ; // valie is 1 if received
extern int watt_var_points_count ;
extern float watt_var_x[NUM_POINTS_CURVE];
extern float watt_var_y[NUM_POINTS_CURVE];
extern int watt_var_curve_verify;

extern int volt_watt_curve_received; // valie is 1 if received
extern int volt_watt_points_count ;
extern float volt_watt_x[NUM_POINTS_CURVE];
extern float volt_watt_y[NUM_POINTS_CURVE];
extern int volt_watt_curve_verify;

extern int low_volt_trip_curve_received ; // valie is 1 if received
extern int low_volt_trip_points_count ;
extern float low_volt_trip_x[NUM_POINTS_CURVE];
extern float low_volt_trip_y[NUM_POINTS_CURVE];
extern int low_volt_trip_curve_verify;

extern int high_volt_trip_curve_received ; // valie is 1 if received
extern int high_volt_trip_points_count ;
extern float high_volt_trip_x[NUM_POINTS_CURVE];
extern float high_volt_trip_y[NUM_POINTS_CURVE];
extern int high_volt_trip_curve_verify;

extern int low_freq_trip_curve_received ; // valie is 1 if received
extern int low_freq_trip_points_count ;
extern float low_freq_trip_x[NUM_POINTS_CURVE];
extern float low_freq_trip_y[NUM_POINTS_CURVE];
extern int low_freq_trip_curve_verify;

extern int high_freq_trip_curve_received ; // valie is 1 if received
extern int high_freq_trip_points_count ;
extern float high_freq_trip_x[NUM_POINTS_CURVE];
extern float high_freq_trip_y[NUM_POINTS_CURVE];
extern int high_freq_trip_curve_verify;

extern uint16_t actype_sep2;

/// 701 sf
extern short current_sf_701;
extern short voltage_sf_701;
extern short frequency_sf_701;
extern short activepower_sf_701;
extern short powerfactor_sf_701;
extern short apparentpower_sf_701;
extern short reactivepower_sf_701;

// 701 params
extern short activepower_701_rep;
extern short reactivepower_701_rep;
extern short voltage_701_rep;
extern short frequency_701_rep;

// 701 status
extern short status_701;
extern short inv_status_701;
extern short conn_status_701;
extern time_t status_time_701;


void process_recv_message_ssproto();


#endif // SS_PROTO_H