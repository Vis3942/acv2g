#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "ss_proto.h"
#include "ss_proto_can.h"
#include "sl_api.h"
#include "utils.h"
#include "task_queue.h"
#include "can2sep2.h"
#include "usock_proto.h"

// Note: data in modbus array to send over can
/*
 FUNCTION CODE,
 Model ID Hi
 Model ID Lo
 Address Offset Hi
 Address Offset Lo
 Num of Regs Hi
 Num of Regs Lo
*/

int current_proto_task_id = 0;
time_t verify_start_time = 0;
time_t verify_end_time = 0;

int read_cmd = 0;

// DERSettings vars
short setMaxW = 0;                    // setMaxWValue and setMaxWMultiplier to convert
unsigned short setMaxChargeRateW = 0; // value and multiplier
short setMaxVar = 0;                  // value and multiplier
short setMaxVarNeg = 0;               // value and multipler
unsigned short setVNom = 0;           // value and multiplier
unsigned short setVRef = 0;           // value and multipler
unsigned short setVRefOfs = 0;        // value and multiplier
unsigned short setMaxV = 0;           // value and multipler
unsigned short setMinV = 0;           // value and multipler
int64_t updated_time_dersett = 0;

// 702 scale factors
short w_sf_702 = 0;
short pf_sf_702 = 0;
short va_sf_702 = 0;
short var_sf_702 = 0;
short v_sf_702 = 0;
short a_sf_702 = 0;
short s_sf_702 = 0;

// 702 parameters for read part1
unsigned short w_max_rtg_702 = 0;
unsigned short w_ovr_ext_rtg_702 = 0;
unsigned short w_ovr_ext_rtg_pf_702 = 0;
unsigned short w_und_ext_rtg_702 = 0;
unsigned short w_und_ext_rtg_pf_702 = 0;

unsigned short react_suscept_rtg_702 = 0;
unsigned short nor_op_cat_rtg_702 = 0;
unsigned short abn_op_cat_rtg_702 = 0;
uint32_t ctrl_modes_702 = 0;
uint32_t sep2_conv_ctrl_modes_702 = 0;

// 702 parameters for write
short wmax_702 = 0;
short vamax_702 = 0;
short wcha_rte_max_702 = 0;
short vacha_rte_max_702 = 0;
short wchar_rte_max_702 = 0;
short var_max_inj_702 = 0;
short var_max_abs_702 = 0;
short vnom_702 = 0;
short vmax_702 = 0;
short vmin_702 = 0;

bool prev_ES = 0; // previos state of ES write 703 ES value only when there is a state change
bool ES = 0;               // default_derc.base.opmodenergize
uint32_t ESHzHi = 0;     // default_derc.setESHighFreq
short ESHzHi_source = 0;     // 0 default values read from OBCM sunspec module, 1 received over 2030.5 client
uint32_t ESVHi = 0;               // default_derc.setESHighVolt
short ESVHi_source = 0;     // 0 default values read from OBCM sunspec module, 1 received over 2030.5 client
uint32_t ESHzLo = 0;     // default_derc.setESLowFreq
short ESHzLo_source = 0;     // 0 default values read from OBCM sunspec module, 1 received over 2030.5 client
uint32_t ESVLo = 0;               // default_derc.setESLowVolt
short ESVLo_source = 0;     // 0 default values read from OBCM sunspec module, 1 received over 2030.5 client
uint32_t ESDlyTms = 0;          //  default_derc.setESDelay
short ESDlyTms_source = 0;     // 0 default values read from OBCM sunspec module, 1 received over 2030.5 client
uint32_t ESRmpTms = 0;         // default_derc.setESRampTms
short ESRmpTms_source = 0;     // 0 default values read from OBCM sunspec module, 1 received over 2030.5 client
short v_sf_703 = 0;
short hz_sf_703 = 0;
int default_derc_received = -1; // -1 init, 0 recvd and written; // 1 if recvd
int wset_pct_704 = 0;
short wset_pct_ena_704 = 0;

char model_str_001[NUM_MODEL_CHARS+1]; // +1 for zero char at end
char version_str_001[NUM_VERSION_CHARS+1]; // +1 for zero char at end

// for freqdroop model 711
float DbOf = 0;
float DbUf = 0;
float KOf = 0;
float KUf = 0;
float RspTms = 0; //  opModFReqDroop.openLoopTms
int freq_droop_curve_received = 0; // valie is 1 if received
int freq_droop_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed

// for actype model 701
uint16_t actype_sep2 = 0;

int volt_var_curve_received[MAX_SUPERSEDE_EVENTS] = {0}; // valie is 1 if received
int volt_var_points_count[MAX_SUPERSEDE_EVENTS] = {0};
float volt_var_x[MAX_SUPERSEDE_EVENTS][NUM_POINTS_CURVE];
float volt_var_y[MAX_SUPERSEDE_EVENTS][NUM_POINTS_CURVE];
int volt_var_curve_verify[MAX_SUPERSEDE_EVENTS] = {0}; // 0 => still evaluating, 1 => complete (success), 2 => failed
u8_t volt_var_curve_derc_mrid[MAX_SUPERSEDE_EVENTS][SL_XSD_MRID_LEN];
int volt_var_current_curve_index = 0;
int volt_var_set_curve_index = 0;

// Note: Watt var curve is not included in the rule 21 based curve settings and verifications
int watt_var_curve_received = 0; // valie is 1 if received
int watt_var_points_count = 0;
float watt_var_x[NUM_POINTS_CURVE];
float watt_var_y[NUM_POINTS_CURVE];
u8_t watt_var_curve_derc_mrid[SL_XSD_MRID_LEN];
int watt_var_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed

int volt_watt_curve_received[MAX_SUPERSEDE_EVENTS] = {0}; // valie is 1 if received
int volt_watt_points_count[MAX_SUPERSEDE_EVENTS] = {0};
float volt_watt_x[MAX_SUPERSEDE_EVENTS][NUM_POINTS_CURVE];
float volt_watt_y[MAX_SUPERSEDE_EVENTS][NUM_POINTS_CURVE];
int volt_watt_curve_verify[MAX_SUPERSEDE_EVENTS] = {0}; // 0 => still evaluating, 1 => complete (success), 2 => failed
u8_t volt_watt_curve_derc_mrid[MAX_SUPERSEDE_EVENTS][SL_XSD_MRID_LEN];
int volt_watt_current_curve_index = 0;
int volt_watt_set_curve_index = 0;

int low_volt_trip_curve_received = 0; // valie is 1 if received
int low_volt_trip_points_count = 0;
float low_volt_trip_x[NUM_POINTS_CURVE];
float low_volt_trip_y[NUM_POINTS_CURVE];
u8_t low_volt_trip_curve_derc_mrid[SL_XSD_MRID_LEN];
int low_volt_trip_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed

int low_volt_cess_curve_received = 0; // valie is 1 if received
int low_volt_cess_points_count = 0;
float low_volt_cess_x[NUM_POINTS_CURVE];
float low_volt_cess_y[NUM_POINTS_CURVE];
// not used combined with low_volt_trip_curve_verify 
//int low_volt_cess_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed
u8_t low_volt_cess_curve_derc_mrid[SL_XSD_MRID_LEN];

int high_volt_trip_curve_received = 0; // valie is 1 if received
int high_volt_trip_points_count = 0;
float high_volt_trip_x[NUM_POINTS_CURVE];
float high_volt_trip_y[NUM_POINTS_CURVE];
u8_t high_volt_trip_curve_derc_mrid[SL_XSD_MRID_LEN];
int high_volt_trip_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed

int high_volt_cess_curve_received = 0; // valie is 1 if received
int high_volt_cess_points_count = 0;
float high_volt_cess_x[NUM_POINTS_CURVE];
float high_volt_cess_y[NUM_POINTS_CURVE];
// not used combined with low_volt_trip_curve_verify 
//int high_volt_cess_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed
u8_t high_volt_cess_curve_derc_mrid[SL_XSD_MRID_LEN];

int low_freq_trip_curve_received = 0; // valie is 1 if received
int low_freq_trip_points_count = 0;
float low_freq_trip_x[NUM_POINTS_CURVE];
float low_freq_trip_y[NUM_POINTS_CURVE];
u8_t low_freq_trip_curve_derc_mrid[SL_XSD_MRID_LEN];
int low_freq_trip_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed

int high_freq_trip_curve_received = 0; // valie is 1 if received
int high_freq_trip_points_count = 0;
float high_freq_trip_x[NUM_POINTS_CURVE];
float high_freq_trip_y[NUM_POINTS_CURVE];
u8_t high_freq_trip_curve_derc_mrid[SL_XSD_MRID_LEN];
int high_freq_trip_curve_verify = 0; // 0 => still evaluating, 1 => complete (success), 2 => failed

// 704 SF
short wsetpct_sf_704 = 0;

// 705 SF
short v_sf_705 = 0;
short deptref_sf_705 = 0;
short rsptms_sf_705 = 0;

// 706 SF
short v_sf_706 = 0;
short deptref_sf_706 = 0;
short rsptms_sf_706 = 0;

// 707 sf
short v_sf_707 = 0;
short tms_sf_707 = 0;

// 708 sf
short v_sf_708 = 0;
short tms_sf_708 = 0;

// 709 sf
short hz_sf_709 = 0;
short tms_sf_709 = 0;

// 710 sf
short hz_sf_710 = 0;
short tms_sf_710 = 0;

// 711 sf
short db_sf_711 = 0;
short k_sf_711 = 0;
short rsptms_sf_711 = 0;

// 712 sf
short w_sf_712 = 0;
short deptref_sf_712 = 0;

/// 701 sf
short current_sf_701 = 0;
short voltage_sf_701 = 0;
short frequency_sf_701 = 0;
short activepower_sf_701 = 0;
short powerfactor_sf_701 = 0;
short apparentpower_sf_701 = 0;
short reactivepower_sf_701 = 0;

// 701 params
short activepower_701_rep = 0;
short reactivepower_701_rep = 0;
short voltage_701_rep = 0;
uint32_t frequency_701_rep = 0;

// 701 status
short status_701 = 0;
short inv_status_701 = 0;
short conn_status_701 = 0;
time_t status_time_701;

bool sts_init = false;
bool comm_status = false;
bool before_override_comm_status = false;
int server_status; // 0=> not found, 1 => found, 2 => searching, -1 => just initialized
int before_override_server_status; // 0=> not found, 1 => found, 2 => searching, -1 => just initialized

int test_ss_model_num = 0;
int test_ss_model_start_addr = -1;
int test_ss_model_regs_read_count = 0;


int verify_message()
{
    // loc [0] function code should be 0x67
    // loc [1] byte count
    // curr_ss_rx_len = byte count + 2
    int pkt_len = ss_rx_buf[1];
    //debug 
    fprintf(stdout, "pkt len %d; ss_rx_buf[0] = %d, curr_ss_rx_len=%d \n", pkt_len, ss_rx_buf[0], curr_ss_rx_len);
    if (ss_rx_buf[0] != READ_REG_SS_CODE)
    {
        return 0;
    }

    if ((pkt_len + 2) > curr_ss_rx_len)
    {
        return 0;
    }

    return 1;
}

