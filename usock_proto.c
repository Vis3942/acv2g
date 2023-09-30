#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include "usock_proto.h"
#include "sl_api.h"
#include "ss_proto.h"
#include "can2sep2.h"
#include "utils.h"
#include "usock_server.h"
#include "task_queue.h"
#include "usock_utils.h"

#define DEFAULT_MMR_NUM_MR_GROUPS     (SL_METER_MIRROR_MAX_MR_GROUPS)
#define DEFAULT_NUM_MMRS (4)
#define DEFAULT_ACTIVEPOWER_DESCRIPTION  "Active Power"
#define DEFAULT_REACTIVEPOWER_DESCRIPTION "Reactive Power"
#define DEFAULT_VOLTAGE_DESCRIPTION  "Voltage"
#define DEFAULT_FREQUENCY_DESCRIPTION "Frequency"

// Default Reading Type information required for Instantaneous demand data
// See SEP2.0 specification, table 12-3.
static sl_cmn_rt_t defaultRtype = {
  SL_XSD_AB_INSTANTANEOUS,       //sl_xsd_acc_behavior_type_t accumulationBehaviour;
  {false, 0},                    // sl_xsd_unit_val_t          calorificValue;
  {false, 0},                    // sl_xsd_unit_val_t          conversionFactor;
  SL_XSD_COMMODITY_ELEC_SECOND,  // sl_xsd_commodity_type_t    commodity;
  SL_XSD_DATA_QUAL_NOT_APPL,     // sl_xsd_data_qual_type_t    dataQualifier;
  SL_XSD_FLOW_DIR_FORWARD,       // sl_xsd_flow_dir_type_t     flowDirection;
  0,                             // u32_t                      intervalLength;
  false,                         // bool                       intervalLengthExists;
  SL_XSD_KIND_DEMAND,            // sl_xsd_kind_type_t         kindType;
  0,                             // u8_t                       maxNumIntervals;
  false,                         // bool                       maxNumIntervalsExists;
  0,                             // u8_t                       numConsumBlocks;
  false,                         // bool                       numConsumBlocksExists;
  0,                             // u8_t                       numTouTiers;
  false,                         // bool                       numTouTiersExists;
  SL_XSD_PHASE_CODE_NOT_APPL,    // sl_xsd_phase_code_type_t   phaseCode;
  SL_XSD_PTM_NONE,               // sl_xsd_ptm_type_t          powerOfTenMultiplier;
  0,                             // u32_t                      subIntervalLength;
  false,                         // bool                       subIntervalLengthExists;
  0,                             // u64_t                      supplyLimit;
  false,                         // bool                       supplyLimitExists;
  0,                             // bool                       tieredConsumptionBlocks;
  false,                         // bool                       tieredConsumptionBlocksExists;
  SL_XSD_UOM_WATT,               // sl_xsd_uom_t               uomType;
};


char recv_buf[2048];
int recv_buf_len = 0;
char send_buf[2048];
int send_buf_len = 0;
char data_4_send_buf[2048];
int data_4_send_buf_len = 0;

int sent_on_usock = 0;
// message type is based on defines in sl_api.h
char proc_buf[3*1024];
int proc_buf_len = 0;
bool server_status_override = false;
bool comm_status_override = false;


void get_data_der_settings()
{
    sl_der_settings_t der_sett = {0};
    int len = sizeof(der_sett);
    memcpy(&der_sett, recv_buf, len);
    setMaxW = (short)(der_sett.setMaxWValue * pow(10, der_sett.setMaxWMultiplier));
    if (der_sett.setMaxChargeRateWExists)
    {
        setMaxChargeRateW = (unsigned short)(der_sett.setMaxChargeRateWValue * pow(10, der_sett.setMaxChargeRateWMultiplier));
    }
    if (der_sett.setMaxVarExists)
    {
        setMaxVar = (unsigned short)(der_sett.setMaxVarValue * pow(10, der_sett.setMaxVarMultiplier));
    }
    if (der_sett.setMaxVarNegativeExists)
    {
        setMaxVarNeg = (short)(der_sett.setMaxVarNegativeValue * pow(10, der_sett.setMaxVarNegativeMultiplier));
    }
    if (der_sett.setVNomExists)
    {
        setVNom = (unsigned short)(der_sett.setVNomValue * pow(10, der_sett.setVNomMultiplier));
    }
    if (der_sett.setVRefExists)
    {
        setVRef = (unsigned short)(der_sett.setVRefValue * pow(10, der_sett.setVRefMultiplier));
    }
    if (der_sett.setVRefOfsExists)
    {
        setVRefOfs = (unsigned short)(der_sett.setVRefOfsValue * pow(10, der_sett.setVRefOfsMultiplier));
    }
    if (der_sett.setMaxVExists)
    {
        setMaxV = (unsigned short)(der_sett.setMaxVValue * pow(10, der_sett.setMaxVMultiplier));
    }
    if (der_sett.setMinVExists)
    {
        setMinV = (unsigned short)(der_sett.setMinVValue * pow(10, der_sett.setMinVMultiplier));
    }
    updated_time_dersett = der_sett.updatedTime;
    // debug
    fprintf(stdout, "==>>>  update time dersett %lld\n", updated_time_dersett);
}

void get_default_der_data()
{
    sl_der_default_derc_t def_derc = {0};
    int len = sizeof(def_derc);
    memcpy(&def_derc, recv_buf, len);
    if (def_derc.dercBase.opModEnergizeExists)
    {
        ES = def_derc.dercBase.opModEnergize;
    }
    else
    {
        ES = 0;
    }
    if (def_derc.setESHighFreqExists)
    {
        ESHzHi = def_derc.setESHighFreq;
    }
    if (def_derc.setESHighVoltExists)
    {
        ESVHi = def_derc.setESHighVolt;
    }
    if (def_derc.setESLowVoltExists)
    {
        ESHzLo = def_derc.setESLowVolt;
    }
    if (def_derc.setESLowVoltExists)
    {
        ESVLo = def_derc.setESLowVolt;
    }
    if (def_derc.setESDelayExists)
    {
        ESDlyTms = def_derc.setESDelay;
    }
    if (def_derc.setESRampTmsExists)
    {
        ESRmpTms = def_derc.setESRampTms;
    }
    default_derc_received = 1;
    if (sts_init == false)
    {
        if (comm_status_override == false)
        {
            comm_status = true; // comm established
        }
        else 
        {
            before_override_comm_status = true;
        }
        if (server_status_override == false)
        {
            server_status = 1; // found
        }
        else 
        {
            before_override_server_status = 1;
        }

        sts_init = true;
    }

}