void write_evse_info_part1()
{
    // model 702 = 0x02BE
    // write WMax
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBE);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 26;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count
    ss_tx_buf[8] = (unsigned char)((wmax_702 & 0xFF00) >> 8);
    ss_tx_buf[9] = (unsigned char)(wmax_702 & 0xFF);
    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

/*
 * This is to be called to setup registers for performing task id
 *     SSP_2_0_READ_702_SF
 */
void read_scale_factors_model702()
{
    // model 702 = 0x02BE
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBE);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 45;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 7;
    curr_ss_tx_len = 7;
    read_cmd = SSP_2_0_READ_702_SF;
}

void process_702_sf()
{
    if (ss_rx_buf[1] == 14)
    {
        // data is verified
        w_sf_702 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        pf_sf_702 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        va_sf_702 = (short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);
        var_sf_702 = (short)((ss_rx_buf[8] << 8) | ss_rx_buf[9]);
        v_sf_702 = (short)((ss_rx_buf[10] << 8) | ss_rx_buf[11]);
        a_sf_702 = (short)((ss_rx_buf[12] << 8) | ss_rx_buf[13]);
        s_sf_702 = (short)((ss_rx_buf[14] << 8) | ss_rx_buf[15]);

        if ((w_sf_702 < -10) || (w_sf_702 > 10))
        {
            printf("incorrent w_sf_702 value recd %d \n", w_sf_702);
            w_sf_702 = 0;
        }
        if ((pf_sf_702 < -10) || (pf_sf_702 > 10))
        {
            printf("incorrent pf_sf_702 value recd %d \n", pf_sf_702);
            pf_sf_702 = 0;
        }
        if ((va_sf_702 < -10) || (va_sf_702 > 10))
        {
            printf("incorrent va_sf_702 value recd %d \n", va_sf_702);
            va_sf_702 = 0;
        }
        if ((var_sf_702 < -10) || (var_sf_702 > 10))
        {
            printf("incorrent var_sf_702 value recd %d \n", var_sf_702);
            var_sf_702 = 0;
        }
        if ((v_sf_702 < -10) || (v_sf_702 > 10))
        {
            printf("incorrent v_sf_702 value recd %d \n", v_sf_702);
            v_sf_702 = 0;
        }
        if ((a_sf_702 < -10) || (a_sf_702 > 10))
        {
            printf("incorrent a_sf_702 value recd %d \n", a_sf_702);
            a_sf_702 = 0;
        }
        if ((s_sf_702 < -10) || (s_sf_702 > 10))
        {
            printf("incorrent s_sf_702 value recd %d \n", s_sf_702);
            s_sf_702 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 702 sf, expected 14; got = %d \n", ss_rx_buf[1]);
    }
}

void read_702_nameplate_part1()
{
    // model 702 = 0x02BE
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBE);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 5;
    curr_ss_tx_len = 7;
    read_cmd = SSP_2_1A_READ_702_NAMEPLATE_PART1;
}

void process_702_nameplate_part1()
{
    //int tmp_scale; 
    if (ss_rx_buf[1] == 10)
    {
        // data is verified
        w_max_rtg_702 = (unsigned short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        w_ovr_ext_rtg_702 = (unsigned short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        w_ovr_ext_rtg_pf_702 = (unsigned short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);
        w_und_ext_rtg_702 = (unsigned short)((ss_rx_buf[8] << 8) | ss_rx_buf[9]);
        w_und_ext_rtg_pf_702 = (unsigned short)((ss_rx_buf[10] << 8) | ss_rx_buf[11]);
    }
    else
    {
        printf("recv length is not adequate for 702 nameplate part1, expected 10; got = %d \n", ss_rx_buf[1]);
    }
}

void read_702_nameplate_part2()
{
    // model 702 = 0x02BE
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBE);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 20;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 5;
    curr_ss_tx_len = 7;
    read_cmd = SSP_2_1B_READ_702_NAMEPLATE_PART2;
}

void process_702_nameplate_part2()
{
    //int tmpi;
    uint32_t tmp_u32; 
    if (ss_rx_buf[1] == 10)
    {
        // data is verified
        react_suscept_rtg_702 = (unsigned short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        nor_op_cat_rtg_702 = (unsigned short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        abn_op_cat_rtg_702 = (unsigned short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);
        tmp_u32 = (uint32_t)((ss_rx_buf[8] << 8) | ss_rx_buf[9]);
        ctrl_modes_702 = convertBytesToUint32BigEndian(ss_rx_buf, 10);
        // ctrl_modes_702 = (uint32_t)((ss_rx_buf[10] << 8) | ss_rx_buf[11]);
        // ctrl_modes_702 = ctrl_modes_702 + (uint32_t) (tmp_u32 << 16);
    }
    else
    {
        printf("recv length is not adequate for 702 nameplate part2, expected 10; got = %d \n", ss_rx_buf[1]);
    }
}

void read_702_config_info()
{
    // model 702 = 0x02BE
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBE);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 26;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 15;
    curr_ss_tx_len = 7;
    read_cmd = SSP_2_2_READ_702_CONFIG_INFO;
}

void process_702_config_info()
{
    // int tmpi;
    // uint32_t tmp_u32; 
    if (ss_rx_buf[1] == 30)
    {
        // data is verified
        wmax_702 = (unsigned short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        vamax_702 = (unsigned short)((ss_rx_buf[12] << 8) | ss_rx_buf[13]);
        var_max_inj_702 = (unsigned short)((ss_rx_buf[14] << 8) | ss_rx_buf[15]);
        var_max_abs_702 = (unsigned short)((ss_rx_buf[16] << 8) | ss_rx_buf[17]);
        wcha_rte_max_702 = (unsigned short)((ss_rx_buf[18] << 8) | ss_rx_buf[19]);
        vacha_rte_max_702 = (unsigned short)((ss_rx_buf[22] << 8) | ss_rx_buf[23]);
        vnom_702 = (unsigned short)((ss_rx_buf[26] << 8) | ss_rx_buf[27]);
        vmax_702 = (unsigned short)((ss_rx_buf[28] << 8) | ss_rx_buf[29]);
        vmin_702 = (unsigned short)((ss_rx_buf[30] << 8) | ss_rx_buf[31]);
    }
    else
    {
        printf("recv length is not adequate for 702 config info, expected 30; got = %d \n", ss_rx_buf[1]);
    }
}

void read_all_703()
{
    // model 703 = 0x02BF
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBF);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 16;
    curr_ss_tx_len = 7;
    read_cmd = SSP_2_3_READ_703_ALL;
}

void process_all_703()
{
    if (ss_rx_buf[1] == 32)
    {
        // data is verified
        if (ESVHi_source != 1) 
        {
            ESVHi = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        }
        if (ESVLo_source != 1) 
        {
            ESVLo = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        }
        if (ESHzHi_source != 1)
        {
            ESHzHi = convertBytesToUint32BigEndian(ss_rx_buf, 6);
        }
        if (ESHzLo_source != 1) 
        {
            ESHzLo = convertBytesToUint32BigEndian(ss_rx_buf, 10);
        }
        if (ESDlyTms_source != 1) 
        {
            ESDlyTms = convertBytesToUint32BigEndian(ss_rx_buf, 14);
        }
        ESRmpTms = convertBytesToUint32BigEndian(ss_rx_buf, 22);
        v_sf_703 = (short)((ss_rx_buf[30] << 8) | ss_rx_buf[31]);
        hz_sf_703 = (short)((ss_rx_buf[32] << 8) | ss_rx_buf[33]);

        if ((v_sf_703 < -10) || (v_sf_703 > 10))
        {
            printf("incorrent v_sf_703 value recd %d \n", v_sf_702);
            v_sf_702 = 0;
        }
        if ((hz_sf_703 < -10) || (hz_sf_703 > 10))
        {
            printf("incorrent hz_sf_703 value recd %d \n", hz_sf_703);
            hz_sf_703 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 703 all, expected 32; got = %d \n", ss_rx_buf[1]);
    }
}

void test_read_custom_model()
{
    int ii = 0;
    int length = 7;
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char) ( (test_ss_model_num & 0xFF00) >> 8 );
    ss_tx_buf[2] = (unsigned char) (test_ss_model_num & 0x00FF) ;
    ss_tx_buf[3] = (unsigned char) ( (test_ss_model_start_addr & 0xFF00) >> 8 );
    ss_tx_buf[4] = (unsigned char) (test_ss_model_start_addr & 0x00FF) ;
    ss_tx_buf[5] = (unsigned char) ( (test_ss_model_regs_read_count & 0xFF00) >> 8 );
    ss_tx_buf[6] = (unsigned char) (test_ss_model_regs_read_count & 0x00FF) ;
    curr_ss_tx_len = 7;
    read_cmd = SSP_TEST_READ_CUSTOM_MODEL;
}

void process_test_read_custom_model() 
{
    int data;
    int ii, jj;
    // // debug
    // fprintf(stdout, "process read custom regs \n");
    if (ss_rx_buf[1] == 2* test_ss_model_regs_read_count)
    {
        ii = 2;
        jj = (int)((ii-2)/2);
        while (jj < test_ss_model_regs_read_count)
        {
            data = (short)((ss_rx_buf[ii] << 8) | ss_rx_buf[ii+1]);
            fprintf(stdout, "data at reg %d = %d\n", jj, data);
            ii += 2;
            jj = (int)((ii-2)/2);
        }
    }
    else
    {
        printf("recv length is not adequate for num regs read %d, expected %d; got = %d \n", 
            test_ss_model_regs_read_count, 2*test_ss_model_regs_read_count, ss_rx_buf[1]);
    }
}


void read_params_001()
{
    // model 001 = 0x0001
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x00);
    ss_tx_buf[2] = (unsigned char)(0x01);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 18;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 32;
    curr_ss_tx_len = 7;
    read_cmd = SSP_2_5_READ_001_PARAMS;
}

void process_params_001()
{
    if (ss_rx_buf[1] == 64)
    {
        // data is verified
        memset(model_str_001, 0, NUM_MODEL_CHARS+1);
        memcpy(model_str_001, &ss_rx_buf[2], NUM_MODEL_CHARS);
        memset(version_str_001, 0, NUM_VERSION_CHARS+1);
        memcpy(version_str_001, &ss_rx_buf[50], NUM_VERSION_CHARS);
    }
    else
    {
        printf("recv length is not adequate for 001 params, expected 32; got = %d \n", ss_rx_buf[1]);
    }
}


void write_curve_data(int curve_type)
{
    float *x_pts;
    float *y_pts;
    int *pts_count;
    int *curve_received;

    if (curve_type == SL_XSD_CURVE_TYPE_VOLT_WATT)
    {
        x_pts = &volt_watt_x[volt_watt_set_curve_index][0];
        y_pts = &volt_watt_y[volt_watt_set_curve_index][0];
        pts_count = &volt_watt_points_count[volt_watt_set_curve_index];
        curve_received = &volt_watt_curve_received[volt_watt_set_curve_index];
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_VOLT_VAR)
    {
        x_pts = &volt_var_x[volt_var_set_curve_index][0];
        y_pts = &volt_var_y[volt_var_set_curve_index][0];
        pts_count = &volt_var_points_count[volt_var_set_curve_index];
        curve_received = &volt_var_curve_received[volt_var_set_curve_index];
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_WATT_VAR)
    {
        x_pts = &watt_var_x[0];
        y_pts = &watt_var_y[0];
        pts_count = &watt_var_points_count;
        curve_received = &watt_var_curve_received;
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_LVRT_MUST_TRIP)
    {
        x_pts = &low_volt_trip_x[0];
        y_pts = &low_volt_trip_y[0];
        pts_count = &low_volt_trip_points_count;
        curve_received = &low_volt_trip_curve_received;
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_HVRT_MUST_TRIP)
    {
        x_pts = &high_volt_trip_x[0];
        y_pts = &high_volt_trip_y[0];
        pts_count = &high_volt_trip_points_count;
        curve_received = &high_volt_trip_curve_received;
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_LFRT_MUST_TRIP)
    {
        x_pts = &low_freq_trip_x[0];
        y_pts = &low_freq_trip_y[0];
        pts_count = &low_freq_trip_points_count;
        curve_received = &low_freq_trip_curve_received;
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_HFRT_MUST_TRIP)
    {
        x_pts = &high_freq_trip_x[0];
        y_pts = &high_freq_trip_y[0];
        pts_count = &high_freq_trip_points_count;
        curve_received = &high_freq_trip_curve_received;
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_LVRT_MOM_CESS)
    {
        x_pts = &low_volt_cess_x[0];
        y_pts = &low_volt_cess_y[0];
        pts_count = &low_volt_cess_points_count;
        curve_received = &low_volt_cess_curve_received;
    }
    else if (curve_type == SL_XSD_CURVE_TYPE_HVRT_MOM_CESS)
    {
        x_pts = &high_volt_cess_x[0];
        y_pts = &high_volt_cess_y[0];
        pts_count = &high_volt_cess_points_count;
        curve_received = &high_volt_cess_curve_received;
    }
    else
    {
        fprintf(stdout, "unsupported curve type %d. Unable to process this curve to send to OBCM \n", curve_type);
        return;
    }

}

void write_default_dercontrol_step3()
{
    //debug
    fprintf(stdout, "set up buffer to write default derc control to obcm v_sf %d, hz_sf %d\n", v_sf_703, hz_sf_703);
    fprintf(stdout, "writing VHi %u [src: %d], VLo %u[src: %d], HzHi %u[src: %d], HzLo %u[src: %d], delay %u[src: %d]\n", 
        ESVHi, ESVHi_source, ESVLo, ESVLo_source, ESHzHi, ESHzHi_source, 
        ESHzLo, ESHzLo_source, ESDlyTms, ESDlyTms_source);
    uint32_t tmp_u32;
    // model 703 = 0x02BF
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBF);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 8; //12;
    ss_tx_buf[7] = 16; //24; // byte count
    if (ESVHi_source == 1)  
    {
        tmp_u32 = (uint32_t) (ESVHi / 100);  // div by 100 since the 2030.5 messages have it specified after multiplication by 100
        tmp_u32 = (uint32_t) (tmp_u32/pow(10, v_sf_703) ); 
        tmp_u32 = tmp_u32 / 100; // expects value as 1.00 for 100, 1.05 for 105
    }
    else 
    {
        // it is zero ;what ever is read from obcm is stored in ESVHi
        tmp_u32 = (uint32_t) (ESVHi);
    }
    ss_tx_buf[8] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
    ss_tx_buf[9] = (unsigned char)(tmp_u32 & 0xFF);
    if (ESVLo_source == 1) 
    {
        tmp_u32 = (uint32_t) (ESVLo / 100);  // div by 100 since the 2030.5 messages have it specified after multiplication by 100
        tmp_u32 = (uint32_t) (tmp_u32/pow(10, v_sf_703)); 
        tmp_u32 = tmp_u32 / 100; // expects value as 1.00 for 100, 1.05 for 105
    }
    else 
    {
        // it is zero ;what ever is read from obcm is stored in ESVLo
        tmp_u32 = (uint32_t) (ESVLo);
    }
    ss_tx_buf[10] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
    ss_tx_buf[11] = (unsigned char)(tmp_u32 & 0xFF);
    if (ESHzHi_source == 1) 
    {
        tmp_u32 = (uint32_t) (ESHzHi/pow(10, hz_sf_703)); 
        tmp_u32 = (uint32_t) (tmp_u32 / 100);  // div by 100 since the 2030.5 messages have it specified after multiplication by 100
    }
    else 
    {
        // it is zero ;what ever is read from obcm is stored in ESVHi
        tmp_u32 = (uint32_t) (ESHzHi);
    }
    ss_tx_buf[12] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
    ss_tx_buf[13] = (unsigned char)((tmp_u32 & 0x00FF0000) >> 16);
    ss_tx_buf[14] = (unsigned char)((tmp_u32 & 0x0000FF00) >> 8);
    ss_tx_buf[15] = (unsigned char)(tmp_u32 & 0xFF);
    if (ESHzLo_source == 1) 
    {
        tmp_u32 = (uint32_t) (ESHzLo/pow(10, hz_sf_703)); 
        tmp_u32 = (uint32_t) (tmp_u32 / 100);  // div by 100 since the 2030.5 messages have it specified after multiplication by 100
    }
    else 
    {
        // it is zero ;what ever is read from obcm is stored in ESVHi
        tmp_u32 = (uint32_t) (ESHzLo);
    }
    ss_tx_buf[16] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
    ss_tx_buf[17] = (unsigned char)((tmp_u32 & 0x00FF0000) >> 16);
    ss_tx_buf[18] = (unsigned char)((tmp_u32 & 0x0000FF00) >> 8);
    ss_tx_buf[19] = (unsigned char)(tmp_u32 & 0xFF);
    if (ESDlyTms_source == 1) 
    {
        tmp_u32 = (uint32_t) (ESDlyTms); 
        tmp_u32 = (uint32_t) (tmp_u32 / 100);  // div by 100 since the 2030.5 messages have it specified after multiplication by 100
    }
    else 
    {
        // it is zero ;what ever is read from obcm is stored in ESVHi
        tmp_u32 = (uint32_t) (ESDlyTms);
    }

    ss_tx_buf[20] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
    ss_tx_buf[21] = (unsigned char)((tmp_u32 & 0x00FF0000) >> 16);
    ss_tx_buf[22] = (unsigned char)((tmp_u32 & 0x0000FF00) >> 8);
    ss_tx_buf[23] = (unsigned char)(tmp_u32 & 0xFF);
    curr_ss_tx_len = 24;

    // // ESRndTms set to 0xFFFFFFFF
    // ss_tx_buf[24] = 0xFF;
    // ss_tx_buf[25] = 0xFF;
    // ss_tx_buf[26] = 0xFF;
    // ss_tx_buf[27] = 0xFF;
    // tmp_u32 = (uint32_t) (ESRmpTms); 
    // if (ESRmpTms_source == 1) 
    // {
    //     tmp_u32 = (uint32_t) (tmp_u32 / 100);  // div by 100 since the 2030.5 messages have it specified after multiplication by 100
    // }
    // ss_tx_buf[28] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
    // ss_tx_buf[29] = (unsigned char)((tmp_u32 & 0x00FF0000) >> 16);
    // ss_tx_buf[30] = (unsigned char)((tmp_u32 & 0x0000FF00) >> 8);
    // ss_tx_buf[31] = (unsigned char)(tmp_u32 & 0xFF);

    // curr_ss_tx_len = 32;
    read_cmd = READ_NONE;
}

void read_scale_factors_model704()
{
    // model 704 = 0x02C0
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC0);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 56;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_DER_READ_704_SF;
}

void process_704_sf()
{
    if (ss_rx_buf[1] == 2)
    {
        // data is verified
        wsetpct_sf_704 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        if ((wsetpct_sf_704 < -10) || (wsetpct_sf_704 > 10))
        {
            printf("incorrent wsetpct_sf_704 value recd %d \n", wsetpct_sf_704);
            wsetpct_sf_704 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 704 sf, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_wset_pct_704_der()
{
    int tmpi = 0;
    // model 704 = 0x02C0
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC0);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 28;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    //tmpi = (int)( wset_pct_704/pow(10, wsetpct_sf_704) ); // Wsetpct
    tmpi = (int)( wset_pct_704 ); // Wsetpct
    fprintf(stdout, "$$$$ => writing wsetpct on CAN = %d \n", wset_pct_704);

    ss_tx_buf[8] = ( char) (tmpi >> 8);
    ss_tx_buf[9] = (char) (tmpi);

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}


void write_enable_wsetpct_704_der()
{
    // model 705 = 0x02C0
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC0);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 22;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = wset_pct_ena_704; // enable set to 1 ; disable set to 0

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}


void read_scale_factors_model705()
{
    // model 705 = 0x02C1
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC1);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 12;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 3;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_705_SF;
}

void process_705_sf()
{
    if (ss_rx_buf[1] == 6)
    {
        // data is verified
        v_sf_705 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        deptref_sf_705 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        rsptms_sf_705 = (short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);

        if ((v_sf_705 < -10) || (v_sf_705 > 10))
        {
            printf("incorrent v_sf_705 value recd %d \n", v_sf_705);
            v_sf_705 = 0;
        }
        if ((deptref_sf_705 < -10) || (deptref_sf_705 > 10))
        {
            printf("incorrent deptref_sf_705 value recd %d \n", deptref_sf_705);
            deptref_sf_705 = 0;
        }
        if ((rsptms_sf_705 < -10) || (rsptms_sf_705 > 10))
        {
            printf("incorrent rsptms_sf_705 value recd %d \n", rsptms_sf_705);
            rsptms_sf_705 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 705 sf, expected 6; got = %d \n", ss_rx_buf[1]);
    }
}

void write_params1_curve_705_step3()
{
    int tmpi;
    // model 705 = 0x02C1
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC1);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 75;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 4;
    ss_tx_buf[7] = 8; // byte count
    ss_tx_buf[8] = 0x00; // num pts
    ss_tx_buf[9] = (char)volt_var_points_count[volt_var_set_curve_index];
    ss_tx_buf[10] = 0x00; // DeptRef
    ss_tx_buf[11] = 0x03; 
    ss_tx_buf[12] = 0x00; // pri
    ss_tx_buf[13] = 0x01;
    tmpi = (int)( 1/pow(10, v_sf_705) ); // VRef
    ss_tx_buf[14] = ( char) (tmpi >> 8);
    ss_tx_buf[15] = (char) (tmpi);
    curr_ss_tx_len = 16;
    read_cmd = READ_NONE;
}

void write_params2_curve_705_step3()
{
    // model 705 = 0x02C1
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC1);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 80;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 4;
    ss_tx_buf[7] = 8; // byte count
    ss_tx_buf[8] = 0x00; // VRefAutoEna
    ss_tx_buf[9] = 0x00;
    ss_tx_buf[10] = 0x00; // VRefAutoTms
    ss_tx_buf[11] = 0x00; 
    ss_tx_buf[12] = 0x00; // RspTms " default: 5 secs with scale of -1 it should be 50"
    ss_tx_buf[13] = 0x00;
    ss_tx_buf[14] = 0x00;
    ss_tx_buf[15] = 0x32;
    curr_ss_tx_len = 16;
    read_cmd = READ_NONE;
}