void get_derc_ind_data() 
{
    sl_der_client_derc_ind derc_ind = {0};
    int len = sizeof(derc_ind);
    memcpy(&derc_ind, recv_buf, len);
    if (derc_ind.derc.dercBase.opModFixedWExists)
    {
        wset_pct_704 = (int)(derc_ind.derc.dercBase.opModFixedW/100);
    }
    else 
    {
        wset_pct_704 = 0;
    }


    // debug
    fprintf(stdout, "activeInfo eventRespStatus = %d \n", derc_ind.activeInfo.eventRespStatus);
    fprintf(stdout, "DERC IND eventStatusCurrStatus = %d \n", derc_ind.eventStatusCurrStatus);

    //if (derc_ind.eventStatusCurrStatus == SL_XSD_EVENT_CURR_STATUS_ACTIVE)
    if (derc_ind.activeInfo.eventRespStatus == SL_XSD_RESP_STATUS_EVENT_STARTED)
    {
        wset_pct_ena_704 = 1; // enable
        // in case there are previous events, this will allow it to continue till 
        // this event starts
        enqueue_2(SSP_DER_WRITE_704_PARAMS);    
        enqueue_2(SSP_DER_WRITE_704_ENABLE);
    }
    else if (derc_ind.activeInfo.eventRespStatus == SL_XSD_RESP_STATUS_MSG_RXED)
    {
        // do nothing wait for event to start
    }
    else if (
        (derc_ind.activeInfo.eventRespStatus == SL_XSD_RESP_STATUS_EVENT_COMPLETED) ||
        (derc_ind.activeInfo.eventRespStatus == SL_XSD_RESP_STATUS_OPT_OUT) ||
        (derc_ind.activeInfo.eventRespStatus == SL_XSD_RESP_STATUS_EVENT_CANCELED) ||
        (derc_ind.activeInfo.eventRespStatus == SL_XSD_RESP_STATUS_EVENT_SUPERSEDED)
    )
    {
        wset_pct_ena_704 = 0; // disable
        enqueue_2(SSP_DER_WRITE_704_ENABLE);
    }

}


void get_freq_droop_data()
{
    sl_xsd_freq_droop_t freq_droop = {0};
    int len = sizeof(freq_droop);
    memcpy(&freq_droop, recv_buf, len);
    DbOf = freq_droop.dBOF;
    DbUf = freq_droop.dBUF;
    KOf = freq_droop.kOF;
    KUf = freq_droop.kUF;
    RspTms = freq_droop.openLoopTms;
}

void get_curve_data()
{
    sl_der_curve_t curve = {0};
    int len = sizeof(curve);
    float *x_pts;
    float *y_pts;
    int *pts_count;
    int *curve_received;
    int ii;
    int x_mul;
    int y_mul;
    memcpy(&curve, recv_buf, len);

    if (curve.curveType == SL_XSD_CURVE_TYPE_VOLT_WATT)
    {
        x_pts = &volt_watt_x[0];
        y_pts = &volt_watt_y[0];
        pts_count = &volt_watt_points_count;
        curve_received = &volt_watt_curve_received;
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_VOLT_VAR)
    {
        x_pts = &volt_var_x[0];
        y_pts = &volt_var_y[0];
        pts_count = &volt_var_points_count;
        curve_received = &volt_var_curve_received;
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_WATT_VAR)
    {
        x_pts = &watt_var_x[0];
        y_pts = &watt_var_y[0];
        pts_count = &watt_var_points_count;
        curve_received = &watt_var_curve_received;
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_LVRT_MUST_TRIP)
    {
        x_pts = &low_volt_trip_x[0];
        y_pts = &low_volt_trip_y[0];
        pts_count = &low_volt_trip_points_count;
        curve_received = &low_volt_trip_curve_received;
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_HVRT_MUST_TRIP)
    {
        x_pts = &high_volt_trip_x[0];
        y_pts = &high_volt_trip_y[0];
        pts_count = &high_volt_trip_points_count;
        curve_received = &high_volt_trip_curve_received;
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_LFRT_MUST_TRIP)
    {
        x_pts = &low_freq_trip_x[0];
        y_pts = &low_freq_trip_y[0];
        pts_count = &low_freq_trip_points_count;
        curve_received = &low_freq_trip_curve_received;
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_HFRT_MUST_TRIP)
    {
        x_pts = &high_freq_trip_x[0];
        y_pts = &high_freq_trip_y[0];
        pts_count = &high_freq_trip_points_count;
        curve_received = &high_freq_trip_curve_received;
    }
    else
    {
        fprintf(stdout, "unsupported curve type %d. Unable to process this curve indication \n", curve.curveType);
        return;
    }

    x_mul = curve.xMultiplier;
    if ((x_mul < -9) || (x_mul > 9))
    {
        x_mul = 0;
    }
    x_mul = (int)pow(10, x_mul); // actual value to multiply by

    y_mul = curve.yMultiplier;
    if ((y_mul < -9) || (y_mul > 9))
    {
        y_mul = 0;
    }
    y_mul = pow(10, y_mul); // actual value to multiply by

    *pts_count = curve.numCurveData;
    *pts_count = MIN(*pts_count, NUM_POINTS_CURVE); //  incase more points come, use only available values
    for (ii = 0; ii < *pts_count; ii++)
    {
        x_pts[ii] = (float)(curve.curveData[ii].xValue * x_mul);
        y_pts[ii] = (float)(curve.curveData[ii].yValue * y_mul);
    }

    *curve_received = 1;

    if (curve.curveType == SL_XSD_CURVE_TYPE_VOLT_WATT)
    {
        enqueue_2(SSP_3_READ_706_SF);
        enqueue_2(SSP_3_WRITE_706_PARAMS);
        enqueue_2(SSP_3_WRITE_706_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_706_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_706_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_706_CURVE_ENABLE);
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_VOLT_VAR)
    {
        enqueue_2(SSP_3_READ_705_SF);
        enqueue_2(SSP_3_WRITE_705_PARAMS_1);
        enqueue_2(SSP_3_WRITE_705_PARAMS_2);
        enqueue_2(SSP_3_WRITE_705_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_705_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_705_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_705_CURVE_ENABLE);
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_WATT_VAR)
    {
        enqueue_2(SSP_3_READ_712_SF);
        enqueue_2(SSP_3_WRITE_712_PARAMS);
        enqueue_2(SSP_3_WRITE_712_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_712_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_712_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_712_CURVE_ENABLE);
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_LVRT_MUST_TRIP)
    {
        enqueue_2(SSP_3_READ_707_SF);
        enqueue_2(SSP_3_WRITE_707_PARAMS);
        enqueue_2(SSP_3_WRITE_707_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_707_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_707_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_707_CURVE_ENABLE);
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_HVRT_MUST_TRIP)
    {
        enqueue_2(SSP_3_READ_708_SF);
        enqueue_2(SSP_3_WRITE_708_PARAMS);
        enqueue_2(SSP_3_WRITE_708_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_708_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_708_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_708_CURVE_ENABLE);
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_LFRT_MUST_TRIP)
    {
        enqueue_2(SSP_3_READ_709_SF);
        enqueue_2(SSP_3_WRITE_709_PARAMS);
        enqueue_2(SSP_3_WRITE_709_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_709_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_709_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_709_CURVE_ENABLE);
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_HFRT_MUST_TRIP)
    {
        enqueue_2(SSP_3_READ_710_SF);
        enqueue_2(SSP_3_WRITE_710_PARAMS);
        enqueue_2(SSP_3_WRITE_710_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_710_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_710_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_710_CURVE_ENABLE);
    }
    else if (curve.curveType == SL_XSD_CURVE_TYPE_FREQ_WATT)
    {
        enqueue_2(SSP_3_READ_711_SF);
        enqueue_2(SSP_3_WRITE_711_CURVE_DATA);
        enqueue_2(SSP_3_WRITE_711_CURVE_VERIFY_REQ);
        enqueue_2(SSP_3_READ_711_CURVE_VERIFY_RESP);
        enqueue_2(SSP_3_WRITE_711_CURVE_ENABLE);
    }
    else
    {
        // do nothing
    }
}