void write_volt_var_curve_705_step3()
{
    int32_t tmp_i32;
    uint32_t tmp_u32;
    int ii;
    // model 705 = 0x02C1
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC1);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 85;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) 2*volt_var_points_count[volt_var_set_curve_index];
    ss_tx_buf[7] = 2*volt_var_points_count[volt_var_set_curve_index] * 2; // byte count = num pts (x,y) * 2 bytes per x or y point

    for (ii=0; ii < volt_var_points_count[volt_var_set_curve_index]; ii++) 
    {
        tmp_u32 = (uint32_t) (volt_var_x[volt_var_set_curve_index][ii] / pow(10, v_sf_705));
        ss_tx_buf[8+4*ii] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+4*ii+1] = (unsigned char)(tmp_u32 & 0xFF) ;
        tmp_i32 = (int32_t) (volt_var_y[volt_var_set_curve_index][ii] / pow(10, deptref_sf_705));
        ss_tx_buf[8+4*ii+2] = (unsigned char)((tmp_i32 & 0xFF00) >> 8);
        ss_tx_buf[8+4*ii+3] = (unsigned char)(tmp_i32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* volt_var_points_count[volt_var_set_curve_index] *2 + 8;
    read_cmd = READ_NONE;
}

void write_verify_req_volt_var_curve_705_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 705 = 0x02C1
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC1);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 705

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_volt_var_curve_705_step3()
{
    // model 705 = 0x02C1
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC1);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_705_CURVE_VERIFY_RESP;
}

void process_verify_resp_volt_var_curve_705_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        volt_var_curve_verify[volt_var_set_curve_index] = (int) ss_rx_buf[3];
        // TODO: Action to take when volt_var_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_705_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 705 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_enable_volt_var_curve_705_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 705 = 0x02C1
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC1);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (volt_var_curve_verify[volt_var_set_curve_index] == 1)
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else 
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}


void read_scale_factors_model706()
{
    // model 706 = 0x02C2
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC2);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 12;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 3;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_706_SF;
}

void process_706_sf()
{
    if (ss_rx_buf[1] == 6)
    {
        // data is verified
        v_sf_706 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        deptref_sf_706 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        rsptms_sf_706 = (short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);

        if ((v_sf_706 < -10) || (v_sf_706 > 10))
        {
            printf("incorrent v_sf_706 value recd %d \n", v_sf_706);
            v_sf_706 = 0;
        }
        if ((deptref_sf_706 < -10) || (deptref_sf_706 > 10))
        {
            printf("incorrent deptref_sf_706 value recd %d \n", deptref_sf_706);
            deptref_sf_706 = 0;
        }
        if ((rsptms_sf_706 < -10) || (rsptms_sf_706 > 10))
        {
            printf("incorrent rsptms_sf_706 value recd %d \n", rsptms_sf_706);
            rsptms_sf_706 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 706 sf, expected 6; got = %d \n", ss_rx_buf[1]);
    }
}

void write_params_curve_706_step3()
{
    // model 706 = 0x02C2
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC2);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 65;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 4;
    ss_tx_buf[7] = 8; // byte count
    ss_tx_buf[8] = 0x00; // num pts
    ss_tx_buf[9] = (char)volt_watt_points_count[volt_watt_set_curve_index];
    ss_tx_buf[10] = 0x00; // DeptRef
    ss_tx_buf[11] = 0x00; 
    ss_tx_buf[12] = 0x00; // RspTms " default: 100" INCLUSIVE OF factor (-1)
    ss_tx_buf[13] = 0x00;
    ss_tx_buf[14] = 0x00;
    ss_tx_buf[15] = 0x64;
    curr_ss_tx_len = 16;
    read_cmd = READ_NONE;
}

void write_volt_watt_curve_706_step3()
{
    int32_t tmp_i32;
    uint32_t tmp_u32;
    int ii;
    // model 706 = 0x02C2
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC2);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 70;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) 2*volt_watt_points_count[volt_watt_set_curve_index];
    ss_tx_buf[7] = 2*volt_watt_points_count[volt_watt_set_curve_index] * 2; // byte count = num pts (x,y) * 2 bytes per x or y point

    for (ii=0; ii < volt_watt_points_count[volt_watt_set_curve_index]; ii++) 
    {
        tmp_u32 = (uint32_t) (volt_watt_x[volt_watt_set_curve_index][ii] / pow(10, v_sf_706));
        ss_tx_buf[8+4*ii] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+4*ii+1] = (unsigned char)(tmp_u32 & 0xFF) ;
        tmp_i32 = (int32_t) (volt_watt_y[volt_watt_set_curve_index][ii] / pow(10, deptref_sf_706));
        ss_tx_buf[8+4*ii+2] = (unsigned char)((tmp_i32 & 0xFF00) >> 8);
        ss_tx_buf[8+4*ii+3] = (unsigned char)(tmp_i32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* volt_watt_points_count[volt_watt_set_curve_index] *2 + 8;
    read_cmd = READ_NONE;
}

void write_verify_req_volt_watt_curve_706_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 706 = 0x02C2
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC2);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 706

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_volt_watt_curve_706_step3()
{
    // model 706 = 0x02C2
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC2);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_706_CURVE_VERIFY_RESP;
}

void process_verify_resp_volt_watt_curve_706_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        volt_watt_curve_verify[volt_watt_set_curve_index] = (int) ss_rx_buf[3];
        // TODO: Action to take when volt_watt_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_706_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 706 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_enable_volt_watt_curve_706_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 706 = 0x02C2
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC2);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (volt_watt_curve_verify[volt_var_set_curve_index] == 1) // verified response
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else 
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_scale_factors_model707()
{
    // model 707 = 0x02C3
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC3);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 7;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 2;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_707_SF;
}

void process_707_sf()
{
    if (ss_rx_buf[1] == 4)
    {
        // data is verified
        v_sf_707 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        tms_sf_707 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);

        if ((v_sf_707 < -10) || (v_sf_707 > 10))
        {
            printf("incorrent v_sf_707 value recd %d \n", v_sf_707);
            v_sf_707 = 0;
        }
        if ((tms_sf_707 < -10) || (tms_sf_707 > 10))
        {
            printf("incorrent tms_sf_707 value recd %d \n", tms_sf_707);
            tms_sf_707 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 707 sf, expected 4; got = %d \n", ss_rx_buf[1]);
    }
}

void write_params_curve_707_step3()
{
    // model 707 = 0x02C3
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC3);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 108;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count
    ss_tx_buf[8] = 0x00; // num pts
    ss_tx_buf[9] = (char)low_volt_trip_points_count;
    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}


void write_low_volt_trip_curve_707_step3()
{
    uint32_t tmp_u32;
    int ii;
    // model 707 = 0x02C3
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC3);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 109;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) 3*low_volt_trip_points_count;
    ss_tx_buf[7] = 2*low_volt_trip_points_count * 3; // byte count = num pts (x,y) * 2 bytes per x or y point

    for (ii=0; ii < low_volt_trip_points_count; ii++) 
    {
        tmp_u32 = (uint32_t) (low_volt_trip_y[ii] / pow(10, v_sf_707));
        tmp_u32 = (uint32_t) (tmp_u32 / 100); // model expecting range from 0 to 1 mapped to 0 to 100%
        ss_tx_buf[8+6*ii] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+6*ii+1] = (unsigned char)(tmp_u32 & 0xFF) ;
        tmp_u32 = (uint32_t) (low_volt_trip_x[ii] / pow(10, tms_sf_707));
        ss_tx_buf[8+6*ii+2] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[8+6*ii+3] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[8+6*ii+4] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+6*ii+5] = (unsigned char)(tmp_u32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* low_volt_trip_points_count *3 + 8;
    read_cmd = READ_NONE;
}

void write_low_volt_cess_curve_707_step3()
{
    // combiningnumber of points and data points in a single message
    uint32_t tmp_u32;
    int ii;
    // model 707 = 0x02C3
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC3);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 140;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) (3*low_volt_cess_points_count + 1);
    ss_tx_buf[7] = 2*low_volt_cess_points_count * 3 + 2; // byte count = num pts (x,y) * 2 bytes per x or y point + 2 for number of points
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = (char)low_volt_cess_points_count;

    for (ii=0; ii < low_volt_cess_points_count; ii++) 
    {
        tmp_u32 = (uint32_t) (low_volt_cess_y[ii] / pow(10, v_sf_707));
        tmp_u32 = (uint32_t) (tmp_u32 / 100); // model expects values 0 to 1 mapped to 0 to 100%
        ss_tx_buf[10+6*ii] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[10+6*ii+1] = (unsigned char)(tmp_u32 & 0xFF) ;
        tmp_u32 = (uint32_t) (low_volt_cess_x[ii] / pow(10, tms_sf_707));
        ss_tx_buf[10+6*ii+2] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[10+6*ii+3] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[10+6*ii+4] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[10+6*ii+5] = (unsigned char)(tmp_u32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* low_volt_cess_points_count *3 + 8 + 2;
    read_cmd = READ_NONE;
}

void write_verify_req_low_volt_trip_curve_707_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 707 = 0x02C3
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC3);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 707

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_low_volt_trip_curve_707_step3()
{
    // model 707 = 0x02C3
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC3);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_707_CURVE_VERIFY_RESP;
}

void process_verify_resp_low_volt_trip_curve_707_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        low_volt_trip_curve_verify = (int) ss_rx_buf[3];
        // TODO: Action to take when low_volt_trip_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_707_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 707 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_enable_low_volt_trip_curve_707_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 707 = 0x02C3
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC3);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (low_volt_trip_curve_verify == 1) // verified 
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_scale_factors_model708()
{
    // model 708 = 0x02C4
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC4);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 7;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 2;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_708_SF;
}

void process_708_sf()
{
    if (ss_rx_buf[1] == 4)
    {
        // data is verified
        v_sf_708 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        tms_sf_708 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);

        if ((v_sf_708 < -10) || (v_sf_708 > 10))
        {
            printf("incorrent v_sf_708 value recd %d \n", v_sf_708);
            v_sf_708 = 0;
        }
        if ((tms_sf_708 < -10) || (tms_sf_708 > 10))
        {
            printf("incorrent tms_sf_708 value recd %d \n", tms_sf_708);
            tms_sf_708 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 708 sf, expected 4; got = %d \n", ss_rx_buf[1]);
    }
}

void write_params_curve_708_step3()
{
    // model 708 = 0x02C4
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC4);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 108;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count
    ss_tx_buf[8] = 0x00; // num pts
    ss_tx_buf[9] = (char)high_volt_trip_points_count;
    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}


void write_high_volt_trip_curve_708_step3()
{
    uint32_t tmp_u32;
    int ii;
    // model 708 = 0x02C4
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC4);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 109;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) 3*high_volt_trip_points_count;
    ss_tx_buf[7] = 2*high_volt_trip_points_count * 3; // byte count = num pts (x,y) * 2 bytes per x or y point

    for (ii=0; ii < high_volt_trip_points_count; ii++) 
    {
        tmp_u32 = (uint32_t) (high_volt_trip_y[ii] / pow(10, v_sf_708));
        tmp_u32 = (uint32_t) (tmp_u32 / 100); // model expects values 0 to 1 mapped to 0 to 100%
        ss_tx_buf[8+6*ii] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+6*ii+1] = (unsigned char)(tmp_u32 & 0xFF) ;
        tmp_u32 = (uint32_t) (high_volt_trip_x[ii] / pow(10, tms_sf_708));
        ss_tx_buf[8+6*ii+2] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[8+6*ii+3] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[8+6*ii+4] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+6*ii+5] = (unsigned char)(tmp_u32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* high_volt_trip_points_count *3 + 8;
    read_cmd = READ_NONE;
}

void write_high_volt_cess_curve_708_step3()
{
    uint32_t tmp_u32;
    int ii;
    // model 708 = 0x02C4
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC4);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 140;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) (3*high_volt_cess_points_count + 1);
    ss_tx_buf[7] = 2*high_volt_cess_points_count * 3 + 2; // byte count = num pts (x,y) * 2 bytes per x or y point + 2 for num of pts
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = (unsigned char) (high_volt_cess_points_count);

    for (ii=0; ii < high_volt_cess_points_count; ii++) 
    {
        tmp_u32 = (uint32_t) (high_volt_cess_y[ii] / pow(10, v_sf_708));
        tmp_u32 = (uint32_t) (tmp_u32 / 100); // model expects values 0 to 1 mapped to 0 to 100%
        ss_tx_buf[10+6*ii] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[10+6*ii+1] = (unsigned char)(tmp_u32 & 0xFF) ;
        tmp_u32 = (uint32_t) (high_volt_cess_x[ii] / pow(10, tms_sf_708));
        ss_tx_buf[10+6*ii+2] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[10+6*ii+3] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[10+6*ii+4] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[10+6*ii+5] = (unsigned char)(tmp_u32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* high_volt_cess_points_count *3 + 8 + 2;
    read_cmd = READ_NONE;
}


void write_verify_req_high_volt_trip_curve_708_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 708 = 0x02C4
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC4);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 708

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_high_volt_trip_curve_708_step3()
{
    // model 708 = 0x02C4
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC4);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_708_CURVE_VERIFY_RESP;
}

void process_verify_resp_high_volt_trip_curve_708_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        high_volt_trip_curve_verify = (int) ss_rx_buf[3];
        // TODO: Action to take when high_volt_trip_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_708_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 708 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_enable_high_volt_trip_curve_708_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 708 = 0x02C4
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC4);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (high_volt_trip_curve_verify == 1)
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_scale_factors_model709()
{
    // model 709 = 0x02C5
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC5);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 7;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 2;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_709_SF;
}

void process_709_sf()
{
    if (ss_rx_buf[1] == 4)
    {
        // data is verified
        hz_sf_709 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        tms_sf_709 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);

        if ((hz_sf_709 < -10) || (hz_sf_709 > 10))
        {
            printf("incorrent hz_sf_709 value recd %d \n", hz_sf_709);
            hz_sf_709 = 0;
        }
        if ((tms_sf_709 < -10) || (tms_sf_709 > 10))
        {
            printf("incorrent tms_sf_709 value recd %d \n", tms_sf_709);
            tms_sf_709 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 709 sf, expected 4; got = %d \n", ss_rx_buf[1]);
    }
}

void write_params_curve_709_step3()
{
    // model 709 = 0x02C5
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC5);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 138;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count
    ss_tx_buf[8] = 0x00; // num pts
    ss_tx_buf[9] = (char)low_freq_trip_points_count;
    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}



void write_low_freq_trip_curve_709_step3()
{
    uint32_t tmp_u32;
    int ii;
    // model 709 = 0x02C5
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC5);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 139;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) (4*low_freq_trip_points_count);
    ss_tx_buf[7] = 2*low_freq_trip_points_count * 4; // byte count = num pts (x,y) * 4 bytes per x or y point

    for (ii=0; ii < low_freq_trip_points_count; ii++) 
    {
        tmp_u32 = (uint32_t) (low_freq_trip_y[ii] / pow(10, hz_sf_709));
        ss_tx_buf[8+8*ii] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[8+8*ii+1] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[8+8*ii+2] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+8*ii+3] = (unsigned char)(tmp_u32 & 0xFF) ;

        tmp_u32 = (uint32_t) (low_freq_trip_x[ii] / pow(10, tms_sf_709));
        ss_tx_buf[8+8*ii+4] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[8+8*ii+5] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[8+8*ii+6] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+8*ii+7] = (unsigned char)(tmp_u32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* low_freq_trip_points_count *4 + 8;
    read_cmd = READ_NONE;
}

void write_verify_req_low_freq_trip_curve_709_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 709 = 0x02C5
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC5);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 709

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_low_freq_trip_curve_709_step3()
{
    // model 709 = 0x02C5
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC5);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_709_CURVE_VERIFY_RESP;
}

void process_verify_resp_low_freq_trip_curve_709_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        low_freq_trip_curve_verify = (int) ss_rx_buf[3];
        // TODO: Action to take when low_freq_trip_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_709_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 709 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_enable_low_freq_trip_curve_709_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 709 = 0x02C5
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC5);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (low_freq_trip_curve_verify == 1)
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_scale_factors_model710()
{
    // model 710 = 0x02C6
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC6);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 7;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 2;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_710_SF;
}

void process_710_sf()
{
    if (ss_rx_buf[1] == 4)
    {
        // data is verified
        hz_sf_710 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        tms_sf_710 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);

        if ((hz_sf_710 < -10) || (hz_sf_710 > 10))
        {
            printf("incorrent hz_sf_710 value recd %d \n", hz_sf_710);
            hz_sf_710 = 0;
        }
        if ((tms_sf_710 < -10) || (tms_sf_710 > 10))
        {
            printf("incorrent tms_sf_710 value recd %d \n", tms_sf_710);
            tms_sf_710 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 710 sf, expected 4; got = %d \n", ss_rx_buf[1]);
    }
}

void write_params_curve_710_step3()
{
    // model 710 = 0x02C6
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC6);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 138;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count
    ss_tx_buf[8] = 0x00; // num pts
    ss_tx_buf[9] = (char)high_freq_trip_points_count;
    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void write_high_freq_trip_curve_710_step3()
{
    uint32_t tmp_u32;
    int ii;
    // model 710 = 0x02C6
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC6);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 139;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) 4*high_freq_trip_points_count;
    ss_tx_buf[7] = 2*high_freq_trip_points_count * 4; // byte count = num pts (x,y) * 4 bytes per x or y point

    for (ii=0; ii < high_freq_trip_points_count; ii++) 
    {
        tmp_u32 = (uint32_t) round((high_freq_trip_y[ii] / pow(10, hz_sf_710)));
        ss_tx_buf[8+8*ii] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[8+8*ii+1] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[8+8*ii+2] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+8*ii+3] = (unsigned char)(tmp_u32 & 0xFF) ;

        tmp_u32 = (uint32_t) round((high_freq_trip_x[ii] / pow(10, tms_sf_710)));
        ss_tx_buf[8+8*ii+4] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
        ss_tx_buf[8+8*ii+5] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
        ss_tx_buf[8+8*ii+6] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
        ss_tx_buf[8+8*ii+7] = (unsigned char)(tmp_u32 & 0xFF) ;
    }
    curr_ss_tx_len = 2* high_freq_trip_points_count *4 + 8;
    read_cmd = READ_NONE;
}

void write_verify_req_high_freq_trip_curve_710_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 710 = 0x02C6
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC6);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 710

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_high_freq_trip_curve_710_step3()
{
    // model 710 = 0x02C6
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC6);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_710_CURVE_VERIFY_RESP;
}

void process_verify_resp_high_freq_trip_curve_710_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        high_freq_trip_curve_verify = (int) ss_rx_buf[3];
        // TODO: Action to take when high_freq_trip_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_710_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 710 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_enable_high_freq_trip_curve_710_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 710 = 0x02C6
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC6);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (high_freq_trip_curve_verify == 1)
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else 
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_scale_factors_model711()
{
    // model 711 = 0x02C7
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC7);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 11;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 3;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_711_SF;
}

void process_711_sf()
{
    if (ss_rx_buf[1] == 6)
    {
        // data is verified
        db_sf_711 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        k_sf_711 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        rsptms_sf_711 = (short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);

        if ((db_sf_711 < -10) || (db_sf_711 > 10))
        {
            printf("incorrent db_sf_711 value recd %d \n", db_sf_711);
            db_sf_711 = 0;
        }
        if ((k_sf_711 < -10) || (k_sf_711 > 10))
        {
            printf("incorrent k_sf_711 value recd %d \n", k_sf_711);
            k_sf_711 = 0;
        }
        if ((rsptms_sf_711 < -10) || (rsptms_sf_711 > 10))
        {
            printf("incorrent rsptms_sf_711 value recd %d \n", rsptms_sf_711);
            rsptms_sf_711 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 711 sf, expected 6; got = %d \n", ss_rx_buf[1]);
    }
}

void write_freq_droop_curve_711_step3()
{
    // //debug
    // fprintf(stdout, "<<<<xxxx>>>>!!!! Freq Droop set up buffer to write droop curve, db_sf = %d, k_sf = %d", db_sf_711, k_sf_711);
    // fprintf(stdout, "dbof = %.3f, \t dbuf=%.3f \n", DbOf, DbUf);
    // fprintf(stdout, "KoF  = %.3f, \t KUF =%.3f, Rsptms = %.3f \n", KOf, KUf, RspTms);

    uint32_t tmp_u32;
    uint16_t tmp_u16;
    // model 711 = 0x02C7
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC7);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 34;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 8;
    ss_tx_buf[7] = 16; // byte count
    tmp_u32 = (uint32_t) round((DbOf / pow(10,db_sf_711))); 
    //fprintf(stdout, "writing to OBCM DBof = %u \n", tmp_u32);
    ss_tx_buf[8] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
    ss_tx_buf[9] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
    ss_tx_buf[10] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
    ss_tx_buf[11] = (unsigned char)(tmp_u32 & 0xFF) ;
    tmp_u32 = (uint32_t)round((DbUf / pow(10,db_sf_711)));
    //fprintf(stdout, "writing to OBCM DBUf = %u \n", tmp_u32);
    ss_tx_buf[12] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
    ss_tx_buf[13] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
    ss_tx_buf[14] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
    ss_tx_buf[15] = (unsigned char)(tmp_u32 & 0xFF) ;
    tmp_u16 = (uint16_t) round((KOf / pow(10, k_sf_711)));
    //fprintf(stdout, "writing to OBCM kOf = %u \n", tmp_u16);
    ss_tx_buf[16] = (unsigned char)((tmp_u16 & 0xFF00) >> 8);
    ss_tx_buf[17] = (unsigned char)(tmp_u16 & 0xFF) ;
    tmp_u16 = (uint16_t) round((KUf / pow(10, k_sf_711)));
    //fprintf(stdout, "writing to OBCM Kuf = %u \n", tmp_u16);
    ss_tx_buf[18] = (unsigned char)((tmp_u16 & 0xFF00) >> 8);
    ss_tx_buf[19] = (unsigned char)(tmp_u16 & 0xFF) ;
    tmp_u32 = (uint32_t) (RspTms / pow(10, rsptms_sf_711));
    ss_tx_buf[20] = (unsigned char)((tmp_u32 & 0xFF000000) >> 24);
    ss_tx_buf[21] = (unsigned char)((tmp_u32 & 0xFF0000) >> 16);
    ss_tx_buf[22] = (unsigned char)((tmp_u32 & 0xFF00) >> 8);
    ss_tx_buf[23] = (unsigned char)(tmp_u32 & 0xFF) ;


    curr_ss_tx_len = 24 ;
    read_cmd = READ_NONE;
}