void get_communication_status()
{
    if (recv_buf[0])
    {
        if (comm_status_override == false)
        {
            comm_status = true;
        }
        if (server_status_override == false)
        {
            if (server_status != 1)
            {
                server_status = 1;
            }
        }
    }
    else 
    {
        if (comm_status_override == false)
        {
            comm_status = false;
        }
    }
}

void process_protocol_message(int message_type)
{
    switch (message_type)
    {
    case CAN2SEP_DER_SETTINGS_T_ID:
        get_data_der_settings();
        break;

    case CAN2SEP_DER_DEFAULT_DERC_T_ID:
        get_default_der_data();
        break;

    case CAN2SEP_FREQ_DROOP_T_ID:
        get_freq_droop_data();
        break;

    case CAN2SEP_DER_CURVE_T_ID:
        get_curve_data();
        break;

    case CAN2SEP_DER_DERC_IND_T_ID:
        get_derc_ind_data();
        break;
  
    case CAN2SEP_EVSE_COMMUNICATION_STATUS_ID:
        get_communication_status();
        break; 


    default:
        break;
    }
}

void send_message(char *tmp_send_buf, int tmp_send_buf_len, uint32_t message_type)
{
    int sent_len = -1;
    uint32_t send_len = (uint32_t)(tmp_send_buf_len + 8);
    int ii;
    // debug
    printf("proto: in send message: msg len %d\n", send_len);
    memset(send_buf, 0, 2048);
    memcpy(send_buf, &send_len, 4);

    memcpy(&send_buf[4], &message_type, 4);
    memcpy(&send_buf[8], tmp_send_buf, tmp_send_buf_len);
    sent_len = usock_write_message(send_buf, send_len);
    printf("sent message type %d, %d bytes\n", message_type, sent_len);
    sent_on_usock = sent_len;
    // // debug
    // fprintf(stdout, "[send buf]: \n");
    // for (ii=0; ii < 16; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", tmp_send_buf[ii]);    
    // }
    // fprintf(stdout, "\n");
    // for (ii=16; ii < 32; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", tmp_send_buf[ii]);    
    // }
    // fprintf(stdout, "\n");
    // for (ii=32; ii < 48; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", tmp_send_buf[ii]);    
    // }
    // fprintf(stdout, "\n");
    // fprintf(stdout, "[copy buf]: \n");
    // for (ii=0; ii < 16; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", send_buf[8+ii]);    
    // }
    // fprintf(stdout, "\n");
    // for (ii=16; ii < 32; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", send_buf[8+ii] );    
    // }
    // fprintf(stdout, "\n");
    // for (ii=32; ii < 48; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", send_buf[8+ii] );    
    // }
    // fprintf(stdout, "\n");
    // // debug
    // writeToFile(&send_buf[8], tmp_send_buf_len);

    // console_log("sent %d bytes", sent_len);
}

/* TODO: Process packets in proc_buf, data
  process both complete and incomplete packets. If complete packets recvd,
  proc_buf_len is 0, else it contains the previous remaining data
  after processing copy to the pipe buffer
*/
void processPackets()
{
    int bytesProcessed = 0;
    uint32_t proto_message_type = 0;

    while (bytesProcessed < proc_buf_len) {
        if (proc_buf_len - bytesProcessed < 8) {
            // Insufficient data for tag and length
            break;
        }

        int t_length = bytesToInt(proc_buf, bytesProcessed);
        // int t_tag = bytesToInt(proc_buf, bytesProcessed + 4);
       
        if (proc_buf_len - bytesProcessed < t_length) {
            // Incomplete packet
            break;
        }

        memcpy(recv_buf, &proc_buf[bytesProcessed+8] , t_length-8);
        recv_buf_len = t_length-8;

        // Process the complete packet
        memcpy(&proto_message_type, &proc_buf[bytesProcessed+4], 4);
        fprintf(stdout, "-------\n packet type = %02x\n ---------\n", proto_message_type);

        process_protocol_message(proto_message_type);

        // Update the bytes processed
        bytesProcessed += t_length;
        printf("bytesProc = %d, t_len = %d, proc buf len = %d\n", bytesProcessed, t_length, proc_buf_len);
    }

    if (bytesProcessed < proc_buf_len) {
        // copy the last incomplete packet to the beginning of recv_buf
        // processIncompletePackets(buffer + bytesProcessed, proc_buf_len - bytesProcessed);
        recv_buf_len = proc_buf_len - bytesProcessed;
        memcpy(recv_buf, proc_buf + bytesProcessed, recv_buf_len);
        memcpy(proc_buf, recv_buf, recv_buf_len);
        proc_buf_len = recv_buf_len;
    }
    else 
    {
        proc_buf_len = 0;
    }
}

void process_recv_message(char *rd_buf, int rd_buf_len)
{
  memcpy(&proc_buf[proc_buf_len], rd_buf, rd_buf_len);
  proc_buf_len += rd_buf_len;

  processPackets();

}


void process_recv_message_old(char *rd_buf, int rd_buf_len)
{
    // return the type of message received, and copy the contents of the message into recv_buf
    uint32_t proto_message_len = 0;
    uint32_t proto_message_type = 0;
    // debug
    printf("start of processing message \n");
    memcpy(&proto_message_len, rd_buf, 4);
    // debug
    printf("rd length of packet = %d\n", proto_message_len);
    printf("length of packet arg = %d\n", rd_buf_len);
    memcpy(&proto_message_type, &rd_buf[4], 4);
    printf("-------\n packet type = %02x\n ---------\n", proto_message_type);
    if (proto_message_len <= 8)
    {
        printf("insufficient message packet recvd: lenght recvd: %d\n", proto_message_len);
        // console_log("insufficient message packet recvd: lenght recvd: %d\n", proto_message_len);
        return;
    }
    if (proto_message_len == rd_buf_len)
    {
        // debug
        printf("copying data to recv buf\n");
        memcpy(recv_buf, (void *)&rd_buf[8], rd_buf_len - 8);
        // console_log("recvd msg type %02x\n", proto_message_type);
        process_protocol_message(proto_message_type);
    }
    else
    {
        printf("recvd msg type %02x, incomplete message\n", proto_message_type);
        // console_log("recvd msg type %02x, incomplete message\n", proto_message_type);
        return; // UNKNOWN message type since incomplete message
    }
    //return 1;
}