void write_verify_req_freq_droop_curve_711_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 711 = 0x02C7
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC7);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 711

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_freq_droop_curve_711_step3()
{
    // model 711 = 0x02C7
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC7);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_711_CURVE_VERIFY_RESP;
}

void process_verify_resp_freq_droop_curve_711_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        freq_droop_curve_verify = (int) ss_rx_buf[3];
        // TODO: Action to take when freq_droop_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_711_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 711 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}

void write_enable_freq_droop_curve_711_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 711 = 0x02C7
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC7);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (freq_droop_curve_verify == 1)
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_scale_factors_model712()
{
    // model 712 = 0x02C8
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC8);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 12;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 2;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_712_SF;
}

void process_712_sf()
{
    if (ss_rx_buf[1] == 4)
    {
        // data is verified
        w_sf_712 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        deptref_sf_712 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);

        if ((w_sf_712 < -10) || (w_sf_712 > 10))
        {
            printf("incorrent w_sf_712 value recd %d \n", w_sf_712);
            w_sf_712 = 0;
        }
        if ((deptref_sf_712 < -10) || (deptref_sf_712 > 10))
        {
            printf("incorrent deptref_sf_712 value recd %d \n", deptref_sf_712);
            deptref_sf_712 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 712 sf, expected 4; got = %d \n", ss_rx_buf[1]);
    }
}

void write_params_curve_712_step3()
{
    // model 706 = 0x02C2
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC2);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 62;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 3;
    ss_tx_buf[7] = 6; // byte count
    ss_tx_buf[8] = 0x00; // num pts
    ss_tx_buf[9] = (char)watt_var_points_count;
    ss_tx_buf[10] = 0x00; // DeptRef
    ss_tx_buf[11] = 0x03; 
    ss_tx_buf[12] = 0x00; // pri
    ss_tx_buf[13] = 0x01;
    curr_ss_tx_len = 14;
    read_cmd = READ_NONE;
}

void write_watt_var_curve_712_step3()
{
    int32_t tmp_i32;
    int ii;
    // model 712 = 0x02C8
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC8);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 66;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = (unsigned char) 2*watt_var_points_count;
    ss_tx_buf[7] = 2*watt_var_points_count * 2; // byte count = num pts (x,y) * 2 bytes per x or y point

    for (ii=0; ii < watt_var_points_count; ii++) 
    {
        tmp_i32 = (int32_t) (watt_var_x[ii] / pow(10, w_sf_712));
        ss_tx_buf[8+4*ii] = (unsigned char)((tmp_i32 & 0xFF00) >> 8);
        ss_tx_buf[8+4*ii+1] = (unsigned char)(tmp_i32 & 0xFF0000);

        tmp_i32 = (int32_t) (watt_var_y[ii] / pow(10, deptref_sf_712));
        ss_tx_buf[8+4*ii+3] = (unsigned char)((tmp_i32 & 0xFF00) >> 8);
        ss_tx_buf[8+4*ii+4] = (unsigned char)(tmp_i32 & 0xFF);
    }
    curr_ss_tx_len = 2* watt_var_points_count *2 + 8;
    read_cmd = READ_NONE;
}

void write_verify_req_watt_var_curve_712_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 712 = 0x02C8
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC8);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = 2; // third curve verify in model 712

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_verify_resp_watt_var_curve_712_step3()
{
    // model 712 = 0x02C8
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC8);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 4;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_3_READ_712_CURVE_VERIFY_RESP;
}

void process_verify_resp_watt_var_curve_712_step3()
{
    if (ss_rx_buf[1] == 2)
    {
        // 0 => in progress
        // 1 => completed : success
        // 2 => failed 
        watt_var_curve_verify = (int) ss_rx_buf[3];
        // TODO: Action to take when watt_var_curve_verify == failed
        // TODO: if value is 1, write SSP_3_WRITE_712_CURVE_ENABLE  to top of queue
    }
    else
    {
        printf("recv length is not adequate for 712 verify curve, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}


void write_enable_watt_var_curve_712_step3()
{
    // int32_t tmp_i32;
    // uint32_t tmp_u32;
    // int ii;
    // model 712 = 0x02C8
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xC8);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count 
    ss_tx_buf[8] = 0x00;
    if (watt_var_curve_verify == 1)
    {
        ss_tx_buf[9] = 1; // enable set to 1
    }
    else
    {
        ss_tx_buf[9] = 0; // disable
    }

    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_scale_factors_model701()
{
    // model 701 = 0x02BD
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBD);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 113;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 7;
    curr_ss_tx_len = 7;
    read_cmd = SSP_4_2_READ_701_SF;
}

void process_701_sf()
{
    if (ss_rx_buf[1] == 14)
    {
        // data is verified
        current_sf_701 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        voltage_sf_701 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        frequency_sf_701 = (short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);
        activepower_sf_701 = (short)((ss_rx_buf[8] << 8) | ss_rx_buf[9]);
        powerfactor_sf_701 = (short)((ss_rx_buf[10] << 8) | ss_rx_buf[11]);
        apparentpower_sf_701 = (short)((ss_rx_buf[12] << 8) | ss_rx_buf[13]);
        reactivepower_sf_701 = (short)((ss_rx_buf[14] << 8) | ss_rx_buf[15]);

        if ((current_sf_701 < -10) || (current_sf_701 > 10))
        {
            printf("incorrent current_sf_701 value recd %d \n", current_sf_701);
            current_sf_701 = 0;
        }
        if ((voltage_sf_701 < -10) || (voltage_sf_701 > 10))
        {
            printf("incorrent voltage_sf_701 value recd %d \n", voltage_sf_701);
            voltage_sf_701 = 0;
        }
        if ((frequency_sf_701 < -10) || (frequency_sf_701 > 10))
        {
            printf("incorrent frequency_sf_701 value recd %d \n", frequency_sf_701);
            frequency_sf_701 = 0;
        }
        if ((activepower_sf_701 < -10) || (activepower_sf_701 > 10))
        {
            printf("incorrent activepower_sf_701 value recd %d \n", activepower_sf_701);
            activepower_sf_701 = 0;
        }
        if ((powerfactor_sf_701 < -10) || (powerfactor_sf_701 > 10))
        {
            printf("incorrent powerfactor_sf_701 value recd %d \n", powerfactor_sf_701);
            powerfactor_sf_701 = 0;
        }
        if ((apparentpower_sf_701 < -10) || (apparentpower_sf_701 > 10))
        {
            printf("incorrent apparentpower_sf_701 value recd %d \n", apparentpower_sf_701);
            apparentpower_sf_701 = 0;
        }
        if ((reactivepower_sf_701 < -10) || (reactivepower_sf_701 > 10))
        {
            printf("incorrent reactivepower_sf_701 value recd %d \n", reactivepower_sf_701);
            reactivepower_sf_701 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 701 sf, expected 14; got = %d \n", ss_rx_buf[1]);
    }
}

void read_actype_model701()
{
    // model 701 = 0x02BD
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBD);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    curr_ss_tx_len = 7;
    read_cmd = SSP_4_3_READ_701_ACTYPE;
}

void process_701_actype()
{
    if (ss_rx_buf[1] == 2)
    {
        // data is verified
        if (ss_rx_buf[3] == 0)  
        {
            actype_sep2 = 129;
        }
        else if (ss_rx_buf[3] == 1)
        {
            actype_sep2 = 132;
        }
        else if (ss_rx_buf[3] == 2)
        {
            actype_sep2 = 224;
        }
        else 
        {
            actype_sep2 = 0;
        }
    }
    else
    {
        printf("recv length is not adequate for 701 ac type, expected 2; got = %d \n", ss_rx_buf[1]);
    }
}


void write_es_status_default_dercontrol_step5()
{
    //uint32_t tmp_u32;
    // model 703 = 0x02BF
    ss_tx_buf[0] = (unsigned char)WRITE_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBF);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 2;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 1;
    ss_tx_buf[7] = 2; // byte count

    ss_tx_buf[8] = 0x00;
    ss_tx_buf[9] = ES;
    
    curr_ss_tx_len = 10;
    read_cmd = READ_NONE;
}

void read_params_model701()
{
    // model 701 = 0x02BD
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBD);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 10;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 9;
    curr_ss_tx_len = 7;
    read_cmd = SSP_6_1_READ_701_REPORT_VALUE;
}

void process_701_params()
{
    uint32_t tmp_u32;
    if (ss_rx_buf[1] == 18)
    {
        // data is verified
        activepower_701_rep = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        reactivepower_701_rep = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        voltage_701_rep = (short)((ss_rx_buf[12] << 8) | ss_rx_buf[13]);
        tmp_u32 = (uint32_t) ( ( ((ss_rx_buf[16] << 8) | ss_rx_buf[17])  ) << 16);
        tmp_u32 = tmp_u32 + (uint32_t)((ss_rx_buf[18] << 8) | ss_rx_buf[19]);
        frequency_701_rep = tmp_u32;
    }
    else
    {
        printf("recv length is not adequate for 701 params, expected 16; got = %d \n", ss_rx_buf[1]);
    }
}

void read_status_model701()
{
    // model 701 = 0x02BD
    ss_tx_buf[0] = (unsigned char)READ_REG_SS_CODE;
    ss_tx_buf[1] = (unsigned char)(0x02);
    ss_tx_buf[2] = (unsigned char)(0xBD);
    ss_tx_buf[3] = 0x00;
    ss_tx_buf[4] = 3;
    ss_tx_buf[5] = 0x00;
    ss_tx_buf[6] = 3;
    curr_ss_tx_len = 7;
    read_cmd = SSP_6_2_READ_701_STATUS_VALUE;
}

void process_701_status()
{
    if (ss_rx_buf[1] == 6)
    {
        // data is verified
        status_701 = (short)((ss_rx_buf[2] << 8) | ss_rx_buf[3]);
        inv_status_701 = (short)((ss_rx_buf[4] << 8) | ss_rx_buf[5]);
        conn_status_701 = (short)((ss_rx_buf[6] << 8) | ss_rx_buf[7]);
        status_time_701 = getCurrentTime();
    }
    else
    {
        printf("recv length is not adequate for 701 status, expected 6; got = %d \n", ss_rx_buf[1]);
    }
}