void send_dercapability_ind()
{
    u32_t tmp_u32;
    sl_eder_client_send_dercap_req dercap_req = {0};
    tmp_u32 = 0;
    if ((ctrl_modes_702 & 0x01) == 0x01)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 20);
    }
    if ((ctrl_modes_702 & 0x02) == 0x02)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 7);
    }
    if ((ctrl_modes_702 & 0x04) == 0x04)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 6);
    }
    if ((ctrl_modes_702 & 0x08) == 0x08)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 4);
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 5);
    }
    if ((ctrl_modes_702 & 16) == 16)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 23);
    }
    if ((ctrl_modes_702 & 32) == 32)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 9);
    }
    // if ( (ctrl_modes_702 & 64) == 64) {
    //     //no conversion for DYN_REACT_CURR of SUNSPEC;
    // }
    if ((ctrl_modes_702 & 128) == 128)
    {
        // LV_TRIP (ssPEC) MAPPed to LVRT_MUSTtRIP (2030.5)
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 19);
    }
    if ((ctrl_modes_702 & 256) == 256)
    {
        // HV_TRIP (SSpEC) mapped to HVRT_MUSTTRIP (2030.5)
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 14);
    }
    if ((ctrl_modes_702 & 512) == 512)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 26);
    }
    if ((ctrl_modes_702 & 1024) == 1024)
    {
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 24);
    }
    if ((ctrl_modes_702 & 2048) == 2048)
    {
        // Scheduled (SSpec) mapped to charge/discharge (2030.5)
        tmp_u32 = (u32_t)(tmp_u32 + 4 + 1);
    }
    if ((ctrl_modes_702 & 4096) == 4096)
    {
        // LF_TRIP (SSpec) mapped to LFRT_MUSTTRIP (2030.5)
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 16);
    }
    if ((ctrl_modes_702 & 8192) == 8192)
    {
        // HF_TRIP (SSpec) mapped to HFRT_MUSTTRIP (2030.5)
        tmp_u32 = tmp_u32 + (uint32_t)(1 << 11);
    }
    sep2_conv_ctrl_modes_702 = tmp_u32;
    dercap_req.dercap.modesSupported = tmp_u32;
    dercap_req.dercap.rtgMaxWValue = w_max_rtg_702;
    dercap_req.dercap.rtgMaxWMultiplier = w_sf_702;
    dercap_req.dercap.rtgAbnormalCategoryExists = 1;
    dercap_req.dercap.rtgAbnormalCategory = abn_op_cat_rtg_702 + 1;
    dercap_req.dercap.rtgNormalCategoryExists = 1;
    dercap_req.dercap.rtgNormalCategory = nor_op_cat_rtg_702 + 1;
    dercap_req.dercap.rtgOverExcitedPFExists = 1;
    dercap_req.dercap.rtgOverExcitedPFDisplacement = w_ovr_ext_rtg_pf_702;
    dercap_req.dercap.rtgOverExcitedPFMultiplier = pf_sf_702;
    dercap_req.dercap.rtgOverExcitedWExists = 1;
    dercap_req.dercap.rtgOverExcitedWValue = w_ovr_ext_rtg_702;
    dercap_req.dercap.rtgOverExcitedWMultiplier = w_sf_702;
    dercap_req.dercap.rtgReactiveSusceptanceExists = 1;
    dercap_req.dercap.rtgReactiveSusceptanceValue = react_suscept_rtg_702;
    dercap_req.dercap.rtgReactiveSusceptanceMultiplier = s_sf_702;
    dercap_req.dercap.rtgUnderExcitedPFExists = 1;
    dercap_req.dercap.rtgUnderExcitedPFDisplacement = w_und_ext_rtg_pf_702;
    dercap_req.dercap.rtgUnderExcitedPFMultiplier = pf_sf_702;
    dercap_req.dercap.rtgUnderExcitedWExists = 1;
    dercap_req.dercap.rtgUnderExcitedWValue = w_und_ext_rtg_702;
    dercap_req.dercap.rtgUnderExcitedWMultiplier = w_sf_702;
    data_4_send_buf_len = sizeof(dercap_req);
    memcpy(data_4_send_buf, &dercap_req, send_buf_len);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_EDER_CLIENT_SEND_DERCAP_REQ);
}

void send_dersettings_req()
{
    sl_eder_client_send_dersett_req dersett_req = {0};
    dersett_req.dersett.setModesEnabledExists = 1;
    dersett_req.dersett.setModesEnabled = sep2_conv_ctrl_modes_702;
    dersett_req.dersett.setESDelayExists = 1;
    dersett_req.dersett.setESDelay = ESDlyTms;
    dersett_req.dersett.setESHighFreqExists = 1;
    // hz_sf_703 == -2, so simply set it
    dersett_req.dersett.setESHighFreq = ESHzHi;
    dersett_req.dersett.setESHighVoltExists = 1;
    // v_sf_703 == -3, so multiply by 10 to give -2 for sep2
    // TODO: convert to % look at sl_api documentation
    dersett_req.dersett.setESHighVolt = (u16_t)(ESVHi / 10.0);
    dersett_req.dersett.setESLowFreqExists = 1;
    // hz_sf_703 == -2, so simply set it
    dersett_req.dersett.setESLowFreq = ESHzLo;
    dersett_req.dersett.setESLowVoltExists = 1;
    // v_sf_703 == -3, so multiply by 10 to give -2 for sep2
    // TODO: convert to % look at sl_api documentation
    dersett_req.dersett.setESLowVolt = (u16_t)(ESVLo / 10.0);
    dersett_req.dersett.setESRampTmsExists = 1;
    dersett_req.dersett.setESRampTms = ESRmpTms;
    dersett_req.dersett.setESRandomDelayExists = 1;
    dersett_req.dersett.setESRandomDelay = 0;
    dersett_req.dersett.setMaxChargeRateVAExists = 1;
    dersett_req.dersett.setMaxChargeRateVAValue = vacha_rte_max_702;
    dersett_req.dersett.setMaxChargeRateVAMultiplier = va_sf_702;
    dersett_req.dersett.setMaxChargeRateWExists = 1;
    dersett_req.dersett.setMaxChargeRateWValue = wcha_rte_max_702;
    dersett_req.dersett.setMaxChargeRateWMultiplier = w_sf_702;

    dersett_req.dersett.setMaxDischargeRateVAExists = 1;
    dersett_req.dersett.setMaxDischargeRateVAValue = vacha_rte_max_702;
    dersett_req.dersett.setMaxDischargeRateVAMultiplier = va_sf_702;
    dersett_req.dersett.setMaxDischargeRateWExists = 1;
    dersett_req.dersett.setMaxDischargeRateWValue = wcha_rte_max_702;
    dersett_req.dersett.setMaxDischargeRateWMultiplier = w_sf_702;

    dersett_req.dersett.setMaxVExists = 1;
    dersett_req.dersett.setMaxVValue = vmax_702;
    dersett_req.dersett.setMaxVMultiplier = v_sf_702;

    dersett_req.dersett.setMaxVAExists = 1;
    dersett_req.dersett.setMaxVAValue = vamax_702;
    dersett_req.dersett.setMaxVAMultiplier = v_sf_702;

    dersett_req.dersett.setMaxVarExists = 1;
    dersett_req.dersett.setMaxVarValue = var_max_inj_702;
    dersett_req.dersett.setMaxVAMultiplier = var_sf_702;

    dersett_req.dersett.setMaxVarNegativeExists = 1;
    dersett_req.dersett.setMaxVarNegativeValue = var_max_abs_702;
    dersett_req.dersett.setMaxVarNegativeMultiplier = var_sf_702;

    // dersett_req.dersett.setMaxWExists = 1;
    dersett_req.dersett.setMaxWValue = wmax_702;
    dersett_req.dersett.setMaxWMultiplier = w_sf_702;

    dersett_req.dersett.setMinVExists = 1;
    dersett_req.dersett.setMinVValue = vmin_702;
    dersett_req.dersett.setMinVMultiplier = v_sf_702;

    dersett_req.dersett.setVNomExists = 1;
    dersett_req.dersett.setVNomValue = vnom_702;
    dersett_req.dersett.setVNomMultiplier = v_sf_702;

    dersett_req.dersett.setVRefExists = 1;
    dersett_req.dersett.setVRefValue = vnom_702;
    dersett_req.dersett.setVRefMultiplier = v_sf_702;

    dersett_req.dersett.setMaxWhExists = 1;
    dersett_req.dersett.setMaxWhValue = max_Wh;
    dersett_req.dersett.setMaxWhMultiplier = 0;

    data_4_send_buf_len = sizeof(dersett_req);
    memcpy(data_4_send_buf, &dersett_req, data_4_send_buf_len);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_EDER_CLIENT_SEND_DERSETT_REQ);
}

void send_deviceinfo_req()
{
    int tmp_i;
    int tmp_i2;
    int tmp_len;
    int ii;
    sl_edinfo_client_send_dinfo_req dinfo_req = {0};
    dinfo_req.devInfo.mfDate = J3072_CERTIFIED_DATE;
    memcpy(dinfo_req.devInfo.mfHWVersion, "J3072 Certified", 15);
    memcpy(dinfo_req.devInfo.mfInfo, MANUFACTURER, MANUFACTURER_LEN);
    tmp_i = strlen(model_str_001);
    memcpy(dinfo_req.devInfo.mfModel, model_str_001, tmp_i);
    memcpy(dinfo_req.devInfo.mfSerialNum, VIN_NUM_MF_SERNUM, VIN_NUM_LEN);
    dinfo_req.devInfo.primaryPower = SL_XSD_POWER_SOURCE_BATTERY;
    dinfo_req.devInfo.secondaryPower = SL_XSD_POWER_SOURCE_LOCAL;
    dinfo_req.devInfo.swActivationTime = J3072_CERTIFIED_DATE + 10 * 24 * 60 * 60; // 10 DAYS from CERTIFIED DATE
    tmp_i = VERSION;
    tmp_i2 = hcp_sw_ver;
    tmp_len = snprintf(NULL, 0, "%d", tmp_i);
    ii = 0;
    snprintf(&dinfo_req.devInfo.swVersion[ii], tmp_len + 1, "%d", tmp_i);
    ii += tmp_len;
    dinfo_req.devInfo.swVersion[ii] = '_';
    ii += 1;
    tmp_len = strlen(version_str_001);
    memcpy(&dinfo_req.devInfo.swVersion[ii], version_str_001, tmp_len);
    ii += tmp_len;
    dinfo_req.devInfo.swVersion[ii] = '_';
    ii += 1;
    tmp_len = snprintf(NULL, 0, "%d", tmp_i2);
    snprintf(&dinfo_req.devInfo.swVersion[ii], tmp_len + 1, "%d", tmp_i2);
    ii += tmp_len;

    data_4_send_buf_len = sizeof(dinfo_req);
    memcpy(data_4_send_buf, &dinfo_req, data_4_send_buf_len);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_EDINFO_CLIENT_SEND_DINFO_REQ);
}

// void send_mup_setup_req() {
//     sl_meter_mirror_client_send_mup_req mup_req = {0};
//     mup_req.numMeterReadingGroups = 0; // TODO: CHECK that this would work without specifiying any value for mrGroup[]

//     //mup_req.mrId: TODO: setup mrID in the 2030.5 EVCC client app
//     //mup_req.deviceLFDI : TODO: setup deviceLFDI in 2030.5 client app
//     memcpy(mup_req.description, "PEV V2G DEMO DATA", 17);
//     mup_req.roleFlags = 0x04;
//     mup_req.serviceCategory = SL_XSD_SERVICE_ELECTRICITY;
//     mup_req.status = SL_XSD_STATUS_ON;

//     data_4_send_buf_len = sizeof(mup_req);
//     memcpy(data_4_send_buf, &mup_req, data_4_send_buf_len);
//     send_message(data_4_send_buf, data_4_send_buf_len, (u32_t) SL_METER_MIRROR_CLIENT_SEND_MUP_REQ);
// }

void writeToFile(char * wr_buf, int wr_buf_len)
{
    int f = open("/tmp/write_mup_bytes.dat", O_RDWR | O_CREAT);
    if (f == -1) {
        perror("mup data wr open failed");
        exit(1);
    }

    int written = write(f, wr_buf, wr_buf_len);
    if (written == -1) {
        perror("write failed");
        close(f);
        exit(1);
    } else if (written != wr_buf_len) {
        fprintf(stderr, "wrote %d bytes, expected %d\n", written, wr_buf_len);
    }
    printf("mup buf sz %d, wrote %d bytes to file %s\n", wr_buf_len, written, "/tmp/write_mup_bytes.dat");
    close(f);

}