void process_recv_message_ssproto()
{
    // // debug
    // fprintf(stdout, "func: process_recv_message_ssproto read_cmd = %d \n", read_cmd);
    
    if (read_cmd == READ_NONE)
    {
        return;
    }

    if (verify_message())
    {
        switch (read_cmd)
        {
        case SSP_2_0_READ_702_SF:
            process_702_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_2_1A_READ_702_NAMEPLATE_PART1:
            process_702_nameplate_part1();
            read_cmd = READ_NONE;
            break;
        case SSP_2_1B_READ_702_NAMEPLATE_PART2:
            process_702_nameplate_part2();
            read_cmd = READ_NONE;
            break;
        case SSP_2_2_READ_702_CONFIG_INFO:
            process_702_config_info();
            read_cmd = READ_NONE;
            break;
        case SSP_2_3_READ_703_ALL:
            process_all_703();
            read_cmd = READ_NONE;
            break;
        case SSP_2_5_READ_001_PARAMS:
            process_params_001();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_705_SF:
            process_705_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_705_CURVE_VERIFY_RESP:
            process_verify_resp_volt_var_curve_705_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_706_SF:
            process_706_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_706_CURVE_VERIFY_RESP:
            process_verify_resp_volt_watt_curve_706_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_707_SF:
            process_707_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_707_CURVE_VERIFY_RESP:
            process_verify_resp_low_volt_trip_curve_707_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_708_SF:
            process_708_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_708_CURVE_VERIFY_RESP:
            process_verify_resp_high_volt_trip_curve_708_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_709_SF:
            process_709_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_709_CURVE_VERIFY_RESP:
            process_verify_resp_low_freq_trip_curve_709_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_710_SF:
            process_710_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_710_CURVE_VERIFY_RESP:
            process_verify_resp_high_freq_trip_curve_710_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_711_SF:
            process_711_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_711_CURVE_VERIFY_RESP:
            process_verify_resp_freq_droop_curve_711_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_712_SF:
            process_712_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_3_READ_712_CURVE_VERIFY_RESP:
            process_verify_resp_watt_var_curve_712_step3();
            read_cmd = READ_NONE;
            break;
        case SSP_4_2_READ_701_SF:
            process_701_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_4_3_READ_701_ACTYPE:
            process_701_actype();
            read_cmd = READ_NONE;
            break;
        case SSP_6_1_READ_701_REPORT_VALUE:
            process_701_params();
            read_cmd = READ_NONE;
            break;
        case SSP_6_2_READ_701_STATUS_VALUE:
            process_701_status();
            read_cmd = READ_NONE;
            break;
        case SSP_DER_READ_704_SF:
            process_704_sf();
            read_cmd = READ_NONE;
            break;
        case SSP_TEST_READ_CUSTOM_MODEL:
            process_test_read_custom_model();
            read_cmd = READ_NONE;
            break;
        }
    }
}

void ss_init_task(int task_id)
{
    int ii;
    current_proto_task_id = task_id;
    switch (task_id) {
        case SSP_1_0_RECEIVED_DERSETTINGS:
            // DO NOTHING
            break;
        case SSP_2_0_READ_702_SF:
            read_scale_factors_model702();
            start_ss_can_proto();
            break;
        case SSP_2_1A_READ_702_NAMEPLATE_PART1:
            read_702_nameplate_part1();
            start_ss_can_proto();
            break;
        case SSP_2_1B_READ_702_NAMEPLATE_PART2:
            read_702_nameplate_part2();
            start_ss_can_proto();
            break;
        case SSP_2_2_READ_702_CONFIG_INFO:
            read_702_config_info();
            start_ss_can_proto();
            break;
        case SSP_2_3_READ_703_ALL:
            read_all_703();
            start_ss_can_proto();
            break;
        case SSP_2_4_RECEIVED_WHMAX:
            // DO NOTHING
            break;
        case SSP_2_5_READ_001_PARAMS:
            read_params_001();
            start_ss_can_proto();
            break;
        case SSP_2_6_RECEIVED_HCP_SW_VERSION:
            // do nothing
            break;
        case SSP_3_RECEIVED_DEFAULT_DERCONTROL:
            // do nothing
            if (default_derc_received == 1)
            {
                write_default_dercontrol_step3();
                start_ss_can_proto();
            }
            break;
        case SSP_4_1_WRITE_MUP_SETUP:
            // do nothing
            break;
        case SSP_4_2_READ_701_SF:
            read_scale_factors_model701();
            start_ss_can_proto();
            break;
        case SSP_4_3_READ_701_ACTYPE:
            read_actype_model701();
            start_ss_can_proto();
            break;
        case SSP_4_4_WRITE_ACTIVE_POWER_MMR_SETUP:
            // do nothing
            break;
        case SSP_4_5_WRITE_REACTIVE_POWER_MMR_SETUP:
            // do nothing
            break;
        case SSP_4_6_WRITE_VOLTAGE_MMR_SETUP:
            // do nothing
            break;
        case SSP_4_7_WRITE_FREQUENCY_MMR_SETUP:
            // do nothing
            break;
        case SSP_5_1_RECEIVED_DEFAULT_DERCONTROL:
            // do nothing
            break;
        case SSP_5_2_WRITE_703_ES:
            ii = high_freq_trip_curve_verify + low_freq_trip_curve_verify;
            ii = ii + low_volt_trip_curve_verify + high_volt_trip_curve_verify;
            ii = ii + volt_var_curve_verify[0] + volt_watt_curve_verify[0] + freq_droop_curve_verify;
            fprintf(stdout, "HF trip = %d, LF trip = %d\n", high_freq_trip_curve_verify, low_freq_trip_curve_verify);
            fprintf(stdout, "HV trip = %d, LV trip = %d\n", high_volt_trip_curve_verify, low_volt_trip_curve_verify);
            fprintf(stdout, "volt var = %d, volt watt = %d, freq droop = %d\n" ,
                volt_var_curve_verify[0], volt_watt_curve_verify[0], freq_droop_curve_verify);
            fprintf(stdout, "------\nprevES = %d, ES = %d, sum ii = %d\n" ,prev_ES, ES, ii);
            if (ii >= 7 )  //7) 
            {
                if (prev_ES != ES) 
                {
                    write_es_status_default_dercontrol_step5();
                    start_ss_can_proto();
                }
            }
            // else 
            // {
            //     enqueue(SSP_5_2_WRITE_703_ES);
            // }
            break;
        case SSP_6_1_READ_701_REPORT_VALUE:
            read_params_model701();
            start_ss_can_proto();
            break;
        case SSP_6_2_READ_701_STATUS_VALUE:
            read_status_model701();
            start_ss_can_proto();
            break;
        case SSP_3_READ_705_SF:
            read_scale_factors_model705();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_705_PARAMS_1:
            write_params1_curve_705_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_705_PARAMS_2:
            write_params2_curve_705_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_705_CURVE_DATA:
            write_volt_var_curve_705_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_705_CURVE_VERIFY_REQ:
            write_verify_req_volt_var_curve_705_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_705_CURVE_VERIFY_RESP:
            read_verify_resp_volt_var_curve_705_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 705 verify resp\n");
            break;
        case SSP_3_WRITE_705_CURVE_ENABLE:
            write_enable_volt_var_curve_705_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_706_SF:
            read_scale_factors_model706();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_706_PARAMS:
            write_params_curve_706_step3();
            start_ss_can_proto();
            break;            
        case SSP_3_WRITE_706_CURVE_DATA:
            write_volt_watt_curve_706_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_706_CURVE_VERIFY_REQ:
            write_verify_req_volt_watt_curve_706_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_706_CURVE_VERIFY_RESP:
            read_verify_resp_volt_watt_curve_706_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 706 verify resp\n");
            break;
        case SSP_3_WRITE_706_CURVE_ENABLE:
            write_enable_volt_watt_curve_706_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_707_SF:
            read_scale_factors_model707();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_707_PARAMS:
            write_params_curve_707_step3();
            start_ss_can_proto();
            break;            
        case SSP_3_WRITE_707_CURVE_DATA_MUST_TRIP:
            write_low_volt_trip_curve_707_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_707_CURVE_DATA_MOME_CESS:
            write_low_volt_cess_curve_707_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_707_CURVE_VERIFY_REQ:
            write_verify_req_low_volt_trip_curve_707_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_707_CURVE_VERIFY_RESP:
            read_verify_resp_low_volt_trip_curve_707_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 707 verify resp\n");
            break;
        case SSP_3_WRITE_707_CURVE_ENABLE:
            write_enable_low_volt_trip_curve_707_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_708_SF:
            read_scale_factors_model708();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_708_PARAMS:
            write_params_curve_708_step3();
            start_ss_can_proto();
            break;            
        case SSP_3_WRITE_708_CURVE_DATA_MUST_TRIP:
            write_high_volt_trip_curve_708_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_708_CURVE_DATA_MOME_CESS:
            write_high_volt_cess_curve_708_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_708_CURVE_VERIFY_REQ:
            write_verify_req_high_volt_trip_curve_708_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_708_CURVE_VERIFY_RESP:
            read_verify_resp_high_volt_trip_curve_708_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 708 verify resp\n");
            break;
        case SSP_3_WRITE_708_CURVE_ENABLE:
            write_enable_high_volt_trip_curve_708_step3();
            start_ss_can_proto();
            break;

        case SSP_3_READ_709_SF:
            read_scale_factors_model709();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_709_PARAMS:
            write_params_curve_709_step3();
            start_ss_can_proto();
            break;            
        case SSP_3_WRITE_709_CURVE_DATA:
            write_low_freq_trip_curve_709_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_709_CURVE_VERIFY_REQ:
            write_verify_req_low_freq_trip_curve_709_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_709_CURVE_VERIFY_RESP:
            read_verify_resp_low_freq_trip_curve_709_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 709 verify resp\n");
            break;
        case SSP_3_WRITE_709_CURVE_ENABLE:
            write_enable_low_freq_trip_curve_709_step3();
            start_ss_can_proto();
            break;

        case SSP_3_READ_710_SF:
            read_scale_factors_model710();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_710_PARAMS:
            write_params_curve_710_step3();
            start_ss_can_proto();
            break;            
        case SSP_3_WRITE_710_CURVE_DATA:
            write_high_freq_trip_curve_710_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_710_CURVE_VERIFY_REQ:
            write_verify_req_high_freq_trip_curve_710_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_710_CURVE_VERIFY_RESP:
            read_verify_resp_high_freq_trip_curve_710_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 710 verify resp\n");
            break;
        case SSP_3_WRITE_710_CURVE_ENABLE:
            write_enable_high_freq_trip_curve_710_step3();
            start_ss_can_proto();
            break;

        case SSP_3_READ_711_SF:
            read_scale_factors_model711();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_711_CURVE_DATA:
            write_freq_droop_curve_711_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_711_CURVE_VERIFY_REQ:
            write_verify_req_freq_droop_curve_711_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_711_CURVE_VERIFY_RESP:
            read_verify_resp_freq_droop_curve_711_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 711 verify resp\n");
            break;
        case SSP_3_WRITE_711_CURVE_ENABLE:
            write_enable_freq_droop_curve_711_step3();
            start_ss_can_proto();
            break;

        case SSP_3_READ_712_SF:
            read_scale_factors_model712();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_712_PARAMS:
            write_params_curve_712_step3();
            start_ss_can_proto();
            break;            
        case SSP_3_WRITE_712_CURVE_DATA:
            write_watt_var_curve_712_step3();
            start_ss_can_proto();
            break;
        case SSP_3_WRITE_712_CURVE_VERIFY_REQ:
            write_verify_req_watt_var_curve_712_step3();
            start_ss_can_proto();
            break;
        case SSP_3_READ_712_CURVE_VERIFY_RESP:
            read_verify_resp_watt_var_curve_712_step3();
            start_ss_can_proto();
            verify_start_time = getCurrentTime();
            fprintf(stdout, "xxxx====xxxx---> started curve 712 verify resp\n");
            break;
        case SSP_3_WRITE_712_CURVE_ENABLE:
            write_enable_watt_var_curve_712_step3();
            start_ss_can_proto();
            break;

        case SSP_DER_READ_704_SF:
            read_scale_factors_model704();
            start_ss_can_proto();
            break;

        case SSP_DER_WRITE_704_PARAMS:
            write_wset_pct_704_der();
            start_ss_can_proto();
            break;
        case SSP_DER_WRITE_704_ENABLE:
            write_enable_wsetpct_704_der();
            start_ss_can_proto();
            break;
        case SSP_TEST_READ_CUSTOM_MODEL:
            test_read_custom_model();
            start_ss_can_proto();
            break;

        default:
            console_log("invalid task id in ss_init_task => %d \n", task_id);
    }
}