void send_mup_req()
{
    int descLen;
    int ii;
    // SL_METER_MIRROR_CLIENT_SEND_MUP_REQ
    //  TODO: FILL UP MRID OF mup and mrGroup[0], and LFDI IN SEP2 APP
    sl_meter_mirror_client_send_mup_req *pmup_req;
    int length = sizeof(sl_meter_mirror_client_send_mup_req) + 1*sizeof(sl_mr_group_t);
    pmup_req = malloc(length);
    if (pmup_req == NULL) 
    {
        printf("error alloc memory for mup request\n");
        perror("mem_alloc:");
        printf("failed to allocate Memory for MUP Request, unable to send MUP Request to EVCC\n");
        return;
    }    
    descLen = strlen(DEFAULT_MMR_DESCRIPTION);
    if (descLen >= SL_XSD_DESCRIPTION_LEN)
    descLen = SL_XSD_DESCRIPTION_LEN - 1;
    strncpy(pmup_req->mrGroup[0].description, DEFAULT_MMR_DESCRIPTION, descLen);

    pmup_req->roleFlags = SL_XSD_ROLE_FLAG_PEV_MASK;
    pmup_req->serviceCategory = SL_XSD_SERVICE_ELECTRICITY;
    pmup_req->status = SL_XSD_STATUS_ON;
    pmup_req->numMeterReadingGroups = 1;

    // Readings and Reading sets are not included in the MUP
    pmup_req->mrGroup[0].numReadingSets = 0;
    pmup_req->mrGroup[0].readingExists  = false;

    pmup_req->mrGroup[0].rtypeExists = true;
    pmup_req->mrGroup[0].rtype.accumulationBehaviour = SL_XSD_AB_INSTANTANEOUS;
    pmup_req->mrGroup[0].rtype.flowDirection = SL_XSD_FLOW_DIR_FORWARD; // or SL_XSD_FLOW_DIR_REVERSE
    pmup_req->mrGroup[0].rtype.phaseCode = actype_sep2;
    pmup_req->mrGroup[0].rtype.powerOfTenMultiplier = SL_XSD_PTM_NONE;
    pmup_req->mrGroup[0].rtype.uomType = SL_XSD_UOM_WATT;
    pmup_req->mrGroup[0].rtype.kindType = SL_XSD_KIND_POWER;

    data_4_send_buf_len = length;
    memcpy(data_4_send_buf, pmup_req, data_4_send_buf_len);

    // // debug
    // fprintf(stdout, "[send mup req buf]: \n");
    // for (ii=0; ii < 16; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", data_4_send_buf[ii]);    
    // }
    // fprintf(stdout, "\n");
    // for (ii=16; ii < 32; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", data_4_send_buf[ii]);    
    // }
    // fprintf(stdout, "\n");
    // for (ii=32; ii < 48; ii++)
    // {
    //     fprintf(stdout, " 0x%02x", data_4_send_buf[ii]);    
    // }
    // fprintf(stdout, "\n");


    if (pmup_req != NULL)
    {
        free(pmup_req);
    }
    // debug
    // fprintf(stdout, "just before sending numMeter Reading groups %d\n", pmup_req->numMeterReadingGroups);
    // fprintf(stdout, "just before sending rtypeExists %d\n", pmup_req->mrGroup[0].rtypeExists);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_METER_MIRROR_CLIENT_SEND_MUP_REQ);
}

void send_mmr_setup_or_data(int typeof_req, bool sendReading)
{
    // if sendReading is true, values are included else it is a setup request
    u16_t length;
    u8_t descLen;
    // typeof_req == 1 (Active Power)
    // typeof_req == 2 (Reactive Power)
    // typeof_req == 3 (Voltage)
    // typeof_req == 4 (Freqency)
    // any other value do nothing

    // in SEP2 app, look at the value of mrGroup[0].description to figure what this MMR represents
    if ((typeof_req < 1) || (typeof_req > 4))
    {
        return;
    }

    sl_meter_mirror_client_send_mmr_req *pmmr_req = {0};
    length = sizeof(sl_meter_mirror_client_send_mmr_req) + DEFAULT_MMR_NUM_MR_GROUPS*sizeof(sl_mr_group_t);
    pmmr_req = malloc(length);
    memset(pmmr_req, 0, length);

    pmmr_req->numMeterReadingGroups = DEFAULT_MMR_NUM_MR_GROUPS;

    if (sendReading)
    {
        pmmr_req->mrGroup[0].readingExists = 1;
        pmmr_req->mrGroup[0].reading.duration = 0;
        pmmr_req->mrGroup[0].reading.start = (i64_t)getCurrentTime();

    }

    switch (typeof_req)
    {
    case 1:
        // Copy description field
        descLen = strlen(DEFAULT_ACTIVEPOWER_DESCRIPTION);
        if (descLen >= SL_XSD_DESCRIPTION_LEN)
        descLen = SL_XSD_DESCRIPTION_LEN - 1;
        strncpy(pmmr_req->mrGroup[0].description, DEFAULT_ACTIVEPOWER_DESCRIPTION, descLen);

        defaultRtype.accumulationBehaviour = SL_XSD_AB_INSTANTANEOUS;
        defaultRtype.flowDirection = SL_XSD_FLOW_DIR_FORWARD; // or SL_XSD_FLOW_DIR_REVERSE
        defaultRtype.phaseCode = actype_sep2;
        defaultRtype.powerOfTenMultiplier = SL_XSD_PTM_NONE;
        defaultRtype.uomType = SL_XSD_UOM_WATT;

        if (sendReading)
        {
            pmmr_req->mrGroup[0].reading.valueExists = true;
            pmmr_req->mrGroup[0].reading.value = activepower_701_rep * pow(10, activepower_sf_701);
        }

        break;

    case 2:
        // Copy description field
        descLen = strlen(DEFAULT_REACTIVEPOWER_DESCRIPTION);
        if (descLen >= SL_XSD_DESCRIPTION_LEN)
        descLen = SL_XSD_DESCRIPTION_LEN - 1;
        strncpy(pmmr_req->mrGroup[0].description, DEFAULT_REACTIVEPOWER_DESCRIPTION, descLen);

        defaultRtype.accumulationBehaviour = SL_XSD_AB_INSTANTANEOUS;
        defaultRtype.flowDirection = SL_XSD_FLOW_DIR_FORWARD; // or SL_XSD_FLOW_DIR_REVERSE
        defaultRtype.phaseCode = actype_sep2;
        defaultRtype.powerOfTenMultiplier = SL_XSD_PTM_NONE;
        defaultRtype.uomType = SL_XSD_UOM_REACT_POWER;

        if (sendReading)
        {
            pmmr_req->mrGroup[0].reading.valueExists = true;
            pmmr_req->mrGroup[0].reading.value = reactivepower_701_rep * pow(10, reactivepower_sf_701);
        }


        break;
    case 3:
        // Copy description field
        descLen = strlen(DEFAULT_VOLTAGE_DESCRIPTION);
        if (descLen >= SL_XSD_DESCRIPTION_LEN)
        descLen = SL_XSD_DESCRIPTION_LEN - 1;
        strncpy(pmmr_req->mrGroup[0].description, DEFAULT_VOLTAGE_DESCRIPTION, descLen);

        defaultRtype.accumulationBehaviour = SL_XSD_AB_INSTANTANEOUS;
        defaultRtype.flowDirection = SL_XSD_FLOW_DIR_FORWARD; // or SL_XSD_FLOW_DIR_REVERSE
        defaultRtype.phaseCode = actype_sep2;
        defaultRtype.powerOfTenMultiplier = SL_XSD_PTM_NONE;
        defaultRtype.uomType = SL_XSD_UOM_VOLT_SQ;
   
        if (sendReading)
        {
            pmmr_req->mrGroup[0].reading.valueExists = true;
            pmmr_req->mrGroup[0].reading.value = voltage_701_rep * pow(10, voltage_sf_701);
        }

        break;
    case 4:
        // Copy description field
        descLen = strlen(DEFAULT_FREQUENCY_DESCRIPTION);
        if (descLen >= SL_XSD_DESCRIPTION_LEN)
        descLen = SL_XSD_DESCRIPTION_LEN - 1;
        strncpy(pmmr_req->mrGroup[0].description, DEFAULT_FREQUENCY_DESCRIPTION, descLen);

        defaultRtype.accumulationBehaviour = SL_XSD_AB_INSTANTANEOUS;
        defaultRtype.flowDirection = SL_XSD_FLOW_DIR_FORWARD; // or SL_XSD_FLOW_DIR_REVERSE
        defaultRtype.phaseCode = actype_sep2;
        defaultRtype.powerOfTenMultiplier = SL_XSD_PTM_NONE;
        defaultRtype.uomType = SL_XSD_UOM_FREQ;

        if (sendReading)
        {
            pmmr_req->mrGroup[0].reading.valueExists = true;
            pmmr_req->mrGroup[0].reading.value = frequency_701_rep * pow(10, frequency_sf_701);
        }

        break;
    default:
        return;
    }

    // Reading sets are not included in these MMRs.
    pmmr_req->mrGroup[0].numReadingSets = 0;

    pmmr_req->mrGroup[0].rtypeExists = 1;
    memcpy(&pmmr_req->mrGroup[0].rtype, &defaultRtype, sizeof(sl_cmn_rt_t));

    data_4_send_buf_len = length;
    memcpy(data_4_send_buf, pmmr_req, data_4_send_buf_len);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_METER_MIRROR_CLIENT_SEND_MMR_REQ);

    if (pmmr_req != NULL)
    {
        free(pmmr_req);
    }
}

// void send_mmr_data(int typeof_req)
// {
//     // typeof_req == 1 (Active Power)
//     // typeof_req == 2 (Reactive Power)
//     // typeof_req == 3 (Voltage)
//     // typeof_req == 4 (Freqency)
//     // any other value do nothing

//     // in SEP2 app, look at the value of mrGroup[0].description to figure what this MMR represents
//     if ((typeof_req < 1) || (typeof_req > 4))
//     {
//         return;
//     }
//     sl_meter_mirror_client_send_mmr_req mmr_req = {0};
//     mmr_req.numMeterReadingGroups = 1;
//     mmr_req.mrGroup[0].readingExists = 1;
//     mmr_req.mrGroup[0].reading.duration = 0;
//     mmr_req.mrGroup[0].reading.start = (i64_t)getCurrentTime();

//     switch (typeof_req)
//     {
//     case 1:
//         memcpy(mmr_req.mrGroup[0].description, "Active Power", 12);
//         mmr_req.mrGroup[0].reading.value = activepower_701_rep * pow(10, activepower_sf_701);
//         break;
//     case 2:
//         memcpy(mmr_req.mrGroup[0].description, "Reactive Power", 14);
//         mmr_req.mrGroup[0].reading.value = reactivepower_701_rep * pow(10, reactivepower_sf_701);
//         break;
//     case 3:
//         memcpy(mmr_req.mrGroup[0].description, "Voltage", 7);
//         mmr_req.mrGroup[0].reading.value = voltage_701_rep * pow(10, voltage_sf_701);
//         break;
//     case 4:
//         memcpy(mmr_req.mrGroup[0].description, "Frequency", 9);
//         mmr_req.mrGroup[0].reading.value = frequency_701_rep * pow(10, frequency_sf_701);
//         break;
//     default:
//         return;
//     }

//     data_4_send_buf_len = sizeof(mmr_req);
//     memcpy(data_4_send_buf, &mmr_req, data_4_send_buf_len);
//     send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_METER_MIRROR_CLIENT_SEND_MMR_REQ);
// }

void send_power_status_req()
{
    // SL_EPWRSTAT_CLIENT_SEND_PS_REQ
    sl_epwrstat_client_send_ps_req ps_req = {0};
    ps_req.pwrstat.batteryStatus = battery_status;
    ps_req.pwrstat.changedTime = (i64_t)changed_time;
    ps_req.pwrstat.currentPowerSource = current_power_source;
    ps_req.pwrstat.estChargeRemainingExists = true;
    ps_req.pwrstat.estChargeRemaining = estimated_charge_remaining;
    ps_req.pwrstat.pevInfoExists = true;
    ps_req.pwrstat.pevInfo.chargingPowerNow.value = obc_current_charging_pwr_w;
    ps_req.pwrstat.pevInfo.chargingPowerNow.mult = SL_XSD_PTM_NONE;
    ps_req.pwrstat.pevInfo.energyRequestNow.value = energy_request_now_Wh;
    ps_req.pwrstat.pevInfo.energyRequestNow.mult = SL_XSD_PTM_NONE;
    ps_req.pwrstat.pevInfo.maxForwardPower.value = obc_max_fwd_pwr_w;
    ps_req.pwrstat.pevInfo.maxForwardPower.mult = SL_XSD_PTM_NONE;
    ps_req.pwrstat.pevInfo.minimumChargingDuration = minimum_charging_duration_secs;
    ps_req.pwrstat.pevInfo.targetStateOfCharge = target_soc;
    ps_req.pwrstat.pevInfo.timeChargeIsNeeded = (i64_t)time_charge_is_neeeded_duration_secs;
    ps_req.pwrstat.pevInfo.timeChargingStatusPEV = (i64_t)changed_time;

    data_4_send_buf_len = sizeof(ps_req);
    memcpy(data_4_send_buf, &ps_req, data_4_send_buf_len);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_EPWRSTAT_CLIENT_SEND_PS_REQ);
}