/*
 * return 1 on success and 0 on not completed yet 
 */
int ss_completed_task(int task_id)
{
    int ret_val = 0;
    int ss_can_proto_state;
    int tmpi;
    int ii;
    if (current_proto_task_id > 0)
    {
        switch (task_id)
        {
        case SSP_1_0_RECEIVED_DERSETTINGS:
            if (updated_time_dersett > 0) 
            {
                ret_val = 1;
            }
            break;
        
        case SSP_2_0_READ_702_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_2_1A_READ_702_NAMEPLATE_PART1:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_2_1B_READ_702_NAMEPLATE_PART2:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
                send_dercapability_ind();
            }
            break;
        case SSP_2_2_READ_702_CONFIG_INFO:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_2_3_READ_703_ALL:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_2_4_RECEIVED_WHMAX:
            if (max_Wh_recvd) 
            {
                ret_val = 1;
                send_dersettings_req();
            }
            break;
        case SSP_2_5_READ_001_PARAMS:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_2_6_RECEIVED_HCP_SW_VERSION:
            if (hcp_sw_ver_recvd == 1) 
            {
                ret_val = 1;
                send_deviceinfo_req();
            }
            break;
        case SSP_3_RECEIVED_DEFAULT_DERCONTROL:
            if (default_derc_received == 1)
            {
                //write_default_dercontrol_step3();
                ss_can_proto_state = get_current_state();
                if (ss_can_proto_state == SSP_IDLE_STATE)
                {
                    // debug 
                    fprintf(stdout, "completed write to OBCM default derc set to 0\n");
                    default_derc_received = 0;
                    ret_val = 1;
                }
            }
            else 
            {
                // default derc  not received; will perform this step again when received
                ret_val = 1;
            }
            break;
        case SSP_4_1_WRITE_MUP_SETUP:
            ret_val = 1;
            send_mup_req();
            break;
        case SSP_4_2_READ_701_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_4_3_READ_701_ACTYPE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_4_4_WRITE_ACTIVE_POWER_MMR_SETUP:
            send_mmr_setup_or_data(1, false);
            ret_val = 1;
            break;
        case SSP_4_5_WRITE_REACTIVE_POWER_MMR_SETUP:
            send_mmr_setup_or_data(2, false);
            ret_val = 1;
            break;
        case SSP_4_6_WRITE_VOLTAGE_MMR_SETUP:
            send_mmr_setup_or_data(3, false);
            ret_val = 1;
            break;
        case SSP_4_7_WRITE_FREQUENCY_MMR_SETUP:
            send_mmr_setup_or_data(4, false);
            ret_val = 1;
        case SSP_5_1_RECEIVED_DEFAULT_DERCONTROL:
            if (default_derc_received == 1) {
                ret_val = 1;
                enqueue(SSP_5_1_RECEIVED_DEFAULT_DERCONTROL);
                topqueue(SSP_5_2_WRITE_703_ES);
                default_derc_received = 0;
            }
            else {
                // instead of waiting on this state; enqueue it again
                ret_val = 1;
                enqueue(SSP_5_1_RECEIVED_DEFAULT_DERCONTROL); // try it again next time
            }
            break; 
        case SSP_5_2_WRITE_703_ES:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
                //enqueue(SSP_5_2_WRITE_703_ES);
            }
            ii = high_freq_trip_curve_verify + low_freq_trip_curve_verify;
            ii = ii + low_volt_trip_curve_verify + high_volt_trip_curve_verify;
            ii = ii + volt_var_curve_verify[0] + volt_watt_curve_verify[0] + freq_droop_curve_verify;
            if (ii >= 7 )  //7) 
            {
                if (prev_ES != ES)
                {
                    prev_ES = ES;
                    evcc_es = ES;
                }
            } 
            break;
        case SSP_6_1_READ_701_REPORT_VALUE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
                send_mmr_setup_or_data(1, true);
                send_mmr_setup_or_data(2, true);
                send_mmr_setup_or_data(3, true);
                send_mmr_setup_or_data(4, true);
                enqueue(SSP_6_1_READ_701_REPORT_VALUE);
            }
            break;
        case SSP_6_2_READ_701_STATUS_VALUE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                send_power_status_req();
                send_der_availabilit_req();
                send_der_status_req();
                enqueue(SSP_6_2_READ_701_STATUS_VALUE);   
                ret_val = 1;
            }
            break;
        case SSP_3_READ_705_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_705_PARAMS_1:
        case SSP_3_WRITE_705_PARAMS_2:
        case SSP_3_WRITE_705_CURVE_DATA:
        case SSP_3_WRITE_705_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_705_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_705_CURVE_VERIFY_RESP:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (volt_var_curve_verify[volt_var_set_curve_index] == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (volt_var_curve_verify[volt_var_set_curve_index] == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                        fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 705\n");
                    }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;
        case SSP_3_READ_706_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_706_PARAMS:
        case SSP_3_WRITE_706_CURVE_DATA:
        case SSP_3_WRITE_706_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_706_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_706_CURVE_VERIFY_RESP:
                    ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (volt_watt_curve_verify[volt_watt_set_curve_index] == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (volt_watt_curve_verify[volt_watt_set_curve_index] == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                        fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 706\n");
                    }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;
        case SSP_3_READ_707_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_707_PARAMS:
        case SSP_3_WRITE_707_CURVE_DATA_MUST_TRIP:
        case SSP_3_WRITE_707_CURVE_DATA_MOME_CESS:
        case SSP_3_WRITE_707_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_707_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_707_CURVE_VERIFY_RESP:
                    ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (low_volt_trip_curve_verify == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (low_volt_trip_curve_verify == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                         fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 707\n");
                   }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;
        case SSP_3_READ_708_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_708_PARAMS:
        case SSP_3_WRITE_708_CURVE_DATA_MUST_TRIP:
        case SSP_3_WRITE_708_CURVE_DATA_MOME_CESS:
        case SSP_3_WRITE_708_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_708_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_708_CURVE_VERIFY_RESP:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (high_volt_trip_curve_verify == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (high_volt_trip_curve_verify == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                        fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 708\n");
                    }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;

        case SSP_3_READ_709_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_709_PARAMS:
        case SSP_3_WRITE_709_CURVE_DATA:
        case SSP_3_WRITE_709_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_709_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_709_CURVE_VERIFY_RESP:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (low_freq_trip_curve_verify == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (low_freq_trip_curve_verify == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                        fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 709\n");
                    }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;

        case SSP_3_READ_710_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_710_PARAMS:
        case SSP_3_WRITE_710_CURVE_DATA:
        case SSP_3_WRITE_710_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_710_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_710_CURVE_VERIFY_RESP:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (high_freq_trip_curve_verify == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (high_freq_trip_curve_verify == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                        fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 710\n");
                    }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;

        case SSP_3_READ_711_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_711_PARAMS:
        case SSP_3_WRITE_711_CURVE_DATA:
        case SSP_3_WRITE_711_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_711_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_711_CURVE_VERIFY_RESP:
                    ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (freq_droop_curve_verify == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (freq_droop_curve_verify == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                        fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 711\n");
                    }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;

        case SSP_3_READ_712_SF:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_WRITE_712_PARAMS:
        case SSP_3_WRITE_712_CURVE_DATA:
        case SSP_3_WRITE_712_CURVE_VERIFY_REQ:
        case SSP_3_WRITE_712_CURVE_ENABLE:
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;
        case SSP_3_READ_712_CURVE_VERIFY_RESP:
                    ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                if (watt_var_curve_verify == 1)
                {
                    ret_val = 1;
                    topqueue(SSP_5_2_WRITE_703_ES);
                } 
                else if (watt_var_curve_verify == 2) // verify failied
                {
                    ret_val = 1;
                    // there is no need to write the enable function, so simple remove it from queue
                    tmpi = dequeue_2();
                    // send INVALID CURVE status response to SEP2 client
                    topqueue(SSP_5_2_WRITE_703_ES);
                }
                else
                {
                    verify_end_time = getCurrentTime();
                    if ( (verify_end_time - verify_start_time) > OBCM_VERIFY_TIMEOUT) // ADDING 1 sec in addition to spec provided by DiamondElectric since I am doing init and verify in successive steps
                    {
                        ret_val = 1;
                        // there is no need to write the enable function, so simple remove it from queue
                        tmpi = dequeue_2();
                        // send INVALID CURVE status response to SEP2 client
                        fprintf(stdout, "xxxx======xxxxx===> Timed out waiting to verify curve 712\n");
                    }
                    else
                    {
                        ret_val = 0;
                    }
                }
            }
            break;

        case SSP_DER_WRITE_704_ENABLE:
            //write_enable_wsetpct_704_der();
            ss_can_proto_state = get_current_state();
            if (ss_can_proto_state == SSP_IDLE_STATE)
            {
                ret_val = 1;
            }
            break;

        default:
            // unknown task id; return 1
            console_log("ss completed task(), unknown proto task id => %d\n", task_id);
            ret_val = 1;
            break;
        }
    }
    else 
    {
        console_log("ss completed task called without init for task id => %d\n", task_id);
        ret_val = 1;
    }
    return ret_val;
}

void ss_proto_task()
{
    int tmp_queue_val;
    int num_items_queue2;
    int do_next_task = 0;
    if (current_proto_task_id > 0) // there is a task executing
    {
        // is the task done?
        if (ss_completed_task(current_proto_task_id))
        {
            do_next_task = 1;
        }
    }
    else
    {
        do_next_task = 1;
    }
    if (do_next_task) 
    {
        num_items_queue2 = count_queue_2();
        // load and execute the next task
        if ( 
            (current_proto_task_id > SSP_3_RECEIVED_DEFAULT_DERCONTROL) &&
            (num_items_queue2 > 0)
        )
        {
            tmp_queue_val = dequeue_2();
            if (tmp_queue_val != -1)
            {
                ss_init_task(tmp_queue_val);
            }
        }
        else 
        {
            tmp_queue_val = dequeue();
            if (tmp_queue_val != -1) 
            {
                ss_init_task(tmp_queue_val);
            }
        }
    }
}

int get_ss_proto_task_id()
{
    return current_proto_task_id;
}