void send_der_availabilit_req()
{
    // SL_EDER_CLIENT_SEND_DERA_REQ
    sl_eder_client_send_dera_req dera_req = {0};
    dera_req.dera.availabilityDurationExists = true;
    dera_req.dera.availabilityDuration = (u32_t)availability_duration_secs;
    dera_req.dera.maxChargeDurationExists = true;
    dera_req.dera.maxChargeDuration = (u32_t)max_charge_duration_secs;
    dera_req.dera.readingTime = (i64_t)reading_time;
    dera_req.dera.reserveChargePercentExists = true;
    dera_req.dera.reserveChargePercent = (u16_t)reserve_charge_percent;
    dera_req.dera.reservePercentExists = true;
    dera_req.dera.reservePercent = (u16_t)reserve_percent;

    data_4_send_buf_len = sizeof(dera_req);
    memcpy(data_4_send_buf, &dera_req, data_4_send_buf_len);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_EDER_CLIENT_SEND_DERA_REQ);
}

void send_der_status_req() 
{
    // SL_EDER_CLIENT_SEND_DERS_REQ
    sl_eder_client_send_ders_req ders_req = {0};
    ders_req.ders.genConnectStatusExists = true;
    ders_req.ders.genConnectStatusValue = conn_status_701;
    ders_req.ders.genConnectStatusDateTime = status_time_701;
    ders_req.ders.inverterStatusExists = true;
    ders_req.ders.inverterStatusValue = inv_status_701 + 1; // to map sunspec values to SEP2 values
    ders_req.ders.inverterStatusDateTime = status_time_701;
    ders_req.ders.operationalModeStatusExists = true;
    ders_req.ders.operationalModeStatusValue = status_701 + 1; // to map sunspec values to SEP2 value
    ders_req.ders.stateOfChargeStatusExists = true;
    ders_req.ders.stateOfChargeStatusValue = (u16_t)(current_soc);
    ders_req.ders.stateOfChargeStatusDateTime = (i64_t)changed_time;
    ders_req.ders.readingTime = (i64_t)changed_time;

    data_4_send_buf_len = sizeof(ders_req);
    memcpy(data_4_send_buf, &ders_req, data_4_send_buf_len);
    send_message(data_4_send_buf, data_4_send_buf_len, (u32_t)SL_EDER_CLIENT_SEND_DERS_REQ);
}

void test_server_send_dera_ind()
{
    sl_eder_server_dera_ind tmp_dera_ind = {0};
    char buf_wr[2048];
    int buf_wr_len = 0;
    tmp_dera_ind.deraExists = 1;
    tmp_dera_ind.dera.availabilityDurationExists = 1;
    tmp_dera_ind.dera.availabilityDuration = 4800;
    tmp_dera_ind.dera.maxChargeDurationExists = 1;
    tmp_dera_ind.dera.maxChargeDuration = 4 * 60;
    buf_wr_len = sizeof(tmp_dera_ind);
    memcpy(buf_wr, &tmp_dera_ind, buf_wr_len);
    send_message(buf_wr, buf_wr_len, (u32_t)SL_EDER_SERVER_DERA_IND);
}

void test_client_send_derc_ind()
{
    sl_der_client_derc_ind tmp_derc_ind = {0};
    char buf_wr[2048];
    int buf_wr_len = 0;
    tmp_derc_ind.derpMrId[0] = 'a';
    tmp_derc_ind.derpMrId[1] = 'b';
    tmp_derc_ind.derpMrId[2] = 'c';
    tmp_derc_ind.derpMrId[3] = 'd';
    tmp_derc_ind.derpMrId[4] = 'e';
    tmp_derc_ind.derpMrId[5] = 'f';
    tmp_derc_ind.derpMrId[6] = '0';
    tmp_derc_ind.derpMrId[7] = '1';
    tmp_derc_ind.derpMrId[8] = '2';
    tmp_derc_ind.derpMrId[9] = '3';
    tmp_derc_ind.derpMrId[10] = '4';
    tmp_derc_ind.derpMrId[11] = '5';
    tmp_derc_ind.derpMrId[12] = '6';
    tmp_derc_ind.derpMrId[13] = '7';
    tmp_derc_ind.derpMrId[14] = '8';
    tmp_derc_ind.derpMrId[15] = '9';
    tmp_derc_ind.derc.dercBase.rampTmsExists = 0;
    tmp_derc_ind.derc.dercBase.rampTms = 7623;
    buf_wr_len = sizeof(tmp_derc_ind);
    memcpy(buf_wr, &tmp_derc_ind, buf_wr_len);
    send_message(buf_wr, buf_wr_len, (u32_t)SL_DER_CLIENT_DERC_IND);
}

static int test_ev_params_post_succ = 0;
void test_ev_params_post_usock()
{
    fprintf(stdout, "in test ev params post usock func sts = %d\n", test_ev_params_post_succ);
    if (!test_ev_params_post_succ)
    {
        fprintf(stdout, "sending dera \n");
        sent_on_usock = -1;
        availability_duration_secs = 1440;
        max_charge_duration_secs = 1425;
        reading_time = 12345;
        reserve_charge_percent = 20;
        reserve_percent =  5;
        send_der_availabilit_req();
        if (sent_on_usock > 0)
        {
            test_ev_params_post_succ = 1;
        }
        else 
        {
            test_ev_params_post_succ = 0;
            return;
        }
        sleep(5);
        send_power_status_req();
        sleep(5);
        send_der_status_req();

    }
}

static int test_mirror_mup_setup = 0;
static int test_mirror_mmr_setup = 0;
void test_mirror_usock()
{
    if (!test_mirror_mup_setup)
    {
        sent_on_usock = -1;
        send_mup_req();
        if (sent_on_usock > 0)
        {
            test_mirror_mup_setup = 1;
        }
        return;
    }
    if (!test_mirror_mmr_setup)
    {
        sent_on_usock = -1;
        send_mmr_setup_or_data(1, false);
        if (sent_on_usock <= 0)
            return;
        sleep(5);
        sent_on_usock = -1;
        send_mmr_setup_or_data(2, false);
        if (sent_on_usock <= 0)
            return;
        sleep(5);
        sent_on_usock = -1;
        send_mmr_setup_or_data(3, false);
        if (sent_on_usock <= 0)
            return;
        sleep(5);
        sent_on_usock = -1;
        send_mmr_setup_or_data(4, false);
        if (sent_on_usock > 0)
        {
            test_mirror_mmr_setup = 1;
        }
        return;
    }

    activepower_701_rep = 4;
    send_mmr_setup_or_data(1, true);
    sleep(5);
    reactivepower_701_rep = 3;
    send_mmr_setup_or_data(2, true);
    sleep(5);
    voltage_701_rep = 108;
    send_mmr_setup_or_data(3, true);
    sleep(5);
    frequency_701_rep = 62;
    send_mmr_setup_or_data(4, true);
}