/** \file sl_api.h
 *
 * <p>KITU SYSTEMS SMART ENERGY 2
 *
 * <p>Copyright (C) 2020 Kitu Systems, Inc. All rights reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of Kitu Systems, Inc and is confidential in nature.
 *
 * \brief Services Layer public header file
 *
 * \section info  Change Information
 *
 * \verbatim
   $History: $
   \endverbatim
 */

#ifndef SL_API_H
#define SL_API_H

#include "psal_types.h"
#include <stdbool.h>

/*******************************************************************************
 * Mail Ids
 ******************************************************************************/
/**
 * \defgroup MAIL_IDS Mail Messages and Associated IDs
 * Defines the list of mail messages that are supported by the SL task and
 * their associated Mail IDs.
 * Note that the SL task must be configured for client and/or server support and
 * will only support the associated mail IDs. Please see the associated
 * structure for a definition of the use of each API and details on the
 * fields associated with it.
 * <P><b>Note: Mail ID values are subject to change. It is highly recommended that
 * code refer only to the defined names and not the values. Mail IDs currently
 * set to 0x00 have not yet had an ID assigned. </b>
 * \def SL_SERVER_OBJ_CREATE_REQ
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_create_derp_req         - objId=\ref SL_OBJ_ID_X_DERP_X\n
 *      sl_der_server_create_derc_req         - objId=\ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 *      sl_der_server_create_dc_req           - objId=\ref SL_OBJ_ID_X_DERP_X_DC_X\n
 *      sl_drlc_server_create_drp_req         - objId=\ref SL_OBJ_ID_X_DR_X\n
 *      sl_drlc_server_create_edc_req         - objId=\ref SL_OBJ_ID_X_DR_X_EDC_X\n
 *      sl_edev_server_create_enddev_req      - objId=\ref SL_OBJ_ID_X_EDEV_X\n
 *      sl_edev_server_store_enddev_req       - objId=\ref SL_OBJ_ID_X_EDEV_X\n
 *      sl_flow_server_create_res_resp_req    - objId=\ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 *      sl_fsa_server_create_fsa_req          - objId=\ref SL_OBJ_ID_X_FSA_X\n
 *      sl_meter_server_create_mr_req         - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X\n
 *      sl_meter_server_create_rset_req       - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 *      sl_meter_server_create_reading_req    - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 *      sl_meter_server_create_rtype_req      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_meter_server_create_up_req         - objId=\ref SL_OBJ_ID_X_UPT_X\n
 *      sl_msg_server_create_msgp_req         - objId=\ref SL_OBJ_ID_X_MSG_X\n
 *      sl_msg_server_create_txt_req          - objId=\ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 *      sl_price_server_create_tp_req         - objId=\ref SL_OBJ_ID_X_TP_X\n
 *      sl_price_server_create_rc_req         - objId=\ref SL_OBJ_ID_X_TP_X_RC_X\n
 *      sl_price_server_create_tti_req        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 *      sl_price_server_create_cti_req        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 *      sl_price_server_create_rtype_req      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_resp_server_create_resp_set_req    - objId=\ref SL_OBJ_ID_X_RSPS_X\n
 * \def SL_SERVER_OBJ_CANCEL_REQ
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_cancel_derc_req         - objId=\ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 *      sl_drlc_server_cancel_edc_req         - objId=\ref SL_OBJ_ID_X_DR_X_EDC_X\n
 *      sl_flow_server_cancel_res_resp_req    - objId=\ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 *      sl_msg_server_cancel_txt_req          - objId=\ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 *      sl_price_server_cancel_tti_req        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * \def SL_SERVER_OBJ_DELETE_REQ
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_delete_derp_req         - objId=\ref SL_OBJ_ID_X_DERP_X\n
 *      sl_der_server_delete_default_derc_req - objId=\ref SL_OBJ_ID_X_DERP_X_DDERC\n
 *      sl_der_server_delete_derc_req         - objId=\ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 *      sl_der_server_delete_dc_req           - objId=\ref SL_OBJ_ID_X_DERP_X_DC_X\n
 *      sl_drlc_server_delete_drp_req         - objId=\ref SL_OBJ_ID_X_DR_X\n
 *      sl_drlc_server_delete_edc_req         - objId=\ref SL_OBJ_ID_X_DR_X_EDC_X\n
 *      sl_edev_server_delete_enddev_req      - objId=\ref SL_OBJ_ID_X_EDEV_X\n
 *      sl_flow_server_delete_res_req_req     - objId=\ref SL_OBJ_ID_X_EDEV_X_FRQ_X\n
 *      sl_flow_server_delete_res_resp_req    - objId=\ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 *      sl_fsa_server_delete_fsa_req          - objId=\ref SL_OBJ_ID_X_FSA_X\n
 *      sl_meter_server_delete_mr_req         - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X\n
 *      sl_meter_server_delete_rset_req       - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 *      sl_meter_server_delete_reading_req    - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 *      sl_meter_server_delete_rtype_req      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_meter_server_delete_top_read_req   - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_R\n
 *      sl_meter_server_delete_up_req         - objId=\ref SL_OBJ_ID_X_UPT_X\n
 *      sl_msg_server_delete_msgp_req         - objId=\ref SL_OBJ_ID_X_MSG_X\n
 *      sl_msg_server_delete_txt_req          - objId=\ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 *      sl_price_server_delete_tp_req         - objId=\ref SL_OBJ_ID_X_TP_X\n
 *      sl_price_server_delete_rc_req         - objId=\ref SL_OBJ_ID_X_TP_X_RC_X\n
 *      sl_price_server_delete_tti_req        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 *      sl_price_server_delete_cti_req        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 *      sl_price_server_delete_rtype_req      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_resp_server_delete_resp_set_req    - objId=\ref SL_OBJ_ID_X_RSPS_X\n
 * \def SL_SERVER_OBJ_STORE_REQ
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_store_default_derc_req  - objId=\ref SL_OBJ_ID_X_DERP_X_DDERC\n
 *      sl_meter_server_store_mr_req          - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X\n
 *      sl_meter_server_store_reading_req     - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 *      sl_meter_server_store_rset_req        - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 *      sl_meter_server_store_top_read_req    - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_R\n
 *      sl_meter_server_store_up_req          - objId=\ref SL_OBJ_ID_X_UPT_X\n
 *      sl_meter_server_store_rtype_req       - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_price_server_store_rtype_req       - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_sdinfo_server_store_dinfo_req      - objId=\ref SL_OBJ_ID_X_SDEV_SDI\n
 * \def SL_SERVER_CONFIG_DSP_REQ
 *      This mail ID uses the sl_server_config_dsp_req structure.
 * \def SL_DER_CLIENT_GET_DERP_LIST_REQ
 *      This mail ID uses the sl_der_client_get_derp_list_req structure.
 * \def SL_DER_CLIENT_CANCEL_GET_DERP_LIST_REQ
 *      This mail ID uses the sl_der_client_cancel_get_derp_list_req structure.
 * \def SL_DER_CLIENT_GET_DERC_LIST_REQ
 *      This mail ID uses the sl_der_client_get_derc_list_req structure.
 * \def SL_DER_CLIENT_CANCEL_GET_DERC_LIST_REQ
 *      This mail ID uses the sl_der_client_cancel_get_derc_list_req structure.
 * \def SL_DER_CLIENT_GET_DC_LIST_REQ
 *      This mail ID uses the sl_der_client_get_dc_list_req structure.
 * \def SL_DER_CLIENT_CANCEL_GET_DC_LIST_REQ
 *      This mail ID uses the sl_der_client_cancel_get_dc_list_req structure.
 * \def SL_DER_CLIENT_SET_EVENT_ROOTS_REQ
 *      This mail ID uses the sl_der_client_set_event_roots_req structure.
 * \def SL_DER_CLIENT_SET_EVENT_POLL_RATE_REQ
 *      This mail ID uses the sl_der_client_set_event_poll_rate_req structure.
 * \def SL_DER_CLIENT_SET_EVENT_PROGRAMS_REQ
 *      This mail ID uses the sl_der_client_set_event_programs_req structure.
 * \def SL_DER_CLIENT_SET_DEVICE_TYPE_REQ
 *      This mail ID uses the sl_der_client_set_device_type_req structure.
 * \def SL_EDER_CLIENT_SEND_DERA_REQ
 *      This mail ID uses the sl_eder_client_send_dera_req structure.
 * \def SL_EDER_CLIENT_SEND_DERCAP_REQ
 *      This mail ID uses the sl_eder_client_send_dercap_req structure.
 * \def SL_EDER_CLIENT_SEND_DERS_REQ
 *      This mail ID uses the sl_eder_client_send_ders_req structure.
 * \def SL_EDER_CLIENT_SEND_DERSETT_REQ
 *      This mail ID uses the sl_eder_client_send_dersett_req structure.
 * \def SL_DRLC_CLIENT_GET_DRP_LIST_REQ
 *      This mail ID uses the sl_drlc_client_get_drp_list_req structure.
 * \def SL_DRLC_CLIENT_CANCEL_GET_DRP_LIST_REQ
 *      This mail ID uses the sl_drlc_client_cancel_get_drp_list_req structure.
 * \def SL_DRLC_CLIENT_GET_EDC_LIST_REQ
 *      This mail ID uses the sl_drlc_client_get_edc_list_req structure.
 * \def SL_DRLC_CLIENT_CANCEL_GET_EDC_LIST_REQ
 *      This mail ID uses the sl_drlc_client_cancel_get_edc_list_req structure.
 * \def SL_DRLC_CLIENT_OPT_OUT_EDC_REQ
 *      This mail ID uses the sl_drlc_client_opt_out_edc_req structure.
 * \def SL_DRLC_CLIENT_OPT_IN_EDC_REQ
 *      This mail ID uses the sl_drlc_client_opt_in_edc_req structure.
 * \def SL_DRLC_CLIENT_SET_EVENT_ROOTS_REQ
 *      This mail ID uses the sl_drlc_client_set_event_roots_req structure.
 * \def SL_DRLC_CLIENT_SET_EVENT_PROGRAMS_REQ
 *      This mail ID uses the sl_drlc_client_set_event_programs_req structure.
 * \def SL_DRLC_CLIENT_SET_EVENT_POLL_RATE_REQ
 *      This mail ID uses the sl_drlc_client_set_event_poll_rate_req structure.
 * \def SL_DRLC_CLIENT_SET_APPLIED_VALUES_REQ
 *      This mail ID uses the sl_drlc_client_set_applied_values_req structure.
 * \def SL_DRLC_CLIENT_SET_DEVICE_TYPE_REQ
 *      This mail ID uses the sl_drlc_client_set_device_type_req structure.
 * \def SL_EDEV_CLIENT_SEND_ENDDEV_REQ
 *      This mail ID uses the sl_edev_client_send_enddev_req structure.
 * \def SL_EDEV_CLIENT_SET_PIN_REQ
 *      This mail ID uses the sl_edev_client_set_pin_req structure.
 * \def SL_EDEV_CLIENT_GET_EDEV_LIST_REQ
 *      This mail ID uses the sl_edev_client_get_edev_list_req structure.
 * \def SL_EDEV_CLIENT_CANCEL_GET_EDEV_LIST_REQ
 *      This mail ID uses the sl_edev_client_cancel_get_edev_list_req structure.
 * \def SL_EDEV_CLIENT_FIND_SERVER_REQ
 *      This mail ID uses the sl_edev_client_find_server_req structure.
 * \def SL_EDEV_SERVER_POST_EDEV_PENDING_RSP
 *      This mail ID uses the sl_edev_server_post_edev_pending_rsp structure.
 * \def SL_EDINFO_CLIENT_SEND_DINFO_REQ
 *      This mail ID uses the sl_edinfo_client_send_dinfo_req structure.
 * \def SL_EPWRSTAT_CLIENT_SEND_PS_REQ
 *      This mail ID uses the sl_epwrstat_client_send_ps_req structure.
 * \def SL_EDSTAT_CLIENT_SEND_DSTAT_REQ
 *      This mail ID uses the sl_edstat_client_send_dstat_req structure.
 * \def SL_FLOW_CLIENT_CREATE_RES_REQUEST_REQ
 *      This mail ID uses the sl_flow_client_create_res_request_req structure.
 * \def SL_FLOW_CLIENT_CANCEL_RES_REQUEST_REQ
 *      This mail ID uses the sl_flow_client_cancel_res_request_req structure.
 * \def SL_FLOW_CLIENT_GET_RES_RESP_LIST_REQ
 *      This mail ID uses the sl_flow_client_get_res_resp_list_req structure.
 * \def SL_FLOW_CLIENT_CANCEL_GET_RES_RESP_LIST_REQ
 *      This mail ID uses the sl_flow_client_cancel_get_res_resp_list_req structure.
 * \def SL_FLOW_CLIENT_SET_EVENT_POLL_RATE_REQ
 *      This mail ID uses the sl_flow_client_set_event_poll_rate_req structure.
 * \def SL_METER_CLIENT_GET_UP_LIST_REQ
 *      This mail ID uses the sl_meter_client_get_up_list_req structure.
 * \def SL_METER_CLIENT_CANCEL_GET_UP_LIST_REQ
 *      This mail ID uses the sl_meter_client_cancel_get_up_list_req structure.
  * \def SL_METER_CLIENT_GET_MR_LIST_REQ
 *      This mail ID uses the sl_meter_client_get_mr_list_req structure.
 * \def SL_METER_CLIENT_CANCEL_GET_MR_LIST_REQ
 *      This mail ID uses the sl_meter_client_cancel_get_mr_list_req structure.
 * \def SL_METER_CLIENT_GET_RC_LIST_REQ
 *      This mail ID uses the sl_meter_client_get_rc_list_req structure.
 * \def SL_METER_CLIENT_CANCEL_GET_RC_LIST_REQ
 *      This mail ID uses the sl_meter_client_cancel_get_rc_list_req structure.
 * \def SL_METER_CLIENT_GET_RSET_LIST_REQ
 *      This mail ID uses the sl_meter_client_get_rset_list_req structure.
 * \def SL_METER_CLIENT_CANCEL_GET_RSET_LIST_REQ
 *      This mail ID uses the sl_meter_client_cancel_get_rset_list_req structure.
 * \def SL_METER_CLIENT_GET_READING_LIST_REQ
 *      This mail ID uses the sl_meter_client_get_reading_list_req structure.
 * \def SL_METER_CLIENT_CANCEL_GET_READING_LIST_REQ
 *      This mail ID uses the sl_meter_client_cancel_get_reading_list_req structure.
 * \def SL_METER_MIRROR_CLIENT_SEND_MUP_REQ
 *      This mail ID uses the sl_meter_mirror_client_send_mup_req structure.
 * \def SL_METER_MIRROR_CLIENT_SEND_MMR_REQ
 *      This mail ID uses the sl_meter_mirror_client_send_mmr_req structure.
 * \def SL_METER_MIRROR_CLIENT_GET_MUP_RATES_REQ
 *      This mail ID uses the sl_meter_mirror_client_get_mup_rates_req structure.
 * \def SL_METER_MIRROR_SERVER_CONFIG_CLIENT_FILTER_REQ
 *      This mail ID uses the sl_meter_mirror_server_config_client_filter_req structure.
 * \def SL_MSG_SERVER_DELETE_MSGP_REQ
 *      This mail ID uses the sl_msg_server_delete_msgp_req structure.
 * \def SL_MSG_CLIENT_GET_MSGP_LIST_REQ
 *      This mail ID uses the sl_msg_client_get_msgp_list_req structure.
 * \def SL_MSG_CLIENT_CANCEL_GET_MSGP_LIST_REQ
 *      This mail ID uses the sl_msg_client_cancel_get_msgp_list_req structure.
 * \def SL_MSG_CLIENT_GET_TXT_LIST_REQ
 *      This mail ID uses the sl_msg_client_get_txt_list_req structure.
 * \def SL_MSG_CLIENT_CANCEL_GET_TXT_LIST_REQ
 *      This mail ID uses the sl_msg_client_get_cancel_txt_list_req structure.
 * \def SL_MSG_CLIENT_SET_EVENT_ROOTS_REQ
 *      This mail ID uses the sl_msg_client_set_event_roots_req structure.
 * \def SL_MSG_CLIENT_SET_EVENT_PROGRAMS_REQ
 *      This mail ID uses the sl_msg_client_set_event_programs_req structure.
 * \def SL_MSG_CLIENT_SET_EVENT_POLL_RATE_REQ
 *      This mail ID uses the sl_msg_client_set_event_poll_rate_req structure.
 * \def SL_PRICE_CLIENT_GET_TP_LIST_REQ
 *      This mail ID uses the sl_price_client_get_tp_list_req structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_TP_LIST_REQ
 *      This mail ID uses the sl_price_client_cancel_get_tp_list_req structure.
 * \def SL_PRICE_CLIENT_GET_RC_LIST_REQ
 *      This mail ID uses the sl_price_client_get_rc_list_req structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_RC_LIST_REQ
 *      This mail ID uses the sl_price_client_cancel_get_rc_list_req structure.
 * \def SL_PRICE_CLIENT_GET_TTI_LIST_REQ
 *      This mail ID uses the sl_price_client_get_tti_list_req structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_TTI_LIST_REQ
 *      This mail ID uses the sl_price_client_cancel_get_tti_list_req structure.
 * \def SL_PRICE_CLIENT_GET_CTI_LIST_REQ
 *      This mail ID uses the sl_price_client_get_cti_list_req structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_CTI_LIST_REQ
 *      This mail ID uses the sl_price_client_cancel_get_cti_list_req structure.
 * \def SL_PRICE_CLIENT_SET_EVENT_ROOTS_REQ
 *      This mail ID uses the sl_price_client_set_event_roots_req structure.
 * \def SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_REQ
 *      This mail ID uses the sl_price_client_set_event_programs_req structure.
 * \def SL_PRICE_CLIENT_SET_EVENT_POLL_RATE_REQ
 *      This mail ID uses the sl_price_client_set_event_poll_rate_req structure.
 * \def SL_RESP_CLIENT_SEND_RESP_REQ
 *      This mail ID uses the sl_resp_client_send_resp_req structure.
 * \def SL_TIME_SERVER_SET_TIME_REQ
 *      This mail ID uses the sl_time_server_set_time_req structure.
 * \def SL_STARTUP_REQ
 *      This mail ID does not have an associated structure because there is no
 *      data associated with the startup request. The SL_STARTUP_REQ will trigger
 *      the Services Layer to start normal processing. Please note particular
 *      cases that indicate a particular mail message should be sent prior to
 *      the SL_STARTUP_REQ.
 * \def SL_CLIENT_DISCOVER_RESOURCES_REQ
 *      This mail ID does not have an associated structure. This request is used to
 *      request the Services Layer to immediately start resource discovery. During
 *      normal operation the Services Layer performs resource discovery at a periodic
 *      interval. If the application does not wish to wait until the next resource
 *      discovery interval this request may be sent. If resource discovery is already
 *      in progress when this request is received the resource discovery process will
 *      not be restarted.
 * \def SL_CLIENT_SET_SERVER_REQ
 *      This mail ID uses the sl_client_set_server_req structure.
 * \def SL_DNS_CLIENT_CONFIG_REQ
 *      This mail ID uses the sl_dns_client_config_req structure.
 * \def SL_DNS_SERVER_CONFIG_REQ
 *      This mail ID uses the sl_dns_server_config_req structure.
 * \def SL_SEC_STORE_PRIVATE_KEY_REQ
 *      This mail ID uses the sl_sec_store_private_key_req structure.
 * \def SL_SEC_STORE_CERT_REQ
 *      This mail ID uses the sl_sec_store_cert_req structure. It can be used for both
 *      client and server.
 * \def SL_SEC_GET_SFDI_REQ
 *      This mail ID is used to request the SFDI of the device, which is sent in the
 *      sl_sec_get_sfdi_cnf structure.
 * \def SL_ZB_CONFIG_BORDER_ROUTER_REQ
 *      This mail ID uses the sl_zb_config_border_router_req structure.
 * \def SL_ZB_CONFIG_ROUTER_REQ
 *      This mail ID uses the sl_zb_config_router_req structure.
 * \def SL_ZB_CONFIG_HOST_REQ
 *      This mail ID uses the sl_zb_config_host_req structure.
 * \def SL_SERVER_CONFIG_DSP_CNF
 *      This mail ID uses the sl_server_config_dsp_cnf structure.
 * \def SL_SERVER_OBJ_CREATE_CNF
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_create_derp_cnf         - objId=\ref SL_OBJ_ID_X_DERP_X\n
 *      sl_der_server_create_derc_cnf         - objId=\ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 *      sl_der_server_create_dc_cnf           - objId=\ref SL_OBJ_ID_X_DERP_X_DC_X\n
 *      sl_drlc_server_create_drp_cnf         - objId=\ref SL_OBJ_ID_X_DR_X\n
 *      sl_drlc_server_create_edc_cnf         - objId=\ref SL_OBJ_ID_X_DR_X_EDC_X\n
 *      sl_edev_server_create_enddev_cnf      - objId=\ref SL_OBJ_ID_X_EDEV_X\n
 *      sl_edev_server_store_enddev_cnf       - objId=\ref SL_OBJ_ID_X_EDEV_X\n
 *      sl_flow_server_create_res_resp_cnf    - objId=\ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 *      sl_fsa_server_create_fsa_cnf          - objId=\ref SL_OBJ_ID_X_FSA_X\n
 *      sl_meter_server_create_mr_cnf         - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X\n
 *      sl_meter_server_create_rset_cnf       - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 *      sl_meter_server_create_reading_cnf    - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 *      sl_meter_server_create_rtype_cnf      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_meter_server_create_up_cnf         - objId=\ref SL_OBJ_ID_X_UPT_X\n
 *      sl_msg_server_create_msgp_cnf         - objId=\ref SL_OBJ_ID_X_MSG_X\n
 *      sl_msg_server_create_txt_cnf          - objId=\ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 *      sl_price_server_create_tp_cnf         - objId=\ref SL_OBJ_ID_X_TP_X\n
 *      sl_price_server_create_rc_cnf         - objId=\ref SL_OBJ_ID_X_TP_X_RC_X\n
 *      sl_price_server_create_tti_cnf        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 *      sl_price_server_create_cti_cnf        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 *      sl_price_server_create_rtype_cnf      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_resp_server_create_resp_set_cnf    - objId=\ref SL_OBJ_ID_X_RSPS_X\n
 * \def SL_SERVER_OBJ_CANCEL_CNF
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_cancel_derc_cnf         - objId=\ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 *      sl_drlc_server_cancel_edc_cnf         - objId=\ref SL_OBJ_ID_X_DR_X_EDC_X\n
 *      sl_flow_server_cancel_res_resp_cnf    - objId=\ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 *      sl_msg_server_cancel_txt_cnf          - objId=\ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 *      sl_price_server_cancel_tti_cnf        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * \def SL_SERVER_OBJ_DELETE_CNF
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_delete_derp_cnf         - objId=\ref SL_OBJ_ID_X_DERP_X\n
 *      sl_der_server_delete_default_derc_cnf - objId=\ref SL_OBJ_ID_X_DERP_X_DDERC\n
 *      sl_der_server_delete_derc_cnf         - objId=\ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 *      sl_der_server_delete_dc_cnf           - objId=\ref SL_OBJ_ID_X_DERP_X_DC_X\n
 *      sl_drlc_server_delete_drp_cnf         - objId=\ref SL_OBJ_ID_X_DR_X\n
 *      sl_drlc_server_delete_edc_cnf         - objId=\ref SL_OBJ_ID_X_DR_X_EDC_X\n
 *      sl_edev_server_delete_enddev_cnf      - objId=\ref SL_OBJ_ID_X_EDEV_X\n
 *      sl_flow_server_delete_res_req_cnf     - objId=\ref SL_OBJ_ID_X_EDEV_X_FRQ_X\n
 *      sl_flow_server_delete_res_resp_cnf    - objId=\ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 *      sl_fsa_server_delete_fsa_cnf          - objId=\ref SL_OBJ_ID_X_FSA_X\n
 *      sl_meter_server_delete_mr_cnf         - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X\n
 *      sl_meter_server_delete_rset_cnf       - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 *      sl_meter_server_delete_reading_cnf    - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 *      sl_meter_server_delete_rtype_cnf      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_meter_server_delete_top_read_cnf   - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_R\n
 *      sl_meter_server_delete_up_cnf         - objId=\ref SL_OBJ_ID_X_UPT_X\n
 *      sl_msg_server_delete_msgp_cnf         - objId=\ref SL_OBJ_ID_X_MSG_X\n
 *      sl_msg_server_delete_txt_cnf          - objId=\ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 *      sl_price_server_delete_tp_cnf         - objId=\ref SL_OBJ_ID_X_TP_X\n
 *      sl_price_server_delete_rc_cnf         - objId=\ref SL_OBJ_ID_X_TP_X_RC_X\n
 *      sl_price_server_delete_tti_cnf        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 *      sl_price_server_delete_cti_cnf        - objId=\ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 *      sl_price_server_delete_rtype_cnf      - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_resp_server_delete_resp_set_cnf    - objId=\ref SL_OBJ_ID_X_RSPS_X\n
 * \def SL_SERVER_OBJ_STORE_CNF
 *      This mail ID uses the following structures, based on which objId is specified:\n
 *      sl_der_server_store_default_derc_cnf  - objId=\ref SL_OBJ_ID_X_DERP_X_DDERC\n
 *      sl_meter_server_store_mr_cnf          - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X\n
 *      sl_meter_server_store_reading_cnf     - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 *      sl_meter_server_store_rset_cnf        - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 *      sl_meter_server_store_top_read_cnf    - objId=\ref SL_OBJ_ID_X_UPT_X_MR_X_R\n
 *      sl_meter_server_store_up_cnf          - objId=\ref SL_OBJ_ID_X_UPT_X\n
 *      sl_meter_server_store_rtype_cnf       - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_price_server_store_rtype_cnf       - objId=\ref SL_OBJ_ID_X_RT_X\n
 *      sl_sdinfo_server_store_dinfo_cnf      - objId=\ref SL_OBJ_ID_X_SDEV_SDI\n
 * \def SL_DCAP_CLIENT_SERVER_IND
 *      This mail ID uses the sl_dcap_client_server_ind structure.
 * \def SL_DCAP_CLIENT_GET_DCAP_REQ
 *      This mail ID uses the sl_dcap_client_get_dcap_req structure.
 * \def SL_DCAP_CLIENT_GET_DCAP_CNF
 *      This mail ID uses the sl_dcap_client_get_dcap_cnf structure.
 * \def SL_DER_SERVER_EVENT_STATUS_IND
 *      This mail ID uses the sl_der_server_event_status_ind structure.
 * \def SL_DER_CLIENT_DC_IND
 *      This mail ID uses the sl_der_client_dc_ind structure.
 * \def SL_DER_CLIENT_DERC_IND
 *      This mail ID uses the sl_der_client_derc_ind structure.
 * \def SL_DER_CLIENT_DERP_IND
 *      This mail ID uses the sl_der_client_derp_ind structure.
 * \def SL_DER_CLIENT_DEFAULT_DERC_IND
 *      This mail ID uses the sl_der_client_default_derc_ind structure.
 * \def SL_DER_CLIENT_SERVER_IND
 *      This mail ID uses the sl_der_client_server_ind structure.
 * \def SL_DER_CLIENT_GET_DERP_LIST_CNF
 *      This mail ID uses the sl_der_client_get_derp_list_cnf structure.
 * \def SL_DER_CLIENT_DERP_LIST_IND
 *      This mail ID uses the sl_der_client_derp_list_ind structure.
 * \def SL_DER_CLIENT_CANCEL_GET_DERP_LIST_CNF
 *      This mail ID uses the sl_der_client_cancel_get_derp_list_cnf structure.
 * \def SL_DER_CLIENT_GET_DERC_LIST_CNF
 *      This mail ID uses the sl_der_client_get_derc_list_cnf structure.
 * \def SL_DER_CLIENT_DERC_LIST_IND
 *      This mail ID uses the sl_der_client_derc_list_ind structure.
 * \def SL_DER_CLIENT_CANCEL_GET_DERC_LIST_CNF
 *      This mail ID uses the sl_der_client_cancel_get_derc_list_cnf structure.
 * \def SL_DER_CLIENT_GET_DC_LIST_CNF
 *      This mail ID uses the sl_der_client_get_dc_list_cnf structure.
 * \def SL_DER_CLIENT_DC_LIST_IND
 *      This mail ID uses the sl_der_client_dc_list_ind structure.
 * \def SL_DER_CLIENT_CANCEL_GET_DC_LIST_CNF
 *      This mail ID uses the sl_der_client_cancel_get_dc_list_cnf structure.
 * \def SL_DER_CLIENT_SET_EVENT_ROOTS_CNF
 *      This mail ID uses the sl_der_client_set_event_roots_cnf structure.
 * \def SL_DER_CLIENT_EVENT_ROOTS_IND
 *      This mail ID uses the sl_der_client_event_roots_ind structure.
 * \def SL_DER_CLIENT_SET_EVENT_PROGRAMS_CNF
 *      This mail ID uses the sl_der_client_set_event_programs_cnf structure.
 * \def SL_DER_CLIENT_EVENT_PROGRAMS_IND
 *      This mail ID uses the sl_der_client_event_programs_ind structure.
 * \def SL_DER_CLIENT_SET_EVENT_POLL_RATE_CNF
 *      This mail ID uses the sl_der_client_set_event_poll_rate_cnf structure.
 * \def SL_DER_CLIENT_SET_DEVICE_TYPE_CNF
 *      This mail ID uses the sl_der_client_set_device_type_cnf structure.
 * \def SL_EDER_SERVER_DERA_IND
 *      This mail ID uses the sl_eder_server_dera_ind structure.
 * \def SL_EDER_SERVER_DERCAP_IND
 *      This mail ID uses the sl_eder_server_dercap_ind structure.
 * \def SL_EDER_SERVER_DERS_IND
 *      This mail ID uses the sl_eder_server_ders_ind structure.
 * \def SL_EDER_SERVER_DERSETT_IND
 *      This mail ID uses the sl_eder_server_dersett_ind structure.
 * \def SL_EDER_CLIENT_SERVER_IND
 *      This mail ID uses the sl_eder_client_server_ind structure.
 * \def SL_EDER_CLIENT_SEND_DERA_CNF
 *      This mail ID uses the sl_eder_client_send_dera_cnf structure.
 * \def SL_EDER_CLIENT_SEND_DERCAP_CNF
 *      This mail ID uses the sl_eder_client_send_dercap_cnf structure.
 * \def SL_EDER_CLIENT_SEND_DERS_CNF
 *      This mail ID uses the sl_eder_client_send_ders_cnf structure.
 * \def SL_EDER_CLIENT_SEND_DERSETT_CNF
 *      This mail ID uses the sl_eder_client_send_dersett_cnf structure.
 * \def SL_DRLC_CLIENT_EDC_IND
 *      This mail ID uses the sl_drlc_client_edc_ind structure.
 * \def SL_DRLC_CLIENT_DRP_IND
 *      This mail ID uses the sl_drlc_client_drp_ind structure.
 * \def SL_DRLC_CLIENT_SERVER_IND
 *      This mail ID uses the sl_drlc_client_server_ind structure.
 * \def SL_DRLC_CLIENT_EDC_LIST_IND
 *      This mail ID uses the sl_drlc_client_edc_list_ind structure.
 * \def SL_DRLC_CLIENT_DRP_LIST_IND
 *      This mail ID uses the sl_drlc_client_drp_list_ind structure.
 * \def SL_DRLC_CLIENT_GET_DRP_LIST_CNF
 *      This mail ID uses the sl_drlc_client_get_drp_list_cnf structure.
 * \def SL_DRLC_CLIENT_CANCEL_GET_DRP_LIST_CNF
 *      This mail ID uses the sl_drlc_client_cancel_get_drp_list_cnf structure.
 * \def SL_DRLC_CLIENT_GET_EDC_LIST_CNF
 *      This mail ID uses the sl_drlc_client_get_edc_list_cnf structure.
 * \def SL_DRLC_CLIENT_CANCEL_GET_EDC_LIST_CNF
 *      This mail ID uses the sl_drlc_client_cancel_get_edc_list_cnf structure.
 * \def SL_DRLC_CLIENT_OPT_OUT_EDC_CNF
 *      This mail ID uses the sl_drlc_client_opt_out_edc_cnf structure.
 * \def SL_DRLC_CLIENT_OPT_IN_EDC_CNF
 *      This mail ID uses the sl_drlc_client_opt_in_edc_cnf structure.
 * \def SL_DRLC_CLIENT_SET_EVENT_ROOTS_CNF
 *      This mail ID uses the sl_drlc_client_set_event_roots_cnf structure.
 * \def SL_DRLC_CLIENT_EVENT_ROOTS_IND
 *      This mail ID uses the sl_drlc_client_event_roots_ind structure.
 * \def SL_DRLC_CLIENT_SET_EVENT_PROGRAMS_CNF
 *      This mail ID uses the sl_drlc_client_set_event_programs_cnf structure.
 * \def SL_DRLC_CLIENT_EVENT_PROGRAMS_IND
 *      This mail ID uses the sl_drlc_client_event_programs_ind structure.
 * \def SL_DRLC_CLIENT_SET_APPLIED_VALUES_CNF
 *      This mail ID uses the sl_drlc_client_set_applied_values_cnf structure.
 * \def SL_DRLC_SERVER_EVENT_STATUS_IND
 *      This mail ID uses the sl_drlc_server_event_status_ind structure.
 * \def SL_DRLC_CLIENT_SET_EVENT_POLL_RATE_CNF
 *      This mail ID uses the sl_drlc_client_set_event_poll_rate_cnf structure.
 * \def SL_DRLC_CLIENT_SET_DEVICE_TYPE_CNF
 *      This mail ID uses the sl_drlc_client_set_device_type_req structure.
 * \def SL_EDEV_SERVER_POST_EDEV_PENDING_IND
 *      This mail ID uses the sl_edev_server_post_edev_pending_ind structure.
 * \def SL_EDEV_SERVER_POST_EDEV_IND
 *      This mail ID uses the sl_edev_server_post_edev_ind structure.
 * \def SL_EDEV_CLIENT_SEND_ENDDEV_CNF
 *      This mail ID uses the sl_edev_client_send_enddev_cnf structure.
 * \def SL_EDEV_CLIENT_SERVER_FOUND_IND
 *      This mail ID uses the sl_edev_client_server_found_ind structure.
 * \def SL_EDEV_CLIENT_SET_PIN_CNF
 *      This mail ID uses the sl_edev_client_set_pin_cnf structure.
 * \def SL_EDEV_CLIENT_GET_EDEV_LIST_CNF
 *      This mail ID uses the sl_edev_client_get_edev_list_cnf structure.
 * \def SL_EDEV_CLIENT_CANCEL_GET_EDEV_LIST_CNF
 *      This mail ID uses the sl_edev_client_cancel_get_edev_list_cnf structure.
 * \def SL_EDEV_CLIENT_FIND_SERVER_CNF
 *      This mail ID uses the sl_edev_client_find_server_cnf structure.
 * \def SL_EDEV_CLIENT_EDEV_LIST_IND
 *      This mail ID uses the sl_edev_client_edev_list_ind structure.
 * \def SL_EDINFO_CLIENT_SERVER_IND
 *      This mail ID uses the sl_edinfo_client_server_ind structure.
 * \def SL_EDINFO_CLIENT_SEND_DINFO_CNF
 *      This mail ID uses the sl_edinfo_client_send_dinfo_cnf structure.
 * \def SL_EDSTAT_CLIENT_SERVER_IND
 *      This mail ID uses the sl_edstat_client_server_ind structure.
 * \def SL_EDSTAT_CLIENT_SEND_DSTAT_CNF
 *      This mail ID uses the sl_edstat_client_send_dstat_cnf structure.
 * \def SL_EPWRSTAT_CLIENT_SERVER_IND
 *      This mail ID uses the sl_epwrstat_client_server_ind structure.
 * \def SL_EPWRSTAT_CLIENT_SEND_PS_CNF
 *      This mail ID uses the sl_epwrstat_client_send_ps_cnf structure.
 * \def SL_EPWRSTAT_SERVER_PS_IND
 *      This mail ID uses the sl_epwrstat_server_ps_ind structure.
 * \def SL_FLOW_CLIENT_CREATE_RES_REQUEST_CNF
 *      This mail ID uses the sl_flow_client_create_res_resp_cnf structure.
 * \def SL_FLOW_CLIENT_CANCEL_RES_REQUEST_CNF
 *      This mail ID uses the sl_flow_client_cancel_res_resp_cnf structure.
 * \def SL_FLOW_CLIENT_GET_RES_RESP_LIST_CNF
 *      This mail ID uses the sl_flow_client_get_res_resp_list_cnf structure.
 * \def SL_FLOW_CLIENT_CANCEL_GET_RES_RESP_LIST_CNF
 *      This mail ID uses the sl_flow_client_cancel_get_res_resp_list_cnf structure.
 * \def SL_FLOW_CLIENT_RES_RESP_LIST_IND
 *      This mail ID uses the sl_flow_client_res_resp_list_ind structure.
 * \def SL_FLOW_SERVER_NEW_RES_REQUEST_IND
 *      This mail ID uses the sl_flow_server_new_res_request_ind structure.
 * \def SL_FLOW_SERVER_CANCEL_RES_REQUEST_IND
 *      This mail ID uses the sl_flow_server_cancel_res_request_ind structure.
 * \def SL_FLOW_SERVER_EVENT_STATUS_IND
 *      This mail ID uses the sl_flow_server_event_status_ind structure.
 * \def SL_FLOW_CLIENT_RES_RESP_IND
 *      This mail ID uses the sl_flow_client_res_resp_ind structure.
 * \def SL_FLOW_CLIENT_SERVER_IND
 *      This mail ID uses the sl_flow_client_server_ind structure.
 * \def SL_FLOW_CLIENT_SET_EVENT_POLL_RATE_CNF
 *      This mail ID uses the sl_flow_client_set_event_poll_rate_cnf structure.
 * \def SL_METER_CLIENT_GET_UP_LIST_CNF
 *      This mail ID uses the sl_meter_client_get_up_list_cnf structure.
 * \def SL_METER_CLIENT_UP_LIST_IND
 *      This mail ID uses the sl_meter_client_up_list_ind structure.
 * \def SL_METER_CLIENT_CANCEL_GET_UP_LIST_CNF
 *      This mail ID uses the sl_meter_client_cancel_get_up_list_cnf structure.
 * \def SL_METER_CLIENT_GET_MR_LIST_CNF
 *      This mail ID uses the sl_meter_client_get_mr_list_cnf structure.
 * \def SL_METER_CLIENT_MR_LIST_IND
 *      This mail ID uses the sl_meter_client_mr_list_ind structure.
 * \def SL_METER_CLIENT_CANCEL_GET_MR_LIST_CNF
 *      This mail ID uses the sl_meter_client_cancel_get_mr_list_cnf structure.
 * \def SL_METER_CLIENT_GET_RC_LIST_CNF
 *      This mail ID uses the sl_meter_client_get_rc_list_cnf structure.
 * \def SL_METER_CLIENT_RC_LIST_IND
 *      This mail ID uses the sl_meter_client_rc_list_ind structure.
 * \def SL_METER_CLIENT_CANCEL_GET_RC_LIST_CNF
 *      This mail ID uses the sl_meter_client_cancel_get_rc_list_cnf structure.
 * \def SL_METER_CLIENT_GET_RSET_LIST_CNF
 *      This mail ID uses the sl_meter_client_get_rset_list_cnf structure.
 * \def SL_METER_CLIENT_RSET_LIST_IND
 *      This mail ID uses the sl_meter_client_rset_list_ind structure.
 * \def SL_METER_CLIENT_CANCEL_GET_RSET_LIST_CNF
 *      This mail ID uses the sl_meter_client_cancel_get_rset_list_cnf structure.
 * \def SL_METER_CLIENT_GET_READING_LIST_CNF
 *      This mail ID uses the sl_meter_client_get_reading_list_cnf structure.
 * \def SL_METER_CLIENT_READING_LIST_IND
 *      This mail ID uses the sl_meter_client_reading_list_ind structure.
 * \def SL_METER_CLIENT_CANCEL_GET_READING_LIST_CNF
 *      This mail ID uses the sl_meter_client_cancel_get_reading_list_cnf structure.
 * \def SL_METER_CLIENT_SERVER_IND
 *      This mail ID uses the sl_meter_client_server_ind structure.
 * \def SL_METER_CLIENT_UP_LIST_IND
 *      This mail ID uses the sl_meter_client_up_list_ind structure.
 * \def SL_METER_MIRROR_CLIENT_SEND_MUP_CNF
 *      This mail ID uses the sl_meter_mirror_client_send_mup_cnf structure.
 * \def SL_METER_MIRROR_CLIENT_SEND_MMR_CNF
 *      This mail ID uses the sl_meter_mirror_client_send_mmr_cnf structure.
 * \def SL_METER_MIRROR_CLIENT_GET_MUP_RATES_CNF
 *      This mail ID uses the sl_meter_mirror_client_get_mup_rates_cnf structure.
 * \def SL_METER_MIRROR_CLIENT_MUP_IND
 *      This mail ID uses the sl_meter_mirror_client_mup_ind structure.
 * \def SL_METER_MIRROR_SERVER_RX_MUP_IND
 *      This mail ID uses the sl_meter_mirror_server_rx_mup_ind structure.
 * \def SL_METER_MIRROR_SERVER_RX_MMR_IND
 *      This mail ID uses the sl_meter_mirror_server_rx_mmr_ind structure.
 * \def SL_METER_MIRROR_CLIENT_SERVER_IND
 *      This mail ID uses the sl_meter_mirror_client_server_ind structure.
 * \def SL_METER_MIRROR_SERVER_CONFIG_CLIENT_FILTER_CNF
 *      This mail ID uses the sl_meter_mirror_server_config_client_filter_req structure.
 * \def SL_MSG_SERVER_EVENT_STATUS_IND
 *      This mail ID uses the sl_msg_server_event_status_ind structure.
 * \def SL_MSG_CLIENT_MSGP_IND
 *      This mail ID uses the sl_msg_client_msgp_ind structure.
 * \def SL_MSG_CLIENT_TXT_IND
 *      This mail ID uses the sl_msg_client_txt_ind structure.
 * \def SL_MSG_CLIENT_SERVER_IND
 *      This mail ID uses the sl_msg_client_server_ind structure.
 * \def SL_MSG_CLIENT_TXT_LIST_IND
 *      This mail ID uses the sl_msg_client_txt_list_ind structure.
 * \def SL_MSG_CLIENT_MSGP_LIST_IND
 *      This mail ID uses the sl_msg_client_msgp_list_ind structure.
 * \def SL_MSG_CLIENT_GET_MSGP_LIST_CNF
 *      This mail ID uses the sl_msg_client_get_msgp_list_cnf structure.
 * \def SL_MSG_CLIENT_CANCEL_GET_MSGP_LIST_CNF
 *      This mail ID uses the sl_msg_client_cancel_get_msgp_list_cnf structure.
 * \def SL_MSG_CLIENT_GET_TXT_LIST_CNF
 *      This mail ID uses the sl_msg_client_get_txt_list_cnf structure.
 * \def SL_MSG_CLIENT_CANCEL_GET_TXT_LIST_CNF
 *      This mail ID uses the sl_msg_client_cancel_get_txt_list_cnf structure.
 * \def SL_MSG_CLIENT_SET_EVENT_ROOTS_CNF
 *      This mail ID uses the sl_msg_client_set_event_roots_cnf structure.
 * \def SL_MSG_CLIENT_EVENT_ROOTS_IND
 *      This mail ID uses the sl_msg_client_event_roots_ind structure.
 * \def SL_MSG_CLIENT_SET_EVENT_PROGRAMS_CNF
 *      This mail ID uses the sl_msg_client_set_event_programs_cnf structure.
 * \def SL_MSG_CLIENT_EVENT_PROGRAMS_IND
 *      This mail ID uses the sl_msg_client_event_programs_ind structure.
 * \def SL_MSG_CLIENT_SET_EVENT_POLL_RATE_CNF
 *      This mail ID uses the sl_msg_client_set_event_poll_rate_cnf structure.
 * \def SL_PRICE_SERVER_EVENT_STATUS_IND
 *      This mail ID uses the sl_price_server_event_status_ind structure.
 * \def SL_PRICE_CLIENT_TTI_IND
 *      This mail ID uses the sl_price_client_tti_ind structure.
 * \def SL_PRICE_CLIENT_GET_TP_LIST_CNF
 *      This mail ID uses the sl_price_client_get_tp_list_cnf structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_TP_LIST_CNF
 *      This mail ID uses the sl_price_client_cancel_get_tp_list_cnf structure.
 * \def SL_PRICE_CLIENT_GET_RC_LIST_CNF
 *      This mail ID uses the sl_price_client_get_rc_list_cnf structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_RC_LIST_CNF
 *      This mail ID uses the sl_price_client_cancel_get_rc_list_cnf structure.
 * \def SL_PRICE_CLIENT_GET_TTI_LIST_CNF
 *      This mail ID uses the sl_price_client_get_tti_list_cnf structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_TTI_LIST_CNF
 *      This mail ID uses the sl_price_client_cancel_get_tti_list_cnf structure.
 * \def SL_PRICE_CLIENT_GET_CTI_LIST_CNF
 *      This mail ID uses the sl_price_client_get_cti_list_cnf structure.
 * \def SL_PRICE_CLIENT_CANCEL_GET_CTI_LIST_CNF
 *      This mail ID uses the sl_price_client_cancel_get_cti_list_cnf structure.
 * \def SL_PRICE_CLIENT_SERVER_IND
 *      This mail ID uses the sl_price_client_server_ind structure.
 * \def SL_PRICE_CLIENT_TP_IND
 *      This mail ID uses the sl_price_client_tp_ind structure.
 * \def SL_PRICE_CLIENT_RC_IND
 *      This mail ID uses the sl_price_client_rc_ind structure.
 * \def SL_PRICE_CLIENT_TP_LIST_IND
 *      This mail ID uses the sl_price_client_tp_list_ind structure.
 * \def SL_PRICE_CLIENT_RC_LIST_IND
 *      This mail ID uses the sl_price_client_rc_list_ind structure.
 * \def SL_PRICE_CLIENT_TTI_LIST_IND
 *      This mail ID uses the sl_price_client_tti_list_ind structure.
 * \def SL_PRICE_CLIENT_CTI_LIST_IND
 *      This mail ID uses the sl_price_client_cti_list_ind structure.
 * \def SL_PRICE_CLIENT_SET_EVENT_ROOTS_CNF
 *      This mail ID uses the sl_price_client_set_event_roots_cnf structure.
 * \def SL_PRICE_CLIENT_EVENT_ROOTS_IND
 *      This mail ID uses the sl_price_client_event_roots_ind structure.
 * \def SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_CNF
 *      This mail ID uses the sl_price_client_set_event_programs_cnf structure.
 * \def SL_PRICE_CLIENT_EVENT_PROGRAMS_IND
 *      This mail ID uses the sl_price_client_event_programs_ind structure.
 * \def SL_PRICE_CLIENT_SET_EVENT_POLL_RATE_CNF
 *      This mail ID uses the sl_price_client_set_event_poll_rate_cnf structure.
 * \def SL_RESP_SERVER_RESP_IND
 *      This mail ID uses the sl_resp_server_resp_ind structure.
 * \def SL_RESP_CLIENT_SEND_RESP_CNF
 *      This mail ID uses the sl_resp_client_send_resp_cnf structure.
 * \def SL_TIME_SERVER_SET_TIME_CNF
 *      This mail ID uses the sl_time_server_set_time_cnf structure.
 * \def SL_TIME_CLIENT_SERVER_IND
 *      This mail ID uses the sl_time_client_server_ind structure.
 * \def SL_TIME_CLIENT_SERVER_TIME_IND
 *      This mail ID uses the sl_time_client_server_time_ind structure.
 * \def SL_STARTUP_CNF
 *      This mail ID uses the sl_startup_cnf structure.
 * \def SL_CLIENT_SET_SERVER_CNF
 *      This mail ID uses the sl_client_set_server_cnf structure.
 * \def SL_DNS_CLIENT_CONFIG_CNF
 *      This mail ID uses the sl_dns_client_config_cnf structure.
 * \def SL_DNS_SERVER_CONFIG_CNF
 *      This mail ID uses the sl_dns_server_config_cnf structure.
 * \def SL_SEC_STORE_PRIVATE_KEY_CNF
 *      This mail ID uses the sl_sec_store_private_key_cnf structure.
 * \def SL_SEC_GET_SFDI_CNF
 *      This mail ID is uses the sl_sec_get_sfdi_cnf structure.
 * \def SL_ZB_CONFIG_BORDER_ROUTER_CNF
 *      This mail ID uses the sl_zb_config_border_router_cnf structure.
 * \def SL_ZB_CONFIG_ROUTER_CNF
 *      This mail ID uses the sl_zb_config_router_cnf structure.
 * \def SL_ZB_CONFIG_HOST_CNF
 *      This mail ID uses the sl_zb_config_host_cnf structure.
 * \def SL_STACK_INFO_REQ
 *      This mail ID uses the sl_stack_info_req structure.
 * \def SL_STACK_INFO_CNF
 *      This mail ID uses the sl_stack_info_cnf structure.
 */

// ========= REQUESTS AND INDICATIONS ===========

// ================ REQUESTS  ===================
// -------------------- SL Server Common --------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_SERVER_OBJ_CREATE_REQ             0x01
#define SL_SERVER_OBJ_CANCEL_REQ             0x0A
#define SL_SERVER_OBJ_DELETE_REQ             0x0B
#define SL_SERVER_OBJ_STORE_REQ              0x0D
/** @} */

// -------------------- BILL --------------------


// -------------------- Config ------------------
/** \cond NOTRELEASED */
#define SL_ECFG_CLIENT_PUT_CONFIG_REQ     0x0E
/** \endcond */

// -------------------- DER ---------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_DER_CLIENT_GET_DERP_LIST_REQ        0x140
#define SL_DER_CLIENT_CANCEL_GET_DERP_LIST_REQ 0x141
#define SL_DER_CLIENT_GET_DERC_LIST_REQ        0x142
#define SL_DER_CLIENT_CANCEL_GET_DERC_LIST_REQ 0x143
#define SL_DER_CLIENT_GET_DC_LIST_REQ          0x144
#define SL_DER_CLIENT_CANCEL_GET_DC_LIST_REQ   0x145
#define SL_DER_CLIENT_SET_EVENT_PROGRAMS_REQ   0x14F // OUT OF ORDER!!
#define SL_DER_CLIENT_SET_EVENT_ROOTS_REQ      0x152 // OUT OF ORDER!!
#define SL_DER_CLIENT_SET_EVENT_POLL_RATE_REQ  0x40  // OUT OF ORDER!!
#define SL_DER_CLIENT_SET_DEVICE_TYPE_REQ      0x186 // OUT OF ORDER!!


// -------------------- DINFO -------------------
#define SL_EDINFO_CLIENT_SEND_DINFO_REQ         0x30

// -------------------- DRLC --------------------

#define SL_DRLC_CLIENT_GET_DRP_LIST_REQ        0x71  // MailID is TBD
#define SL_DRLC_CLIENT_CANCEL_GET_DRP_LIST_REQ 0x72  // MailID is TBD
#define SL_DRLC_CLIENT_GET_EDC_LIST_REQ        0x73  // MailID is TBD
#define SL_DRLC_CLIENT_CANCEL_GET_EDC_LIST_REQ 0x74  // MailID is TBD
#define SL_DRLC_CLIENT_OPT_OUT_EDC_REQ         0x1C  // OUT OF ORDER!!
#define SL_DRLC_CLIENT_OPT_IN_EDC_REQ          0x1D  // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_EVENT_PROGRAMS_REQ  0x1E  // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_EVENT_ROOTS_REQ     0x1F  // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_EVENT_POLL_RATE_REQ 0x41  // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_APPLIED_VALUES_REQ  0x104 
#define SL_DRLC_CLIENT_SET_DEVICE_TYPE_REQ     0x188 // OUT OF ORDER!!


// -------------------- EDER --------------------
#define SL_EDER_CLIENT_SEND_DERSETT_REQ      0x18 // OUT OF ORDER!!
#define SL_EDER_CLIENT_SEND_DERCAP_REQ       0x19 // OUT OF ORDER!!
#define SL_EDER_CLIENT_SEND_DERS_REQ         0x1A // OUT OF ORDER!!
#define SL_EDER_CLIENT_SEND_DERA_REQ         0x1B // OUT OF ORDER!!

// -------------------- End Device---------------
#define SL_EDEV_CLIENT_SEND_ENDDEV_REQ      0x27
#define SL_EDEV_CLIENT_SET_PIN_REQ          0x29 // OUT OF ORDER!!
#define SL_EDEV_CLIENT_GET_EDEV_LIST_REQ    0x101 // MailID is TBD
#define SL_EDEV_CLIENT_CANCEL_GET_EDEV_LIST_REQ  0x102 // MailID is TBD
#define SL_EDEV_CLIENT_FIND_SERVER_REQ      0x103 // MailID is TBD
#define SL_EDEV_SERVER_POST_EDEV_PENDING_RSP 0x28

// -------------------- EDSTAT ------------------
#define SL_EDSTAT_CLIENT_SEND_DSTAT_REQ     0x4E
/** @} */

// -------------------- EFILE -------------------
/** \cond NOTRELEASED */
#define SL_EFILE_CLIENT_SEND_FILESTAT_REQ   0x2C // OUT OF ORDER!!
/** \endcond */

// -------------------- EPWRSTAT ----------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_EPWRSTAT_CLIENT_SEND_PS_REQ      0x4A

// -------------------- FILE --------------------


// -------------------- Flow Reservation ------
#define SL_FLOW_CLIENT_CREATE_RES_REQUEST_REQ 0x6D // OUT OF ORDER!!
#define SL_FLOW_CLIENT_CANCEL_RES_REQUEST_REQ 0x6F // OUT OF ORDER!!

#define SL_FLOW_CLIENT_GET_RES_RESP_LIST_REQ    0x80
#define SL_FLOW_CLIENT_CANCEL_GET_RES_RESP_LIST_REQ 0x81
#define SL_FLOW_CLIENT_SET_EVENT_POLL_RATE_REQ  0x48  // OUT OF ORDER!!
/** @} */

// -------------------- FSA ---------------------
#define SL_FSA_CLIENT_GET_FSA_LIST_REQ          0x178 // OUT OF ORDER!!
#define SL_FSA_CLIENT_CANCEL_GET_FSA_LIST_REQ   0x179 // OUT OF ORDER!!
#define SL_FSA_CLIENT_DELETE_FSA_ROOT_REQ       0x17E // OUT OF ORDER!!
#define SL_FSA_CLIENT_DELETE_FSA_ROOT_CNF       0x17F // OUT OF ORDER!!


// -------------------- Log Event ---------------


// -------------------- Load Shed Availability --
//** \cond NOTRELEASED */
#define SL_EDRLC_CLIENT_PUT_LSA_REQ           0x31
/** \endcond */

// -------------------- Msg ---------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_MSG_SERVER_DELETE_MSGP_REQ          0x34
#define SL_MSG_CLIENT_REINIT_MSG_PROC_REQ      0x32
#define SL_MSG_CLIENT_GET_MSGP_LIST_REQ        0x108 // MailID is TBD
#define SL_MSG_CLIENT_CANCEL_GET_MSGP_LIST_REQ 0x109 // MailID is TBD
#define SL_MSG_CLIENT_GET_TXT_LIST_REQ         0x10A // MailID is TBD
#define SL_MSG_CLIENT_CANCEL_GET_TXT_LIST_REQ  0x10B // MailID is TBD
#define SL_MSG_CLIENT_SET_EVENT_PROGRAMS_REQ   0x160 // OUT OF ORDER!!
#define SL_MSG_CLIENT_SET_EVENT_ROOTS_REQ      0x161 // OUT OF ORDER!!
#define SL_MSG_CLIENT_SET_EVENT_POLL_RATE_REQ  0x42  // OUT OF ORDER!!
/** @} */

// -------------------- Meter -------------------
/** \addtogroup MAIL_IDS
* @{ */

#define SL_METER_CLIENT_GET_UP_LIST_REQ              0x120
#define SL_METER_CLIENT_CANCEL_GET_UP_LIST_REQ       0x121
#define SL_METER_CLIENT_GET_MR_LIST_REQ              0x122
#define SL_METER_CLIENT_CANCEL_GET_MR_LIST_REQ       0x123
#define SL_METER_CLIENT_GET_RC_LIST_REQ              0x124
#define SL_METER_CLIENT_CANCEL_GET_RC_LIST_REQ       0x125
#define SL_METER_CLIENT_GET_RSET_LIST_REQ            0x126
#define SL_METER_CLIENT_CANCEL_GET_RSET_LIST_REQ     0x127
#define SL_METER_CLIENT_GET_READING_LIST_REQ         0x128
#define SL_METER_CLIENT_CANCEL_GET_READING_LIST_REQ  0x129

#define SL_METER_MIRROR_CLIENT_GET_MUP_RATES_REQ      0x3D
#define SL_METER_MIRROR_CLIENT_SEND_MUP_REQ           0x3E
#define SL_METER_MIRROR_CLIENT_SEND_MMR_REQ           0x3F

#define SL_METER_MIRROR_SERVER_CONFIG_CLIENT_FILTER_REQ  0x20

/** @} */

// -------------------- Network Status ----------


// -------------------- PrePay ------------------


// -------------------- Price -------------------
/** \addtogroup MAIL_IDS
* @{ */

#define SL_PRICE_CLIENT_GET_TP_LIST_REQ         0x55 // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_TP_LIST_REQ  0x56 // MailId TBD
#define SL_PRICE_CLIENT_GET_RC_LIST_REQ         0x57 // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_RC_LIST_REQ  0x5D // MailId TBD
#define SL_PRICE_CLIENT_GET_TTI_LIST_REQ        0x5E // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_TTI_LIST_REQ 0x5F // MailId TBD
#define SL_PRICE_CLIENT_GET_CTI_LIST_REQ        0x61 // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_CTI_LIST_REQ 0x62 // MailId TBD
#define SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_REQ  0x63 // MailId TBD
#define SL_PRICE_CLIENT_SET_EVENT_ROOTS_REQ     0x64 // MailId TBD
#define SL_PRICE_CLIENT_SET_EVENT_POLL_RATE_REQ 0x43 // OUT OF ORDER!!
/** @} */

// -------------------- Response-----------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_RESP_CLIENT_SEND_RESP_REQ        0x113 // MailId TBD
/** @} */

// -------------------- SDER --------------------
// -------------------- SFILE -------------------


// -------------------- Subscription ------------


// -------------------- Time --------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_TIME_SERVER_SET_TIME_REQ         0x68
/** @} */

// -------------------- General------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_STARTUP_REQ                      0x70
#define SL_CLIENT_DISCOVER_RESOURCES_REQ    0x6A // Out of order!
#define SL_CLIENT_SET_SERVER_REQ            0x75 // Out of order!
#define SL_DNS_CLIENT_CONFIG_REQ            0x150 // MailId TBD
#define SL_DNS_SERVER_CONFIG_REQ            0x114 // MailId TBD
#define SL_SEC_STORE_PRIVATE_KEY_REQ        0x76
#define SL_SEC_STORE_CERT_REQ               0x77
#define SL_SEC_GET_SFDI_REQ                 0x7B
#define SL_SEC_STORE_ROOT_CA_CERT_REQ       0x7D
#define SL_SEC_STORE_SERVER_WHITE_LIST_REQ  0x18A // SPRK-370
#define SL_SEC_STORE_CLIENT_WHITE_LIST_REQ  0x18D // SPRK-1493
#define SL_SERVER_CONFIG_DSP_REQ            0x11E // Out of order!
/** @} */

// -------------------- Zigbee ------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_ZB_CONFIG_BORDER_ROUTER_REQ      0x78
#define SL_ZB_CONFIG_ROUTER_REQ             0x79
#define SL_ZB_CONFIG_HOST_REQ               0x7A
/** @} */

// ======= CONFIRMS & INDICATIONS ===============
// -------------------- SL Server Common --------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_SERVER_OBJ_CREATE_CNF             0x08
#define SL_SERVER_OBJ_CANCEL_CNF             0x09
#define SL_SERVER_OBJ_DELETE_CNF             0x0C
#define SL_SERVER_OBJ_STORE_CNF              0x0F
/** @} */

// -------------------- Bill --------------------

// -------------------- Config ------------------
/** \cond NOTRELEASED */
#define SL_ECFG_CLIENT_PUT_CONFIG_CNF     0x8E
/** \endcond */

/** \addtogroup MAIL_IDS
* @{ */
// -------------------- DCAP -------------------------
//
#define SL_DCAP_CLIENT_SERVER_IND                 0x91
#define SL_DCAP_CLIENT_GET_DCAP_REQ               0x92
#define SL_DCAP_CLIENT_GET_DCAP_CNF               0x93
#define SL_DCAP_CLIENT_DCAP_IND                   0x18C

// -------------------- DER ---------------------
#define SL_DER_CLIENT_DC_IND                0x9D
#define SL_DER_CLIENT_DERC_IND              0x9E
#define SL_DER_CLIENT_DEFAULT_DERC_IND      0x9F
#define SL_DER_CLIENT_DERP_IND              0x04
#define SL_DER_CLIENT_SERVER_IND            0x05
#define SL_DER_SERVER_EVENT_STATUS_IND      0x11A // OUT OF ORDER!!

#define SL_DER_CLIENT_DERP_LIST_IND            0x146
#define SL_DER_CLIENT_DERC_LIST_IND            0x147
#define SL_DER_CLIENT_DC_LIST_IND              0x148
#define SL_DER_CLIENT_GET_DERP_LIST_CNF        0x149
#define SL_DER_CLIENT_CANCEL_GET_DERP_LIST_CNF 0x14A
#define SL_DER_CLIENT_GET_DERC_LIST_CNF        0x14B
#define SL_DER_CLIENT_CANCEL_GET_DERC_LIST_CNF 0x14C
#define SL_DER_CLIENT_GET_DC_LIST_CNF          0x14D
#define SL_DER_CLIENT_CANCEL_GET_DC_LIST_CNF   0x14E
#define SL_DER_CLIENT_SET_EVENT_PROGRAMS_CNF   0x180 // OUT OF ORDER!!
#define SL_DER_CLIENT_EVENT_PROGRAMS_IND       0x181 // OUT OF ORDER!!
#define SL_DER_CLIENT_SET_EVENT_ROOTS_CNF      0x182 // OUT OF ORDER!!
#define SL_DER_CLIENT_EVENT_ROOTS_IND          0x183 // OUT OF ORDER!!
#define SL_DER_CLIENT_SET_EVENT_POLL_RATE_CNF  0x44  // OUT OF ORDER!!
#define SL_DER_CLIENT_SET_DEVICE_TYPE_CNF      0x187 // OUT OF ORDER!!


// -------------------- DINFO -------------------
#define SL_EDINFO_CLIENT_SERVER_IND            0xBC
#define SL_EDINFO_CLIENT_SEND_DINFO_CNF        0xBD
#define SL_EDINFO_SERVER_DINFO_IND             0xBB

// -------------------- DRLC --------------------

#define SL_DRLC_SERVER_EVENT_STATUS_IND     0x119 // OUT OF ORDER!!
#define SL_DRLC_CLIENT_EDC_IND              0xA4
#define SL_DRLC_CLIENT_DRP_IND              0xA5
#define SL_DRLC_CLIENT_SERVER_IND           0xE2 // MailID is TBD
#define SL_DRLC_CLIENT_EDC_LIST_IND         0xE3 // MailID is TBD
#define SL_DRLC_CLIENT_DRP_LIST_IND         0xE4 // MailID is TBD
#define SL_DRLC_CLIENT_GET_DRP_LIST_CNF        0xE5 // MailID is TBD
#define SL_DRLC_CLIENT_CANCEL_GET_DRP_LIST_CNF 0xE7 // MailID is TBD
#define SL_DRLC_CLIENT_GET_EDC_LIST_CNF        0xC3 // MailID is TBD
#define SL_DRLC_CLIENT_CANCEL_GET_EDC_LIST_CNF 0xAA // MailID is TBD
#define SL_DRLC_CLIENT_OPT_OUT_EDC_CNF      0x8A // OUT OF ORDER!!
#define SL_DRLC_CLIENT_OPT_IN_EDC_CNF       0x8B // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_EVENT_PROGRAMS_CNF   0x8C // OUT OF ORDER!!
#define SL_DRLC_CLIENT_EVENT_PROGRAMS_IND       0x8D // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_EVENT_ROOTS_CNF    0x8F // OUT OF ORDER!!
#define SL_DRLC_CLIENT_EVENT_ROOTS_IND        0x90 // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_EVENT_POLL_RATE_CNF  0x45  // OUT OF ORDER!!
#define SL_DRLC_CLIENT_SET_APPLIED_VALUES_CNF  0x13B
#define SL_DRLC_CLIENT_SET_DEVICE_TYPE_CNF     0x189 // OUT OF ORDER!!


// -------------------- EDER --------------------
#define SL_EDER_SERVER_DERA_IND              0x9C
#define SL_EDER_SERVER_DERCAP_IND            0x94
#define SL_EDER_SERVER_DERS_IND              0x95
#define SL_EDER_SERVER_DERSETT_IND           0x96
#define SL_EDER_CLIENT_SERVER_IND            0x97
#define SL_EDER_CLIENT_SEND_DERSETT_CNF      0x98  // OUT OF ORDER!!
#define SL_EDER_CLIENT_SEND_DERCAP_CNF       0x99  // OUT OF ORDER!!
#define SL_EDER_CLIENT_SEND_DERS_CNF         0x9A  // OUT OF ORDER!!
#define SL_EDER_CLIENT_SEND_DERA_CNF         0x9B  // OUT OF ORDER!!

// -------------------- End Device---------------
#define SL_EDEV_SERVER_POST_EDEV_IND        0x25
#define SL_EDEV_SERVER_POST_EDEV_PENDING_IND 0x26
#define SL_EDEV_CLIENT_SEND_ENDDEV_CNF      0xA7
#define SL_EDEV_CLIENT_SERVER_FOUND_IND     0xA9 // NOTE: This mail ID is out of order!!
#define SL_EDEV_CLIENT_SET_PIN_CNF          0xC2 // NOTE: This mail ID is out of order!!
#define SL_EDEV_CLIENT_GET_EDEV_LIST_CNF    0x06 // MailID is TBD
#define SL_EDEV_CLIENT_CANCEL_GET_EDEV_LIST_CNF 0x105 // MailID is TBD
#define SL_EDEV_CLIENT_FIND_SERVER_CNF      0x106 // MailID is TBD
#define SL_EDEV_CLIENT_EDEV_LIST_IND        0x107 // MailID is TBD

// -------------------- EDSTAT ----------------
#define SL_EDSTAT_CLIENT_SERVER_IND         0xCD
#define SL_EDSTAT_CLIENT_SEND_DSTAT_CNF     0xCE

// -------------------- EPWRSTAT --------------
#define SL_EPWRSTAT_SERVER_PS_IND           0x118 // OUT OF ORDER!!
#define SL_EPWRSTAT_CLIENT_SERVER_IND       0xCB
#define SL_EPWRSTAT_CLIENT_SEND_PS_CNF      0xCA

// -------------------- Flow Reservation ------
#define SL_FLOW_CLIENT_CREATE_RES_REQUEST_CNF 0xEB // OUT OF ORDER!!
#define SL_FLOW_CLIENT_CANCEL_RES_REQUEST_CNF 0xEC // OUT OF ORDER!!
#define SL_FLOW_SERVER_NEW_RES_REQUEST_IND    0xED // OUT OF ORDER!!
#define SL_FLOW_SERVER_CANCEL_RES_REQUEST_IND 0xEE // OUT OF ORDER!!
#define SL_FLOW_CLIENT_RES_RESP_IND           0xEF // OUT OF ORDER!!
#define SL_FLOW_CLIENT_SERVER_IND             0x02 // OUT OF ORDER!!
#define SL_FLOW_SERVER_EVENT_STATUS_IND       0x11D // OUT OF ORDER!!

#define SL_FLOW_CLIENT_GET_RES_RESP_LIST_CNF  0x80
#define SL_FLOW_CLIENT_CANCEL_GET_RES_RESP_LIST_CNF 0x81
#define SL_FLOW_CLIENT_RES_RESP_LIST_IND      0x82
#define SL_FLOW_CLIENT_SET_EVENT_POLL_RATE_CNF      0x49  // OUT OF ORDER!!
/** @} */

// -------------------- Log Event ---------------
#define SL_ELEL_CLIENT_SERVER_IND       0x174 // OUT OF ORDER!!
#define SL_ELEL_CLIENT_SEND_LE_REQ      0x175 // OUT OF ORDER!!
#define SL_ELEL_CLIENT_SEND_LE_CNF      0x176 // OUT OF ORDER!!
#define SL_ELEL_SERVER_LE_IND           0x177 // OUT OF ORDER!!


// -------------------- EFILE -------------------
/** \cond NOTRELEASED */
#define SL_EFILE_CLIENT_SEND_FILESTAT_CNF   0xAF // OUT OF ORDER!!
/** \endcond */

// -------------------- FILE --------------------
/** \cond NOTRELEASED */
#define SL_FILE_CLIENT_FILE_IND             0xC7 // OUT OF ORDER!!
/** \endcond */

// -------------------- FSA ---------------------
#define SL_FSA_CLIENT_FSA_LIST_IND            0x17A // OUT OF ORDER!!
#define SL_FSA_CLIENT_GET_FSA_LIST_CNF        0x17B // OUT OF ORDER!!
#define SL_FSA_CLIENT_CANCEL_GET_FSA_LIST_CNF 0x17C // OUT OF ORDER!!
#define SL_FSA_CLIENT_SERVER_FOUND_IND        0x17D // OUT OF ORDER!!

// -------------------- Load Shed Availability --
/** \cond NOTRELEASED */
#define SL_EDRLC_CLIENT_PUT_LSA_CNF           0xB1

#define SL_EDRLC_SERVER_LSA_IND               0xB0

/** \endcond */

// -------------------- Msg ---------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_MSG_SERVER_EVENT_STATUS_IND      0x11B // OUT OF ORDER!!
#define SL_MSG_CLIENT_REINIT_MSG_PROC_CNF   0x33
#define SL_MSG_CLIENT_MSGP_IND              0xB6
#define SL_MSG_CLIENT_TXT_IND               0xB7
#define SL_MSG_CLIENT_SERVER_IND            0x10C // MailID is TBD
#define SL_MSG_CLIENT_TXT_LIST_IND          0x10D // MailID is TBD
#define SL_MSG_CLIENT_MSGP_LIST_IND         0x10E // MailID is TBD
#define SL_MSG_CLIENT_GET_MSGP_LIST_CNF     0x10F // MailID is TBD
#define SL_MSG_CLIENT_CANCEL_GET_MSGP_LIST_CNF 0x110 // MailID is TBD
#define SL_MSG_CLIENT_GET_TXT_LIST_CNF        0x111 // MailID is TBD
#define SL_MSG_CLIENT_CANCEL_GET_TXT_LIST_CNF 0x112 // MailID is TBD
#define SL_MSG_CLIENT_SET_EVENT_PROGRAMS_CNF  0x162 // OUT OF ORDER!!
#define SL_MSG_CLIENT_EVENT_PROGRAMS_IND      0x163 // OUT OF ORDER!!
#define SL_MSG_CLIENT_SET_EVENT_ROOTS_CNF     0x164 // OUT OF ORDER!!
#define SL_MSG_CLIENT_EVENT_ROOTS_IND         0x165 // OUT OF ORDER!!
#define SL_MSG_CLIENT_SET_EVENT_POLL_RATE_CNF 0x46  // OUT OF ORDER!!
/** @} */

// -------------------- Meter -------------------
/** \addtogroup MAIL_IDS
* @{ */

#define SL_METER_CLIENT_SERVER_IND                   0x12A
#define SL_METER_CLIENT_GET_UP_LIST_CNF              0x12B
#define SL_METER_CLIENT_UP_LIST_IND                  0x12C
#define SL_METER_CLIENT_CANCEL_GET_UP_LIST_CNF       0x12D
#define SL_METER_CLIENT_GET_MR_LIST_CNF              0x12E
#define SL_METER_CLIENT_MR_LIST_IND                  0x12F
#define SL_METER_CLIENT_CANCEL_GET_MR_LIST_CNF       0x130
#define SL_METER_CLIENT_GET_RC_LIST_CNF              0x131
#define SL_METER_CLIENT_RC_LIST_IND                  0x132
#define SL_METER_CLIENT_CANCEL_GET_RC_LIST_CNF       0x133
#define SL_METER_CLIENT_GET_RSET_LIST_CNF            0x134
#define SL_METER_CLIENT_RSET_LIST_IND                0x135
#define SL_METER_CLIENT_CANCEL_GET_RSET_LIST_CNF     0x136
#define SL_METER_CLIENT_GET_READING_LIST_CNF         0x137
#define SL_METER_CLIENT_READING_LIST_IND             0x138
#define SL_METER_CLIENT_CANCEL_GET_READING_LIST_CNF  0x139

#define SL_METER_MIRROR_CLIENT_MUP_POLLRATE_IND         0xB8
#define SL_METER_MIRROR_CLIENT_MUP_POSTRATE_IND         0xB9
#define SL_METER_MIRROR_CLIENT_GET_MUP_RATES_CNF        0xBA
#define SL_METER_MIRROR_CLIENT_SEND_MUP_CNF             0xBE
#define SL_METER_MIRROR_CLIENT_SEND_MMR_CNF             0xBF
#define SL_METER_MIRROR_SERVER_RX_MUP_IND               0xC0
#define SL_METER_MIRROR_SERVER_RX_MMR_IND               0xC1
#define SL_METER_MIRROR_CLIENT_SERVER_IND               0xC5
#define SL_METER_MIRROR_CLIENT_MUP_IND                  0x07

#define SL_METER_MIRROR_SERVER_CONFIG_CLIENT_FILTER_CNF  0x21

/** @} */

// -------------------- Network Status ----------
/** \cond NOTRELEASED */
//                                          0xXX
/** \endcond */

// -------------------- PrePay ------------------

// -------------------- Price -------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_PRICE_SERVER_EVENT_STATUS_IND    0x11C // OUT OF ORDER!!
#define SL_PRICE_CLIENT_TTI_IND             0xDD

#define SL_PRICE_CLIENT_GET_TP_LIST_CNF         0xDE // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_TP_LIST_CNF  0xDF // MailId TBD
#define SL_PRICE_CLIENT_GET_RC_LIST_CNF         0xF2 // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_RC_LIST_CNF  0xF3 // MailId TBD
#define SL_PRICE_CLIENT_GET_TTI_LIST_CNF        0xF4 // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_TTI_LIST_CNF 0xF5 // MailId TBD
#define SL_PRICE_CLIENT_GET_CTI_LIST_CNF        0xF6 // MailId TBD
#define SL_PRICE_CLIENT_CANCEL_GET_CTI_LIST_CNF 0xF7 // MailId TBD

#define SL_PRICE_CLIENT_SERVER_IND              0xF8 // MailId TBD
#define SL_PRICE_CLIENT_TP_IND                  0xF9 // MailId TBD
#define SL_PRICE_CLIENT_RC_IND                  0xFA // MailId TBD
#define SL_PRICE_CLIENT_TP_LIST_IND             0xFC // MailId TBD
#define SL_PRICE_CLIENT_RC_LIST_IND             0xFD // MailId TBD
#define SL_PRICE_CLIENT_TTI_LIST_IND            0xFE // MailId TBD
#define SL_PRICE_CLIENT_CTI_LIST_IND            0xFF // MailId TBD
#define SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_CNF  0x170 // OUT OF ORDER!!
#define SL_PRICE_CLIENT_EVENT_PROGRAMS_IND      0x171 // OUT OF ORDER!!
#define SL_PRICE_CLIENT_SET_EVENT_ROOTS_CNF     0x172 // OUT OF ORDER!!
#define SL_PRICE_CLIENT_EVENT_ROOTS_IND         0x173 // OUT OF ORDER!!
#define SL_PRICE_CLIENT_SET_EVENT_POLL_RATE_CNF 0x47  // OUT OF ORDER!!
/** @} */

// -------------------- Response-----------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_RESP_SERVER_RESP_IND             0xE1
#define SL_RESP_CLIENT_SEND_RESP_CNF        0x117 // MailId TBD
/** @} */

// -------------------- SDEV --------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_SDEV_CLIENT_SERVER_IND           0x13C
#define SL_SDEV_CLIENT_SERVER_SDEV_IND      0x13D
/** @} */

// -------------------- SDER --------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_SDER_CLIENT_SERVER_IND           0x13E
#define SL_SDER_CLIENT_GET_DERSETT_REQ      0x13F
#define SL_SDER_CLIENT_GET_DERSETT_CNF      0x153 // OUT OF ORDER!!
/** @} */

// -------------------- SFILE -------------------

// -------------------- Subscription ------------
/** \cond NOTRELEASED */
#define SL_SUBS_SERVER_POST_SUBS_IND        0xE6
/** \endcond */

// -------------------- Time --------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_TIME_SERVER_SET_TIME_CNF         0xE8
#define SL_TIME_CLIENT_SERVER_IND           0x13A // MailId TBD
#define SL_TIME_CLIENT_SERVER_TIME_IND      0x116 // MailId TBD
/** @} */

// -------------------- General------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_STARTUP_CNF                      0xF0
#define SL_CLIENT_DISCOVER_RESOURCES_CNF    0xDC // Out of order!
#define SL_CLIENT_SET_SERVER_CNF            0xF1
#define SL_DNS_CLIENT_CONFIG_CNF            0x151 // MailId TBD
#define SL_DNS_SERVER_CONFIG_CNF            0x115 // MailId TBD
#define SL_SEC_STORE_PRIVATE_KEY_CNF        0xAB
#define SL_SEC_STORE_CERT_CNF               0xAC // NOTE: This ID is out of order!!
#define SL_SEC_GET_SFDI_CNF                 0x7C
#define SL_SEC_STORE_ROOT_CA_CERT_CNF       0x7E
#define SL_SEC_STORE_SERVER_WHITE_LIST_CNF  0x18B // SPRK-370
#define SL_SEC_STORE_CLIENT_WHITE_LIST_CNF  0x18E // SPRK-1493
#define SL_SERVER_CONFIG_DSP_CNF            0x11F // Out of order!
/** @} */

// -------------------- Zigbee ------------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_ZB_CONFIG_BORDER_ROUTER_CNF      0xAD
#define SL_ZB_CONFIG_ROUTER_CNF             0xAE
#define SL_ZB_CONFIG_HOST_CNF               0xA8
/** @} */

// ------------------ Stack Info ----------------
/** \addtogroup MAIL_IDS
* @{ */
#define SL_STACK_INFO_REQ                   0x184
#define SL_STACK_INFO_CNF                   0x185
/** @} */

/*******************************************************************************
 * Common Typedefs
 ******************************************************************************/

/**
 * \defgroup COMMON_GROUP Common Definitions and Structures
 * This section contains common definitions and structures used across function
 * sets.
 */
/** \addtogroup COMMON_GROUP
 * @{ */

/**
 * \defgroup COMMON_GROUP_DEFINES Common Definitions
 * This section contains common definitions used across function
 * sets.
 */
/** \addtogroup COMMON_GROUP_DEFINES
 * @{ */


/**
 * Used by SEP Clients. This defines how to request "ALL" in amount or numResources
 * fields when getting a list.
 */
#define SL_CMN_CLIENT_GET_ENTIRE_LIST    (255)

/**
 * Used by SEP Clients. This defines the max number of sources of root lists
 * that can be supported (this value maps to 1 DCAP source + 1 DNS subtype source +
 * up to 6 FSA sources.
 */
#define SL_CMN_CLIENT_MAX_NUM_ROOT_SOURCES   (16)

/**
 * Used by SEP Clients. This defines the max number of programs that can be
 * supported for event processing.
 */
#define SL_CMN_CLIENT_MAX_NUM_EVENT_PROGRAMS    (25)    // SPRK-358: devices branch used (3)

/**
 * Used by SEP Clients. This defines the max number of servers that can be
 * supported for event processing per function set.
 */
#define SL_CMN_CLIENT_MAX_NUM_SERVERS           (1)

/**
 * Used by SEP Clients. This defines the max number of event roots that can
 * be supported for event processing per function set.  It is the product of
 * \ref SL_CMN_CLIENT_MAX_NUM_SERVERS and \ref SL_CMN_CLIENT_MAX_NUM_ROOT_SOURCES.
 */
#define SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS       (SL_CMN_CLIENT_MAX_NUM_SERVERS * SL_CMN_CLIENT_MAX_NUM_ROOT_SOURCES)

/**
 * Used by SEP Clients. This defines the maximum length of a server address name.
 */
#define SL_CMN_CLIENT_SERVER_NAME_LEN           (64)

/**
 * Used by SEP clients when setting server information via the
 * \ref SL_CLIENT_SET_SERVER_REQ interface.
 */
#define SL_CMN_DCAP_DEFAULT_URI   "/sep2/dcap"

/**
 * Defines maximum length of an IP address. This assumes support for IPv4 and IPv6.
 */
#define SL_CMN_IP_ADDR_LEN  (16)

/**
 * Defines the maximum number of characters in a response HREF.
 * Per the specification the max value is 255 but a smaller value is arbitrarily
 * chosen because relative URIs (as opposed to fully qualified) are assumed.
 */
#define SL_CMN_REPLY_TO_HREF_LEN     (32)
/**
 * Defines the maximum number of characters in the relative DCAP path.
 * Per the specification the max value is 255 but a smaller value is arbitrarily
 * chosen because the specification defines this as a relative path.
 */
#define SL_CMN_DCAP_PATH_LEN    (32)

/** @} */
// end addtogroup COMMON_GROUP_DEFINES


/**
 * \defgroup COMMON_GROUP_TYPES Common Types
 * This section contains common definitions used across function
 * sets.
 */
/** \addtogroup COMMON_GROUP_TYPES
 * @{ */

/******************************************************************************/
/**
 * \defgroup SL_CMN_AMOUNT_TYPE_XXX SL Common Amount types: sl_cmn_amount_type_t (SL_CMN_AMOUNT_TYPE_XXX)
 * SL Common Amounts. Defines different types of amounts of a resource that
 * can be requested. For example, EDCs can be requested by quantity (e.g.,
 * 5), or by start time (e.g., get the resources that start within the next
 * 24 hours). Generally this type is used with respect to lists that have more
 * than one resource associated with them. Note that this is an amount TYPE, and
 * the actual amount being requested is contained in a separate field.
 * Acceptable values are SL_CMN_AMOUNT_XXX as defined below.
 */
/** \addtogroup SL_CMN_AMOUNT_TYPE_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_amount_type_t
 * Acceptable values are SL_CMN_AMOUNT_TYPE_XXX.
 */
typedef u8_t sl_cmn_amount_type_t;
/**
 * Indicates that the amount of requested resources is a quantity (e.g., 10 EDCs)
 */
#define SL_CMN_AMOUNT_TYPE_QUANTITY      (0)
/**
 * Indicates that the amount of requested resources is based on time in hours
 * (e.g., send all the resources that start within the next 10 hours).
 */
#define SL_CMN_AMOUNT_TYPE_TIME_IN_HOURS (1)
/**
 * Indicates that the all of the available resources are requested. Note that
 * if this value is chosen, the associated amount field is ignored.
 */
#define SL_CMN_AMOUNT_TYPE_ALL           (255)

/** @} */


/******************************************************************************/
/**
 * \defgroup SL_CMN_CLIENT_ROOT_SOURCE_XXX SL Common Client Root List Source: sl_cmn_client_root_source_t (SL_CMN_CLIENT_ROOT_SOURCE_XXX)
 * SL Common Program Source values. Defines a bitmap of sources of a particular
 * program, depending on where the SL got the program link. The source can be
 * used by the application to determine priority. It can also be used to request
 * program information from particular sources, or all sources.
 */
/** \addtogroup SL_CMN_CLIENT_ROOT_SOURCE_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_client_root_source_t
 * Acceptable values are SL_CMN_CLIENT_ROOT_SOURCE_XXX.
 */
typedef u8_t sl_cmn_client_root_source_t;
/**
 * This bit indicates that a root source was obtained via DCAP.
 * Note that information from DCAP could have ACL applied, in which case it
 * could be private information meant specifically for a particular client. OR,
 * it could be purely public information.
 */
#define SL_CMN_CLIENT_ROOT_SOURCE_DCAP       (0x01)
/**
 * This bit indicates that a root source was obtained from a DNS
 * subtype query. This information should always be treated as public information.
 */
#define SL_CMN_CLIENT_ROOT_SOURCE_DNS        (0x02)
/**
 * This bit indicates that a root source was obtained from an FSA.
 * This information should be treated as specific to the particular client (note
 * that a server always has an option to include public list links in an FSA).
 */
#define SL_CMN_CLIENT_ROOT_SOURCE_FSA        (0x04)
/**
 * This bit indicates that a root source was obtained via the DNS DCAP key.  Note
 * that this information should always be treated as public information.
 */
#define SL_CMN_CLIENT_ROOT_SOURCE_DCAPKEY    (0x08)
/**
 * This bit indicates that a root source was obtained from a DNS sub-subtype
 * query. This information should be treated as specific to the particular client.
 */
#define SL_CMN_CLIENT_ROOT_SOURCE_SUBSUBTYPE (0x10)
/**
 * This bit indicates that a root source was obtained from an End Device (EDEV)
 * resource. This information should be treated as specific to the particular
 * client.
 */
#define SL_CMN_CLIENT_ROOT_SOURCE_EDEV       (0x20)
/**
 * This bit indicates that a root source was obtained from a Self Device (SDEV)
 * resource. This information should be treated as specific to the particular
 * client.
 */
#define SL_CMN_CLIENT_ROOT_SOURCE_SDEV       (0x40)
/** @} */

/**
 * \var typedef u32_t sl_cmn_client_server_handle_t
 * Defines a serverHandle used by a SEP2 client. This is a unique number assigned
 * by a SEP client to refer to a particular server.
 */
typedef u32_t sl_cmn_client_server_handle_t;


/******************************************************************************/
/**
 * \defgroup SL_CMN_PROG_STATUS_XXX SL Common Program Status: sl_cmn_prog_status_t (SL_CMN_PROG_STATUS_XXX)
 * SL Common Program Status values. Defines status values that are supported with respect to a
 * program (e.g., a DRLC Demand Response Program or an MSG Messaging Program).
 * Acceptable values are SL_CMN_PROG_STATUS_XXX as defined below. Note that these are
 * used across function sets.
 */
/** \addtogroup SL_CMN_PROG_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_prog_status_t
 * Acceptable values are SL_CMN_PROG_STATUS_XXX.
 */
typedef u8_t sl_cmn_prog_status_t;
  /** Indicates that a new resource has been received. */
#define SL_CMN_PROG_STATUS_RXED          (0)
  /** Indicates that a particular resource has been deleted. */
#define SL_CMN_PROG_STATUS_DELETE        (1)
/** Indicates that the sources of the program has changed. */
#define SL_CMN_PROG_STATUS_SOURCE_CHANGE (2)
/** Indicates that no programs exist. */
#define SL_CMN_PROG_STATUS_NONE          (3)
/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_CLIENT_PROG_CHANGE_XXX Root Change Type: sl_cmn_client_prog_change_t (SL_CMN_CLIENT_PROG_CHANGE_XXX)
 * Defines the reason for a change to the event programs list. Acceptable values are
 * SL_CMN_CLIENT_PROG_CHANGE_XXX as defined below.
 */
/** \addtogroup SL_CMN_CLIENT_PROG_CHANGE_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_client_prog_change_t
 * Acceptable values are SL_CMN_CLIENT_PROG_CHANGE_XXX.
 */
typedef u8_t sl_cmn_client_prog_change_t;
/**
 * The application successfully requested a change to the program list.
 */
#define SL_CMN_CLIENT_PROG_CHANGE_APP_PROGRAMS  (0)
/**
 * The application successfully requested a change to the server list and
 * therefore all programs associated with all removed servers were removed.
 */
#define SL_CMN_CLIENT_PROG_CHANGE_APP_SERVERS   (1)
/**
 * Communication with a server was lost and therefore all programs associated
 * with the lost servers were removed.
 */
#define SL_CMN_CLIENT_PROG_CHANGE_SERVER_LOST   (2)
/**
 * Server errors prevented event handling of a program and therefore the program
 * was removed from event handling.
 */
#define SL_CMN_CLIENT_PROG_CHANGE_SERVER_ERROR  (3)
/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_SERVER_STATUS_XXX SL Common Server Status: sl_cmn_server_status_t (SL_CMN_SERVER_STATUS_XXX)
 * SL Common Server Status values. Defines status values that are supported with
 * respect to a server. Acceptable values are SL_CMN_SERVER_STATUS_XXX as defined
 * below. Note that these are used across function sets.
 */
/** \addtogroup SL_CMN_SERVER_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_server_status_t
 * Acceptable values are SL_CMN_SERVER_STATUS_XXX.
 */
typedef u8_t sl_cmn_server_status_t;
/** Indicates that a new server has been found. */
#define SL_CMN_SERVER_STATUS_FOUND             (0)
/** Indicates that the time sync flag of the server has changed. */
#define SL_CMN_SERVER_STATUS_TIME_SYNC_CHANGE  (1)
/** Indicates that the registration flag of the server has changed. */
#define SL_CMN_SERVER_STATUS_REG_CHANGE        (2)
/** Indicates that the sources of the server have changed. */
#define SL_CMN_SERVER_STATUS_SOURCE_CHANGE     (3)
/** Indicates that the server has been lost. */
#define SL_CMN_SERVER_STATUS_LOST              (4)
/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_CLIENT_ROOT_CHANGE_XXX Root Change Type: sl_cmn_client_root_change_t (SL_CMN_CLIENT_ROOT_CHANGE_XXX)
 * Defines the reason for a change to the event roots list. Acceptable values are
 * SL_CMN_CLIENT_ROOT_CHANGE_XXX as defined below.
 */
/** \addtogroup SL_CMN_CLIENT_ROOT_CHANGE_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_client_root_change_t
 * Acceptable values are SL_CMN_CLIENT_ROOT_CHANGE_XXX.
 */
typedef u8_t sl_cmn_client_root_change_t;
/**
 * The function set root was found.
 */
#define SL_CMN_CLIENT_ROOT_CHANGE_FOUND              (0)
/**
 * The SL client successfully received the time resource associated with this
 * root.  Only roots that are time synced may be set for event processing in
 * \ref sl_cmn_client_set_event_roots_req_t.
 */
#define SL_CMN_CLIENT_ROOT_CHANGE_TIME_SYNCED        (1)
/**
 * Communication with the function set server for this root was lost.
 */
#define SL_CMN_CLIENT_ROOT_CHANGE_LOST               (2)
/**
 * The client successfully registered on the server for this root.
 */
#define SL_CMN_CLIENT_ROOT_CHANGE_REGISTERED         (3)
/**
 * The application changed the list of roots set for event processing.
 */
#define SL_CMN_CLIENT_ROOT_CHANGE_APP_SELECTION      (4)
/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_LIST_AMOUNT_TYPE_XXX SL Common Amount types: sl_cmn_list_amount_type_t (SL_CMN_LIST_AMOUNT_TYPE_XXX)
 * SL Common List Amounts. Defines different types of list amounts of a resource
 * that can be requested. For example, RSETs can be requested by quantity (e.g.,
 * 5), or by time range (e.g., get the resources with start time between 2pm and
 * 4pm). Note that this is an amount TYPE, and the actual amount being requested
 * is contained in a separate field.
 * Acceptable values are SL_CMN_LIST_AMOUNT_XXX as defined below.
 */
/** \addtogroup SL_CMN_LIST_AMOUNT_TYPE_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_list_amount_type_t
 * Acceptable values are SL_CMN_LIST_AMOUNT_TYPE_XXX.
 */
typedef u8_t sl_cmn_list_amount_type_t;
/**
 * Indicates that the amount of requested resources is a quantity (e.g., 10 RCs)
 * starting from the beginning of the resource list.  Note that if this value
 * is chosen, the \ref sl_cmn_get_list_req_time_t::numMinutes, \ref sl_cmn_get_list_req_time_t::startRange,
 * and \ref sl_cmn_get_list_req_time_t::endRange fields are ignored.
 */
#define SL_CMN_LIST_AMOUNT_TYPE_QUANTITY               (0)
/**
 * Indicates that the amount of requested resources is based on quantity and a
 * limited number of minutes.  The quantity is defined by \ref sl_cmn_get_list_req_time_t::numResources
 * and the number of minutes is defined by \ref sl_cmn_get_list_req_time_t::numMinutes
 * (e.g., send the first 10 resources in the list that have a start time greater
 * than now minus 210 minutes). The number of minutes will be in the future or the
 * past based on whether the list is specified to be sorted in ascending or descending
 * order.  If the list is specified to be sorted in ascending order the number of
 * minutes will be in the future (now plus numMinutes).  If the list is specified
 * to be sorted in descending order the number of minutes will be in the past
 * (now minus numMinutes).
 *
 * If this value is chosen, the \ref sl_cmn_get_list_req_time_t::startRange and
 * \ref sl_cmn_get_list_req_time_t::endRange fields are ignored. Note that to
 * request all resources within the specified number of minutes, the
 * \ref sl_cmn_get_list_req_time_t::numResources field must be set to
 * \ref SL_CMN_CLIENT_GET_ENTIRE_LIST.
 */
#define SL_CMN_LIST_AMOUNT_TYPE_TIME_IN_MINUTES        (1)
/**
 * Indicates that the amount of requested resources is based on quantity and a
 * limited time range.  The time range is defined by \ref sl_cmn_get_list_req_time_t::startRange
 * and \ref sl_cmn_get_list_req_time_t::endRange (e.g, send the first 10 resources
 * that have a start time between 2:00pm and 4:00pm).
 *
 * If this value is chosen, the \ref sl_cmn_get_list_req_time_t::numMinutes field
 * is ignored.  Note that to request all resources within the specified time range,
 * the \ref sl_cmn_get_list_req_time_t::numResources field must be set to
 * \ref SL_CMN_CLIENT_GET_ENTIRE_LIST.
 */
#define SL_CMN_LIST_AMOUNT_TYPE_TIME_RANGE             (2)

/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_RC_XXX SL Common Return Codes: sl_cmn_rc_t (SL_CMN_RC_XXX)
 * SL Common Return Codes. This type is used to return information on the
 * result of a request to the application. Generally, negative numbers refer
 * to failure cases and non-negative numbers refer to non-error cases.
 * Note that additional return codes may be defined in the future. Acceptable
 * values are SL_CMN_RC_XXX as defined below.
 */
/** \addtogroup SL_CMN_RC_XXX
* @{ */
/**
 * \var typedef i8_t sl_cmn_rc_t
 * Acceptable values are SL_CMN_RC_XXX.
 */
/**
 * \def SL_CMN_RC_SUCCESS
 *  Operation was a success.
 * \def SL_CMN_RC_OPERATION_IN_PROG
 *  Operation is still in progress without errors. This code is used for non-atomic
 *  operations that may require multiple mail messages in response.
 * \def SL_CMN_RC_OPERATION_DONE
 *  Operation is complete without errors. This code is used for non-atomic
 *  operations that may require multiple mail messages in response.
 * \def SL_CMN_RC_RETRYING
 * Operation is still in progress and a retry is under way.
 * \def SL_CMN_RC_FAIL
 *  Operation failed.
 *  No further details are available on the operation.
 * \def SL_CMN_RC_FILE_EXISTS
 *  Operation failed because the XML file already exists.
 * \def SL_CMN_RC_FILE_DOES_NOT_EXIST
 *  Operation failed because the XML file already exists.
 * \def SL_CMN_RC_NOT_ALLOWED
 * Operation failed because operation is not allowed.
 * \def SL_CMN_RC_FS_FULL
 * Operation failed because the file system is full.
 * \def SL_CMN_RC_METHOD_NOT_ALLOWED
 * Operation failed because the the requested method is not allowed.
 * \def SL_CMN_RC_TIMEOUT
 * Operation failed due to timeout talking to server.
 * \def SL_CMN_RC_NO_SERVER
 * Operation failed because there is no server.
 * \def SL_CMN_RC_MEMORY_ALLOC_FAIL
 * Operation failed because memory could not be allocated for the operation.
 * \def SL_CMN_RC_DATA_INTEGRITY_FAIL
 * Operation failed because a data storage inconsistency was detected.
 * \def SL_CMN_RC_READ_ONLY
 * Write operation failed because the data is marked as read only.
 * \def SL_CMN_RC_DATA_LOCKED
 * Operation failed because the data is locked.
 * \def SL_CMN_RC_NOT_SUPPORTED
 * Operation failed because the operation is not supported (or not configured).
 * \def SL_CMN_RC_MRID_MISMATCH
 * Operation failed because the requested mRID does not match the stored mRID.
 * Used when resources are being overwritten.
 */
typedef i8_t sl_cmn_rc_t;
#define SL_CMN_RC_SUCCESS              (0)
#define SL_CMN_RC_OPERATION_IN_PROG    (1)
#define SL_CMN_RC_OPERATION_DONE       (2)
#define SL_CMN_RC_RETRYING             (3)
#define SL_CMN_RC_FAIL                (-1)
#define SL_CMN_RC_FILE_EXISTS         (-2)
#define SL_CMN_RC_FILE_DOES_NOT_EXIST (-3)
#define SL_CMN_RC_NOT_ALLOWED         (-4)
#define SL_CMN_RC_FS_FULL             (-5)
#define SL_CMN_RC_METHOD_NOT_ALLOWED  (-6)
#define SL_CMN_RC_TIMEOUT             (-7)
#define SL_CMN_RC_NO_SERVER           (-8)
#define SL_CMN_RC_RX_DATA_TOO_BIG     (-9)
#define SL_CMN_RC_INVALID_PARAMETERS  (-10)
#define SL_CMN_RC_NOT_ACCEPTABLE      (-11)
#define SL_CMN_RC_MEMORY_ALLOC_FAIL   (-12)
#define SL_CMN_RC_DATA_INTEGRITY_FAIL (-13)
#define SL_CMN_RC_READ_ONLY           (-14)
#define SL_CMN_RC_DATA_LOCKED         (-15)
#define SL_CMN_RC_NOT_SUPPORTED       (-16)
#define SL_CMN_RC_MRID_MISMATCH       (-17)

/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_SCHEME_XXX SL Scheme: sl_cmn_scheme_t (SL_CMN_SCHEME_XXX)
 * SL Scheme. Defines HTTP sheme.
 */
/** \addtogroup SL_CMN_SCHEME_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_scheme_t
 * Acceptable values are SL_CMN_SCHEME_XXX.
 */
typedef u8_t sl_cmn_scheme_t;
/**
 * Uses HTTP (non secure)
 */
#define SL_CMN_SCHEME_HTTP (0)
/**
 * Uses HTTPS (secure)
 */
#define SL_CMN_SCHEME_HTTPS (1)
/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_IP_VERSION_XXX SL IP Version: sl_cmn_ip_version_t (SL_CMN_IP_VERSION_XXX)
 * SL IP Version. This defined the particular IP version to be used for a given
 * operation or event.
 */
/** \addtogroup SL_CMN_IP_VERSION_XXX
* @{ */
/**
 * \var typedef u8_t sl_cmn_ip_version_t
 * Acceptable values are SL_CMN_IP_VERSION_XXX.
 */
typedef u8_t sl_cmn_ip_version_t;
/**
 * IPv4
 */
#define SL_CMN_IP_V4  (0)
/**
 * IPv6
 */
#define SL_CMN_IP_V6  (1)
/** @} */

/******************************************************************************/
/**
 * \defgroup SL_CMN_SECURITY_XXX Security Definitions.
 */
/** \addtogroup SL_CMN_SECURITY_XXX
* @{ */
/**
 * Certificate chain format. PKCS7 enumeration.
 */
#define SL_CMN_SECURITY_CERT_CHAIN_PKCS7 (0)
/**
 * Certificate chain format. PEM enumeration.
 */
#define SL_CMN_SECURITY_CERT_CHAIN_PEM (1)
/**
 * Certificate chain format. TLS enumeration.
 */
#define SL_CMN_SECURITY_CERT_CHAIN_TLS (2)
/**
 * Private Key format. PKCS8 enumeration.
 */
#define SL_CMN_SECURITY_PRIVATE_KEY_PKCS8 (0)
/**
 * Private Key format. Basic EC enumeration.
 */
#define SL_CMN_SECURITY_PRIVATE_KEY_BASIC_EC (1)
/** @} */

/** @} */
// end addtogroup COMMON_GROUP_TYPES

/**
 * \defgroup COMMON_GROUP_STRUCTS Common Structures
 * This section contains common structures used across function
 * sets.
 */
/** \addtogroup COMMON_GROUP_STRUCTS
 * @{ */

typedef u16_t sl_fsa_id_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_root_source_info_t
 * Defines the source of a top level list or resource such as a DRP or UPT.
 * The fsaId is only valid if the \ref source bitmap includes \ref SL_CMN_CLIENT_ROOT_SOURCE_FSA.
 */
typedef struct {
  /**
   * Source of the program information/link. This can be any combination of
   * DCAP, DNS, or FSA.
   */
  sl_cmn_client_root_source_t   source;
  /**
   * A bitmap of fsaIds that are associated with this resource/list.
   * This field is only valid if the \ref source bitmap includes
   * \ref SL_CMN_CLIENT_ROOT_SOURCE_FSA.
   */
  sl_fsa_id_t                   fsaId;
} sl_cmn_client_root_source_info_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_server_source_info_t
 * Defines the server and source of a top level list or resource such as a
 * DRP or UPT. The \ref sl_cmn_client_root_source_info_t::fsaId is only valid
 * if the \ref sl_cmn_client_root_source_info_t::source bitmap includes
 * \ref SL_CMN_CLIENT_ROOT_SOURCE_FSA.
 */
typedef struct {
  /**
   * Handle referring to the specific server that this resource or top level list
   * is served from.
   */
  sl_cmn_client_server_handle_t    serverHandle;
  /**
   * Specific source of the resource or top level list.
   */
  sl_cmn_client_root_source_info_t source;
} sl_cmn_client_server_source_info_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_root_info_t
 * Defines the source and time capability of a function set root.  The root is the
 * top level program or resource of the function set. The fsaId is only valid if
 * the \ref source bitmap includes \ref SL_CMN_CLIENT_ROOT_SOURCE_FSA.
 */
typedef struct {
  /**
   * Source of the program information/link. This can be any combination of
   * DCAP, DNS, or FSA.
   */
  sl_cmn_client_root_source_t   source;
  /**
   * A bitmap of fsaIds that are associated with this program information/link.
   * This field is only valid if the \ref source bitmap includes
   * \ref SL_CMN_CLIENT_ROOT_SOURCE_FSA.
   */
  sl_fsa_id_t                   fsaId;
  /**
   * A flag indicating if the SL client has successfully received an appropriate time
   * resource associated with this program information/link.
   */
  bool                          timeSynced;
} sl_cmn_client_root_info_t;

/** @} */
// end addtogroup COMMON_GROUP_STRUCTS

/** @} */
// end addtogroup COMMON_GROUP

/*******************************************************************************
 * XSD Typedefs
 ******************************************************************************/

/**
 * \defgroup XSD_GROUP XSD Definitions and Structures
 * This section contains definitions and structures used on the SL API that
 * are defined in the SEP XSD.
 */
/** \addtogroup XSD_GROUP
 * @{ */

// XSD Array Lengths
/**
 * \defgroup XSD_GROUP_ARRAY_LENS XSD Array Lengths
 * The following array length definitions are used on the SL API. These lengths
 * are defined in the specification [ZB-SEP2-XSD].
 */
/** \addtogroup XSD_GROUP_ARRAY_LENS
 * @{ */

/**
 * Character string of maximum 16 characters in size.
 */
#define SL_XSD_STRING16_LEN     (16)
/**
 * Character string of maximum 20 characters in size.
 */
#define SL_XSD_STRING20_LEN     (20)
/**
 * Character string of maximum 32 characters in size.
 */
#define SL_XSD_STRING32_LEN     (32)
/**
 * Character string of maximum 42 characters in size.
 */
#define SL_XSD_STRING42_LEN     (42)
/**
 * Character string of maximum 192 characters in size.
 */
#define SL_XSD_STRING192_LEN    (192)
/**
 * Maximum number of characters in the description field.
 */
#define SL_XSD_DESCRIPTION_LEN  (32)
/**
 * Maximum number of characters in the details field.
 */
#define SL_XSD_DETAILS_LEN      (32)
/**
 * Maximum number of characters in the lat and lon fields of GPS Location.
 */
#define SL_XSD_GPSLOCATION_LEN  (32)
/**
 * Length of the IP Address array.
 */
#define SL_XSD_IPADDR_LEN       (16)
/**
 * Maximum number of characters in a link.
 */
#define SL_XSD_LINK_LEN         (32)
/**
 * Length of the LFDI array.
 */
#define SL_XSD_LFDI_LEN         (20)
/**
 * Length of the MRID array.
 */
#define SL_XSD_MRID_LEN         (16)
/**
 * Maximum number of characters in the reason field.
 */
#define SL_XSD_REASON_LEN       (192)
/**
 * Maximum number of characters in the locale type field.
 */
#define SL_XSD_LOCALE_MAX_LEN    (42)
/**
 * Maximum number of characters in the message originator field.
 */
#define SL_XSD_MSG_ORIG_MAX_LEN  (20)
/**
 * Maximum number of characters in the quality type field.
 */
#define SL_XSD_QUALITY_LEN       (6)
/**
 * Maximum number of characters in the token field.
 */
#define SL_XSD_TOKEN_MAX_LEN     (32)
/**
 * Maximum number of characters in the value type field.
 */
#define SL_XSD_VALUE_LEN         (6)
/**
 * Maximum number of characters in the rate code field.
 */
#define SL_XSD_RATECODE_LEN    	 (20)
/**
 * Length of the Response Subject field (note that this is an mRID).
 */
 #define SL_XSD_RESP_SUBJ_LEN    (SL_XSD_MRID_LEN)

/** @} */
// end addtogroup XSD_GROUP_ARRAY_LENS

/**
 * \defgroup XSD_GROUP_TYPES XSD Types
 * This section contains types used on the SL API that
 * are defined in the SEP XSD.
 */
/** \addtogroup XSD_GROUP_TYPES
 * @{ */



// XSD AccumulationBehaviourType
/******************************************************************************/
/**
 * \defgroup SL_XSD_AB_XXX XSD Accumulation Behavior Type: sl_xsd_acc_behavior_type_t (SL_XSD_AB_XXX)
 * The accumulation behavior indicates how the value is represented to
 * accumulate over time.
 * Acceptable values are SL_XSD_AB_XXX as defined below.
 */
/** \addtogroup SL_XSD_AB_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_acc_behavior_type_t
 * Acceptable values are SL_XSD_AB_XXX.
 */
typedef u8_t sl_xsd_acc_behavior_type_t;
/**
 * Accumulation behavior is not applicable (default, if not specified)
 */
#define SL_XSD_AB_NOT_APPL          (0)
#define SL_XSD_AB_BULK              (1)
#define SL_XSD_AB_CUMULATIVE        (3)
#define SL_XSD_AB_DELTA             (4)
#define SL_XSD_AB_INDICATING        (6)
#define SL_XSD_AB_SUMMATION         (9)
#define SL_XSD_AB_INSTANTANEOUS     (12)
/**
 * Indicates that the accumulation behavior field is not in use. This is
 * a valid value if the accumulation behavior field is optional for the
 * particular resource.
 */
#define SL_XSD_AB_NOT_USED          (0xFF)
/** @} */

// XSD ApplianceLoadReductionType
/******************************************************************************/
/**
 * \defgroup SL_XSD_APP_LOAD_RED_XXX XSD Appliance Load Reduction Type: sl_xsd_appliance_load_red_type_t (SL_XSD_APP_LOAD_RED_XXX)
 * The ApplianceLoadReduction object is used by a Demand Response service
 * provider to provide signals for ENERGY STAR compliant appliances.
 *
 * Acceptable values are SL_XSD_APP_LOAD_RED_XXX as defined below.
 */
/** \addtogroup SL_XSD_APP_LOAD_RED_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_appliance_load_red_type_t
 * Acceptable values are SL_XSD_APP_LOAD_RED_XXX.
 */
typedef u8_t sl_xsd_appliance_load_red_type_t;
/**
 * Parameter requesting the appliance to respond by providing a moderate
 * load reduction for the duration of a delay period.  Typically referring
 * to a non-emergency event in which appliances can continue operating
 * if already in a load consuming period.
 */
#define SL_XSD_APP_LOAD_RED_DELAY          (0)
/**
 * Parameter requesting the appliance to respond by providing an aggressive
 * load reduction for a short time period.  Typically referring to an
 * emergency/spinning reserved event in which an appliance should start
 * shedding load if currently in a load consuming period.
 */
#define SL_XSD_APP_LOAD_RED_TEMPORARY      (1)
/**
 * Indicates that the appliance load reduction field is not in use. This is
 * a valid value if the appliance load reduction field is optional for the
 * particular resource.
 */
#define SL_XSD_APP_LOAD_RED_NOT_USED       (0xFF)
/** @} */

// XSD Battery status
/******************************************************************************/
/**
 * \defgroup SL_XSD_BATTERY_STATUS_XXX XSD Battery Status: sl_xsd_battery_status_t (SL_XSD_BATTERY_STATUS_XXX)
 * System battery status.
 * Acceptable values are SL_XSD_BATTERY_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_BATTERY_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_battery_status_t
 * Acceptable values are SL_XSD_BATTERY_STATUS_XXX.
 */
typedef u8_t sl_xsd_battery_status_t;
/** Unknown. */
#define SL_XSD_BATTERY_STATUS_UNKNOWN   (0)
/** More than LowChargeThreshold remaining */
#define SL_XSD_BATTERY_STATUS_NORMAL    (1)
/** Less than LowChargeThreshold remaining */
#define SL_XSD_BATTERY_STATUS_LOW       (2)
/** 0% charge remaining */
#define SL_XSD_BATTERY_STATUS_DEPELETED (3)
/** Mains powered only */
#define SL_XSD_BATTERY_STATUS_NA        (4)
/** @} */

// XSD CommodityType
/******************************************************************************/
/**
 * \defgroup SL_XSD_COMMODITY_XXX XSD Commodity Type: sl_xsd_commodity_type_t (SL_XSD_COMMODITY_XXX)
 * Indicates the commodity applicable to a reading type.
 * Acceptable values are SL_XSD_COMMODITY_XXX as defined below.
 */
/** \addtogroup SL_XSD_COMMODITY_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_commodity_type_t
 * Acceptable values are SL_XSD_COMMODITY_XXX.
 */
typedef u8_t sl_xsd_commodity_type_t;
/**
 * Not applicable (default, if not specified)
 */
#define SL_XSD_COMMODITY_NOT_APPL        (0)
/**
 * Electricity secondary metered value (a premises meter is typically a secondary meter)
 */
#define SL_XSD_COMMODITY_ELEC_SECOND     (1)
/**
 * Electricity primary metered value
 */
#define SL_XSD_COMMODITY_ELEC_PRIMARY    (2)
#define SL_XSD_COMMODITY_AIR             (4)
#define SL_XSD_COMMODITY_GAS             (7)
#define SL_XSD_COMMODITY_PROPANE         (8)
#define SL_XSD_COMMODITY_POTABLE_WATER   (9)
#define SL_XSD_COMMODITY_STEAM           (10)
#define SL_XSD_COMMODITY_WASTE_WATER     (11)
#define SL_XSD_COMMODITY_HEAT_FLUID      (12)
#define SL_XSD_COMMODITY_COOL_FLUID      (13)
/**
 * Indicates that the commodity field is not in use. This is
 * a valid value if the commodity field is optional for the
 * particular resource.
 */
#define SL_XSD_COMMODITY_NOT_USED        (0xFF)
/** @} */

// XSD ConnectStatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_CONN_STATUS_XXX XSD Connect Status Type: sl_xsd_conn_status_t (SL_XSD_CONN_STATUS_XXX)
 * Indicates the DER Connect Status.
 *
 * Bitmap values are SL_XSD_CONN_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_CONN_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_conn_status_t
 * Acceptable bitmap values are SL_XSD_CONN_STATUS_XXX.
 */
typedef u8_t sl_xsd_conn_status_t;
/**
 * Not applicable (default, if not specified)
 */
#define SL_XSD_CONN_STATUS_NA             (0x00)
/**
 * Connected
 */
#define SL_XSD_CONN_STATUS_CONNECTED      (0x01)
/**
 * Available
 */
#define SL_XSD_CONN_STATUS_AVAILABLE      (0x02)
/**
 * Operating
 */
#define SL_XSD_CONN_STATUS_OPERATING      (0x04)
/**
 * Test
 */
#define SL_XSD_CONN_STATUS_TEST           (0x08)
/**
 * Fault/Error
 */
#define SL_XSD_CONN_STATUS_FAULT          (0x10)
/**
 * All other values reserved.
 */

/** @} */

// XSD ConsumptionBlockType
/******************************************************************************/
/**
 * \defgroup SL_XSD_CONS_BLOCK_XXX XSD Consumption Block Type: sl_xsd_cons_block_type_t (SL_XSD_CONS_BLOCK_XXX)
 * Indicates the type of consumption block associated with a particular resource.
 * These block types are defined by number, and the characteristics of each
 * particular block type are outside the scope of this document.
 *
 * Values are SL_XSD_CONS_BLOCK_XXX as defined below.
 */
/** \addtogroup SL_XSD_CONS_BLOCK_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_cons_block_type_t
 * Acceptable values are SL_XSD_CONS_BLOCK_XXX.
 */
typedef u8_t sl_xsd_cons_block_type_t;
/**
 * Not applicable (default, if not specified)
 */
#define SL_XSD_CONS_BLOCK_TYPE_DEFAULT (0)
/** Block 1 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK1  (1)
/** Block 2 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK2  (2)
/** Block 3 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK3  (3)
/** Block 4 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK4  (4)
/** Block 5 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK5  (5)
/** Block 6 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK6  (6)
/** Block 7 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK7  (7)
/** Block 8 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK8  (8)
/** Block 9 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK9  (9)
/** Block 10 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK10 (10)
/** Block 11 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK11 (11)
/** Block 12 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK12 (12)
/** Block 13 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK13 (13)
/** Block 14 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK14 (14)
/** Block 15 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK15 (15)
/** Block 16 */
#define SL_XSD_CONS_BLOCK_TYPE_BLOCK16 (16)
/** @} */

// XSD CostKindType
/******************************************************************************/
/**
 * \defgroup SL_XSD_COST_XXX XSD Cost Kind Type: sl_xsd_cost_kind_type_t (SL_XSD_COST_XXX)
 * The kind of cost referred to in a particular amount.
 *
 * Values are SL_XSD_COST_XXX as defined below.
 */
/** \addtogroup SL_XSD_COST_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_cost_kind_type_t
 * Acceptable values are SL_XSD_COST_XXX.
 */
typedef u8_t sl_xsd_cost_kind_type_t;
/**
 * Refers to Carbon Dioxide emissions, in grams per unit.
 */
#define SL_XSD_COST_CARBON_DIOXIDE  (0)
/**
 * Refers to Sulfur Dioxide emissions, in grams per unit.
 */
#define SL_XSD_COST_SULFER_DIOXIDE  (1)
/**
 * Refers to Nitrogen Oxides emissions, in grams per unit.
 */
#define SL_XSD_COST_NITROGEN_OXIDE  (2)
/**
 * Refers to renewable generation, as a percentage of overall generation.
 */
#define SL_XSD_COST_RENEWABLE       (3)
/** @} */

// XSD CreditStatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_CRED_STAT_XXX XSD Credit Status Type: sl_xsd_cred_stat_t (SL_XSD_CRED_STAT_XXX)
 * Indicates the current status of a particular type of credit associated
 * with a prepayment account (available credit or emergency credit).
 *
 * Values are SL_XSD_CRED_STAT_XXX as defined below.
 */
/** \addtogroup SL_XSD_CRED_STAT_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_cred_stat_t
 * Acceptable values are SL_XSD_CRED_STAT_XXX.
 */
typedef u8_t sl_xsd_cred_stat_t;
#define SL_XSD_CRED_STAT_OK        (0)
#define SL_XSD_CRED_STAT_LOW       (1)
#define SL_XSD_CRED_STAT_EXHAUSTED (2)
#define SL_XSD_CRED_STAT_NEGATIVE  (3)
/** @} */

// XSD CreditTypeType
/******************************************************************************/
/**
 * \defgroup SL_XSD_CRED_TYPE_XXX XSD Credit Type Type: sl_xsd_cred_type_t (SL_XSD_CRED_TYPE_XXX)
 * Indicates the type of credit being referred to (regular, emergency, or
 * a combination of both).
 *
 * Values are SL_XSD_CRED_TYPE_XXX as defined below.
 */
/** \addtogroup SL_XSD_CRED_TYPE_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_cred_type_t
 * Acceptable values are SL_XSD_CRED_TYPE_XXX.
 */
typedef u8_t sl_xsd_cred_type_t;
/**
 * Credit type is regular.
 */
#define SL_XSD_CRED_TYPE_REG            (0)
/**
 * Credit type is emergency.
 */
#define SL_XSD_CRED_TYPE_EMERG          (1)
/**
 * Credit type is regular followed by emergency.
 */
#define SL_XSD_CRED_TYPE_REG_THEN_EMERG (2)
/**
 * Credit type is emergency followed by regular.
 */
#define SL_XSD_CRED_TYPE_EMERG_THEN_REQ (3)
/** @} */

// XSD CurrencyCodeType
/******************************************************************************/
/**
 * \defgroup SL_XSD_CURR_XXX XSD Currency Code Type: sl_xsd_curr_code_t (SL_XSD_CURR_XXX)
 * Defines currency codes based on codes defined in ISO 4217. Full list at
 * http://www.currency-iso.org/
 *
 * Values are SL_XSD_CURR_XXX as defined below.
 */
/** \addtogroup SL_XSD_CURR_XXX
* @{ */
/**
 * \var typedef i8_t sl_xsd_curr_code_t
 * Acceptable values are SL_XSD_CURR_XXX.
 */
typedef u16_t sl_xsd_curr_code_t;
#define SL_XSD_CURR_NOT_APPL        (0)
#define SL_XSD_CURR_AUSTRALIA       (36)
#define SL_XSD_CURR_CANADA          (124)
#define SL_XSD_CURR_US              (840)
#define SL_XSD_CURR_EURO            (978)
/**
 * Indicates that the currency field is not in use. This is
 * a valid value if the currency field is optional for the
 * particular resource.
 */
#define SL_XSD_CURR_NOT_USED        (0xFFFF)
/** @} */

// XSD CurrencyCodeType
/******************************************************************************/
/**
 * \defgroup SL_XSD_CURVE_TYPE_XXX XSD Curve Type: sl_xsd_curve_type_t (SL_XSD_CURVE_TYPE_XXX)
 * Defines the type of curve represented by the curve data.
 *
 * Values are SL_XSD_CURVE_TYPE_XXX as defined below.
 */
/** \addtogroup SL_XSD_CURVE_TYPE_XXX
* @{ */
/**
 * \var typedef i8_t sl_xsd_curve_type_t
 * Acceptable values are SL_XSD_CURVE_TYPE_XXX.
 */
typedef u16_t sl_xsd_curve_type_t;

/**
 * Frequency-Watt Curve Mode
 */
#define SL_XSD_CURVE_TYPE_FREQ_WATT            (0)
/**
 * High Frequency Ride Through, May Trip Mode
 */
#define SL_XSD_CURVE_TYPE_HFRT_MAY_TRIP        (1)
/**
 * High Frequency Ride Through, Must Trip Mode
 */
#define SL_XSD_CURVE_TYPE_HFRT_MUST_TRIP       (2)
/**
 * High Voltage Ride Through, May Trip Mode
 */
#define SL_XSD_CURVE_TYPE_HVRT_MAY_TRIP        (3)
/**
 * High Voltage Ride Through, Momentary Cessation Mode
 */
#define SL_XSD_CURVE_TYPE_HVRT_MOM_CESS        (4)
/**
 * High Voltage Ride Through, Must Trip Mode
 */
#define SL_XSD_CURVE_TYPE_HVRT_MUST_TRIP       (5)
/**
 * Low Frequency Ride Through, May Trip Mode
 */
#define SL_XSD_CURVE_TYPE_LFRT_MAY_TRIP        (6)
/**
 * Low Frequency Ride Through, Must Trip Mode
 */
#define SL_XSD_CURVE_TYPE_LFRT_MUST_TRIP       (7)
/**
 * Low Voltage Ride Through, May Trip Mode
 */
#define SL_XSD_CURVE_TYPE_LVRT_MAY_TRIP        (8)
/**
 * Low Voltage Ride Through, Momentary Cessation Mode
 */
#define SL_XSD_CURVE_TYPE_LVRT_MOM_CESS        (9)
/**
 * Low Voltage Ride Through, Must Trip Mode
 */
#define SL_XSD_CURVE_TYPE_LVRT_MUST_TRIP       (10)
/**
 * Volt-Var Curve Mode
 */
#define SL_XSD_CURVE_TYPE_VOLT_VAR             (11)
/**
 * Volt-Watt Mode
 */
#define SL_XSD_CURVE_TYPE_VOLT_WATT            (12)
/**
 * Watt-PowerFactor mode
 */
#define SL_XSD_CURVE_TYPE_WATT_PWR_FACTOR      (13)
/**
 * Watt-Var Mode
 */
#define SL_XSD_CURVE_TYPE_WATT_VAR             (14)

/** @} */

// XSD DataQualifierType
/******************************************************************************/
/**
 * \defgroup SL_XSD_DATA_QUAL_XXX XSD Data Qualifier Type: sl_xsd_data_qual_type_t (SL_XSD_DATA_QUAL_XXX)
 * The data type can be used to describe a salient attribute of the data.
 * Possible values are average, absolute, and etc.
 * Acceptable values are SL_XSD_DATA_QUAL_XXX as defined below.
 */
/** \addtogroup SL_XSD_DATA_QUAL_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_data_qual_type_t
 * Acceptable values are SL_XSD_DATA_QUAL_XXX.
 */
typedef u8_t sl_xsd_data_qual_type_t;
/**
 * Not applicable (default, if not specified).
 */
#define SL_XSD_DATA_QUAL_NOT_APPL          (0)
/**
 * Data is averaged.
 */
#define SL_XSD_DATA_QUAL_AVERAGE           (2)
/**
 * Value is a maximum data value.
 */
#define SL_XSD_DATA_QUAL_MAX               (8)
/**
 * Value is a minimum data value.
 */
#define SL_XSD_DATA_QUAL_MIN               (9)
/**
 * Data is normalized.
 */
#define SL_XSD_DATA_QUAL_NORMAL            (12)
/**
 * Value is standard deviation of population.
 */
#define SL_XSD_DATA_QUAL_STD_DEV_POPULATION (29)
/**
 * Value is standard deviation of sample.
 */
#define SL_XSD_DATA_QUAL_STD_DEV_SAMPLE     (30)
/**
 * Indicates that the data qualifier field is not in use. This is
 * a valid value if the data qualifier field is optional for the
 * particular resource.
 */
#define SL_XSD_DATA_QUAL_NOT_USED          (0xFF)
/** @} */

// XSD DERUnitRefType
/******************************************************************************/
/**
 * \defgroup SL_XSD_DERREF_XXX XSD Unit Type: sl_xsd_der_ref_t (SL_XSD_DERREF_XXX)
 * Defines the type of units for a particular value. Acceptable values are
 * SL_XSD_DERREF_XXX as defined below.
 */
/** \addtogroup SL_XSD_DERREF_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_der_ref_t
 * Acceptable values are SL_XSD_DERREF_XXX.
 */
typedef u8_t sl_xsd_der_ref_t;
/**
 * Not applicable
 */
#define SL_XSD_DERREF_NOT_APPL            (0)
/**
 * %setMaxW
 */
#define SL_XSD_DERREF_PERC_SET_MAX_W      (1)
/**
 * %setMaxVar
 */
#define SL_XSD_DERREF_PERC_SET_MAX_VAR    (2)
/**
 * %statVarAvailable
 */
#define SL_XSD_DERREF_PERC_STAT_VAR_AVAIL (3)
/**
 * %setEffectiveV
 */
#define SL_XSD_DERREF_EFFECTIVE_V         (4)
/**
 * %setMaxChargeRate
 */
#define SL_XSD_DERREF_MAX_CHARGE_RATE     (5)
/**
 * %setMaxDischargeRate
 */
#define SL_XSD_DERREF_MAX_DISCHARGE_RATE  (6)
/**
 * %statWAvailable
 */
#define SL_XSD_DERREF_PERC_STAT_W_AVAIL   (7)
/**
 * All other values are reserved.
 */

/** @} */

// XSD DERControlType
/******************************************************************************/
/**
 * \defgroup SL_XSD_DER_CONT_XXX XSD DER Control Type: sl_xsd_der_cont_t (SL_XSD_DER_CONT_XXX)
 * Define the Control modes supported by the DER.
 *
 * Values are SL_XSD_DER_CONT_XXX as defined below.
 */
/** \addtogroup SL_XSD_DER_CONT_XXX
* @{ */
/**
 * \var typedef u32_t sl_xsd_der_cont_t
 * Acceptable values are SL_XSD_DER_CONT_XXX.
 */
typedef u32_t sl_xsd_der_cont_t;
/**
 * Charge mode
 */
#define SL_XSD_DER_CONT_CHARGE_MODE           (0x00000001)
/**
 * Discharge mode
 */
#define SL_XSD_DER_CONT_DISCHARGE_MODE        (0x00000002)
/**
 * Connect / Disconnect - implies galvanic isolation
 */
#define SL_XSD_DER_CONT_CONNECT               (0x00000004)
/**
 * Energize / De-Energize
 */
#define SL_XSD_DER_CONT_ENERGIZE              (0x00000008)
/**
 * Fixed Power Factor AbsorbW Setpoint
 */
#define SL_XSD_DER_CONT_FIXED_PF_ABSORBW_SP   (0x00000010)
/**
 * Fixed Power Factor InjectW Setpoint
 */
#define SL_XSD_DER_CONT_FIXED_PF_INJECTW_SP   (0x00000020)
/**
 * Reactive Power Setpoint
 */
#define SL_XSD_DER_CONT_FIXED_VAR_SP          (0x00000040)
/**
 * Charge / Discharge Setpoint
 */
#define SL_XSD_DER_CONT_FIXED_W               (0x00000080)
/**
 * Frequency-Watt Parameterized Mode
 */
#define SL_XSD_DER_CONT_FREQ_DROOP_MODE       (0x00000100)
/**
 * Frequency-Watt Curve Mode
 */
#define SL_XSD_DER_CONT_FREQ_WATT_MODE        (0x00000200)
/**
 * High Frequency Ride Through, Must Trip Mode
 */
#define SL_XSD_DER_CONT_HFRT_MAY_TRP_MODE     (0x00000400)
/**
 * High Frequency Ride Through, Must Trip Mode
 */
#define SL_XSD_DER_CONT_HFRT_MUST_TRP_MODE    (0x00000800)
/**
 * High Voltage Ride Through, May Trip Mode
 */
#define SL_XSD_DER_CONT_HVRT_MAY_TRP_MODE     (0x00001000)
/**
 * High Voltage Ride Through, Momentary Cessation Mode
 */
#define SL_XSD_DER_CONT_HVRT_MOM_CESS_MODE    (0x00002000)
/**
 * High Voltage Ride Through, Must Trip Mode
 */
#define SL_XSD_DER_CONT_HVRT_MUST_TRP_MODE    (0x00004000)
/**
 * Low Frequency Ride Through, May Trip Mode
 */
#define SL_XSD_DER_CONT_LFRT_MAY_TRP_MODE     (0x00008000)
/**
 * Low Frequency Ride Through, Must Trip Mode
 */
#define SL_XSD_DER_CONT_LFRT_MUST_TRP_MODE    (0x00010000)
/**
 * Low Voltage Ride Through, May Trip Mode
 */
#define SL_XSD_DER_CONT_LVRT_MAY_TRP_MODE     (0x00020000)
/**
 * Low Voltage Ride Through, Momentary Cessation Mode
 */
#define SL_XSD_DER_CONT_LVRT_MOM_CESS_MODE    (0x00040000)
/**
 * Low Voltage Ride Through, Must Trip Mode
 */
#define SL_XSD_DER_CONT_LVRT_MUST_TRP_MODE    (0x00080000)
/**
 * Maximum Active Power
 */
#define SL_XSD_DER_CONT_MAX_LIM_W             (0x00100000)
/**
 * Target Rective Power
 */
#define SL_XSD_DER_CONT_TARGET_VAR            (0x00200000)
/**
 * Target Active Power
 */
#define SL_XSD_DER_CONT_TARGET_W              (0x00400000)
/**
 * Volt-Var Mode
 */
#define SL_XSD_DER_CONT_VOLT_VAR_MODE         (0x00800000)
/**
 * Volt-Watt Mode
 */
#define SL_XSD_DER_CONT_VOLT_WATT_MODE        (0x01000000)
/**
 * Watt-PowerFactor Mode
 */
#define SL_XSD_DER_CONT_WATT_PF_MODE          (0x02000000)
/**
 * Watt-Var Mode
 */
#define SL_XSD_DER_CONT_WATT_VAR_MODE         (0x04000000)

/**
 * All other values are reserved.
 */
#define SL_XSD_DER_FIRST_CONTROL                        (2)                    // Charge/Dischage Mode is not control
#define SL_XSD_DER_MAX_CONTROL                          (27 -SL_XSD_DER_FIRST_CONTROL)

/** @} */

// XSD DERType
/******************************************************************************/
/**
 * \defgroup SL_XSD_DER_TYPE_XXX XSD DER Type: sl_xsd_der_type_t (SL_XSD_DER_TYPE_XXX)
 * Defines the type of units for a particular value. Acceptable values are
 * SL_XSD_DER_TYPE_XXX as defined below.
 */
/** \addtogroup SL_XSD_DER_TYPE_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_der_type_t
 * Acceptable values are SL_XSD_DER_TYPE_XXX.
 */
typedef u8_t sl_xsd_der_type_t;
/**
 * Virtual or mixed DER
 */
#define SL_XSD_DER_TYPE_VIRTUAL_MIXED_DER       (1)
/**
 * Reciprocating engine
 */
#define SL_XSD_DER_TYPE_REC_ENGINE              (2)
/**
 * Fuel cell
 */
#define SL_XSD_DER_TYPE_FUEL_CELL               (3)
/**
 * Photovoltaic system
 */
#define SL_XSD_DER_TYPE_PHOTO_SYSTEM            (4)
/**
 * Combined heat and power
 */
#define SL_XSD_DER_TYPE_HEAT_POWER              (5)
/**
 * Other generation system
 */
#define SL_XSD_DER_TYPE_OTHER_GENERATION_SYSTEM (6)
/**
 * Storage (immobile)
 */
#define SL_XSD_DER_TYPE_OTHER_STORAGE_SYSTEM    (80)
/**
 * Electric vehicle
 */
#define SL_XSD_DER_TYPE_EV                      (81)
/**
 * EVSE
 */
#define SL_XSD_DER_TYPE_EVSE                    (82)
/**
 * Combined PV and storage
 */
#define SL_XSD_DER_TYPE_PV_STORAGE              (83)
/**
 * All other values are reserved.
 */

/** @} */


// XSD alarmStatus
#define DER_FAULT_OVER_CURRENT                  (0) 
#define DER_FAULT_OVER_VOLTAGE                  (1) 
#define DER_FAULT_UNDER_VOLTAGE                 (2) 
#define DER_FAULT_OVER_FREQUENCY                (3) 
#define DER_FAULT_UNDER_FREQUENCY               (4) 
#define DER_FAULT_VOLTAGE_IMBALANCE             (5) 
#define DER_FAULT_CURRENT_IMBALANCE             (6) 
#define DER_FAULT_EMERGENCY_LOCAL               (7) 
#define DER_FAULT_EMERGENCY_REMOTE              (8) 
#define DER_FAULT_LOW_POWER_INPUT               (9) 
#define  DER_FAULT_PHASE_ROTATION               (10)


// XSD DeviceCategoryType
/******************************************************************************/
/**
 * \defgroup SL_XSD_DEVCAT_XXX XSD Device Category Type: sl_xsd_dev_cat_bitmap_t (SL_XSD_DEVCAT_XXX)
 * The device category is a bitmap with each bit defined as below. Note that bits
 * 26-31 are reserved.
 */
/** \addtogroup SL_XSD_DEVCAT_XXX
* @{ */
/**
 * \var typedef u32_t sl_xsd_dev_cat_bitmap_t
 * Acceptable values are SL_XSD_DEVCAT_XXX.
 */
typedef u32_t sl_xsd_dev_cat_bitmap_t;
#define SL_XSD_DEVCAT_THERMOSTAT                (0x00000001)
#define SL_XSD_DEVCAT_STRIP_HEATER              (0x00000002)
#define SL_XSD_DEVCAT_BASEBOARD_HEATER          (0x00000004)
#define SL_XSD_DEVCAT_WATER_HEATER              (0x00000008)
#define SL_XSD_DEVCAT_POOL_PUMP                 (0x00000010)
#define SL_XSD_DEVCAT_SPA                       (0x00000020)
#define SL_XSD_DEVCAT_JACUZZI                   (0x00000040)
#define SL_XSD_DEVCAT_SMART_APPLIANCE           (0x00000080)
#define SL_XSD_DEVCAT_IRRIGATION_PUMP           (0x00000100)
#define SL_XSD_DEVCAT_COMMERCIAL_LOADS          (0x00000200)
#define SL_XSD_DEVCAT_SIMPLE_LOADS              (0x00000400)
#define SL_XSD_DEVCAT_EXTERIOR_LIGHTING         (0x00000800)
#define SL_XSD_DEVCAT_INTERIOR_LIGHTING         (0x00001000)
#define SL_XSD_DEVCAT_LOAD_CONTROL_SWITCH       (0x00002000)
#define SL_XSD_DEVCAT_EMS                       (0x00004000)
#define SL_XSD_DEVCAT_SMART_ENERGY_MODULE       (0x00008000)
#define SL_XSD_DEVCAT_ELECTRIC_VEHICLE          (0x00010000)
#define SL_XSD_DEVCAT_EVSE                      (0x00020000)
#define SL_XSD_DEVCAT_VIRTUAL_MIXED_DER         (0x00040000)
#define SL_XSD_DEVCAT_RECIPROCATING_ENGINE      (0x00080000)
#define SL_XSD_DEVCAT_FUEL_CELL                 (0x00100000)
#define SL_XSD_DEVCAT_PV_SYSTEM                 (0x00200000)
#define SL_XSD_DEVCAT_COMBINED_HEAT_POWER       (0x00400000)
#define SL_XSD_DEVCAT_COMBINED_PV_STORAGE       (0x00800000)
#define SL_XSD_DEVCAT_OTHER_GENERATION_SYSTEMS  (0x01000000)
#define SL_XSD_DEVCAT_OTHER_STORAGE_SYSTEMS     (0x02000000)
/**
 * Bits 26-31 are reserved
 */
#define SL_XSD_DEVCAT_RESERVED_MIN              (0x04000000)
#define SL_XSD_DEVCAT_RESERVED_MAX              (0x80000000)

/** @} */

// XSD DRLC Options
/******************************************************************************/
/**
 * \defgroup SL_XSD_DRLC_OPTIONS_XXX XSD DRLC Options: sl_xsd_drlc_options_bitmap_t (SL_XSD_DRLC_OPTIONS_XXX)
 * The DRLC options is a bitmap defining the DRLC options supported by a device,
 * with each bit defined as below.
 */
/** \addtogroup SL_XSD_DRLC_OPTIONS_XXX
* @{ */
/**
 * \var typedef u32_t sl_xsd_drlc_options_bitmap_t
 * Acceptable values are SL_XSD_DRLC_OPTIONS_XXX.
 */
typedef u32_t sl_xsd_drlc_options_bitmap_t;
/**
 * Target Reduction (kWH)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_KWH         (0)
/**
 * Target Reduction (kW)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_KW          (1)
/**
 * Target Reduction (Watts)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_W           (2)
/**
 * Target Reduction (Cubic Meters)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_CUBIC_M     (3)
/**
 * Target Reduction (Cubic Feet)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_CUBIC_FT    (4)
/**
 * Target Reduction (US Gallons)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_US_GAL      (5)
/**
 * Target Reduction (Imperial Gallons)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_IMP_GAL     (6)
/**
 * Target Reduction (BTUs)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_BTUS        (7)
/**
 * Target Reduction (Liters)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_L           (8)
/**
 * Target Reduction (KPA Gauge)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_KPA_GAUGE   (9)
/**
 * Target Reduction (KPA Absolute)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_KPA_ABS    (10)
/**
 * Target Reduction (Mega Joules)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_MEGA_JOULE (11)
/**
 * Target Recution (Unitless)
 */
#define SL_XSD_DRLC_OPTIONS_TARGET_RED_UNITLESS   (12)
/**
 * Bits 13 - 15 are reserved.
 */
/**
 * Temperature Set Point
 */
#define SL_XSD_DRLC_OPTIONS_TEMP_SETPOINT         (16)
/**
 * Temperature Offset
 */
#define SL_XSD_DRLC_OPTIONS_TEMP_OFFSET           (17)
/**
 * Duty Cycle
 */
#define SL_XSD_DRLC_OPTIONS_DUTY_CYCLE            (18)
/**
 * Load Adjustment Percentage
 */
#define SL_XSD_DRLC_OPTIONS_LOAD_ADJ_PERCENT      (19)
/**
 * Appliance Load Reduction
 */
#define SL_XSD_DRLC_OPTIONS_APPL_LOAD_RED         (20)
/**
 * Bits 21 - 32 are reserved.
 */
/** @} */

// XSD eventStatus.currentStatus
/******************************************************************************/
/**
 * \defgroup SL_XSD_EVENT_CURR_STATUS_XXX XSD Event Status Current Status Type: sl_xsd_event_curr_status_t (SL_XSD_EVENT_CURR_STATUS_XXX)
 * Represents the current status of a particular event.
 * Acceptable values are SL_XSD_EVENT_CURR_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_EVENT_CURR_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_event_curr_status_t
 * Acceptable values are SL_XSD_EVENT_CURR_STATUS_XXX.
 */
typedef u8_t sl_xsd_event_curr_status_t;
/**
 * Indicates that the event has been scheduled and it has not yet started.
 */
#define SL_XSD_EVENT_CURR_STATUS_SCHEDULED     (0)
/**
 * Indicates that the event is currently active. The server SHALL set the event to this status
 * when the event reaches its earliest Effective Start Time.
 */
#define SL_XSD_EVENT_CURR_STATUS_ACTIVE        (1)
/**
 * Indicates that the event has been canceled.
 */
#define SL_XSD_EVENT_CURR_STATUS_CANCELED      (2)
/**
 * Indicates that an event has been canceled by the server and that the client should apply
 * randomization when it cancels the event.
 */
#define SL_XSD_EVENT_CURR_STATUS_CANCELED_RAND (3)
/**
 * Indicates that this event has been superseded by another event.
 */
#define SL_XSD_EVENT_CURR_STATUS_SUPERSEDED    (4)
/** @} */

// XSD Excitation
/******************************************************************************/
/**
 * \defgroup SL_XSD_EXCITATION_XXX XSD Excitation: sl_xsd_excitation_t (SL_XSD_EXCITATION_XXX)
 * Defines the excitation of a power factor.
 * Acceptable values are SL_XSD_EXCITATION_XXX as defined below.
 */
/** \addtogroup SL_XSD_EXCITATION_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_excitation_t
 * Acceptable values are SL_XSD_EXCITATION_XXX.
 */
typedef i8_t sl_xsd_excitation_t;
/**
 * Under-excited
 */
#define SL_XSD_EXCITATION_OVER            (0)

/**
 * Over-excited
 */
#define SL_XSD_EXCITATION_UNDER           (1)

/** @} */

// XSD FlowDirectionType
/******************************************************************************/
/**
 * \defgroup SL_XSD_FLOW_DIR_XXX XSD Flow Direction Type: sl_xsd_flow_dir_type_t (SL_XSD_FLOW_DIR_XXX)
 * Anything involving current might have a flow direction. Possible values
 * include forward and reverse.
 * Acceptable values are SL_XSD_FLOW_DIR_XXX as defined below.
 */
/** \addtogroup SL_XSD_FLOW_DIR_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_flow_dir_type_t
 * Acceptable values are SL_XSD_FLOW_DIR_XXX.
 */
typedef u8_t sl_xsd_flow_dir_type_t;
/**
 * Not applicable (default, if not specified).
 */
#define SL_XSD_FLOW_DIR_NOT_APPL          (0)
#define SL_XSD_FLOW_DIR_FORWARD           (1)
#define SL_XSD_FLOW_DIR_REVERSE           (19)
/**
 * Indicates that the flow direction field is not in use. This is
 * a valid value if the flow direction field is optional for the
 * particular resource.
 */
#define SL_XSD_FLOW_DIR_NOT_USED          (0xFF)
/** @} */

// XSD InverterStatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_INV_STATUS_XXX XSD Inverter Status Type: sl_xsd_inv_status_t (SL_XSD_INV_STATUS_XXX)
 * Indicates the inverter status.
 *
 * Values are SL_XSD_INV_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_INV_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_inv_status_t
 * Acceptable values are SL_XSD_INV_STATUS_XXX.
 */
typedef u8_t sl_xsd_inv_status_t;
/**
 * Not applicable (default, if not specified).
 */
#define SL_XSD_INV_STATUS_NA         (0)
/**
 * Off
 */
#define SL_XSD_INV_STATUS_OFF        (1)
/**
 * Sleeping (auto-shutdown) or DER is at low output power/voltage
 */
#define SL_XSD_INV_STATUS_SLEEP      (2)
/**
 * Starting up or ON but not producing power
 */
#define SL_XSD_INV_STATUS_START_ON   (3)
/**
 * Tracking MPPT power point
 */
#define SL_XSD_INV_STATUS_TRACKING   (4)
/**
 * Forced power reduction/derating
 */
#define SL_XSD_INV_STATUS_PWR_REDUC  (5)
/**
 * Shutting down
 */
#define SL_XSD_INV_STATUS_SHUTDOWN   (6)
/**
 * One or more faults exist
 */
#define SL_XSD_INV_STATUS_FAULTS     (7)
/**
 * Standby (service on unit) - DER may be at high output voltage/power
 */
#define SL_XSD_INV_STATUS_STANDBY    (8)
/**
 * Test mode
 */
#define SL_XSD_INV_STATUS_TESTMODE   (9)
/**
 * As defined in manufacturer status
 */
#define SL_XSD_INV_STATUS_MANU_DEF   (10)

/** @} */

// XSD KindType
/******************************************************************************/
/**
 * \defgroup SL_XSD_KIND_XXX XSD Kind Type: sl_xsd_kind_type_t (SL_XSD_KIND_XXX)
 * Defines the kind used for a particular value. Acceptable
 * values are SL_XSD_KIND_XXX as defined below.
 */
/** \addtogroup SL_XSD_KIND_XXX
* @{ */
/**
 * \var typedef i8_t sl_xsd_kind_type_t
 * Acceptable values are SL_XSD_KIND_XXX.
 */
typedef u8_t sl_xsd_kind_type_t;
/**
 * Not applicable (default, if not specified).
 */
#define SL_XSD_KIND_NOT_APPL       (0)
#define SL_XSD_KIND_CURRENCY       (3)
#define SL_XSD_KIND_DEMAND         (8)
#define SL_XSD_KIND_ENERGY         (12)
#define SL_XSD_KIND_POWER          (37)
/**
 * Indicates that the kind type field is not in use. This is
 * a valid value if the kind type field is optional for the
 * particular resource.
 */
#define SL_XSD_KIND_NOT_USED       (0xFF)
/** @} */

// XSD Profile Id   // TODO (Legacy S0, Remove for S1)
/******************************************************************************/
/**
 * \defgroup SL_XSD_PROFILE_ID_XXX XSD Profile Id Type: sl_xsd_profile_id_t (SL_XSD_PROFILE_ID_XXX)
 * Indicates the profile id.
*
 * Values are SL_XSD_PROFILE_ID_XXX as defined below.
 */
/** \addtogroup SL_XSD_PROFILE_ID_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_profile_id_t
 * Acceptable values are SL_XSD_PROFILE_ID_XXX.
 */
typedef u8_t sl_xsd_profile_id_t;
/**
 * Not profile specific
 */
#define SL_XSD_PROFILE_ID_NOT_SPECIFIC         0
/**
 * Profile is vendor defined
 */
#define SL_XSD_PROFILE_ID_VENDOR_DEFINED       1
/**
 * Smart Energy profile
 */
#define SL_XSD_PROFILE_ID_SMART_ENERGY         2
/**
 * Home Automation profile
 */
#define SL_XSD_PROFILE_ID_HOME_AUTOMATION      3
/**
 * Building Automation profile
 */
#define SL_XSD_PROFILE_ID_BUILDING_AUTOMATION  4
/**
 * All other values reserved.
 */
/** @} */

// XSD Function Set   // TODO (Legacy S0, Remove for S1)
/******************************************************************************/
/**
 * \defgroup SL_XSD_FUNCTION_SET_XXX XSD Function Set Type: sl_xsd_function_set_t (SL_XSD_FUNCTION_SET_XXX)
 * Indicates the function set.
*
 * Values are SL_XSD_FUNCTION_SET_XXX as defined below.
 */
/** \addtogroup SL_XSD_FUNCTION_SET_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_function_set_t
 * Acceptable values are SL_XSD_FUNCTION_SET_XXX.
 */
typedef u8_t sl_xsd_function_set_t;
/**
 * Not specific to a function set
 */
#define SL_XSD_FUNCTION_SET_GENERAL               0
/**
 * Subscription / Notification function set
 */
#define SL_XSD_FUNCTION_SET_SUBSCRIBE             1
/**
 * End Device function set
 */
#define SL_XSD_FUNCTION_SET_ENDDEVICE             2
/**
 * Function Set Assignments function set
 */
#define SL_XSD_FUNCTION_SET_FUNCTION_SETASSIGNMENTS    3
/**
 * Response function set
 */
#define SL_XSD_FUNCTION_SET_RESPONSE              4
/**
 * Demand Response Load Control function set
 */
#define SL_XSD_FUNCTION_SET_DRLC                  5
/**
 * Metering function set
 */
#define SL_XSD_FUNCTION_SET_METERING              6
/**
 * Pricing function set
 */
#define SL_XSD_FUNCTION_SET_PRICING               7
/**
 * Messaging function set
 */
#define SL_XSD_FUNCTION_SET_MESSAGING             8
/**
 * Billing function set
 */
#define SL_XSD_FUNCTION_SET_BILLING               9
/**
 * Prepayment function set
 */
#define SL_XSD_FUNCTION_SET_PREPAYMENT            10
/**
 * Distributed Energy Resource function set
 */
#define SL_XSD_FUNCTION_SET_DER                   11
/**
 * Time function set
 */
#define SL_XSD_FUNCTION_SET_TIME                  12
/**
 * Software Download function set
 */
#define SL_XSD_FUNCTION_SET_SOFTWAREDOWNLOAD      13
/**
 * Device Info function set
 */
#define SL_XSD_FUNCTION_SET_DEVINFO               14
/**
 * Power Status function set
 */
#define SL_XSD_FUNCTION_SET_POWERSTATUS           15
/**
 * Network Status function set
 */
#define SL_XSD_FUNCTION_SET_NETWORKSTATUS         16
/**
 * Log Event List function set
 */
#define SL_XSD_FUNCTION_SET_LEL                   17
/**
 * Configuration function set
 */
#define SL_XSD_FUNCTION_SET_CONFIG                18
/**
 * Security
 */
#define SL_XSD_FUNCTION_SET_SECURITY              19
/**
 * All other values reserved.
 */

/** @} */

// XSD LocalControlModeStatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_LOCAL_CONT_MODE_STATUS_XXX XSD Local Control Mode Status Type: sl_xsd_local_cont_mode_status_t (SL_XSD_LOCAL_CONT_MODE_STATUS_XXX)
 * Indicates the local control mode status type.
*
 * Values are SL_XSD_LOCAL_CONT_MODE_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_LOCAL_CONT_MODE_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_local_cont_mode_status_t
 * Acceptable values are SL_XSD_LOCAL_CONT_MODE_STATUS_XXX.
 */
typedef u8_t sl_xsd_local_cont_mode_status_t;
/**
 * Local control
 */
#define SL_XSD_LOCAL_CONT_MODE_STATUS_LOCAL   (0)
/**
 * Remote control
 */
#define SL_XSD_LOCAL_CONT_MODE_STATUS_REMOTE  (1)
/**
 * All other values reserved.
 */

/** @} */

// XSD OperationalModeStatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_OP_MODE_STATUS_XXX XSD Operational Mode Status Type: sl_xsd_op_mode_status_t (SL_XSD_OP_MODE_STATUS_XXX)
 * Contains DER operational mode status values
 * Acceptable values are SL_XSD_OP_MODE_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_OP_MODE_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_op_mode_status_t
 * Acceptable values are SL_XSD_OP_MODE_STATUS_XXX.
 */
typedef u8_t sl_xsd_op_mode_status_t;
/**
 * Not applicable
 */
#define SL_XSD_OP_MODE_STATUS_NA     (0)
/**
 * Off
 */
#define SL_XSD_OP_MODE_STATUS_OFF    (1)
/**
 * Operational mode
 */
#define SL_XSD_OP_MODE_STATUS_OPER   (2)
/**
 * Test mode
 */
#define SL_XSD_OP_MODE_STATUS_TEST   (3)

/** @} */

// XSD PhaseCode
/******************************************************************************/
/**
 * \defgroup SL_XSD_PHASE_CODE_XXX XSD Phase Code Type: sl_xsd_phase_code_type_t (SL_XSD_PHASE_CODE_XXX)
 * Contains phase information associated with the type.
 * Acceptable values are SL_XSD_PHASE_CODE_XXX as defined below.
 */
/** \addtogroup SL_XSD_PHASE_CODE_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_phase_code_type_t
 * Acceptable values are SL_XSD_PHASE_CODE_XXX.
 */
typedef u8_t sl_xsd_phase_code_type_t;
/**
 * Not applicable (default, if not specified)
 */
#define SL_XSD_PHASE_CODE_NOT_APPL       (0)
/**
 * Phase AN (and S1N)
 */
#define SL_XSD_PHASE_CODE_AN             (129)
/**
 * Phase A (and S1)
 */
#define SL_XSD_PHASE_CODE_A              (128)
/**
 * Phase AB
 */
#define SL_XSD_PHASE_CODE_AB             (132)
/**
 * Phase BN
 */
#define SL_XSD_PHASE_CODE_BN             (65)
/**
 * Phase B
 */
#define SL_XSD_PHASE_CODE_B              (64)
/**
 * Phase CN (and S2N)
 */
#define SL_XSD_PHASE_CODE_CN             (33)
/**
 * Phase C (and S2)
 */
#define SL_XSD_PHASE_CODE_C              (32)
/**
 * Phase ABC
 */
#define SL_XSD_PHASE_CODE_ABC            (224)
/**
 * Phase BC
 */
#define SL_XSD_PHASE_CODE_BC             (66)
/**
 * Phase CA
 */
#define SL_XSD_PHASE_CODE_CA             (40)
/**
 * Indicates that the phase code field is not in use. This is
 * a valid value if the phase code field is optional for the
 * particular resource.
 */
#define SL_XSD_PHASE_CODE_NOT_USED       (0xFF)
/** @} */

// XSD PowerOfTenMultiplierType
/******************************************************************************/
/**
 * \defgroup SL_XSD_PTM_XXX XSD Power Of Ten Multiplier Type: sl_xsd_ptm_type_t (SL_XSD_PTM_XXX)
 * Defines the power of ten multiplier used for a particular value. Acceptable
 * values are SL_XSD_PTM_XXX as defined below.
 */
/** \addtogroup SL_XSD_PTM_XXX
* @{ */
/**
 * \var typedef i8_t sl_xsd_ptm_type_t
 * Acceptable values are SL_XSD_PTM_XXX.
 */
typedef i8_t sl_xsd_ptm_type_t;
  /** None (default if not specified) */
#define SL_XSD_PTM_NONE            (0)
  /** deca  = x10                     */
#define SL_XSD_PTM_DECA            (1)
  /** hecto = x100                    */
#define SL_XSD_PTM_HECTO           (2)
  /** mili  = x10^-3                  */
#define SL_XSD_PTM_MILI            (-3)
  /** kilo  = x1000                   */
#define SL_XSD_PTM_KILO            (3)
  /** Mega  = x10^6                   */
#define SL_XSD_PTM_MEGA            (6)
  /** micro = x10^-6                  */
#define SL_XSD_PTM_MICRO           (-6)
  /** Giga  = x10^9                   */
#define SL_XSD_PTM_GIGA            (9)
/**
 * Indicates that the power of ten field is not in use. This is
 * a valid value if the power of ten field is optional for the
 * particular resource.
 */
#define SL_XSD_PTM_NOT_USED        (10)
/** @} */

// XSD PowerSourceType
/******************************************************************************/
/**
 * \defgroup SL_XSD_POWER_SOURCE_XXX XSD Power Source Type: sl_xsd_power_source_t (SL_XSD_POWER_SOURCE_XXX)
 * Defines the power source of a device. This will be fixed for devices powered
 * by a single source. It may chagne for devices able to transition between
 * multiple power sources. Acceptable values are SL_XSD_POWER_SOURCE_XXX as defined below.
 */
/** \addtogroup SL_XSD_POWER_SOURCE_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_power_source_t
 * Acceptable values are SL_XSD_POWER_SOURCE_XXX.
 */
typedef u8_t sl_xsd_power_source_t;
/** Unknown */
#define SL_XSD_POWER_SOURCE_NONE           (0)
/** Mains */
#define SL_XSD_POWER_SOURCE_MAIN           (1)
/** Battery */
#define SL_XSD_POWER_SOURCE_BATTERY        (2)
/** Local generation */
#define SL_XSD_POWER_SOURCE_LOCAL          (3)
/** Emergency */
#define SL_XSD_POWER_SOURCE_EMERGENCY      (4)
/** Unknown */
#define SL_XSD_POWER_SOURCE_UNKNOWN        (5)
/** @} */

// XSD PrepayModeType
/******************************************************************************/
/**
 * \defgroup SL_XSD_PREPAY_MODE_XXX XSD Prepay Mode Type: sl_xsd_prepay_mode_type_t (SL_XSD_PREPAY_MODE_XXX)
 * Defines the power of ten multiplier used for a particular value. Acceptable
 * values are SL_XSD_PREPAY_MODE_XXX as defined below.
 */
/** \addtogroup SL_XSD_PREPAY_MODE_XXX
* @{ */
/**
 * \var typedef i8_t sl_xsd_prepay_mode_type_t
 * Acceptable values are SL_XSD_PREPAY_MODE_XXX.
 */
typedef u8_t sl_xsd_prepay_mode_type_t;
/**
 * Central wallet mode indicates that the prepayment algorithms are implemented within the utility systems.
 */
#define SL_XSD_PREPAY_MODE_CENTRAL_WALLET (0)
/**
 * ESI mode indicates that the prepayment algorithms are implemented  within the home at the
 * interface between utility WAN and the HAN
 */
#define SL_XSD_PREPAY_MODE_ESI            (1)
/**
 * Local mode indicates that the prepayment algorithms are implemented locally within the metering
 * device itself.
 */
#define SL_XSD_PREPAY_MODE_LOCAL          (2)
/**
 * Credit mode indicates that prepayment is not currently in effect
 * */
#define SL_XSD_PREPAY_MODE_CREDIT         (3)
/** @} */


// XSD PrimacyType
/******************************************************************************/
/**
 * \defgroup SL_XSD_PRIMACY_XXX XSD Primacy Type: sl_xsd_primacy_type_t (SL_XSD_PRIMACY_XXX)
 * Defines primary provider type. Acceptable values are SL_XSD_PRIMACY_XXX as
 * defined below.
 */
/** \addtogroup SL_XSD_PRIMACY_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_primacy_type_t
 * Acceptable values are SL_XSD_PRIMACY_XXX.
 */
typedef u8_t sl_xsd_primacy_type_t;
  /** In home Energy Management System */
#define SL_XSD_PRIMACY_IN_HOME_EMS                (0)
  /** Contracted Premise Service Provider */
#define SL_XSD_PRIMACY_CONTRACTED_PREMISE_SP      (1)
  /** Non-contractual service provider */
#define SL_XSD_PRIMACY_NON_CONTRACTUAL_SP         (2)
/** @} */

// XSD PriorityType
/******************************************************************************/
/**
 * \defgroup SL_XSD_MSG_PRIOR_XXX XSD Priority Type: sl_xsd_msg_priority_type_t (SL_XSD_MSG_PRIOR_XXX)
 * Defines the priority of a received text message. Acceptable values are
 * SL_XSD_MSG_PRIOR_XXX as defined below.
 */
/** \addtogroup SL_XSD_MSG_PRIOR_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_msg_priority_type_t
 * Acceptable values are SL_XSD_MSG_PRIOR_XXX.
 */
typedef u8_t sl_xsd_msg_priority_type_t;
#define SL_XSD_MSG_PRIOR_LOW                (0)
#define SL_XSD_MSG_PRIOR_NORMAL             (1)
#define SL_XSD_MSG_PRIOR_HIGH               (2)
#define SL_XSD_MSG_PRIOR_CRITICAL           (3)
/** @} */

// XSD DeviceOperationalStateType
/******************************************************************************/
/**
 * \defgroup SL_XSD_OP_STATE_XXX XSD Op State Type: sl_xsd_op_state_t (SL_XSD_OP_STATE_XXX)
 * Indicates the operation state of a device.
 *
 * Values are SL_XSD_OP_STATE_XXX as defined below.
 */
/** \addtogroup SL_XSD_OP_STATE_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_op_state_t
 * Acceptable values are SL_XSD_OP_STATE_XXX.
 */
typedef u8_t sl_xsd_op_state_t;
/**
 * The operational state is not applicable or unknown.
 */
#define SL_XSD_OP_STATE_NA_OR_UNKNOWN     (0)
/**
 * The device not operating.
 */
#define SL_XSD_OP_STATE_NOT_OPERATING     (1)
/**
 * The device is operating.
 */
#define SL_XSD_OP_STATE_OPERATING         (2)
/**
 * The device is starting up.
 */
#define SL_XSD_OP_STATE_STARTING_UP       (3)
/**
 * The device is shutting down.
 */
#define SL_XSD_OP_STATE_SHUTTING_DOWN     (4)
/**
 * The device is operating a disconnect level.
 */
#define SL_XSD_OP_STATE_AT_DISC_LEVEL     (5)
/**
 * The device is kW ramping.
 */
#define SL_XSD_OP_STATE_KW_RAMPING        (6)
/**
 * The device is kVar ramping.
 */
#define SL_XSD_OP_STATE_KVAR_RAMPING      (7)
/** @} */

// XSD PerCent
/******************************************************************************/
/**
 * A value used for percentages, specified in hundredths of a percent, from
 * 0 - 10000. (For example, 10000 = 100%)
 */
typedef u16_t sl_xsd_percent_t;

// XSD Quality
/******************************************************************************/
/**
 * \defgroup SL_XSD_QUAL_XXX XSD Quality Type: sl_xsd_quality_t (SL_XSD_QUAL_XXX)
 * Metric indicating the quality of a time source. Lower (smaller) quality
 * enumeration values are assumed to be more accurate.
 */
/** \addtogroup SL_XSD_QUAL_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_quality_t
 * Acceptable values are SL_XSD_QUAL_XXX.
 */
typedef u8_t sl_xsd_quality_t;
/**
 * Time set using an external authoritative source such as NTP.
 */
#define SL_XSD_QUAL_EXT_AUTH              (3)
/**
 * Time is obtained from a level 3 source.
 */
#define SL_XSD_QUAL_OBTAINED_FROM_LEVEL_3 (4)
/**
 * Time is manually set or obtained from a level 4 source.
 */
#define SL_XSD_QUAL_MANUALLY_SET          (5)
/**
 * Time is obtained from a level 5 source.
 */
#define SL_XSD_QUAL_OBTAINED_FROM_LEVEL_5 (6)
/**
 * Time is left intentionally uncoordinated.
 */
#define SL_XSD_QUAL_INTEN_UNCOORD         (7)
/** @} */


// XSD Reading.qualityFlags
/******************************************************************************/
/**
 * \defgroup SL_XSD_READ_QUAL_FLAG_XXX XSD Reading Quality Flags Type: sl_xsd_read_qual_flags_type_t (SL_XSD_READ_QUAL_FLAG_XXX)
 * Bitmap codes indicating the quality of a reading.
 */
/** \addtogroup SL_XSD_READ_QUAL_FLAG_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_read_qual_flags_type_t
 * Acceptable values are SL_XSD_READ_QUAL_FLAG_XXX.
 */
typedef u16_t sl_xsd_read_qual_flags_type_t;
/**
 * Valid. Data that has gone through all required validation checks and either
 * passed them all or has been verified.
 */
#define SL_XSD_READ_QUAL_FLAG_VALID_MASK      (0x0001)
/**
 * Manually edited. Replaced or approved by a human.
 */
#define SL_XSD_READ_QUAL_FLAG_MANUAL_MASK     (0x0002)
/**
 * Estimated using reference day. Data value was replaced by a machine computed
 * value based on analysis of historical data using the same type of measurement.
 */
#define SL_XSD_READ_QUAL_FLAG_EST_REFERENCE   (0x0004)
/**
 * Estimated using linear interpolation. Data value was computed using linear
 * interpolation based on the readings before and after it.
 */
#define SL_XSD_READ_QUAL_FLAG_EST_INTERPOL    (0x0008)
/**
 * Questionable. Data that has failed one or more checks.
 */
#define SL_XSD_READ_QUAL_FLAG_QUESTIONABLE    (0x0010)
/**
 * Derived. Data that has been calculated (using logic or mathematical operations),
 * not necessarily measured directly
 */
#define SL_XSD_READ_QUAL_FLAG_DERIVED         (0x0020)
/**
 * Projected (forecast): data that has been calculated as a projection or
 * forecast of future readings.
 */
#define SL_XSD_READ_QUAL_FLAG_PROJECTED       (0x0040)
/** @} */

// XSD RequestStatus Type
/******************************************************************************/
/**
 * \defgroup SL_XSD_REQ_STATUS_XXX XSD Request Status Type: sl_xsd_req_status_type_t (SL_XSD_REQ_STATUS_XXX)
 * Defines the status of a Flow Reservation Request. Acceptable values are
 * SL_XSD_REQ_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_REQ_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_req_status_type_t
 * Acceptable values are SL_XSD_REQ_STATUS_XXX.
 */
typedef u8_t sl_xsd_req_status_type_t;
#define SL_XSD_REQ_STATUS_REQUESTED         (0)
#define SL_XSD_REQ_STATUS_CANCELLED         (1)
/** @} */

// XSD ReservationStatus Type
/******************************************************************************/
/**
 * \defgroup SL_XSD_RES_STATUS_XXX XSD Reservation Status Type: sl_xsd_res_status_type_t (SL_XSD_RES_STATUS_XXX)
 * Defines the priority of a received text message. Acceptable values are
 * SL_XSD_MSG_PRIOR_XXX as defined below.
 */
/** \addtogroup SL_XSD_RES_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_res_status_type_t
 * Acceptable values are SL_XSD_RES_STATUS_XXX.
 */
typedef u8_t sl_xsd_res_status_type_t;
#define SL_XSD_RES_STATUS_PENDING         (0)
#define SL_XSD_RES_STATUS_APPROVED        (1)
#define SL_XSD_RES_STATUS_REVOKED         (2)
/** @} */

// XSD RespondableResource.responseRequired
/******************************************************************************/
/**
 * \defgroup SL_XSD_RESP_XXX XSD Response Required Type: sl_xsd_resp_req_bitmap_t (SL_XSD_RESP_XXX)
 * This type maps to the XSD RespondableResource.responseRequired type, which
 * indicates whether or not a response is required upon receipt or creation or
 * update of this resource. This bitmap provide information on what type of status
 * must be sent in the response to a message using the sl_xsd_resp_status_type_t
 * type. For more details view the SEP 2.0 specification. Acceptable values are
 * SL_XSD_RESP_XXX.
 */
/** \addtogroup SL_XSD_RESP_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_resp_req_bitmap_t
 * Acceptable values are SL_XSD_RESP_XXX.
 */
typedef u8_t sl_xsd_resp_req_bitmap_t;
  /**
   * Indicates that a response is required when the event is received.
   */
#define SL_XSD_RESP_REQ_RXED_MASK    (0x0001)
  /**
   * Indicates that a detailed response is required when the event status changes.
   * The list of allowed responses is specified by the sl_xsd_resp_status_type_t
   * enumeration. Note that only a subset of the status types are valid for
   * this case. Please see the sl_xsd_resp_status_type_t for details.
   */
#define SL_XSD_RESP_REQ_DETAILS_MASK (0x0002)
  /**
   * End user / customer response is required.
   * The list of allowed responses is specified by the sl_xsd_resp_status_type_t
   * enumeration. Note that only a subset of the status types are valid for
   * this case. Please see the sl_xsd_resp_status_type_t for details.
   */
#define SL_XSD_RESP_REQ_USER_MASK    (0x0004)
/** @} */

// XSD StatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_RESP_STATUS_XXX XSD Status Type: sl_xsd_resp_status_type_t (SL_XSD_RESP_STATUS_XXX)
 * Defines the status bits that can be returned as part of sl_xsd_resp_status_type_t.
 * Acceptable values are SL_XSD_RESP_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_RESP_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_resp_status_type_t
 * Acceptable values are SL_XSD_RESP_STATUS_XXX.
 */
typedef u8_t sl_xsd_resp_status_type_t;
#define SL_XSD_RESP_STATUS_RESERVED_0                    (0)

// The following status value(s) apply to responseRequired bit 1
  /**
   * Applies to responseRequired bit 1 and indicates that the message was received.
   */
#define SL_XSD_RESP_STATUS_MSG_RXED                      (1)
// The following status value(s) apply to responseRequired bit 2
  /**
   * Applies to responseRequired bit 2 and indicates that the event has started.
   */
#define SL_XSD_RESP_STATUS_EVENT_STARTED                 (2)
  /**
   * Applies to responseRequired bit 2 and indicates that the event has completed.
   */
#define SL_XSD_RESP_STATUS_EVENT_COMPLETED               (3)
/**
 * Applies to responseRequired bit 2 and indicates that the user has opted-out.
 * This is used for EDCs only.
 */
#define SL_XSD_RESP_STATUS_OPT_OUT                       (4)
/**
 * Applies to responseRequired bit 2 and indicates that the user has opted-in.
 * This is used for EDCs only.
 */
#define SL_XSD_RESP_STATUS_OPT_IN                        (5)
/**
   * Applies to responseRequired bit 2 and indicates that the event has been canceled.
   */
#define SL_XSD_RESP_STATUS_EVENT_CANCELED                (6)
  /**
   * Applies to responseRequired bit 2 and indicates that the event has been superseded.
   */
#define SL_XSD_RESP_STATUS_EVENT_SUPERSEDED              (7)
/**
 * Applies to responseRequired bit 2 and indicates that the event has been
 * partially completed with user opt-out. This is used for EDCs only.
 */
#define SL_XSD_RESP_STATUS_EVENT_PART_COMPLETE_OPT_OUT   (8)
/**
 * Applies to responseRequired bit 2 and indicates that the event has been
 * partially completed with user opt-in. This is used for EDCs only.
 */
#define SL_XSD_RESP_STATUS_EVENT_PART_COMPLETE_OPT_IN    (9)
  /**
   * Applies to responseRequired bit 2 and indicates that the event has
   * completed with no user participation (previous opt-out). This is used for
   * EDCs only.
   */
#define SL_XSD_RESP_STATUS_EVENT_COMPLETE_NO_PARTICIPATION  (10)
  /**
   * Applies to responseRequired bit 2 and indicates that the event cannot be displayed.
   * This is used for TXTs only.
   */
#define SL_XSD_RESP_STATUS_CANNOT_DISPLAY                (12)
/**
 * Applies to responseRequired bit 2 and indicates that the event was aborted due to
 * an event from an alternate provider.
 */
#define SL_XSD_RESP_STATUS_ABORTED_ALTERNATE_EVENT       (13)
/**
 * Applies to responseRequired bit 2 and indicates that the event was aborted due to
 * an event from an alternate program.
 */
#define SL_XSD_RESP_STATUS_ABORTED_ALTERNATE_PROGRAM_EVENT (14)
/**
 * Applies to responseRequired bit 2 and indicates that the event was rejected due to
 * the event not containing any applicable controls. This is used for EDCs and DERCs
 * only.
 */
#define SL_XSD_RESP_STATUS_REJECT_CTRL_NOT_APPLICABLE  (252)
/**
 * Applies to responseRequired bit 2 and indicates that the event was rejected due to
 * the controls being out of range or not possible for the device. This is used for
 * EDCs and DERCs only.
 */
#define SL_XSD_RESP_STATUS_REJECT_INVALID_EVENT        (253)
/**
 * Applies to responseRequired bit 2 and indicates that the event was rejected because
 * it was received after the specified end time.
 */
#define SL_XSD_RESP_STATUS_REJECT_EVENT_RX_AFTER_EXP   (254)
// The following status value(s) apply to responseRequired bit 3
  /**
   * Applies to responseRequired bit 3 and indicates that the receiving device displayed
   * the event and a human user actively acknowledged it.
   */
#define SL_XSD_RESP_STATUS_USER_ACK                     (11)
// The following status values have not yet been defined, so are not applicable to any responseRequired value.
// 14-246 - Reserved
  /**
   * Defines the minimum of the range of the set of reserved bits. Bits in this range
   * have not been defined and as such are not applicable to any responseRequired value.
   */
#define SL_XSD_RESP_STATUS_RESERVED_MIN                 (15)
  /**
   * Defines the maximum of the range of the set of reserved bits. Bits in this range
   * have not been defined and as such are not applicable to any responseRequired value.
   */
#define SL_XSD_RESP_STATUS_RESERVED_MAX                (251)
#define SL_XSD_RESP_STATUS_RESERVED_255                (255)
/** @} */

// XSD UsagePointBase.roleFlags, RateComponent.roleFlags
/******************************************************************************/
/**
 * \defgroup SL_XSD_ROLE_FLAG_XXX XSD Role Flags Type: sl_xsd_role_flag_t (SL_XSD_ROLE_FLAG_XXX)
 * Defines bits used to determine role flags for usage points and rate components.
 *
 * Values are SL_XSD_ROLE_FLAG_XXX as defined below.
 */
/** \addtogroup SL_XSD_ROLE_FLAG_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_role_flag_t
 * Acceptable values are SL_XSD_ROLE_FLAG_XXX.
 */
typedef u16_t sl_xsd_role_flag_t;
/**
 * MIRROR indicates that the device is a mirror. This bit SHALL be set if the server is not the
 * measurement device.
 */
#define SL_XSD_ROLE_FLAG_MIRROR_MASK     (0x0001)
/**
 * AGGR indicates that the device is a premises aggregation point. This bit SHALL be set if the
 * server is the point of delivery for the premises.
 */
#define SL_XSD_ROLE_FLAG_AGGR_MASK       (0x0002)
/**
 * PEV indicates that the usage applies to an electric vehicle.
 */
#define SL_XSD_ROLE_FLAG_PEV_MASK        (0x0004)
/**
 * DER indicates that the usage applies to a distributed energy resource, capable of delivering
 * power to the grid.
 */
#define SL_XSD_ROLE_FLAG_DER_MASK        (0x0008)
/**
 * REVQUAL indicates that the usage was measured by a device certified as revenue quality.
 */
#define SL_XSD_ROLE_FLAG_REVQUAL_MASK    (0x0010)
/**
 * DC indicates that the usage point measures direct current.
 */
#define SL_XSD_ROLE_FLAG_DC_MASK         (0x0020)
/**
 * SUB indicates that the usage point is a sub meter. This bit SHALL be set if the usage point
 * is not a premises aggregation point.
 */
#define SL_XSD_ROLE_FLAG_SUB_MASK         (0x0040)
/** @} */


// XSD ServiceKind
/******************************************************************************/
/**
 * \defgroup SL_XSD_SERVICE_XXX XSD Service Kind Type: sl_xsd_service_t (SL_XSD_SERVICE_XXX)
 * Defines the kind of service provided by a usage point.
 *
 * Values are SL_XSD_SERVICE_XXX as defined below.
 */
/** \addtogroup SL_XSD_SERVICE_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_service_t
 * Acceptable values are SL_XSD_SERVICE_XXX.
 */
typedef u8_t sl_xsd_service_t;
#define SL_XSD_SERVICE_ELECTRICITY  (0)
#define SL_XSD_SERVICE_GAS          (1)
#define SL_XSD_SERVICE_WATER        (2)
#define SL_XSD_SERVICE_PRESSURE     (4)
#define SL_XSD_SERVICE_HEAT         (5)
#define SL_XSD_SERVICE_COLD         (6)
#define SL_XSD_SERVICE_COMM         (7)
#define SL_XSD_SERVICE_TIME         (8)
/** @} */

// XSD ServiceStatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_SERV_STAT_XXX XSD Service Status Type: sl_xsd_serv_stat_t (SL_XSD_SERV_STAT_XXX)
 * Indicates service status.
 *
 * Values are SL_XSD_SERV_STAT_XXX as defined below.
 */
/** \addtogroup SL_XSD_SERV_STAT_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_serv_stat_t
 * Acceptable values are SL_XSD_SERV_STAT_XXX.
 */
typedef u8_t sl_xsd_serv_stat_t;
#define SL_XSD_SERV_STAT_CONNECTED      (0)
#define SL_XSD_SERV_STAT_DISCONNECTED   (1)
#define SL_XSD_SERV_STAT_ARMED_FOR_CONN (2)
#define SL_XSD_SERV_STAT_ARMED_FOR_DIS  (3)
#define SL_XSD_SERV_STAT_NO_CONTACTOR   (4)
#define SL_XSD_SERV_STAT_OTHER          (5)
/** @} */

// XSD UsagePointBase.status
/******************************************************************************/
/**
 * \defgroup SL_XSD_STATUS_XXX XSD Status Type: sl_xsd_status_t (SL_XSD_STATUS_XXX)
 * Indicates status  of a device.
 *
 * Values are SL_XSD_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_status_t
 * Acceptable values are SL_XSD_STATUS_XXX.
 */
typedef u8_t sl_xsd_status_t;
#define SL_XSD_STATUS_OFF           (0)
#define SL_XSD_STATUS_ON            (1)
/** @} */

// XSD StorageModeStatusType
/******************************************************************************/
/**
 * \defgroup SL_XSD_STOR_MODE_STATUS_XXX XSD Status Type: sl_xsd_stor_mode_status_t (SL_XSD_STOR_MODE_STATUS_XXX)
 * Indicates DER storage mode status.
 *
 * Values are SL_XSD_STOR_MODE_STATUS_XXX as defined below.
 */
/** \addtogroup SL_XSD_STOR_MODE_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_stor_mode_status_t
 * Acceptable values are SL_XSD_STOR_MODE_STATUS_XXX.
 */
typedef u8_t sl_xsd_stor_mode_status_t;
/**
 * storage charging
 */
#define SL_XSD_STOR_MODE_STATUS_CHARGING     (0)
/**
 * storage discharging
 */
#define SL_XSD_STOR_MODE_STATUS_DISCHARGING  (1)
/**
 * storage holding
 */
#define SL_XSD_STOR_MODE_STATUS_HOLDING      (2)
/** @} */

// XSD TempSubjectType
/******************************************************************************/
/**
 * \defgroup SL_XSD_TEMP_SUBJECT_XXX XSD Temp Subject Type: sl_xsd_temp_subject_t (SL_XSD_TEMP_SUBJECT_XXX)
 * Indicates the subject of a temperature measurement.
 *
 * Values are SL_XSD_TEMP_SUBJECT_XXX as defined below.
 */
/** \addtogroup SL_XSD_TEMP_SUBJECT_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_temp_subject_t
 * Acceptable values are SL_XSD_TEMP_SUBJECT_XXX.
 */
typedef u8_t sl_xsd_temp_subject_t;
/**
 * Temperature of an enclosure.
 */
#define SL_XSD_TEMP_SUBJECT_ENCLOSURE      (0)
/**
 * Temperature of a transformer.
 */
#define SL_XSD_TEMP_SUBJECT_TRANSFORMER    (1)
/**
 * Temperature of a heat sink.
 */
#define SL_XSD_TEMP_SUBJECT_HEATSINK       (2)
/** @} */

// XSD TimeType
/******************************************************************************/
/**
 * A signed 64 bit value representing the number of seconds since 0 hours,
 * 0 minutes, 0 seconds, on the 1st of January, 1970, in UTC, not counting leap
 * seconds.
 */
typedef i64_t sl_xsd_time_type_t;

// XSD TOUType
/******************************************************************************/
/**
 * \defgroup SL_XSD_TOU_TYPE_XXX XSD TOU Type: sl_xsd_tou_type_t (SL_XSD_TOU_TYPE_XXX)
 * Indicates time of use related to a particular resource. The particular
 * definition of each TOU type (e.g. "A") is outside the scope of this
 * document.
 *
 * Values are SL_XSD_TOU_TYPE_XXX as defined below.
 */
/** \addtogroup SL_XSD_TOU_TYPE_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_tou_type_t
 * Acceptable values are SL_XSD_STATUS_XXX.
 */
typedef u8_t sl_xsd_tou_type_t;
#define SL_XSD_TOU_TYPE_NA  (0)
#define SL_XSD_TOU_TYPE_A   (1)
#define SL_XSD_TOU_TYPE_B   (2)
#define SL_XSD_TOU_TYPE_C   (3)
#define SL_XSD_TOU_TYPE_D   (4)
#define SL_XSD_TOU_TYPE_E   (5)
#define SL_XSD_TOU_TYPE_F   (6)
#define SL_XSD_TOU_TYPE_G   (7)
#define SL_XSD_TOU_TYPE_H   (8)
#define SL_XSD_TOU_TYPE_I   (9)
#define SL_XSD_TOU_TYPE_J   (10)
#define SL_XSD_TOU_TYPE_K   (11)
#define SL_XSD_TOU_TYPE_L   (12)
#define SL_XSD_TOU_TYPE_M   (13)
#define SL_XSD_TOU_TYPE_N   (14)
#define SL_XSD_TOU_TYPE_O   (15)
/** @} */

// XSD UnitType
/******************************************************************************/
/**
 * \defgroup SL_XSD_UNIT_XXX XSD Unit Type: sl_xsd_unit_type_t (SL_XSD_UNIT_XXX)
 * Defines the type of units for a particular value. Acceptable values are
 * SL_XSD_UNIT_XXX as defined below.
 */
/** \addtogroup SL_XSD_UNIT_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_unit_type_t
 * Acceptable values are SL_XSD_UNIT_XXX.
 */
typedef u8_t sl_xsd_unit_type_t;
#define SL_XSD_UNIT_KWH           (0)
#define SL_XSD_UNIT_KW            (1)
#define SL_XSD_UNIT_WATT          (2)
#define SL_XSD_UNIT_CUBIC_METER   (3)
#define SL_XSD_UNIT_CUBIC_FOOT    (4)
#define SL_XSD_UNIT_US_GALLON     (5)
#define SL_XSD_UNIT_IMP_GALLON    (6)
#define SL_XSD_UNIT_BTU           (7)
#define SL_XSD_UNIT_LITER         (8)
#define SL_XSD_UNIT_KPA_GAUGE     (9)
#define SL_XSD_UNIT_KPA_ABS       (10)
#define SL_XSD_UNIT_MEGA_JOULE    (11)
#define SL_XSD_UNIT_UNITLESS      (12)
/** @} */


// XSD UomType
/******************************************************************************/
/**
 * \defgroup SL_XSD_UOM_XXX XSD Unit Type: sl_xsd_uom_t (SL_XSD_UOM_XXX)
 * Defines the type of units for a particular value. Acceptable values are
 * SL_XSD_UOM_XXX as defined below.
 */
/** \addtogroup SL_XSD_UOM_XXX
* @{ */
/**
 * \var typedef u8_t sl_xsd_uom_t
 * Acceptable values are SL_XSD_UOM_XXX.
 */
typedef u8_t sl_xsd_uom_t;
/**
 * Not applicable (default if not specified)
 */
#define SL_XSD_UOM_NOT_APPL             (0)
/**
 * Amps (current)
 */
#define SL_XSD_UOM_CURRENT              (5)
/**
 * Kelvin (temperature)
 */
#define SL_XSD_UOM_TEMPERATURE          (6)
/**
 * Degrees celsius (relative temperature)
 */
#define SL_XSD_UOM_RELATIVE_TEMP        (23)
#define SL_XSD_UOM_VOLTAGE              (29)
/**
 * Joule (energy joule)
 */
#define SL_XSD_UOM_JOULE                (31)
/**
 * Hertz (frequency)
 */
#define SL_XSD_UOM_FREQ                 (33)
/**
 * Real power (watts)
 */
#define SL_XSD_UOM_WATT                 (38)
#define SL_XSD_UOM_CUBIC_METER          (42)
#define SL_XSD_UOM_APPAR_POWER          (61)
#define SL_XSD_UOM_REACT_POWER          (63)
#define SL_XSD_UOM_POWER_FACTOR         (65)
#define SL_XSD_UOM_VOLT_SQ              (67)
#define SL_XSD_UOM_AMP_SQ               (69)
#define SL_XSD_UOM_APPAR_ENERGY         (71)
#define SL_XSD_UOM_WATT_HOUR            (72)
#define SL_XSD_UOM_REACT_ENERGY         (73)
#define SL_XSD_UOM_AMP_HOUR             (106)
#define SL_XSD_UOM_CUBIC_FEET           (119)
#define SL_XSD_UOM_CUBIC_FEET_PER_HOUR  (122)
#define SL_XSD_UOM_CUBIC_METER_PER_HOUR (125)
#define SL_XSD_UOM_US_GALLON            (128)
#define SL_XSD_UOM_US_GALLON_PER_HOUR   (129)
#define SL_XSD_UOM_IMP_GALLON           (130)
#define SL_XSD_UOM_IMP_GALLON_PER_HOUR  (131)
#define SL_XSD_UOM_BTU                  (132)
#define SL_XSD_UOM_BTU_PER_HOUR         (133)
#define SL_XSD_UOM_LITER                (134)
#define SL_XSD_UOM_LITER_PER_HOUR       (137)
#define SL_XSD_UOM_PA_GAUGE             (140)
#define SL_XSD_UOM_PA_ABS               (155)
#define SL_XSD_UOM_THERM                (169)
/**
 * Indicates that the unit of measure field is not in use. This is
 * a valid value if the unit of measure field is optional for the
 * particular resource.
 */
#define SL_XSD_UOM_NOT_USED         (0xFF)
/** @} */

// XSD Version Type
/******************************************************************************/
/**
 * \typedef XSD Version Type: sl_xsd_version_t
 * Version SHALL indicate a distinct identifier for each revision of an
 * IdentifiedObject. If not specified, a default version of "0" (initial version)
 * SHALL be assumed. Upon modification of any IdentifiedObject, the mRID SHALL
 * remain the same, but the version SHALL be incremented. Servers MAY NOT
 * modify objects that they did not create, unless they were notified of the
 * change from the entity controlling the object's PEN.
 */
typedef u16_t sl_xsd_version_t;


/** @} */
// end addtogroup XSD_GROUP_DEFINES

/**
 * \defgroup XSD_GROUP_STRUCTS XSD Structures
 * This section contains structures used on the SL API that
 * are defined in the SEP XSD.
 */
/** \addtogroup XSD_GROUP_STRUCTS
 * @{ */

// XSD ActivePower
/******************************************************************************/
/**
 * \struct sl_xsd_active_power_t
 * The active (real) power P (in W) is the product of root-mean-square (RMS)
 * voltage, RMS current, and cos(theta) where theta is the phase angle of
 * current relative voltage. It is the primary measure of the rate of flow
 * of energy.
 */
typedef struct {
  /**
   * Multiplier for 'value'.
   */
  sl_xsd_ptm_type_t    mult;
  /**
   * Value in Watts
   */
  i16_t                value;
} sl_xsd_active_power_t;

// XSD FreqDroopType
/******************************************************************************/
/**
 * \struct sl_xsd_freq_droop_t
 * Specifies a frequency-watt operation. This operation limits active power
 * generation or consumption when the line frequency deviates from nominal by
 * a specified amount.
*/
typedef struct
{
   /**
   * Frequency droop dead band for over-frequency conditions. In thousandths of Hz.
   */
   u32_t               dBOF;
   /**
    * Frequency droop dead band for under-frequency conditions. In thousandths of Hz.
    */
   u32_t               dBUF;
   /**
    * Frequency droop per-unit frequency change for over-frequency conditions
    * corresponding to 1 per-unit power output change. In thousandths, unitless.
    */
   u16_t               kOF;
   /**
    * Frequency droop per-unit frequency change for under-frequency conditions
    * corresponding to 1 per-unit power output change. In thousandths, unitless.
    */
   u16_t               kUF;
   /**
    * Open loop response time, the duration from a step change in control signal
    * input until the output changes by 90% of its final change before any overshoot,
    * in hundredths of a second. Resolution is 1/100 sec. A value of 0 is used to mean no limit.
    */
   u16_t               openLoopTms;
} sl_xsd_freq_droop_t;

// XSD Pricing.Cost
/******************************************************************************/
/**
 * \struct sl_xsd_cost_t
 * A cost element, typically used for environmental costs. Provides alternative
 * or secondary price information for the relevant RateComponent. Supports
 * jurisdictions that seek to convey the environmental price per unit of the
 * specified commodity not expressed in currency. Implementers and consumers can
 * use this attribute to prioritize operations of their HAN devices (e.g., PEV
 * charging during times of high availability of renewable electricity resources).
 */
typedef struct {
  /**
   * The kind of cost referred to in the amount.
   */
  sl_xsd_cost_kind_type_t costKind;
  /**
   * The relative level of the amount attribute. In conjunction with numCostLevels,
   * this attribute informs a device of the relative scarcity of the amount attribute
   * (e.g., a high or low availability of renewable generation). If costLevel is
   * provided by the server, then numCostLevels SHALL also be provided by the server.
   * numCostLevels and costLevel values SHALL ascend in order of scarcity, where "0"
   * signals the lowest relative cost and higher values signal increasing cost.
   */
  u8_t                    costLevel;
  /**
   * The number of all relative cost levels. In conjunction with costLevel, signals
   * the relative scarcity of the commodity for the duration of the TimeTariffInterval
   * instance (e.g., a relative indication of cost). If numCostLevels is provided by
   * the server, then costLevel SHALL also be provided by the server.
   */
  u8_t                    numCostLevel;
  /**
   * The estimated or actual environmental or other cost, per commodity unit
   * defined by the ReadingType, for this RateComponent (e.g., grams per Watt
   * of carbon dioxide emissions each kWh).
   */
  u32_t                   amount;
} sl_xsd_cost_t;

// XSD RealEnergyType
/******************************************************************************/
/**
 * \struct sl_xsd_real_energy_t
 * Amount of real electrical energy.
 */
typedef struct {
  /**
   * Multiplier for 'value'.
   */
  sl_xsd_ptm_type_t    mult;
  /**
   * Value of the energy in Watt-hours (max of 2^48-1).
   */
  u64_t                value;
} sl_xsd_real_energy_t;

// XSD SignedRealEnergyType
/******************************************************************************/
/**
 * \struct sl_xsd_signed_real_energy_t
 * Amount of real electrical energy, signed.
 */
typedef struct {
  /**
   * Multiplier for 'value'.
   */
  sl_xsd_ptm_type_t    mult;
  /**
   * Value of the energy in Watt-hours (max of 2^48-1).
   */
  i64_t                value;
} sl_xsd_signed_real_energy_t;

// XSD TemperatureType
/******************************************************************************/
/**
 * \struct sl_xsd_temp_t
 * The temperature of a device.
 */
typedef struct
{
  /**
   * Multiplier for 'value'.
   */
  sl_xsd_ptm_type_t      mult;                    // multiplier (M, Int8)
  /**
   * The subject of the temperature measurement.
   */
  sl_xsd_temp_subject_t  subj;                    // subject (M, UInt8)
  /**
   * Temperature value in Celsius.
   */
  i16_t                  valu;                    // value (M, Int16)
} sl_xsd_temp_t;

// XSD UnitValueType
/******************************************************************************/
/**
 * \struct sl_xsd_unit_val_t
 * Type for specification of a specific value, with units and power of ten multiplier.
 */
typedef struct {
  /**
   * Boolean indicating if the unit value information exists in the structure
   * or not. Note that this field is not part of the XSD but it enables
   * flexibility for supporting optional fields.
   */
  bool                exists;
  /**
   * Multiplier for 'unit'.
   */
  sl_xsd_ptm_type_t   multiplier;
  /**
   * Unit associated with value.
   */
  sl_xsd_uom_t        unit;
  /**
   * Value in units specified.
   */
  i32_t               value;
} sl_xsd_unit_val_t;

// XSD PEVInfo
/******************************************************************************/
/**
 * \struct sl_xsd_pev_info_t
 * Contains attributes that can be exposed by PEVs and other devices that have
 * charging requirements.
 */
typedef struct {
  /**
   * This is the actual power flow in or out of the charger or inverter. This is
   * calculated by the vehicle based on actual measurements. This number is
   * positive for charging.
   */
  sl_xsd_active_power_t   chargingPowerNow;
  /**
   * This is the amount of energy that must be transferred from the grid to EVSE
   * and PEV to achieve the target state of charge allowing for charger efficiency
   * and any vehicle and EVSE parasitic loads. This is calculated by the vehicle
   * and changes throughout the connection as forward or reverse power flow
   * change the battery state of charge. This number is positive for charging.
   */
  sl_xsd_real_energy_t    energyRequestNow;
  /**
   * This maximum power transfer capability that could be used for charging the PEV
   * to perform the requested energy transfer. It is the lower of the vehicle or
   * EVSE physical power limitations. It is not based on economic considerations.
   * The vehicle may draw less power than this value based on its charging cycle.
   * The vehicle defines this parameter. This number is positive for charging
   * power flow.
   */
  sl_xsd_active_power_t   maxForwardPower;
  /**
   * This is computed by the PEV based on the charging profile to complete the
   * energy transfer if the maximum power is authorized. The value will never
   * be smaller than the ratio of the energy request to the power request
   * because the charing profile may not allow the maximum power to be used
   * throughout the transfer.
   */
  u32_t                   minimumChargingDuration;
  /**
   * This is the target state of charge that is to be achieved during charging before
   * the time of departure (TCIN). The default value is 100%. The value cannot be set to a
   * value less than the actual state of charge. This value is specified in hundredths
   * of a percent (0 - 10000) where 10000 = 100%.
   */
  u16_t                   targetStateOfCharge;
  /**
   * The Time Charge is Needed (TCIN) is the time that the PEV is expected to depart.
   */
  sl_xsd_time_type_t      timeChargeIsNeeded;
  /**
   * The time at which the parameters are updated, except for chagnes to TCIN.
   */
  sl_xsd_time_type_t      timeChargingStatusPEV;
} sl_xsd_pev_info_t;

// XSD DRLC Capabilities
/******************************************************************************/
/**
 * \struct sl_xsd_drlc_capabilities_t
 * Contains information about the static capabilities of the device, to allow
 * service providers to know what types of functions are supported, what the
 * normal operating ranges and limits are, and other similar information, in
 * order to provide better suggestions of applicable programs to receive the
 * maximum benefit.
 */
typedef struct
{
  /**
   * The average hourly energy used when in normal operating mode.
   */
  sl_xsd_real_energy_t          averageEnergy;
  /**
   * The maximum demand rating of this end device.
   */
  sl_xsd_active_power_t         maxDemand;
  /**
   * Bitmap indicating the DRLC options implemented in the device.
   */
  sl_xsd_drlc_options_bitmap_t  optionsImplemented;
} sl_xsd_drlc_capabilities_t;

/** @} */
// end addtogroup XSD_GROUP_STRUCTS


/** @} */
// end addtogroup XSD_GROUP

/*******************************************************************************
 * Mail Structures
 ******************************************************************************/

// -------------------- Common ------------------
/** \cond NOTRELEASED */

/* TODO: Remove this structure and replace with id and status
 * fields in each individual confirmation.
 */
typedef struct {
  u16_t         id;
  sl_cmn_rc_t   status;
} sl_result_t;

/** \endcond */


/**
 * \defgroup COMMON_GROUP_STRUCTS Common Structures
 * This section contains common structures that are not used for a particular function
 * set.
 */
/** \addtogroup COMMON_GROUP_STRUCTS
 * @{ */


/******************************************************************************/
/**
 * \struct sl_cmn_server_info_t
 * This structure contains server information.
 */
typedef struct {
  /**
   * IP Address of the server. This may be a v4 address or v6 address.
   */
  u8_t                addr[SL_CMN_IP_ADDR_LEN]; // Supports IPv4 and IPv6 addressing
  /**
   * Port to use on the server.
   */
  u16_t               port;
  /**
   * Scheme to use when accessing the server (either HTTP or HTTPS).
   */
  sl_cmn_scheme_t     scheme;
  /**
   * Interface id to use when accessing the server. Set to 0 if not using a
   * link local address.
   */
  u32_t               interfaceId;
} sl_cmn_server_info_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_resp_info_t
 * This structure contains details to the Customer Application for sending
 * a response to the server. This information is generally only needed if
 * the Customer Application is using the \ref sl_resp_client_send_resp_req
 * interface to send a response to the server.
 */
typedef struct {
  /**
  * HREF that responses should be sent to. Please note that currently the HREF
  * is assumed to be relative rather than fully qualified. The max length of
  * the HREF is SL_CMN_REPLY_TO_HREF_LEN is arbitrary and assumes the URI is
  * not fully qualified.
  */
 u8_t                      replyToHref[SL_CMN_REPLY_TO_HREF_LEN];
 /**
  * Boolean indicating whether the replyToHref is included.
  */
 bool                      replyToHrefExists;
 /**
  * Indicates information about the server serving this event. Generally
  * this information is used for response purposes.
  */
 sl_cmn_server_info_t      serverInfo;
 /**
  * Boolean indicating whether the serverInfo is included.
  */
 bool                      serverInfoExists;
} sl_cmn_client_resp_info_t;

/******************************************************************************/
/**
 * \struct sl_cmn_event_t
 * This structure contains details for a particular event.
 */
typedef struct {
  /**
   * Indicates the time the resource is created. This is an optional field
   * that may be used if the Server APP would like to specify the
   * creation time. if it is used, the creationTimeExists field
   * should be set to true.
   */
  sl_xsd_time_type_t       creationTime;
  /**
   * Character array providing a description of the event, with max length
   * of \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                     description[SL_XSD_DESCRIPTION_LEN];
  /**
   * The length of time the event is active following the start time.
   */
  u32_t                    duration;
  /**
   * Unique MRID for this event of max length SL_XSD_MRID_LEN.
   */
  u8_t                     mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates whether or not a response is required upon receipt or update
   * of this resource.
   */
  sl_xsd_resp_req_bitmap_t respRequired;
  /**
   * The time at which the event starts.
   */
  sl_xsd_time_type_t       start;
} sl_cmn_event_t;

/******************************************************************************/
/**
 * \struct sl_cmn_rand_event_t
 * This structure contains details for a particular randomizable event.
 */
typedef struct {
  /**
   * Contains details of the event.
   */
  sl_cmn_event_t           event;
  /**
   * Number of seconds boundary inside which a random value must be selected to
   * be applied to the event end time, to avoid sudden synchronized demand changes.
   * If 0, randomization will not be applied.
   */
  i16_t                    randomDuration;
  /**
   * Number of seconds boundary inside which a random value must be selected to
   * be applied to the event start time, to avoid sudden synchronized demand changes.
   * If 0, randomization will not be applied.
   */
  i16_t                    randomStart;
} sl_cmn_rand_event_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_root_list_t
 * This structure contains common information use to identify a list of function set
 * roots to be used for event processing.  A root represents a unique URI and
 * therefore a unique resource or list of resources.  A root is defined by a
 * server id and a URI source that has been received for that server.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The list of event roots.
   */
  sl_cmn_client_server_source_info_t  list[SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS];
} sl_cmn_client_root_list_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_server_ind_t
 * This structure contains common information use to identify a function set server.
 * The server and source information is used in event processing to specify which
 * servers are selected in \ref sl_cmn_client_set_event_roots_req_t.  The server
 * and source information is also used in list processing to specify which root
 * node to get in \ref sl_cmn_get_list_req_root_t.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Handle associated with the particular server.
   */
  sl_cmn_client_server_handle_t    serverHandle;
  /**
   * Indicates the status of the current server (received/deleted/server lost).
   */
  sl_cmn_server_status_t           status;
  /**
   * The DNS name associated with the particular server.
   */
  char                             serverName[SL_CMN_CLIENT_SERVER_NAME_LEN];
  /**
   * A flag indicating if the client is successfully registered on the server.
   */
  bool                             registered;
  /**
   * Number of valid entries in the \ref sourceList array, up to \ref SL_CMN_CLIENT_MAX_NUM_ROOT_SOURCES.
   */
  u8_t                             numSources;
  /**
   * Root source information associated with the particular server.
   */
  sl_cmn_client_root_info_t        sourceList[SL_CMN_CLIENT_MAX_NUM_ROOT_SOURCES];
} sl_cmn_client_server_ind_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_set_event_roots_req_t
 * This structure contains common information sent to set the list of roots
 * to be used for event processing.
 */
typedef struct {
  /**
   * The number of entries in \ref rootList up to \ref SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS.
   */
  u8_t                            numRoots;
  /**
   * The list of roots selected by the application for a function set.
   */
  sl_cmn_client_root_list_t       rootList;
} sl_cmn_client_set_event_roots_req_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_set_event_roots_cnf_t
 * This structure contains common information sent in confirmation of a request
 * to set the list of roots for event processing.
 */
typedef struct {
   /**
    * Status indicating whether the request was successful or not.
    */
   sl_cmn_rc_t                     status;
} sl_cmn_client_set_event_roots_cnf_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_event_roots_ind_t
 * This structure contains common information sent to the application indicating
 * a change to the list of server roots that are being used for event processing.
 */
typedef struct {
  /**
   * The reason that the list of available roots has been changed.
   */
  sl_cmn_client_root_change_t       rootChangeReason;
  /**
   * The number of entries in \ref rootList up to \ref SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS.
   */
  u8_t                              numRoots;
  /**
   * The list of servers selected by the application for a function set.
   */
  sl_cmn_client_root_list_t         rootList;
} sl_cmn_client_event_roots_ind_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_set_event_poll_rate_req_t
 * This structure contains common information sent to set the polling rate for
 * events.
 */
typedef struct {
  /**
   * Indicates whether the default poll rate should be used, or the value set in
   * pollRate;
   */
  bool                  setPollRate;
  /**
   * If setPollRate is set to true, pollRate sets the polling rate to be
   * used in seconds.  If pollRate is set to 0 then the event polling will be disabled.
   * If setPollRate is set to false then this value is not used and the default
   * poll rate will be used.
   */
  u32_t                 pollRate;
} sl_cmn_client_set_event_poll_rate_req_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_set_event_poll_rate_cnf_t
 * This structure contains common information sent in confirmation of a request
 * to set the polling rate for events.
 */
typedef struct {
   /**
    * Status indicating whether the request was successful or not.
    */
   sl_cmn_rc_t status;
} sl_cmn_client_set_event_poll_rate_cnf_t;

/******************************************************************************/
/**
 * \struct sl_cmn_cancel_get_list_cnf_t
 * This structure contains common information sent in confirmation of a request
 * to cancel getting a list.
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                transactionId;
} sl_cmn_cancel_get_list_cnf_t;

/******************************************************************************/
/**
 * \struct sl_cmn_cancel_get_list_req_t
 * This structure contains common information sent to cancel a request to get a
 * list.
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                transactionId;
} sl_cmn_cancel_get_list_req_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_program_list_t
 * This structure contains common information defining the list of programs that
 * are used for event processing.
 */
typedef struct {
  /**
   * Array of length \ref SL_CMN_CLIENT_MAX_NUM_EVENT_PROGRAMS containing the mrIds
   * of length \ref SL_XSD_MRID_LEN of the program/parent of a list used for
   * event processing.
   */
  u8_t               mrId[SL_CMN_CLIENT_MAX_NUM_EVENT_PROGRAMS][SL_XSD_MRID_LEN];
} sl_cmn_client_program_list_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_set_event_programs_req_t
 * This structure contains common information sent to set the list of programs
 * to be used for event processing.
 */
typedef struct {
  /**
   * The number of entries in \ref list up to \ref SL_CMN_CLIENT_MAX_NUM_EVENT_PROGRAMS.
   */
  u8_t                       numListEntries;
  /**
   * The list of unique programs used for event processing.
   */
  sl_cmn_client_program_list_t  list;
} sl_cmn_client_set_event_programs_req_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_set_event_programs_cnf_t
 * This structure contains common information sent in confirmation of a request
 * to set the list of roots for event processing.
 */
typedef struct {
   /**
    * Status indicating whether the request was successful or not.
    */
   sl_cmn_rc_t status;
} sl_cmn_client_set_event_programs_cnf_t;

/******************************************************************************/
/**
 * \struct sl_cmn_client_event_programs_ind_t
 * This structure contains common information sent to the application indicating
 * a change to the list of programs that are being used for event processing.
 */
typedef struct {
  /**
   * The reason that the program list has been changed.
   */
  sl_cmn_client_prog_change_t  progChangeReason;
  /**
   * The number of entries in \ref list up to \ref SL_CMN_CLIENT_MAX_NUM_EVENT_PROGRAMS.
   */
  u8_t                         numListEntries;
  /**
   * The list of unique programs used for event processing.
   */
  sl_cmn_client_program_list_t list;
} sl_cmn_client_event_programs_ind_t;

/******************************************************************************/
/**
 * \struct sl_cmn_get_list_cnf_t
 * This structure contains common information sent in confirmation of a request
 * to get a list.
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t       transactionId;
   /**
    * Status indicating whether the request was successful or not. If the
    * request is successful, received resources will be sent in indications.
    */
   sl_cmn_rc_t status;
} sl_cmn_get_list_cnf_t;

/******************************************************************************/
/**
 * \struct sl_cmn_get_list_req_quantity_t
 * This structure contains common information sent to request a list of resources
 * that may only be requested by quantity.
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                transactionId;
   /**
    * Unique MRID for the parent resource of the requested resource, of max length
    * SL_XSD_MRID_LEN.
    */
   u8_t                 parentMrId[SL_XSD_MRID_LEN];
   /**
    * This is the number of resources that are being requested by the application,
    * where \ref SL_CMN_CLIENT_GET_ENTIRE_LIST may be used to indicate that the
    * application is requesting all available resources. Note that there may be
    * fewer than numResources available so less than this number may be returned.
    */
   u8_t                 numResources;
} sl_cmn_get_list_req_quantity_t;

/******************************************************************************/
/**
 * \struct sl_cmn_get_list_req_root_t
 * This structure contains common information sent to request a list of resources
 * that do not have a parent resource and may only be requested by quantity.
 */
typedef struct {
  /**
   * This is the number of resources that are being requested by the application,
   * where \ref SL_CMN_CLIENT_GET_ENTIRE_LIST may be used to indicate that the
   * application is requesting all available resources. Note that there may be
   * fewer than numResources available so less than this number may be returned.
   */
  u8_t                                 numResources;
  /**
   * Server and source information for the list of interest. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                               transactionId;
} sl_cmn_get_list_req_root_t;

/******************************************************************************/
/**
 * \struct sl_cmn_get_list_req_time_t
 * This structure contains common information sent to request a list of resources
 * that may be requested by quantity and time.
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                     transactionId;
   /**
    * Unique MRID for the parent resource of the requested resource, of max length
    * SL_XSD_MRID_LEN.
    */
   u8_t                      parentMrId[SL_XSD_MRID_LEN];
   /**
    * Type of amount that is being requested.
    *
    * If this is set to \ref SL_CMN_LIST_AMOUNT_TYPE_QUANTITY, then the \ref numResources
    * field indicates the number of resources and the \ref startRange and \ref endRange fields
    * are ignored.
    *
    * If this is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_RANGE, then the
    * \ref startRange and \ref endRange fields indicate the time range and the
    * \ref numResources field indicates the maximum number of resources in that
    * time range.
    *
    * If this is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_IN_MINUTES, then the
    * \ref numMinutes field indicates the number of minutes worth of resources to get
    * and the \ref numResources field indicates the maximum number of resources in
    * that time range.
    *
    * All other values for this field are invalid.
    */
   sl_cmn_list_amount_type_t amountType;
   /**
    * This is the number of resources that are being requested by the application,
    * where \ref SL_CMN_CLIENT_GET_ENTIRE_LIST may be used to indicate that the
    * application is requesting all available resources. Note that there may be
    * fewer than \ref numResources available so less than this number may be returned.
    */
   u8_t                      numResources;
   /**
    * If \ref amountType is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_IN_MINUTES this field
    * indicates the number of minutes worth of resources to get. The number of minutes
    * may be in the future or past depending on the sort direction of the list.
    * If the list is specified to be sorted in ascending order this field defines
    * the number of minutes from now in the future.  If this list is specified to
    * be sorted in descending order this field defines the number of minutes from
    * now in the past.
    */
   u32_t                     numMinutes;
   /**
    * If \ref amountType is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_RANGE this field
    * indicates the start of the time range to get resources.
    */
   sl_xsd_time_type_t        startRange;
   /**
    * If \ref amountType is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_RANGE this field
    * indicates the end of the time range to get resources.
    */
   sl_xsd_time_type_t        endRange;
} sl_cmn_get_list_req_time_t;

/******************************************************************************/
/**
 * \struct sl_cmn_list_ind_t
 * This structure contains common information sent in indications resulting from
 * a request to get a list.
 */
typedef struct {
/**
 * transactionId is used to match the associated confirmation and indication
 * messages with the initial request message.
 */
u32_t                  transactionId;
/**
 * Status indicating the current state of the operation. If the client is still
 * processing resources, it will return a status of \ref SL_CMN_RC_OPERATION_IN_PROG.
 * If it is done handling the request, it will return a status of \ref SL_CMN_RC_OPERATION_DONE.
 * If there has been an error, it will return the appropriate error status and stop
 * processing. If an error status is received, the app client should not expect
 * to receive any more indications.
 */
sl_cmn_rc_t            status;
/**
 * Start offset indicates the index of this set of resources in the total number of resources
 * that have been or will be sent in indications.
 */
u16_t                  startOffset;
/**
 * Total number of resources included in the indication.
 */
u8_t                   numList;
/**
 * Total number of resources available in the server list.
 */
u16_t                  all;
/**
 * Indicates whether pollRate exists in this structure.
 */
bool                   pollRateExists;
/**
 * Polling rate in seconds.
 */
u32_t                  pollRate;
} sl_cmn_list_ind_t;

/******************************************************************************/
/**
 * \struct sl_cmn_rt_t
 * This structure contains data fields associated with a Reading Type resource.
 */
typedef struct {
  /**
   * The accumulation behaviour indicates how the value is represented
   * to accumulate over time.
   */
  sl_xsd_acc_behavior_type_t accumulationBehaviour;
  /**
   * The amount of heat generated when a given mass of fuel is completely burned.
   * The CalorificValue is used to convert the measured volume or mass of gas into kWh.
   * The CalorificValue attribute represents the current active value.
   */
  sl_xsd_unit_val_t          calorificValue;
  /**
   * Accounts for changes in the volume of gas based on temperature and pressure.
   * The ConversionFactor attribute represents the current active value.
   * The ConversionFactor is dimensionless. The default value for the ConversionFactor
   * is 1, which means no conversion is applied. A price server can advertise a new/different
   * value at any time.
   */
  sl_xsd_unit_val_t          conversionFactor;
  /**
   * Indicates the commodity applicable to this ReadingType.
   */
  sl_xsd_commodity_type_t    commodity;
  /**
   * The data type can be used to describe a salient attribute of the data.
   * Possible values are average, absolute, and etc.
   */
  sl_xsd_data_qual_type_t    dataQualifier;
  /**
   * Anything involving current might have a flow direction. Possible values
   * include forward and reverse.
   */
  sl_xsd_flow_dir_type_t     flowDirection;
  /**
   * Default interval length specified in seconds for Readings of ReadingType.
   */
  u32_t                      intervalLength;
  /**
   * Boolean indicating whether or not the interval length field is present in the
   * reading type.
   */
  bool                       intervalLengthExists;
  /**
   * Compound class that contains kindCategory and kindIndex.
   */
  sl_xsd_kind_type_t         kindType;
  /**
   * For mirrors of interval data, sets the expected number of intervals per ReadingSet.
   */
  u8_t                       maxNumIntervals;
  /**
   * Boolean indicating whether or not the maxNumIntervals field is present in the
   * reading type.
   */
  bool                       maxNumIntervalsExists;
  /**
  * Number of consumption blocks (0 is equivalent to 1, and greater than 15
  * is equal to 15).
  */
  u8_t                       numConsumBlocks;
  /**
   * Boolean indicating whether or not the number of consumption blocks field is present in the
   * reading type.
   */
  bool                       numConsumBlocksExists;
  /**
   * The number of TOU tiers that can be used by any resource configured by this ReadingType.
   *  Servers SHALL populate this value with the largest touTier value that will ever be used
   *  while this ReadingType is in effect. Servers SHALL set numberOfTouTiers equal to the
   *  number of standard TOU tiers plus the number of CPP tiers that may be used while this
   *  ReadingType is in effect. Servers SHALL specify a value between 1 and 15 (inclusive)
   *  for numberOfTouTiers (servers providing flat rate pricing SHALL set numberOfTouTiers to 1,
   *  as in practice there is no difference between having no tiers and having one tier).
   */
  u8_t                       numTouTiers;
  /**
   * Boolean indicating whether or not the number of TOU tiers field is present in the
   * reading type.
   */
  bool                       numTouTiersExists;
  /**
   * Contains phase information associated with the type.
   */
  sl_xsd_phase_code_type_t   phaseCode;
  /**
   * Indicates the power of ten multiplier applicable to the unit of measure of this ReadingType.
   */
  sl_xsd_ptm_type_t          powerOfTenMultiplier;
  /**
   * Default sub-interval length specified in seconds for Readings of ReadingType.
   */
  u32_t                      subIntervalLength;
  /**
   * Boolean indicating whether or not the subIntervalLength field is present in the
   * reading type.
   */
  bool                       subIntervalLengthExists;
  /**
   * Reflects the supply limit set in the meter. This value can be compared to the
   * Reading value to understand if limits are being approached or exceeded. Units
   * follow the same definition as in this ReadingType.
   */
  u64_t                      supplyLimit;
  /**
   * Boolean indicating whether or not the supplyLimit field is present in the
   * reading type.
   */
  bool                       supplyLimitExists;
  /**
   * Specifies whether or not the consumption blocks are differentiated by TOUTier or not.
   *  Default is false, if not specified.
   * true = consumption accumulated over individual tiers
   * false = consumption accumulated over all tiers
   */
  bool                       tieredConsumptionBlocks;
  /**
   * Boolean indicating whether or not the tierdConsumptionBlocks field is present in the
   * reading type.
   */
  bool                       tieredConsumptionBlocksExists;
  /**
   * Compound class that contains metricPrefix, uomCategory, and uomIndex.
   */
  sl_xsd_uom_t               uomType;
} sl_cmn_rt_t;

/******************************************************************************/
/**
 * \struct sl_cmn_rcomp_t
 * This structure contains data fields associated with a Rate Component resource.
 */
typedef struct {
  /**
   * Unique MRID for this RC of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t               mrId[SL_XSD_MRID_LEN];
  /**
   * Array providing a description of the RC, with max
   * length of \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char               description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Specifies the maximum flow rate (e.g. kW for electricity) for which this RC applies,
   * for the usage point and given rate / tariff. In combination with startLimit, allows
   * a service provider to define the demand or output characteristics for the particular
   * tariff design. If a server includes the startLimit attribute, then it SHALL also include
   * endLimit attribute.
   */
  sl_xsd_unit_val_t  endLimit;
  /**
   * Specifies the minimum flow rate (e.g., kW for electricity) for which this RC applies,
   * for the usage point and given rate / tariff. In combination with endLimit, allows a
   * service provider to define the demand or output characteristics for the particular
   * tariff design. If a server includes the startLimit attribute, then it SHALL also include
   * endLimit attribute.
   */
  sl_xsd_unit_val_t  startLimit;
  /**
   * Specifies the roles that this usage point has been assigned.
   */
  sl_xsd_role_flag_t roleFlag;
  /**
   * Reading type information associated with the RC.
   */
  sl_cmn_rt_t        rtype;
} sl_cmn_rcomp_t;

/******************************************************************************/
/**
 * \struct sl_cmn_up_t
 * This structure contains the data fields associated with a Usage Point resource.
 */
typedef struct {
  /**
   * Array providing a human readable description of the Usage Point,
   * with max length of SL_XSD_DESCRIPTION_LEN. Character array must be
   * null terminated.
   */
  char               description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for this Usage Point of length SL_XSD_MRID_LEN.
   */
  u8_t               mrId[SL_XSD_MRID_LEN];
  /**
   * Specifies the roles that apply to this usage point.
   */
  sl_xsd_role_flag_t roleFlags;
  /**
   * Specifies the kind of service provided by this usage point.
   */
  sl_xsd_service_t   serviceKind;
  /**
   * Specifies the current status of the service at this usage point.
   */
  sl_xsd_status_t    status;
  /**
   * Boolean indicating whether the lfdi field is included for this UP or not.
   */
  bool               lFDIExists;
  /**
   * Specifies the lFDI of the device at this usage point.
   */
  u8_t               lFDI[SL_XSD_LFDI_LEN];
} sl_cmn_up_t;

/** @} */
// end addtogroup COMMON_GROUP_STRUCTS

/** @} */
// end addtogroup COMMON_GROUP


/*******************************************************************************
 * Server Object Defines and Structures
 ******************************************************************************/
/**
 * \defgroup OBJ_GROUP Server Object Definitions and Structures
 * This section contains definitions and structures used with the SL_SERVER_OBJ_XXXXX
 * mail messages.
 */
/** \addtogroup OBJ_GROUP
 * @{ */

/**
 * \defgroup OBJ_GROUP_DEFINES Object Defines
 * This section contains definitions used with the SL_SERVER_OBJ_XXXXX mail message.
 */
/** \addtogroup OBJ_GROUP_DEFINES
 * @{ */

/** SL_OBJ_MAX_NUM_INSTANCE_ID - Defines the maximum # of possible instance Ids used in a SEP reference */
#define SL_OBJ_MAX_NUM_INSTANCE_ID (6)

/** SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID - Defines the # of instance Ids required to reference a "top level" resource */
#define SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID (2)

/** @} */
// end addtogroup OBJ_GROUP_DEFINES

/**
 * \defgroup OBJ_GROUP_TYPES Object Types
 * This section contains type definitions used with the SL_SERVER_OBJ_XXXXX mail messages.
 */
/** \addtogroup OBJ_GROUP_TYPES
 * @{ */

/*******************************************************************************/
/**
 * \defgroup SL_OBJ_ID_XXX Object Id Type: sl_obj_id_t (SL_OBJ_ID_XXX)
 * This section contains type definitions of the object Ids used with the
 * SL_SERVER_OBJ_XXXXX  mail messages (e.g., \ref SL_SERVER_OBJ_CREATE_REQ,
 * \ref SL_SERVER_OBJ_CREATE_CNF, \ref SL_SERVER_OBJ_CANCEL_REQ,
 * \ref SL_SERVER_OBJ_CANCEL_CNF. It is also used in the mail messages to
 * pass server event status indications (e.g., \ref SL_DER_SERVER_EVENT_STATUS_IND) which
 * use the \ref sl_server_obj_event_status_ind_t structure.
 *
 * The nomenclature being used in these definitions contain the full resource dependency
 * and ordering specified by the SEP spec. In this definition, resources and lists
 * are subordinate to parent resources (or lists). Parent resources/lists appear in
 * front of subordinate resources (or lists).
 *
 * Referencing an object in SEP involves specifying one of these Object Id definitions
 * and any associated instance IDs that are needed to fully reference the object.
 * Each _X_ denotes an instance ID that must be specified in order to complete the
 * reference. The first _X_ always denotes a group ID, subsequent _X_s refer to
 * resource instance IDs that are needed for that reference. Group IDs appear only
 * at the beginning of the reference and are required for function set assignment
 * (FSA). For consistency reasons, the Group ID is used in all of the references even
 * references that do not use FSA, in these cases the default group ID value is used
 * (SL_OBJ_INSTANCE_DEF_GRP_ID).
 */

/** \addtogroup SL_OBJ_ID_XXX
 * @{ */
/**
 * \var typedef u16_t sl_obj_id_t
 * Acceptable values are SL_OBJ_ID_XXX.
 */
typedef u16_t sl_obj_id_t;

/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_BILL - Defines the list of Customer Agreement resource types.  */
#define  SL_OBJ_ID_X_BILL                         (0)
/**  SL_OBJ_ID_X_BILL_X - Defines an individual Customer Agreement resource type.  */
#define  SL_OBJ_ID_X_BILL_X                       (1)
/**  SL_OBJ_ID_X_BILL_X_SS - Defines an individual Service Supplier resource type.  */
#define  SL_OBJ_ID_X_BILL_X_SS                    (2)
/**  SL_OBJ_ID_X_BILL_X_CA - Defines the list of Customer Account resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA                    (3)
/**  SL_OBJ_ID_X_BILL_X_CA_X - Defines an individual Customer Account resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X                  (4)
/**  SL_OBJ_ID_X_BILL_X_CA_X_ACTBP - Defines the list of active Billing Period resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_ACTBP            (5)
/**  SL_OBJ_ID_X_BILL_X_CA_X_ACTBP_X - Defines an individual active Billing Period resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_ACTBP_X          (6)
/**  SL_OBJ_ID_X_BILL_X_CA_X_BP - Defines the list of Billing Period resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_BP               (7)
/**  SL_OBJ_ID_X_BILL_X_CA_X_BP_X - Defines an individual Billing Period resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_BP_X             (8)
/**  SL_OBJ_ID_X_BILL_X_CA_X_ACTPRO - Defines the list of active projected reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_ACTPRO           (9)
/**  SL_OBJ_ID_X_BILL_X_CA_X_ACTPRO_X - Defines an individual active projected reading resource type.  */
#define  SL_OBJ_ID_X_BILL_X_CA_X_ACTPRO_X         (10)
/**  SL_OBJ_ID_X_BILL_X_CA_X_PRO - Defines the list of projected reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_PRO              (11)
/**  SL_OBJ_ID_X_BILL_X_CA_X_VER - Defines the list of historical reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_VER              (12)
/**  SL_OBJ_ID_X_BILL_X_CA_X_TAR - Defines the list of targeted reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_TAR              (13)
/**  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X - Defines an individual projected reading resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X            (14)
/**  SL_OBJ_ID_X_BILL_X_CA_X_VER_X - Defines an individual historical reading resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_VER_X            (15)
/**  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X - Defines an individual targeted reading resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X            (16)
/**  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS - Defines the list of projected billing reading set resource types.  */
#define  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS        (17)
/**  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS - Defines the list of historical billing reading set resource types.  */
#define  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS        (18)
/**  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS - Defines the list of targeted billing reading set resource types.  */
#define  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS        (19)
/**  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X - Defines an individual projected billing reading set resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X      (20)
/**  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X - Defines an individual historic billing reading set resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X      (21)
/**  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X - Defines an individual targeted billing reading set resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X      (22)
/**  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X_BR - Defines the list of projected billing reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X_BR   (23)
/**  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X_BR - Defines the list of historical billing reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X_BR   (24)
/**  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X_BR - Defines the list of targeted billing reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X_BR   (25)
/**  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X_BR_X - Defines an individual projected billing reading resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X_BR_X (26)
/**  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X_BR_X - Defines an individual historical billing reading resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X_BR_X (27)
/**  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X_BR_X - Defines an individual targeted billing reading resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X_BR_X (28)
/**  SL_OBJ_ID_X_BILL_X_CA_X_ACTTAR - Defines the list of active targeted reading resource types. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_ACTTAR           (29)
/**  SL_OBJ_ID_X_BILL_X_CA_X_ACTTAR_X - Defines an individual active targeted reading resource type. */
#define  SL_OBJ_ID_X_BILL_X_CA_X_ACTTAR_X         (30)

/**  SL_OBJ_ID_X_DCAP - Defines the device capabilities resource type. */
#define  SL_OBJ_ID_X_DCAP                         (31)

/**  SL_OBJ_ID_X_DERP - Defines the list of distributed energy program resource types. */
#define  SL_OBJ_ID_X_DERP                         (32)
/** \endcond */
/**  SL_OBJ_ID_X_DERP_X - Defines an individual distributed energy program resource type. */
#define  SL_OBJ_ID_X_DERP_X                       (33)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_DERP_X_ACTDERC - Defines the list of active distributed energy control resource types. */
#define  SL_OBJ_ID_X_DERP_X_ACTDERC               (34)
/**  SL_OBJ_ID_X_DERP_X_ACTDERC_X - Defines an individual distributed energy control resource type. */
#define  SL_OBJ_ID_X_DERP_X_ACTDERC_X             (35)
/**  SL_OBJ_ID_X_DERP_X_DERC - Defines the list of distributed energy control resource types. */
#define  SL_OBJ_ID_X_DERP_X_DERC                  (36)
/** \endcond */
/**  SL_OBJ_ID_X_DERP_X_DERC_X - Defines an individual distributed energy control resource type. */
#define  SL_OBJ_ID_X_DERP_X_DERC_X                (37)
/**  SL_OBJ_ID_X_DERP_X_DDERC - Defines the individual Default DERC resource type. */
#define  SL_OBJ_ID_X_DERP_X_DDERC                 (38)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_DERP_X_DC - Defines the list of DC resource types. */
#define  SL_OBJ_ID_X_DERP_X_DC                    (39)
/** \endcond */
/**  SL_OBJ_ID_X_DERP_X_DC_X - Defines an individual DC resource type. */
#define  SL_OBJ_ID_X_DERP_X_DC_X                  (40)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_DR - Defines the list of demand control program resource types.  */
#define  SL_OBJ_ID_X_DR                           (41)
/** \endcond */
/**  SL_OBJ_ID_X_DR_X - Defines an individual demand control program resource type. */
#define  SL_OBJ_ID_X_DR_X                         (42)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_DR_X_EDC - Defines the list of end device control resource types. */
#define  SL_OBJ_ID_X_DR_X_EDC                     (43)
/** \endcond */
/**  SL_OBJ_ID_X_DR_X_EDC_X - Defines an individual end device control resource type. */
#define  SL_OBJ_ID_X_DR_X_EDC_X                   (44)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_DR_X_AEDC - Defines the list of active end device control resource types. */
#define  SL_OBJ_ID_X_DR_X_AEDC                    (45)
/**  SL_OBJ_ID_X_DR_X_AEDC_X - Defines an individual active end device control resource type. */
#define  SL_OBJ_ID_X_DR_X_AEDC_X                  (46)

/**  SL_OBJ_ID_X_EDEV - Defines the list of end device resource types. */
#define  SL_OBJ_ID_X_EDEV                         (47)
/** \endcond */
/**  SL_OBJ_ID_X_EDEV_X - Defines an individual end evice resource type. */
#define  SL_OBJ_ID_X_EDEV_X                       (48)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_EDEV_X_RG - Defines an end device registration resource type. */
#define  SL_OBJ_ID_X_EDEV_X_RG                    (49)
/**  SL_OBJ_ID_X_EDEV_X_DER - Defines the list of DER resource types. */
#define  SL_OBJ_ID_X_EDEV_X_DER                   (50)
/**  SL_OBJ_ID_X_EDEV_X_DER_X - Defines an individual DER resource type. */
#define  SL_OBJ_ID_X_EDEV_X_DER_X                 (51)
/** \endcond */
/**  SL_OBJ_ID_X_EDEV_X_DER_X_DERS - Defines the DER Status resource type. */
#define  SL_OBJ_ID_X_EDEV_X_DER_X_DERS            (52)
/**  SL_OBJ_ID_X_EDEV_X_DER_X_DERA - Defines the DER Availability resource type. */
#define  SL_OBJ_ID_X_EDEV_X_DER_X_DERA            (53)
/**  SL_OBJ_ID_X_EDEV_X_DER_X_DERCAP - Defines the DER Capabilities resource type. */
#define  SL_OBJ_ID_X_EDEV_X_DER_X_DERCAP          (54)
/**  SL_OBJ_ID_X_EDEV_X_DER_X_DERG - Defines the DER Settings resource type. */
#define  SL_OBJ_ID_X_EDEV_X_DER_X_DERG            (55)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_EDEV_X_DI - Defines the device information resource type. */
#define  SL_OBJ_ID_X_EDEV_X_DI                    (56)
/**  SL_OBJ_ID_X_EDEV_X_DSTAT - Defines the device status resource type. */
#define  SL_OBJ_ID_X_EDEV_X_DSTAT                 (57)
/**  SL_OBJ_ID_X_EDEV_X_CFG - Defines the configuration resource type. */
#define  SL_OBJ_ID_X_EDEV_X_CFG                   (58)
/**  SL_OBJ_ID_X_EDEV_X_FRP - Defines the list of flow response resource types. */
#define  SL_OBJ_ID_X_EDEV_X_FRP                   (59)
/** \endcond */

/**  SL_OBJ_ID_X_EDEV_X_FRP_X - Defines an individual flow response resource type. */
#define  SL_OBJ_ID_X_EDEV_X_FRP_X                 (60)

/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_EDEV_X_FRQ - Defines the list of flow request resource types. */
#define  SL_OBJ_ID_X_EDEV_X_FRQ                   (61)
/** \endcond */

/**  SL_OBJ_ID_X_EDEV_X_FRQ_X - Defines an individual flow request resource type. */
#define  SL_OBJ_ID_X_EDEV_X_FRQ_X                 (62)

/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_EDEV_X_FILE - Defines a file status resource type. */
#define  SL_OBJ_ID_X_EDEV_X_FILE                  (63)
/**  SL_OBJ_ID_X_EDEV_X_LEL - Defines the list of log event log resource types. */
#define  SL_OBJ_ID_X_EDEV_X_LEL                   (64)
/**  SL_OBJ_ID_X_EDEV_X_LEL_X - Defines an individual log event resource type. */
#define  SL_OBJ_ID_X_EDEV_X_LEL_X                 (65)
/**  SL_OBJ_ID_X_EDEV_X_LSA - Defines the list of load shed availability resource types. */
#define  SL_OBJ_ID_X_EDEV_X_LSA                   (66)
/**  SL_OBJ_ID_X_EDEV_X_LSA_X - Defines a load shed availability resource type. */
#define  SL_OBJ_ID_X_EDEV_X_LSA_X                 (67)
/**  SL_OBJ_ID_X_EDEV_X_SUB - Defines the list of subscription resource types. */
#define  SL_OBJ_ID_X_EDEV_X_SUB                   (68)
/**  SL_OBJ_ID_X_EDEV_X_SUB_X - Defines an individual subscription resource type. */
#define  SL_OBJ_ID_X_EDEV_X_SUB_X                 (69)
/**  SL_OBJ_ID_X_EDEV_X_PS - Defines a power status resource type. */
#define  SL_OBJ_ID_X_EDEV_X_PS                    (70)
/**  SL_OBJ_ID_X_FILE - Defines the list of file resource types. */
#define  SL_OBJ_ID_X_FILE                         (71)
/**  SL_OBJ_ID_X_FILE_X - Defines an individual file resource type. */
#define  SL_OBJ_ID_X_FILE_X                       (72)
/**  SL_OBJ_ID_X_FILE_X_DATA - Defines a file data resource type. */
#define  SL_OBJ_ID_X_FILE_X_DATA                  (73)
/**  SL_OBJ_ID_X_FSA - Defines the list of function set assignment resource types. */
#define  SL_OBJ_ID_X_FSA                          (74)
/** \endcond */
/**  SL_OBJ_ID_X_FSA_X - Defines an individual function set assignment resource type. */
#define  SL_OBJ_ID_X_FSA_X                        (75)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_MUP - Defines the list of mirror usage point resource types. */
#define  SL_OBJ_ID_X_MUP                          (76)
/**  SL_OBJ_ID_X_MUP_X - Defines an individual mirror usage point resource type. */
#define  SL_OBJ_ID_X_MUP_X                        (77)
/**  SL_OBJ_ID_X_MUP_X_MMR - Defines the list of mirror meter reading resource types. */
#define  SL_OBJ_ID_X_MUP_X_MMR                    (78)
/**  SL_OBJ_ID_X_MUP_X_MMR - Defines an individual mirror meter reading resource type.  */
#define  SL_OBJ_ID_X_MUP_X_MMR_X                  (79)
/** \endcond */
/**  SL_OBJ_ID_X_MSG - Defines the list of messaging program resource types. */
#define  SL_OBJ_ID_X_MSG                          (80)
/**  SL_OBJ_ID_X_MSG_X - Defines an individual messaging program resource type. */
#define  SL_OBJ_ID_X_MSG_X                        (81)
/**  SL_OBJ_ID_X_MSG_X_TXT - Defines the list of text message resource types. */
#define  SL_OBJ_ID_X_MSG_X_TXT                    (82)
/**  SL_OBJ_ID_X_MSG_X_TXT_X - Defines an individual text message resource type. */
#define  SL_OBJ_ID_X_MSG_X_TXT_X                  (83)
/**  SL_OBJ_ID_X_MSG_X_ACTTXT - Defines the list of active text message resource types. */
#define  SL_OBJ_ID_X_MSG_X_ACTTXT                 (84)
/**  SL_OBJ_ID_X_MSG_X_ACTTXT_X - Defines an individual active text message resource type. */
#define  SL_OBJ_ID_X_MSG_X_ACTTXT_X               (85)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_NTFY - Defines the list of subscription notification resource types. */
#define  SL_OBJ_ID_X_NTFY                         (86)
/**  SL_OBJ_ID_X_NTFY_X - Defines an individual subscription notification resource type. */
#define  SL_OBJ_ID_X_NTFY_X                       (87)

/**  SL_OBJ_ID_X_PPY - Defines the list of pre-payment resource types. */
#define  SL_OBJ_ID_X_PPY                          (88)
/**  SL_OBJ_ID_X_PPY_X - Defines an individual pre-payment resource type. */
#define  SL_OBJ_ID_X_PPY_X                        (89)
/**  SL_OBJ_ID_X_PPY_X_AB - Defines an account balance resource type. */
#define  SL_OBJ_ID_X_PPY_X_AB                     (90)
/**  SL_OBJ_ID_X_PPY_X_OS - Defines a pre-payment operation status resource type. */
#define  SL_OBJ_ID_X_PPY_X_OS                     (91)
/**  SL_OBJ_ID_X_PPY_X_ACTSI - Defines the list of active supply interruption override resource types. */
#define  SL_OBJ_ID_X_PPY_X_ACTSI                  (92)
/**  SL_OBJ_ID_X_PPY_X_ACTSI_X - Defines an individual active supply interruption override resource type. */
#define  SL_OBJ_ID_X_PPY_X_ACTSI_X                (93)
/**  SL_OBJ_ID_X_PPY_X_SI - Defines the list of supply interruption override resource types. */
#define  SL_OBJ_ID_X_PPY_X_SI                     (94)
/**  SL_OBJ_ID_X_PPY_X_SI_X - Defines an individual supply interruption override resource type. */
#define  SL_OBJ_ID_X_PPY_X_SI_X                   (95)
/**  SL_OBJ_ID_X_PPY_X_ACTCR - Defines the list of active credit register resource types. */
#define  SL_OBJ_ID_X_PPY_X_ACTCR                  (96)
/**  SL_OBJ_ID_X_PPY_X_ACTCR_X - Defines an individual active credit register resource type. */
#define  SL_OBJ_ID_X_PPY_X_ACTCR_X                (97)
/**  SL_OBJ_ID_X_PPY_X_CR - Defines the list of credit register resource types. */
#define  SL_OBJ_ID_X_PPY_X_CR                     (98)
/**  SL_OBJ_ID_X_PPY_X_CR_X - Defines an individual credit register resource type. */
#define  SL_OBJ_ID_X_PPY_X_CR_X                   (99)
/** \endcond */
/**  SL_OBJ_ID_X_RSPS - Defines the list of response set resource types. */
#define  SL_OBJ_ID_X_RSPS                         (100)
/**  SL_OBJ_ID_X_RSPS_X - Defines an individual response set resource type. */
#define  SL_OBJ_ID_X_RSPS_X                       (101)
/**  SL_OBJ_ID_X_RSPS_X_RSP - Defines the list of response resource types. */
#define  SL_OBJ_ID_X_RSPS_X_RSP                   (102)
/**  SL_OBJ_ID_X_RSPS_X_RSP_X - Defines an individual response resource type. */
#define  SL_OBJ_ID_X_RSPS_X_RSP_X                 (103)
/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_SDEV - Defines the self device resource type. */
#define  SL_OBJ_ID_X_SDEV                         (104)
/**  SL_OBJ_ID_X_SDEV_SCFG - Defines the self config resource type. */
#define  SL_OBJ_ID_X_SDEV_SCFG                    (105)
/**  SL_OBJ_ID_X_SDEV_DER - Defines the list of self DER resource types. */
#define  SL_OBJ_ID_X_SDEV_DER                     (106)
/**  SL_OBJ_ID_X_SDEV_DER_X - Defines an individual self DER resource type. */
#define  SL_OBJ_ID_X_SDEV_DER_X                   (107)
/**  SL_OBJ_ID_X_SDEV_DER_X_DERA - Defines the self DER Availability resource type. */
#define  SL_OBJ_ID_X_SDEV_DER_X_DERA              (108)
/**  SL_OBJ_ID_X_SDEV_DER_X_DERCAP - Defines the self DER Capabilities resource type. */
#define  SL_OBJ_ID_X_SDEV_DER_X_DERCAP            (109)
/**  SL_OBJ_ID_X_SDEV_DER_X_DERS - Defines the self DER Status resource type. */
#define  SL_OBJ_ID_X_SDEV_DER_X_DERS              (110)
/**  SL_OBJ_ID_X_SDEV_DER_X_DERG - Defines the self DER Settings resource type. */
#define  SL_OBJ_ID_X_SDEV_DER_X_DERG              (111)
/**  SL_OBJ_ID_X_SDEV_FILE - Defines the self file status resource type. */
#define  SL_OBJ_ID_X_SDEV_FILE                    (112)
/**  SL_OBJ_ID_X_SDEV_NS - Defines the list of self net status resource types. */
#define  SL_OBJ_ID_X_SDEV_NS                      (113)
/**  SL_OBJ_ID_X_SDEV_NS_X - Defines an individual self net status resource type. */
#define  SL_OBJ_ID_X_SDEV_NS_X                    (114)
/**  SL_OBJ_ID_X_SDEV_SDSTAT - Defines an individual self device status resource type. */
#define  SL_OBJ_ID_X_SDEV_SDSTAT                  (115)
/** \endcond */

/**  SL_OBJ_ID_X_SDEV_SDI - Defines an individual self device information resource type. */
#define  SL_OBJ_ID_X_SDEV_SDI                     (116)

/** \cond NOTRELEASED */
/**  SL_OBJ_ID_X_SDEV_SLEL - Defines the list of self log event log resource types. */
#define  SL_OBJ_ID_X_SDEV_SLEL                    (117)
/**  SL_OBJ_ID_X_SDEV_SLEL_X - Defines an individual self log event log resource type. */
#define  SL_OBJ_ID_X_SDEV_SLEL_X                  (118)
/**  SL_OBJ_ID_X_SDEV_SLSA - Defines an individual self load shed availability resource type. */
#define  SL_OBJ_ID_X_SDEV_SLSA                    (119)
/**  SL_OBJ_ID_X_SDEV_SPS - Defines an individual self power status resource type. */
#define  SL_OBJ_ID_X_SDEV_SPS                     (120)

/**  SL_OBJ_ID_X_TM - Defines the time resource type. */
#define  SL_OBJ_ID_X_TM                           (121)
/** \endcond */
/**  SL_OBJ_ID_X_TP - Defines the list of tariff profile resource types. */
#define  SL_OBJ_ID_X_TP                           (122)
/**  SL_OBJ_ID_X_TP_X - Defines an individual tariff profile resource types. */
#define  SL_OBJ_ID_X_TP_X                         (123)
/**  SL_OBJ_ID_X_TP_X_RC - Defines the list of rate component resource types. */
#define  SL_OBJ_ID_X_TP_X_RC                      (124)
/**  SL_OBJ_ID_X_TP_X_RC_X - Defines an individual rate component resource type. */
#define  SL_OBJ_ID_X_TP_X_RC_X                    (125)
/**  SL_OBJ_ID_X_TP_X_RC_X_TTI - Defines the list of time tariff interval resource types. */
#define  SL_OBJ_ID_X_TP_X_RC_X_TTI                (126)
/**  SL_OBJ_ID_X_TP_X_RC_X_TTI_X - Defines an individual time tariff interval resource type. */
#define  SL_OBJ_ID_X_TP_X_RC_X_TTI_X              (127)
/**  SL_OBJ_ID_X_TP_X_RC_X_ACTTTI - Defines the list of active time tariff interval resource types. */
#define  SL_OBJ_ID_X_TP_X_RC_X_ACTTTI             (128)
/**  SL_OBJ_ID_X_TP_X_RC_X_ACTTTI_X - Defines an individual active time tariff interval resource type. */
#define  SL_OBJ_ID_X_TP_X_RC_X_ACTTTI_X           (129)
/**  SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI - Defines the list of consumption tariff interval resource types. */
#define  SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI          (130)
/**  SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X - Defines an individual consumption tariff interval resource type. */
#define  SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X        (131)

/**  SL_OBJ_ID_X_RT - Defines the list of reading type resource types. */
#define  SL_OBJ_ID_X_RT                           (132)

/**  SL_OBJ_ID_X_RT_X - Defines an individual reading type resource type. */
#define  SL_OBJ_ID_X_RT_X                         (133)

/** \cond NOTRELEASED */
/* SL_OBJ_ID_X_UPT - Defines the list of usage point resource types. */
#define  SL_OBJ_ID_X_UPT                          (134)
/** \endcond */
/* SL_OBJ_ID_X_UPT_X - Defines an individual usage point resource type. */
#define  SL_OBJ_ID_X_UPT_X                        (135)
/** \cond NOTRELEASED */
/* SL_OBJ_ID_X_UPT_X_MR - Defines the list of meter reading resource types. */
#define  SL_OBJ_ID_X_UPT_X_MR                     (136)
/** \endcond */
/* SL_OBJ_ID_X_UPT_X_MR_X - Defines an individual meter reading resource type. */
#define  SL_OBJ_ID_X_UPT_X_MR_X                   (137)
/* SL_OBJ_ID_X_UPT_X_MR_X_R - Defines an individual reading resource type. */
#define  SL_OBJ_ID_X_UPT_X_MR_X_R                 (138)
/** \cond NOTRELEASED */
/* SL_OBJ_ID_X_UPT_X_MR_X_RS - Defines the list of reading set resource types. */
#define  SL_OBJ_ID_X_UPT_X_MR_X_RS                (139)
/** \endcond */
/* SL_OBJ_ID_X_UPT_X_MR_X_RS_X - Defines an individual reading set resource type. */
#define  SL_OBJ_ID_X_UPT_X_MR_X_RS_X              (140)
/** \cond NOTRELEASED */
/* SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R - Defines the list of reading resource types. */
#define  SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R            (141)
/** \endcond */
/* SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X - Defines an individual reading resource type. */
#define  SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X          (142)
/** \cond NOTRELEASED */
/* SL_OBJ_ID_X_MAX - Not a SEP object, used to define the upper bound of object types */
#define  SL_OBJ_ID_X_MAX                          (143)
/** \endcond */

/** @} */
// end addtogroup SL_OBJ_ID_XXX


/*******************************************************************************/
/**
 * \defgroup SL_OBJ_INSTANCE_ID Object Instance Id Type
 * This section contains definitions used with Object instances. These defines are
 * used with the SL_SERVER_OBJ_XXXXX mail messages.
 */

/** \addtogroup SL_OBJ_INSTANCE_ID
 * @{ */

/** SL_OBJ_INSTANCE_DEF_GRP_ID - Default Function Set Assignment (FSA) Group ID. */
#define SL_OBJ_INSTANCE_DEF_GRP_ID (0)

/** Opaque instanceID type used in sl_server_obj_ref_t struct */
typedef u16_t sl_obj_instance_id_t;

/** @} */
// end addtogroup SL_OBJ_INSTANCE_ID

/*******************************************************************************/
/**
 * \defgroup SL_OBJ_ACL_ID Object ACL Id Type
 * This section contains ACL related definitions used with Object instances. These defines are
 * used with the SL_SERVER_OBJ_XXXXX mail messages.
 */

/** \addtogroup SL_OBJ_ACL_ID
 * @{ */

/** SL_OBJ_ACL_DEF_ACL_ID - Default Access Control List (ACL) ID. */
#define SL_OBJ_ACL_DEF_ACL_ID (0)

/** Opaque ACL ID type used in sl_server_obj_ref_t struct */
typedef u16_t sl_obj_acl_id_t;

/** @} */
// end addtogroup SL_OBJ_ACL_ID

/** @} */
// end addtogroup OBJ_GROUP_TYPES

/******************************************************************************/
/**
 * \defgroup OBJ_GROUP_STRUCTS Object Structures
 * This section contains structures used with the SL_SERVER_OBJ_XXXXX mail messages.
 */
/** \addtogroup OBJ_GROUP_STRUCTS
 * @{ */
/**
 * \struct sl_server_obj_ref_t
 * This structure provides all of the reference information needed for referencing
 * Objects that reside in the SEP Server.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   *  Specifies the Object (SL_OBJ_ID_XXXX resource, list, etc.) being referenced in a message.
   */
  sl_obj_id_t objId;
  /**
   * Specifies all of the instance IDs in the URI path being used to refer to this object.  Instance IDs
   * are ordered in the array from left to right based on their top down parent instance IDs.
   * The first instance ID is always the root group ID.  For SEP resources that have an instance ID, the
   * last element in the array will usually reference the resource instance ID (unless the resource is
   * being created in which case SEP will return the instance ID that was created for the resource).
   */
  sl_obj_instance_id_t instanceIDs[SL_OBJ_MAX_NUM_INSTANCE_ID];
  /**
   *  Specifies the number of elements in the instanceID array that are valid for this reference.
   */
  u8_t  numInstanceIDs;
  /**
   *  Specifies the Access Control ID for the SEP object being referenced.
   */
  sl_obj_acl_id_t aclID;
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
  u32_t transactionId;
}sl_server_obj_ref_t;

/******************************************************************************/
/**
 * \struct sl_server_obj_event_status_ind_t
 * This structure is used to provide event status information to the
 * Customer Server Application. The reference structure is defined
 * based on the particular function set and event.
 *
 * Note that valid event status values are:
 * - \ref SL_XSD_RESP_STATUS_EVENT_STARTED\n This status is sent at the very
 * earliest possible start time based on the randomStart value defined
 * for the event, or at the defined start time if randomization is
 * not allowed or off.
 * - \ref SL_XSD_RESP_STATUS_EVENT_COMPLETED\n This status is sent at the
 * very latest end time of the event based on the randomStart
 * and randomDuration values defined for the event, or at the defined
 * end time based on the defined start and duration times if randomization
 * is not allowed or off.
 * - \ref SL_XSD_RESP_STATUS_EVENT_CANCELED\n This status is sent when the
 * event is canceled via a CANCEL request from the Customer Server Application.
 * - \ref SL_XSD_RESP_STATUS_EVENT_SUPERSEDED\n This status is sent at the
 * time that the SL Server determines that the event has been superseded.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object that was acted upon.
   */
  sl_server_obj_ref_t       ref;
  /**
   * Unique MRID for this event of length SL_XSD_MRID_LEN.
   */
  u8_t                      mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the current status of the event.
   */
  sl_xsd_resp_status_type_t eventStatus;
}sl_server_obj_event_status_ind_t;

/******************************************************************************/
/**
 * \struct sl_server_obj_cnf_t
 * This structure defines information passed in confirmation messages for
 * \ref SL_SERVER_OBJ_CREATE_CNF, \ref SL_SERVER_OBJ_CANCEL_CNF and
 * \ref SL_SERVER_OBJ_DELETE_CNF.
 *
 * The mRID is an optional field and its inclusion will be based on the
 * following rules:\n
 * 1) If the mRID is included in the associated request and the status > 0
 * (indicating a non-error condition), the mRID <b>SHALL</b> be included in the
 * confirmation.\n
 * 2) If the mRID is included in the associated request and the status < 0
 * (indicating an error condition), the mRID <b>MAY</b> be included in the
 * confirmation.\n
 * 3) If the mRID is NOT included in the associated request, it <b>SHALL NOT</b>
 * be included in the confirmation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object that was acted upon.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Indicates the current status of the event.
   */
  sl_cmn_rc_t          status;
  /**
   * Boolean indicating whether the mRID is included in the confirmation or not.
   */
  bool                 mrIdExists;
  /**
   * Unique MRID for this object of length \ref SL_XSD_MRID_LEN.
   */
  u8_t                 mrId[SL_XSD_MRID_LEN];
}sl_server_obj_cnf_t;


/** @} */
// end addtogroup OBJ_GROUP_STRUCTS

/** @} */
// end addtogroup OBJ_GROUP

/** \addtogroup COMMON_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_cmn_server_create_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Reading
 * Type (RT) within the server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_cmn_server_create_rtype_cnf.
 *
 * Note that this is a common interface that is used by multiple function
 * sets which each support reading types, including METER, BILL, and Pricing.
 *
 * The ref field of the sl_cmn_server_create_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * The reading type to be created.
   */
  sl_cmn_rt_t          rtype;
} sl_cmn_server_create_rtype_req;

/******************************************************************************/
/**
 * \struct sl_cmn_server_create_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * Note that this is a common interface that is used by multiple function
 * sets which each support reading types, including METER, BILL, and Pricing.
 *
 * The ref field of the sl_cmn_server_create_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_cmn_server_create_rtype_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_cmn_server_create_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_cmn_server_delete_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Reading
 * Type (RT) within the Server.  Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_cmn_server_delete_rtype_cnf.
 *
 * Note that this is a common interface that is used by multiple function
 * sets which each support reading types, including METER, BILL, and Pricing.
 *
 * The ref field of the sl_cmn_server_delete_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: The \ref sl_cmn_server_delete_rtype_req may only be sent after an
 * \ref sl_cmn_server_create_rtype_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_cmn_server_delete_rtype_req
*/
typedef sl_server_obj_ref_t sl_cmn_server_delete_rtype_req;

/******************************************************************************/
/**
 * \struct sl_cmn_server_delete_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted DRP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * Note that this is a common interface that is used by multiple function
 * sets which each support reading types, including METER, BILL, and Pricing.
 *
 * The ref field of the sl_cmn_server_delete_rtype_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the TT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_cmn_server_delete_rtype_cnf
*/
typedef sl_server_obj_cnf_t sl_cmn_server_delete_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_cmn_server_store_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite an existing
 * Reading Type (RT) within the server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_cmn_server_store_rtype_cnf.
 *
 * Note that this is a common interface that is used by multiple function
 * sets which each support reading types, including METER, BILL, and Pricing.
 *
 * The ref field of the sl_cmn_server_store_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_create_rtype_req sl_cmn_server_store_rtype_req
 *
 */
typedef sl_cmn_server_create_rtype_req sl_cmn_server_store_rtype_req;

/******************************************************************************/
/**
 * \struct sl_cmn_server_store_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the updated RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * Note that this is a common interface that is used by multiple function
 * sets which each support reading types, including METER, BILL, and Pricing.
 *
 * The ref field of the sl_cmn_server_store_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_cmn_server_store_rtype_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_cmn_server_store_rtype_cnf;

/** @} */
// end addtogroup COMMON_GROUP_STRUCTS


/** \cond NOTRELEASED */

// -------------------- BILLING ------------------

// TODO:  Clean-up
#define SL_BILL_MAX_CHARGE_ELE          (5)

typedef u8_t sl_xsd_chargeKind_t;
#define SL_XSD_BILL_CHARGEKIND_CONSUMP  (0)
#define SL_XSD_BILL_CHARGEKIND_REBATE   (1)
#define SL_XSD_BILL_CHARGEKIND_AUX      (2)
#define SL_XSD_BILL_CHARGEKIND_DEMAND   (3)
#define SL_XSD_BILL_CHARGEKIND_TAX      (4)

typedef u16_t qualityFlag_t;
#define SL_XSD_BILL_QUALFLAG_VALID         0x0001
#define SL_XSD_BILL_QUALFLAG_MANUAL        0x0002
#define SL_XSD_BILL_QUALFLAG_EST_REFDAY    0x0004
#define SL_XSD_BILL_QUALFLAG_EST_INTERPOL  0x0008
#define SL_XSD_BILL_QUALFLAG_QUESTIONABLE  0x0010
#define SL_XSD_BILL_QUALFLAG_DERIVED       0x0020
#define SL_XSD_BILL_QUALFLAG_PROJECTED     0x0040

typedef struct {
  char                 description[SL_XSD_STRING20_LEN];
  bool                 kindExists;
  sl_xsd_chargeKind_t  kind;
  i32_t                value;
} sl_billing_charge_t;

typedef u8_t sl_brs_parentType;
#define SL_BILL_BRSPARENT_TAR (1)
#define SL_BILL_BRSPARENT_PRO (2)
#define SL_BILL_BRSPARENT_VER (3)

/******************************************************************************/
/**
 * \struct sl_bill_server_create_bill_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Customer
 * Account Resource (BILL) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_bill_cnf.
 *
 * The ref field of the sl_bill_server_create_bill_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */

typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * ISO 4217 code indicating the currency applicable to the bill amounts in the summary.
   */
  u16_t                 currency;
  /**
   * Customer Account.
   */
  char                  customerAccount[SL_XSD_STRING42_LEN];
  /**
   * Customer Name.
   */
  char                  customerName[SL_XSD_STRING42_LEN];
  /**
   * Price Power of Ten Multiple.
   */
  sl_xsd_ptm_type_t     pricePowerOfTenMult;
  /**
   * Unique MRID for this customer account resource of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Description of the customer account resource (BILL), with max length of
   *  SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_bill_server_create_bill_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_bill_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X (Customer Account Resource or BILL).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created BILL. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_bill_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_bill_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_bill_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_ca_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Customer
 * Account Agreement Resource (CA) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_ca_cnf.
 *
 * The ref field of the sl_bill_server_create_ca_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Specifies all of the instance IDs necessary to reference a Pre-Payment resource.
   * The first element refers to the group ID.
   */
  u16_t                 ppyId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
  /**
   * Specifies all of the instance IDs necessary to reference a Tariff Profile resource.
   * The first element refers to the group ID.
   */
  u16_t                 tpId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
  /**
   * Specifies all of the instance IDs necessary to reference a Usage Point resource.
   * The first element refers to the group ID.
   */
  u16_t                 uptId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
  /**
   * Service Account
   */
  char                  serviceAccount[SL_XSD_STRING42_LEN];
  /**
   * Service Location
   */
  char                  serviceLocation[SL_XSD_STRING42_LEN];
  /**
   * Unique MRID for this customer agreement resource of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Description of this customer agreement resource (CA), string must be
   *  null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_bill_server_create_ca_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_ca_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_CA_X (Customer Account Agreement or CA).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created CA. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_ca_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_ca_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_ca_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Reading
 * Type (RT) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_rtype_cnf.
 *
 * The ref field of the sl_bill_server_create_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_create_rtype_req sl_bill_server_create_rtype_req
 */
typedef sl_cmn_server_create_rtype_req sl_bill_server_create_rtype_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created RT. It uses the common structure
 *  \ref sl_cmn_server_create_rtype_cnf.
 *
 * The ref field of the sl_bill_server_create_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_create_rtype_cnf sl_bill_server_create_rtype_cnf
 *
 */
typedef sl_cmn_server_create_rtype_cnf sl_bill_server_create_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_delete_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Reading
 * Type (RT) within the BILL Server.  Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_bill_server_delete_rtype_cnf.
 *
 * The ref field of the sl_bill_server_delete_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: The \ref sl_bill_server_delete_rtype_cnf may only be sent after an
 * \ref sl_bill_server_create_rtype_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_cmn_server_delete_rtype_req sl_bill_server_delete_rtype_req
*/
typedef sl_cmn_server_delete_rtype_req sl_bill_server_delete_rtype_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_delete_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_delete_rtype_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_delete_rtype_cnf sl_bill_server_delete_rtype_cnf
*/
typedef sl_cmn_server_delete_rtype_cnf sl_bill_server_delete_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_store_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite an existing
 * Reading Type (RT) within the server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_store_rtype_cnf.
 *
 * The ref field of the sl_bill_server_store_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_store_rtype_req sl_bill_server_store_rtype_req
 */
typedef sl_cmn_server_store_rtype_req sl_bill_server_store_rtype_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_store_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the updated RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_store_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_store_rtype_cnf sl_bill_server_store_rtype_cnf
 *
 */
typedef sl_cmn_server_store_rtype_cnf sl_bill_server_store_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_store_ss_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Service
 * Supplier Resource (SS) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_store_ss_cnf.
 *
 * The ref field of the sl_bill_server_store_ss_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_SS\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Email
   */
  char                  email[SL_XSD_STRING32_LEN];
  /**
   * Phone
   */
  char                  phone[SL_XSD_STRING20_LEN];
  /**
   * Provider ID
   */
  u32_t                 providerID;
  /**
   * Web
   */
  char                  web[SL_XSD_STRING42_LEN];
  /**
   * Unique MRID for this service provider resource of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Description of the service provider resource (SS), string must be
   *  null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_bill_server_store_ss_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_store_ss_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_SS (Service Supplier or SS).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created SS. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_store_ss_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_SS\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_store_ss_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_store_ss_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_bp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Billing
 * Period Resource (BP) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_bp_cnf.
 *
 * The ref field of the sl_bill_server_create_bp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_BP_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Existence Flag for billLastPeriod
   */
  bool                  billLastPeriodExists;
  /**
   * The amount of the bill for the previous billing period
   */
  u64_t                 billLastPeriod;
  /**
   * Existence Flag for billToDate
   */
  bool                  billToDateExists;
  /**
   * The amount of the bill for the previous billing period
   */
  u64_t                 billToDate;
  /**
   * The date / time of the last update of this resource.
   */
  sl_xsd_time_type_t    statusTimeStamp;
  /**
   * The date and time of the start of the interval
   */
  sl_xsd_time_type_t    start;
  /**
   * The duration of the interval in seconds.
   */
  u32_t                 duration;
} sl_bill_server_create_bp_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_bp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_CA_X_BP_X (Billing Period or BP).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created BP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_bp_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_BP_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the BP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_bp_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_bp_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_ver_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Historical
 * Reading Resource (VER) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_ver_cnf.
 *
 * The ref field of the sl_bill_server_create_ver_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Specifies all of the instance IDs necessary to reference a reading type resource.  The first element refers
   * to the group ID.
   */
  u16_t                 rtId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
  /**
   * Unique MRID for this historical reading resource of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Description of this historical reading resource (VER), tring must be
   *  null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_bill_server_create_ver_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_ver_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X (Historical Reading
 * Resource or VER).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created VER. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_ver_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the VER\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_ver_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_ver_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_tar_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Target
 * Reading Resource (TAR) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_tar_cnf.
 *
 * The ref field of the sl_bill_server_create_tar_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Specifies all of the instance IDs necessary to reference a reading type resource.
   * The first element refers to the group ID.
   */
  u16_t                 rtId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];

  /**
   * Unique MRID for this target reading resource of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Description of this target reading resource (TAR), string must be
   *  null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_bill_server_create_tar_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_tar_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X (Target Reading
 * Resource or TAR).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created TAR. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_tar_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the TAR\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_tar_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_tar_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_pro_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Projection
 * Reading Resource (PRO) within the BILL Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_pro_cnf.
 *
 * The ref field of the sl_bill_server_create_tar_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t   ref;
  /**
   * Specifies all of the instance IDs necessary to reference a reading type resource.
   * The first element refers to the group ID.
   */
  u16_t                 rtId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];

  /**
   * Unique MRID for this projection reading resource of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Description of this projection reading resource (PRO), string must be
   *  null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_bill_server_create_pro_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_pro_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X (Projected Reading
 * Resource or PRO).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created PRO. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_pro_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the PRO\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_pro_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_pro_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_brs_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new
 * Reading Set Resource (BRS) within the BILL Server associated with either an
 * Historical Reading (VER), Target Reading (TAR) or Projection Reading (PRO).
 * Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_brs_cnf.
 *
 * The ref field of the sl_bill_server_create_brs_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the TAR/VER/PRO Reading Resource\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Time Period duration (interval in seconds)
   */
  u32_t                 duration;
  /**
   * Date and time of the start of the interval
   */
  sl_xsd_time_type_t    start;
  /**
   * Unique MRID for this billing reading set resource of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Description of this billing reading set resource (BRS), string must be
   *  null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_bill_server_create_brs_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_brs_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X,
 * \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X, or \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X
 * (Reading Set Resource  or BRS attached to either a TAR, VER, or PRO).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created PRO. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_brs_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the TAR/VER/PRO Reading Resource\n
 * ref.instanceIDs[4] = The unique ID for the BRS\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_brs_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_brs_cnf;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_br_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Billing
 * Reading Resource (BR) within the BILL Server associated with either an
 * Historical Reading (VER), Target Reading (TAR) or Projection Reading (PRO).
 * Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_bill_server_create_br_cnf.
 *
 * The ref field of the sl_bill_server_create_br_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X_BR_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X_BR_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X_BR_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the TAR/VER/PRO Reading Resource\n
 * ref.instanceIDs[4] = The unique ID for the BRS\n
 *
 * Dependencies: None.
 *
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t   ref;
  /**
   * Consumption Block Exists
   */
  bool                  consumptionBlockExists;
  /**
   * Consumption Block Type
   */
  sl_xsd_cons_block_type_t consumptionBlock;
  /**
   * Quality Flag Exists
   */
  bool                  qualityFlagsExists;
  /**
   * Quality Flag (bitfields)
   */
  qualityFlag_t         qualityFlags;
  /**
   * Date and time of the start of the interval
   */
  sl_xsd_time_type_t    start;
  /**
   * Duration of the interval in seconds.
   */
  u32_t                 duration;
  /**
   * touTier Duration of the interval (in seconds)
   */
  bool                  touTierExists;
  /**
   * touTier Duration of the interval (in seconds)
   */
  sl_xsd_tou_type_t     touTier;
  /**
   * value (in units specified by ReadingType)
   */
  u64_t                 value;
  /**
   * numCharge, number of charge elements specified in this request message.
   */
  u16_t                 numCharge;
  /**
   * Charge, billing charge specific information
   */
  sl_billing_charge_t   charge[SL_BILL_MAX_CHARGE_ELE];
} sl_bill_server_create_br_req;

/******************************************************************************/
/**
 * \struct sl_bill_server_create_br_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X_BR_X,
 * \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X_BR_X, or \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X_BR_X
 * (Reading Resource or BR attached to either a TAR, VER, or PRO reading set).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created BR. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_bill_server_create_brs_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_BILL_X_CA_X_TAR_X_BRS_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_VER_X_BRS_X or\n
 *                      \ref SL_OBJ_ID_X_BILL_X_CA_X_PRO_X_BRS_X\n
 * ref.numInstanceIDs = 6\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the BILL\n
 * ref.instanceIDs[2] = The unique ID for the CA\n
 * ref.instanceIDs[3] = The unique ID for the TAR/VER/PRO Reading Resource\n
 * ref.instanceIDs[4] = The unique ID for the BRS\n
 * ref.instanceIDs[5] = The unique ID for the BR\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_bill_server_create_br_cnf
 */
typedef sl_server_obj_cnf_t sl_bill_server_create_br_cnf;


// -------------------- CONFIG -------------------

#define SL_DEVNAME_LEN      32
#define SL_LOCALE_LEN       42

typedef struct {
  char          userDeviceName[SL_DEVNAME_LEN];
  sl_xsd_time_type_t  batteryInstallTime;
  u32_t         lowChargeThreshold;
  bool          timeConfigurationExists;
  u32_t         dstEndRule;
  i32_t         dstOffset;
  u32_t         dstStartRule;
  i32_t         tzOffset;
  char          currentLocale[SL_LOCALE_LEN];
} sl_configuration_t;


/**
 * \defgroup SDEV_GROUP_STRUCTS SDEV Structures
 * This section contains structures used by the SDEV function set.
 */
/** \addtogroup SDEV_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_sdev_services_t
 * This structure contains a boolean for each function set or service that is supported
 * by a particular SDEV instance.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether SDEV Config FS is supported for this device.
   */
  bool                    config;
  /**
   * Hash of the Config link HREF
   */
  u32_t                   configHash;
  /**
   * Boolean indicating whether SDEV DER FS is supported for this device.
   */
  bool                    der;
  /**
   * Hash of the DER list link HREF
   */
  u32_t                   derHash;
  /**
   * Boolean indicating whether SDEV Device Info FS is supported for this device.
   */
  bool                    devInfo;
  /**
   * Hash of the Device Info link HREF
   */
  u32_t                   devInfoHash;
  /**
   * Boolean indicating whether SDEV Device Status FS is supported for this device.
   */
  bool                    deviceStatus;
  /**
   * Hash of the Device Status link HREF
   */
  u32_t                   deviceStatusHash;
  /**
   * Boolean indicating whether SDEV File Status FS is supported for this device.
   */
  bool                    fileStatus;
  /**
   * Hash of the File Status link HREF
   */
  u32_t                   fileStatusHash;
  /**
   * Boolean indicating whether SDEV LSA FS is supported for this device.
   */
  bool                    loadShedAvail;
  /**
   * Hash of the LoadShedAvailability list link HREF
   */
  u32_t                   loadShedAvailHash;
  /**
   * Boolean indicating whether SDEV LEL FS is supported for this device.
   */
  bool                    logEvent;
  /**
   * Hash of the Log Event list link HREF
   */
  u32_t                   logEventHash;
  /**
   * Boolean indicating whether SDEV Power Status FS is supported for this device.
   */
  bool                    powerStatus;
  /**
   * Hash of the Power Status link HREF
   */
  u32_t                   powerStatusHash;
} sl_sdev_services_t;

/** @} */
// end addtogroup SDEV_GROUP_STRUCTS


/******************************************************************************/
/**
 * \struct sl_sdev_server_store_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new self-device
 * (SDEV) resource within the Config Server.
 * Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_sdev_server_store_config_cnf.
 *
 * The ref field of the sl_sdev_server_store_config_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 */

typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;

  /**
   * This field is for use in devices that can adjust energy usage (e.g., demand response, 
   * distributed energy resources).  For devices that do not respond to EndDeviceControls 
   * or DERControls (for instance, an ESI), this field should not have any bits set.
   */
  sl_xsd_dev_cat_bitmap_t deviceCategory;
  /**
   * Boolean indicating whether the deviceCategory field is included for this SDEV or not.
   */
  bool                    deviceCategoryExists;

  /**
   * This structure indicates which services should be available for this SDEV instance.
   * Note that even if a boolean within the structure is set to TRUE, that service
   * will only be available if the server supports it.
   */
  sl_sdev_services_t      services;

} sl_sdev_server_store_req;

/******************************************************************************/
/**
 * \struct sl_sdev_server_store_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_SDEV (self device resource).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created SDEV. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_sdev_server_store_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_sdev_server_store_cnf
 */
typedef sl_server_obj_cnf_t sl_sdev_server_store_cnf;

/******************************************************************************/
/**
 * \struct sl_sdev_client_server_sdev_ind
 * This indication is used to indicate to the Customer Application that
 * an SDEV server was found.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * This field is for use in devices that can adjust energy usage (e.g., demand response,
   * distributed energy resources).  For devices that do not respond to EndDeviceControls
   * or DERControls (for instance, an ESI), this field should not have any bits set.
   */
  sl_xsd_dev_cat_bitmap_t deviceCategory;
  /**
   * Boolean indicating whether the deviceCategory field is included for this SDEV or not.
   */
  bool                    deviceCategoryExists;
  /**
   * This structure indicates which services are available as part of this SDEV instance.
   */
  sl_sdev_services_t      services;
  /**
   * SFDI of this SDEV instance.
   */
  u64_t                   sfdi;

} sl_sdev_client_server_sdev_ind;

/******************************************************************************/
/**
 * \struct sl_scfg_server_store_config_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new self-device
 * (SDEV) self-config (SCFG)resource within the Config Server.
 * Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_scfg_server_store_config_cnf.
 *
 * The ref field of the sl_scfg_server_store_config_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_SCFG\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 */

typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Configuration information
   */
  sl_configuration_t     config;
} sl_scfg_server_store_config_req;

/******************************************************************************/
/**
 * \struct sl_scfg_server_store_config_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_SDEV_SCFG (self device self config resource).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created SCFG. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_scfg_server_store_config_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_SCFG\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_scfg_server_store_config_cnf
 */
typedef sl_server_obj_cnf_t sl_scfg_server_store_config_cnf;

typedef sl_configuration_t sl_ecfg_client_put_config_req;

typedef struct {
  i8_t          status;
} sl_ecfg_client_put_config_cnf;
/** \endcond */

// -------------------- DCAP ---------------------
/**
 * \defgroup DCAP_GROUP DCAP Definitions and Structures
 * \brief This section contains definitions and structures used by the DCAP function set.
 */
/** \addtogroup DCAP_GROUP
 * @{ */

/**
 * \defgroup DCAP_GROUP_STRUCTS DCAP Structures
 * This section contains structures used by the DCAP function set.
 */
/** \addtogroup DCAP_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_dcap_client_services_t
 *
 * This structure captures the DCAP service availability information. The
 * boolean fields indicate if the associated service is available or not in
 * the Server.
 *
 * This structure is a member of the Get DCAP Confirmation sent from the
 * Services layer to the Application. The client application can process/use the
 * information about the DCAP resource availability as it deems fit.
*/
typedef struct
{
  /**
   * Boolean indicating whether the Billing function set is supported for this device.
   */
   bool bill;
  /**
   * Hash of the Billing HREF
   */
  u32_t billHash;
  /**
   * Boolean indicating whether the DRLC function set is supported for this device.
   */
   bool drlc;
  /**
   * Hash of the DRLC HREF
   */
  u32_t drlcHash;
  /**
   * Boolean indicating whether the DER function set is supported for this device.
   */
   bool der;
  /**
   * Hash of the DER HREF
   */
  u32_t derHash;
  /**
   * Boolean indicating whether the File function set is supported for this device.
   */
   bool file;
  /**
   * Hash of the File HREF
   */
  u32_t fileHash;
  /**
   * Boolean indicating whether the Messaging function set is supported for this device.
   */
   bool msg;
  /**
   * Hash of the Messaging HREF
   */
  u32_t msgHash;
  /**
   * Boolean indicating whether the PPY (Pre-Payment) function set is supported for this device.
   */
   bool ppy;
  /**
   * Hash of the PrePayment HREF
   */
  u32_t ppyHash;
  /**
   * Boolean indicating whether the Response function set is supported for this device.
   */
   bool resp;
  /**
   * Hash of the Response HREF
   */
  u32_t respHash;
  /**
   * Boolean indicating whether the Price function set is supported for this device.
   */
   bool price;
  /**
   * Hash of the Price HREF
   */
  u32_t priceHash;
  /**
   * Boolean indicating whether the Time function set is supported for this device.
   */
   bool time;
  /**
   * Hash of the Time HREF
   */
  u32_t timeHash;
  /**
   * Boolean indicating whether the Meter function set is supported for this device.
   */
   bool meter;
  /**
   * Hash of the Metering HREF
   */
  u32_t meterHash;
  /**
   * Boolean indicating whether the EDEV (End Device) function set is supported for this device.
   */
   bool edev;
  /**
   * Hash of the EndDevice HREF
   */
  u32_t edevHash;
  /**
   * Boolean indicating whether the MUP (Mirror Usage Point) function set is supported for this device.
   */
   bool mup;
  /**
   * Hash of the Mirror Usage Point HREF
   */
  u32_t mupHash;
  /**
   * Boolean indicating whether the SDEV (Self Device) function set is supported for this device.
   */
   bool sdev;
  /**
   * Hash of the Self-Device HREF
   */
  u32_t sdevHash;
} sl_dcap_client_services_t;

/** @} */
// end addtogroup DCAP_GROUP_STRUCTS

/**
 * \defgroup DCAP_GROUP_MAIL_STRUCTS DCAP Mail Structures
 * This section contains mail structures used by the DCAP function set.
 */
/** \addtogroup DCAP_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_dcap_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the DCAP Client to indicate that a new DCAP server has been found. Note
 * that multiple indications may be sent if there are multiple servers.
 *
 * The client application may use this indication as a trigger to start
 * requesting DCAP information from the DCAP client. The included server/source
 * information is used to request a DCAP via the \ref sl_dcap_client_get_dcap_req.
 * If DCAP information is requested before this indication is sent, the DCAP
 * client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_dcap_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_dcap_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_dcap_client_get_dcap_req
 * This structure contains information sent to request a list of dcap
 * resources available. The \ref SL_DCAP_CLIENT_GET_DCAP_CNF message shall be
 * sent to the client app in response to this request.
 *
 * Dependencies: The \ref SL_DCAP_CLIENT_SERVER_IND must be received by the client
 * app indicating the server source information available.
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                               transactionId;
  /**
   * Server and source information for the dcap of interest. The set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
} sl_dcap_client_get_dcap_req;

/******************************************************************************/
/**
 * \struct sl_dcap_client_get_dcap_cnf
 *
 * This indication is sent to the Customer Client application from the DCAP
 * client to indicate DCAP resource availability. This is sent in response
 * to the corresponding \ref SL_DCAP_CLIENT_GET_DCAP_REQ.
 *
 * The status field will indicate the SUCCESS or FAILURE or other status
 * of this operation.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                        transactionId;
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                   status;
  /**
   * Identity of the Server for which this DCAP resources are present.
   */
  sl_cmn_client_server_handle_t serverHandle;
  /**
   * Structure indicating which services are available from DCAP.
   */
  sl_dcap_client_services_t     services;
  /**
  * The default polling rate for this function set (this resource and all
  * resources below), in seconds. If not specified, a default of 900 seconds
  * (15 minutes) is used. It is RECOMMENDED a client poll the resources of
  * this function set every pollRate seconds.
  */
  u32_t                  pollRate;
  /**
  * Boolean indicating if the optional pollRate field is valid.
  */
  bool                   pollRateExists;
} sl_dcap_client_get_dcap_cnf;

/******************************************************************************/
/**
 * \struct sl_dcap_client_dcap_ind
 *
 * This indication is sent to the Customer Client application from the DCAP
 * client to indicate DCAP resource availability. 
 *
 * The status field will indicate the SUCCESS or FAILURE or other status
 * of this operation.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                   status;
  /**
   * Structure indicating which services are available from DCAP.
   */
  sl_dcap_client_services_t     services;
  /**
  * The default polling rate for this function set (this resource and all
  * resources below), in seconds. If not specified, a default of 900 seconds
  * (15 minutes) is used. It is RECOMMENDED a client poll the resources of
  * this function set every pollRate seconds.
  */
  u32_t                  pollRate;
  /**
  * Boolean indicating if the optional pollRate field is valid.
  */
  bool                   pollRateExists;
} sl_dcap_client_dcap_ind;

/** @} */
// end addtogroup DCAP_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup DCAP_GROUP

// -------------------- EDER/SDER Common ---------------------

/**
 * \defgroup EDER_SDER_GROUP EDER/SDER Definitions and Structures
 * \brief This section contains common definitions and structures used by the
 *        EDER(End Device DER) and SDER(Self Device DER) function sets.\n
 *        <b>NOTE: The EDER and SDER function sets are not released.  Documentation
 *        on data belonging to these function sets is provided only as reference
 *        for the DER function set.</b>
 */
/** \addtogroup EDER_SDER_GROUP
 * @{ */

/**
 * \defgroup EDER_SDER_GROUP_STRUCTS EDER/SDER Common Structures
 * This section contains structures used by the EDER (End Device DER) and
 * SDER (Self Device DER) function sets.
 */
/** \addtogroup EDER_SDER_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_der_settings_t
 * This structure contains the client DER settings.
 */
typedef struct {
  /**
   * Indicates whether the \ref setModesEnabled exists.
   */
  bool                  setModesEnabledExists;
  /**
   * Bitmap indicating the DER Controls enabled on the device. See DERControlType
   * for values. If a control is supported (see DERCapability::modesSupported),
   * but not enabled, the control will not be executed if encountered.
   */
  u32_t                 setModesEnabled;

  /**
   * Indicates whether the \ref setESDelay exists.
   */
  bool                  setESDelayExists;
  /**
   * Enter service delay, in hundredths of a second.
   */
  u32_t                 setESDelay;

  /**
   * Indicates whether the \ref setESHighFreq exists.
   */
  bool                  setESHighFreqExists;
  /**
   * Enter service frequency high. Specified in hundredths of Hz.
   */
  u16_t                 setESHighFreq;

  /**
   * Indicates whether the \ref setESHighVolt exists.
   */
  bool                  setESHighVoltExists;
  /**
   * Enter service voltage high. Specified as an effective percent voltage,
   * defined as (100% * (locally measured voltage - setVRefOfs) / setVRef),
   * in hundredths of a percent.
   */
  u16_t                 setESHighVolt;

  /**
   * Indicates whether the \ref setESLowFreq exists.
   */
  bool                  setESLowFreqExists;
  /**
   * Enter service frequency low. Specified in hundredths of Hz.
   */
  u16_t                 setESLowFreq;

  /**
   * Indicates whether the \ref setESLowVolt exists.
   */
  bool                  setESLowVoltExists;
  /**
   * Enter service voltage low. Specified as an effective percent voltage,
   * defined as (100% * (locally measured voltage - setVRefOfs) / setVRef),
   * in hundredths of a percent.
   */
  u16_t                 setESLowVolt;

  /**
   * Indicates whether the \ref setESRampTms exists.
   */
  bool                  setESRampTmsExists;
  /**
   * Enter service ramp time, in hundredths of a second.
   */
  u32_t                 setESRampTms;

  /**
   * Indicates whether the \ref setESRandomDelay exists.
   */
  bool                  setESRandomDelayExists;
  /**
   * Enter service randomized delay, in hundredths of a second.
   */
  u32_t                 setESRandomDelay;

  /**
   * Specifies the set default rate of change (ramp rate) of active power output
   * defined in \ref setMaxWValue / second.  The resolution is in hundredths of a
   * percent/second and may be in the range 1 - 20000. This value is interpreted
   * as a percentage change in output capability limit per second when used as
   * a default ramp rate.
   */
  u16_t                 setGradWValue;

  /**
   * Indicates whether the \ref setMaxA exists.
   */
  bool                  setMaxAExists;
  /**
   * AC current maximum value. Maximum AC current in RMS Amperes.
   */
  u16_t                 setMaxAValue;
  /**
   * Specifies the exponent of \ref setMaxAValue.
   */
  sl_xsd_ptm_type_t     setMaxAMultiplier;

  /**
   * Indicates whether the \ref setMaxAh exists.
   */
  bool                  setMaxAhExists;
  /**
   * Value of maximum usable energy storage capacity of the DER, in AmpHours.
   * Note: this may be different from physical capability.
   */
  u16_t                 setMaxAhValue;
  /**
   * Specifies the exponent of \ref setMaxAhValue.
   */
  sl_xsd_ptm_type_t     setMaxAhMultiplier;

  /**
   * Indicates whether the \ref setMaxChargeRateVA exists.
   */
  bool                  setMaxChargeRateVAExists;
  /**
   * Apparent power charge maximum value. Maximum apparent power the DER can absorb
   * from the grid in Volt-Amperes. May differ from the apparent power maximum
   * (setMaxVA)
   */
  u16_t                 setMaxChargeRateVAValue;
  /**
   * Specifies the exponent of \ref setMaxChargeRateVA.
   */
  sl_xsd_ptm_type_t     setMaxChargeRateVAMultiplier;

  /**
   * Indicates whether the \ref setMaxChargeRateW exists.
   */
  bool                  setMaxChargeRateWExists;
  /**
   * Value of maximum rate of energy transfer received by the storage device,
   * in Watts. Defaults to rtgMaxChargeRateW.
   */
  u16_t                 setMaxChargeRateWValue;
  /**
   * Specifies the exponent of \ref setMaxChargeRateW.
   */
  sl_xsd_ptm_type_t     setMaxChargeRateWMultiplier;

  /**
   * Indicates whether the \ref setMaxDischargeRateVA exists.
   */
  bool                  setMaxDischargeRateVAExists;
  /**
   * Apparent power discharge maximum value. Maximum apparent power the DER can deliver
   * to the grid in Volt-Amperes. May differ from the apparent power maximum (setMaxVA).
   */
  u16_t                 setMaxDischargeRateVAValue;
  /**
   * Specifies the exponent of \ref setMaxDischargeRateVA.
   */
  sl_xsd_ptm_type_t     setMaxDischargeRateVAMultiplier;

  /**
   * Indicates whether the \ref setMaxDischargeRateW exists.
   */
  bool                  setMaxDischargeRateWExists;
  /**
   * Value of maximum rate of energy transfer delivered by the storage device,
   * in Watts. Defaults to rtgMaxDischargeRateW.
   */
  u16_t                 setMaxDischargeRateWValue;
  /**
   * Specifies the exponent of \ref setMaxDischargeRateW.
   */
  sl_xsd_ptm_type_t     setMaxDischargeRateWMultiplier;

  /**
   * Indicates whether the \ref setMaxVMultiplier and \ref setMaxVValue
   * fields are present in this structure.
   */
  bool                  setMaxVExists;
  /**
   * AC voltage maximum setting.
   */
  u16_t                 setMaxVValue;
  /**
   * Specifies the exponent of \ref setMaxVValue.
   */
  sl_xsd_ptm_type_t     setMaxVMultiplier;

  /**
   * Indicates whether the \ref setMaxVAMultiplier and \ref setMaxVAValue
   * fields are present in this structure.
   */
  bool                  setMaxVAExists;
  /**
   * Specifies the set limit for the maximum apparent power capability of the
   * DER (in VA). If this value does not exist, the default value is sl_dercap_t::rtgVAValue.
   */
  u16_t                 setMaxVAValue;
  /**
   * Specifies the exponent of \ref setMaxVAValue.
   */
  sl_xsd_ptm_type_t     setMaxVAMultiplier;

  /**
   * Indicates whether the \ref setMaxVarMultiplier and \ref setMaxVarValue
   * fields are present in this structure.
   */
  bool                  setMaxVarExists;
  /**
   * Specifies the set limit for the maximum reactive power delivered by the
   * DER (in var). setMaxVarValue must be a positive value <= sl_dercap_t::rtgVAValue.
   */
  i16_t                 setMaxVarValue;
  /**
   * Specifies the exponent of \ref setMaxVarValue.
   */
  sl_xsd_ptm_type_t     setMaxVarMultiplier;

  /**
   * Indicates whether the \ref setMaxVarNegativeMultiplier and
   * \ref setMaxVarNegativeValue fields are present in this structure.
   */
  bool                  setMaxVarNegativeExists;
  /**
   * Specifies the set limit for the maximum reactive power received by the
   * DER (in var). If this value exists, it must be a negative value >= sl_dercap_t::rtgVarNegValue.
   * If this value does not exist, the default value is negative \ref setMaxVarValue.
   */
  i16_t                 setMaxVarNegativeValue;
  /**
   * Specifies the exponent of \ref setMaxVarNegativeValue.
   */
  sl_xsd_ptm_type_t     setMaxVarNegativeMultiplier;

  /**
   * Specifies the set limit for the maximum active power capability of the
   * DER (in W). If this value does not exist, the default value is
   * sl_dercap_t::rtgWValue.
   */
  i16_t                 setMaxWValue;
  /**
   * Specifies the exponent of \ref setMaxWValue.
   */
  sl_xsd_ptm_type_t     setMaxWMultiplier;

  /**
   * Indicates whether the \ref setMaxWh exists.
   */
  bool                  setMaxWhExists;
  /**
   * Value of maximum energy storage capacity of the DER, in WattHours. Note:
   * this may be different from physical capability.
   */
  u16_t                 setMaxWhValue;
  /**
   * Specifies the exponent of \ref setMaxWh.
   */
  sl_xsd_ptm_type_t     setMaxWhMultiplier;

  /**
   * Indicates whether the \ref setMinPFOverExcitedMultiplier and 
   * \ref setMinPFOverExcitedDisplacement fields are present in this structure.
   */
  bool                  setMinPFOverExcitedExists;
  /**
   * Set minimum Power Factor displacement limit of the DER when injecting reactive 
   * power (over-excited); SHALL be a positive value between 0.0 (typically > 0.7) 
   * and 1.0.  SHALL be >= rtgMinPFOverExcited (default).
   */
  u16_t                 setMinPFOverExcitedDisplacement;
  /**
   * Specifies the exponent of \ref setMinPFOverExcitedDisplacement.
   */
  sl_xsd_ptm_type_t     setMinPFOverExcitedMultiplier;

  /**
   * Indicates whether the \ref setMinPFUnderExcitedMultiplier and 
   * \ref setMinPFUnderExcitedDisplacement fields are present in this structure.
   */
  bool                  setMinPFUnderExcitedExists;
  /**
   * Set minimum Power Factor displacement limit of the DER when absorbing reactive 
   * power (under-excited); SHALL be a positive value between 0.0 (typically > 0.7) 
   * and 0.9999.  If present, SHALL be >= rtgMinPFUnderExcited (default).  
   * If absent, defaults to setMinPFOverExcited.
   */
  u16_t                 setMinPFUnderExcitedDisplacement;
  /**
   * Specifies the exponent of \ref setMinPFUnderExcitedDisplacement.
   */
  sl_xsd_ptm_type_t     setMinPFUnderExcitedMultiplier;

  /**
   * Indicates whether the \ref setMinVMultiplier and \ref setMinVValue
   * fields are present in this structure.
   */
  bool                  setMinVExists;
  /**
   * AC voltage minimum setting.
   */
  u16_t                 setMinVValue;
  /**
   * Specifies the exponent of \ref setMinVValue.
   */
  sl_xsd_ptm_type_t     setMinVMultiplier;

  /**
   * Indicates whether the \ref setSoftGradW exists.
   */
  bool                  setSoftGradWExists;
  /**
   * Set soft-start rate of change (soft-start ramp rate) of active power output due
   * to command or internal action, defined in %setWMax / second.  Resolution is in
   * hundredths of a percent/second. A value of 0 means there is no limit. Interpreted
   * as a percentage change in output capability limit per second when used as a ramp rate.
   */
  u16_t                 setSoftGradW;

  /**
   * Indicates whether the \ref setVNomMultiplier and \ref setVNomValue
   * fields are present in this structure.
   */
  bool                  setVNomExists;
  /**
   * AC voltage nominal setting.
   */
  u16_t                 setVNomValue;
  /**
   * Specifies the exponent of \ref setVNomValue.
   */
  sl_xsd_ptm_type_t     setVNomMultiplier;

  /**
   * Indicates whether the \ref setVRefMultiplier and \ref setVRefValue
   * fields are present in this structure.
   */
  bool                  setVRefExists;
  /**
   * Specifies the set nominal AC voltage (RMS) at the utility's point of common
   * coupling.
   */
  u16_t                 setVRefValue;
  /**
   * Specifies the exponent of \ref setVRefValue.
   */
  sl_xsd_ptm_type_t     setVRefMultiplier;

  /**
   * Indicates whether the \ref setVRefOfsMultiplier and \ref setVRefOfsValue
   * fields are present in this structure.
   */
  bool                  setVRefOfsExists;
  /**
   * Specifies the set nominal AC voltage (RMS) offset between the DER's
   * electrical connection point and the utility's point of common coupling.
   */
  u16_t                 setVRefOfsValue;
  /**
   * Specifies the exponent of \ref setVRefOfsValue.
   */
  sl_xsd_ptm_type_t     setVRefOfsMultiplier;

  /**
   * Specifies the time at which the DER information was last updated. 
   */
   sl_xsd_time_type_t   updatedTime;

} sl_der_settings_t;

/******************************************************************************/
/**
 * \struct sl_dera_t
 * This structure contains the current client DER availability status.
 */
typedef struct {
  /**
   * Indicates whether the \ref availabilityDuration field is present in this
   * structure.
   */
  bool                  availabilityDurationExists;
  /**
   * Indicates whether the \ref reservePercent field is present in this
   * structure.
   */
  bool                  reservePercentExists;
  /**
   * Indicates whether the \ref statVarAvailMultiplier and \ref statVarAvailValue
   * fields are present in this structure.
   */
  bool                  statVarAvailExists;
  /**
   * Indicates whether the \ref statWAvailMultiplier and \ref statWAvailValue
   * fields are present in this structure.
   */
  bool                  statWAvailExists;
  /**
   * Specifies the exponent of \ref statWAvailValue.
   */
  sl_xsd_ptm_type_t     statWAvailMultiplier;
  /**
   * Specifies the percent of continuous delivered active power
   * (sl_der_settings_t::setMaxWValue) that is estimated to be available in reserve.
   */
  u16_t                 reservePercent;
  /**
   * Specifies the exponent of \ref statVarAvailValue.
   */
  sl_xsd_ptm_type_t     statVarAvailMultiplier;
  /**
   * Specifies the estimated reserve active power, in watts.
   */
  i16_t                 statWAvailValue;
  /**
   * Specifies the estimated reserve reactive power, in var. This value
   * represents the lesser of received or delivered reactive power.
   */
  i16_t                 statVarAvailValue;
  /**
   * Specifies the number of seconds the DER will be able to deliver active power
   * at the \ref reservePercent level.
   */
  u32_t                 availabilityDuration;
  /**
   * Specifies the number of seconds the DER will be able to receive active power
   * at the \ref reserveChargePercent level.
   */
  u32_t                 maxChargeDuration;
  /**
   * Indicates whether the \ref maxChargeDuration field is present in this
   * structure.
   */
  bool                  maxChargeDurationExists;
  /**
   * Specifies the date and time when the DER availability was last updated.
   */
  sl_xsd_time_type_t    readingTime;
  /**
   * Specifies the percent of continuous received active power
   * (sl_der_settings_t::setMaxChargeRateValue) that is estimated to be available
   * in reserve.
   */
  u16_t                 reserveChargePercent;
  /**
   * Indicates whether the \ref reserveChargePercent field is present in this
   * structure.
   */
  bool                  reserveChargePercentExists;
} sl_dera_t;

/******************************************************************************/
/**
 * \struct sl_dercap_t
 * This structure contains the client DER type and nameplate ratings.
 */
typedef struct {
  /**
   * Specifies a bitmap indicating the DER Controls implemented by the device.
   */
  sl_xsd_der_cont_t      modesSupported;

  /**
   * Indicates whether the \ref rtgAbnormalCategory is present in this structure.
   */
  bool                   rtgAbnormalCategoryExists;
  /**
   * Abnormal operating performance category as defined by IEEE 1547-2017. One of:
   * 0 - not specified
   * 1 - Category I
   * 2 - Category II
   * 3 - Category III
   * All other values reserved.
   */
  u8_t                   rtgAbnormalCategory;

  /**
   * Indicates whether the \ref rtgMaxAValue and \ref rtgMaxAMultiplier 
   * fields are present in this structure.
   */
  bool                   rtgMaxAExists;
  /**
   * Specifies the maximum continuous AC current capability of the DER, in
   * Amperes (RMS).
   */
  u16_t                  rtgMaxAValue;
  /**
   * Specifies the exponent of \ref rtgMaxAValue.
   */
  sl_xsd_ptm_type_t      rtgMaxAMultiplier;

  /**
   * Indicates whether the \ref rtgMaxAhValue and \ref rtgMaxAhMultiplier 
   * fields are present in this structure.
   */
  bool                   rtgMaxAhExists;
  /**
   * Specifies the usable energy storage capacity of the DER, in AmpHours.
   */
  u16_t                  rtgMaxAhValue;
  /**
   * Specifies the exponent of \ref rtgMaxAhValue.
   */
  sl_xsd_ptm_type_t      rtgMaxAhMultiplier;

  /**
   * Indicates whether the \ref rtgMaxChargeRateVAValue and
   * \ref rtgMaxChargeRateVAMultiplier fields are present in this structure.
   */
  bool                   rtgMaxChargeRateVAExists;
  /**
   * Maximum apparent power charge rating in Volt-Amperes. May differ from the
   * maximum apparent power rating.
   */
  i16_t                  rtgMaxChargeRateVAValue;
  /**
   * Specifies the exponent of \ref rtgMaxChargeRateVA.
   */
  sl_xsd_ptm_type_t      rtgMaxChargeRateVAMultiplier;

  /**
   * Indicates whether the \ref rtgMaxChargeRateWValue and
   * \ref rtgMaxChargeRateWMultiplier fields are present in this structure.
   */
  bool                   rtgMaxChargeRateWExists;
  /**
   * Maximum rate of energy transfer received by the storage DER, in Watts.
   */
  i16_t                  rtgMaxChargeRateWValue;
  /**
   * Specifies the exponent of \ref rtgMaxChargeRateW.
   */
  sl_xsd_ptm_type_t      rtgMaxChargeRateWMultiplier;

  /**
   * Indicates whether the \ref rtgMaxDischargeRateVAValue  and
   * \ref rtgMaxDischargeRateVAMultiplier fields are present in this structure.
   */
  bool                   rtgMaxDischargeRateVAExists;
  /**
   * Maximum apparent power discharge rating in Volt-Amperes. May differ from
   * the maximum apparent power rating.
   */
  i16_t                  rtgMaxDischargeRateVAValue;
  /**
   * Specifies the exponent of \ref rtgMaxDischargeRateVAValue.
   */
  sl_xsd_ptm_type_t      rtgMaxDischargeRateVAMultiplier;

  /**
   * Indicates whether the \ref rtgMaxDischargeRateWValue and
   * \ref rtgMaxDischargeRateWMultiplier fields are present in this structure.
   */
  bool                   rtgMaxDischargeRateWExists;
  /**
   * Maximum rate of energy transfer delivered by the storage DER, in Watts.
   * Required for combined generation/storage DERs (e.g. DERType == 82).
   */
  i16_t                  rtgMaxDischargeRateWValue;
  /**
   * Specifies the exponent of \ref rtgMaxDischargeRateWValue.
   */
  sl_xsd_ptm_type_t      rtgMaxDischargeRateWMultiplier;

  /**
   * Indicates whether the \ref rtgMaxVValue and \ref rtgMaxVMultiplier 
   * fields are present in this structure.
   */
  bool                   rtgMaxVExists;
  /**
   * AC Maximum voltage rating.
   */
  u16_t                  rtgMaxVValue;
  /**
   * Specifies the exponent of \ref rtgMaxVValue.
   */
  sl_xsd_ptm_type_t      rtgMaxVMultiplier;

  /**
   * Indicates whether the \ref rtgMaxVAValue and \ref rtgMaxVAMultiplier 
   * fields are present in this structure.
   */
  bool                   rtgMaxVAExists;
  /**
   * Specifies the maximum continuous apparent power output capability of the DER, in VA.
   */
  u16_t                  rtgMaxVAValue;
  /**
   * Specifies the exponent of \ref rtgMaxVAValue.
   */
  sl_xsd_ptm_type_t      rtgMaxVAMultiplier;

  /**
   * Indicates whether the \ref rtgMaxVarValue and \ref rtgMaxVarMultiplier
   * fields are present in this structure.
   */
  bool                   rtgMaxVarExists;
  /**
   * Specifies the maximum continuous reactive power that can be delivered by
   * the DER, in var.
   */
  i16_t                  rtgMaxVarValue;
  /**
   * Specifies the exponent of \ref rtgMaxVarValue.
   */
  sl_xsd_ptm_type_t      rtgMaxVarMultiplier;

  /**
   * Indicates whether the \ref rtgMaxVarNegValue and \ref rtgMaxVarNegMultiplier
   * fields are present in this structure.
   */
  bool                   rtgMaxVarNegExists;
  /**
   * Specifies the maximum continuous reactive power that can be  received by
   * the DER, in var. If this value does not exist, the default value is
   * negative \ref rtgMaxVarValue.
   */
  i16_t                  rtgMaxVarNegValue;
  /**
   * Specifies the exponent of \ref rtgMaxVarNegValue.
   */
  sl_xsd_ptm_type_t      rtgMaxVarNegMultiplier;

  /**
   * Specifies the maximum continuous active power output capability of the DER, in watts.
   * This value represents combined generation plus storage output if
   * \ref type == \ref SL_XSD_DER_TYPE_PV_STORAGE.
   */
  i16_t                  rtgMaxWValue;
  /**
   * Specifies the exponent of \ref rtgMaxWValue.
   */
  sl_xsd_ptm_type_t      rtgMaxWMultiplier;

  /**
   * Indicates whether the \ref rtgMaxWhValue \ref rtgMaxWhMultiplier 
   * fields are present in this structure.
   */
  bool                   rtgMaxWhExists;
  /**
   * Specifies the maximum energy storage capacity of the DER, in WattHours.
   */
  u16_t                  rtgMaxWhValue;
  /**
   * Specifies the exponent of \ref rtgMaxWhValue.
   */
  sl_xsd_ptm_type_t      rtgMaxWhMultiplier;

  /**
   * Indicates whether the \ref rtgMinPFOverExcitedMultiplier and
   * \ref rtgMinPFOverExcitedDisplacement fields are present in this structure.
   */
  bool                   rtgMinPFOverExcitedExists;
  /**
   * Minimum Power Factor displacement capability of the DER when injecting 
   * reactive power (over-excited); SHALL be a positive value between 0.0 
   * (typically > 0.7) and 1.0. If absent, defaults to unity.
   */
  u16_t                  rtgMinPFOverExcitedDisplacement;
  /**
   * Specifies the exponent of \ref rtgMinPFOverExcitedDisplacement.
   */
  sl_xsd_ptm_type_t      rtgMinPFOverExcitedMultiplier;

  /**
   * Indicates whether the \ref rtgMinPFUnderExcitedMultiplier and
   * \ref rtgMinPFUnderExcitedDisplacement fields are present in this structure.
   */
  bool                   rtgMinPFUnderExcitedExists;
  /**
   * Minimum Power Factor displacement capability of the DER when absorbing 
   * reactive power (under-excited); SHALL be a positive value between 0.0 
   * (typically > 0.7) and 0.9999.  If absent, defaults to rtgMinPFOverExcited.
   */
  u16_t                  rtgMinPFUnderExcitedDisplacement;
  /**
   * Specifies the exponent of \ref rtgMinPFUnderExcitedDisplacement.
   */
  sl_xsd_ptm_type_t      rtgMinPFUnderExcitedMultiplier;

  /**
   * Indicates whether the \ref rtgMinVValue and \ref rtgMinVMultiplier 
   * fields are present in this structure.
   */
  bool                   rtgMinVExists;
  /**
   * AC Minimum voltage rating.
   */
  u16_t                  rtgMinVValue;
  /**
   * Specifies the exponent of \ref rtgMinVValue.
   */
  sl_xsd_ptm_type_t      rtgMinVMultiplier;

  /**
   * Indicates whether the \ref rtgNormalCategory exists.
   */
  bool                   rtgNormalCategoryExists;
  /**
   * Normal operating performance category as defined by IEEE 1547-2017. One of:
   * 0 - not specified
   * 1 - Category A
   * 2 - Category B
   * All other values reserved.
   */
  u8_t                   rtgNormalCategory;

  /**
   * Indicates whether the \ref rtgOverExcitedPFMultiplier and
   * \ref rtgOverExcitedPFDisplacement fields are present in this structure.
   */
  bool                   rtgOverExcitedPFExists;
  /**
   * Specified over-excited power factor.
   */
  u16_t                  rtgOverExcitedPFDisplacement;
  /**
   * Specifies the exponent of \ref rtgOverExcitedPFDisplacement.
   */
  sl_xsd_ptm_type_t      rtgOverExcitedPFMultiplier;

  /**
   * Indicates whether the \ref rtgOverExcitedWMultiplier and
   * \ref rtgOverExcitedWValue fields are present in this structure.
   */
  bool                   rtgOverExcitedWExists;
  /**
   * Active power rating in Watts at specified over-excited power factor
   * (rtgOverExcitedPF). If present, rtgOverExcitedPF SHALL be present.
   */
  i16_t                  rtgOverExcitedWValue;
  /**
   * Specifies the exponent of \ref rtgOverExcitedWValue.
   */
  sl_xsd_ptm_type_t      rtgOverExcitedWMultiplier;

  /**
   * Indicates whether the \ref rtgReactiveSusceptanceValue and 
   * \ref rtgReactiveSusceptanceMultiplier fields are present in this structure.
   */
  bool                   rtgReactiveSusceptanceExists;
  /**
   * AC Minimum voltage rating.
   */
  u16_t                  rtgReactiveSusceptanceValue;
  /**
   * Specifies the exponent of \ref rtgReactiveSusceptanceValue.
   */
  sl_xsd_ptm_type_t      rtgReactiveSusceptanceMultiplier;

  /**
   * Indicates whether the \ref rtgUnderExcitedPFMultiplier and
   * \ref rtgUnderExcitedPFDisplacement fields are present in this structure.
   */
  bool                   rtgUnderExcitedPFExists;
  /**
   * Specified under-excited power factor.
   */
  u16_t                  rtgUnderExcitedPFDisplacement;
  /**
   * Specifies the exponent of \ref rtgUnderExcitedPFDisplacement.
   */
  sl_xsd_ptm_type_t      rtgUnderExcitedPFMultiplier;

  /**
   * Indicates whether the \ref rtgUnderExcitedWMultiplier and
   * \ref rtgUnderExcitedWValue fields are present in this structure.
   */
  bool                   rtgUnderExcitedWExists;
  /**
   * Active power rating in Watts at specified under-excited power factor
   * (rtgUnderExcitedPF). If present, rtgUnderExcitedPF SHALL be present.
   */
  i16_t                  rtgUnderExcitedWValue;
  /**
   * Specifies the exponent of \ref rtgUnderExcitedWValue.
   */
  sl_xsd_ptm_type_t      rtgUnderExcitedWMultiplier;

  /**
   * Indicates whether the \ref rtgVNomValue and \ref rtgVNomMultiplier 
   * fields are present in this structure.
   */
  bool                   rtgVNomExists;
  /**
   * AC Nominal voltage rating.
   */
  u16_t                  rtgVNomValue;
  /**
   * Specifies the exponent of \ref rtgVNomValue.
   */
  sl_xsd_ptm_type_t      rtgVNomMultiplier;

  /**
   * Specifies the type of DER.
   */
  sl_xsd_der_type_t      type;
} sl_dercap_t;

/******************************************************************************/
/**
 * \struct sl_ders_t
 * This structure contains the client DER status information.
 */
typedef struct {
  /**
   * Indicates whether the \ref alarmStatusValue fields is present in this structure.
   */
  bool                            alarmStatusExists;
  /**
   * Indicates whether the \ref genConnectStatusDateTime and
   * \ref genConnectStatusValue fields are present in this structure.
   */
  bool                            genConnectStatusExists;
  /**
   * Indicates whether the \ref inverterStatusDateTime and
   * \ref inverterStatusValue fields are present in this structure.
   */
  bool                            inverterStatusExists;
  /**
   * Indicates whether the \ref localControlModeStatusDateTime and
   * \ref localControlModeStatusValue fields are present in this structure.
   */
  bool                            localControlModeStatusExists;
  /**
   * Indicates whether the \ref manufacturerStatusDateTime and
   * \ref manufacturerStatusValue fields are present in this structure.
   */
  bool                            manufacturerStatusExists;
  /**
   * Indicates whether the \ref operationalModeStatusDateTime and
   * \ref operationalModeStatusValue fields are present in this structure.
   */
  bool                            operationalModeStatusExists;
  /**
   * Indicates whether the \ref stateOfChargeStatusDateTime and
   * \ref stateOfChargeStatusValue fields are present in this structure.
   */
  bool                            stateOfChargeStatusExists;
  /**
   * Indicates whether the \ref storageModeStatusDateTime and
   * \ref storageModeStatusValue fields are present in this structure.
   */
  bool                            storageModeStatusExists;
  /**
   * Indicates whether the \ref storConnectStatusDateTime and
   * \ref storConnectStatusValue fields are present in this structure.
   */
  bool                            storConnectStatusExists;
  /**
   * Bitmap indicating the status of DER alarms (see DER LogEvents for more details).
   */
  u32_t                           alarmStatus;
   /**
   * Specifies the connect/status value for generator DER.
   */
  sl_xsd_conn_status_t            genConnectStatusValue;
  /**
   * Specifies the DER inverterStatus/value.
   */
  sl_xsd_inv_status_t             inverterStatusValue;
  /**
   * Specifies the local control mode status.
   */
  sl_xsd_local_cont_mode_status_t localControlModeStatusValue;
  /**
   * Specifies the operational mode currently in use.
   */
  sl_xsd_op_mode_status_t         operationalModeStatusValue;
  /**
   * Specifies the state of charge status.
   */
  sl_xsd_percent_t                stateOfChargeStatusValue;
  /**
   * Specifies the storage mode status.
   */
  sl_xsd_stor_mode_status_t       storageModeStatusValue;
  /**
   * Specifies the connect/status value for storage DER.
   */
  sl_xsd_conn_status_t            storConnectStatusValue;
  /**
   * Specifies the manufacturer status code.
   */
  char                            manufacturerStatusValue[SL_XSD_VALUE_LEN];
  /**
   * Specifies the date and time \ref genConnectStatusValue was set.
   */
  sl_xsd_time_type_t              genConnectStatusDateTime;
  /**
   * Specifies the date and time \ref inverterStatusValue was set.
   */
  sl_xsd_time_type_t              inverterStatusDateTime;
  /**
   * Specifies the date and time \ref localControlModeStatusValue was set.
   */
  sl_xsd_time_type_t              localControlModeStatusDateTime;
  /**
   * Specifies the date and time \ref manufacturerStatusValue was set.
   */
  sl_xsd_time_type_t              manufacturerStatusDateTime;
  /**
   * Specifies the date and time \ref operationalModeStatusValue was set.
   */
  sl_xsd_time_type_t              operationalModeStatusDateTime;
  /**
   * Specifies the date and time when the DER Status was last updated.
   */
  sl_xsd_time_type_t              readingTime;
  /**
   * Specifies the date and time \ref stateOfChargeStatusValue was last updated.
   */
  sl_xsd_time_type_t              stateOfChargeStatusDateTime;
  /**
   * Specifies the date and time \ref storageModeStatusValue was last updated.
   */
  sl_xsd_time_type_t              storageModeStatusDateTime;
  /**
   * Specifies the date and time \ref storConnectStatusValue was last updated.
   */
  sl_xsd_time_type_t              storConnectStatusDateTime;
} sl_ders_t;

/******************************************************************************/
/**
 * \struct sl_eder_services_t
 * This structure contains a boolean for each service that is supported by a
 * particular DER instance.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether DER Availability is supported.
   */
  bool                    dera;
  /**
   * Boolean indicating whether EDER Capability is supported.
   */
  bool                    dercap;
  /**
   * Boolean indicating whether DER Settings is supported.
   */
  bool                    dersett;
  /**
   * Boolean indicating whether DER Settings is supported.
   */
  bool                    ders;
} sl_eder_services_t;


/** @} */
// end addtogroup EDER_SDER_GROUP_STRUCTS

/**
 * \defgroup EDER_SDER_GROUP_MAIL_STRUCTS EDER/SDER Mail Structures
 * This section contains mail structures used by the EDER/SDER function sets.
 */
/** \addtogroup EDER_SDER_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_eder_server_dera_ind
 *
 * This message is sent to indicate to the Customer Application that a client device
 * has put a Distributed Energy Resource Availability (DERA) resource to the server.
 *
 * Dependencies: None.
 */
typedef struct {
    /**
     * Instance ID associated with the end device updating its DER Availability.
     */
    u16_t                                edevId;
  /**
   * References the SEP object.  Shall contain the following values:\n
   * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_DER_X_DERA\n
   * ref.numInstanceIDs = 3\n
   * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
   * ref.instanceIDs[1] = The unique ID for the EDEV\n
   * ref.instanceIDs[2] = The unique ID for the DER\n
   */
  sl_server_obj_ref_t   ref;
  /**
   * Flag indicating if the /ref dera field contains information.  When false,
   * this indicates that an empty resource was stored.
   */
  bool                  deraExists;
  /**
   * DERA Information.
   */
  sl_dera_t             dera;
} sl_eder_server_dera_ind;

/******************************************************************************/
/**
 * \struct sl_eder_server_dercap_ind
 *
 * This message is sent to indicate to the Customer Application that a client device
 * has put a Distributed Energy Resource Capability (DERCAP) resource to the server.
 *
 * Dependencies: None.
 */
typedef struct {
    /**
     * Instance ID associated with the end device updating its DER Capability.
     */
    u16_t                                edevId;
  /**
   * References the SEP object.  Shall contain the following values:\n
   * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_DER_X_DERCAP\n
   * ref.numInstanceIDs = 3\n
   * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
   * ref.instanceIDs[1] = The unique ID for the EDEV\n
   * ref.instanceIDs[2] = The unique ID for the DER\n
   */
  sl_server_obj_ref_t   ref;
  /**
   * Flag indicating if the /ref dercap field contains information.  When false,
   * this indicates that an empty resource was stored.
   */
  bool                  dercapExists;
  /**
   * DERCAP Information.
   */
  sl_dercap_t           dercap;
} sl_eder_server_dercap_ind;

/******************************************************************************/
/**
 * \struct sl_eder_server_ders_ind
 *
 * This message is sent to indicate to the Customer Application that a client device
 * has put a Distributed Energy Resource Status (DERS) resource to the server.
 *
 * Dependencies: None.
 */
typedef struct {
    /**
     * Instance ID associated with the end device updating its DER Status.
     */
    u16_t                                edevId;
  /**
   * References the SEP object.  Shall contain the following values:\n
   * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_DER_X_DERS\n
   * ref.numInstanceIDs = 3\n
   * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
   * ref.instanceIDs[1] = The unique ID for the EDEV\n
   * ref.instanceIDs[2] = The unique ID for the DER\n
   */
  sl_server_obj_ref_t   ref;
  /**
   * Flag indicating if the /ref ders field contains information.  When false,
   * this indicates that an empty resource was stored.
   */
  bool                  dersExists;
  /**
   * DERS Information.
   */
  sl_ders_t             ders;
} sl_eder_server_ders_ind;

/******************************************************************************/
/**
 * \struct sl_eder_server_dersett_ind
 *
 * This message is sent to indicate to the Customer Application that a client device
 * has put a Distributed Energy Resource Settings (DERSETT) resource to the server.
 *
 * Dependencies: None.
 */
typedef struct {
    /**
     * Instance ID associated with the end device updating its DER Settings.
     */
    u16_t                                edevId;
  /**
   * References the SEP object.  Shall contain the following values:\n
   * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_DER_X_DERG\n
   * ref.numInstanceIDs = 3\n
   * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
   * ref.instanceIDs[1] = The unique ID for the EDEV\n
   * ref.instanceIDs[2] = The unique ID for the DER\n
   */
  sl_server_obj_ref_t   ref;
  /**
   * Flag indicating if the /ref dersett field contains information.  When false,
   * this indicates that an empty resource was stored.
   */
  bool                  dersettExists;
  /**
   * DERSETT Information.
   */
  sl_der_settings_t     dersett;
} sl_eder_server_dersett_ind;

/******************************************************************************/
/**
 * \struct sl_eder_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the EDER Client to indicate that a EDER server has been found.
 *
 * The client application may use this indication as a trigger to start
 * putting EDER information to the server. The included server/source
 * information is used to send DER Settings, DER Availability, DER Capability, and
 * DER Status resources to the server.  If a request is made to send a resource
 * to the EDER server before this indication is sent, the EDER client will respond
 * with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Note that although a list of multiple End Device DER resources may exist on the server,
 * the EDER client will only support sending DER Settings, DER Availability, DER
 * Capability, and DER Status to the locations indicated in the first End Device DER
 * resource in the list.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * This structure indicates which services are available as part of this EDER instance.
   * The possible services are DER Settings, DER Availability, DER Capability, and
   * DER Status.
   */
  sl_eder_services_t                  services;
  /**
   * This structure contains the detailed information regarding the server.
   */
  sl_cmn_client_server_ind_t          serverDetails;
} sl_eder_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_dersett_req
 * This request is used by the client Customer Application to send a Distributed
 * Energy Resource (DER) to the DER Server. Once the request is handled
 * the SL Task responds with a \ref SL_EDER_CLIENT_SEND_DERSETT_CNF.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * The DER Settings information to be sent to the server.
   */
  sl_der_settings_t                    dersett;
} sl_eder_client_send_dersett_req;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_dersett_cnf
 * This confirmation is sent in response to the \ref SL_EDER_CLIENT_SEND_DERSETT_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                          status;
} sl_eder_client_send_dersett_cnf;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_dera_req
 * This request is used by the client Customer Application to send a Distributed
 * Energy Resource Availability (DERA) to the DER Server. Once the request is handled
 * the SL Task responds with a \ref SL_EDER_CLIENT_SEND_DERA_CNF.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * The DER Availability information to be sent to the server.
   */
  sl_dera_t                            dera;
} sl_eder_client_send_dera_req;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_dera_cnf
 * This confirmation is sent in response to the \ref SL_EDER_CLIENT_SEND_DERA_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                          status;
} sl_eder_client_send_dera_cnf;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_dercap_req
 * This request is used by the client Customer Application to send a Distributed
 * Energy Resource Capability (DERCAP) to the DER Server. Once the request is handled
 * the SL Task responds with a \ref SL_EDER_CLIENT_SEND_DERCAP_CNF.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * The DER Capability information to be sent to the server.
   */
  sl_dercap_t                          dercap;
} sl_eder_client_send_dercap_req;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_dercap_cnf
 * This confirmation is sent in response to the \ref SL_EDER_CLIENT_SEND_DERCAP_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                          status;
} sl_eder_client_send_dercap_cnf;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_ders_req
 * This request is used by the client Customer Application to send a Distributed
 * Energy Resource Status (DERS) to the DER Server. Once the request is handled
 * the SL Task responds with a \ref SL_EDER_CLIENT_SEND_DERS_CNF.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * The DER Status information to be sent to the server.
   */
  sl_ders_t                            ders;
} sl_eder_client_send_ders_req;

/******************************************************************************/
/**
 * \struct sl_eder_client_send_ders_cnf
 * This confirmation is sent in response to the \ref SL_EDER_CLIENT_SEND_DERS_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                          status;
} sl_eder_client_send_ders_cnf;

/** @} */
// end addtogroup EDER_SDER_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup EDER_SDER_GROUP


// -------------------- DER ---------------------

/**
 * \defgroup DER_GROUP DER Definitions and Structures
 * \brief This section contains definitions and structures used by the DER function set.
 */
/** \addtogroup DER_GROUP
 * @{ */

/**
 * \defgroup DER_GROUP_DEFINES DER Definitions
 * This section contains definitions used by the DER function set.
 */
/** \addtogroup DER_GROUP_DEFINES
 * @{ */

/**
 * This defines the maximum sets of DER Curve data that may be provided in a
 * single DER Curve.
 */
#define SL_DER_MAX_CURVE_DATA  10

/**
 * This defines the number of curves that can be associated with a given DERC.
 */
#define SL_DER_CLIENT_NUM_DERC_CURVES (15)

/**
 * Used by the DER Function Set. This defines the maximum number of DER Programs
 * that may be returned in a single mail message.
 */
#define SL_DER_CLIENT_MAX_NUM_DERPS (3)   // SPRK-358

/**
 * Used by the DER Function Set. This defines the maximum number of DER
 * Controls that may be returned in a single mail message.
 */
#define SL_DER_CLIENT_MAX_NUM_DERCS (2)

/**
 * Used by the DER Function Set. This defines the maximum number of DER
 * Curves that may be returned in a single mail message.
 */
#define SL_DER_CLIENT_MAX_NUM_DCS (5)

/**
 * This defines the default polling rate for DER Control events in seconds.  This
 * value is used with event handling only.
 */
#define SL_DER_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC  (5*60)

/** @} */
// end addtogroup DER_GROUP_DEFINES

/**
 * \defgroup DER_GROUP_STRUCTS DER Structures
 * This section contains structures used by the DER function set.
 */
/** \addtogroup DER_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_der_curve_data_t
 * This structure contains curve data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * If yvalue is Power Factor, then this field SHALL be present. If yvalue is 
   * not Power Factor, then this field SHALL NOT be present. True when DER is 
   * absorbing reactive power (under-excited), false when DER is injecting 
   * reactive power (over-excited).
   */
   bool         excitation;
  /**
   * Indicates whether the \ref excitation information is present in this structure.
   */
   bool         excitationExists;
  /**
   * Specifies the data value of the x-axis.
   */
  i32_t         xValue;
  /**
   * Specifies the data value of the y-axis.
   */
  i32_t         yValue;
} sl_der_curve_data_t;

/******************************************************************************/
/**
 * \struct sl_der_curve_t
 * This structure contains the data associated with DER Curves.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * If the curveType is opModVoltVar, then this field MAY be present. If the 
   * curveType is not opModVoltVar, then this field SHALL NOT be present. 
   * Enable/disable autonomous vRef adjustment. When enabled, the Volt-Var 
   * curve characteristic SHALL be adjusted autonomously as vRef changes and 
   * autonomousVRefTimeConstant SHALL be present. If a DER is able to support 
   * Volt-Var mode but is unable to support autonomous vRef adjustment, 
   * then the DER SHALL execute the curve without autonomous vRef adjustment. 
   * If not specified, then the value is false.
   */
  bool                  autonomousVRefEnable;
  /**
   * Indicates whether the \ref autonomousVRefEnable information is present 
   * in this structure.
   */
  bool                  autonomousVRefEnableExists;
  /**
   * If the curveType is opModVoltVar, then this field MAY be present. If the 
   * curveType is not opModVoltVar, then this field SHALL NOT be present. 
   * Adjustment range for vRef time constant, in hundredths of a second. 
   */
  u32_t                 autonomousVRefTimeConstant;
  /**
   * Indicates whether the \ref autonomousVRefTimeConstant information is present 
   * in this structure.
   */
  bool                  autonomousVRefTimeConstantExists;
  /**
   * Indicates the time the resource is created. This is an optional field
   * that may be used if the Server APP would like to specify the
   * creation time. if it is used, the creationTimeExists field
   * should be set to true.
   */
  sl_xsd_time_type_t    creationTime;
  /**
   * Array of size SL_DER_MAX_CURVE_DATA containing the curve data.
   */
  sl_der_curve_data_t   curveData[SL_DER_MAX_CURVE_DATA];
  /**
   * Specifies the type of curves defined in the curve group.
   */
  sl_xsd_curve_type_t   curveType;
  /**
   * Array providing a description of the DC, with length of \ref SL_XSD_DESCRIPTION_LEN.
   * Character string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for this DC of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Specifies the number of sets of curve data in the structure, of max \ref SL_DER_MAX_CURVE_DATA.
   */
  u8_t                  numCurveData;
  /**
   * Open loop response time, the time to ramp up to 90% of the new reactive power target in response
   * to the change in voltage, in hundredths of a second. Resolution is 1/100 sec. A value of 0 is
   * used to mean no limit. When not present, the device SHOULD follow its default behavior.
   */
  u16_t                 openLoopTms;
  /**
   * Indicates whether the \ref openLoopTms information is present in this
   * structure.
   */
  bool                  openLoopTmsExists;
  /**
   * Decreasing ramp rate, interpreted as a percentage change in output capability limit per
   * second (e.g. %setMaxW / sec).  Resolution is in hundredths of a percent/second. A value of 0
   * means there is no limit. If absent, ramp rate defaults to \ref setGradW.
   */
  u16_t                 rampDecTms;
  /**
   * Indicates whether the \ref rampDecTms information is present in this
   * structure.
   */
  bool                  rampDecTmsExists;
  /**
   * Increasing ramp rate, interpreted as a percentage change in output capability limit per
   * second (e.g. %setMaxW / sec).  Resolution is in hundredths of a percent/second. A value of 0
   * means there is no limit. If absent, ramp rate defaults to \ref rampDecTms.
   */
  u16_t                 rampIncTms;
  /**
   * Indicates whether the \ref rampIncTms information is present in this
   * structure.
   */
  bool                  rampIncTmsExists;
  /**
   * Specifies the configuration parameter for a low-pass filter.  Resolution
   * is in 1/100 sec, in which the filter will settle to 95% of a step change
   * in the input value.
   */
  u16_t                 rampPT1Tms;
  /**
   * Indicates whether the \ref rampPT1Tms information is present in this
   * structure.
   */
  bool                  rampPT1TmsExists;
  /**
   * If the curveType is opModVoltVar, then this field MAY be present. If the 
   * curveType is not opModVoltVar, then this field SHALL NOT be present. 
   * The nominal AC voltage (RMS) adjustment to the voltage curve points for 
   * Volt-Var curves.
   */
  u16_t                 vRef;
  /**
   * Indicates whether the \ref vRef information is present in this structure.
   */
  bool                  vRefExists;
  /**
   * Specifies the exponent for the x-axis value.
   */
  sl_xsd_ptm_type_t     xMultiplier;
  /**
   * Specifies the exponent for the y-axis value.
   */
  sl_xsd_ptm_type_t     yMultiplier;
  /**
   * Specifies the context for interpreting the y-axis value.
   */
  sl_xsd_der_ref_t      yRefType;
} sl_der_curve_t;

/******************************************************************************/
/**
 * \struct sl_der_client_list_dc_t
 * This structure contains information about a DC which is passed as part
 * of the list handling interface \ref sl_der_client_dc_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing DC data and event information.
   */
  sl_der_curve_t                    dc;
  /**
   * The unique MRID for the DERP that this DC is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                             derpMrId[SL_XSD_MRID_LEN];
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_der_client_list_dc_t;

/******************************************************************************/
/**
 * \struct sl_der_derc_base_t
 * This structure contains base DER Control data used in Default DERCs and
 * DERC events.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Specifies a requested charge or discharge mode setpoint in
   * \ref sl_der_settings_t::setMaxChargeRateValue if the setpoint is a negative
   * value or \ref sl_der_settings_t::setMaxWValue or
   * \ref sl_der_settings_t::setMaxDischargeRateValue if the setpoint is a positive
   * value.  SHALL be ignored by the client if the device is not a storage DER
   * or if \ref sl_der_settings_t::setStorageConnected is false.
   */
  /**
   * Set DER as connected (true) or disconnected (false). Used in conjunction with
   * ramp rate when re-connecting. Implies galvanic isolation.
   */
  bool                     opModConnect;
  /**
   * Indicates whether the \ref opModConnect information is present in this structure.
   */
  bool                     opModConnectExists;
  /**
   * Set DER as energized (true) or de-energized (false). Used in conjunction with
   * ramp rate when re-energizing.
   */
  bool                     opModEnergize;
  /**
   * Indicates whether the \ref opModEnergize information is present in this structure.
   */
  bool                     opModEnergizeExists;
  /**
   * The opModFixedW function specifies a requested charge or discharge mode setpoint,
   * in %setMaxChargeRateW if negative value or %setMaxW or %setMaxDischargeRateW if
   * positive value (in hundredths).
   */
  i16_t                    opModFixedW;
  /**
   * Indicates whether the \ref opModFixedW information is present in this structure.
   */
  bool                     opModFixedWExists;
  /**
   * Indicates whether the \ref opModFixedPFAbsorbWDisplacement, \ref opModFixedPFAbsorbWExcitation,
   * and \ref opModFixedPFAbsorbWMultiplier information is present in this structure.
   */
  bool                     opModFixedPFAbsorbWExists;
  /**
   * Specifies the requested Power Factor displacement setting when absorbing W.
   */
  u16_t                    opModFixedPFAbsorbWDisplacement;

  /**
   * Specifies the exponent of \ref opModFixedPFAbsorbWDisplacement.
   */
  sl_xsd_ptm_type_t        opModFixedPFAbsorbWMultiplier;
  /**
   * Indicates whether excitation is over-excited (false) or under-excited (true)
   */
  bool                     opModFixedPFAbsorbWExcitation;
  /**
   * Indicates whether the \ref opModFixedPFInjectWDisplacement, \ref opModFixedPFInjectWExcitation,
   * and \ref opModFixedPFInjectWMultiplier information is present in this structure.
   */
  bool                     opModFixedPFInjectWExists;
  /**
   * Specifies the requested Power Factor displacement setting when injecting W.
   */
  u16_t                    opModFixedPFInjectWDisplacement;

  /**
   * Specifies the exponent of \ref opModFixedPFInjectWDisplacement.
   */
  sl_xsd_ptm_type_t        opModFixedPFInjectWMultiplier;
  /**
   * Indicates whether excitation is over-excited (false) or under-excited (true)
   */
  bool                     opModFixedPFInjectWExcitation;
  /**
   * Indicates whether the \ref opModFixedVarRefType and \ref opModFixedVarValue
   * information is present in this structure.
   */
  bool                     opModFixedVarExists;
  /**
   * Indicates whether to interpret \ref opModFixedVarValue as sl_der_settings_t::setMaxVarMultiplier
   * or sl_dera_t::statVarAvailValue.
   */
  sl_xsd_der_ref_t         opModFixedVarRefType;
  /**
   * Specifies the setpoint value for reactive power.  \ref opModFixedVarRefType
   * indicates how this field is interpreted.
   */
  i16_t                    opModFixedVarValue;
  /**
   * Specifies the maximum active power generation level at the electrical
   * coupling point as a percentage of set capacity \ref sl_der_settings_t::setMaxWValue.
   */
  u16_t                    opModMaxLimW;
  /**
   * Indicates whether the \ref opModMaxLimW information is present in this structure.
   */
  bool                     opModMaxLimWExists;
  /**
   * Indicates whether the \ref opModTargetVarMult and \ref opModTargetVarValue
   * information is present in this structure.
   */
  bool                     opModTargetVarExists;
  /**
   * Specifies the exponent of \ref opModTargetVarValue.
   */
  i8_t                     opModTargetVarMult;
  /**
   * Specifies the target value for reactive power.
   */
  i16_t                    opModTargetVarValue;
  /**
   * Indicates whether the \ref opModTargetWMult and \ref opModTargetWValue
   * information is present in this structure.
   */
  bool                     opModTargetWExists;
  /**
   * Specifies the exponent of \ref opModTargetWValue.
   */
  i8_t                     opModTargetWMult;
  /**
   * Specifies the target value for active power.
   */
  i16_t                    opModTargetWValue;
  /**
   * Specifies Frequency-Droop (Frequency-Watt) operation
   */
  sl_xsd_freq_droop_t      opModFreqDroop;
  /**
   * Indicates whether the opModFreqDroop information is present in this structure.
   */
  bool                     opModFreqDroopExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_FREQ_WATT
   * is available on the DER server.
   */
  bool                     opModFreqWattCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_LVRT_MOM_CESS
   * is available on the DER server.
   */
  bool                     opModLVRTMomentaryCessationCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_LVRT_MUST_TRIP
   * is available on the DER server.
   */
  bool                     opModLVRTMustTripCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_LVRT_MAY_TRIP
   * is available on the DER server.
   */
  bool                     opModLVRTMayTripCurveExists;
    /**
     * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_HVRT_MOM_CESS
     * is available on the DER server.
     */
  bool                     opModHVRTMomentaryCessationCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_HVRT_MUST_TRIP
   * is available on the DER server.
   */
  bool                     opModHVRTMustTripCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_HVRT_MAY_TRIP
   * is available on the DER server.
   */
  bool                     opModHVRTMayTripCurveExists;
    /**
     * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_LFRT_MUST_TRIP
     * is available on the DER server.
     */
  bool                     opModLFRTMustTripCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_LFRT_MAY_TRIP
   * is available on the DER server.
   */
  bool                     opModLFRTMayTripCurveExists;
    /**
     * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_HFRT_MUST_TRIP
     * is available on the DER server.
     */
  bool                     opModHFRTMustTripCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_HFRT_MAY_TRIP
   * is available on the DER server.
   */
  bool                     opModHFRTMayTripCurveExists;
    /**
     * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_VOLT_VAR
     * is available on the DER server.
     */
  bool                     opModVoltVarCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_VOLT_WATT
   * is available on the DER server.
   */
  bool                     opModVoltWattCurveExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_WATT_PWR_FACTOR
   * is available on the DER server.
   */
  bool                     opModWattPFCurveExists;
  /**
   * Specifies which curve id represents curve type \ref SL_XSD_CURVE_TYPE_WATT_PWR_FACTOR.
   */
  u16_t                    rampTms;
  /**
   * Indicates whether the \ref rampTms information is present in this structure.
   */
  bool                     rampTmsExists;
  /**
   * Indicates whether the curve data representing curve type \ref SL_XSD_CURVE_TYPE_WATT_VAR
   * is available on the DER server.
   */
  bool                     opModWattVarCurveExists;
} sl_der_derc_base_t;


/******************************************************************************/
/**
 * \struct sl_der_derc_t
 * This structure contains DER Control data
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Base information for this DERC.
   */
  sl_der_derc_base_t        dercBase;
  /**
   * Indicates if the deviceCategory field exists in this structure.
   */
  bool                      deviceCategoryExists;
  /**
   * This field is for use in devices that can adjust energy usage (e.g., demand response, 
   * distributed energy resources).  For devices that do not respond to EndDeviceControls 
   * or DERControls (for instance, an ESI), this field should not have any bits set.
   */
  sl_xsd_dev_cat_bitmap_t   deviceCategory;
  /**
   * Contains details for this randomizable event such as start, duration,
   * response required, etc.
   */
  sl_cmn_rand_event_t       randEvent;
  /**
   * Character array that allows the server to provide a textual explanation
   * of the status. Array is of max length SL_XSD_REASON_LEN. Character string
   * must be null terminated.
   */
  char                      reason[SL_XSD_REASON_LEN];
} sl_der_derc_t;

/******************************************************************************/
/**
 * \struct sl_der_default_derc_t
 * This structure contains Default DER Control data
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Base information for this DERC.
   */
  sl_der_derc_base_t        dercBase;
  /**
   * Enter service delay.
   */
  u32_t                     setESDelay;
  /**
   * Boolean indicating whether the setESDelay is included with the DERC.
   */
  bool                      setESDelayExists;
  /**
   * Enter service frequency high.
   */
  u16_t                     setESHighFreq;
  /**
   * Boolean indicating whether the setESHighFreq is included with the DERC.
   */
  bool                      setESHighFreqExists;
  /**
   * Enter service voltage high.
   */
  i16_t                     setESHighVolt;
  /**
   * Boolean indicating whether the setESHighVolt is included with the DERC.
   */
  bool                      setESHighVoltExists;
  /**
   * Enter service frequency low.
   */
  u16_t                     setESLowFreq;
  /**
   * Boolean indicating whether the setESLowFreq is included with the DERC.
   */
  bool                      setESLowFreqExists;
  /**
   * Enter service voltage low.
   */
  i16_t                     setESLowVolt;
  /**
   * Boolean indicating whether the setESLowVolt is included with the DERC.
   */
  bool                      setESLowVoltExists;
  /**
   * Enter service ramp time, in hundredths of a second. When present, this value 
   * SHALL update the value of the corresponding setting (DERSettings::setESRampTms).
   */
  u32_t                     setESRampTms;
  /**
   * Boolean indicating whether the setESRampTms is included with the DERC.
   */
  bool                      setESRampTmsExists;
  /**
   * Enter service randomized delay, in hundredths of a second. When present, 
   * this value SHALL update the value of the corresponding setting 
   * (DERSettings::setESRandomDelay).
   */
  u32_t                     setESRandomDelay;
  /**
   * Boolean indicating whether the setESRandomDelay is included with the DERC.
   */
  bool                      setESRandomDelayExists;
  /**
   * Set default rate of change.
   */
  u16_t                     setGradW;
  /**
   * Boolean indicating whether the setGradW is included with the DERC.
   */
  bool                      setGradWExists;
  /**
   * Set soft-start rate of change.
   */
  u16_t                     setSoftGradW;
  /**
   * Boolean indicating whether the setSoftGradW is included with the DERC.
   */
  bool                      setSoftGradWExists;
  /**
   * Unique MRID for this DERC of length SL_XSD_MRID_LEN.
   */
  u8_t                      mrId[SL_XSD_MRID_LEN];
  /**
   * Array providing a description of the DERC, with max length of
   * SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                      description[SL_XSD_DESCRIPTION_LEN];
} sl_der_default_derc_t;

/******************************************************************************/
/**
 * \struct sl_der_client_derc_active_info_t
 * This structure contains information about an DERC which is being acted
 * upon by the DER client. This structure will only be valid if active
 * event handling is enabled.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the current client status of the event. This is the same status
   * that would be sent to the server in a response.
   */
  sl_xsd_resp_status_type_t eventRespStatus;
  /**
   * The length of time the event is active following the start time. Note that any
   * start time or end time randomization is calculated into this value. This is
   * the ACTUAL duration employed by the SL client.
   */
  u32_t                     randomizedDuration;
  /**
   * The time at which the event starts. Note that any start time randomization is
   * calculated into this value. This is the ACTUAL start time employed by the
   * SL client.
   */
  sl_xsd_time_type_t        randomizedStart;
} sl_der_client_derc_active_info_t;

/******************************************************************************/
/**
 * \struct sl_der_client_derc_curve_mapping_t
 * This structure contains the mRIDs of the curves that are associated with
 * a DERC. Note that not all mRIDs may be valid. Validity is determined by
 * the state of the booleans in the \ref sl_der_derc_base_t.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The mRID of the curve data representing curve type \ref SL_XSD_CURVE_TYPE_FREQ_WATT.
   * This field is valid if sl_der_derc_base_t::opModFreqWattCurveExists is TRUE.
   */
  u8_t                     opModFreqWattCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_LVRT_MOM_CESS.
   * This field is valid if sl_der_derc_base_t::opModLVRTMomentaryCessationCurveExists is TRUE.
   */
  u8_t                     opModLVRTMomentaryCessationCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_LVRT_MUST_TRIP.
   * This field is valid if sl_der_derc_base_t::opModLVRTMustTripCurveExists is TRUE.
   */
  u8_t                     opModLVRTMustTripCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_LVRT_MAY_TRIP.
   * This field is valid if sl_der_derc_base_t::opModLVRTMayTripCurveExists is TRUE.
   */
  u8_t                     opModLVRTMayTripCurveMrid[SL_XSD_MRID_LEN];
    /**
     * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_HVRT_MOM_CESS.
     * This field is valid if sl_der_derc_base_t::opModHVRTMomentaryCessationCurveExists is TRUE.
     */
  u8_t                     opModHVRTMomentaryCessationCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_HVRT_MUST_TRIP.
   * This field is valid if sl_der_derc_base_t::opModHVRTMustTripCurveExists is TRUE.
   */
  u8_t                     opModHVRTMustTripCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_HVRT_MAY_TRIP.
   * This field is valid if sl_der_derc_base_t::opModHVRTMayTripCurveExists is TRUE.
   */
  u8_t                     opModHVRTMayTripCurveMrid[SL_XSD_MRID_LEN];
    /**
     * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_LFRT_MUST_TRIP.
     * This field is valid if sl_der_derc_base_t::opModLFRTMustTripCurveExists is TRUE.
     */
  u8_t                     opModLFRTMustTripCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_LFRT_MAY_TRIP.
   * This field is valid if sl_der_derc_base_t::opModLFRTMayTripCurveExists is TRUE.
   */
  u8_t                     opModLFRTMayTripCurveMrid[SL_XSD_MRID_LEN];
    /**
     * The mRID of the curve data representing the curve type \ref SL_XSD_CURVE_TYPE_HFRT_MUST_TRIP.
     * This field is valid if sl_der_derc_base_t::opModHFRTMustTripCurveExists is TRUE.
     */
  u8_t                     opModHFRTMustTripCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing curve type \ref SL_XSD_CURVE_TYPE_HFRT_MAY_TRIP.
   * This field is valid if sl_der_derc_base_t::opModHFRTMayTripCurveExists is TRUE.
   */
  u8_t                     opModHFRTMayTripCurveMrid[SL_XSD_MRID_LEN];
    /**
     * The mRID of the curve data representing curve type \ref SL_XSD_CURVE_TYPE_VOLT_VAR.
     * This field is valid if sl_der_derc_base_t::opModVoltVarCurveExists is TRUE.
     */
  u8_t                     opModVoltVarCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing curve type \ref SL_XSD_CURVE_TYPE_VOLT_WATT.
   * This field is valid if sl_der_derc_base_t::opModVoltWattCurveExists is TRUE.
   */
  u8_t                     opModVoltWattCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing curve type \ref SL_XSD_CURVE_TYPE_WATT_PWR_FACTOR.
   * This field is valid if sl_der_derc_base_t::opModWattPFCurveExists is TRUE.
   */
  u8_t                     opModWattPFCurveMrid[SL_XSD_MRID_LEN];
  /**
   * The mRID of the curve data representing curve type \ref SL_XSD_CURVE_TYPE_WATT_VAR.
   * This field is valid if sl_der_derc_base_t::opModWattVarCurveExists is TRUE.
   */
  u8_t                     opModWattVarCurveMrid[SL_XSD_MRID_LEN];
} sl_der_client_derc_curve_mapping_t;

/******************************************************************************/
/**
 * \struct sl_der_client_list_derc_t
 * This structure contains information about a DERC which is passed as part
 * of the list handling interface \ref sl_der_client_derc_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the event (i.e.,
   * information calculated or maintained by the DER Client as part of active
   * handling).
   */
  sl_der_client_derc_active_info_t   activeInfo;
  /**
   * Boolean indicating whether the activeInfo structure contains valid information.
   * In the case that active handling is disabled, this field will always be set to
   * FALSE. In the case that active handling is enabled, this field may or may not
   * be present depending on whether the DER Client is acting on it.
   */
  bool                               activeInfoExists;
  /**
   * Provides a mapping of which curve mRIDs are associated with this DERC and in
   * what capacity.
   */
  sl_der_client_derc_curve_mapping_t curveMapping;
  /**
   * Curve data associated with this DERC.
   */
  sl_der_client_list_dc_t            curves[SL_DER_CLIENT_NUM_DERC_CURVES];
  /**
   * The unique MRID for the DERP that this DERC is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                               derpMrId[SL_XSD_MRID_LEN];
  /**
   * Structure containing DERC data and event information.
   */
  sl_der_derc_t                      derc;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t         eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t                 eventStatusDateTime;
  /**
   * Indicates how many curves are included in the \ref sl_der_client_list_derc_t::curves array.
   * Note that this value can be set to 0, and curve data can be passed via the
   * curve list handling interface. Or it may be 0 if no curves exist for the DDERC.
   */
  u8_t                               numCurves;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t          respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                   version;
} sl_der_client_list_derc_t;

/******************************************************************************/
/**
 * \struct sl_der_derp_t
 * This structure contains information about an DERP.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Ascii description of the DER Program with max length of
   * SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for this DERP of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the relative primacy of the provider of this Program.
   */
  sl_xsd_primacy_type_t primacyType;
  /**
   * Indicates whether program has a dercListLink
   */
  bool                  dercListLinkExists;
} sl_der_derp_t;

/******************************************************************************/
/**
 * \struct sl_der_client_list_derp_t
 * This structure contains information about an DERP which is passed as part
 * of the list handling interface \ref sl_der_client_derp_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Provides a mapping of which curve mRIDs are associated with this DDERC and in
   * what capacity.
   */
  sl_der_client_derc_curve_mapping_t curveMapping;
  /**
   * Curve data associated with this DDERC.
   */
  sl_der_client_list_dc_t            curves[SL_DER_CLIENT_NUM_DERC_CURVES];
  /**
   * Default DERC information.
   */
  sl_der_default_derc_t              dderc;
  /**
   * Boolean indicating whether the DDERC is included with the DERP.
   */
  bool                               ddercExists;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                   ddercVersion;
  /**
   * DERP information.
   */
  sl_der_derp_t                      derp;
  /**
   * Indicates how many curves are included in the \ref sl_der_client_list_derc_t::curves array.
   * Note that this value can be set to 0, and curve data can be passed via the
   * curve list handling interface. Or it may be 0 if no curves exist for the DDERC.
   */
  u8_t                               numCurves;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                   version;
} sl_der_client_list_derp_t;

/******************************************************************************/
/**
 * \struct sl_der_server_derc_curve_ids_t
 * This structure contains the set of curve instance Ids associated with a
 * particular DERC.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Specifies which curve id represents curve type \ref SL_XSD_CURVE_TYPE_FREQ_WATT. This
   * is only valid if \ref sl_der_derc_base_t::opModFreqWattCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModFreqWattCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_LVRT_MAY_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModLVRTMayTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModLVRTMayTripCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_LVRT_MOM_CESS. This is only valid if
   * \ref sl_der_derc_base_t::opModLVRTMomentaryCessationCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModLVRTMomentaryCessationCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_LVRT_MUST_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModLVRTMustTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModLVRTMustTripCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_HVRT_MAY_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModHVRTMayTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModHVRTMayTripCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_HVRT_MOM_CESS. This is only valid if
   * \ref sl_der_derc_base_t::opModHVRTMomentaryCessationCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModHVRTMomentaryCessationCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_HVRT_MUST_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModHVRTMustTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModHVRTMustTripCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_LFRT_MAY_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModLFRTMayTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModLFRTMayTripCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_LFRT_MUST_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModLFRTMustTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModLFRTMustTripCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_HFRT_MAY_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModHFRTMayTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModHFRTMayTripCurveId;
  /**
   * Specifies which curve id represents the curve type
   * \ref SL_XSD_CURVE_TYPE_HFRT_MUST_TRIP. This is only valid if
   * \ref sl_der_derc_base_t::opModHFRTMustTripCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModHFRTMustTripCurveId;
  /**
   * Specifies which curve id represents curve type \ref SL_XSD_CURVE_TYPE_VOLT_VAR.
   * This is only valid if \ref sl_der_derc_base_t::opModVoltVarCurveExists is set to TRUE.
   */
  sl_obj_instance_id_t   opModVoltVarCurveId;
  /**
   * Specifies which curve id represents curve type \ref SL_XSD_CURVE_TYPE_VOLT_WATT.
   * This is only valid if \ref sl_der_derc_base_t::opModVoltWattCurveExists is set to TRUE.
   *
   */
  sl_obj_instance_id_t  opModVoltWattCurveId;
  /**
   * Specifies which curve id represents Watt-PowerFactor mode. This is only valid
   * if \ref sl_der_derc_base_t::opModWattPFCurveExists is set to TRUE.
   *
   */
  sl_obj_instance_id_t   opModWattPFCurveId;
  /**
   * Specifies which curve id represents curve type \ref SL_XSD_CURVE_TYPE_WATT_VAR.
   * This is only valid if \ref sl_der_derc_base_t::opModWattVarCurveExists is set to TRUE.
   *
   */
  sl_obj_instance_id_t   opModWattVarCurveId;
  /**
   * Indicates which response set group should be used for client responses to this event.
   */
  sl_obj_instance_id_t   respSetGroupId;
  /**
   * Indicates which response set should be used for client responses to this event.
   */
  sl_obj_instance_id_t   respSetId;
} sl_der_server_derc_curve_ids_t;


/** @} */
// end addtogroup DER_GROUP_STRUCTS

/**
 * \defgroup DER_GROUP_MAIL_STRUCTS DER Mail Structures
 * This section contains mail structures used by the DER function set.
 */
/** \addtogroup DER_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_der_server_create_derp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Distributed
 * Energy Resource Program (DERP) within the DER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_der_server_create_derp_cnf.
 *
 * The ref field of the sl_der_server_create_derp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t   ref;
  /**
   * DERP Information.
   */
  sl_der_derp_t         derp;
} sl_der_server_create_derp_req;

/******************************************************************************/
/**
 * \struct sl_der_server_create_derp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_DERP_X (Distributed Energy Resource
 * Program). The confirmation provides a status of the operation and contains
 * the ref structure for the created DERP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_der_server_create_derp_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_create_derp_cnf
 */
typedef sl_server_obj_cnf_t sl_der_server_create_derp_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_derp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Distributed
 * Energy Resource Program (DERP) within the DER Server. It will also cause all child
 * events to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_der_server_delete_derp_cnf.
 *
 * The ref field of the sl_der_server_delete_derp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 *
 * Dependencies: The \ref sl_der_server_delete_derp_req may only be sent after an
 * \ref sl_der_server_create_derp_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_der_server_delete_derp_req
*/
typedef sl_server_obj_ref_t sl_der_server_delete_derp_req;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_derp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_DERP_X (Distributed Energy Resource Program or
 * DERP). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted DERP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_der_server_delete_derp_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_delete_derp_cnf
*/
typedef sl_server_obj_cnf_t sl_der_server_delete_derp_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_create_derc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new DER Control
 * (DERC) within the DER Server. This request will trigger the DER Server to
 * create the DERC and to start the associated timers and other handling for the
 * DERC. Once the request is handled the SL Task responds with a mail message of
 * \ref SL_SERVER_OBJ_CREATE_CNF using the structure \ref sl_der_server_create_derc_cnf.
 *
 * The ref field of the sl_der_server_create_derc_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 *
 * Dependencies: The sl_der_server_create_derc_req may only be sent after
 * a DERP has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t              ref;
  /**
   * If TRUE, indicates to the SL server that the creation time
   * included in the DERC should be used to specify the resource creation time. If
   * FALSE, indicates to the SL server to use the current time
   * as the creation time.
   */
  bool                             creationTimeExists;
  /**
   * Specifies the curve IDs associated with the curve types for this DERC.
   * The curve IDs listed in this structure are only valid if the associated
   * "exists" flag is enabled.
   */
  sl_der_server_derc_curve_ids_t   curveIds;
  /**
   * Contains the DERC data, including event specific details
   * such as start and duration.
   */
  sl_der_derc_t                    derc;
  /**
   * Indicates which response set group should be used for client responses to this event.
   */
  sl_obj_instance_id_t             respSetGroupId;
  /**
   * Indicates which response set should be used for client responses to this event.
   */
  sl_obj_instance_id_t             respSetId;
} sl_der_server_create_derc_req;

/******************************************************************************/
/**
 * \struct sl_der_server_create_derc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_DERP_X_DERC_X (Distributed Energy
 * Resource Control). The confirmation provides a status of the operation
 * and contains the ref structure for the created DERC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_der_server_create_derp_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 * ref.instanceIDs[2] = The unique ID for the DERC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_create_derc_cnf
 */
typedef sl_server_obj_cnf_t sl_der_server_create_derc_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_cancel_derc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_REQ mail message.
 *
 * This request is used by the Customer Application to immediately cancel an
 * existing DERC (DER Control) within the DER Server. Once the request is handled
 * the SL Task responds with a mail message of \ref SL_SERVER_OBJ_CANCEL_CNF using
 * the structure \ref sl_der_server_cancel_derc_cnf.
 *
 * The ref field of the sl_der_server_cancel_derc_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 * ref.instanceIDs[2] = The unique ID for the DERC\n
 *
 * Dependencies: The sl_der_server_cancel_derc_req may only be sent after
 * a DERC has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
 *
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t ref;
  /**
   * Indicates whether the client needs to apply randomization to the
   * cancel time.
   */
  bool          randomize;
  /**
   * Variable length array that allows the server to provide a textual
   * explanation of the status. Array is of max length SL_XSD_REASON_LEN.
   * Character string must be null terminated.
   */
  char          reason[SL_XSD_REASON_LEN];
} sl_der_server_cancel_derc_req;

/******************************************************************************/
/**
 * \struct sl_der_server_cancel_derc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CANCEL_REQ
 * message to cancel a \ref SL_OBJ_ID_X_DERP_X_DERC_X (DER Control) object.
 * The confirmation provides a status of the operation and contains the ref
 * structure of the canceled DERC. It uses the generic cancel confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_der_server_cancel_derc_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 * ref.instanceIDs[2] = The unique ID for the DERC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_cancel_derc_cnf
*/
typedef sl_server_obj_cnf_t sl_der_server_cancel_derc_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_derc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a DER
 * Control (DERC) within the DER Server. It will also delete the active DERC if
 * there is one associated with this DERC. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_der_server_delete_derc_cnf.
 *
 * The ref field of the sl_der_server_delete_derc_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 * ref.instanceIDs[2] = The unique ID for the DERC\n
 *
 * Dependencies: The \ref sl_der_server_delete_derc_req may only be sent after an
 * \ref sl_der_server_create_derc_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_delete_derc_req
*/
typedef sl_server_obj_ref_t sl_der_server_delete_derc_req;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_derc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_DERP_X_DERC_X (DER Control or
 * DERC). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted DERC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_der_server_delete_derc_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 * ref.instanceIDs[2] = The unique ID for the DERC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_delete_derc_cnf
*/
typedef sl_server_obj_cnf_t sl_der_server_delete_derc_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_event_status_ind
 * This indication is sent to the Customer Server application from the DER
 * server to indicate a change in the event status of objects of type
 * \ref SL_OBJ_ID_X_DERP_X_DERC_X. This is an unsolicited
 * message sent directly to the Application Task. It uses the generic
 * event status indication structure \ref sl_server_obj_event_status_ind_t.
 *
 * The ref field of the sl_der_server_derc_ind will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_DERP_X_DERC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 * ref.instanceIDs[2] = The unique ID for the DERC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_event_status_ind_t sl_der_server_event_status_ind
*/
typedef sl_server_obj_event_status_ind_t sl_der_server_event_status_ind;

/******************************************************************************/
/**
 * \struct sl_der_server_store_default_derc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a Default DER
 * Control (DERC) within the DER Server. Once the request is handled the SL Task
 * responds with a mail message of \ref SL_SERVER_OBJ_CREATE_CNF using the
 * structure \ref sl_der_server_store_default_derc_cnf. Subsequent requests
 * to create the Default DERC for a given DERP will overwrite the existing
 * Default DERC for that DERP.
 *
 * Note: This structure takes the place of the sl_der_server_create_default_derc_req,
 * which is deprecated.
 *
 * The ref field of the sl_der_server_store_default_derc_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_DERP_X_DDERC\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 *
 * Dependencies: The sl_der_server_store_default_derc_req may only be sent after
 * a DERP has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t              ref;
  /**
   * Specifies the curve IDs associated with the curve types for this DERC.
   * The curve IDs listed in this structure are only valid if the associated
   * "exists" flag is enabled.
   */
  sl_der_server_derc_curve_ids_t   curveIds;
  /**
   * Contains the default DERC data
   */
  sl_der_default_derc_t            dderc;
} sl_der_server_store_default_derc_req;

// DEPRECATED: The sl_der_server_create_default_derc_req is deprecated.
// sl_der_server_store_default_derc_req should be used in its place.
typedef sl_der_server_store_default_derc_req sl_der_server_create_default_derc_req;

/******************************************************************************/
/**
 * \struct sl_der_server_store_default_derc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_DERP_X_DDERC (Default DER Control).
 * The confirmation provides a status of the operation and contains the ref
 * structure for the created DDERC. It uses the generic cancel confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * Note: This structure takes the place of the sl_der_server_create_default_derc_cnf,
 * which is deprecated.
 *
 * The ref field of the sl_der_server_store_default_derc_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DDERC\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_store_default_derc_cnf
 */
typedef sl_server_obj_cnf_t sl_der_server_store_default_derc_cnf;

// DEPRECATED: The sl_der_server_create_default_derc_cnf is deprecated.
// sl_der_server_sotre_default_derc_cnf should be used in its place.
typedef sl_der_server_store_default_derc_cnf sl_der_server_create_default_derc_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_default_derc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a default DER
 * Control (DDERC) within the DER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_der_server_delete_default_derc_cnf.
 *
 * The ref field of the sl_der_server_delete_default_derc_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DDERC\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 *
 * Dependencies: The \ref sl_der_server_delete_default_derc_req may only be sent after an
 * \ref sl_der_server_create_default_derc_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_delete_default_derc_req
*/
typedef sl_server_obj_ref_t sl_der_server_delete_default_derc_req;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_default_derc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref sl_der_server_delete_default_derc_cnf (Default DER
 * Control or DDERC). The confirmation provides a status of the operation and
 * contains the ref structure for the deleted DDERC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the contains will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DDERC\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_delete_default_derc_cnf
*/
typedef sl_server_obj_cnf_t sl_der_server_delete_default_derc_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_create_dc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new
 * \ref SL_OBJ_ID_X_DERP_X_DDERC (DER Curve) resource within the DER Server.
 * Once the request is handled the SL Task responds with a
 * \ref SL_SERVER_OBJ_CREATE_CNF with an objID of \ref SL_OBJ_ID_X_DERP_X_DERC_X.
 *
 * The ref field of the sl_der_server_create_dc_req must be defined as
 * follows:\n
 * ref.objId    = SL_OBJ_ID_X_DERP_X_DC_X\n
 * ref.numInstanceIDs  = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 *
 * Dependencies: The sl_der_server_create_dc_req may only be sent after
 * a DERP has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t   ref;
  /**
   * If TRUE, indicates to the SL server that the creation time
   * included in the DC should be used to specify the resource creation time. If
   * FALSE, indicates to the SL server to use the current time
   * as the creation time.
   */
  bool                  creationTimeExists;
  /**
   * Contains the curve data.
   */
  sl_der_curve_t        curve;
} sl_der_server_create_dc_req;

/******************************************************************************/
/**
 * \struct sl_der_server_create_dc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_DERP_X_DC_X (DER Curve).
 * The confirmation provides a status of the operation and contains the ref
 * structure for the created DC. It uses the generic cancel confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_der_server_create_default_derc_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 * ref.instanceIDs[2] = The unique ID for the DC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_create_dc_cnf
 */
typedef sl_server_obj_cnf_t sl_der_server_create_dc_cnf;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_dc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a DER
 * Curve (DC) within the DER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_der_server_delete_dc_cnf.
 *
 * The ref field of the sl_der_server_delete_dc_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DERP\n
 * ref.instanceIDs[2] = The unique ID for the DC\n
 *
 * Dependencies: The \ref sl_der_server_delete_dc_req may only be sent after an
 * \ref sl_der_server_create_dc_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_delete_dc_req
*/
typedef sl_server_obj_ref_t sl_der_server_delete_dc_req;

/******************************************************************************/
/**
 * \struct sl_der_server_delete_dc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_DERP_X_DERC_X (DER Curve or
 * DC). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted DC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_der_server_delete_dc_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DERP_X_DC_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DERP\n
 * ref.instanceIDs[2] = The unique ID for the DC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_der_server_delete_dc_cnf
*/
typedef sl_server_obj_cnf_t sl_der_server_delete_dc_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_dc_ind
 * This indication is sent to the Customer Client application from the DER
 * client to indicate that a new DC has been received. This is an unsolicited
 * message sent directly to the Application Task. This indication refers to
 * the next DC.
 *
 * If the DER client receives a DERC which indicates that curve data exists,
 * the first time that DERC is received the DER Client will GET the curve data
 * from the DER server and provide it to the Customer Application in a
 * \ref SL_DER_CLIENT_DC_IND message.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The unique MRID for the DERC that this DC is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                      dercMrid[SL_XSD_MRID_LEN];
  /**
   * Contains the curve data.
   */
  sl_der_curve_t            curve;
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t               status; // TODO: Why?
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t          version;
} sl_der_client_dc_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_default_derc_ind
 * This indication is sent to the Customer Client application from the DER
 * client to indicate that a new Default DERC has been received. This is an
 * unsolicited message sent directly to the Application Task.
 *
 * Dependencies: None.
 *
 */
typedef struct {
  /**
   * Indicates whether the Default DERC exists.
   */
   bool                     ddercExists;
  /**
   * Structure containing Default DERC.
   */
  sl_der_default_derc_t     dderc;
  /**
   * The unique MRID for the DERP that this Default DERC is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                      derpMrId[SL_XSD_MRID_LEN];
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t          version;
} sl_der_client_default_derc_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_derc_ind
 * This indication is sent to the Customer Client application from the DER
 * client to indicate that a new DERC has been received. This is an unsolicited
 * message sent directly to the Application Task. This indication refers to
 * the next DERC that will be handled by the DERC Client.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Specifies a bitmap indicating the DER Control.
   */
  sl_xsd_der_cont_t                controlType;
  /**
   * Structure containing information about the active handling of the event (i.e.,
   * information calculated or maintained by the DER Client as part of active
   * handling).
   */
  sl_der_client_derc_active_info_t activeInfo;
  /**
   * Structure containing DERC data and event information.
   */
  sl_der_derc_t                    derc;
  /**
   * The unique MRID for the DERP that this event is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                             derpMrId[SL_XSD_MRID_LEN];
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_der_client_derc_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_derp_ind
 * This indication is sent to the Customer Client application from the DER
 * Client to indicate that a new DERP has been received. This is an unsolicited
 * message sent directly to the Application Task.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether this indication contains valid DER Program information.
   * If false, the /ref derp field does not contain valid information.
   */
  bool                                derpExists;
  /**
   * DERP information.
   */
  sl_der_derp_t                       derp;
  /**
   * Server and source information associated with this DRP.
   */
  sl_cmn_client_server_source_info_t  serverSourceInfo;
  /**
   * Indicates the status of the current program (received/deleted/server lost).
   */
  sl_cmn_prog_status_t                status;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                    version;
} sl_der_client_derp_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the DER Client to indicate that a new DER server has been found. Note
 * that multiple indications may be sent if there are multiple servers and/or
 * sources of DRLC information available.
 *
 * The client application may use this indication as a trigger to start
 * requesting DER information from the DER client. The included server/source
 * information is used to request a DERP list via the \ref sl_der_client_get_derp_list_req.
 * If DER information is requested before this indication is sent, the DER
 * client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_der_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_der_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_set_event_programs_req
 * This request is used by the Customer Application to request a list of DER
 * Programs to be used for event processing.  The \ref SL_DER_CLIENT_SET_EVENT_PROGRAMS_CNF
 * will be sent as an acknowledgment of the request.  If the request is successful
 * a \ref SL_DER_CLIENT_EVENT_PROGRAMS_IND will be sent after the confirm to
 * indicate the change to the DER Program event list.
 *
 * Dependencies: The client must receive the DERP mrIds for the requested DER Programs
 *               from the \ref SL_DER_CLIENT_DERP_IND.
 *
 * typedef sl_cmn_client_set_event_programs_req_t sl_der_client_set_event_programs_req
 */
typedef sl_cmn_client_set_event_programs_req_t sl_der_client_set_event_programs_req;

/******************************************************************************/
/**
 * \struct sl_der_client_set_event_programs_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DER_CLIENT_SET_EVENT_PROGRAMS_REQ. It contains a status field
 * which indicates success if the request is being handled, or an error status
 * in case the request is not being handled.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_programs_cnf_t sl_der_client_set_event_programs_cnf
*/
typedef sl_cmn_client_set_event_programs_cnf_t sl_der_client_set_event_programs_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_event_programs_ind
 * This indication is sent when there is a change to the list of DER Programs that
 * are being used for event processing.
 *
 * Dependencies: None
 *
 * typedef sl_cmn_client_event_programs_ind_t sl_der_client_event_programs_ind
 */
typedef sl_cmn_client_event_programs_ind_t sl_der_client_event_programs_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_set_event_roots_req
 * This request is used by the Customer Application to request a list of DER servers
 * to be used for event processing, up to a maximum of \ref SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS.
 * The \ref SL_DER_CLIENT_SET_EVENT_ROOTS_CNF will be sent as an acknowledgment
 * of this request.
 *
 * Note that the client app is responsible for meeting the following requirement
 * defined in the SEP2.0 specification:
 *   "When devices are registered to one or more DER servers, they SHALL NOT act
 *    upon any public DER servers that are present in the HAN or become available."
 *
 * Also note that the client app may not select a root(server/source) which is
 * not indicated to be time synced in \ref sl_der_client_server_ind.
 *
 * Dependencies: The client app must receive indication of available DER servers
 *               from \ref sl_der_client_server_ind.
 *
 * typedef sl_cmn_client_set_event_roots_req_t sl_der_client_set_event_roots_req
 */
typedef sl_cmn_client_set_event_roots_req_t sl_der_client_set_event_roots_req;

/******************************************************************************/
/**
 * \struct sl_der_client_set_event_roots_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DER_CLIENT_SET_EVENT_ROOTS_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_roots_cnf_t sl_der_client_set_event_roots_cnf
 */
typedef sl_cmn_client_set_event_roots_cnf_t sl_der_client_set_event_roots_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_event_roots_ind
 * This indication is sent to the Customer Application when there is a change in
 * the list of roots that are used for event processing.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_event_roots_ind_t sl_der_client_event_roots_ind;
 */
typedef sl_cmn_client_event_roots_ind_t sl_der_client_event_roots_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_set_event_poll_rate_req
 * This request is used by the Customer Application to change the Services Layer
 * polling rate for DER Control events.  The default event polling rate for DER
 * is \ref SL_DER_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_req_t sl_der_client_set_event_poll_rate_req
 */
typedef sl_cmn_client_set_event_poll_rate_req_t sl_der_client_set_event_poll_rate_req;

/******************************************************************************/
/**
 * \struct sl_der_client_set_event_poll_rate_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DER_CLIENT_SET_EVENT_POLL_RATE_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_der_client_set_event_poll_rate_cnf
 */
typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_der_client_set_event_poll_rate_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_get_derp_list_req
 * This request is used by the Customer Application to request some number
 * of DERPs. The \ref SL_DER_CLIENT_GET_DERP_LIST_CNF will be sent as an
 * acknowledgment of the request, and the DERPs themselves will be sent in
 * the \ref SL_DER_CLIENT_DERP_LIST_IND message. While the application may request as
 * many DERPs as it wants up to 254 (255 is defined as requesting all available DERPs)
 * only up to \ref SL_DER_CLIENT_MAX_NUM_DERPS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_DER_CLIENT_GET_DERP_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The app client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_DER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DER client. An error will be
 * returned if there is no DRLC server.
 *
 * typedef sl_cmn_get_list_req_root_t sl_der_client_get_derp_list_req
*/
typedef sl_cmn_get_list_req_root_t sl_der_client_get_derp_list_req;

/******************************************************************************/
/**
 * \struct sl_der_client_get_derp_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DER_CLIENT_GET_DERP_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_der_client_get_derp_list_cnf
*/
typedef sl_cmn_get_list_cnf_t sl_der_client_get_derp_list_cnf;


/******************************************************************************/
/**
 * \struct sl_der_client_cancel_get_derp_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for DERPs. Note that until the \ref SL_DER_CLIENT_CANCEL_GET_DERP_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The SL_DER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DERe client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_der_client_cancel_get_derp_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_der_client_cancel_get_derp_list_req;


/******************************************************************************/
/**
 * \struct sl_der_client_cancel_get_derp_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated DERP processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_der_client_cancel_get_derp_list_cnf
*/
typedef sl_cmn_cancel_get_list_cnf_t sl_der_client_cancel_get_derp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_derp_list_ind
 * This indication is sent in response to the \ref SL_DER_CLIENT_GET_DERP_LIST_REQ.
 * It will contain some number of DERPs up to \ref SL_DER_CLIENT_MAX_NUM_DERPS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available DERPS have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t         results;
  /**
   * List of DERPs.
   */
  sl_der_client_list_derp_t list[];  // Variable length up to SL_DER_CLIENT_MAX_NUM_DERPS
} sl_der_client_derp_list_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_get_derc_list_req
 * This request is used by the Customer Application to request some number
 * of DERCs. The \ref SL_DER_CLIENT_GET_DERC_LIST_CNF will be sent as an
 * acknowledgment of the request, and the DERCs themselves will be sent in
 * the \ref SL_DER_CLIENT_DERC_LIST_IND message. While the application may request as
 * many DERCs as it wants, only up to \ref SL_DER_CLIENT_MAX_NUM_DERCS will be returned
 * in a single indication. Therefore this request may generate multiple indications.
 *
 * Dependencies: The \ref SL_DER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DER client. Also, the client
 * must receive the DERP information for the requested DERCs either from the
 * \ref SL_DER_CLIENT_DERP_LIST_IND or the \ref SL_DER_CLIENT_DERP_IND.
 *
 * typedef sl_cmn_get_list_req_time_t sl_der_client_get_derc_list_req
 */
typedef sl_cmn_get_list_req_time_t sl_der_client_get_derc_list_req;

/******************************************************************************/
/**
 * \struct sl_der_client_get_derc_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DER_CLIENT_GET_DERC_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_der_client_get_derc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t  sl_der_client_get_derc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_cancel_get_derc_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for DERCs. Note that until the \ref SL_DER_CLIENT_CANCEL_GET_DERC_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_DER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DER client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_der_client_cancel_get_derc_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_der_client_cancel_get_derc_list_req;

/******************************************************************************/
/**
 * \struct sl_der_client_cancel_get_derc_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated DERC processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_der_client_cancel_get_derc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_der_client_cancel_get_derc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_derc_list_ind
 * This indication is sent in response to the \ref SL_DER_CLIENT_GET_DERC_LIST_REQ.
 * It will contain some number of DERCs up to \ref SL_DER_CLIENT_MAX_NUM_DERCS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available DERCs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of DERCs.
   */
  sl_der_client_list_derc_t list[];  // Variable length up to SL_DER_CLIENT_MAX_NUM_DERCS
} sl_der_client_derc_list_ind;

/******************************************************************************/
/**
 * \struct sl_der_client_get_dc_list_req
 * This request is used by the Customer Application to request some number
 * of DCs. The \ref SL_DER_CLIENT_GET_DC_LIST_CNF will be sent as an
 * acknowledgment of the request, and the DCs themselves will be sent in
 * the \ref SL_DER_CLIENT_DC_LIST_IND message. While the application may request as
 * many DCs as it wants, only up to \ref SL_DER_CLIENT_MAX_NUM_DCS will be returned
 * in a single indication. Therefore this request may generate multiple indications.
 *
 * Dependencies: The \ref SL_DER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DER client. Also, the client
 * must receive the DERP information for the requested DCs either from the
 * \ref SL_DER_CLIENT_DERP_LIST_IND or the \ref SL_DER_CLIENT_DERP_IND.
 *
 * typedef sl_cmn_get_list_req_quantity_t sl_der_client_get_dc_list_req
 */
typedef sl_cmn_get_list_req_quantity_t sl_der_client_get_dc_list_req;

/******************************************************************************/
/**
 * \struct sl_der_client_get_dc_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DER_CLIENT_GET_DC_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_der_client_get_dc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t  sl_der_client_get_dc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_cancel_get_dc_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for DCs. Note that until the \ref SL_DER_CLIENT_CANCEL_GET_DC_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_DER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DER client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_der_client_cancel_get_dc_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_der_client_cancel_get_dc_list_req;

/******************************************************************************/
/**
 * \struct sl_der_client_cancel_get_dc_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated DC processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_der_client_cancel_get_dc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_der_client_cancel_get_dc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_der_client_dc_list_ind
 * This indication is sent in response to the \ref SL_DER_CLIENT_GET_DC_LIST_REQ.
 * It will contain some number of DCs up to \ref SL_DER_CLIENT_MAX_NUM_DCS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available DCs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of DCs.
   */
  sl_der_client_list_dc_t list[];  // Variable length up to SL_DER_CLIENT_MAX_NUM_DCS
} sl_der_client_dc_list_ind;

/** @} */
// end addtogroup DER_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup DER_GROUP


// -------------------- DINFO -------------------

/**
 * \defgroup DINFO_GROUP EDINFO/SDINFO Definitions and Structures
 * \brief This section contains definitions and structures used by the End
 *        Device Info (EDINFO) and Self Device Info (SDINFO) function sets.
 */
/** \addtogroup DINFO_GROUP
 * @{ */

/**
 * \defgroup DINFO_GROUP_DEFINES DER Definitions
 * This section contains definitions used by the DINFO function set.
 */
/** \addtogroup DINFO_GROUP_DEFINES
 * @{ */

/******************************************************************************/
/**
 * \defgroup SL_DINFO_FUNCS_IMPL_XXX SL DINFO Functions Implemented: sl_dinfo_funcs_impl_t (SL_DINFO_FUNCS_IMPL_XXX)
 * SL Device Info function set values. Defines a bitmap of function sets that are
 * implemented.
 */
/** \addtogroup SL_DINFO_FUNCS_IMPL_XXX
* @{ */
/**
 * \var typedef u64_t sl_dinfo_funcs_impl_t
 * Acceptable values are SL_DINFO_FUNCS_IMPL_XXX.
 */
typedef u64_t sl_dinfo_funcs_impl_t;

/**
 * Device Capabilities function set.
 */
#define SL_DINFO_FUNCS_IMPL_DCAP      (0x00000001)
/**
 * Self Device function set.
 */
#define SL_DINFO_FUNCS_IMPL_SDEV      (0x00000002)
/**
 * End Device function set.
 */
#define SL_DINFO_FUNCS_IMPL_EDEV      (0x00000004)
/**
 * Function Set Assignments function set.
 */
#define SL_DINFO_FUNCS_IMPL_FSA       (0x00000008)
/**
 * Subscription/Notification function sets.
 */
#define SL_DINFO_FUNCS_IMPL_SUBS      (0x00000010)
/**
 * Response function set.
 */
#define SL_DINFO_FUNCS_IMPL_RESP      (0x00000020)
/**
 * Time function set.
 */
#define SL_DINFO_FUNCS_IMPL_TIME      (0x00000040)
/**
 * Device Information function set.
 */
#define SL_DINFO_FUNCS_IMPL_DINFO     (0x00000080)
/**
 * Power Status function set.
 */
#define SL_DINFO_FUNCS_IMPL_PWRSTAT   (0x00000100)
/**
 * Network Status function set.
 */
#define SL_DINFO_FUNCS_IMPL_NETSTAT   (0x00000200)
/**
 * Log Event function set.
 */
#define SL_DINFO_FUNCS_IMPL_LOG       (0x00000400)
/**
 * Configuration Resource function set.
 */
#define SL_DINFO_FUNCS_IMPL_CONFIG    (0x00000800)
/**
 * File Download function set.
 */
#define SL_DINFO_FUNCS_IMPL_FILE      (0x00001000)
/**
 * Demand Response Load Control function set.
 */
#define SL_DINFO_FUNCS_IMPL_DRLC      (0x00002000)
/**
 * Metering function set.
 */
#define SL_DINFO_FUNCS_IMPL_METER     (0x00004000)
/**
 * Pricing function set.
 */
#define SL_DINFO_FUNCS_IMPL_PRICE     (0x00008000)
/**
 * Messaging function set.
 */
#define SL_DINFO_FUNCS_IMPL_MSG       (0x00010000)
/**
 * Billing function set.
 */
#define SL_DINFO_FUNCS_IMPL_BILL      (0x00020000)
/**
 * Prepayment function set.
 */
#define SL_DINFO_FUNCS_IMPL_PPY       (0x00040000)
/**
 * Eneregy Flow Reservation function set.
 */
#define SL_DINFO_FUNCS_IMPL_FLOW      (0x00080000)
/**
 * Distributed Energy Resource function set.
 */
#define SL_DINFO_FUNCS_IMPL_DER       (0x00100000)
/** @} */

/** @} */
// end addtogroup DINFO_GROUP_DEFINES

/**
 * \defgroup DINFO_GROUP_STRUCTS Device Info Structures
 * This section contains structures used by the EDINFO and SDINFO function sets.
 */
/** \addtogroup DINFO_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_device_info_t
 * This structure contains Device Info data.  The Device Info contains general
 * information about the device.
 *
 * <b> NOTE: The SupportedLocale resource is not yet supported. </b>
 *
 * Dependencies: None.
 */
typedef struct
{
  /**
  * The default polling rate for this function set (this resource and all
  * resources below), in seconds. If not specified, a default of 900 seconds
  * (15 minutes) is used. It is RECOMMENDED a client poll the resources of
  * this function set every pollRate seconds.
  */
  u32_t                  pollRate;
  /**
  * Boolean indicating if the optional pollRate field is valid.
  */
  bool                   pollRateExists;
  /**
   * DRLC Capabilities
   */
  sl_xsd_drlc_capabilities_t drlcCapa;
  /**
   * Boolean indicating if the optional drlcCapa field is valid.
   */
  bool                   drlcCapaExists;

  /**
   * gpsLocation latitude
   */
  char                   gpsLocationLat[SL_XSD_GPSLOCATION_LEN];
  /**
   * gpsLocation longitude
   */
  char                   gpsLocationLon[SL_XSD_GPSLOCATION_LEN];
  /**
   * Boolean indicating if the optional gpsLocationLat and gpsLocationLon fields
   * are valid.
   */
  bool                   gpsLocationExists;

  /**
   * The date and time that the device was manufactured.
   */
  sl_xsd_time_type_t     mfDate;
  /**
   * The hardware version number of the device.
   */
  char                   mfHWVersion[SL_XSD_DESCRIPTION_LEN];
  /**
   * The manufacturer's IANA enterprise number.
   */
  u32_t                  mfId;
  /**
   * Manufacturer-specific device information. This is an optional field.
   * Set to the empty string if it should not be included in the device info.
   */
  char                   mfInfo[SL_XSD_DESCRIPTION_LEN];
  /**
   * The model number of the device.
   */
  char                   mfModel[SL_XSD_DESCRIPTION_LEN];
  /**
   * The serial number of the device.
   */
  char                   mfSerialNum[SL_XSD_DESCRIPTION_LEN];
  /**
   * The devices's primary source of power.
   */
  sl_xsd_power_source_t  primaryPower;
  /**
   * The device's secondary source of power.
   */
  sl_xsd_power_source_t  secondaryPower;
  /**
   * The date and time that the software currently running on the device
   * was activated.
   */
  sl_xsd_time_type_t     swActivationTime;
  /**
   * The version number of the software currently running on the device.
   */
  char                   swVersion[SL_XSD_DESCRIPTION_LEN];
} sl_device_info_t;

/** @} */
// end addtogroup DINFO_GROUP_STRUCTS

/**
 * \defgroup DINFO_GROUP_MAIL_STRUCTS Device Info Mail Structures
 * This section contains mail structures used by the SDINFO and EDINFO function sets.
 */
/** \addtogroup DINFO_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_sdinfo_server_store_dinfo_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new
 * \ref SL_OBJ_ID_X_SDEV_SDI (Self Device - Device Info) resource within the DINFO
 * Server. Once the request is handled the SL Task responds with a
 * \ref SL_SERVER_OBJ_CREATE_CNF with an objID of \ref SL_OBJ_ID_X_SDEV_SDI.
 *
 * This request may not be sent prior to sending the \ref SL_STARTUP_REQ and
 * receiving the \ref SL_STARTUP_CNF.
 *
 * The ref field of the sl_sdinfo_server_store_dinfo_req must be defined as
 * follows:\n
 * ref.objId    = SL_OBJ_ID_X_SDEV_SDI\n
 * ref.numInstanceIDs  = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: MUST NOT be sent prior to receiving the \ref SL_STARTUP_CNF.
 */
typedef struct {
  /**
   * References the SEP object (and action) for delivery of this message.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Device Info information
   */
  sl_device_info_t       devInfo;
  /**
   * Boolean indicating if the optional Function sets implemented
   * field should be included in the device information.
   */
  bool                   includeFuncSets;
} sl_sdinfo_server_store_dinfo_req;

/******************************************************************************/
/**
 * \struct sl_sdinfo_server_store_dinfo_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_SDEV_SDI (Self Device - Device Info Resource).
 * The confirmation provides a status of the operation and contains the ref
 * structure for the created resource. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_sdinfo_server_store_dinfo_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_SDI\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_sdinfo_server_store_dinfo_cnf
 */
typedef sl_server_obj_cnf_t sl_sdinfo_server_store_dinfo_cnf;

/******************************************************************************/
/**
 * \struct sl_edinfo_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the EDINFO Client to indicate that a EDINFO server has been found.
 *
 * The client application may use this indication as a trigger to start
 * putting DINFO information to the server. The included server/source
 * information is used to put a EDINFO via the \ref sl_edinfo_client_send_dinfo_req.
 * If \ref sl_edinfo_client_send_dinfo_req is requested before this indication is
 * sent, the DINFO client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_edinfo_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_edinfo_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_edinfo_client_send_dinfo_req
 * This request is used by the client Customer Application to put a Device Info
 * resource to a EDINFO Server. Once the request is handled
 * the SL Task responds with a \ref SL_EDINFO_CLIENT_SEND_DINFO_CNF.
 *
 * Dependencies: None.
 *
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * The device specific information provided in this request.
   */
  sl_device_info_t                     devInfo;
  /**
   * Boolean indicating if the optional Function sets implemented
   * field should be included in the device information.
   */
  bool                                 includeFuncSets;

} sl_edinfo_client_send_dinfo_req;

/******************************************************************************/
/**
 * \struct sl_edinfo_client_send_dinfo_cnf
 * This confirmation is sent in response to the \ref SL_EDINFO_CLIENT_SEND_DINFO_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t         transactionId;
  /**
   * Status indicating whether the operation was successful or not.
   */
  i8_t          status;
} sl_edinfo_client_send_dinfo_cnf;

/******************************************************************************/
/**
 * \struct sl_edinfo_server_dinfo_ind
 * This indication is sent to the Customer Application when a client device
 * updates the information stored in its device information resource.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Instance ID associated with the end device updating its device information.
   */
  u16_t                                edevId;
  /**
   * The new client device information.
   */
  sl_device_info_t                     devInfo;
  /**
   * Boolean indicating whether the functionsImplemented field is valid.
   */
  bool                                 functionsImplementedExists;
  /*
   * A bitmap of the function sets implemented by the client.
   */
  sl_dinfo_funcs_impl_t                functionsImplemented;
  /**
   * The Long Form Device Identifier of the client device.
   */
  u8_t                                 lFDI[SL_XSD_LFDI_LEN];
} sl_edinfo_server_dinfo_ind;

/** @} */
// end addtogroup DINFO_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup DINFO_GROUP


// -------------------- DRLC --------------------

/**
 * \defgroup DRLC_GROUP DRLC Definitions and Structures
 * \brief This section contains definitions and structures used by the DRLC function set.
 */
/** \addtogroup DRLC_GROUP
 * @{ */

/**
 * \defgroup DRLC_GROUP_DEFINES DRLC Definitions
 * This section contains definitions used by the DRLC function set.
 */
/** \addtogroup DRLC_GROUP_DEFINES
 * @{ */

/**
 * Used by the DRLC Function Set. This defines the maximum number of DR Programs
 * that may be returned in a single mail message.
 */
#define SL_DRLC_CLIENT_MAX_NUM_DRPS (5)

/**
 * Used by the DRLC Function Set. This defines the maximum number of End Device
 * Controls that may be returned in a single mail message.
 */
#define SL_DRLC_CLIENT_MAX_NUM_EDCS (5)

/**
 * This defines the default polling rate for DR End Device Control events in seconds.
 * This value is used with event handling only.
 */
#define SL_DRLC_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC  (5*60)

/** @} */
// end addtogroup DRLC_GROUP_DEFINES


/**
 * \defgroup DRLC_GROUP_STRUCTS DRLC Structures
 * This section contains structures used by the DRLC function set.
 */
/** \addtogroup DRLC_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_drlc_drp_t
 * This structure contains DRLC DRP data. Currently this structure is used
 * on the server side when creating a DRP. However, its use will be extended
 * to additional server interfaces as well as client interfaces in future
 * releases.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Specifies the minimum LSA sheddablePercent change which SHALL trigger an
   * end device to update their LSA. If set to 100, LSA SHALL be posted once
   * (if it is provided), but need not be updated thereafter. 0 SHALL NOT be
   * used. If neither threshold is specified, then LSA updates from end devices
   * are not requested.
   */
  sl_xsd_percent_t      availUpdatePercentThresh;
  /**
   * Boolean indicating whether the availUpdatePercentThresh is included in the DRP.
   */
  bool                  availUpdatePercentThreshExists;
  /**
   * Specifies the minimum LSA sheddablePower change which SHALL trigger an end
   * device to update their LSA. 0 SHALL NOT be used. If neither threshold is
   * specified, then LSA updates from end devices are not requested.
   */
  sl_xsd_active_power_t availUpdatePowerThresh;
  /**
   * Boolean indicating whether the availUpdatePowerThresh is included in the DRP.
   */
  bool                  availUpdatePowerThreshExists;
  /**
   * Character array providing a description of the DRP, with max length
   *  of \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for this DRP of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the type of provider sending the DRP.
   */
  sl_xsd_primacy_type_t primacyType;
} sl_drlc_drp_t;

/******************************************************************************/
/**
 * \struct sl_drlc_client_list_drp_t
 * This structure contains information about an DRP which is passed as part
 * of the list handling interface \ref sl_drlc_client_drp_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * DRP information.
   */
  sl_drlc_drp_t                        drp;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                     version;
} sl_drlc_client_list_drp_t;

/******************************************************************************/
/**
 * \struct sl_drlc_client_edc_active_info_t
 * This structure contains information about an EDC which is being acted
 * upon by the DRLC client. This structure will only be valid if active
 * event handling is enabled.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the current client status of the EDC. This is the same status
   * that would be sent to the server in a DR response.
   */
  sl_xsd_resp_status_type_t eventRespStatus;
  /**
   * Indicates whether the Customer Application is currently opted-out of the event
   */
  bool                      opt_out;
  /**
   * The length of time the event is active following the start time. Note that any
   * start time or end time randomization is calculated into this value. This is
   * the ACTUAL duration employed by the SL client.
   */
  u32_t                     randomizedDuration;
  /**
   * The time at which the event starts. Note that any start time randomization is
   * calculated into this value. This is the ACTUAL start time employed by the
   * SL client.
   */
  sl_xsd_time_type_t        randomizedStart;
} sl_drlc_client_edc_active_info_t;

/******************************************************************************/
/**
 * \struct sl_drlc_edc_t
 * This structure contains DRLC EDC data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the type of appliance load reduction requested.
   */
  sl_xsd_appliance_load_red_type_t  applianceLoadRed;
  /**
   * The value change requested for the cooling offset, in degree C / 10. The
   * value should be added to the normal set point for cooling.
   */
  u8_t                              coolOffset;
  /**
   * Boolean indicating whether or not the coolOffset field is present in the
   * EDC. Field not present indicates that this field has not been used by the
   * end device.
   */
  bool                              coolOffsetExists;
  /**
   * Cooling Temperature Set Point / 100 = temperature in degrees Celsius where
   * -273.15C <= temperature <= 327.67C, corresponding to a Cooling Temperature
   * Set Point. The maximum resolution this format allows is 0.01C. The field
   * not present indicates that this field has not been used by the end device.
   */
  i16_t                             coolSetpoint;
  /**
   * Boolean indicating whether or not the cooling setpoint field is present in
   * the EDC. Field not present indicates that this field has not been used by
   * the end device.
   */
  bool                              coolSetpointExists;
  /**
   * Specifies the bitmap specifying the category of devices that should respond.
   */
  sl_xsd_dev_cat_bitmap_t           deviceBitmap;
  /**
   * A flag to indicate if the EDC is considered a mandatory event as defined by
   * the service provider issuing the EDC. The flag alerts the client/user that
   * they will be subject to penalty or ineligibility based on the service
   * provider's program rules for that EndDeviceCategory.
   */
  bool                              drpMandatory;
  /**
   * Contains the maximum On state duty cycle applied by the end device, as a
   * percentage of time.  The field not present indicates that this field has
   * not been used by the end device.
   */
  u8_t                              dutyCycle;
  /**
   * Boolean indicating whether or not the dutyCycle field is present in the
   * EDC. Field not present indicates that this field has not been used by the
   * end device.
   */
  bool                              dutyCycleExists;
  /**
   * The value change requested for the heating offset, in degree C / 10.
   * The value should be subtracted for heating.
   */
  u8_t                              heatOffset;
  /**
   * Boolean indicating whether or not the heatOffset field is present in the
   * EDC. Field not present indicates that this field has not been used by the
   * end device.
   */
  bool                              heatOffsetExists;
  /**
   * Heating Temperature Set Point / 100 = temperature in degrees Celsius where
   * -273.15C <= temperature <= 327.67C, corresponding to a Heating Temperature
   * Set Point. The maximum resolution this format allows is 0.01C. The field
   * not present indicates that this field has not been used by the end device.
   */
  i16_t                             heatSetpoint;
  /**
   * Boolean indicating whether or not the heating setpoint field is present in
   * the EDC. Field not present indicates that this field has not been used by
   * the end device.
   */
  bool                              heatSetpointExists;
  /**
   * The value change requested for the load adjustment percentage, in tenths of
   * a percent. The value should be subtracted from the normal setting.
   */
  u16_t                             loadAdjustPercentOffset;
  /**
   * Boolean indicating whether or not the loadAdjustPercentOffset field is
   * present in the EDC. Field not present indicates that this field has not
   * been used by the end device.
   */
  bool                              loadAdjustPercentOffsetExists;
  /**
   * Indicates that the event intends to increase consumption.
   * TRUE: Indicates the intention to increase usage value
   * FALSE: indicates the intention to decrease usage
   */
  bool                              loadShiftForward;
  /**
   * The overrideDuration attribute provides a duration, in seconds, for which a
   * client device is allowed to override an EDC as contractually agreed upon
   * with a service provider.
   */
  u16_t                             overrideDuration;
  /**
   * Contains details for this randomizable event such as start, duration,
   * response required, etc.
   */
  sl_cmn_rand_event_t               randEvent;
  /**
   * Character array that allows the server to provide a textual explanation
   * of the status. Array is of max length \ref SL_XSD_REASON_LEN. Character string
   * must be null terminated.
   */
  char                              reason[SL_XSD_REASON_LEN];
  /**
   * Boolean indicating whether or not the targetReduction Type and Value fields
   * are present in the EDC.
   */
  bool                              targetReductionExists;
  /**
   * Threshold to which a device should reduce its load. Indicates the type of
   * reduction requested.
   */
  sl_xsd_unit_type_t                targetReductionType;
  /**
   * Threshold to which a device should reduce its load. Indicates the requested
   * amount of the relevant commodity to be reduced, as defined by the
   * targetReductionType.
   */
  u16_t                             targetReductionValue;
} sl_drlc_edc_t;

/******************************************************************************/
/**
 * \struct sl_drlc_client_list_edc_t
 * This structure contains information about an EDC which is passed as part
 * of the list handling interface \ref sl_drlc_client_edc_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the EDC (i.e.,
   * information calculated or maintained by the DRLC Client as part of active
   * handling).
   */
  sl_drlc_client_edc_active_info_t activeInfo;
  /**
   * Boolean indicating whether the activeInfo structure contains valid information.
   * In the case that active handling is disabled, this field will always be set to
   * FALSE. In the case that active handling is enabled, this field may or may not
   * be present depending on whether the DRLC Client is acting on it.
   */
  bool                             activeInfoExists;
  /**
   * The unique MRID for the DRP that this EDC is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                             drpMrId[SL_XSD_MRID_LEN];
  /**
   * Structure containing EDC data and event information.
   */
  sl_drlc_edc_t                    edc;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_drlc_client_list_edc_t;

/** @} */
// end addtogroup DRLC_GROUP_STRUCTS

/**
 * \defgroup DRLC_GROUP_MAIL_STRUCTS DRLC Mail Structures
 * This section contains mail structures used by the DRLC function set.
 */
/** \addtogroup DRLC_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_drlc_server_create_drp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Demand
 * Response Program (DRP) within the DRLC Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_drlc_server_create_drp_cnf.
 *
 * The ref field of the sl_drlc_server_create_drp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t   ref;
  /**
   * DRP Information.
   */
  sl_drlc_drp_t         drp;
} sl_drlc_server_create_drp_req;

/******************************************************************************/
/**
 * \struct sl_drlc_server_create_drp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_DR_X (Demand Response Program or
 * DRP). The confirmation provides a status of the operation and contains
 * the ref structure for the created DRP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_drlc_server_create_drp_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DRP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_drlc_server_create_drp_cnf
 */
typedef sl_server_obj_cnf_t sl_drlc_server_create_drp_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_server_delete_drp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Demand
 * Response Program (DRP) within the DRLC Server. It will also cause all child
 * events to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_drlc_server_delete_drp_cnf.
 *
 * The ref field of the sl_drlc_server_delete_drp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DRP\n
 *
 * Dependencies: The \ref sl_drlc_server_delete_drp_req may only be sent after an
 * \ref sl_drlc_server_create_drp_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_drlc_server_delete_drp_req
*/
typedef sl_server_obj_ref_t sl_drlc_server_delete_drp_req;

/******************************************************************************/
/**
 * \struct sl_drlc_server_delete_drp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_DR_X (Demand Response Program or
 * DRP). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted DRP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_drlc_server_delete_drp_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DRP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_drlc_server_delete_drp_cnf
*/
typedef sl_server_obj_cnf_t sl_drlc_server_delete_drp_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_server_create_edc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new End Device Control
 * (EDC) within the DRLC Server. This request will trigger the DRLC Server to
 * create the EDC and to start the associated timers and other handling for the
 * EDC. Once the request is handled the SL Task responds with a mail message of
 * \ref SL_SERVER_OBJ_CREATE_CNF using the structure \ref sl_drlc_server_create_edc_cnf.
 *
 * The ref field of the sl_drlc_server_create_edc_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_DR_X_EDC_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DRP\n
 *
 * Dependencies: The sl_drlc_server_create_edc_req may only be sent after
 * a DRP has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t     ref;
  /**
   * If TRUE, indicates to the SL server that the creation time
   * included in the EDC should be used to specify the resource creation time. If
   * FALSE, indicates to the SL server to use the current time
   * as the creation time.
   */
  bool                     creationTimeExists;
  /**
   * Structure containing the details of the EDC, including event specific details
   * such as start and duration.
   */
  sl_drlc_edc_t            edc;
  /**
   * Indicates which response set group should be used for client responses to this event.
   */
  sl_obj_instance_id_t     respSetGroupId;
  /**
   * Indicates which response set should be used for client responses to this event.
   */
  sl_obj_instance_id_t     respSetId;
} sl_drlc_server_create_edc_req;

/******************************************************************************/
/**
 * \struct sl_drlc_server_create_edc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_DR_X_EDC_X (End Device Control or
 * EDC). The confirmation provides a status of the operation
 * and contains the ref structure for the created EDC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_drlc_server_create_edc_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X_EDC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DRP\n
 * ref.instanceIDs[2] = The unique ID for the EDC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_drlc_server_create_edc_cnf
 */
typedef sl_server_obj_cnf_t sl_drlc_server_create_edc_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_server_cancel_edc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_REQ mail message.
 *
 * This request is used by the Customer Application to immediately cancel an
 * existing EDC (End Device Control) within the DRLC Server. Once the request is handled
 * the SL Task responds with a mail message of \ref SL_SERVER_OBJ_CANCEL_CNF using
 * the structure \ref sl_drlc_server_cancel_edc_cnf.
 *
 * The ref field of the sl_drlc_server_cancel_edc_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_DR_X_EDC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DRP\n
 * ref.instanceIDs[2] = The unique ID for the EDC\n
 *
 * Dependencies: The sl_drlc_server_cancel_edc_req may only be sent after
 * an EDC has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t ref;
  /**
   * Indicates whether the client needs to apply randomization to the
   * cancel time.
   */
  bool                randomize;
  /**
   * Character array that allows the server to provide a textual
   * explanation of the status. Array is of max length \ref SL_XSD_REASON_LEN.
   * Character string must be null terminated.
   */
  char                 reason[SL_XSD_REASON_LEN];
} sl_drlc_server_cancel_edc_req;

/******************************************************************************/
/**
 * \struct sl_drlc_server_cancel_edc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CANCEL_REQ
 * message to cancel a \ref SL_OBJ_ID_X_DR_X_EDC_X (End Device Control) object.
 * The confirmation provides a status of the operation and contains the ref
 * structure of the canceled EDC. It uses the generic cancel confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_drlc_server_cancel_edc_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X_EDC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DRP\n
 * ref.instanceIDs[2] = The unique ID for the EDC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_drlc_server_cancel_edc_cnf
*/
typedef sl_server_obj_cnf_t sl_drlc_server_cancel_edc_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_server_delete_edc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete an End Device
 * Control (EDC) within the DRLC Server. It will also delete the active EDC if
 * there is one associated with this EDC. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_drlc_server_delete_edc_cnf.
 *
 * The ref field of the sl_drlc_server_delete_edc_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X_EDC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DRP\n
 * ref.instanceIDs[2] = The unique ID for the EDC\n
 *
 * Dependencies: The \ref sl_drlc_server_delete_edc_req may only be sent after an
 * \ref sl_drlc_server_create_edc_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_drlc_server_delete_edc_req
*/
typedef sl_server_obj_ref_t sl_drlc_server_delete_edc_req;

/******************************************************************************/
/**
 * \struct sl_drlc_server_delete_edc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_DR_X_EDC_X (End Device Control or
 * EDC). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted EDC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_drlc_server_delete_edc_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_DR_X_EDC_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DRP\n
 * ref.instanceIDs[2] = The unique ID for the EDC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_drlc_server_delete_edc_cnf
*/
typedef sl_server_obj_cnf_t sl_drlc_server_delete_edc_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_server_event_status_ind
 * This indication is sent to the Customer Server application from the DRLC
 * server to indicate a change in the event status of objects of type
 * \ref SL_OBJ_ID_X_DR_X_EDC_X. This is an unsolicited
 * message sent directly to the Application Task. It uses the generic
 * event status indication structure \ref sl_server_obj_event_status_ind_t.
 *
 * The ref field of the sl_drlc_server_event_status_ind will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_DR_X_EDC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent DRP\n
 * ref.instanceIDs[2] = The unique ID for the event\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_event_status_ind_t sl_drlc_server_event_status_ind
 */
typedef sl_server_obj_event_status_ind_t sl_drlc_server_event_status_ind;

/******************************************************************************/
/**
 * \struct sl_drlc_client_edc_ind
 * This indication is sent to the Customer Client application from the DRLC
 * client to indicate that a new EDC has been received. This is an unsolicited
 * message sent directly to the Application Task. This indication refers to
 * the next EDC. If more than the next EDC is needed, the client may send the
 * \ref SL_DRLC_CLIENT_GET_EDC_LIST_REQ to request more.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the EDC (i.e.,
   * information calculated or maintained by the DRLC Client as part of active
   * handling).
   */
  sl_drlc_client_edc_active_info_t activeInfo;
  /**
   * The unique MRID for the DRP that this EDC is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                             drpMrId[SL_XSD_MRID_LEN];
  /**
   * Structure containing EDC data and event information.
   */
  sl_drlc_edc_t                    edc;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_drlc_client_edc_ind;



/******************************************************************************/
/**
 * \struct sl_drlc_client_drp_ind
 * This indication is sent to the Customer Client application from the DRLC
 * Client to indicate that a new DRP has been received. This is an unsolicited
 * message sent directly to the Application Task. If more than this DRP is needed,
 * the client may send the \ref SL_DRLC_CLIENT_GET_DRP_LIST_REQ to request more.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether this indication contains DRP information.
   * If false, the /ref drp field does not contain information.
   */
  bool                                drpExists;
  /**
   * DRP information.
   */
  sl_drlc_drp_t                       drp;
  /**
   * Server and source information associated with this DRP.
   */
  sl_cmn_client_server_source_info_t  serverSourceInfo;
  /**
   * Indicates the status of the current program (received/deleted/server lost).
   */
  sl_cmn_prog_status_t                status;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                    version;
} sl_drlc_client_drp_ind;

/******************************************************************************/
/**
 * \struct sl_drlc_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the DRLC Client to indicate that a new DRLC server has been found. Note
 * that multiple indications may be sent if there are multiple servers and/or
 * sources of DRLC information available.
 *
 * The client application may use this indication as a trigger to start
 * requesting DRLC information from the DRLC client. The included server/source
 * information is used to request a DRP list via the \ref sl_drlc_client_get_drp_list_req.
 * If DRLC information is requested before this indication is sent, the DRLC
 * client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_drlc_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_drlc_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_event_programs_req
 *
 * This request is used by the Customer Application to request a list of DR
 * Programs to be used for event processing.  The \ref SL_DRLC_CLIENT_SET_EVENT_PROGRAMS_CNF
 * will be sent as an acknowledgment of the request.  If the request is successful
 * a \ref SL_DRLC_CLIENT_EVENT_PROGRAMS_IND will be sent after the confirm to
 * indicate the change to the DR Program event list.
 *
 * Dependencies: The client must receive the DRP mrIds for the requested DR Programs
 *               from the \ref SL_DRLC_CLIENT_DRP_IND.
 *
 * typedef sl_cmn_client_set_event_programs_req_t sl_drlc_client_set_event_programs_req
 */
typedef sl_cmn_client_set_event_programs_req_t sl_drlc_client_set_event_programs_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_event_programs_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DRLC_CLIENT_SET_EVENT_PROGRAMS_REQ. It contains a status field
 * which indicates success if the request is being handled, or an error status
 * in case the request is not being handled.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_programs_cnf_t sl_drlc_client_set_event_programs_cnf
*/
typedef sl_cmn_client_set_event_programs_cnf_t sl_drlc_client_set_event_programs_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_event_programs_ind
 *
 * This indication is sent when there is a change to the list of DR Programs that
 * are being used for event processing.
 *
 * Dependencies: None
 *
 * typedef sl_cmn_client_event_programs_ind_t sl_drlc_client_event_programs_ind
 */
typedef sl_cmn_client_event_programs_ind_t sl_drlc_client_event_programs_ind;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_event_roots_req
 *
 * This request is used by the Customer Application to request a list of DRLC servers
 * to be used for event processing, up to a maximum of \ref SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS.
 * The \ref SL_DRLC_CLIENT_SET_EVENT_ROOTS_CNF will be sent as an acknowledgment
 * of this request.
 *
 * Note that the client app is responsible for meeting the following requirement
 * defined in the SEP2.0 specification:
 *   "When devices are registered to one or more DRLC servers, they SHALL NOT act
 *    upon any public DRLC servers that are present in the HAN or become available."
 *
 * Also note that the client app may not select a root(server/source) which is
 * not indicated to be time synced in \ref sl_drlc_client_server_ind.
 *
 * Dependencies: The client app must receive indication of available DRLC servers
 *               from \ref sl_drlc_client_server_ind.
 *
 * typedef sl_cmn_client_set_event_roots_req_t sl_drlc_client_set_event_roots_req
 */
typedef sl_cmn_client_set_event_roots_req_t sl_drlc_client_set_event_roots_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_event_roots_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DRLC_CLIENT_SET_EVENT_ROOTS_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_roots_cnf_t sl_drlc_client_set_event_roots_cnf
*/
typedef sl_cmn_client_set_event_roots_cnf_t sl_drlc_client_set_event_roots_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_event_roots_ind
 *
 * This indication is sent to the Customer Application when there is a change in
 * the list of roots that are used for event processing.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_event_roots_ind_t sl_drlc_client_event_roots_ind;

*/
typedef sl_cmn_client_event_roots_ind_t sl_drlc_client_event_roots_ind;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_event_poll_rate_req
 * This request is used by the Customer Application to change the Services Layer
 * polling rate for DR End Device Control (EDC) events.  The default event polling
 * rate for DRLC is \ref SL_DRLC_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_req_t sl_drlc_client_set_event_poll_rate_req
 */
typedef sl_cmn_client_set_event_poll_rate_req_t sl_drlc_client_set_event_poll_rate_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_event_poll_rate_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DRLC_CLIENT_SET_EVENT_POLL_RATE_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_drlc_client_set_event_poll_rate_cnf
 */
typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_drlc_client_set_event_poll_rate_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_get_drp_list_req
 * This request is used by the Customer Application to request some number
 * of DRPs. The \ref SL_DRLC_CLIENT_GET_DRP_LIST_CNF will be sent as an
 * acknowledgment of the request, and the DRPs themselves will be sent in
 * the \ref SL_DRLC_CLIENT_DRP_LIST_IND message. While the application may request as
 * many DRPs as it wants up to 254 (255 is defined as requesting all available DRPs)
 * only up to \ref SL_DRLC_CLIENT_MAX_NUM_DRPS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_DRLC_CLIENT_GET_DRP_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The app client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_DRLC_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DRLC client. An error will be
 * returned if there is no DRLC server.
 *
 * typedef sl_cmn_get_list_req_root_t sl_drlc_client_get_drp_list_req
*/
typedef sl_cmn_get_list_req_root_t sl_drlc_client_get_drp_list_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_get_drp_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DRLC_CLIENT_GET_DRP_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_drlc_client_get_drp_list_cnf
*/
typedef sl_cmn_get_list_cnf_t sl_drlc_client_get_drp_list_cnf;


/******************************************************************************/
/**
 * \struct sl_drlc_client_cancel_get_drp_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for DRPs. Note that until the \ref SL_DRLC_CLIENT_CANCEL_GET_DRP_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The SL_DRLC_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DRLC client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_drlc_client_cancel_get_drp_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_drlc_client_cancel_get_drp_list_req;


/******************************************************************************/
/**
 * \struct sl_drlc_client_cancel_get_drp_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated DRP processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_drlc_client_cancel_get_drp_list_cnf
*/
typedef sl_cmn_cancel_get_list_cnf_t sl_drlc_client_cancel_get_drp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_drp_list_ind
 * This indication is sent in response to the \ref SL_DRLC_CLIENT_GET_DRP_LIST_REQ.
 * It will contain some number of DRPs up to \ref SL_DRLC_CLIENT_MAX_NUM_DRPS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available DRPS have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t         results;
  /**
   * List of DRPs.
   */
  sl_drlc_client_list_drp_t list[];  // Variable length up to SL_DRLC_CLIENT_MAX_NUM_DRPS
} sl_drlc_client_drp_list_ind;

/******************************************************************************/
/**
 * \struct sl_drlc_client_get_edc_list_req
 * This request is used by the Customer Application to request some number
 * of EDCs. The \ref SL_DRLC_CLIENT_GET_EDC_LIST_CNF will be sent as an
 * acknowledgment of the request, and the EDCs themselves will be sent in
 * the \ref SL_DRLC_CLIENT_EDC_LIST_IND message. While the application may request as
 * many EDCs as it wants, only up to \ref SL_DRLC_CLIENT_MAX_NUM_EDCS will be returned
 * in a single indication. Therefore this request may generate multiple indications.
 *
 * Dependencies: The \ref SL_DRLC_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DRLC client. Also, the client
 * must receive the DRP information for the requested EDCs either from the
 * \ref SL_DRLC_CLIENT_DRP_LIST_IND or the \ref SL_DRLC_CLIENT_DRP_IND.
 *
 * typedef sl_cmn_get_list_req_time_t sl_drlc_client_get_edc_list_req
 */
typedef sl_cmn_get_list_req_time_t sl_drlc_client_get_edc_list_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_get_edc_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_DRLC_CLIENT_GET_EDC_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_drlc_client_get_edc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t  sl_drlc_client_get_edc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_cancel_get_edc_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for EDCs. Note that until the \ref SL_DRLC_CLIENT_CANCEL_GET_EDC_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_DRLC_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the DRLC client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_drlc_client_cancel_get_edc_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_drlc_client_cancel_get_edc_list_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_cancel_get_edc_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated list processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_drlc_client_cancel_get_edc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_drlc_client_cancel_get_edc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_edc_list_ind
 * This indication is sent in response to the \ref SL_DRLC_CLIENT_GET_EDC_LIST_REQ.
 * It will contain some number of EDCs up to \ref SL_DRLC_CLIENT_MAX_NUM_EDCS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available EDCs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of EDCs.
   */
  sl_drlc_client_list_edc_t list[];  // Variable length up to SL_DRLC_CLIENT_MAX_NUM_EDCS
} sl_drlc_client_edc_list_ind;

/******************************************************************************/
/**
 * \struct sl_drlc_client_opt_out_edc_req
 * This request is used by the Customer Application to opt-out of an End Device
 * Control (EDC). Once the Customer Application has opted-out of an EDC, the
 * Customer Application may opt back in to the EDC by sending a
 * \ref SL_DRLC_CLIENT_OPT_IN_EDC_REQ.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Unique MRID for the EDC to override of length SL_XSD_MRID_LEN.
   */
  u8_t        mrId[SL_XSD_MRID_LEN];
  /**
   * Flag indicating that the user was informed if the event was mandatory and
   * has acknowledged that they are opting out of a mandatory event.  This field
   * is not required if the event being opted-out is not mandatory.
   */
  bool        userAck;
} sl_drlc_client_opt_out_edc_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_opt_out_edc_cnf
 * This confirmation indicates the status of the EDC opt-out request.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * status of the request
   */
  sl_cmn_rc_t   status;
} sl_drlc_client_opt_out_edc_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_opt_in_edc_req
 * This request is used by the Customer Application to opt back into an
 * End Device Control (EDC) after it has already been opted-out using
 * \ref SL_DRLC_CLIENT_OPT_OUT_EDC_REQ.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Unique MRID for the EDC to override of length \ref SL_XSD_MRID_LEN.
   */
  u8_t        mrId[SL_XSD_MRID_LEN];
} sl_drlc_client_opt_in_edc_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_opt_in_edc_cnf
 * This confirmation indicates the status of the opt-in request.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * status of the request
   */
  sl_cmn_rc_t   status;
} sl_drlc_client_opt_in_edc_cnf;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_applied_values_req
 * This request is used by the Customer Application to communicate to the Services
 * Layer which of the fields of the EDC have been applied by the device.
 *
 * If the Response Client is enabled and the server indicates that responses are
 * required, then the values in this request will be sent to the server in the
 * DrResponse when the status of the indicated EDC changes.  If this message is
 * not sent to the Services Layer, no applied values will by sent in the DrResponse.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Unique MRID of the EDC associated with the DR response values.
   */
  u8_t                              mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the type of appliance load reduction applied.  A value of
   * \ref SL_XSD_APP_LOAD_RED_NOT_USED indicates that this field has not
   * been applied by device.
   */
  sl_xsd_appliance_load_red_type_t  appliedApplianceLoadRed;
  /**
   * Contains the maximum On state duty cycle applied by the end device, as a
   * percentage of time.
   */
  u8_t                              appliedDutyCycle;
  /**
   * Boolean indicating whether or not the dutyCycle field is present in the
   * request.  The field not present indicates that this field has not been
   * applied by the device.
   */
  bool                              appliedDutyCycleExists;
  /**
   * Contains the cooling offset applied by the device, in degree C / 10.
   */
  u8_t                              appliedCoolOffset;
  /**
   * Boolean indicating whether or not the appliedCoolOffset field is present in
   * the request.  The field not present indicates that this field has not been
   * applied by the device.
   */
  bool                              appliedCoolOffsetExists;

  /**
   * Contains the applied heating offset, in degree C / 10 applied by the device.
   */
  u8_t                              appliedHeatOffset;
  /**
   * Boolean indicating whether or not the appliedHeatOffset field is present in the
   * request.  Field not present indicates that this field has not been applied by
   * the device.
   */
  bool                              appliedHeatOffsetExists;
  /**
   * The applied load adjustment percentage, in tenths of a percent.
   */
  u8_t                              appliedLoadAdjustPercentOffset;
  /**
   * Boolean indicating whether or not the appliedLoadAdjustPercentOffset field is
   * present in the request. Field not present indicates that this field has not
   * been applied by the device.
   */
  bool                              appliedLoadAdjustPercentOffsetExists;
  /**
   * Contains the cooling Temperature Set Point / 100 = temperature in degrees
   * Celsius applied by the device.
   */
  i16_t                             appliedCoolSetpoint;
  /**
   * Boolean indicating whether or not the appliedCoolSetpoint field is present
   * in the request. Field not present indicates that this field has not been
   * applied by the device.
   */
  bool                              appliedCoolSetpointExists;
  /**
   * Contains the heating Temperature Set Point applied by the device.
   */
  i16_t                             appliedHeatSetpoint;
  /**
   * Boolean indicating whether or not the heating appliedHeatSetpoint field is
   * present in the request. Field not present indicates that this field has not
   * been applied by the device.
   */
  bool                              appliedHeatSetpointExists;
  /**
   * Contains the type of target reduction applied.
   */
  sl_xsd_unit_type_t                appliedTargetReductionType;
  /**
   * Contains the applied threshold to which the device will reduce its load.
   */
  u16_t                             appliedTargetReductionValue;
  /**
   * Boolean indicating whether or not the appliedTargetReductionType and
   * appliedTargetReductionValue fields are present in the request.  Field not
   * present indicates that target reduction has not been applied by the device.
   */
  bool                              appliedTargetReductionExists;
} sl_drlc_client_set_applied_values_req;

/******************************************************************************/
/**
 * \struct sl_drlc_client_set_applied_values_cnf
 * This confirmation indicates the status of the request to set the applied EDC
 * values.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Unique MRID of the EDC associated with the DR response values.
   */
  u8_t                              mrId[SL_XSD_MRID_LEN];
  /**
   * status of the request
   */
  sl_cmn_rc_t                       status;
} sl_drlc_client_set_applied_values_cnf;

/** @} */
// end addtogroup DRLC_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup DRLC_GROUP


// -------------------- Device Status ---------

/**
 * \defgroup DSTAT_GROUP EDSTAT/SDSTAT Definitions and Structures
 * \brief This section contains definitions and structures used by the End Device
 *        Device Status (EDSTAT) and Self Device Device Status (SDSTAT) function sets.
 */
/** \addtogroup DSTAT_GROUP
 * @{ */

/**
 * \defgroup DSTAT_GROUP_DEFINES Device Status Defines
 * This section contains defines used by the EDSTAT and SDSTAT function sets.
 */
/** \addtogroup DSTAT_GROUP_DEFINES
 * @{ */

/**
 * The maximum number of temperature readings in the device status resource.
 */
#define SL_DSTAT_MAX_NUM_TEMP                   (5)

/** @} */
// end addtogroup DSTAT_GROUP_DEFINES

/**
 * \defgroup DSTAT_GROUP_STRUCTS Device Status Structures
 * This section contains structures used by the EDSTAT and SDSTAT function sets.
 */
/** \addtogroup DSTAT_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_device_status_t
 *
 * This structure contains all of the information that is part of the SEP2
 * device status resource, used for both EDEV and SDEV device status cases.
 */
typedef struct {
  /**
   * The number of time that the device has been turned on since the last time the
   * counter was reset.
   */
  u16_t              onCount;
  /**
   * Boolean indicating if the onCount field is included.
   */
  bool               onCountExists;
  /**
   * The operational state of the device.
   */
  sl_xsd_op_state_t  opState;
  /**
   * Boolean indicating if the opState field is included.
   */
  bool               opStateExists;
  /**
   * The total accumulated amount of time in seconds that the device has been
   * turned on since the last time the counter was reset.
   */
  u32_t              opTime;
  /**
   * Boolean indicating if the opTime field is included.
   */
  bool               opTimeExists;
  /**
   * The time at which the reported values were recorded.
   */
  sl_xsd_time_type_t changedTime;
  /**
   * The number of temperature measurements.
   */
  u8_t               numTemp;
  /**
   * The temperature of the device.
   */
  sl_xsd_temp_t      temp[SL_DSTAT_MAX_NUM_TEMP];
} sl_device_status_t;

/** @} */
// end addtogroup DSTAT_GROUP_STRUCTS

/**
 * \defgroup DSTAT_GROUP_MAIL_STRUCTS Device Status Mail Structures
 * This section contains mail structures used by the SDSTAT and EDSTAT function sets.
 */
/** \addtogroup DSTAT_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_edstat_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the EDSTAT Client to indicate that a ESTAT server has been found.
 *
 * The client application may use this indication as a trigger to start
 * putting DSTAT information to the server. The included server/source
 * information is used to put a EDSTAT via the \ref sl_edstat_client_send_dstat_req.
 * If \ref sl_edstat_client_send_dstat_req is requested before this indication is
 * sent, the DSTAT client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_edstat_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_edstat_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_edstat_client_send_dstat_req
 * This request is used by the client Customer Application to put a Device Status
 * resource to a EDSTAT Server. Once the request is handled the SL Task responds
 * with a \ref SL_EDSTAT_CLIENT_SEND_DSTAT_CNF.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * The device status information to be sent to the server.
   */
  sl_device_status_t                   dstat;
} sl_edstat_client_send_dstat_req;

/******************************************************************************/
/**
 * \struct sl_edstat_client_send_dstat_cnf
 * This confirmation is sent in response to the \ref SL_EDSTAT_CLIENT_SEND_DSTAT_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Indicates the status of the send power status operation.
   */
  i8_t                                 status;
} sl_edstat_client_send_dstat_cnf;

/** @} */
// end addtogroup DSTAT_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup DSTAT_GROUP


/** \cond NOTRELEASED */

/******************************************************************************/
/**
 * \struct sl_dstat_server_store_sdstat_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new
 * \ref SL_OBJ_ID_X_SDEV_SDSTAT (Self Device - Device Status) resource within the
 * Device Status Server. Once the request is handled the SL Task responds with a
 * \ref SL_SERVER_OBJ_CREATE_CNF with an objID of \ref SL_OBJ_ID_X_SDEV_SDSTAT.
 *
 * The ref field of the sl_dstat_server_store_sdstat_req must be defined as
 * follows:\n
 * ref.objId    = SL_OBJ_ID_X_SDEV_SDSTAT\n
 * ref.numInstanceIDs  = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: none.
 *
 */
typedef struct {
  /**
   * References the SEP object (and action) for delivery of this message.
   */
  sl_server_obj_ref_t    ref;
  sl_device_status_t dstat;
} sl_sdstat_server_store_sdstat_req;

/******************************************************************************/
/**
 * \struct sl_dstat_server_store_sdstat_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_SDEV_SDSTAT (Self Device - Device Status Resource).
 * The confirmation provides a status of the operation and contains the ref
 * structure for the created resource. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_dstat_server_store_sdstat_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_SDSTAT\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_dstat_server_store_sdstat_cnf
 */
typedef sl_server_obj_cnf_t sl_sdstat_server_store_sdstat_cnf;

/** \endcond */


// -------------------- End Device ------------

/**
 * \defgroup EDEV_GROUP EDEV Definitions and Structures
 * This section contains definitions and structures used by the EDEV function set.
 */
/** \addtogroup EDEV_GROUP
 * @{ */

/**
 * \defgroup EDEV_GROUP_DEFINES EDEV Definitions
 * This section contains definitions used by the EDEV function set.
 */
/** \addtogroup EDEV_GROUP_DEFINES
 * @{ */
/**
 * Used by the EDEV Function Set. This defines the maximum number of EDEVs
 * that may be returned in a single mail message.
 */
#define SL_EDEV_CLIENT_MAX_NUM_EDEVS   (5)

/** @} */
// end addtogroup EDEV_GROUP_DEFINES


/**
 * \defgroup EDEV_GROUP_TYPEDEFS EDEV Types
 * This section contains types used by the EDEV function set.
 */
/** \addtogroup EDEV_GROUP_TYPEDEFS
 * @{ */



/******************************************************************************/
/**
 * \defgroup SL_EDEV_CLIENT_SERVER_STATUS_XXX SL EDEV Client Server Status sl_edev_client_server_status_t (SL_EDEV_CLIENT_SERVER_STATUS_XXX)
 * Defines the status of a particular EDEV server. This type provides information
 * on whether or not a particular device is registered on an EDEV server or not.
 * Depending on the server status the Customer Application may choose to perform
 * different actions.
 */
/** \addtogroup SL_EDEV_CLIENT_SERVER_STATUS_XXX
* @{ */
/**
 * \var typedef u8_t sl_edev_client_server_status_t
 * Acceptable values are SL_EDEV_CLIENT_SERVER_STATUS_XXX.
 */
typedef u8_t sl_edev_client_server_status_t;
/**
 * Indicates that there is an EDEV server available but it is not yet known if the
 * device is registered on it (i.e., if there is an EDEV instance for this device
 * on the server).
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_UNKNOWN      (0)
/**
 * Indicates that there is NOT an EDEV instance on the server for this device.
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_UNREGISTERED (1)
/**
 * Indicates that there is an EDEV instance but no registration data on the server
 * for this device.
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_NO_REG_INFO  (2)
/**
 * There is an EDEV instance on the server for this device with registration information.
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_REGISTERED   (3)
/**
 * Indicates that the EDEV instance PIN has been verified for this server and device.
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_VERIFIED     (4)
/**
 * Indicates that verification of PIN for the EDEV instance for this device on this
 * server failed (e.g., due to a PIN mismatch).
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_VER_FAILED   (5)
/**
 * Indicates that SL was unable to determine the registration status of the device
 * for this server.  This may be due to communication errors with the server, or
 * if the client is not authorized to get the registration information.
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_UNDETERMINED (6)
/**
 * Indicates the EDEV has been disabled
 */
#define SL_EDEV_CLIENT_SERVER_STATUS_DISABLED (7)
/** @} */
// end addtogroup SL_EDEV_CLIENT_SERVER_STATUS_XXX

/** @} */
// end addtogroup EDEV_GROUP_TYPEDEFS


/**
 * \defgroup EDEV_GROUP_STRUCTS EDEV Structures
 * This section contains structures used by the EDEV function set.
 */
/** \addtogroup EDEV_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_edev_services_t
 * This structure contains a boolean for each function set or service that is supported
 * by a particular EDEV instance.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether EDEV Config FS is supported for this device.
   */
  bool                    config;
  /**
   * Hash of the Config link HREF
   */
  u32_t                   configHash;
  /**
   * Boolean indicating whether EDEV DER FS is supported for this device.
   */
  bool                    der;
  /**
   * Hash of the DER list link HREF
   */
  u32_t                   derHash;
  /**
   * Boolean indicating whether EDEV Device Info FS is supported for this device.
   */
  bool                    devInfo;
  /**
   * Hash of the Device Info link HREF
   */
  u32_t                   devInfoHash;
  /**
   * Boolean indicating whether EDEV Device Status FS is supported for this device.
   */
  bool                    deviceStatus;
  /**
   * Hash of the Device Status link HREF
   */
  u32_t                   deviceStatusHash;
  /**
   * Boolean indicating whether EDEV File Status FS is supported for this device.
   */
  bool                    fileStatus;
  /**
   * Hash of the File Status link HREF
   */
  u32_t                   fileStatusHash;
  /**
   * Boolean indicating whether EDEV Flow Reservation FS is supported for this device.
   */
  bool                    flowReservationRequest;
  /**
   * Hash of the Flow Reservation Request list link HREF
   */
  u32_t                   flowReservationRequestHash;
  /**
   * Boolean indicating whether EDEV Flow Reservation FS is supported for this device.
   */
  bool                    flowReservationResponse;
  /**
   * Hash of the Flow Reservation Response list link HREF
   */
  u32_t                   flowReservationResponseHash;
  /**
   * Boolean indicating whether EDEV Function Set Assignment FS is supported for this device.
   */
  bool                    funcSetAssign;
  /**
   * Hash of the Function Set Assignment list link HREF
   */
  u32_t                   funcSetAssignHash;
  /**
   * Boolean indicating whether EDEV LSA FS is supported for this device.
   */
  bool                    loadShedAvail;
  /**
   * Hash of the LoadShedAvailability list link HREF
   */
  u32_t                   loadShedAvailHash;
  /**
   * Boolean indicating whether EDEV LEL FS is supported for this device.
   */
  bool                    logEvent;
  /**
   * Hash of the Log Event list link HREF
   */
  u32_t                   logEventHash;
  /**
   * Boolean indicating whether EDEV Network Status is supported for this device.
   */
  bool                    netStatus;
  /**
   * Hash of the Network Status link HREF
   */
  u32_t                   netStatusHash;
  /**
   * Boolean indicating whether EDEV Power Status FS is supported for this device.
   */
  bool                    powerStatus;
  /**
   * Hash of the Power Status link HREF
   */
  u32_t                   powerStatusHash;
  /**
   * Boolean indicating whether EDEV is enabled or registered.
   */
  bool                    enabled;
  /**
   * Boolean indicating whether EDEV enabled exists.
   */
  bool                    enabledExists;
  /**
   * POST rate, or how often EndDevice and subordinate resources should be POSTed, 
   * in seconds. A client MAY indicate a preferred postRate when POSTing EndDevice. 
   * A server MAY add or modify postRate to indicate its preferred posting rate.
   */
  u32_t                   postRate;
  /**
   * Boolean indicating whether postRate exists.
   */
  bool                    postRateExists;
} sl_edev_services_t;

/** @} */
// end addtogroup EDEV_GROUP_STRUCTS


/**
 * \defgroup EDEV_GROUP_MAIL_STRUCTS EDEV Mail Structures
 * This section contains mail structures used by the EDEV function set.
 */
/** \addtogroup EDEV_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_edev_server_create_enddev_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create an end device
 * instance for a particular device (defined by its SFDI) on the SL server.
 * The request include fields to enable various function sets within the
 * EDEV instance (e.g., enableFlowReservation). Note that even if those
 * booleans are set to TRUE in this messages, they will only be supported
 * if those function sets are supported within the SL server. Once the request
 * is handled the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using
 * the structure \ref sl_edev_server_create_enddev_cnf.
 *
 * The ref field of the sl_edev_server_create_enddev_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
*/
typedef struct {

  sl_server_obj_ref_t     ref;
  /**
   * Indicates the groupId for the function set assignment that this device should
   * use, or zero for none. Note that the exact function set assignments are created
   * as part of the \ref sl_fsa_server_create_fsa_req. Please note that while there is
   * no particular order required when creating an EDEV and an associated FSA, the
   * Customer Application should choose a groupId that will be used for both
   * (funcSetAssignGroupId maps to \ref sl_server_obj_ref_t::instanceIDs[0] in the
   * \ref sl_fsa_server_create_fsa_req::ref).
   * Note: In order for an FSA with this groupId to be included in the EDEV,
   * \ref sl_edev_services_t::funcSetAssign must be set to true.
   */
  u16_t                   funcSetAssignGroupId;
  /**
   * This field is for use in devices that can adjust energy usage (e.g., demand response, 
   * distributed energy resources).  For devices that do not respond to EndDeviceControls 
   * or DERControls (for instance, an ESI), this field should not have any bits set.
   */
  sl_xsd_dev_cat_bitmap_t deviceCategory;
  /**
   * Boolean indicating whether the deviceCategory field is included for this EDEV or not.
   */
  bool                    deviceCategoryExists;
  /**
   * 6-digit PIN associated with the EDEV instance.
   */
  u32_t                   pin;
  /**
   * Boolean field indicating whether registration is supported for this EDEV instance.
   * If true, the PIN is used.
   */
  bool                    regExists;
  /**
   * This structure indicates which services should be available for this EDEV instance.
   * Note that even if a boolean within the structure is set to TRUE, that service
   * will only be available if the server supports it.
   */
  sl_edev_services_t      services;
  /*  replaced by lfdi
   u64_t                   sfdi;
   */
  /**
   * LFDI of the EDEV instance that is being created.
   */
  u8_t                    lfdi[SL_XSD_LFDI_LEN];
} sl_edev_server_create_enddev_req;

/******************************************************************************/
/**
 * \struct sl_edev_server_create_enddev_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_EDEV_X (End Device or EDEV).
 * The confirmation provides a status of the operation
 * and contains the ref structure for the created EDEV.
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_edev_server_create_enddev_cnf;
 */
typedef sl_server_obj_cnf_t sl_edev_server_create_enddev_cnf;

/******************************************************************************/
/**
 * \struct sl_edev_server_store_enddev_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to update an end device
 * instance for a particular device on the SL server.
 * The request include fields to enable various function sets within the
 * EDEV instance (e.g., enableFlowReservation). Note that even if those
 * booleans are set to TRUE in this messages, they will only be supported
 * if those function sets are supported within the SL server. Once the request
 * is handled the SL Task responds with a \ref SL_SERVER_OBJ_STORE_CNF using
 * the structure \ref sl_edev_server_store_enddev_cnf.
 *
 * The ref field of the sl_edev_server_store_enddev_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV\n
 *
 * Dependencies: None.
*/
typedef struct {

  sl_server_obj_ref_t     ref;
  /**
   * Indicates the groupId for the function set assignment that this device should
   * use, or zero for none. Note that the exact function set assignments are created
   * as part of the \ref sl_fsa_server_create_fsa_req. Please note that while there is
   * no particular order required when creating an EDEV and an associated FSA, the
   * Customer Application should choose a groupId that will be used for both
   * (funcSetAssignGroupId maps to \ref sl_server_obj_ref_t::instanceIDs[0] in the
   * \ref sl_fsa_server_create_fsa_req::ref).
   * Note: In order for an FSA with this groupId to be included in the EDEV,
   * \ref sl_edev_services_t::funcSetAssign must be set to true.
   */
  u16_t                   funcSetAssignGroupId;
  /**
   * This field is for use in devices that can adjust energy usage (e.g., demand response,
   * distributed energy resources).  For devices that do not respond to EndDeviceControls
   * or DERControls (for instance, an ESI), this field should not have any bits set.
   */
  sl_xsd_dev_cat_bitmap_t deviceCategory;
  /**
   * Boolean indicating whether the deviceCategory field is included for this EDEV or not.
   */
  bool                    deviceCategoryExists;
  /**
   * 6-digit PIN associated with the EDEV instance.
   */
  u32_t                   pin;
  /**
   * Boolean field indicating whether registration is supported for this EDEV instance.
   * If true, the PIN is used.
   */
  bool                    regExists;
  /**
   * This structure indicates which services should be available for this EDEV instance.
   * Note that even if a boolean within the structure is set to TRUE, that service
   * will only be available if the server supports it.
   */
  sl_edev_services_t      services;
} sl_edev_server_store_enddev_req;

/******************************************************************************/
/**

 * \struct sl_edev_server_store_enddev_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to store a \ref SL_OBJ_ID_X_EDEV_X (End Device instance or
 * EDEV). The confirmation provides a status of the operation and contains
 * the ref structure for the stored EDEV. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_edev_serverstore_enddev_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X\n
 * ref.numInstanceIDs = 2\n

 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_edev_server_store_enddev_cnf
*/
typedef sl_server_obj_cnf_t sl_edev_server_store_enddev_cnf;

/******************************************************************************/
/**
 * \struct sl_edev_server_delete_enddev_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete an End Device
 * instance (EDEV) within the EDEV Server. It will also cause all child
 * resources to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_edev_server_delete_enddev_cnf.
 *
 * The ref field of the sl_edev_server_delete_enddev_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV\n
 *
 * Dependencies: The \ref sl_edev_server_delete_enddev_req may only be sent after an
 * \ref sl_edev_server_create_enddev_req for that resource has been sent and handled
 * successfully OR after a client has posted an EDEV and it has been successfully created.
 *
 * typedef sl_server_obj_ref_t sl_edev_server_delete_enddev_req
*/
typedef sl_server_obj_ref_t sl_edev_server_delete_enddev_req;

/******************************************************************************/
/**
 * \struct sl_edev_server_delete_enddev_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_EDEV_X (End Device instance or
 * EDEV). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted EDEV. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_edev_server_delete_enddev_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_edev_server_delete_enddev_cnf
*/
typedef sl_server_obj_cnf_t sl_edev_server_delete_enddev_cnf;

/******************************************************************************/
/**
 * \struct sl_edev_server_post_edev_pending_ind
 * This message is used to indicate to the Customer Application that a client device
 * is attempting to post an EDEV instance to the server.  The Customer Application
 * MUST respond to this indication with a \ref SL_EDEV_SERVER_POST_EDEV_PENDING_RSP
 * indicating whether or not to accept the post.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the subsequent response message with this
   * indication message.
   */
  u32_t         transactionId;
  /**
   * SFDI of the client device attempting to post to the end device list.
   */
  u64_t         sfdi;
  /**
   * Boolean indicating whether the lfdi field is included for this EDEV or not.
   */
  bool          lfdiExists;
  /**
   * LFDI of the client device attempting to post to the end device list.
   */
  u8_t          lfdi[SL_XSD_LFDI_LEN];
} sl_edev_server_post_edev_pending_ind;

/******************************************************************************/
/**
 * \struct sl_edev_server_post_edev_pending_rsp
 * This response is sent by the Customer Application in response to receiving
 * a \ref SL_EDEV_SERVER_POST_EDEV_PENDING_IND.  This message indicates to the
 * Services Layer whether or not to accept the client POST.
 *
 * Dependencies: The Customer Application must only send this message in response
 * to receiving a \ref SL_EDEV_SERVER_POST_EDEV_PENDING_IND.
 */
typedef struct {
  /**
   * transactionId is used to match the original indication message with this
   * response message.  The application MUST populate the \ref transactionId
   * field with the transactionId value received in the associated
   * \ref SL_EDEV_SERVER_POST_EDEV_PENDING_IND.
   */
  u32_t         transactionId;
  /**
   * Flag indicating if the Services Layer should accept the client post to the
   * end device list.  If \ref accept is set to true the Service Layer will accept
   * the post.
   */
  bool          accept;
} sl_edev_server_post_edev_pending_rsp;

/******************************************************************************/
/**
 * \struct sl_edev_server_post_edev_ind
 * This message is used to indicate to the Customer Application that an end device
 * instance was successfully created from a client POST.
 *
 * Dependencies: The Services Layer will only create an end device from a client
 * POST request if a \ref SL_EDEV_SERVER_POST_EDEV_PENDING_RSP is received from
 * the Customer Application which informs the Services Layer to accept the client POST.
 */
typedef struct {
  /**
   * Unique instance ID associated with this EDEV within the default group.
   */
  u16_t         edevId;
  /**
   * SFDI of the created end device.
   */
  u64_t         sfdi;
  /**
   * Boolean indicating whether the lfdi field is included for this EDEV or not.
   */
  bool          lfdiExists;
  /**
   * LFDI of the client device attempting to post to the end device list.
   */
  u8_t          lfdi[SL_XSD_LFDI_LEN];
} sl_edev_server_post_edev_ind;

/******************************************************************************/
/**
 * \struct sl_edev_client_set_pin_req
 * This request is used by the Customer Application to set the EDEV PIN within
 * the SL Client.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * 6-digit PIN to be associated with this device.
   */
  u32_t          pin;
} sl_edev_client_set_pin_req;

/******************************************************************************/
/**
 * \struct sl_edev_client_set_pin_cnf
 * This confirmation indicates the status of setting the PIN for the device.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the status of the set PIN operation.
   */
  sl_cmn_rc_t   status;
} sl_edev_client_set_pin_cnf;

/******************************************************************************/
/**
 * \struct sl_edev_client_send_enddev_req
 * This request is used by the Customer Application send an EDEV instance to
 * the SL server.  The successful confirmation from the server will result in
 * a SL_EDEV_CLIENT_SEND_ENDDEV_CNF message.
 *
 * The Services Layer will POST the End Device resource to the End Device list
 * if one does not already exist for the device on the server, else the Services
 * Layer will PUT the resource.
 *
 * Dependencies: The Client must get the SL_EDEV_CLIENT_SERVER_FOUND_IND from
 * the Services Layer prior to sending this request.  The
 * \ref sl_edev_client_server_found_ind::serverStatus field indicates whether an
 * EndDevice instance for the client was found on the server.
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirm message with the original
   * request message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information indicating where to post the edev
   * point. This set of available servers/sources is provided by the SEP Client
   * in the \ref sl_edev_client_server_found_ind::serverDetails.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
} sl_edev_client_send_enddev_req;

/******************************************************************************/
/**
 * \struct sl_edev_client_send_enddev_cnf
 * This confirmation indicates whether an EDEV instance for this device was
 * successfully posted to the server or not.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Indicates the status of the POST EDEV operation.
   */
  sl_cmn_rc_t                          status;
} sl_edev_client_send_enddev_cnf;

/******************************************************************************/
/**
 * \struct sl_edev_client_find_server_req
 * This request is used by the Customer Application to trigger the SL task to
 * look for an EDEV server which has an EDEV instance for this device.
 *
 * Dependencies: None.
 */
//typedef struct {
//   // empty?
//} sl_edev_client_find_server_req;

/******************************************************************************/
/**
 * \struct sl_edev_client_find_server_cnf
 * This confirmation is used to indicate whether the \ref SL_EDEV_CLIENT_FIND_SERVER_REQ
 * will be handled or not. Actual server information will be provided in the
 * SL_EDEV_CLIENT_SERVER_FOUND_IND.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates whether the request will be handled or not. Actual server information
   * will be provided in the \ref SL_EDEV_CLIENT_SERVER_FOUND_IND.
   */
  sl_cmn_rc_t                    status;
} sl_edev_client_find_server_cnf;

/******************************************************************************/
/**
 * \struct sl_edev_client_server_found_ind
 * This indication is used to indicate to the Customer Application that
 * an EDEV server for this device was found.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the status of the EDEV server that has been found (i.e., whether
   * an EDEV instance for this device exists, whether there is registration information,
   * and whether that registration information has been verified or not).
   */
  sl_edev_client_server_status_t   serverStatus;
  /**
   * This structure indicates which services are available as part of this EDEV instance.
   */
  sl_edev_services_t               services;
  /**
   * This structure contains the detailed information regarding the server.
   */
  sl_cmn_client_server_ind_t       serverDetails;

} sl_edev_client_server_found_ind;

/******************************************************************************/
/**
 * \struct sl_edev_client_get_edev_list_req
 * This request is used by the Customer Application to request some number
 * of EDEVs. The \ref SL_EDEV_CLIENT_GET_EDEV_LIST_CNF will be sent as an
 * acknowledgment of the request, and the EDEVs themselves will be sent in
 * the \ref SL_EDEV_CLIENT_EDEV_LIST_IND message. While the application may request as
 * many EDEVs as it wants up to 254 (255 is defined as requesting all available EDEVs)
 * only up to \ref SL_EDEV_CLIENT_MAX_NUM_EDEVS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_EDEV_CLIENT_GET_EDEV_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The APP client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_EDEV_CLIENT_SERVER_FOUND_IND must be received by the client
 * app before this request will be handled by the EDEV client. An error will be
 * returned if there is no EDEV server.
 *
 * typedef sl_cmn_get_list_req_root_t sl_edev_client_get_edev_list_req
 */
typedef sl_cmn_get_list_req_root_t sl_edev_client_get_edev_list_req;

/******************************************************************************/
/**
 * \struct sl_edev_client_get_edev_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_EDEV_CLIENT_GET_EDEV_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_edev_client_get_edev_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_edev_client_get_edev_list_cnf;

/******************************************************************************/
/**
 * \struct sl_edev_client_cancel_get_edev_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for EDEVs. Note that until the \ref SL_EDEV_CLIENT_CANCEL_GET_EDEV_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_EDEV_CLIENT_SERVER_FOUND_IND must be received by the client
 * app before this request will be handled by the EDEV client.
*/
typedef struct {
  /**
   * transactionId is used to match the cancel request with the original
   * request.
   */
  u32_t       transactionId;
} sl_edev_client_cancel_get_edev_list_req;

/******************************************************************************/
/**
 * \struct sl_edev_client_cancel_get_edev_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated DRP processing has been stopped.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * transactionId is used to match the cancel confirmation with the original
   * request.
   */
  u32_t       transactionId;
} sl_edev_client_cancel_get_edev_list_cnf;

/******************************************************************************/
/**
 * \struct sl_registration_t
 * This indication contains the EDEV information for a particular EDEV instance.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * 6-digit PIN associated with the EDEV instance, including the checksum digit.
   */
  u32_t                   pin;
  /**
   * The time the registration was created.
   */
  sl_xsd_time_type_t      timeRegistered;
} sl_registration_t;

/******************************************************************************/
/**
 * \struct sl_edev_client_edev_t
 * This indication contains the EDEV information for a particular EDEV instance.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * This field is for use in devices that can adjust energy usage (e.g., demand response,
   * distributed energy resources).  For devices that do not respond to EndDeviceControls
   * or DERControls (for instance, an ESI), this field should not have any bits set.
   */
  sl_xsd_dev_cat_bitmap_t deviceCategory;
  /**
   * Boolean indicating whether the deviceCategory field is included for this EDEV or not.
   */
  bool                    deviceCategoryExists;
  /**
   * This structure indicates which services are available as part of this EDEV instance.
   */
  sl_edev_services_t      services;
  /**
   * SFDI of this EDEV instance.
   */
  u64_t                   sfdi;
  /**
   * Flag indicating whether Registration information is included with the EDEV.
   */
  bool                    registrationExists;
  /**
   * Optional Registration associated with the EDEV.
   */
  sl_registration_t       registration;
} sl_edev_client_edev_t;

/******************************************************************************/
/**
 * \struct sl_edev_client_edev_list_ind
 * This indication is sent in response to the \ref SL_EDEV_CLIENT_GET_EDEV_LIST_REQ.
 * It will contain some number of EDEVs up to \ref SL_EDEV_CLIENT_MAX_NUM_EDEVS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available EDEVS have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t          results;
  /**
   * List of EDEVs.
   */
  sl_edev_client_edev_t list[];  // Variable length up to SL_EDEV_CLIENT_MAX_NUM_EDEVS
} sl_edev_client_edev_list_ind;

/** @} */
// end addtogroup EDEV_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup EDEV_GROUP


/** \cond NOTRELEASED */

// --------------------- EPS --------------------


// -------------------- EFILE -------------------

#define SL_XSD_EFILE_FILENAME_LEN               64

#define SL_XSD_EFILE_STATUS_NO_LOAD_IN_PROGRESS 0
#define SL_XSD_EFILE_STATUS_LOAD_IN_PROGESS     1
#define SL_XSD_EFILE_STATUS_LOAD_FAILED         2
#define SL_XSD_EFILE_STATUS_VERIFY_IN_PROGRESS  3
#define SL_XSD_EFILE_STATUS_VERIFY_FAILED       4
#define SL_XSD_EFILE_STATUS_VERIFIED            5
#define SL_XSD_EFILE_STATUS_ACTIVATION_FAILED   6

typedef struct
{
  char        filename[SL_XSD_EFILE_FILENAME_LEN];
  sl_xsd_time_type_t statusTime;
  u8_t        status;
} sl_efile_filestat_t;

/******************************************************************************/
/**
 * \struct sl_efile_client_send_filestat_req
 * This request is used by the client Customer Application to put a File Status
 * resource to the client End Device (EDEV) on the File Server. Once the request
 * is handled the SL Task responds with a \ref SL_EFILE_CLIENT_SEND_FILESTAT_CNF.
 *
 * Dependencies: None.
 */
typedef sl_efile_filestat_t sl_efile_client_send_filestat_req;

/******************************************************************************/
/**
 * \struct sl_efile_client_send_filestat_cnf
 * This confirmation is sent in response to the \ref SL_EFILE_CLIENT_SEND_FILESTAT_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef sl_result_t sl_efile_client_send_filestat_cnf;

// -------------------- FILE -------------------

#define SL_XSD_FILE_MFVER_LEN       16
#define SL_XSD_FILE_FILENAME_LEN    64

#define SL_XSD_FILE_TYPE_SW_IMAGE   0
#define SL_XSD_FILE_TYPE_SEC_CRED   1
#define SL_XSD_FILE_TYPE_CONFIG     2
#define SL_XSD_FILE_TYPE_LOG        3
#define SL_XSD_FILE_TYPE_START_SEP2_RESERVED 4
#define SL_XSD_FILE_TYPE_START_MF_DEFINED    0x8000

typedef struct
{
  sl_xsd_time_type_t  activateTime;
   char        filename[SL_XSD_FILE_FILENAME_LEN];
   u8_t        lFDI[SL_XSD_LFDI_LEN];
   char        manufacturerHWVersion[SL_XSD_DESCRIPTION_LEN];
   u32_t       manufacturerID;
   char        manufacturerModel[SL_XSD_DESCRIPTION_LEN];
   char        manufacturerSerialNum[SL_XSD_DESCRIPTION_LEN];
   char        manufacturerVersion[SL_XSD_FILE_MFVER_LEN];
   u32_t       size;
   u16_t       type;
   bool        activateTimeExists;
   bool        lFDIExists;
   bool        manufacturerHWVersionExists;
   bool        manufacturerSerialNumExists;
} sl_file_fileinfo_t;

/******************************************************************************/
/**
 * \struct sl_file_client_file_ind
 * This indication is sent to the Customer Client application from the File
 * client to indicate that a new data File has been received. This is an unsolicited
 * message sent directly to the Application Task.
 *
 * Note that the filename provided to the Customer Application in this indication
 * must be the same filename used when sending status updates in the
 * \ref SL_SFILE_SERVER_STORE_FILESTAT_REQ and the \ref SL_EFILE_CLIENT_SEND_FILESTAT_REQ.
 * Once received, the file is owned by the Customer Application and the Customer
 * Application may use it as needed; including moving, renaming, or deleting the file.
 *
 * Dependencies: None.
*/
typedef sl_file_fileinfo_t sl_file_client_file_ind;

/******************************************************************************/
/**
 * \struct sl_file_server_create_file_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new
 * \ref SL_OBJ_ID_X_FILE_X (File information resource) resource within the
 * File Server. Once the request is handled the SL Task responds with a
 * \ref SL_SERVER_OBJ_CREATE_CNF with an objID of \ref SL_OBJ_ID_X_FILE_X.
 *
 * The ref field of the sl_file_server_create_file_req must be defined as
 * follows:\n
 * ref.objId    = SL_OBJ_ID_X_FILE_X\n
 * ref.numInstanceIDs  = 1\n
 * ref.instanceIDs[0] = group ID or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: none.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  sl_file_fileinfo_t     finfo;
} sl_file_server_create_file_req;

/******************************************************************************/
/**
 * \struct sl_file_server_create_file_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ
 * mail message to create a \ref SL_OBJ_ID_X_FILE_X (File information
 * resource). The confirmation provides a status of the operation and contains
 * the ref structure of the created resource. It uses the generic cancel confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_file_server_create_file_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId    = \ref SL_OBJ_ID_X_FILE_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = group ID or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the FILE resource\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_file_server_create_file_cnf
 */
typedef sl_server_obj_cnf_t sl_file_server_create_file_cnf;

/******************************************************************************/
/**
 * \struct sl_file_server_set_act_time_req
 *
 * This request is used by the Customer Application to create set the activation
 * time in an existing File information resource. Once the request is handled
 * the SL Task responds with a \ref SL_FILE_SERVER_SET_ACT_TIME_CNF.
 *
 * Note that this command will fail if the activation time has already been set.
 *
 * Dependencies: None.
 */
typedef struct{
  sl_xsd_time_type_t activationTime;
  u16_t       id;
} sl_file_server_set_act_time_req;

/******************************************************************************/
/**
 * \struct sl_file_server_set_act_time_cnf
 * This confirmation is sent in response to the \ref SL_FILE_SERVER_SET_ACT_TIME_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef sl_result_t sl_file_server_set_act_time_cnf;

/******************************************************************************/
/**
 * \struct sl_file_server_delete_file_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This request is used by the Customer Application to delete a
 * \ref SL_OBJ_ID_X_FILE_X (File information resource) resource within the
 * File Server. Once the request is handled the SL Task responds with a
 * \ref SL_SERVER_OBJ_DELETE_CNF using the structure \ref sl_file_server_delete_file_cnf.
 *
 * The ref field of the sl_file_server_delete_file_req must be defined as
 * follows:\n
 * ref.objId    = SL_OBJ_ID_X_FILE_X\n
 * ref.numInstanceIDs  = 2\n
 * ref.instanceIDs[0] = group ID or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the FILE resource\n
 *
 * Dependencies: none.
 *
 * typedef sl_server_obj_ref_t sl_file_server_delete_file_req
 */
typedef sl_server_obj_ref_t sl_file_server_delete_file_req;

/******************************************************************************/
/**
 * \struct sl_file_server_delete_file_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_FILE_X resource.
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted file resource. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_file_server_delete_file_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_FILE_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the FILE resource\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_file_server_delete_file_cnf
*/
typedef sl_server_obj_cnf_t sl_file_server_delete_file_cnf;

/** \endcond */

// -------------------- Flow Reservation -------

/**
 * \defgroup FLOW_GROUP Flow Reservation Definitions and Structures
 * \brief This section contains definitions and structures used by the FLOW function set.
 */
/** \addtogroup FLOW_GROUP
 * @{ */

/**
 * \defgroup FLOW_GROUP_DEFINES Flow Definitions
 * This section contains definitions used by the Flow function set.
 */
/** \addtogroup FLOW_GROUP_DEFINES
 * @{ */


/**
 * Used by the Flow Function Set. This defines the maximum number of overlapped
 * Flow Reservation Responses(FRP) that may be returned in a single mail message.
 */
#define SL_FLOW_SERVER_MAX_FRP_OVERLAP 5

/**
 * Used by the Flow Reservation Function Set. This defines the maximum number of
 * flow reservation responses that may be returned in a single mail message.
 */
#define SL_FLOW_CLIENT_MAX_NUM_FRPS   (5)

/**
 * This defines the default polling rate for Flow Reservation Response events in
 * seconds.  This value is used with event handling only.
 */
#define SL_FLOW_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC  (5*60)

/** @} */
// end addtogroup FLOW_GROUP_DEFINES

/**
 * \defgroup FLOW_GROUP_STRUCTS Flow Structures
 * This section contains structures used by the Flow function set.
 */
/** \addtogroup FLOW_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_flow_req_t
 * Contains information on the time window and charge requested by the client.
 * This structure is used in the \ref sl_flow_server_req_info_t and
 * \ref sl_flow_client_create_res_request_req structures.
 */
typedef struct {
  /**
   * Ascii description of the client reservation request with max length of
   * SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                         description[SL_XSD_DESCRIPTION_LEN];
  /**
   * The amount of energy required to be transferred into the storage device
   * device from the electric power system.  The units are provided in the
   * energyReqValue field.
   */
  sl_xsd_signed_real_energy_t  energyReq;
  /**
   * The estimated duration (in seconds) that it will take to complete the flow
   * transaction, including ramp time.
   */
  u32_t                        flowDurationReq;
  /**
   * Flag to indicate if the flowDurationReq field is provided.
   */
  bool                         flowDurationReqExists;
  /**
   * Array of length SL_XSD_MRID_LEN containing the MRID of the FRQ.
   */
  u8_t                         mrId[SL_XSD_MRID_LEN];
  /**
   * The amount of power required.
   */
  sl_xsd_active_power_t        powerReq;
  /**
   * The duration of the window or range of time the storage device would like to
   * charge.  The specified window end time (windowStart+windowDuration)
   * indicates the time at which charging must be completed.
   */
  u32_t                        windowDuration;
  /**
   * The start of the window or range of time the storage device would like to
   * charge.
   */
  sl_xsd_time_type_t           windowStart;
} sl_flow_req_t;

/******************************************************************************/
/**
 * \struct sl_flow_resp_t
 * Contains information on the interval and charge granted to a client.  This
 * structure is used in the \ref sl_flow_server_resp_info_t,
 * \ref sl_flow_server_create_res_resp_req, and \ref sl_flow_client_res_resp_ind
 * structures.
 */
typedef struct {
  /**
   * The amount of energy available to be transferred into the storage device.
   */
  sl_xsd_signed_real_energy_t   energyAvail;
  /**
   * Contains details for this randomizable event such as start, duration,
   * response required, etc.
   */
  sl_cmn_event_t                event;
  /**
   * The amount of power available to the storage device.
   */
  sl_xsd_active_power_t         powerAvail;
  /**
   * Ascii description of the reason for the server reservation response with
   * max length of \ref SL_XSD_REASON_LEN. Character string must be null terminated.
   */
  char                          reason[SL_XSD_REASON_LEN];
  /**
   * Array of length SL_XSD_MRID_LEN containing the MRID of the FRQ associated
   * with the FRP.
   */
  u8_t                          requestMrId[SL_XSD_MRID_LEN];
} sl_flow_resp_t;

/******************************************************************************/
/**
 * \struct sl_flow_client_resp_active_info_t
 * This structure contains information about a Response which is being acted
 * upon by the FLOW client. This structure will only be valid if active
 * event handling is enabled.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the current client status of the Response.
   */
  sl_xsd_resp_status_type_t eventRespStatus;
} sl_flow_client_resp_active_info_t;


/******************************************************************************/
/**
 * \struct sl_flow_client_list_res_resp_t
 * This structure contains information about a Resp which is passed as part
 * of the list handling interface \ref sl_flow_client_res_resp_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the FRP (i.e.,
   * information calculated or maintained by the Flow Client as part of active
   * handling).
   */
  sl_flow_client_resp_active_info_t activeInfo;
  /**
   * Boolean indicating whether the activeInfo structure contains valid information.
   * In the case that active handling is disabled, this field will always be set to
   * FALSE. In the case that active handling is enabled, this field may or may not
   * be present depending on whether the Flow Client is acting on it.
   */
  bool                             activeInfoExists;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Structure containing Response data and event information.
   */
  sl_flow_resp_t                   resp;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_flow_client_list_res_resp_t;

/******************************************************************************/
/**
 * \struct sl_flow_server_req_info_t
 * Contains information on a client Flow Reservation Request(FRQ) received by
 * the server.  This structures is used in the \ref sl_flow_server_new_res_request_ind
 * and \ref sl_flow_server_cancel_res_request_ind structures.
 */
typedef struct {
  /**
   * The unique ID for the FRQ.
   */
  u16_t                      frqId;
  /**
   * The time the FRQ was created.
   */
  sl_xsd_time_type_t         creationTime;
  /**
   * Information on the time window and charge requested by the client.
   */
  sl_flow_req_t              request;
  /**
   * The status of the FRQ.
   */
  sl_xsd_req_status_type_t   requestStatus;
  /**
   * The time the currentStatus was updated.
   */
  sl_xsd_time_type_t         statusTime;
} sl_flow_server_req_info_t;

/******************************************************************************/
/**
 * \struct sl_flow_server_resp_info_t
 * Contains information on a server Flow Reservation Response (FRP).  This
 * structure is used in the \ref sl_flow_server_new_res_request_ind and
 * \ref sl_flow_server_cancel_res_request_ind structures.
 */
typedef struct {
  /**
   * The unique ID for the client FRP.
   */
  u16_t               frpId;
  /**
   * Information on the interval and charge in the FRP.
   */
  sl_flow_resp_t      response;
} sl_flow_server_resp_info_t;

/** @} */
// end addtogroup FLOW_GROUP_STRUCTS

/**
 * \defgroup FLOW_GROUP_MAIL_STRUCTS Flow Mail Structures
 * This section contains mail structures used by the FLOW function set.
 */
/** \addtogroup FLOW_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_flow_server_create_res_resp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Flow Reservation
 * Response (FRP) within the Flow Server.  This request will trigger the Flow Server
 * to create the FRP and to start the associated timer and other handling for the
 * FRP.  One the request is handled the SL Task responds with a
 * \ref SL_SERVER_OBJ_CREATE_CNF using the \ref sl_flow_server_create_res_resp_cnf structure.
 *
 * The ref field of the sl_flow_server_create_res_resp_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV that is associated with this
 *                      FRP. This ID is returned by the SL Task in the
 *                      \ref sl_edev_server_create_enddev_cnf.\n
 *
 * Dependencies: A \ref SL_OBJ_ID_X_EDEV_X_FRP_X may only be created after the
 *               parent End Device has been successfully created.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t      ref;
  /**
   * If TRUE, indicates to the SL server that the creation time
   * included in the FRP should be used to specify the resource creation time. If
   * FALSE, indicates to the SL server to use the current time
   * as the creation time.
   */
  bool                     creationTimeExists;
  /**
   * Structure containing the details of the Reservation Response, including event specific details
   * such as start and duration.
   */
  sl_flow_resp_t           response;
  /**
   * Indicates which response set group should be used for client responses to this event.
   */
  sl_obj_instance_id_t     respSetGroupId;
  /**
   * Indicates which response set should be used for client responses to this event.
   */
  sl_obj_instance_id_t     respSetId;
} sl_flow_server_create_res_resp_req;

/******************************************************************************/
/**
 * \struct sl_flow_server_create_res_resp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ
 * mail message to create a \ref SL_OBJ_ID_X_EDEV_X_FRP_X (Flow Reservation
 * Response). The confirmation provides a status of the operation and contains
 * the ref structure of the created FRP. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_flow_server_create_res_resp_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId    = \ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV that is associated with this FRP\n
 * ref.instanceIDs[2] = The unique ID for this FRP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_flow_server_create_res_resp_cnf
 */
typedef sl_server_obj_cnf_t sl_flow_server_create_res_resp_cnf;

/******************************************************************************/
/**
 * \struct sl_flow_server_cancel_res_resp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_REQ mail message.
 *
 * This structure is used by the Customer Application to cancel an existing Flow
 * Reservation Response (FRP) resource within the Flow Server.  Once the request is
 * handled the SL Task responds with a \ref SL_SERVER_OBJ_CANCEL_CNF using the
 * structure \ref sl_flow_server_cancel_res_resp_cnf.
 *
 * The ref field of the sl_flow_server_cancel_res_resp_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV that is associated with this FRP\n
 * ref.instanceIDs[2] = The unique ID for this FRP\n
 *
 * Dependencies: A \ref SL_OBJ_ID_X_EDEV_X_FRP_X may only be canceled after it has been
 *               successfully created.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t        ref;
  /**
   * Ascii description of the reason for canceling the FRP with max length of
   * \ref SL_XSD_REASON_LEN. Character string must be null terminated.
   */
  char                       reason[SL_XSD_REASON_LEN];
} sl_flow_server_cancel_res_resp_req;

/******************************************************************************/
/**
 * \struct sl_flow_server_cancel_res_resp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CANCEL_REQ to
 * cancel a \ref SL_OBJ_ID_X_EDEV_X_FRP_X (Flow Reservation Response). The
 * confirmation provides a status of the operation and contains the ref
 * structure of the canceled FRP. It uses the generic cancel confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_flow_server_cancel_res_resp_cnf will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV that is associated with this FRP\n
 * ref.instanceIDs[2] = The unique ID for this FRP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_flow_server_cancel_res_resp_cnf
 */
typedef sl_server_obj_cnf_t sl_flow_server_cancel_res_resp_cnf;

/******************************************************************************/
/**
 * \struct sl_flow_server_delete_res_req_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Flow Reservation
 * Request (FRQ) within the FLOW Server.  Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_flow_server_delete_res_req_cnf.
 *
 * The ref field of the sl_flow_server_delete_res_req_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_FRQ_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent EDEV\n
 * ref.instanceIDs[2] = The unique ID for the FRQ\n
 *
 * typedef sl_server_obj_cnf_t sl_flow_server_delete_res_req_req
*/
typedef sl_server_obj_ref_t sl_flow_server_delete_res_req_req;

/******************************************************************************/
/**
 * \struct sl_flow_server_delete_res_req_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_EDEV_X_FRQ_X (Flow Reservation Request or
 * FRQ). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted FRQ. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the SL_OBJ_ID_X_EDEV_X_FRQ_X will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_FRQ_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV\n
 * ref.instanceIDs[2] = The unique ID for the FRQ\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_flow_server_delete_res_req_cnf
*/
typedef sl_server_obj_cnf_t sl_flow_server_delete_res_req_cnf;


/******************************************************************************/
/**
 * \struct sl_flow_server_delete_res_resp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Flow Reservation
 * Response (FRP) within the FLOW Server.  Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_flow_server_delete_res_resp_cnf.
 *
 * The ref field of the sl_flow_server_delete_res_resp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent EDEV\n
 * ref.instanceIDs[2] = The unique ID for the FRP\n
 *
 * Dependencies: The \ref sl_flow_server_delete_res_resp_req may only be sent after an
 * \ref sl_flow_server_create_res_resp_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_flow_server_delete_res_resp_req
*/
typedef sl_server_obj_ref_t sl_flow_server_delete_res_resp_req;

/******************************************************************************/
/**
 * \struct sl_flow_server_delete_res_resp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_EDEV_X_FRP_X (Flow Reservation Response or
 * FRP). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted FRP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the SL_OBJ_ID_X_EDEV_X_FRP_X will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_FRP_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the EDEV\n
 * ref.instanceIDs[2] = The unique ID for the FRP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_flow_server_delete_res_resp_cnf
*/
typedef sl_server_obj_cnf_t sl_flow_server_delete_res_resp_cnf;

/******************************************************************************/
/**
 * \struct sl_flow_server_event_status_ind
 * This indication is sent to the Customer Server application from the Flow
 * server to indicate a change in the event status of objects of type
 * \ref SL_OBJ_ID_X_EDEV_X_FRP_X. It will also provide an indication of
 * when an object of type \ref SL_OBJ_ID_X_EDEV_X_FRQ_X completes (after the full
 * requested duration expires and the FRQ is deleted from the server). This is an
 * unsolicited message sent directly to the Application Task. It uses the generic
 * event status indication structure \ref sl_server_obj_event_status_ind_t.
 *
 * The ref field of the sl_flow_server_res_resp_ind will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_EDEV_X_FRP_X or \ref SL_OBJ_ID_X_EDEV_X_FRQ_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent EDEV\n
 * ref.instanceIDs[2] = The unique ID for the FRP or FRQ\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_event_status_ind_t sl_flow_server_event_status_ind
*/
typedef sl_server_obj_event_status_ind_t sl_flow_server_event_status_ind;

/******************************************************************************/
/**
 * \struct sl_flow_server_new_res_request_ind
 * This indication is sent to indicate that a new client reservation request
 * (FRQ) has been received. This is an unsolicited message sent directly to the
 * Application Task.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * The unique ID for the EDEV that this FRQ is associated with.
   */
  u16_t                      edevId;
  /**
   * Number of overlapping responses included in the resp array.
   */
  u8_t                       numOverlapResp;
  /**
   * Information on a client FRQ received by the server.
   */
  sl_flow_server_req_info_t  req;
  /**
   * Array of size \ref SL_FLOW_SERVER_MAX_FRP_OVERLAP containing the list of FRPs
   * that overlap the time window (windowStart, windowDuration) of the new FRQ.
   */
  sl_flow_server_resp_info_t resp[SL_FLOW_SERVER_MAX_FRP_OVERLAP];
} sl_flow_server_new_res_request_ind;

/******************************************************************************/
/**
 * \struct sl_flow_server_cancel_res_request_ind
 * This indication is sent to indicate that a cancel reservation request (FRQ)
 * has been received. This is an unsolicited message sent directly to the
 * Application Task.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * The unique ID for the EDEV that this FRQ is associated with.
   */
  u16_t                      edevId;
  /**
   * Information for the canceled FRQ.
   */
  sl_flow_server_req_info_t  req;
  /**
   * Information for the FRP associated with the canceled FRQ.
   */
  sl_flow_server_resp_info_t resp;
  /**
   * Indicates whether an FRP associated with the canceled FRQ exists.
   */
  bool                       respExists;
} sl_flow_server_cancel_res_request_ind;

/******************************************************************************/
/**
 * \struct sl_flow_client_create_res_request_req
 * This request is used by the Customer Application to send a new Flow Reservation
 * Request (FRQ) to the Flow Reservation server. Once the request is handled the
 * SL Task responds with a \ref SL_FLOW_CLIENT_CREATE_RES_REQUEST_CNF.
 *
 * This request will trigger the Flow Client to POST the FRQ to the Flow Server
 * and start fast polling for the Flow Reservation Response (FRP).   The normal
 * polling rate is every 5 minutes, the fast polling rate is every 15 seconds.
 * The Flow Client will switch back to the normal polling rate when the FRP
 * associated with the create FRQ is received.
 *
 * Limitations: The maximum number of FRQs that can be maintained by the Flow Client
 * at one time is 10.  When the FRP associated with an FRQ is done (completed,
 * canceled, or superseded) the FRQ will no longer be maintained by the Flow Client.
 *
 * Dependencies: The SL_FLOW_CLIENT_CREATE_RES_REQUEST_REQ may only be sent after
 * a \ref SL_FLOW_CLIENT_SERVER_IND has been received by the Customer Application.
 */
typedef struct {
  /**
   * Information on the time window and charge requested by the client.
   */
  sl_flow_req_t              req;
} sl_flow_client_create_res_request_req;

/******************************************************************************/
/**
 * \struct sl_flow_client_create_res_request_cnf
 * This confirmation is sent in response to the \ref SL_FLOW_CLIENT_CREATE_RES_REQUEST_REQ
 * request to send a Flow Reservation Request (FRQ) to the Flow server. The
 * confirmation provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Array of length \ref SL_XSD_MRID_LEN containing the MRID of the FRQ.
   */
  u8_t                       mrId[SL_XSD_MRID_LEN];
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                status;
} sl_flow_client_create_res_request_cnf;

/******************************************************************************/
/**
 * \struct sl_flow_client_cancel_res_request_req
 * This request is used by the Customer Application to send a cancel of an
 * existing Flow Reservation Request (FRQ) to the Flow Reservation server. Once
 * the request is handled the SL Task responds with a \ref SL_FLOW_CLIENT_CANCEL_RES_REQUEST_CNF.
 *
 * Dependencies: The SL_FLOW_CLIENT_CANCEL_RES_REQUEST_REQ may only be sent after
 * a \ref SL_FLOW_CLIENT_CREATE_RES_REQUEST_REQ has been sent and handled successfully.
 */
typedef struct {
  /**
   * Array of length \ref SL_XSD_MRID_LEN containing the MRID of the FRQ to cancel.
   */
  u8_t                       mrId[SL_XSD_MRID_LEN];
} sl_flow_client_cancel_res_request_req;

/******************************************************************************/
/**
 * \struct sl_flow_client_cancel_res_request_cnf
 * This confirmation is sent in response to the \ref SL_FLOW_CLIENT_CANCEL_RES_REQUEST_REQ
 * request to send a cancel Flow Reservation Request (FRQ) to the Flow server.
 * The confirmation provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Array of length \ref SL_XSD_MRID_LEN containing the MRID of the canceled FRQ.
   */
  u8_t                       mrId[SL_XSD_MRID_LEN];
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t                status;
} sl_flow_client_cancel_res_request_cnf;

/******************************************************************************/
/**
 * \struct sl_flow_client_res_resp_ind
 * This indication is sent to indicate that a Flow Reservation Response (FRP)
 * has been received. This is an unsolicited message sent directly to the
 * Application Task.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Structure containing information about the active handling of the
   * reservation response (i.e., information maintained by the Flow Client as
   * part of active handling).
   */
  sl_flow_client_resp_active_info_t activeInfo;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t        eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t                eventStatusDateTime;
  /**
   * Structure containing FRP data and event information.
   */
  sl_flow_resp_t                    resp;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t         respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                  version;
} sl_flow_client_res_resp_ind;

/******************************************************************************/
/**
 * \struct sl_flow_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the Flow Client to indicate that a new Flow server has been found.
 *
 * The client application may use this indication as a trigger to start
 * requesting Flow information from the Flow client and to start creating Flow
 * Reservation Requests. If Flow information is requested before this indication
 * is sent, the Flow client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_flow_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_flow_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_flow_client_get_res_resp_list_req
 * This request is used by the Customer Application to request some number
 * of FRPs. The \ref SL_FLOW_CLIENT_GET_RES_RESP_LIST_CNF will be sent as an
 * acknowledgment of the request, and the FRPs themselves will be sent in
 * the \ref SL_FLOW_CLIENT_RES_RESP_LIST_IND message. While the application may request as
 * many FRPs as it wants, only up to \ref SL_FLOW_CLIENT_MAX_NUM_FRPS will be returned
 * in a single indication. Therefore this request may generate multiple indications.
 *
 * Note that this structure is very similar to the \ref sl_cmn_get_list_req_time_t
 * structure used for getting other event lists, but it does not have the parentMrid
 * field.
 *
 * Dependencies: The \ref SL_FLOW_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the FLOW client.
 *
 */
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
   u32_t                     transactionId;
   /**
    * Type of amount that is being requested.
    *
    * If this is set to \ref SL_CMN_LIST_AMOUNT_TYPE_QUANTITY, then the \ref numResources
    * field indicates the number of resources and the \ref startRange and \ref endRange fields
    * are ignored.
    *
    * If this is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_RANGE, then the
    * \ref startRange and \ref endRange fields indicate the time range and the
    * \ref numResources field indicates the maximum number of resources in that
    * time range.
    *
    * If this is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_IN_MINUTES, then the
    * \ref numMinutes field indicates the number of minutes worth of resources to get
    * and the \ref numResources field indicates the maximum number of resources in
    * that time range.
    *
    * All other values for this field are invalid.
    */
   sl_cmn_list_amount_type_t amountType;
   /**
    * This is the number of resources that are being requested by the application,
    * where \ref SL_CMN_CLIENT_GET_ENTIRE_LIST may be used to indicate that the
    * application is requesting all available resources. Note that there may be
    * fewer than \ref numResources available so less than this number may be returned.
    */
   u8_t                      numResources;
   /**
    * If \ref amountType is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_IN_MINUTES this field
    * indicates the number of minutes worth of resources to get. The number of minutes
    * may be in the future or past depending on the sort direction of the list.
    * If the list is specified to be sorted in ascending order this field defines
    * the number of minutes from now in the future.  If this list is specified to
    * be sorted in descending order this field defines the number of minutes from
    * now in the past.
    */
   u32_t                     numMinutes;
   /**
    * If \ref amountType is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_RANGE this field
    * indicates the start of the time range to get resources.
    */
   sl_xsd_time_type_t        startRange;
   /**
    * If \ref amountType is set to \ref SL_CMN_LIST_AMOUNT_TYPE_TIME_RANGE this field
    * indicates the end of the time range to get resources.
    */
   sl_xsd_time_type_t        endRange;
} sl_flow_client_get_res_resp_list_req;

/******************************************************************************/
/**
 * \struct sl_flow_client_get_res_resp_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_FLOW_CLIENT_GET_RES_RESP_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_flow_client_get_res_resp_list_cnf
 */
typedef sl_cmn_get_list_cnf_t  sl_flow_client_get_res_resp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_flow_client_cancel_get_res_resp_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for FRPs. Note that until the \ref SL_FLOW_CLIENT_CANCEL_GET_RES_RESP_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_FLOW_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the FLOW client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_flow_client_cancel_get_res_resp_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_flow_client_cancel_get_res_resp_list_req;

/******************************************************************************/
/**
 * \struct sl_flow_client_cancel_get_res_resp_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated FRP processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_flow_client_cancel_get_res_resp_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_flow_client_cancel_get_res_resp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_flow_client_res_resp_list_ind
 * This indication is sent in response to the \ref SL_FLOW_CLIENT_GET_RES_RESP_LIST_REQ.
 * It will contain some number of FRPs up to \ref SL_FLOW_CLIENT_MAX_NUM_FRPS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available FRPs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of Flow Reservation Responses.
   */
  sl_flow_client_list_res_resp_t list[];  // Variable length up to SL_FLOW_CLIENT_MAX_NUM_FRPS
} sl_flow_client_res_resp_list_ind;

/******************************************************************************/
/**
 * \struct sl_flow_client_set_event_poll_rate_req
 * This request is used by the Customer Application to change the Services Layer
 * polling rate for Reservation Response events.  The default event polling rate
 * for Flow is \ref SL_FLOW_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_req_t sl_flow_client_set_event_poll_rate_req
 */
typedef sl_cmn_client_set_event_poll_rate_req_t sl_flow_client_set_event_poll_rate_req;

/******************************************************************************/
/**
 * \struct sl_flow_client_set_event_poll_rate_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_FLOW_CLIENT_SET_EVENT_POLL_RATE_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_flow_client_set_event_poll_rate_cnf
 */
typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_flow_client_set_event_poll_rate_cnf;

/** @} */
// end addtogroup FLOW_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup FLOW_GROUP


// -------------------- FSA -------------------

/**
 * \defgroup FSA_GROUP Function Set Assignments Definitions and Structures
 * \brief This section contains definitions and structures used by the FSA function set.
 * <b> Please note that this is an initial release of the FSA interfaces and
 * they are subject to change.</b>
 */
/** \addtogroup FSA_GROUP
 * @{ */

/**
 * \defgroup FSA_GROUP_STRUCTS FSA Structures
 * This section contains structures used by the FSA function set.
 */
/** \addtogroup FSA_GROUP_STRUCTS
 * @{ */

#define SL_FSA_CLIENT_MAX_NUM_FSAS   (5)

/******************************************************************************/
/**
 * \struct sl_fsa_client_server_found_ind
 * This indication is used to indicate to the Customer Application that
 * an EDEV server for this device was found.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * This structure contains the detailed information regarding the server.
   */
  sl_cmn_client_server_ind_t       serverDetails;

} sl_fsa_client_server_found_ind;

/******************************************************************************/
/**
 * \struct sl_fsa_client_get_fsa_list_req
 * This request is used by the Customer Application to request some number
 * of FSAs. The \ref SL_FSA_CLIENT_GET_FSA_LIST_CNF will be sent as an
 * acknowledgment of the request, and the FSAs themselves will be sent in
 * the \ref SL_FSA_CLIENT_FSA_LIST_IND message. While the application may request as
 * many FSAs as it wants up to 254 (255 is defined as requesting all available FSAs)
 * only up to \ref SL_FSA_CLIENT_MAX_NUM_FSAS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_FSA_CLIENT_GET_FSA_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The APP client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_FSA_CLIENT_SERVER_FOUND_IND must be received by the client
 * app before this request will be handled by the FSA client. An error will be
 * returned if there is no FSA server.
 *
 * typedef sl_cmn_get_list_req_root_t sl_fsa_client_get_fsa_list_req
 */
typedef sl_cmn_get_list_req_root_t sl_fsa_client_get_fsa_list_req;

/******************************************************************************/
/**
 * \struct sl_fsa_client_get_fsa_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_FSA_CLIENT_GET_FSA_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_fsa_client_get_fsa_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_fsa_client_get_fsa_list_cnf;

/******************************************************************************/
/**
 * \struct sl_fsa_client_cancel_get_fsa_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for FSAs. Note that until the \ref SL_FSA_CLIENT_CANCEL_GET_FSA_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_FSA_CLIENT_SERVER_FOUND_IND must be received by the client
 * app before this request will be handled by the FSA client.
*/
typedef struct {
  /**
   * transactionId is used to match the cancel request with the original
   * request.
   */
  u32_t       transactionId;
} sl_fsa_client_cancel_get_fsa_list_req;

/******************************************************************************/
/**
 * \struct sl_fsa_client_cancel_get_fsa_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated DRP processing has been stopped.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * transactionId is used to match the cancel confirmation with the original
   * request.
   */
  u32_t       transactionId;
  sl_cmn_rc_t status;
} sl_fsa_client_cancel_get_fsa_list_cnf;

/******************************************************************************/
/**
 * \struct sl_fsa_client_delete_fsa_root_req
 * This confirmation indicates that the associated request has been handled.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * transactionId is used to match the cancel request with the original
   * request.
   */
  u32_t       transactionId;
} sl_fsa_client_delete_fsa_root_req;

/******************************************************************************/
/**
 * \struct sl_fsa_client_delete_fsa_root_cnf
 * This request is used by the Customer Application to delted the FSA root
 *
 * Dependencies: The \ref SL_FSA_CLIENT_SERVER_FOUND_IND must be received by the client
 * app before this request will be handled by the FSA client.
*/
typedef struct {
  /**
   * transactionId is used to match the cancel request with the original
   * request.
   */
  u32_t       transactionId;
  sl_cmn_rc_t status;
} sl_fsa_client_delete_fsa_root_cnf;

/******************************************************************************/
/**
 * \struct sl_fsa_client_fsa_t
 * This structure contains the FSA information.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Indicates whether the CustomerAccountListLinkHash exists in this structure.
   */
  bool    CustomerAccountListLinkExists;
  /**
   * The hash of the CustomerAccountListLink href
   */
  u32_t   CustomerAccountListLinkHash;

  /**
   * Indicates whether the DemandResponseProgramListLinkHash exists in this structure.
   */
  bool    DemandResponseProgramListLinkExists;
  /**
   * The hash of the DemandResponseProgramListLink href
   */
  u32_t   DemandResponseProgramListLinkHash;

  /**
   * Indicates whether the DERProgramListLinkHash exists in this structure.
   */
  bool    DERProgramListLinkExists;
  /**
   * The hash of the DERProgramListLink href
   */
  u32_t   DERProgramListLinkHash;

  /**
   * Indicates whether the FileListLinkHash exists in this structure.
   */
  bool    FileListLinkExists;
  /**
   * The hash of the FileListLink href
   */
  u32_t   FileListLinkHash;

  /**
   * Indicates whether the MessagingProgramListLinkHash exists in this structure.
   */
  bool    MessagingProgramListLinkExists;
  /**
   * The hash of the MessagingProgramListLink href
   */
  u32_t   MessagingProgramListLinkHash;

  /**
   * Indicates whether the PrepaymentListLinkHash exists in this structure.
   */
  bool    PrepaymentListLinkExists;
  /**
   * The hash of the PrepaymentListLink href
   */
  u32_t   PrepaymentListLinkHash;

  /**
   * Indicates whether the ResponseSetListLinkHash exists in this structure.
   */
  bool    ResponseSetListLinkExists;
  /**
   * The hash of the ResponseSetListLink href
   */
  u32_t   ResponseSetListLinkHash;

  /**
   * Indicates whether the TariffProfileListLinkHash exists in this structure.
   */
  bool    TariffProfileListLinkExists;
  /**
   * The hash of the TariffProfileListLink href
   */
  u32_t   TariffProfileListLinkHash;

  /**
   * Indicates whether the TimeLinkHash exists in this structure.
   */
  bool    TimeLinkExists;
  /**
   * The hash of the TimeLink href
   */
  u32_t   TimeLinkHash;

  /**
   * Indicates whether the UsagePointListLinkHash exists in this structure.
   */
  bool    UsagePointListLinkExists;
  /**
   * The hash of the UsagePointListLink href
   */
  u32_t   UsagePointListLinkHash;

  /**
   * Indicates whether the subscribable exists in this structure.
   */
  bool    subscribableExists;
  /**
   * The subscribable object
   */
  u8_t    subscribable;

  /**
   * The mRID of this FSA
   */
  u8_t    mRID[SL_XSD_MRID_LEN];

  /**
   * Indicates whether the CustomerAccountListLinkHash exists in this structure.
   */
  bool    descriptionExists;
  /**
   * The description of this FSA
   */
  char    description[SL_XSD_DESCRIPTION_LEN];

  /**
   * Indicates whether the version exists in this structure.
   */
  bool    versionExists;
  /**
   * The version of this FSA
   */
  u16_t   version;

} sl_fsa_client_fsa_t;

/******************************************************************************/
/**
 * \struct sl_fsa_client_fsa_list_ind
 * This indication is sent in response to the \ref SL_FSA_CLIENT_GET_FSA_LIST_REQ.
 * It will contain some number of FSAs up to \ref SL_FSA_CLIENT_MAX_NUM_FSAS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available FSAS have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t          results;
  /**
   * List of FSAs.
   */
  sl_fsa_client_fsa_t list[];  // Variable length up to SL_FSA_CLIENT_MAX_NUM_FSAS
} sl_fsa_client_fsa_list_ind;
 
 
/******************************************************************************/
/**
 * \struct sl_fsa_server_fsa_t
 * This structure contains the FSA information used by the server.
 *
 * To include a function set list link in the FSA, set the associated "GroupIdExists"
 * field to true. To set which function set group to include in the FSA, choose the
 * appropriate "GroupId". It is acceptable to set the "GroupId" to the default
 * group \ref SL_OBJ_INSTANCE_DEF_GRP_ID, while  setting the "GroupIdExists" to true.
 * In this case, the default or public list link for that function set will be included
 * in the FSA. The GroupId maps to \ref sl_server_obj_ref_t::instanceIDs[0] when
 * creating function set resources.
 *
 * Note: Even if the "Exists" field is set to true, the associated list link will
 * only be created by the server if the associated function set is supported by the
 * server.
 */
typedef struct {
  /**
   * Group ID of the Billing Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t billGroupId;
  /**
   * Boolean indicating that a Billing list link should be included in the FSA.
   */
  bool                 billGroupIdExists;
  /**
   * Group ID of the DER Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t derGroupId;
  /**
   * Boolean indicating that a DER list link should be included in the FSA.
   */
  bool                 derGroupIdExists;
  /**
   * Character array providing a description of the FSA, with max length
   * of \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                 description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Group ID of the DRLC Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t drlcGroupId;
  /**
   * Boolean indicating that a DRLC list link should be included in the FSA.
   */
  bool                 drlcGroupIdExists;
  /**
   * Group ID of the File Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t fileGroupId;
  /**
   * Boolean indicating that a File list link should be included in the FSA.
   */
  bool                 fileGroupIdExists;
  /**
   * Group ID of the Meter Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t meterGroupId;
  /**
   * Boolean indicating that a Meter list link should be included in the FSA.
   */
  bool                 meterGroupIdExists;
  /**
   * Unique MRID for this FSA of length SL_XSD_MRID_LEN.
   */
  u8_t                 mrId[SL_XSD_MRID_LEN];
  /**
   * Group ID of the MSG Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t msgGroupId;
  /**
   * Boolean indicating that a MSG list link should be included in the FSA.
   */
  bool                 msgGroupIdExists;
  /**
   * Group ID of the Prepayment Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t ppyGroupId;
  /**
   * Boolean indicating that a Prepayment list link should be included in the FSA.
   */
  bool                 ppyGroupIdExists;
  /**
   * Group ID of the Price Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t priceGroupId;
  /**
   * Boolean indicating that a Price list link should be included in the FSA.
   */
  bool                 priceGroupIdExists;
  /**
   * Group ID of the Response Group to include in this FSA or \ref SL_OBJ_INSTANCE_DEF_GRP_ID.
   */
  sl_obj_instance_id_t respGroupId;
  /**
   * Boolean indicating that a Response list link should be included in the FSA.
   */
  bool                 respGroupIdExists;
} sl_fsa_server_fsa_t;

/** @} */
// end addtogroup FSA_GROUP_STRUCTS

/**
 * \defgroup FSA_GROUP_MAIL_STRUCTS FSA Mail Structures
 * This section contains mail structures used by the FSA function set.
 */
/** \addtogroup FSA_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_fsa_server_create_fsa_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Function
 * Set Assignment (FSA) within the FSA Server. Once the request is handled
 *  the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the
 *  \ref sl_fsa_server_create_fsa_cnf structure.
 *
 * The ref field of the sl_fsa_server_create_fsa_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_FSA_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Note: Please note that while there is no particular order required when
 * creating an EDEV and an associated FSA, the Customer Application should
 * choose a groupId that will be used for both.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t ref;
  /**
   * FSA to create.
   */
  sl_fsa_server_fsa_t fsa;
} sl_fsa_server_create_fsa_req;

/******************************************************************************/
/**
 * \struct sl_fsa_server_create_fsa_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ
 * mail message to create a \ref SL_OBJ_ID_X_FSA_X (Function Set Assignment
 * Resource). The confirmation provides a status of the operation and contains
 * the ref structure of the created FSA. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_fsa_server_create_fsa_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId    = \ref SL_OBJ_ID_X_FSA_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for this FSA\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_fsa_server_create_fsa_cnf
 */
typedef sl_server_obj_cnf_t sl_fsa_server_create_fsa_cnf;

/******************************************************************************/
/**
 * \struct sl_fsa_server_delete_fsa_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Function
 * Set Assignment (FSA) within the FSA Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_fsa_server_delete_fsa_cnf.
 *
 * The ref field of the sl_fsa_server_delete_fsa_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_FSA_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the FSA\n
 *
 * Dependencies: The \ref sl_fsa_server_delete_fsa_req may only be sent after an
 * \ref sl_drlc_server_create_drp_req for that resource has been sent and handled
 * successfully.
*/
typedef sl_server_obj_ref_t sl_fsa_server_delete_fsa_req;

/******************************************************************************/
/**
 * \struct sl_fsa_server_delete_fsa_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_FSA_X (Function Set Assignment or
 * FA). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted FSA. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_fsa_server_delete_fsa_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_FSA_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the DRP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_fsa_server_delete_fsa_cnf
 */
typedef sl_server_obj_cnf_t sl_fsa_server_delete_fsa_cnf;

/** @} */
// end addtogroup FSA_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup FSA_GROUP




// -------------------- LEL -------------------

/**
 * \defgroup LEL_GROUP ELEL/SLEL Definitions and Structures
 * \brief This section contains definitions and structures used by the End
 *        Log Event (ELEL) and Self Log Event (SLEL) function sets.
 */
/** \addtogroup LEL_GROUP
 * @{ */

/**
 * \defgroup LEL_GROUP_DEFINES Definitions
 * This section contains definitions used by the LEL function set.
 */
/** \addtogroup LEL_GROUP_DEFINES
 * @{ */
// XSD LogEvent.functionSet
#define SL_LE_FUNCSET_GENERAL               0    //106049r31
#define SL_LE_FUNCSET_SUBSCRIBE             1
#define SL_LE_FUNCSET_ENDDEVICE             2
#define SL_LE_FUNCSET_ENDDEVICEGROUPS       3
#define SL_LE_FUNCSET_RESPONSE              4
#define SL_LE_FUNCSET_DRLC                  5
#define SL_LE_FUNCSET_METERING              6
#define SL_LE_FUNCSET_PRICING               7
#define SL_LE_FUNCSET_MESSAGING             8
#define SL_LE_FUNCSET_BILLING               9
#define SL_LE_FUNCSET_PREPAYMENT            10
#define SL_LE_FUNCSET_DER                   11
#define SL_LE_FUNCSET_TIME                  12
#define SL_LE_FUNCSET_SOFTWAREDOWNLOAD      13
#define SL_LE_FUNCSET_DEVINFO               14
#define SL_LE_FUNCSET_POWERSTATUS           15
#define SL_LE_FUNCSET_NETWORKSTATUS         16
#define SL_LE_FUNCSET_LEL                   17
#define SL_LE_FUNCSET_CONFIG                18
#define SL_LE_FUNCSET_SECURITY              19
#define SL_LE_FUNCSET_RESERVED              20    //20-255 reserved

// XSD LogEvent.profileId
#define SL_LE_PROFILEID_NOTSPECIFIC         0
#define SL_LE_PROFILEID_VENDORDEFINED       1
#define SL_LE_PROFILEID_SMARTENERGY         2
#define SL_LE_PROFILEID_HOMEAUTOMATION      3
#define SL_LE_PROFILEID_BUILDINGAUTOMATION  4
#define SL_LE_PROFILEID_RESERVED            5    //5-255 reserved

// XSD LogEvent.logEventPEN
#define SL_LE_LOGEVENTPEN_CSEP              40732

// XSD LogEvent.logEventCode
#define SL_LE_LOGEVENTCODE_SECURITY_TLS_ALERT               0
#define SL_LE_LOGEVENTCODE_SECURITY_REGISTRATION_LIST_MISS  1
#define SL_LE_LOGEVENTCODE_SECURITY_ACL_ACCESS_FAILED       2

#define SL_LE_LOGEVENTCODE_PS_LOW_BATTERY                   0

#define SL_LE_LOGEVENTCODE_TM_TIME_ADJUSTED                 0
#define SL_LE_LOGEVENTCODE_TM_TIME_SOURCE_CHANGED           1

// logEventIDs
#define SL_LE_GEN_HARDWARE                  1
#define SL_LE_GEN_SOFTWARE                  2
/** @} */
// end addtogroup LEL_GROUP_DEFINES

/**
 * \defgroup LEL_GROUP_STRUCTS Log Event Structures
 * This section contains structures used by the ELEL and SLEL function sets.
 */
/** \addtogroup LEL_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_log_event_t
 * This structure contains Log Event data.  The Log Event contains log information.
 *
 * Dependencies: None.
 */
typedef struct
{
  /**
   * The date and time that the event occurred.
   */
  sl_xsd_time_type_t     createdDateTime;
  /**
   * Human readable text that MAY be used to transmit additional details about 
   * the event. A host MAY remove this field when received.
   */
  char                   details[SL_XSD_DETAILS_LEN];
  /**
   * May be used to transmit additional details about the event.
   */
  u32_t                  extendedData;
  /**
   * Flag indicating whether extended data exists.
   */
  bool                   extendedDataExists;
  /**
   * If the  profileID indicates this is the Smart Energy Profile, then
   * functionSet indicates the function set associated with the log event.
   * If the profile is anything else, the logEventCode is defined by the
   * specified profile.
   */
  sl_xsd_function_set_t  functionSet;
  /**
   * If the  profileID indicates this is the Smart Energy Profile, then the
   * logEventCode is defined in the Smart Energy Profile specification. If
   * the profile is anything else, the logEventCode is defined by the specified
   * profile.
   */
  u8_t                   logEventCode;
  /**
   * If the  profileID indicates this is the Smart Energy Profile, then the
   * logEventID is defined in the Smart Energy Profile specification. If
   * the profile is anything else, the logEventID is defined by the specified
   * profile.
   */
  u16_t                  logEventID;
  /**
   * The Private Enterprise Number(PEN) of the entity that defined the profileID,
   * functionSet, logEventCode, and logEventID of the logEvent. The combinations
   * of profileID, functionSet, logEventID, and logEventCode have unique meaning
   * within a logEventPEN and are defined by the owner of the PEN.
   */
  u32_t                  logEventPEN;
  /**
   * The profileID identifies which profile defines the log event information.
   */
  sl_xsd_profile_id_t    profileID;
} sl_log_event_t;

/** @} */
// end addtogroup LEL_GROUP_STRUCTS

/**
 * \defgroup LEL_GROUP_MAIL_STRUCTS Log Event Mail Structures
 * This section contains mail structures used by the SLEL and ELEL function sets.
 */
/** \addtogroup LEL_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_slel_server_create_le_req;
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Log Event Entry
 * entry in the Self Device Log Event Log (\ref SL_OBJ_ID_X_SDEV_SLEL_X). Once the
 * request is handled the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using
 * the \ref sl_slel_server_create_le_cnf structure.
 *
 * This request may not be sent prior to sending the \ref SL_STARTUP_REQ and
 * receiving the \ref SL_STARTUP_CNF.
 *
 * The ref field of the sl_slel_server_create_le_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_SLEL_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: MUST NOT be sent prior to receiving the \ref SL_STARTUP_CNF.
 */
typedef struct {
  /**
   * References the SEP object (and action) for delivery of this message.
   */
  sl_server_obj_ref_t    ref;
  /**
   * Log Event information
   */
  sl_log_event_t         logEvent;
} sl_slel_server_create_le_req;

/******************************************************************************/
/**
 * \struct sl_slel_server_create_le_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ
 * mail message to create a \ref SL_OBJ_ID_X_SDEV_SLEL_X (Self Device Log Event
 * Log or SDEV SLEL). The confirmation provides a status of the operation and contains
 * the ref structure of the created LEL. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_slel_server_create_le_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_SLEL_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the LEL entry\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_slel_server_create_le_cnf
 */
typedef sl_server_obj_cnf_t sl_slel_server_create_le_cnf;

/******************************************************************************/
/**
 * \struct sl_elel_server_le_ind
 * This indication is sent to the Customer Application when a client device
 * updates the information stored in its device information resource.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Instance ID associated with the end device providing a log event.
   */
  u16_t                                edevId;
  /**
   * References the SEP object.  Shall contain the following values:\n
   * ref.objId          = \ref SL_OBJ_ID_X_EDEV_X_LEL\n
   * ref.numInstanceIDs = 2\n
   * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
   * ref.instanceIDs[1] = The unique ID for the EDEV\n
   */
  sl_server_obj_ref_t                  ref;
  /**
   * Received log Event information.
   */
  sl_log_event_t                       logEvent;
} sl_elel_server_le_ind;

/******************************************************************************/
/**
 * \struct sl_elel_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the ELEL Client to indicate that a ELEL server has been found.
 *
 * The client application may use this indication as a trigger to start
 * putting LEL information to the server. The included server/source
 * information is used to put an ELEL via the \ref sl_elel_client_send_lel_req.
 * If \ref sl_elel_client_send_lel_req is requested before this indication is
 * sent, the LEL client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_elel_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_elel_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_elel_client_send_le_req
 * This request is used by the client Customer Application to put a Log Event
 * resource to an ELEL Server. Once the request is handled
 * the SL Task responds with a \ref SL_ELEL_CLIENT_SEND_LE_CNF.
 *
 * Dependencies: None.
 *
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Log event information.
   */
  sl_log_event_t                       logEvent;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
} sl_elel_client_send_le_req;

/******************************************************************************/
/**
 * \struct sl_elel_client_send_le_cnf
 * This confirmation is sent in response to the \ref SL_ELEL_CLIENT_SEND_LE_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t         transactionId;
  /**
   * Status indicating whether the operation was successful or not.
   */
  i8_t          status;
} sl_elel_client_send_le_cnf;

/** @} */
// end addtogroup LEL_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup LEL_GROUP


/** \cond NOTRELEASED */

// -------------------- Load Shed Availability --
typedef struct {
  u32_t               availabilityDuration;
  bool                availabilityDurationExists;
  u16_t               sheddablePercent;
  bool                sheddablePercentExists;
  bool                sheddablePowerExists;
  i8_t                sheddablePowerMultiplier;
  u16_t               sheddablePowerValue;
  /**
   * Boolean indicating if the drpLink should be included in the LSA. If true,
   * the drpMrid is used to create the link.
   */
  bool                 drpLinkExists;
  /**
   * The unique MRID for the DRP that this LSA is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                 drpMrId[SL_XSD_MRID_LEN];
} sl_cmn_lsa_t;

/******************************************************************************/
/**
 * \struct sl_sdrlc_server_store_lsa_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This structure is used by the Customer Application to create or update a
 * Self Device (SDEV) Load Shed Availability resource (\ref SL_OBJ_ID_X_SDEV_SLSA).
 * Once the request is handled the SL Task responds with a
 * \ref SL_SERVER_OBJ_CREATE_CNF using the \ref sl_sdrlc_server_store_lsa_cnf structure.
 *
 * The ref field of the sl_sdrlc_server_store_lsa_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_SLSA\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Contains the LSA resource information
   */
  sl_cmn_lsa_t         lsa;
}sl_sdrlc_server_store_lsa_req;

/******************************************************************************/
/**
 * \struct sl_slsa_server_store_lsa_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ
 * mail message to create a \ref SL_OBJ_ID_X_SDEV_SLSA (Self Device Load Shed
 * Availabiity Resource). The confirmation provides a status of the operation and contains
 * the ref structure of the created LEL. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_slsa_server_store_lsa_cnf will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_SLSA\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_sdrlc_server_store_lsa_cnf
 */
typedef sl_server_obj_cnf_t sl_sdrlc_server_store_lsa_cnf;

typedef struct {
  /**
   * Contains the LSA resource information
   */
  sl_cmn_lsa_t        lsa;
} sl_edrlc_client_put_lsa_req;

typedef struct {
  i8_t          status;
} sl_edrlc_client_put_lsa_cnf;

typedef struct {
  /**
   * Specifies all of the instance IDs necessary to reference the parent EDEV resource.
   * The first element refers to the group ID.
   */
  sl_obj_instance_id_t  edevId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
  /**
   * Contains the LSA resource information
   */
  sl_cmn_lsa_t          lsa;
} sl_edrlc_server_lsa_ind;

/** \endcond */

// -------------------- Meter --------------------

/**
 * \defgroup METER_GROUP Meter Definitions and Structures
 * This section contains definitions and structures used by the Meter function set.
 */
/** \addtogroup METER_GROUP
 * @{ */

/**
 * \defgroup METER_GROUP_DEFINES Meter Definitions
 * This section contains definitions used by the Meter function set.
 */
/** \addtogroup METER_GROUP_DEFINES
 * @{ */

/**
 * Used by the Meter Function Set. This defines the maximum number of Usage Points
 * that may be returned in a single mail message.
 */
#define SL_METER_CLIENT_MAX_NUM_UPS        (5)

/**
 * Used by the Meter Function Set. This defines the maximum number of Meter Reading
 * resources that may be returned in a single mail message.
 */
#define SL_METER_CLIENT_MAX_NUM_MRS        (5)

/**
 * Used by the Meter Function Set. This defines the maximum number of Rate Components
 * that may be returned in a single mail message.
 */
#define SL_METER_CLIENT_MAX_NUM_RCS        (5)

/**
 * Used by the Meter Function Set. This defines the maximum number of Reading Sets
 * that may be returned in a single mail message.
 */
#define SL_METER_CLIENT_MAX_NUM_RSETS      (5)

/**
 * Used by the Meter Function Set. This defines the maximum number of Readings
 * that may be returned in a single mail message.
 */
#define SL_METER_CLIENT_MAX_NUM_READINGS   (5)

/** @} */
// end addtogroup METER_GROUP_DEFINES

/**
 * \defgroup METER_GROUP_TYPES Meter Types
 * This section contains types used by the Meter function set.
 */
/** \addtogroup METER_GROUP_TYPES
 * @{ */

/******************************************************************************/
/**
 * \struct sl_reading_t
 * Contains information specific to a particular reading. This structure is
 * used for both the Metering and Meter Mirroring function sets to capture
 * reading information.
 */
typedef struct {
  /**
   * Indicates the consumption block related to the reading. If not
   * specified, is assumed to be "0 - N/A".
   */
  sl_xsd_cons_block_type_t      consumptionBlock;
  /**
   * Boolean indicating whether or not the consumption block field is
   * present in the reading.
   */
  bool                          consumptionBlockExists;
  /**
   * The time duration associated with the reading in seconds. If not
   * specified, then defaults to the duration specified in the associated
   * ReadingType.
   */
  u32_t                         duration;
  /**
   * The local identifier for this reading within the reading set. localIDs are
   * assigned in order of creation time. For interval data, this value SHALL
   * increase with each interval time, and for block/tier readings,
   * localID SHALL not be specified.
   */
  u16_t                         localId;
  /**
   * Boolean indicating whether or not the localId field is present in the
   * reading.
   */
  bool                          localIdExists;
  /**
   * Indicates the quality of the reading.
   */
  sl_xsd_read_qual_flags_type_t qualFlags;
  /**
   * Boolean indicating whether or not the quality flags field is present
   * in the reading.
   */
  bool                          qualFlagsExists;
  /**
   * The start time associated with the reading. If not specified, then
   * defaults to the start time specified in the associated ReadingType.
   */
  sl_xsd_time_type_t            start;
  /**
   * Indicates the time of use tier related to the reading. If not
   * specified, is assumed to be "0 - N/A".
   */
  sl_xsd_tou_type_t             touTier;
  /**
   * Boolean indicating whether or not the time of use tier field is
   * present in the reading.
   */
  bool                          touTierExists;
  /**
   * Value in units specified by ReadingType.
   */
  i64_t                         value;
  /**
   * Boolean indicating whether or not the value field is present in the
   * reading.
   */
  bool                          valueExists;
} sl_reading_t;

/******************************************************************************/
/**
 * \struct sl_rset_t
 * Contains information specific to a particular reading set. This structure is
 * used for both the Metering and Meter Mirroring function sets to capture reading
 * set information.
 */
typedef struct {
  /**
   * Array providing a human readable description of the Reading Set,
   * with max length of SL_XSD_DESCRIPTION_LEN. Character array must be
   * null terminated.
   */
  char          description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for this Reading Set of length SL_XSD_MRID_LEN.
   */
  u8_t          mrId[SL_XSD_MRID_LEN];
  /**
   * Specifies the time range duration (in seconds) during which the
   * contained readings were taken.
   */
  u32_t         periodDuration;
  /**
   * Specifies the start time during which the contained readings were taken.
   */
  sl_xsd_time_type_t  periodStart;
} sl_rset_t;

/******************************************************************************/
/**
 * \struct sl_rtype_t
 * Contains information specific to a particular reading type. This structure is
 * used for both the Metering and Meter Mirroring function sets to capture reading
 * type information.
 *
 * typedef sl_cmn_rt_t sl_rtype_t
 */
typedef sl_cmn_rt_t sl_rtype_t;

/******************************************************************************/
/**
 * \struct sl_meter_client_mr_t
 * This structure contains the client data fields associated with a Meter
 * Reading container resource.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Unique MRID for this Meter Reading container resource of length SL_XSD_MRID_LEN.
   */
  u8_t                 mrId[SL_XSD_MRID_LEN];
  /**
   * Array providing a human readable description of the Meter Reading container,
   * with max length of SL_XSD_DESCRIPTION_LEN. Character array must be
   * null terminated.
   */
  char                 description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Flag indicating whether a Rate Component list exists for the MR.
   */
  bool                 rateComponentListExists;
  /**
   * Flag indicating whether a Reading Set list exists for the MR.
   */
  bool                 readingSetListExists;
  /**
   * Flag indicating whether a Reading is included in the MR.
   */
  bool                 readingExists;
  /**
   * Optional Reading associated with the MR.
   */
  sl_reading_t         reading;
  /**
   * Reading type associated with the MR.
   */
  sl_rtype_t           rtype;
} sl_meter_client_mr_t;

/******************************************************************************/
/**
 * \struct sl_meter_server_mr_t
 * This structure contains the server data fields associated with a Meter
 * Reading container resource.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Array providing a human readable description of the Meter Reading,
   * with max length of \ref SL_XSD_DESCRIPTION_LEN. Character array must be
   * null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for this Meter Reading Resource of length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Boolean indicating if the Rate Component List Link is to be included in the
   * MR. If set to true, the tpId fields indicate which RC list link to include.
   */
  bool                  rcListLinkExists;
  /**
   * Specifies all of the instance IDs necessary to reference a tariff profile resource.
   * The first element refers to the group ID.
   */
  sl_obj_instance_id_t  tpId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
  /**
   * Specifies all of the instance IDs necessary to reference a Reading Type resource.
   * The first element refers to the group ID. Note that the reading type
   * MUST be created first. This value is returned in the confirmation
   * when the reading type is created.
   */
  sl_obj_instance_id_t  rtypeId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
} sl_meter_server_mr_t;

/** @} */
// end addtogroup METER_GROUP_TYPES


/**
 * \defgroup METER_GROUP_MAIL_STRUCTS Meter Mail Structures
 * This section contains mail structures used by the Meter function set.
 */
/** \addtogroup METER_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_meter_server_store_top_read_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite a new Top Level Reading
 * Resource within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_STORE_CNF using the structure
 * \ref sl_meter_server_store_top_read_cnf.
 *
 * The ref field of the sl_meter_server_store_top_read_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_R\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Specific reading information being created.
   */
  sl_reading_t  reading;
} sl_meter_server_store_top_read_req;


/******************************************************************************/
/**
 * \struct sl_meter_server_store_top_read_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_UPT_X_MR_X_R (Top Level Reading).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created Top Level Reading. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_create_top_read_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_R\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_store_top_read_cnf
 */
typedef sl_server_obj_cnf_t sl_meter_server_store_top_read_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_top_read_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Meter Reading
 * within the METER Server. It will also cause all child resources to be delete
 * as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_meter_server_delete_top_read_cnf.
 *
 * The ref field of the sl_meter_server_delete_top_read_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_R\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: The \ref sl_meter_server_delete_top_read_req may only be sent after an
 * \ref sl_meter_server_store_top_read_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_meter_server_delete_top_read_req
*/
typedef sl_server_obj_ref_t sl_meter_server_delete_top_read_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_top_read_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_UPT_X_MR_X_R (Top Level Reading)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted Top Level Reading. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_delete_top_read_req will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_R\\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
*
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_delete_top_read_cnf
*/
typedef sl_server_obj_cnf_t sl_meter_server_delete_top_read_cnf;


/******************************************************************************/
/**
 * \struct sl_meter_server_create_mr_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Meter Reading
 * Resource within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_meter_server_create_mr_cnf.
 *
 * The ref field of the sl_meter_server_create_mr_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Meter Reading Data
   */
  sl_meter_server_mr_t mr;
} sl_meter_server_create_mr_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_mr_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_UPT_X_MR_X (Meter Reading or MR).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created Meter Reading. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_create_mr_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_create_mr_cnf
 */
typedef sl_server_obj_cnf_t sl_meter_server_create_mr_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_mr_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Meter Reading
 * within the METER Server. It will also cause all child resources to be delete
 * as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_meter_server_delete_mr_cnf.
 *
 * The ref field of the sl_meter_server_delete_mr_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: The \ref sl_meter_server_delete_mr_req may only be sent after an
 * \ref sl_meter_server_create_mr_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_meter_server_delete_mr_req
*/
typedef sl_server_obj_ref_t sl_meter_server_delete_mr_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_mr_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_UPT_X_MR_X (Meter Reading or MR)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted MR. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_delete_mr_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_delete_mr_cnf
*/
typedef sl_server_obj_cnf_t sl_meter_server_delete_mr_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_mr_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite an existing
 * Meter Reading Resource within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_STORE_CNF using the structure
 * \ref sl_meter_server_store_mr_cnf.
 *
 * NOTE: If the mRID does not match the mRID of the existing resource, a
 * failure of SL_CMN_RC_MRID_MISMATCH will be returned.
 *
 * The ref field of the sl_meter_server_store_mr_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: None.
 *
 * typedef sl_meter_server_create_mr_req sl_meter_server_store_mr_req
 */
typedef sl_meter_server_create_mr_req sl_meter_server_store_mr_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_mr_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_UPT_X_MR_X (Meter Reading or MR).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the updated Meter Reading. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_store_mr_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_store_mr_cnf
 */
typedef sl_server_obj_cnf_t sl_meter_server_store_mr_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_reading_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Reading
 * Resource within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_meter_server_create_reading_cnf.
 *
 * The ref field of the sl_meter_server_create_reading_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[2] = The unique ID for the RS\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Specific reading information being created.
   */
  sl_reading_t  reading;
} sl_meter_server_create_reading_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_reading_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X (Reading).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created Reading. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_create_reading_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 * ref.instanceIDs[4] = The unique ID for the Reading\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_create_reading_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_meter_server_create_reading_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_reading_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Reading
 * within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_meter_server_delete_reading_cnf.
 *
 * The ref field of the sl_meter_server_delete_reading_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 * ref.instanceIDs[4] = The unique ID for the Reading\n
 *
 * Dependencies: The \ref sl_meter_server_delete_reading_req may only be sent after an
 * \ref sl_meter_server_create_reading_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_meter_server_delete_reading_req
*/
typedef sl_server_obj_ref_t sl_meter_server_delete_reading_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_reading_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite an existing
 * Reading Resource within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_STORE_CNF using the structure
 * \ref sl_meter_server_store_reading_cnf.
 *
 * The ref field of the sl_meter_server_store_reading_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[2] = The unique ID for the RS\n
 * ref.instanceIDs[4] = The unique ID for the Reading\n
 *
 * Dependencies: None.
 *
 * typedef sl_meter_server_create_reading_req sl_meter_server_store_reading_req
 */
typedef sl_meter_server_create_reading_req sl_meter_server_store_reading_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_reading_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X (Reading).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created Reading. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_create_reading_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 * ref.instanceIDs[4] = The unique ID for the Reading\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_store_reading_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_meter_server_store_reading_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_reading_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X (Reading)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted Reading. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_delete_reading_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X_R_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 * ref.instanceIDs[4] = The unique ID for the Reading\n
*
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_delete_reading_cnf
*/
typedef sl_server_obj_cnf_t sl_meter_server_delete_reading_cnf;


/******************************************************************************/
/**
 * \struct sl_meter_server_create_rset_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Reading
 * Set Resource (RS) within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_meter_server_create_rset_cnf.
 *
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * The reading set to be created.
   */
  sl_rset_t            rset;
} sl_meter_server_create_rset_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_rset_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X (Reading Set or RS).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created RS. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_create_rset_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_create_rset_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_meter_server_create_rset_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_rset_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Reading
 * Set (RS) within the METER Server. It will also cause all child
 * resources to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_meter_server_delete_rset_cnf.
 *
 * The ref field of the sl_meter_server_delete_rset_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 *
 * Dependencies: The \ref sl_meter_server_delete_rset_req may only be sent after an
 * \ref sl_meter_server_create_rset_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_meter_server_delete_rset_req
*/
typedef sl_server_obj_ref_t sl_meter_server_delete_rset_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_rset_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X (Reading Set or RS)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted RS. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * NOTE: When a reading set is deleted, the child readings are deleted as well.
 *
 * The ref field of the sl_meter_server_delete_rset_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_delete_rset_cnf
*/
typedef sl_server_obj_cnf_t sl_meter_server_delete_rset_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_rset_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to over write an existing
 * Reading Set Resource (RS) within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_STORE_CNF using the structure
 * \ref sl_meter_server_store_rset_cnf.
 *
 * The ref field of the sl_meter_server_store_rset_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 *
 * Dependencies: None.
 *
 * typedef sl_meter_server_create_rset_req sl_meter_server_store_rset_req
 */
typedef sl_meter_server_create_rset_req sl_meter_server_store_rset_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_rset_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X (Reading Set or RS).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the updated RS. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_store_rset_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X_MR_X_RS_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 * ref.instanceIDs[2] = The unique ID for the MR\n
 * ref.instanceIDs[3] = The unique ID for the RS\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_store_rset_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_meter_server_store_rset_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Reading
 * Type (RT) within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_meter_server_create_rtype_cnf.
 *
 * The ref field of the sl_meter_server_create_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_create_rtype_req sl_meter_server_create_rtype_req
 */
typedef sl_cmn_server_create_rtype_req sl_meter_server_create_rtype_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created RT. It uses the common structure
 *  \ref sl_cmn_server_create_rtype_cnf.
 *
 * The ref field of the sl_meter_server_create_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_create_rtype_cnf sl_meter_server_create_rtype_cnf
 *
 */
typedef sl_cmn_server_create_rtype_cnf sl_meter_server_create_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Reading
 * Type (RT) within the METER Server.  Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_meter_server_delete_rtype_cnf.
 *
 * The ref field of the sl_meter_server_delete_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: The \ref sl_meter_server_delete_rtype_req may only be sent after an
 * \ref sl_meter_server_create_rtype_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_cmn_server_delete_rtype_req sl_meter_server_delete_rtype_req
*/
typedef sl_cmn_server_delete_rtype_req sl_meter_server_delete_rtype_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_delete_rtype_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_delete_rtype_cnf sl_meter_server_delete_rtype_cnf
*/
typedef sl_cmn_server_delete_rtype_cnf sl_meter_server_delete_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite an existing
 * Reading Type (RT) within the server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_meter_server_store_rtype_cnf.
 *
 * The ref field of the sl_meter_server_store_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_store_rtype_req sl_meter_server_store_rtype_req
 */
typedef sl_cmn_server_store_rtype_req sl_meter_server_store_rtype_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the updated RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_store_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_store_rtype_cnf sl_meter_server_store_rtype_cnf
 *
 */
typedef sl_cmn_server_store_rtype_cnf sl_meter_server_store_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_up_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Usage
 * Point Resource (UPT) within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_meter_server_create_up_cnf.
 *
 * The ref field of the sl_meter_server_create_up_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Usage Point Data
   */
  sl_cmn_up_t          upt;
} sl_meter_server_create_up_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_create_up_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_UPT_X (Usage Point or UPT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created UPT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_create_up_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_create_up_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_meter_server_create_up_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_up_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Usage
 * Point (UPT) within the METER Server. It will also cause all child
 * resources to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_meter_server_delete_up_cnf.
 *
 * The ref field of the sl_meter_server_delete_up_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 *
 * Dependencies: The \ref sl_meter_server_delete_up_req may only be sent after an
 * \ref sl_meter_server_create_up_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_meter_server_delete_up_req
*/
typedef sl_server_obj_ref_t sl_meter_server_delete_up_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_delete_up_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_UPT_X (Usage Point or UPT)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted UPT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_delete_up_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_delete_up_cnf
*/
typedef sl_server_obj_cnf_t sl_meter_server_delete_up_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_up_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite an existing
 * Usage Point Resource (UPT) within the METER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_STORE_CNF using the structure
 * \ref sl_meter_server_store_up_cnf.
 *
 * NOTE: If the mRID does not match the mRID of the existing resource, a
 * failure of SL_CMN_RC_MRID_MISMATCH will be returned.
 *
 * The ref field of the sl_meter_server_store_up_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 *
 * Dependencies: None.
 *
 * typedef sl_meter_server_create_up_req sl_meter_server_store_up_req
 */
typedef sl_meter_server_create_up_req sl_meter_server_store_up_req;

/******************************************************************************/
/**
 * \struct sl_meter_server_store_up_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to over write a \ref SL_OBJ_ID_X_UPT_X (Usage Point or UPT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the updated UPT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_meter_server_store_up_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_UPT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the UPT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_meter_server_store_up_cnf
 *
 */
typedef sl_server_obj_cnf_t sl_meter_server_store_up_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the Meter Client to indicate that a new Meter server has been found. Note
 * that multiple indications may be sent if there are multiple servers and/or
 * sources of Meter information available.
 *
 * The client application may use this indication as a trigger to start
 * requesting Meter information from the Meter client. The included server/source
 * information is used to request a Meter list via the \ref sl_meter_client_get_up_list_req.
 * If Meter information is requested before this indication is sent, the Meter
 * client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_meter_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_meter_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_mr_list_req
 * This request is used by the Customer Application to request some number
 * of MRs (Meter Reading containers). The parentMrId field must contain the
 * mrId of the Usage Point associated with this MR. The \ref SL_METER_CLIENT_GET_MR_LIST_CNF
 * will be sent as an acknowledgment of the request, and the MRs themselves will
 * be sent in the \ref SL_METER_CLIENT_MR_LIST_IND message. While the application may
 * request as many MRs as it wants, only up to \ref SL_METER_CLIENT_MAX_NUM_MRS will
 * be returned in a single indication. Therefore this request may generate multiple
 * indications.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client. Also, the client
 * must receive the UPT information for the requested MRs from the
 * \ref SL_METER_CLIENT_UP_LIST_IND.
 *
 * typedef sl_cmn_get_list_req_quantity_t sl_meter_client_get_mr_list_req
 */
typedef sl_cmn_get_list_req_quantity_t sl_meter_client_get_mr_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_mr_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_METER_CLIENT_GET_MR_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_meter_client_get_mr_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_meter_client_get_mr_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_mr_list_ind
 * This indication is sent in response to the \ref SL_METER_CLIENT_GET_MR_LIST_REQ.
 * It will contain some number of MRs up to \ref SL_METER_CLIENT_MAX_NUM_MRS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available MRs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of MRs.
   */
  sl_meter_client_mr_t   list[];  // Variable length up to SL_METER_CLIENT_MAX_NUM_MRS
} sl_meter_client_mr_list_ind;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_mr_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for MRs. Note that until the \ref SL_METER_CLIENT_CANCEL_GET_MR_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_mr_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_mr_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_mr_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated MR processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_mr_list_cnf
 */
typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_mr_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_rc_list_req
 * This request is used by the Customer Application to request some number
 * of RCs (Rate Components). The parentMrId field must contain the
 * mrId of the Meter Reading container associated with this RC. The \ref SL_METER_CLIENT_GET_RC_LIST_CNF
 * will be sent as an acknowledgment of the request, and the RCs themselves will
 * be sent in the \ref SL_METER_CLIENT_RC_LIST_IND message. While the application may
 * request as many RCs as it wants, only up to \ref SL_METER_CLIENT_MAX_NUM_RCS will
 * be returned in a single indication. Therefore this request may generate multiple
 * indications.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client. Also, the client
 * must receive the MR information for the requested MRs from the
 * \ref SL_METER_CLIENT_MR_LIST_IND.
 *
 * typedef sl_cmn_get_list_req_quantity_t sl_meter_client_get_rc_list_req
 */
typedef sl_cmn_get_list_req_quantity_t sl_meter_client_get_rc_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_rc_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_METER_CLIENT_GET_RC_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_meter_client_get_rc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_meter_client_get_rc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_rc_list_ind
 * This indication is sent in response to the \ref SL_METER_CLIENT_GET_RC_LIST_REQ.
 * It will contain some number of MRs up to \ref SL_METER_CLIENT_MAX_NUM_RCS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available MRs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * The \ref SL_PRICE_CLIENT_GET_TTI_LIST_REQ may be used to get the list of TTIs that
 * are related to the RCs returned in this indication.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of RCs.
   */
  sl_cmn_rcomp_t         list[];  // Variable length up to SL_METER_CLIENT_MAX_NUM_RCS
} sl_meter_client_rc_list_ind;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_rc_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for RCs. Note that until the \ref SL_METER_CLIENT_CANCEL_GET_RC_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_rc_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_rc_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_rc_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated RC processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_rc_list_cnf
 */
typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_rc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_reading_list_req
 * This request is used by the Customer Application to request some number
 * of Readings.  The parentMrId field must contain the mrId of the Reading Set
 * associated with this Reading. The \ref SL_METER_CLIENT_GET_READING_LIST_CNF will
 * be sent as an acknowledgment of the request, and the Readings themselves will
 * be sent in the \ref SL_METER_CLIENT_READING_LIST_IND message. While the application
 * may request as many Readings as it wants, only up to \ref SL_METER_CLIENT_MAX_NUM_READINGS
 * will be returned in a single indication. Therefore this request may generate
 * multiple indications.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client. Also, the client
 * must receive the Reading Set information for the requested Readings from the
 * \ref SL_METER_CLIENT_RSET_LIST_IND.
 *
 * typedef sl_cmn_get_list_req_quantity_t sl_meter_client_get_reading_list_req
 */
typedef sl_cmn_get_list_req_quantity_t sl_meter_client_get_reading_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_reading_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_METER_CLIENT_GET_READING_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_meter_client_get_reading_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_meter_client_get_reading_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_reading_list_ind
 * This indication is sent in response to the \ref SL_METER_CLIENT_GET_READING_LIST_REQ.
 * It will contain some number of Readings up to \ref SL_METER_CLIENT_MAX_NUM_READINGS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available MRs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t         results;
  /**
   * List of Readings.
   */
  sl_reading_t              list[];  // Variable length up to SL_METER_CLIENT_MAX_NUM_READINGS
} sl_meter_client_reading_list_ind;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_reading_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for Readings. Note that until the \ref SL_METER_CLIENT_CANCEL_GET_READING_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_reading_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_reading_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_reading_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated Reading list processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_reading_list_cnf
 */
typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_reading_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_rset_list_req
 * This request is used by the Customer Application to request some number
 * of RSETs (Reading Sets). The \ref SL_METER_CLIENT_GET_RSET_LIST_CNF will be sent as an
 * acknowledgment of the request, and the RSETs themselves will be sent in
 * the \ref SL_METER_CLIENT_RSET_LIST_IND message. While the application may request as
 * many RSETs as it wants, only up to \ref SL_METER_CLIENT_MAX_NUM_RSETS will be returned
 * in a single indication. Therefore this request may generate multiple indications.
 * The RSET List is specified to be provided by the server in descending order
 * based on \ref sl_rset_t::periodStart.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client. Also, the client
 * must receive the MR information for the requested RSs from the
 * \ref SL_METER_CLIENT_MR_LIST_IND.
 *
 * typedef sl_cmn_get_list_req_time_t sl_meter_client_get_rset_list_req
 */
typedef sl_cmn_get_list_req_time_t sl_meter_client_get_rset_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_rset_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_METER_CLIENT_GET_RSET_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_meter_client_get_rset_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_meter_client_get_rset_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_rset_list_ind
 * This indication is sent in response to the \ref SL_METER_CLIENT_GET_RSET_LIST_REQ.
 * It will contain some number of RSs up to \ref SL_METER_CLIENT_MAX_NUM_RSETS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available MRs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of Reading Sets.  The Reading Set list is provided in descending order
   * based on \ref sl_rset_t::periodStart.
   */
  sl_rset_t              list[];  // Variable length up to SL_METER_CLIENT_MAX_NUM_RSETS
} sl_meter_client_rset_list_ind;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_rset_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for RSETs. Note that until the \ref SL_METER_CLIENT_CANCEL_GET_RSET_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_rset_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_rset_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_rset_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated RSET processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_rset_list_cnf
 */
typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_rset_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_up_list_req
 * This request is used by the Customer Application to request some number
 * of UPTs (Usage Points). The \ref SL_METER_CLIENT_GET_UP_LIST_CNF will be sent as an
 * acknowledgment of the request, and the UPTs themselves will be sent in
 * the \ref SL_METER_CLIENT_UP_LIST_IND message. While the application may request as
 * many UPTs as it wants up to 254 (255 is defined as requesting all available UPTs)
 * only up to \ref SL_METER_CLIENT_MAX_NUM_UPS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_METER_CLIENT_GET_UP_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The app client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client. An error will be
 * returned if there is no Meter server.
 *
 * typedef sl_cmn_get_list_req_root_t sl_meter_client_get_up_list_req
 */
typedef sl_cmn_get_list_req_root_t sl_meter_client_get_up_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_get_up_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_METER_CLIENT_GET_UP_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_meter_client_get_up_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_meter_client_get_up_list_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_client_up_list_ind
 * This indication is sent in response to the \ref SL_METER_CLIENT_GET_UP_LIST_REQ.
 * It will contain some number of UPTs up to \ref SL_METER_CLIENT_MAX_NUM_UPS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available UPTS have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t     results;
  /**
   * List of UPTs.
   */
  sl_cmn_up_t           list[];  // Variable length up to SL_METER_CLIENT_MAX_NUM_UPS
} sl_meter_client_up_list_ind;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_up_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for UPTs. Note that until the \ref SL_METER_CLIENT_CANCEL_GET_UP_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_METER_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_up_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_meter_client_cancel_get_up_list_req;

/******************************************************************************/
/**
 * \struct sl_meter_client_cancel_get_up_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated UPT processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_up_list_cnf
 */
typedef sl_cmn_cancel_get_list_cnf_t sl_meter_client_cancel_get_up_list_cnf;

/** @} */
// end addtogroup METER_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup METER_GROUP

// -------------------- Meter Mirror  ------------------------

/**
 * \defgroup METER_MIRROR_GROUP Meter Mirror Definitions and Structures
 * This section contains definitions and structures used by the Meter Mirror function set.
 */
/** \addtogroup METER_MIRROR_GROUP
 * @{ */

/**
 * \defgroup METER_MIRROR_GROUP_DEFINES Meter Mirror Definitions
 * This section contains definitions used by the EDEV function set.
 */
/** \addtogroup METER_MIRROR_GROUP_DEFINES
 * @{ */
  /**
   * Used by the Meter Mirroring Function Set. This defines the maximum number of
   * Mirror Reading Groups that can be included in a mirror usage point at one time.
   * This limit is imposed by SL.
   */
#define SL_METER_MIRROR_MAX_MR_GROUPS   (1)

/**
 * Used by the Meter Mirroring Function Set. This defines the maximum number of
 * Mirror Reading Sets that can be included in a mirror reading group.
 * This limit is imposed by SL.
 */
#define SL_METER_MIRROR_MAX_RSETS       (1)

/**
 * Used by the Meter Mirroring Function Set. This defines the maximum number of
 * readings that can be included in a mirror reading set.
 * This limit is imposed by SL.
 */
#define SL_METER_MIRROR_RSET_MAX_NUM_READINGS    (32)

/** @} */
// end addtogroup MIRROR_METER_GROUP_DEFINES


/**
 * \defgroup METER_MIRROR_GROUP_TYPEDEFS Meter Mirror Types
 * This section contains types used by the Meter Mirror function set.
 */
/** \addtogroup METER_MIRROR_GROUP_TYPEDEFS
 * @{ */




/******************************************************************************/
/**
 * \struct sl_mirror_rset_t
 * Contains mirror metering reading set information.
 */
typedef struct {
  /**
   * Reading set information.
   */
  sl_rset_t     rSet;
  /**
   * Number of reading included in the meter mirroring reading set.
   */
  u8_t          numReadings;
  /**
   * Reading included in the meter mirroring reading set.
   */
  sl_reading_t  readings[SL_METER_MIRROR_RSET_MAX_NUM_READINGS];
} sl_mirror_rset_t;

/******************************************************************************/
/**
 * \struct sl_mr_group_t
 * Contains information specific to a particular meter mirror reading.
 */
typedef struct
{
  /**
   * Array providing a human readable description of the Mirror Meter Reading,
   * with max length of \ref SL_XSD_DESCRIPTION_LEN. Character array must be
   * null terminated.
   */
  char                description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for the Mirror Meter Reading of length SL_XSD_MRID_LEN.
   */
  u8_t                mrId[SL_XSD_MRID_LEN];
  /**
   * The date and time of the last update. lastUpdateTime will only be included
   * if it is non-0.
   */
  sl_xsd_time_type_t  lastUpdateTime;
  /**
   * The date and time of the next planned update. nextUpdateTime will only be
   * included if it is non-0.
   */
  sl_xsd_time_type_t  nextUpdateTime;
  /**
   * Boolean indicating if the Reading Type is to be included in the MMR. The
   * Reading Type must exist in new MMRs.
   */
  bool                rtypeExists;
  /**
   * Reading type to include in the MMR.
   */
  sl_rtype_t          rtype;
  /**
   * Boolean indicating if a top level reading is included in the MMR.
   */
  bool                readingExists;
  /**
   * Top level reading that is included in the MMR.
   */
  sl_reading_t        reading;
  /**
   * Number of reading sets to include in the MMR.
   */
  u8_t                numReadingSets;
  /**
   * Reading sets to include in the MMR.
   */
  sl_mirror_rset_t    mirrorRset[SL_METER_MIRROR_MAX_RSETS];
} sl_mr_group_t;

/** @} */
// end addtogroup METER_MIRROR_GROUP_TYPEDEFS

/**
 * \defgroup METER_MIRROR_GROUP_MAIL_STRUCTS Meter Mirror Mail Structures
 * This section contains mail structures used by the Meter Mirror function set.
 */
/** \addtogroup METER_MIRROR_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_meter_mirror_server_config_client_filter_req
 * This request can be sent to the Meter Mirror Server in order to specify
 * what types of clients (based on the roles) will be allowed to post a MUP. If
 * any of the role flags indicated by the client match the roleFlagFilter, that
 * client will be allowed, otherwise the client will receive an HTTP response
 * of 500 Internal Server Error. This request should be sent prior to startup. Changes
 * to the roleFlagFilter will not affect existing MUPs.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Bitmap specifying the roles that will be accepted by the Meter Mirror Server. If any
   * role matches, the posts from the client will be accepted.
   */
  sl_xsd_role_flag_t roleFlagsFilter;
} sl_meter_mirror_server_config_client_filter_req;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_server_config_client_filter_cnf
 * This structure is sent in response to the SL_METER_MIRROR_SERVER_CONFIG_CLIENT_FILTER_REQ.
 * It provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  sl_cmn_rc_t     status;
} sl_meter_mirror_server_config_client_filter_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_server_rx_mup_ind
 * This indication is sent unsolicited from the Meter Mirroring server when
 * a new MUP is received.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Array providing a human readable description of the Mirror Usage Point,
   * with max length of \ref SL_XSD_DESCRIPTION_LEN. Character array must be
   * null terminated.
   */
  char               description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique ID of this MUP.
   */
  u16_t              mirrorUsagePointId;
  /**
   * Unique ID of the usage point associated with this MUP.
   */
  u16_t              usagePointId;
  /**
   * Unique MRID for the Mirror Usage Point of length \ref SL_XSD_MRID_LEN.
   */
  u8_t               mrId[SL_XSD_MRID_LEN];
  /**
   * Specifies the roles that apply to this mirror usage point.
   */
  sl_xsd_role_flag_t roleFlags;
  /**
   * Specifies the current status of the service at this mirror usage point.
   */
  sl_xsd_status_t    status;
  /**
   * Specifies the kind of service provided by this mirror usage point.
   */
  sl_xsd_service_t   serviceCategory;
  /**
   * Boolean indicating whether this indication contains postRate information.
   */
  bool               postRateExists;
  /**
   * POST rate, or how often mirrored data should be POSTed, in seconds.
   */
  u32_t              postRate;
  /**
   * Number of mirror meter reading groups included in the request, with a maximum
   * of \ref SL_METER_MIRROR_MAX_MR_GROUPS.
   */
  u8_t               numMeterReadingGroups;
  /**
   * LFDI associated with the device creating the Mirror Usage Point.
   */
  u8_t               lfdi[SL_XSD_LFDI_LEN];
  /**
   * Mirror meter reading information to send to the server, with a maximum
   * size of \ref SL_METER_MIRROR_MAX_MR_GROUPS.
   */
  sl_mr_group_t      mrGroup[];  // Variable length up to SL_METER_MIRROR_MAX_MR_GROUPS
} sl_meter_mirror_server_rx_mup_ind;


/******************************************************************************/
/**
 * \struct sl_meter_mirror_server_rx_mmr_ind
 * This indication is sent unsolicited from the Meter Mirroring server when
 * a new MMR is received.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Unique ID of the mirror usage point that this MMR is associated with.
   */
  u16_t         mirrorUsagePointId;
  /**
   * Unique ID of the mirror meter reading.
   */
  u16_t         mirrorMeterReadingId;
  /**
   * Unique ID of the usage point that this MUP/MMR are associated with.
   */
  u16_t         usagePointId;
  /**
   * Received mirror meter reading information.
   */
  sl_mr_group_t mrGroup;
} sl_meter_mirror_server_rx_mmr_ind;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the Meter Mirror client to indicate that a new Meter Mirroring server has been
 * found. The client application may use this indication as a trigger to start
 * sending metering data to the Meter Mirroring client. If meter mirroring data
 * is sent by the app before this indication is sent, the Meter Mirroring client
 * will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 */
typedef sl_cmn_client_server_ind_t sl_meter_mirror_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_send_mup_req
 * This request is used by the Customer Application to send a new or updated
 * Mirror Usage Point to the Meter Mirror server. Once the request is handled
 * the SL Task responds with a \ref SL_METER_MIRROR_CLIENT_SEND_MUP_CNF.
 *
 * Dependencies: The \ref SL_METER_MIRROR_CLIENT_SERVER_IND must be received by the
 * client app before this request is sent, or the confirmation will contain an
 * error status of \ref SL_CMN_RC_NO_SERVER.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the initial request message.
   */
  u32_t              transactionId;
  /**
   * Server and source information indicating where to post the mirror usage
   * point. This set of available servers/sources is provided by the SEP Client
   * in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * Array providing a human readable description of the Mirror Usage Point,
   * with max length of \ref SL_XSD_DESCRIPTION_LEN. Character array must be
   * null terminated.
   */
  char               description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for the Mirror Usage Point of length SL_XSD_MRID_LEN.
   */
  u8_t               mrId[SL_XSD_MRID_LEN];
  /**
   * Specifies the roles that apply to this mirror usage point.
   */
  sl_xsd_role_flag_t roleFlags;
  /**
   * Specifies the current status of the service at this mirror usage point.
   */
  sl_xsd_status_t    status;
  /**
   * Specifies the lFDI of the device at this mirror usage point.
   */
  u8_t               lFDI[SL_XSD_LFDI_LEN];
  /**
   * Specifies the kind of service provided by this mirror usage point.
   */
  sl_xsd_service_t   serviceCategory;
  /**
   * Boolean indicating whether this request contains postRate information.
   */
  bool               postRateExists;
  /**
   * POST rate, or how often mirrored data should be POSTed, in seconds.
   */
  u32_t              postRate;
  /**
   * Number of mirror meter reading groups included in the request, with a maximum
   * of SL_METER_MIRROR_MAX_MR_GROUPS. When sending a new Mirror Usage Point, at
   * least one Meter Reading Group must be provided.
   */
  u8_t               numMeterReadingGroups;
  /**
   * Mirror meter reading information to send to the server, with a maximum
   * size of \ref SL_METER_MIRROR_MAX_MR_GROUPS.
   */
  sl_mr_group_t      mrGroup[];  // Variable length up to SL_METER_MIRROR_MAX_MR_GROUPS
} sl_meter_mirror_client_send_mup_req;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_send_mup_cnf
 * This confirmation is sent in response to the \ref SL_METER_MIRROR_CLIENT_SEND_MUP_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the initial request message.
   */
  u32_t              transactionId;
  /**
   * Unique MRID for the Mirror Usage Point of length \ref SL_XSD_MRID_LEN.
   */
  u8_t               mrId[SL_XSD_MRID_LEN];
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t        status;
} sl_meter_mirror_client_send_mup_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_send_mmr_req
 * This request is used by the Customer Application to send new or updated
 * meter reading data to the Meter Mirror server. Once the request is handled
 * the SL Task responds with a \ref SL_METER_MIRROR_CLIENT_SEND_MMR_CNF.
 *
 * Dependencies: The \ref SL_METER_MIRROR_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Meter Mirroring client. Also
 * the app client must create the MUP using the SL_METER_MIRROR_CLIENT_SEND_MUP_REQ
 * before this request may be sent.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the initial request message.
   */
  u32_t              transactionId;
  /**
   * Unique MRID for the Mirror Usage Point to send the meter reading data
   */
  u8_t               mupMrId[SL_XSD_MRID_LEN];
  /**
   * Number of mirror meter reading groups included in the request, with a maximum
   * of SL_METER_MIRROR_MAX_MR_GROUPS.
   */
  u8_t               numMeterReadingGroups;
  /**
   * Mirror meter reading information to send to the server, with a maximum
   * size of \ref SL_METER_MIRROR_MAX_MR_GROUPS.
   */
  sl_mr_group_t      mrGroup[];  // Variable length up to SL_METER_MIRROR_MAX_MR_GROUPS
} sl_meter_mirror_client_send_mmr_req;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_send_mmr_cnf
 * This confirmation is sent in response to the \ref SL_METER_MIRROR_CLIENT_SEND_MMR_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the initial request message.
   */
  u32_t              transactionId;
  /**
   * Unique MRID for the Mirror Usage Point to send the meter reading data
   */
  u8_t               mupMrId[SL_XSD_MRID_LEN];
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t        status;
} sl_meter_mirror_client_send_mmr_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_mup_ind
 * This indication is sent unsolicited to the Customer Application at startup
 * to indicate whether a Mirror Usage Point for this device LFDI has been found.
 *
 * Dependencies: None
 */
typedef struct {
  /**
   * Status indicating the current state of finding Mirror Usage Points. If the client is
   * not finished finding resources, it will return a status of \ref SL_CMN_RC_OPERATION_IN_PROG.
   * If it is done, it will return a status of \ref SL_CMN_RC_OPERATION_DONE.
   */
  sl_cmn_rc_t        mupStatus;
  /**
   * Boolean indicating whether this indication contains valid Mirror Usage Point
   * information.  If false, all fields except for the /ref mupStatus field do not
   * contain valid information.
   */
  bool               mupExists;
  /**
   * Array providing a human readable description of the Mirror Usage Point,
   * with max length of \ref SL_XSD_DESCRIPTION_LEN.
   */
  char               description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for the Mirror Usage Point of length \ref SL_XSD_MRID_LEN.
   */
  u8_t               mrId[SL_XSD_MRID_LEN];
  /**
   * Specifies the roles that apply to this mirror usage point.
   */
  sl_xsd_role_flag_t roleFlags;
  /**
   * Specifies the current status of the service at this mirror usage point.
   */
  sl_xsd_status_t    status;
  /**
   * Specifies the lFDI of the device at this mirror usage point.
   */
  u8_t               lFDI[SL_XSD_LFDI_LEN];
  /**
   * Specifies the kind of service provided by this mirror usage point.
   */
  sl_xsd_service_t   serviceCategory;
  /**
   * Server and source information associated with this MUP.
   */
  sl_cmn_client_server_source_info_t  serverSourceInfo;
  /**
   * Boolean indicating whether this indication contains postRate information.
   */
  bool               postRateExists;
  /**
   * POST rate, or how often mirrored data should be POSTed, in seconds.
   */
  u32_t              postRate;
} sl_meter_mirror_client_mup_ind;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_get_mup_rates_req
 * This request is used by the Customer Application to request the MUP pollRate 
 * and postRate. The pollRate is an attribute of the MUP list, and the postRate
 * is an element of the MUP instance. This request triggers a GET of the MUP 
 * list and the MUP instance.
 * The \ref SL_METER_MIRROR_CLIENT_GET_MUP_RATES_CNF will be sent as an 
 * acknowledgment of the request.
 *
 * Dependencies: The \ref SL_METER_MIRROR_CLIENT_SERVER_IND must be received by 
 * the client app before this request will be handled by the MUP client. 
 *
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the initial request message.
   */
  u32_t              transactionId;
  /**
   * Server and source information for the list of interest. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * Unique MRID for the Mirror Usage Point to get the post rate
   */
  u8_t               mupMrId[SL_XSD_MRID_LEN];
} sl_meter_mirror_client_get_mup_rates_req;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_get_mup_rates_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_METER_MIRROR_CLIENT_GET_MUP_RATES_REQ. It contains a transaction 
 * ID so the client app can map it to the request. It also contains a status field 
 * which indicates success if the request is being handled, or an error status 
 * in case the request is not being handled. No indications should be expected 
 * by the app client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the initial request message.
   */
  u32_t              transactionId;
  /**
   * Unique MRID for the Mirror Usage Point to get the poll/post rates
   */
  u8_t               mupMrId[SL_XSD_MRID_LEN];
  /**
   * Status indicating whether the operation was successful or not.
   */
  sl_cmn_rc_t        status;
} sl_meter_mirror_client_get_mup_rates_cnf;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_mup_pollrate_ind
 * This indication is sent in response to the \ref SL_METER_MIRROR_CLIENT_GET_MUP_RATES_REQ.
 *
 * If an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
  * The default polling rate for this function set (this resource and all
  * resources below), in seconds. If not specified, a default of 900 seconds
  * (15 minutes) is used. It is RECOMMENDED a client poll the resources of
  * this function set every pollRate seconds.
  */
  u32_t         pollRate;
  /**
  * Boolean indicating if the pollRate field is valid.
  */
  bool          pollRateExists;
} sl_meter_mirror_client_mup_pollrate_ind;

/******************************************************************************/
/**
 * \struct sl_meter_mirror_client_mup_postrate_ind
 * This indication is sent in response to the \ref SL_METER_MIRROR_CLIENT_GET_MUP_RATES_REQ.
 *
 * If an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Unique MRID for the Mirror Usage Point to get the post rate
   */
  u8_t          mupMrId[SL_XSD_MRID_LEN];
  /**
   * Boolean indicating whether this indication contains a valid postRate.
   */
  bool          postRateExists;
  /**
   * POST rate, or how often mirrored data should be POSTed, in seconds.
   */
  u32_t         postRate;
} sl_meter_mirror_client_mup_postrate_ind;

/** @} */
// end addtogroup METER_MIRROR_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup METER_MIRROR_GROUP

// -------------------- Msg ------------------------

/**
 * \defgroup MSG_GROUP MSG Definitions and Structures
 * This section contains definitions and structures used by the Messaging function set.
 */
/** \addtogroup MSG_GROUP
 * @{ */

/**
 * \defgroup MSG_GROUP_DEFINES MSG Definitions
 * This section contains definitions used by the Messaging function set.
 */
/** \addtogroup MSG_GROUP_DEFINES
 * @{ */
  /**
   * Used by the Messaging Function Set (MSG). This defines the maximum number of
   * characters allowed in a text message.
   */
#define SL_MSG_MAX_TXT_LEN  (128)

/**
 * Used by the MSG Function Set. This defines the maximum number of MSG Programs
 * that may be returned in a single mail message.
 */
#define SL_MSG_CLIENT_MAX_NUM_MSGPS (5)

/**
 * Used by the MSG Function Set. This defines the maximum number of text messages
 * that may be returned in a single mail message.
 */
#define SL_MSG_CLIENT_MAX_NUM_TXTS (5)

/**
 * This defines the default polling rate for MSG Text events in seconds.  This
 * value is used with event handling only.
 */
#define SL_MSG_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC  (5*60)

/** @} */
// end addtogroup MSG_GROUP_DEFINES

/**
 * \defgroup MSG_GROUP_STRUCTS MSG Structures
 * This section contains structures used by the MSG function set.
 */
/** \addtogroup MSG_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_msg_msgp_t
 * This structure contains MSG Program (MSGP) data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Character array providing a description of the DRP, with max length
   *  of \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Identifier of a language region (RFC4646). Variable length array
   * with max length \ref SL_XSD_LOCALE_MAX_LEN. Character array must be
   * null terminated.
   */
  char                  locale[SL_XSD_LOCALE_MAX_LEN];
  /**
   * Unique MRID for this DRP of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the type of provider sending the DRP.
   */
  sl_xsd_primacy_type_t primacyType;
} sl_msg_msgp_t;

/******************************************************************************/
/**
 * \struct sl_msg_client_list_msgp_t
 * This structure contains information about an MSGP which is passed as part
 * of the list handling interface \ref sl_msg_client_msgp_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * MSG Program information.
   */
  sl_msg_msgp_t                        msgp;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                     version;
} sl_msg_client_list_msgp_t;

/******************************************************************************/
/**
 * \struct sl_msg_client_txt_active_info_t
 * This structure contains information about a TXT message which is being acted
 * upon by the MSG client. This structure will only be valid if active
 * event handling is enabled.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the current client status of the TXT. This is the same status
   * that would be sent to the server in a response.
   */
  sl_xsd_resp_status_type_t eventRespStatus;
} sl_msg_client_txt_active_info_t;

/******************************************************************************/
/**
 * \struct sl_msg_txt_t
 * This structure contains Text Message data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Contains details for this event such as start, duration,
   * response required, etc.
   */
  sl_cmn_event_t             event;
  /**
   * Length of the text message. Maximum length is \ref SL_MSG_MAX_TXT_LEN.
   * The character string must be null terminated.
   */
  u16_t                      messLeng;
  /**
   * Indicates the human-readable name of the publisher of the message.
   * Max length is SL_MSG_ORIG_MAX_LEN. The character array must be
   * null terminated.
   */
  char                       orig[SL_XSD_MSG_ORIG_MAX_LEN];
  /**
   * The priority is used to inform the client of the priority of the
   * particular message. Devices with constrained or limited resources
   * for displaying Messages should use this attribute to determine how
   * to handle displaying currently active Messages.
   */
  sl_xsd_msg_priority_type_t prio;
  /**
   * Character array that allows the server to provide a textual explanation
   * of the status. Array is of max length \ref SL_XSD_REASON_LEN. Character string
   * must be null terminated.
   */
  char                       reason[SL_XSD_REASON_LEN];
 /**
   * The variable length array with a maximum of \ref SL_MSG_MAX_TXT_LEN.  This
   * array contains the actual UTF-8 encoded text to be displayed.
   */
  char                       textMess[SL_MSG_MAX_TXT_LEN];
} sl_msg_txt_t;

/******************************************************************************/
/**
 * \struct sl_msg_client_list_txt_t
 * This structure contains information about a TXT which is passed as part
 * of the list handling interface \ref sl_msg_client_txt_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the TXT (i.e.,
   * information calculated or maintained by the MSG Client as part of active
   * handling).
   */
  sl_msg_client_txt_active_info_t activeInfo;
  /**
   * Boolean indicating whether the activeInfo structure contains valid information.
   * In the case that active handling is disabled, this field will always be set to
   * FALSE. In the case that active handling is enabled, this field may or may not
   * be present depending on whether the MSG Client is acting on it.
   */
  bool                             activeInfoExists;
  /**
   * The unique MRID for the MSGP that this TXT is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                             msgpMrId[SL_XSD_MRID_LEN];
  /**
   * Structure containing TXT data and event information.
   */
  sl_msg_txt_t                     txt;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_msg_client_list_txt_t;

/** @} */
// end addtogroup MSG_GROUP_STRUCTS


/**
 * \defgroup MSG_GROUP_MAIL_STRUCTS MSG Mail Structures
 * This section contains types used by the Meter Mirror function set.
 */
/** \addtogroup MSG_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_msg_server_create_msgp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Message
 * Program (MSGP) within the MSG Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_msg_server_create_msgp_cnf.
 *
 * The ref field of the sl_msg_server_create_msgp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  sl_server_obj_ref_t ref;
  /**
   * MSG Program Information.
   */
  sl_msg_msgp_t       msgp;
} sl_msg_server_create_msgp_req;

/******************************************************************************/
/**
 * \struct sl_msg_server_create_msgp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_MSG_X (Message Program or
 * MSGP). The confirmation provides a status of the operation and contains
 * the ref structure for the created MSGP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_msg_server_create_msgp_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the MSGP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_msg_server_create_msgp_cnf
 */
typedef sl_server_obj_cnf_t sl_msg_server_create_msgp_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_server_delete_msgp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Message
 * Program (MSGP) within the Message Server. It will also cause all child
 * events to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_msg_server_delete_msgp_cnf.
 *
 * The ref field of the sl_msg_server_delete_msgp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the MSGP\n
 *
 * Dependencies: The \ref sl_msg_server_delete_msgp_req may only be sent after an
 * \ref sl_msg_server_create_msgp_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_msg_server_delete_msgp_req
*/
typedef sl_server_obj_ref_t sl_msg_server_delete_msgp_req;

/******************************************************************************/
/**
 * \struct sl_msg_server_delete_msgp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_MSG_X (Message Program or
 * MSGP). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted MSGP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_msg_server_delete_msgp_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the MSGP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_msg_server_delete_msgp_cnf
*/
typedef sl_server_obj_cnf_t sl_msg_server_delete_msgp_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_server_create_txt_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Text Message
 * (TXT) within the Message Server. This request will trigger the MSG Server to
 * create the TXT and to start the associated timers and other handling for the
 * TXT. Once the request is handled the SL Task responds with a mail message of
 * \ref SL_SERVER_OBJ_CREATE_CNF using the structure \ref sl_msg_server_create_txt_cnf.
 *
 * The ref field of the sl_msg_server_create_txt_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent MSGP\n
 *
 * Dependencies: The sl_msg_server_create_txt_req may only be sent after the parent
 * MSGP has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * The unique ID for the Message Program that this TXT is associated with. This
   * ID is returned by the SL Task in the \ref sl_msg_server_create_msgp_cnf.
   */
  sl_server_obj_ref_t  ref;
  /**
   * If TRUE, indicates to the SL server that the creation time
   * included in the TXT should be used to specify the resource creation time. If
   * FALSE, indicates to the SL server to use the current time
   * as the creation time.
   */
  bool                 creationTimeExists;
  /**
   * Structure containing the details of the TXT, including event specific details
   * such as start and duration.
   */
  sl_msg_txt_t         txt;
  /**
   * Indicates which response set group should be used for client responses to this event.
   */
  sl_obj_instance_id_t respSetGroupId;
  /**
   * Indicates which response set should be used for client responses to this event.
   */
  sl_obj_instance_id_t respSetId;
} sl_msg_server_create_txt_req;

/******************************************************************************/
/**
 * \struct sl_msg_server_create_txt_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_MSG_X_TXT_X (Text Message or
 * TXT). The confirmation provides a status of the operation
 * and contains the ref structure for the created TXT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_msg_server_create_txt_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the MSGP\n
 * ref.instanceIDs[2] = The unique ID for the TXT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_msg_server_create_txt_cnf
 */
typedef sl_server_obj_cnf_t sl_msg_server_create_txt_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_server_cancel_txt_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_REQ mail message.
 *
 * This request is used by the Customer Application to immediately cancel an
 * existing TXT (Text Message) within the Message Server. Once the request is handled
 * the SL Task responds with a mail message of \ref SL_SERVER_OBJ_CANCEL_CNF using
 * the structure \ref sl_msg_server_cancel_txt_cnf.
 *
 * The ref field of the sl_msg_server_cancel_txt_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent MSGP\n
 * ref.instanceIDs[2] = The unique ID for the TXT\n
 *
 * Dependencies: The sl_msg_server_cancel_txt_req may only be sent after
 * a TXT has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t ref;
  /**
   * Variable length array that allows the server to provide a textual
   * explanation of the status. Array is of max length \ref SL_XSD_REASON_LEN.
   * Character string must be null terminated.
   */
  char                reason[SL_XSD_REASON_LEN];
} sl_msg_server_cancel_txt_req;

/******************************************************************************/
/**
 * \struct sl_msg_server_cancel_txt_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CANCEL_REQ
 * message to cancel a \ref SL_OBJ_ID_X_MSG_X_TXT_X (Text Message) object.
 * The confirmation provides a status of the operation and contains the ref
 * structure of the canceled TXT. It uses the generic cancel confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_msg_server_cancel_txt_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the MSG\n
 * ref.instanceIDs[2] = The unique ID for the TXT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_msg_server_cancel_txt_cnf
*/
typedef sl_server_obj_cnf_t sl_msg_server_cancel_txt_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_server_delete_txt_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Text Message
 * (TXT) within the Messages Server. It will also delete the active TXT if
 * there is one associated with this TXT. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_msg_server_delete_txt_cnf.
 *
 * The ref field of the sl_msg_server_delete_txt_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent MSGP\n
 * ref.instanceIDs[2] = The unique ID for the TXT\n
 *
 * Dependencies: The \ref sl_msg_server_delete_txt_req may only be sent after an
 * \ref sl_msg_server_create_txt_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_msg_server_delete_txt_req
*/
typedef sl_server_obj_ref_t sl_msg_server_delete_txt_req;

/******************************************************************************/
/**
 * \struct sl_msg_server_delete_txt_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_MSG_X_TXT_X (Text Message or
 * TXT). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted TXT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_msg_server_delete_txt_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the MSGP\n
 * ref.instanceIDs[2] = The unique ID for the TXT\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_msg_server_delete_txt_cnf
*/
typedef sl_server_obj_cnf_t sl_msg_server_delete_txt_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_server_event_status_ind
 * This indication is sent to the Customer Server application from the Message
 * server to indicate a change in the event status of objects of type
 * \ref SL_OBJ_ID_X_MSG_X_TXT_X. This is an unsolicited
 * message sent directly to the Application Task.
 *
 * The ref field of the sl_msg_server_event_status_ind will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_MSG_X_TXT_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent MSGP\n
 * ref.instanceIDs[2] = The unique ID for the TXT\n
 *
 * Note that valid event status values are:
 * - \ref SL_XSD_RESP_STATUS_EVENT_STARTED\n This status is sent at the start
 * time for the event.
 * - \ref SL_XSD_RESP_STATUS_EVENT_COMPLETED\n This status is sent at the
 * very end time of the event.
 * - \ref SL_XSD_RESP_STATUS_EVENT_CANCELED\n This status is sent when the
 * event is canceled via a CANCEL request from the Customer Server Application.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t       ref;
  /**
   * Unique MRID for this TXT of length SL_XSD_MRID_LEN.
   */
  u8_t                      mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the current status of the event.
   */
  sl_xsd_resp_status_type_t eventStatus;
} sl_msg_server_event_status_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_txt_ind
 * This indication is sent to the Customer Client application from the Message
 * client to indicate that a new TXT has been received. This is an unsolicited
 * message sent directly to the Application Task. This indication refers to
 * the next TXT. If more than the next TXT is needed, the client may send the
 * \ref SL_MSG_CLIENT_GET_TXT_LIST_REQ to request more.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the TXT (i.e.,
   * information calculated or maintained by the MSG Client as part of active
   * handling).
   */
  sl_msg_client_txt_active_info_t activeInfo;
  /**
   * Unique MRID for the Messaging Program associated with this text message.
   */
  u8_t                             msgpMrId[SL_XSD_MRID_LEN];
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * Structure containing TXT data and event information.
   */
  sl_msg_txt_t                     txt;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_msg_client_txt_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_msgp_ind
 * This indication is sent to the Customer Client application from the Message
 * Client to indicate that a new MSGP has been received. This is an unsolicited
 * message sent directly to the Application Task. If more than this MSGP is needed,
 * the client may send the \ref SL_MSG_CLIENT_GET_TXT_LIST_REQ to request more.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether this indication contains MSG Program information.
   * If false, the /ref msgp field does not contain information.
   */
  bool                                msgpExists;
  /**
   * MSG Program Information.
   */
  sl_msg_msgp_t                       msgp;
  /**
   * Server and source information associated with this DRP.
   */
  sl_cmn_client_server_source_info_t  serverSourceInfo;
  /**
   * Indicates the status of the current program (received/deleted/server lost).
   */
  sl_cmn_prog_status_t                status;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                    version;
} sl_msg_client_msgp_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the Message Client to indicate that a new Message server has been found. Note
 * that multiple indications may be sent if there are multiple servers and/or
 * sources of Message information available.
 *
 * The client application may use this indication as a trigger to start
 * requesting Message information from Message client. The included server/source
 * information is used to request a MSGP list via the \ref sl_msg_client_get_msgp_list_req.
 * If Message information is requested before this indication is sent, the Message
 * client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_msg_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_msg_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_set_event_programs_req
 *
 * This request is used by the Customer Application to request a list of Message
 * Programs to be used for event processing.  The \ref SL_MSG_CLIENT_SET_EVENT_PROGRAMS_CNF
 * will be sent as an acknowledgment of the request.  If the request is successful
 * a \ref SL_MSG_CLIENT_EVENT_PROGRAMS_IND will be sent after the confirm to
 * indicate the change to the Message Program event list.
 *
 * Note that the client app is responsible for meeting the following requirement
 * defined in the SEP2.0 specification:
 *   "MessagingPrograms indicated in FunctionSetAssignments SHALL be of higher
 *    priority than those found through discovery."
 *
 * Dependencies: The client must receive the MSGP mrIds for the requested Message Programs
 *               from the \ref SL_MSG_CLIENT_MSGP_IND.
 *
 * typedef sl_cmn_client_set_event_programs_req_t sl_msg_client_set_event_programs_req
 */
typedef sl_cmn_client_set_event_programs_req_t sl_msg_client_set_event_programs_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_set_event_programs_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_MSG_CLIENT_SET_EVENT_PROGRAMS_CNF.  It contains a status field
 * which indicates success if the request is being handled, or an error status
 * in case the request is not being handled.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_programs_cnf_t sl_msg_client_set_event_programs_cnf
*/
typedef sl_cmn_client_set_event_programs_cnf_t sl_msg_client_set_event_programs_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_client_event_programs_ind
 *
 * This indication is sent when there is a change to the list of Message Programs that
 * are being used for event processing.
 *
 * Dependencies: None
 *
 * typedef sl_cmn_client_event_programs_ind_t sl_msg_client_event_programs_ind
 */
typedef sl_cmn_client_event_programs_ind_t sl_msg_client_event_programs_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_set_event_roots_req
 *
 * This request is used by the Customer Application to request a list of MSG servers
 * to be used for event processing, up to a maximum of \ref SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS.
 * The \ref SL_MSG_CLIENT_SET_EVENT_ROOTS_CNF will be sent as an acknowledgment
 * of this request.
 *
 * Note that the client app is responsible for meeting the following requirement
 * defined in the SEP2.0 specification:
 *   "MessagingPrograms indicated in FunctionSetAssignments SHALL be of higher
 *    priority than those found through discovery."
 *
 * Also note that the client app may not select a server/source which is not indicated
 * to be time synced in \ref sl_msg_client_server_ind.
 *
 * Dependencies: The client app must receive indication of available MSG servers
 *               from \ref sl_msg_client_server_ind.
 *
 * typedef sl_cmn_client_set_event_roots_req_t sl_msg_client_set_event_roots_req
 */
typedef sl_cmn_client_set_event_roots_req_t sl_msg_client_set_event_roots_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_set_event_roots_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_MSG_CLIENT_SET_EVENT_ROOTS_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_roots_cnf_t sl_msg_client_set_event_roots_cnf
*/
typedef sl_cmn_client_set_event_roots_cnf_t sl_msg_client_set_event_roots_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_client_event_roots_ind
 *
 * This indication is sent to the Customer Application when there is a change in
 * the list of roots that are used for event processing.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_event_roots_ind_t sl_msg_client_event_roots_ind;

*/
typedef sl_cmn_client_event_roots_ind_t sl_msg_client_event_roots_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_set_event_poll_rate_req
 * This request is used by the Customer Application to change the Services Layer
 * polling rate for MSG Text events.  The default event polling rate for MSG
 * is \ref SL_MSG_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_req_t sl_msg_client_set_event_poll_rate_req
 */
typedef sl_cmn_client_set_event_poll_rate_req_t sl_msg_client_set_event_poll_rate_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_set_event_poll_rate_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_MSG_CLIENT_SET_EVENT_POLL_RATE_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_msg_client_set_event_poll_rate_cnf
 */
typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_msg_client_set_event_poll_rate_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_client_get_msgp_list_req
 * This request is used by the Customer Application to request some number
 * of MSGPs. The \ref SL_MSG_CLIENT_GET_MSGP_LIST_CNF will be sent as an
 * acknowledgment of the request, and the MSGPs themselves will be sent in
 * the \ref SL_MSG_CLIENT_MSGP_LIST_IND message. While the application may request as
 * many MSGPs as it wants up to 254 (255 is defined as requesting all available DRPs)
 * only up to \ref SL_MSG_CLIENT_MAX_NUM_MSGPS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_MSG_CLIENT_GET_MSGP_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The app client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_MSG_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Message client. An error will be
 * returned if there is no MSG server.
 *
 * typedef sl_cmn_get_list_req_root_t sl_msg_client_get_msgp_list_req
*/
typedef sl_cmn_get_list_req_root_t sl_msg_client_get_msgp_list_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_get_msgp_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_MSG_CLIENT_GET_MSGP_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_msg_client_get_msgp_list_cnf
*/
typedef sl_cmn_get_list_cnf_t sl_msg_client_get_msgp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_client_cancel_get_msgp_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for MSGPs. Note that until the \ref SL_MSG_CLIENT_CANCEL_GET_MSGP_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_MSG_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the MSG client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_msg_client_cancel_get_msgp_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_msg_client_cancel_get_msgp_list_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_cancel_get_msgp_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated MSGP processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_msg_client_cancel_get_msgp_list_cnf
*/
typedef sl_cmn_cancel_get_list_cnf_t sl_msg_client_cancel_get_msgp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_client_msgp_list_ind
 * This indication is sent in response to the \ref SL_MSG_CLIENT_GET_MSGP_LIST_REQ.
 * It will contain some number of MSGPs up to \ref SL_MSG_CLIENT_MAX_NUM_MSGPS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available MSGPs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t         results;
  /**
   * List of Message Programs.
   */
  sl_msg_client_list_msgp_t list[];  // Variable length up to SL_MSG_CLIENT_MAX_NUM_MSGPS
} sl_msg_client_msgp_list_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_get_txt_list_req
 * This request is used by the Customer Application to request some number
 * of TXTs. The \ref SL_MSG_CLIENT_GET_TXT_LIST_CNF will be sent as an
 * acknowledgment of the request, and the TXTs themselves will be sent in
 * the \ref SL_MSG_CLIENT_TXT_LIST_IND message. While the application may request as
 * many TXTs as it wants, only up to \ref SL_MSG_CLIENT_MAX_NUM_TXTS will be returned
 * in a single indication. Therefore this request may generate multiple indications.
 *
 * Dependencies: The \ref SL_MSG_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the MSG client. Also, the client
 * must receive the MSGP information for the requested TXTs either from the
 * \ref SL_MSG_CLIENT_MSGP_LIST_IND or the \ref SL_MSG_CLIENT_MSGP_IND.
 *
 * typedef sl_cmn_get_list_req_time_t sl_msg_client_get_txt_list_req
 */
typedef sl_cmn_get_list_req_time_t sl_msg_client_get_txt_list_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_get_txt_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_MSG_CLIENT_GET_TXT_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_msg_client_get_txt_list_cnf
 */
typedef sl_cmn_get_list_cnf_t  sl_msg_client_get_txt_list_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_client_cancel_get_txt_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for TXTs. Note that until the \ref SL_MSG_CLIENT_CANCEL_GET_TXT_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_MSG_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the MSG client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_msg_client_cancel_get_txt_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_msg_client_cancel_get_txt_list_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_cancel_get_txt_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated TXT processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_msg_client_cancel_get_txt_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_msg_client_cancel_get_txt_list_cnf;

/******************************************************************************/
/**
 * \struct sl_msg_client_txt_list_ind
 * This indication is sent in response to the \ref SL_MSG_CLIENT_GET_TXT_LIST_REQ.
 * It will contain some number of TXTs up to \ref SL_MSG_CLIENT_MAX_NUM_TXTS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available TXTs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of TXTs.
   */
  sl_msg_client_list_txt_t list[];  // Variable length up to SL_MSG_CLIENT_MAX_NUM_TXTS
} sl_msg_client_txt_list_ind;

/******************************************************************************/
/**
 * \struct sl_msg_client_reinit_msg_proc_req
 * This request is used by the Customer Application to request a retry of 
 * getting the initial Message Program List. 
 *
 * Dependencies: The \ref SL_MSG_CLIENT_SERVER_IND must be received by the client
 * app before sending this request.
 *
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
} sl_msg_client_reinit_msg_proc_req;

/******************************************************************************/
/**
 * \struct sl_msg_client_reinit_msg_proc_cnf
 * This is the confirmation to the  \ref SL_MSG_CLIENT_REINIT_MSG_PROC_REQ request.
 *
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
} sl_msg_client_reinit_msg_proc_cnf;

/** @} */
// end addtogroup MSG_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup MSG_GROUP

/** \cond NOTRELEASED */

// -------------------- NetStatus -------------------
// All fields per RFC 2863
// Note the data below is not sent via app->sep message
// passing, but is instead done with shared data accessed
// through function calls.
typedef struct {
  char          ifDescr[SL_XSD_STRING192_LEN];
  u32_t         ifHighSpeed;
  u32_t         iflnBroadcastPkts;
  u32_t         ifIndex;
  u32_t         ifInDiscards;
  u32_t         ifInErrors;
  u32_t         ifInMulticastPkts;
  u32_t         ifInOctets;
  u32_t         ifInUcastPkts;
  u32_t         ifInUnknownProtos;
  u32_t         ifMtu;
  char          ifName[SL_XSD_STRING16_LEN];
  u32_t         ifOperStatus;
  u32_t         ifOutBroadcastPkts;
  u32_t         ifOutDiscards;
  u32_t         ifOutErrors;
  u32_t         ifOutMulticastPkts;
  u32_t         ifOutOctets;
  u32_t         ifOutUcastPkts;
  u32_t         ifPromiscuousMode;
  u32_t         ifSpeed;
  u32_t         ifType;
  u8_t          ipAddr[SL_XSD_IPADDR_LEN];
  u32_t         lastResetTime;       // Use u64_t timecode when available
  u32_t         lastUpdatedTime;
} sl_sns_server_create_ipiface_req;

typedef struct {
  sl_result_t   result;
} sl_ns_server_create_ns_cnf;

/** \endcond */

// -------------------- Power Status ------------

/**
 * \defgroup PWRSTAT_GROUP EPWRSTAT/SPWRSTAT Definitions and Structures
 * \brief This section contains definitions and structures used by the End Device
 *        Power Status (EPWRSTAT) and Self Device Power Status (SPWRSTAT) function sets.
 */
/** \addtogroup PWRSTAT_GROUP
 * @{ */

/**
 * \defgroup PWRSTAT_GROUP_STRUCTS Power Status Structures
 * This section contains structures used by the EPWRSTAT and SPWRSTAT function sets.
 */
/** \addtogroup PWRSTAT_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_power_status_t
 *
 * This structure contains all of the information that is part of the SEP2
 * power status resource, used for both EDEV and SDEV power status cases.  The
 * power status resource contains the status of the device's power sources.
 *
 */
typedef struct {
  /**
   * The battery system status.
   */
  sl_xsd_battery_status_t  batteryStatus;
  /**
   * The time at which the reported values were recorded.
   */
  sl_xsd_time_type_t       changedTime;
  /**
   * Current power source of the device. This will be fixed for devices powered
   * by a single source. This value may change for devices able to transition between
   * multiple power sources (mains to battery backup, etc.).
   */
  sl_xsd_power_source_t    currentPowerSource;
  /**
   * Estimate of remaining battery charge as a percent of full charge.
   */
  u16_t                    estChargeRemaining;
  /**
   * Estimated time (in seconds) to total battery charge depletion (under current load).
   */
  u32_t                    estTimeRemaining;
  /**
   * If the device has a battery, this is the time since the device last switched to
   * battery power, or the time since the device was restarted, whichever is less,
   * in seconds.
   */
  u32_t                    sessionTimeOnBattery;
  /**
   * If the device has a battery, this is the total time the device has been on
   * battery power, in seconds. It may be reset when the battery is replaced.
   */
  u32_t                    totalTimeOnBattery;
  /**
   * Contains attributes that can be exposed by PEVs and other devices that have
   * charging requirements.
   */
  sl_xsd_pev_info_t        pevInfo;
  /**
   * Boolean indicating if the estChargeRemaining field is included.
   */
  bool                     estChargeRemainingExists;
  /**
   * Boolean indicating if the estTimeRemainingExists field is included.
   */
  bool                     estTimeRemainingExists;
  /**
   * Boolean indicating if the sessionTimeOnBatteryExists field is included.
   */
  bool                     sessionTimeOnBatteryExists;
  /**
   * Boolean indicating if the totalTimeOnBatteryExists field is included.
   */
  bool                     totalTimeOnBatteryExists;
  /**
   * Boolean indicating if the pevInfoExists field is included.
   */
  bool                     pevInfoExists;
} sl_power_status_t;

/** @} */
// end addtogroup PWRSTAT_GROUP_STRUCTS

/**
 * \defgroup PWRSTAT_GROUP_MAIL_STRUCTS Power Status Mail Structures
 * This section contains mail structures used by the SPWRSTAT and EPWRSTAT function sets.
 */
/** \addtogroup PWRSTAT_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_epwrstat_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the EPWRSTAT Client to indicate that a EPWRSTAT server has been found.
 *
 * The client application may use this indication as a trigger to start
 * putting EPWRSTAT information to the server. The included server/source
 * information is used to put a EPWRSTAT via the \ref sl_epwrstat_client_send_ps_req.
 * If \ref sl_epwrstat_client_send_ps_req is requested before this indication is
 * sent, the EPWRSTAT client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_epwrstat_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_epwrstat_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_epwrstat_client_send_ps_req
 * This request is used by the client Customer Application to put a Power Status
 * resource to a EPWRSTAT Server. Once the request is handled
 * the SL Task responds with a \ref SL_EPWRSTAT_CLIENT_SEND_PS_CNF.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
  /**
   * The power status information to be sent to the server.
   */
  sl_power_status_t                    pwrstat;
} sl_epwrstat_client_send_ps_req;

/******************************************************************************/
/**
 * \struct sl_epwrstat_client_send_ps_cnf
 * This confirmation is sent in response to the \ref SL_EPWRSTAT_CLIENT_SEND_PS_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Indicates the status of the send power status operation.
   */
  i8_t                                 status;
} sl_epwrstat_client_send_ps_cnf;

/** @} */
// end addtogroup PWRSTAT_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup PWRSTAT_GROUP


/** \cond NOTRELEASED */

/******************************************************************************/
/**
 * \struct sl_epwrstat_server_ps_ind
 * This indication is sent to the Customer Application when a client device
 * updates the power status information stored in its power status resource.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Instance ID associated with the end device updating its power status.
   */
  u16_t                                edevId;
  /**
   * The new power status information.
   */
  sl_power_status_t                    pwrstat;
} sl_epwrstat_server_ps_ind;

/******************************************************************************/
/**
 * \struct sl_spwrstat_server_store_sps_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Self Device (SDEV)
 * Power Status resource (\ref SL_OBJ_ID_X_SDEV_SPS). Once the
 * request is handled the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using
 * the \ref sl_spwrstat_server_store_sps_cnf structure.
 *
 * The ref field of the sl_spwrstat_server_store_sps_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_SPS\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t                  ref;
  /**
   * Power status information.
   */
  sl_power_status_t                    pwrstat;
} sl_spwrstat_server_store_sps_req;

/******************************************************************************/
/**
 * \struct sl_spwrstat_server_store_sps_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ
 * mail message to create a \ref SL_OBJ_ID_X_SDEV_SPS (Self Device Power
 * Status Resource). The confirmation provides a status of the operation and contains
 * the ref structure of the  SPS. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_spwrstat_server_store_sps_cnf will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_SPS\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_spwrstat_server_store_sps_cnf
 */
typedef sl_server_obj_cnf_t sl_spwrstat_server_store_sps_cnf;

// -------------------- PrePay ------------------
/**
 * Defines the upt array size for a ppy resource.
 */
#define SL_XSD_PREP_USAGPOIN_MAX (1)

// XSD AccountingUnitType
/******************************************************************************/
/**
 * \struct sl_xsd_acc_unit_t
 * Unit for accounting, using either 'energyUnit' or 'currencyUnit' to specify
 * the unit for 'value'.
 */
typedef struct {
  /**
   * Amount of real electrical energy.
   */
  sl_xsd_real_energy_t     energyUnit;
  /**
   * Indicates whether the energyUnit information is present in this structure.
   */
  bool                     energyUnitExists;
  /**
   * Unit of currency.
   */
  sl_xsd_curr_code_t       monetaryUnit;
  /**
   * Multiplier associated with the value below.
   */
  sl_xsd_ptm_type_t        mult;
  /**
   * Value of the energy in Watt-hours.
   */
  i32_t                    value;
} sl_xsd_acc_unit_t;

// XSD UsagePointType
/******************************************************************************/
/**
 * \struct sl_xsd_usage_point_t
 * Structure containing information used to define a usage point.
 */
typedef struct {
  /**
   * This implementation assumes the UPT was created and this just
   * contains all the UPT information. Other ways to implement:
   * 1) Create the UPTs and MRs via the Metering Function Set Interface
   * and then just pass the uptId and mrIds here
   * 2) Pass all the information here (minus the IDs) and have the
   * PPY server interact with the METER server to create the UPTs.
   */
  u16_t                 uptId;
  /**
   * Unique MRID for this usage point of max length SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Array providing a description of the usage point, with max length of
   * \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Specifies the roles that apply to the usage point.
   */
  sl_xsd_role_flag_t    roleFlags;
  /**
   * The kind of service provided by this usage point.
   */
  sl_xsd_service_t      serviceKind;
  /**
   * Specifies the current status of the service at this usage point.
   */
  sl_xsd_status_t       status;
  /**
   * Boolean indicating whether the lfdi field is included for this UP or not.
   */
  bool                  lFDIExists;
  /**
   * Specifies the lFDI of the device at this mirror usage point.
   */
  u8_t                  lFDI[SL_XSD_LFDI_LEN];
  /**
   * Unique ID associated with the meter reading for this usage point.
   */
  u16_t                 meterReadingId;
  /**
   * Boolean indicating whether the meter reading link should be
   * included with this usage point.
   */
  bool                  includeMeterReadingListLink;
} sl_xsd_usage_point_t;

/******************************************************************************/
/**
 * \struct sl_ppy_server_create_ppy_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Prepayment
 * Resource (PPY) within the Prepayment Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_ppy_server_create_ppy_cnf.
 *
 * The ref field of the sl_ppy_server_create_ppy_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: The usage points referenced in the request (uptId/upIdExists)
 * should be created prior to sending this request.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t         ref;
  /**
   * Unique MRID for this PPY of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t                        mrId[SL_XSD_MRID_LEN];
  /**
   * Array providing a description of the PPY, with max length of
   * \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                        description[SL_XSD_DESCRIPTION_LEN];
  /**
   * CreditExpiryLevel is the set point for availableCredit at which the
   * service level may be changed. The typical value for this attribute is 0,
   * regardless of whether the account balance is measured in a monetary or
   * commodity basis.
   */
  sl_xsd_acc_unit_t           creditExpiryLevel;
  /**
   * Boolean indicating whether the creditExpiryLevel is included in the
   * prepayment object.
   */
  bool                        creditExpiryLevelExists;
  /**
   * LowCreditWarningLevel is the set point for availableCredit at which the
   * creditStatus attribute in the AccountBalance resource indicates that
   * available credit is low.
   */
  sl_xsd_acc_unit_t           lowCreditWarningLevel;
  /**
   * Boolean indicating whether the lowCreditWarningLevel is included in the
   * prepayment object.
   */
  bool                        lowCreditWarningLevelExists;
  /**
   * LowEmergencyCreditWarningLevel is the set point for emergencyCredit at
   * which the creditStatus attribute in the AccountBalance resource indicates
   * that emergencycredit is low.
   */
  sl_xsd_acc_unit_t           lowEmergCreditWarningLevel;
  /**
   * Boolean indicating whether the lowEmergCreditWarningLevel is included in the
   * prepayment object.
   */
  bool                        lowEmergCreditWarningLevelExists;
  /**
   * PrepayMode specifies whether the given prepayment instance is operating in
   * Credit, Central Wallet, ESI, or Local prepayment mode. The Credit mode
   * indicates that prepayment is not presently in effect.
   */
  sl_xsd_prepay_mode_type_t   prepayMode;
  /**
   * Usage Point Resource ID specifying the usage point instance to include.
   */
  u16_t                       uptId;
  /**
   * Boolean indicating whether the usage point link should be included in the
   * prepayment object. If so it uses the uptId instance.
   */
  bool                        uptIdExists;
  /**
   * Number of usage points included as part of the prepayment resource. These
   * are the usage points whose energy use is paid through the prepayment resource.
   */
  u8_t                        numUsagePoints;
  /**
   * Usage points associated with the prepayment resource. These are the usage
   * points whose energy use is paid through the prepayment resource.
   */
  sl_xsd_usage_point_t        upt[SL_XSD_PREP_USAGPOIN_MAX];
} sl_ppy_server_create_ppy_req;

/******************************************************************************/
/**
 * \struct sl_ppy_server_create_ppy_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_PPY_X (Prepayment Resource or PPY).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created PPY. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_ppy_server_create_ppy_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_ppy_server_create_ppy_cnf
 */
typedef sl_server_obj_cnf_t sl_ppy_server_create_ppy_cnf;


/******************************************************************************/
/**
 * \struct sl_ppy_server_store_ab_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Account Balance
 * Resource (AB) within the Prepayment Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_ppy_server_create_ab_cnf.
 *
 * The ref field of the sl_ppy_server_store_ab_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_AB\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 *
 * Dependencies: The parent PPY must be created before creating this AB.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * AvailableCredit shows the balance of the sum of credits minus the sum of charges.
   * In a Central Wallet mode this value may be passed down to the Prepayment server
   * via an out-of-band mechanism. In Local or ESI modes, this value may be calculated
   * based upon summation of CreditRegister transactions minus consumption charges
   * calculated using Metering (and possibly Pricing) function set data.
   * This value may be negative; for instance, if disconnection is prevented due to
   * a Supply Interruption Override.
   */
  sl_xsd_acc_unit_t    availCredit;
  /**
   * CreditStatus identifies whether the present value of availableCredit is considered
   *  OK, low, exhausted, or negative.
   */
  sl_xsd_cred_stat_t   creditStatus;
  /**
   * Indicates whether creditStatus is included in the credit register entity.
   */
  bool                 creditStatusExists;
  /**
   * EmergencyCredit is the amount of credit still available for the given service or
   * commodity prepayment instance. If both availableCredit and emergyCredit are exhausted,
   * the prepayment instance typically will disconnect service.
   */
  sl_xsd_acc_unit_t    emergCredit;
  /**
   * Indicates whether the emergency credit amount is included in the credit register entity.
   */
  bool                 emergCreditExists;
  /**
   * EmergencyCreditStatus identifies whether the present value of emergencyCredit is
   * considered OK, low, exhausted, or negative.
   */
  sl_xsd_cred_stat_t   emergCreditStatus;
  /**
   * Indicates whether the emergencyCreditStatus is included in the credit register entity.
   */
  bool                 emergCreditStatusExists;
} sl_ppy_server_store_ab_req;


/******************************************************************************/
/**
 * \struct sl_ppy_server_create_ab_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_PPY_X_AB (Account Balance Resource or AB).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created AB. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_ppy_server_create_ab_cnf will be defined as
 * follows: \n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_AB\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 *
 * Dependencies: none.
 *
 * typedef sl_server_obj_cnf_t sl_ppy_server_create_ab_cnf
 */
typedef sl_server_obj_cnf_t sl_ppy_server_create_ab_cnf;

/******************************************************************************/
/**
 * \struct sl_ppy_server_store_os_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Operation Status
 * Resource (OS) within the Prepayment Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_ppy_server_create_os_cnf.
 *
 * The ref field of the sl_ppy_server_store_os_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_OS\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 *
 * Dependencies: The parent PPY must be created before creating this OS.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t         ref;
  /**
   * CreditTypeChange is used to define a pending change of creditTypeInUse,
   * which will activate at a specified time.
   */
  sl_xsd_cred_type_t          credTypeChangeCredType;
  /**
   * CreditTypeChange is used to define a pending change of creditTypeInUse,
   * which will activate at a specified time.
   */
  sl_xsd_time_type_t          credTypeChangeStartTime;
  /**
   * Indicates whether the credit type change is included in this operational status.
   */
  bool                        credTypeChangeExists;
  /**
   * CreditTypeInUse identifies whether the present mode of operation is
   * consuming regular credit or emergency credit.
   */
  sl_xsd_cred_type_t          credTypeInUse;
  /**
   * Indicates whether the credit type in use is included in this operational status.
   */
  bool                        credTypeInUseExists;
  /**
   * ServiceChange is used to define a pending change of serviceStatus, which will
   * activate at a specified time.
   */
  sl_xsd_serv_stat_t          servChangeNewServ;
  /**
   * ServiceChange is used to define a pending change of serviceStatus, which will
   * activate at a specified time.
   */
  sl_xsd_time_type_t          servChangeStartTime;
  /**
   * Indicates whether the service change is included in this operational status.
   */
  bool                        servChangeExists;
  /**
   * ServiceStatus identifies whether the service is connected or disconnected,
   * or armed for connection or disconnection.
   */
  sl_xsd_serv_stat_t          serviceStatus;
} sl_ppy_server_store_os_req;

/******************************************************************************/
/**
 * \struct sl_ppy_server_create_os_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_PPY_X_OS (Operation Status Resource or OS).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created OS. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_ppy_server_create_os_cnf will be defined as
 * follows: \n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_OS\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 *
 * Dependencies: none.
 *
 * typedef sl_server_obj_cnf_t sl_ppy_server_create_os_cnf
 */
typedef sl_server_obj_cnf_t sl_ppy_server_create_os_cnf;

/******************************************************************************/
/**
 * \struct sl_ppy_server_create_cr_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Credit Register
 * Resource (CR) within the Prepayment Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_ppy_server_create_cr_cnf.
 *
 * The ref field of the sl_ppy_server_create_cr_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_CR_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 *
 * Dependencies: The parent PPY must be created before creating this CR.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Unique MRID for this CR of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t                 mrId[SL_XSD_MRID_LEN];
  /**
   * Array providing a description of the CR, with max length of
   * \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                 description[SL_XSD_DESCRIPTION_LEN];
  /**
   * The amount of credit being added by a particular CreditRegister transaction.
   * Negative values indicate that credit is being subtracted.
   */
  sl_xsd_acc_unit_t    creditAmount;
  /**
   * Indicates whether the credit transaction applies to regular or emergency credit.
   */
  sl_xsd_cred_type_t   creditType;
  /**
   * Indicates whether the creditType is included in the credit register.
   */
  bool                 creditTypeExists;
  /**
   * EffectiveTime identifies the time at which the credit transaction goes into effect.
   * For credit addition transactions this is typically the moment at which the transaction
   * takes place. For credit subtraction transactions (e.g., non-fuel debt recovery
   * transactions initiated from a back-haul or ESI) this may be a future time at which
   * credit is deducted.
   */
  sl_xsd_time_type_t   effectiveTime;
  /**
   * Token is security data that authenticates the legitimacy of the transaction.
   * Must be null terminated.
   */
  char                 token[SL_XSD_TOKEN_MAX_LEN];
} sl_ppy_server_create_cr_req;

/******************************************************************************/
/**
 * \struct sl_ppy_server_schedule_cr_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_PPY_X_CR_X (Credit Register Resource or CR).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created CR. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_ppy_server_create_cr_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_CR_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 * ref.instanceIDs[2] = The unique ID for the CR\n
 *
 * Dependencies: none.
 *
 * typedef sl_server_obj_cnf_t sl_ppy_server_schedule_cr_cnf
 */
typedef sl_server_obj_cnf_t sl_ppy_server_schedule_cr_cnf;

/******************************************************************************/
/**
 * \struct sl_ppy_server_create_si_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Supply Interruption
 * Override Resource (SI) within the Prepayment Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_ppy_server_create_si_cnf.
 *
 * The ref field of the sl_ppy_server_create_si_req must be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_SI_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 *
 * Dependencies: The parent PPY must be created before creating this SI.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Start time associated with the supply interruption entity.
   */
  sl_xsd_time_type_t   startTime;
  /**
   * Duration of the interval, in seconds.
   */
  u32_t                duration;
  /**
   * Description of the SI resource, string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_ppy_server_create_si_req;

/******************************************************************************/
/**
 * \struct sl_ppy_server_schedule_si_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_PPY_X_SI_X (Supply Interruption Override Resource or SI).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created SI. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_ppy_server_create_cr_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned: \n
 * ref.objId          = \ref SL_OBJ_ID_X_PPY_X_SI_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the PPY\n
 * ref.instanceIDs[2] = The unique ID for the SI\n
 *
 * Dependencies: none.
 *
 * typedef sl_server_obj_cnf_t sl_ppy_server_schedule_si_cnf
 */
typedef sl_server_obj_cnf_t sl_ppy_server_schedule_si_cnf;

/** \endcond */

// -------------------- Price -------------------

/**
 * \defgroup PRICE_GROUP Price Definitions and Structures
 * This section contains definitions and structures used by the Pricing function set.
 */
/** \addtogroup PRICE_GROUP
 * @{ */

/**
 * \defgroup PRICE_GROUP_DEFINES Price Definitions
 * This section contains definitions used by the Pricing function set.
 */
/** \addtogroup PRICE_GROUP_DEFINES
 * @{ */

  /**
   * Used by the Pricing Function Set (PRICE). This defines the maximum number of
   * cost elements that can be included in a Consumption Tariff Interval. This
   * value may be configured at build time.
   */
#define SL_PRICE_MAX_COST_ELE (5)

/**
 * Used by the Pricing Function Set. This defines the maximum number of Tariff
 * Profiles (TPs) that may be returned in a single mail message.
 */
#define SL_PRICE_CLIENT_MAX_NUM_TPS (5)

/**
 * Used by the Pricing Function Set. This defines the maximum number of Rate
 * Components (RCs) that may be returned in a single mail message.
 */
#define SL_PRICE_CLIENT_MAX_NUM_RCS (1)

/**
 * Used by the Pricing Function Set. This defines the maximum number of Time
 * Tariff Intervals (TTIs) that may be returned in a single mail message.
 */
#define SL_PRICE_CLIENT_MAX_NUM_TTIS (5)

/**
 * Used by the Pricing Function Set. This defines the maximum number of Consumption
 * Tariff Intervals (CTIs) that may be returned in a single mail message.
 */
#define SL_PRICE_CLIENT_MAX_NUM_CTIS (5)

/**
 * This defines the default polling rate for Price Time Tariff Interval events in
 * seconds.  This value is used with event handling only.
 */
#define SL_PRICE_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC  (5*60)

/** @} */
// end addtogroup PRICE_GROUP_DEFINES

/**
 * \defgroup PRICE_GROUP_STRUCTS PRICE Structures
 * This section contains structures used by the Pricing function set.
 */
/** \addtogroup PRICE_GROUP_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_price_cti_t
 * This structure contains Pricing Consumption Tariff Interval (CTI) data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * The lowest level of consumption that defines the starting point of this
   * consumption step or block. Thresholds start at zero for each billing period.
   * If specified, the first CTI.startValue for a TTI instance SHALL begin at "0."
   * Subsequent CTI.startValue elements SHALL be incremented from the previous one.
   */
  u64_t                    startValue;
  /**
   * The charge for this rate component, per unit of measure defined by the
   * associated ReadingType, in currency specified in the associated TP.
   */
  i32_t                    price;
  /**
   * Boolean indicating whether the optional price element is included in
   * this CTI.
   */
  bool                     priceExists;
  /**
   * Indicates the consumption block related to the reading. If not specified,
   * is assumed to be "0 - N/A".
   */
  sl_xsd_cons_block_type_t consumptionBlock;
  /**
   * Number of cost elements included in the CTI, max of \ref SL_PRICE_MAX_COST_ELE.
   */
  u8_t                     numCost;
  /**
   * Array of cost elements associated with this CTI.
   */
  sl_xsd_cost_t            cost[SL_PRICE_MAX_COST_ELE];
} sl_price_cti_t;

/******************************************************************************/
/**
 * \struct sl_price_server_rc_t
 * This structure contains Pricing Rate Component (RC) data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Array providing a description of the RC, with max
   * length of \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char               description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Specifies the maximum flow rate (e.g. kW for electricity) for which this RC applies,
   * for the usage point and given rate / tariff. In combination with startLimit, allows
   * a service provider to define the demand or output characteristics for the particular
   * tariff design. If a server includes the startLimit attribute, then it SHALL also include
   * endLimit attribute.
   */
  sl_xsd_unit_val_t  endLimit;
  /**
   * Unique MRID for this RC of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t               mrId[SL_XSD_MRID_LEN];
  /**
   * Specifies the roles that this usage point has been assigned.
   */
  sl_xsd_role_flag_t roleFlag;
  /**
   * Specifies all of the instance IDs necessary to reference a reading type resource.  The first element refers
   * to the group ID.
   */
  u16_t               rtId[SL_OBJ_TOPLEVEL_NUM_INSTANCE_ID];
  /**
   * Specifies the minimum flow rate (e.g., kW for electricity) for which this RC applies,
   * for the usage point and given rate / tariff. In combination with endLimit, allows a
   * service provider to define the demand or output characteristics for the particular
   * tariff design. If a server includes the startLimit attribute, then it SHALL also include
   * endLimit attribute.
   */
  sl_xsd_unit_val_t  startLimit;
} sl_price_server_rc_t;

/******************************************************************************/
/**
 * \struct sl_price_tp_t
 * This structure contains Pricing Tariff Profile (TP) data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * The currency code indicating the currency for this TariffProfile.
   */
  sl_xsd_curr_code_t    currency;
  /**
   * Variable length array providing a description of the DRP, with max
   * length of \ref SL_XSD_DESCRIPTION_LEN. Character string must be null terminated.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
  /**
   * Unique MRID for this TP of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the power of ten multiplier for the price attribute.
   */
  sl_xsd_ptm_type_t     pricePowerOfTenMult;
  /**
   * Indicates the relative primacy of the provider of this program.
   */
  sl_xsd_primacy_type_t primacy;
  /**
   * The rate code for this tariff profile. It is provided by the
   * Pricing service provider per its internal business needs and
   * practices and provides a method to identify the specific rate
   * code for the TariffProfile instance.  This would typically not
   * be communicated to the user except to facilitate troubleshooting
   * due to its service provider-specific technical nature.
   */
  char                  rateCode[SL_XSD_RATECODE_LEN];
  /**
   * The kind of service provided by this usage point.
   */
  sl_xsd_service_t      serviceKind;
} sl_price_tp_t;

/******************************************************************************/
/**
 * \struct sl_price_tti_t
 * This structure contains Pricing Time Tariff Interval data.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Contains details for this randomizable event such as start, duration,
   * response required, etc.
   */
  sl_cmn_rand_event_t  randEvent;
  /**
   * Character array that allows the server to provide a textual explanation
   * of the status. Array is of max length \ref SL_XSD_REASON_LEN. Character string
   * must be null terminated.
   */
  char                 reason[SL_XSD_REASON_LEN];
  /**
   * Indicates the time of use tier related to the reading. If not specified,
   * is assumed to be "0 - N/A".
   */
  sl_xsd_tou_type_t    touTier;
} sl_price_tti_t;

/******************************************************************************/
/**
 * \struct sl_price_client_tti_active_info_t
 * This structure contains information about a TTI which is being acted
 * upon by the PRICE client. This structure will only be valid if active
 * event handling is enabled.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the current client status of the event. This is the same status
   * that would be sent to the server in a response.
   */
  sl_xsd_resp_status_type_t eventRespStatus;
  /**
   * The length of time the event is active following the start time. Note that any
   * start time or end time randomization is calculated into this value. This is
   * the ACTUAL duration employed by the SL client.
   */
  u32_t                     randomizedDuration;
  /**
   * The time at which the event starts. Note that any start time randomization is
   * calculated into this value. This is the ACTUAL start time employed by the
   * SL client.
   */
  sl_xsd_time_type_t        randomizedStart;
} sl_price_client_tti_active_info_t;

/******************************************************************************/
/**
 * \struct sl_price_client_list_rc_t
 * This structure contains information about an RC which is passed as part
 * of the list handling interface \ref sl_price_client_rc_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * TP information.
   */
  sl_cmn_rcomp_t                       rc;
  /**
   * The unique MRID for the TP that this RC is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                                tpMrId[SL_XSD_MRID_LEN];
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                     version;
} sl_price_client_list_rc_t;

/******************************************************************************/
/**
 * \struct sl_price_client_list_tp_t
 * This structure contains information about a TP which is passed as part
 * of the list handling interface \ref sl_price_client_tp_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * TP information.
   */
  sl_price_tp_t                        tp;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                     version;
} sl_price_client_list_tp_t;

/******************************************************************************/
/**
 * \struct sl_price_client_list_tti_t
 * This structure contains information about a TTI which is passed as part
 * of the list handling interface \ref sl_price_client_tti_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the TTI (i.e.,
   * information calculated or maintained by the PRICE Client as part of active
   * handling).
   */
  sl_price_client_tti_active_info_t activeInfo;
  /**
   * Boolean indicating whether the activeInfo structure contains valid information.
   * In the case that active handling is disabled, this field will always be set to
   * FALSE. In the case that active handling is enabled, this field may or may not
   * be present depending on whether the PRICE Client is acting on it.
   */
  bool                             activeInfoExists;
  /**
   * The unique MRID for the RC that this TTI is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                             rcMrId[SL_XSD_MRID_LEN];
  /**
   * Structure containing TTI data and event information.
   */
  sl_price_tti_t                    tti;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_price_client_list_tti_t;

/******************************************************************************/
/**
 * \struct sl_price_client_list_cti_t
 * This structure contains information about a CTI which is passed as part
 * of the list handling interface \ref sl_price_client_cti_list_ind.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * CTI Information
   */
  sl_price_cti_t           cti;
  /**
   * Unique MRID for the associated TTI of length \ref SL_XSD_MRID_LEN.
   */
  u8_t                     ttiMrId[SL_XSD_MRID_LEN];
} sl_price_client_list_cti_t;

/** @} */
// end addtogroup PRICE_GROUP_STRUCTS

/**
 * \defgroup PRICE_GROUP_MAIL_STRUCTS Price Mail Structures
 * This section contains mail structures used by the Pricing function set.
 */
/** \addtogroup PRICE_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_price_server_create_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Reading
 * Type (RT) within the PRICE Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_price_server_create_rtype_cnf.
 *
 * The ref field of the sl_price_server_create_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_create_rtype_req sl_price_server_create_rtype_req
 */
typedef sl_cmn_server_create_rtype_req sl_price_server_create_rtype_req;

/******************************************************************************/
/**
 * \struct sl_price_server_create_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created RT. It uses the common structure
 *  \ref sl_cmn_server_create_rtype_cnf.
 *
 * The ref field of the sl_price_server_create_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_create_rtype_cnf sl_price_server_create_rtype_cnf
 *
 */
typedef sl_cmn_server_create_rtype_cnf sl_price_server_create_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Reading
 * Type (RT) within the PRICE Server.  Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_price_server_delete_rtype_cnf.
 *
 * The ref field of the sl_price_server_delete_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: The \ref sl_price_server_delete_rtype_cnf may only be sent after an
 * \ref sl_price_server_create_rtype_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_cmn_server_delete_rtype_req sl_price_server_delete_rtype_req
*/
typedef sl_cmn_server_delete_rtype_req sl_price_server_delete_rtype_req;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT)
 * The confirmation provides a status of the operation and contains
 * the ref structure for the deleted RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_delete_rtype_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_delete_rtype_cnf sl_price_server_delete_rtype_cnf
*/
typedef sl_cmn_server_delete_rtype_cnf sl_price_server_delete_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_store_rtype_req
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_REQ mail message.
 *
 * This request is used by the Customer Application to overwrite an existing
 * Reading Type (RT) within the server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_price_server_store_rtype_cnf.
 *
 * The ref field of the sl_price_server_store_rtype_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_store_rtype_req sl_price_server_store_rtype_req
 *
 */
typedef sl_cmn_server_store_rtype_req sl_price_server_store_rtype_req;

/******************************************************************************/
/**
 * \struct sl_price_server_store_rtype_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_STORE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_STORE_REQ mail
 * message to update a \ref SL_OBJ_ID_X_RT_X (Reading Type or RT).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the updated RT. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_store_rtype_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RT_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RT\n
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_server_store_rtype_cnf sl_price_server_store_rtype_cnf
 *
 */
typedef sl_cmn_server_store_rtype_cnf sl_price_server_store_rtype_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_create_tp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Tariff
 * Profile (TP) within the PRICE Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using the structure
 * \ref sl_price_server_create_tp_cnf.
 *
 * The ref field of the sl_price_server_create_tp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Tariff Profile Information.
   */
  sl_price_tp_t         tp;
} sl_price_server_create_tp_req;

/******************************************************************************/
/**
 * \struct sl_price_server_create_tp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_TP_X (Tariff Profile or TP).
 * The confirmation provides a status of the operation and contains
 * the ref structure for the created TP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_create_tp_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned:\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the TP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_create_tp_cnf
 */
typedef sl_server_obj_cnf_t sl_price_server_create_tp_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_tp_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Tariff
 * Profie (TP) within the PRICE Server. It will also cause all child
 * resources to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_price_server_delete_tp_cnf.
 *
 * The ref field of the sl_price_server_delete_tp_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the TP\n
 *
 * Dependencies: The \ref sl_price_server_delete_tp_req may only be sent after an
 * \ref sl_price_server_create_tp_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_price_server_delete_tp_req
*/
typedef sl_server_obj_ref_t sl_price_server_delete_tp_req;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_tp_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_TP_X (Tariff Profile or
 * TP). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted TP. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_delete_tp_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the TP\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_delete_tp_cnf
*/
typedef sl_server_obj_cnf_t sl_price_server_delete_tp_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_create_rc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Rate Component
 * (RC) within the PRICE Server. This request will trigger the PRICE Server to
 * create the RC. Once the request is handled the SL Task responds with a mail message of
 * \ref SL_SERVER_OBJ_CREATE_CNF using the structure \ref sl_price_server_create_rc_cnf.
 *
 * The ref field of the sl_d_server_create_rc_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 *
 * Dependencies: The sl_price_server_create_rc_req may only be sent after
 * a TP has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t ref;
  /**
   * Rate Component Information
   */
  sl_price_server_rc_t rc;
} sl_price_server_create_rc_req;

/******************************************************************************/
/**
 * \struct sl_price_server_create_rc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_TP_X_RC_X (Rate Component or
 * RC). The confirmation provides a status of the operation
 * and contains the ref structure for the created RC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_create_rc_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X_RC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the TP\n
 * ref.instanceIDs[2] = The unique ID for the RC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_create_rc_cnf
 */
typedef sl_server_obj_cnf_t sl_price_server_create_rc_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_rc_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Rate Component
 * (RC) within the PRICE Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_price_server_delete_rc_cnf.
 *
 * The ref field of the sl_price_server_delete_rc_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X_RC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the RC\n
 *
 * Dependencies: The \ref sl_price_server_delete_rc_req may only be sent after an
 * \ref sl_price_server_create_rc_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_delete_rc_req
*/
typedef sl_server_obj_ref_t sl_price_server_delete_rc_req;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_rc_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_TP_X_RC_X (Rate Component or
 * RC). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted RC. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_delete_rc_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X_RC_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the TP\n
 * ref.instanceIDs[2] = The unique ID for the RC\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_delete_rc_cnf
*/
typedef sl_server_obj_cnf_t sl_price_server_delete_rc_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_create_cti_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Consumption
 * Tariff Interval (CTI) within the PRICE Server. This request will trigger the
 * PRICE Server to create the CTI. Once the request is handled the SL Task
 * responds with a mail message of \ref SL_SERVER_OBJ_CREATE_CNF using the
 * structure \ref sl_price_server_create_cti_cnf.
 *
 * The ref field of the sl_price_server_create_cti_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the parent TTI\n
 *
 * Dependencies: The parent resources (tariff profile, rate component, and
 * time tariff interval) must be created before this request may be sent.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t     ref;
  /**
   * Structure containing the details of the CTI.
   */
  sl_price_cti_t           cti;
} sl_price_server_create_cti_req;

/******************************************************************************/
/**
 * \struct sl_price_server_create_cti_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X (Consumption
 * Tariff Interval or CTI). The confirmation provides a status of the operation
 * and contains the ref structure for the created CTI. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_create_cti_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the parent TTI\n
 * ref.instanceIDs[4] = The unique ID for the CTI\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_create_cti_cnf
 */
typedef sl_server_obj_cnf_t sl_price_server_create_cti_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_cti_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Consumption
 * Tariff Interval (CTI) within the PRICE Server. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_price_server_delete_cti_cnf.
 *
 * The ref field of the sl_price_server_delete_cti_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the parent TTI\n
 * ref.instanceIDs[4] = The unique ID for the CTI\n
 *
 * Dependencies: The \ref sl_price_server_delete_cti_req may only be sent after an
 * \ref sl_price_server_create_cti_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_delete_cti_req
*/
typedef sl_server_obj_ref_t sl_price_server_delete_cti_req;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_cti_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X (Consumption Tariff
 * Interval or CTI). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted CTI. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * ref.objId          = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X_CTI_X\n
 * ref.numInstanceIDs = 5\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the parent TTI\n
 * ref.instanceIDs[4] = The unique ID for the CTI\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_delete_cti_cnf
*/
typedef sl_server_obj_cnf_t sl_price_server_delete_cti_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_create_tti_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to create a new Time
 * Tariff Interval (TTI) within the PRICE Server. This request will trigger the
 * PRICE Server to create the TTI and to start the associated timers and other
 * handling for the TTI. Once the request is handled the SL Task
 * responds with a mail message of \ref SL_SERVER_OBJ_CREATE_CNF using the
 * structure \ref sl_price_server_create_tti_cnf.
 *
 * The ref field of the sl_price_server_create_tti_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * ref.numInstanceIDs = 3\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 *
 * Dependencies: The parent resources (tariff profile and rate component)
 * must be created before this request may be sent.
 */
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * If TRUE, indicates to the SL server that the creation time
   * included should be used to specify the resource creation time. If
   * FALSE, indicates to the SL server to use the current time
   * as the creation time.
   */
  bool                     creationTimeExists;
  /**
   * Indicates which response set group should be used for client responses to this event.
   */
  sl_obj_instance_id_t     respSetGroupId;
  /**
   * Indicates which response set should be used for client responses to this event.
   */
  u16_t                    respSetId;
  /**
   * Structure containing the details of the TTI, including event specific details
   * such as start and duration.
   */
  sl_price_tti_t            tti;
} sl_price_server_create_tti_req;

/******************************************************************************/
/**
 * \struct sl_price_server_create_tti_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ mail
 * message to create a \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X (Time Tariff Interavl or
 * TTI). The confirmation provides a status of the operation
 * and contains the ref structure for the created TTI. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_create_tti_cnf will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the TTI\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_create_tti_cnf
*/
typedef sl_server_obj_cnf_t sl_price_server_create_tti_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_cancel_tti_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_REQ mail message.
 *
 * This request is used by the Customer Application to immediately cancel an
 * existing TTI (Time Tariff Interval) within the PRICE Server. Once the request is handled
 * the SL Task responds with a mail message of \ref SL_SERVER_OBJ_CANCEL_CNF using
 * the structure \ref sl_price_server_cancel_tti_cnf.
 *
 * The ref field of the sl_price_server_cancel_tti_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the TTI\n
 *
 * Dependencies: The sl_price_server_cancel_tti_req may only be sent after
 * a TTI has been successfully created by using \ref SL_SERVER_OBJ_CREATE_REQ.
*/
typedef struct {
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t  ref;
  /**
   * Indicates whether the client needs to apply randomization to the
   * cancel time.
   */
  bool          randomize;
  /**
   * Variable length array that allows the server to provide a textual
   * explanation of the status. Array is of max length SL_XSD_REASON_LEN.
   * Character string must be null terminated.
   */
  char          reason[SL_XSD_REASON_LEN];
} sl_price_server_cancel_tti_req;


/******************************************************************************/
/**
 * \struct sl_price_server_cancel_tti_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CANCEL_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CANCEL_REQ
 * message to cancel a \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X (Time Tariff Interval
 * or TTI) object. The confirmation provides a status of the operation and
 * contains the ref structure of the canceled TTI. It uses the generic cancel
 * confirmation structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the SL_OBJ_ID_X_TP_X_RC_X_TTI_X will be defined as
 * follows if the action is successful. If the action is not successful the
 * ref structure passed in the request will be returned.\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the TTI\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_cancel_tti_cnf
*/
typedef sl_server_obj_cnf_t sl_price_server_cancel_tti_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_tti_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Time Tariff
 * Interval (TTI) within the PRICE Server. It will also delete the active TTI if
 * there is one associated with this TTI. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_price_server_delete_tti_cnf.
 *
 * The ref field of the sl_price_server_delete_tti_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the TTI\n
 *
 * Dependencies: The \ref sl_price_server_delete_tti_req may only be sent after an
 * \ref sl_price_server_create_tti_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_delete_tti_req
*/
typedef sl_server_obj_ref_t sl_price_server_delete_tti_req;

/******************************************************************************/
/**
 * \struct sl_price_server_delete_tti_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X (Time Tariff Interval or
 * TTI). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted TTI. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_price_server_delete_tti_cnf will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the TTI\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_price_server_delete_tti_cnf
*/
typedef sl_server_obj_cnf_t sl_price_server_delete_tti_cnf;

/******************************************************************************/
/**
 * \struct sl_price_server_event_status_ind
 * This indication is sent to the Customer Server application from the Price
 * server to indicate a change in the TTI event status. This is an unsolicited
 * message sent directly to the Application Task. It uses the generic
 * event status indication structure \ref sl_server_obj_event_status_ind_t.
 *
 * The ref field of the sl_price_server_delete_tti_cnf will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_TP_X_RC_X_TTI_X\n
 * ref.numInstanceIDs = 4\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the parent TP\n
 * ref.instanceIDs[2] = The unique ID for the parent RC\n
 * ref.instanceIDs[3] = The unique ID for the TTI\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_event_status_ind_t sl_price_server_event_status_ind
*/
typedef sl_server_obj_event_status_ind_t sl_price_server_event_status_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the PRICE Client to indicate that a new PRICE server has been found. Note
 * that multiple indications may be sent if there are multiple servers and/or
 * sources of PRICE information available.
 *
 * The client application may use this indication as a trigger to start
 * requesting PRICE information from the PRICE client. The included server/source
 * information is used to request a TP list via the \ref sl_price_client_get_tp_list_req.
 * If PRICE information is requested before this indication is sent, the PRICE
 * client will respond with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_price_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_price_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_set_event_programs_req
 *
 * This request is used by the Customer Application to request a list of Rate
 * Components to be used for event processing.  The \ref SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_CNF
 * will be sent as an acknowledgment of the request.  If the request is successful
 * a \ref SL_PRICE_CLIENT_EVENT_PROGRAMS_IND will be sent after the confirm to
 * indicate the change to the Price event list.
 *
 * Dependencies: The client must receive the RC mrIds for the requested RCs
 *               from the \ref SL_PRICE_CLIENT_RC_IND.
 *
 * typedef sl_cmn_client_set_event_programs_req_t sl_price_client_set_event_programs_req
 */
typedef sl_cmn_client_set_event_programs_req_t sl_price_client_set_event_programs_req;

/******************************************************************************/
/**
 * \struct sl_price_client_set_event_programs_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_REQ. It contains a status field
 * which indicates success if the request is being handled, or an error status
 * in case the request is not being handled.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_programs_cnf_t sl_price_client_set_event_programs_cnf
*/
typedef sl_cmn_client_set_event_programs_cnf_t sl_price_client_set_event_programs_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_event_programs_ind
 *
 * This indication is sent when there is a change to the list of Rate Components that
 * are being used for event processing.
 *
 * Dependencies: None
 *
 * typedef sl_cmn_client_event_programs_ind_t sl_price_client_event_programs_ind
 */
typedef sl_cmn_client_event_programs_ind_t sl_price_client_event_programs_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_set_event_roots_req
 *
 * This request is used by the Customer Application to request a list of Price servers
 * to be used for event processing, up to a maximum of \ref SL_CMN_CLIENT_MAX_NUM_EVENT_ROOTS.
 * The \ref SL_PRICE_CLIENT_SET_EVENT_ROOTS_CNF will be sent as an acknowledgment
 * of this request.
 *
 * Note that the client app is responsible for meeting the following requirement
 * defined in the SEP2.0 specification:
 *   "When devices are registered to a Pricing server, they SHALL not act upon
 *    any "public" pricing servers that are present in the HAN or become available."
 *
 * Also note that the client app may not select a root(server/source) which is
 * not indicated to be time synced in \ref sl_price_client_server_ind.
 *
 * Dependencies: The client app must receive indication of available Price servers
 *               from \ref sl_price_client_server_ind.
 *
 * typedef sl_cmn_client_set_event_roots_req_t sl_price_client_set_event_roots_req
 */
typedef sl_cmn_client_set_event_roots_req_t sl_price_client_set_event_roots_req;

/******************************************************************************/
/**
 * \struct sl_price_client_set_event_roots_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_PRICE_CLIENT_SET_EVENT_ROOTS_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_roots_cnf_t sl_price_client_set_event_roots_cnf
*/
typedef sl_cmn_client_set_event_roots_cnf_t sl_price_client_set_event_roots_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_set_event_poll_rate_req
 * This request is used by the Customer Application to change the Services Layer
 * polling rate for Price Time Tariff Interval events.  The default event polling
 * rate for Price is \ref SL_PRICE_CLIENT_DEFAULT_EVENT_POLL_RATE_SEC.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_req_t sl_price_client_set_event_poll_rate_req
 */
typedef sl_cmn_client_set_event_poll_rate_req_t sl_price_client_set_event_poll_rate_req;

/******************************************************************************/
/**
 * \struct sl_price_client_set_event_poll_rate_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_PRICE_CLIENT_SET_EVENT_POLL_RATE_REQ. It contains a status field
 * which indicates success or an error status in case the request failed.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_price_client_set_event_poll_rate_cnf
 */
typedef sl_cmn_client_set_event_poll_rate_cnf_t sl_price_client_set_event_poll_rate_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_event_roots_ind
 *
 * This indication is sent to the Customer Application when there is a change in
 * the list of roots that are used for event processing.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_event_roots_ind_t sl_price_client_event_roots_ind;
 */
typedef sl_cmn_client_event_roots_ind_t sl_price_client_event_roots_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_tp_ind
 * This indication is sent to the Customer Client application from the Pricing
 * client to indicate that a new Tariff Profile (TP) has been received. This is
 * an unsolicited messages sent directly to the Application Task. If more than
 * this TP is needed, the client may send the \ref SL_PRICE_CLIENT_GET_TP_LIST_REQ
 * to request more.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether this indication contains valid TP information.
   * If false, the /ref tp field does not contain valid information.
   */
  bool                                tpExists;
  /**
   * TP information.
   */
  sl_price_tp_t                       tp;
  /**
   * Server and source information associated with this TP.
   */
  sl_cmn_client_server_source_info_t  serverSourceInfo;
  /**
   * Indicates the status of the current program (received/deleted/server lost).
   */
  sl_cmn_prog_status_t                status;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                    version;
} sl_price_client_tp_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_rc_ind
 * This indication is sent to the Customer Client application from the Pricing
 * client to indicate that a new Rate Component (RC) has been received. This is
 * an unsolicited messages sent directly to the Application Task.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether this indication contains valid RC information.
   * If false, the /ref rc field does not contain valid information.
   */
  bool                 rcExists;
  /**
   * Rate Component Information
   */
  sl_cmn_rcomp_t       rc;
  /**
   * Server and source information associated with this RC.
   */
  sl_cmn_client_server_source_info_t  serverSourceInfo;
  /**
   * The unique MRID for the TP that this RC is associated with, of length
   * \ref SL_XSD_MRID_LEN.
   */
  u8_t                 tpMrId[SL_XSD_MRID_LEN];
  /**
   * Indicates the status of the current program (received/deleted/server lost).
   */
  sl_cmn_prog_status_t status;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t     version;
} sl_price_client_rc_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_tti_ind
 * This indication is sent to the Customer Client application from the Pricing
 * client to indicate that a new TTI has been received. This is an unsolicited
 * messages sent directly to the Application Task.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Structure containing information about the active handling of the TTI (i.e.,
   * information calculated or maintained by the PRICE Client as part of active
   * handling).
   */
  sl_price_client_tti_active_info_t activeInfo;
  /**
   * The unique MRID for the RC that this TTI is associated with, of length
   * SL_XSD_MRID_LEN.
   */
  u8_t                             rcMrId[SL_XSD_MRID_LEN];
  /**
   * Structure containing TTI data and event information.
   */
  sl_price_tti_t                   tti;
  /**
   * Current status of the event as shown by the server.
   */
  sl_xsd_event_curr_status_t       eventStatusCurrStatus;
  /**
   * Time at which the event status was last modified on the server.
   */
  sl_xsd_time_type_t               eventStatusDateTime;
  /**
   * Information used to provide response information back to the server. This
   * information will be needed by the Customer Application if it uses the
   * \ref sl_resp_client_send_resp_req interface.
   */
  sl_cmn_client_resp_info_t        respInfo;
  /**
   * TDB: Version is not yet supported on the interface. By default it is set
   * to 0.
   */
  sl_xsd_version_t                 version;
} sl_price_client_tti_ind;


/******************************************************************************/
/**
 * \struct sl_price_client_get_tp_list_req
 * This request is used by the Customer Application to request some number
 * of Tariff Profiles (TPs). The \ref SL_PRICE_CLIENT_GET_TP_LIST_CNF will be sent as an
 * acknowledgment of the request, and the TPs themselves will be sent in
 * the \ref SL_PRICE_CLIENT_TP_LIST_IND message. While the application may request as
 * many TPs as it wants up to 254 (255 is defined as requesting all available TPs)
 * only up to \ref SL_PRICE_CLIENT_MAX_NUM_TPS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_PRICE_CLIENT_GET_TP_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The app client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The\ref  SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Pricing client.
 *
 * typedef sl_cmn_get_list_req_root_t sl_price_client_get_tp_list_req
*/
typedef sl_cmn_get_list_req_root_t sl_price_client_get_tp_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_get_tp_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_PRICE_CLIENT_GET_TP_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_price_client_get_tp_list_cnf
*/
typedef sl_cmn_get_list_cnf_t sl_price_client_get_tp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_tp_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for TPs. Note that until the \ref SL_PRICE_CLIENT_CANCEL_GET_TP_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Pricing client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_tp_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_tp_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_tp_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated TP processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_price_client_cancel_get_tp_list_cnf
*/
typedef sl_cmn_cancel_get_list_cnf_t sl_price_client_cancel_get_tp_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_tp_list_ind
 * This indication is sent in response to the \ref SL_PRICE_CLIENT_GET_TP_LIST_REQ.
 * It will contain some number of DRPs up to \ref SL_PRICE_CLIENT_MAX_NUM_TPS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available TPS have been returned (SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t         results;
  /**
   * List of TPs.
   */
  sl_price_client_list_tp_t list[];  // Variable length up to SL_PRICE_CLIENT_MAX_NUM_TPS
} sl_price_client_tp_list_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_get_rc_list_req
 * This request is used by the Customer Application to request some number
 * of Rate Components (RCs). The \ref SL_PRICE_CLIENT_GET_RC_LIST_CNF will be sent as an
 * acknowledgment of the request, and the RCs themselves will be sent in
 * the \ref SL_PRICE_CLIENT_RC_LIST_IND message. While the application may request as
 * many RCs as it wants up to 254 (255 is defined as requesting all available RCs)
 * only up to \ref SL_PRICE_CLIENT_MAX_NUM_RCS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_PRICE_CLIENT_GET_RC_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The app client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Pricing client.
 *
 * typedef sl_cmn_get_list_req_quantity_t sl_price_client_get_rc_list_req
 */
typedef sl_cmn_get_list_req_quantity_t sl_price_client_get_rc_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_get_rc_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_PRICE_CLIENT_GET_RC_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_price_client_get_rc_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_price_client_get_rc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_rc_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for RCs. Note that until the \ref SL_PRICE_CLIENT_CANCEL_GET_RC_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Pricing client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_rc_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_rc_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_rc_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated RC processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_cancel_get_list_cnf_t sl_price_client_cancel_get_rc_list_cnf
 */
typedef sl_cmn_cancel_get_list_cnf_t sl_price_client_cancel_get_rc_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_rc_list_ind
 * This indication is sent in response to the \ref SL_PRICE_CLIENT_GET_RC_LIST_REQ.
 * It will contain some number of DRPs up to \ref SL_PRICE_CLIENT_MAX_NUM_RCS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available TPS have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t          results;
  /**
   * List of RCs.
   */
  sl_price_client_list_rc_t   list[];  // Variable length up to SL_PRICE_CLIENT_MAX_NUM_RCS
} sl_price_client_rc_list_ind;


/******************************************************************************/
/**
 * \struct sl_price_client_get_tti_list_req
 * This request is used by the Customer Application to request some number
 * of TTIs. The \ref SL_PRICE_CLIENT_GET_TTI_LIST_CNF will be sent as an
 * acknowledgment of the request, and the TTIs themselves will be sent in
 * the \ref SL_PRICE_CLIENT_TTI_LIST_IND message. While the application may request as
 * many TTIs as it wants, only up to \ref SL_PRICE_CLIENT_MAX_NUM_TTIS will be returned
 * in a single indication. Therefore this request may generate multiple indications.
 *
 * Dependencies: The \ref SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Price client. Also, before sending
 * this request the client must either receive the TP and RC information for the
 * requested TTIs from the \ref SL_PRICE_CLIENT_TP_LIST_IND and \ref SL_PRICE_CLIENT_RC_LIST_IND,
 * or the client must receive the RC information from the \ref SL_METER_CLIENT_RC_LIST_IND.
 *
 * typedef sl_cmn_get_list_req_time_t sl_price_client_get_tti_list_req
 */
typedef sl_cmn_get_list_req_time_t sl_price_client_get_tti_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_get_tti_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_PRICE_CLIENT_GET_TTI_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_price_client_get_tti_list_cnf
 */
typedef sl_cmn_get_list_cnf_t  sl_price_client_get_tti_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_tti_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for TTIs. Note that until the \ref SL_PRICE_CLIENT_CANCEL_GET_TTI_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Pricing client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_tti_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_tti_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_tti_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated TTI processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_price_client_cancel_get_tti_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_price_client_cancel_get_tti_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_tti_list_ind
 * This indication is sent in response to the \ref SL_PRICE_CLIENT_GET_TTI_LIST_REQ.
 * It will contain some number of TTIs up to \ref SL_PRICE_CLIENT_MAX_NUM_TTIS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available TTIs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t      results;
  /**
   * List of TTIs.
   */
  sl_price_client_list_tti_t list[];  // Variable length up to SL_PRICE_CLIENT_MAX_NUM_TTIS
} sl_price_client_tti_list_ind;

/******************************************************************************/
/**
 * \struct sl_price_client_get_cti_list_req
 * This request is used by the Customer Application to request some number
 * of Consumption Tariff Intervals (CTIs). The \ref SL_PRICE_CLIENT_GET_CTI_LIST_CNF will be sent as an
 * acknowledgment of the request, and the CTIs themselves will be sent in
 * the \ref SL_PRICE_CLIENT_CTI_LIST_IND message. While the application may request as
 * many CTIs as it wants up to 254 (255 is defined as requesting all available CTIs)
 * only up to \ref SL_PRICE_CLIENT_MAX_NUM_CTIS will be returned in a single indication.
 * Therefore this request may generate multiple indications.
 * The SL task will only handle a single \ref SL_PRICE_CLIENT_GET_CTI_LIST_REQ at a
 * time. If a second request is sent while the first is still in progress, an
 * error of \ref SL_CMN_RC_NOT_ALLOWED will be returned. The app client may cancel
 * the first request, wait for a cancellation confirmation, and then send
 * the second request, or it may wait until handling of the first request is complete.
 *
 * Dependencies: The \ref SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Pricing client.
 *
 * typedef sl_cmn_get_list_req_quantity_t sl_price_client_get_cti_list_req
 */
typedef sl_cmn_get_list_req_quantity_t sl_price_client_get_cti_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_get_cti_list_cnf
 * This confirmation is sent to the Customer Application in response to an
 * \ref SL_PRICE_CLIENT_GET_CTI_LIST_REQ. It contains a transaction ID so the client
 * app can map it to the request. It also contains a status field which indicates
 * success if the request is being handled, or an error status in case the
 * request is not being handled. No indications should be expected by the app
 * client if an error status is returned in the request.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_price_client_get_cti_list_cnf
 */
typedef sl_cmn_get_list_cnf_t  sl_price_client_get_cti_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_cti_list_req
 * This request is used by the Customer Application to cancel an in-progress
 * request for RCs. Note that until the \ref SL_PRICE_CLIENT_CANCEL_GET_CTI_LIST_CNF
 * is received, the client app may still receive indications associated with
 * the original request.
 *
 * Dependencies: The \ref SL_PRICE_CLIENT_SERVER_IND must be received by the client
 * app before this request will be handled by the Pricing client.
 *
 * typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_cti_list_req
 */
typedef sl_cmn_cancel_get_list_req_t sl_price_client_cancel_get_cti_list_req;

/******************************************************************************/
/**
 * \struct sl_price_client_cancel_get_cti_list_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated CTI processing has been stopped.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_get_list_cnf_t sl_price_client_cancel_get_cti_list_cnf
 */
typedef sl_cmn_get_list_cnf_t sl_price_client_cancel_get_cti_list_cnf;

/******************************************************************************/
/**
 * \struct sl_price_client_cti_list_ind
 * This indication is sent in response to the \ref SL_PRICE_CLIENT_GET_CTI_LIST_REQ.
 * It will contain some number of DRPs up to \ref SL_PRICE_CLIENT_MAX_NUM_CTIS. One
 * request can generate multiple indications. Each indication will have the same
 * transaction ID as the request, as well as a status field which indicates
 * whether the request is still being handled (\ref SL_CMN_RC_OPERATION_IN_PROG), or if
 * all the requested or available CTIs have been returned (\ref SL_CMN_RC_OPERATION_DONE). If
 * an error status is returned, the client app should not expect any further
 * indications.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * The results provided in this indication.
   */
  sl_cmn_list_ind_t       results;
  /**
   * List of CTIs.
   */
  sl_price_client_list_cti_t list[];  // Variable length up to SL_PRICE_CLIENT_MAX_NUM_CTIS
} sl_price_client_cti_list_ind;

/** @} */
// end addtogroup PRICE_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup PRICE_GROUP

// -------------------- Response ----------------

/**
 * \defgroup RESP_GROUP Response Definitions and Structures
 * This section contains definitions and structures used by the Response function set.
 */
/** \addtogroup RESP_GROUP
 * @{ */

/**
 * \defgroup RESP_GROUP_TYPES Response Types
 * This section contains types used by the Response function set.
 */
/** \addtogroup RESP_GROUP_TYPES
* @{ */

/******************************************************************************/
/**
 * \defgroup SL_RESP_TYPE_XXX Response Type: sl_resp_type_t (SL_RESP_TYPE_XXX)
 * Specifies the type of response.
 */
/** \addtogroup SL_RESP_TYPE_XXX
* @{ */
/**
 * \var typedef u8_t sl_resp_type_t
 * Acceptable values are SL_RESP_TYPE_XXX.
 */
typedef u8_t sl_resp_type_t;
/** DR Response */
#define SL_RESP_TYPE_DR      (0)
/** Text Message Response */
#define SL_RESP_TYPE_TEXT    (1)
/** Pricing Response */
#define SL_RESP_TYPE_PRICE   (2)
/** DER Response */
#define SL_RESP_TYPE_DER     (3)
/** Flow Reservation Response Response */
#define SL_RESP_TYPE_FLOW    (4)
/** Generic Response, currently used only for DER */
#define SL_RESP_TYPE_GENERIC (5)
/** @} */
// end addtogroup SL_RESP_TYPE_XXX

/** @} */
// end addtogroup RESP_GROUP_TYPES

/**
 * \defgroup RESP_GROUP_STRUCTS Response Structures
 * This section contains structures used by the Response function set.
 */
/** \addtogroup RESP_GROUP_STRUCTS
* @{ */

/******************************************************************************/
/**
 * \struct sl_resp_type_drresp_t
 * This structure contains the data associated with the DR Response.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * Indicates the type of appliance load reduction requested.
   */
  sl_xsd_appliance_load_red_type_t  applianceLoadRed;
  /**
   * Boolean indicating whether or not the targetReduction Type and Value fields
   * are present in the EDC.
   */
  bool                      appliedTargetRedExists;
  /**
   * Threshold value to which a device should reduce its load. Indicates the
   * requested amount of the relevant commodity to be reduced, as defined by the
   * targetReductionType.
   */
  u16_t                     appliedTargetRedValue;
  /**
   * Threshold type to which a device should reduce its load. Indicates the type of
   * reduction requested.
   */
  sl_xsd_unit_type_t        appliedTargetReduType;
  /**
   * Contains the maximum On state duty cycle applied by the end device, as a
   * percentage of time.  The field not present indicates that this field has
   * not been used by the end device.
   */
  u8_t                      dutyCycle;
  /**
   * Boolean indicating whether or not the dutyCycle field is present.
   * Field not present indicates that this field has not been used by the
   * end device.
   */
  bool                      dutyCycleExists;
  /**
   * The value change requested for the cooling offset, in degree C / 10. The
   * value should be added to the normal set point for cooling.
   */
  u8_t                      coolOffset;
  /**
   * The value change requested for the heating offset, in degree C / 10.
   * The value should be subtracted for heating.
   */
  u8_t                      heatOffset;
  /**
   * The value change requested for the load adjustment percentage, in tenths
   * of a percent. The value should be subtracted from the normal setting.
   */
  u8_t                      loadAdjustPercentOffset;
  /**
   * Boolean indicating whether or not the coolOffset field is present.
   * Field not present indicates that this field has not been used by the
   * end device.
   */
  bool                      coolOffsetExists;
  /**
   * Boolean indicating whether or not the heatOffset field is present.
   * Field not present indicates that this field has not been used by the
   * end device.
   */
  bool                      heatOffsetExists;
  /**
   * Boolean indicating whether or not the loadAdjustPercentOffset field is
   * present. Field not present indicates that this field has not
   * been used by the end device.
   */
  bool                      loadAdjustPercentOffsetExists;
  /**
   * Cooling Temperature Set Point / 100 = temperature in degrees Celsius where
   * -273.15C<= temperature <= 327.67C, corresponding to a Cooling Temperature
   * Set Point. The maximum resolution this format allows is 0.01C. The field
   * not present indicates that this field has not been used by the end device.
   */
  u16_t                     coolSetpoint;
  /**
   * Heating Temperature Set Point / 100 = temperature in degrees Celsius where
   * -273.15C <= temperature <= 327.67C, corresponding to a Heating Temperature
   * Set Point. The maximum resolution this format allows is 0.01C. The field
   * not present indicates that this field has not been used by the end device.
   */
  u16_t                     heatSetpoint;
  /**
   * Boolean indicating whether or not the cooling setpoint field is present.
   * Field not present indicates that this field has not been used
   * by the end device.
   */
  bool                      coolSetpointExists;
  /**
   * Boolean indicating whether or not the heating setpoint field is present.
   * Field not present indicates that this field has not been used
   * by the end device.
   */
  bool                      heatSetpointExists;
  /**
   * The overrideDuration attribute provides a duration, in seconds, for which
   * a client device is allowed to override an EDC as contractually agreed upon
   * with a service provider.
   */
  u16_t                     overrideDuration;
  /**
   * Boolean indicating whether or not the override duration field is present.
   * Field not present indicates that this field has not been used
   * by the end device.
   */
  u16_t                     overrideDurationExists;
} sl_resp_type_drresp_t;

/** @} */
// end addtogroup RESP_GROUP_STRUCTS

/**
 * \defgroup RESP_GROUP_MAIL_STRUCTS Response Mail Structures
 * This section contains mail structures used by the Response function set.
 */
/** \addtogroup RESP_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_resp_server_create_resp_set_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This request is used by the Customer Application to to create a response
 * set to be used by clients for posting responses. Once the request is handled
 * the SL Task responds with a mail message of \ref SL_SERVER_OBJ_CREATE_CNF
 * using the structure \ref sl_resp_server_create_resp_set_cnf.
 *
 * The ref field of the sl_d_server_create_rc_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RSPS_X\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None
*/
typedef struct {
  sl_server_obj_ref_t ref;
  /**
   * Unique MRID for this response set of max length \ref SL_XSD_MRID_LEN.
   */
  u8_t                  mrId[SL_XSD_MRID_LEN];
  /**
   * Array providing a description of the response set resource.
   */
  char                  description[SL_XSD_DESCRIPTION_LEN];
} sl_resp_server_create_resp_set_req;

/******************************************************************************/
/**
 * \struct sl_resp_server_create_resp_set_cnf
 * This confirmation indicates that the associated request has been handled
 * and the associated response set has been created. The respId included
 * in the cnf should be used in other requests such as \ref SL_SERVER_OBJ_CREATE_REQ
 * when creating an \ref SL_OBJ_ID_X_DR_X_EDC_X to indicate which response set the
 * EDC should be associated with.
 *
 * Dependencies: None.
*/

typedef sl_server_obj_cnf_t sl_resp_server_create_resp_set_cnf;

/******************************************************************************/
/**
 * \struct sl_resp_server_delete_resp_set_req
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_REQ mail message.
 *
 * This structure is used by the Customer Application to delete a Response Set
 * Resource (RSPS) within the Response Server. It will also cause all child
 * resources to be deleted as well. Once the request is handled
 * the SL Task responds with a \ref SL_SERVER_OBJ_DELETE_CNF using the structure
 * \ref sl_resp_server_delete_resp_set_cnf.
 *
 * The ref field of the SL_OBJ_ID_X_RSPS_X must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RSPS_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RSPS\n
 *
 * Dependencies: The \ref sl_resp_server_delete_resp_set_req may only be sent after an
 * \ref sl_resp_server_create_resp_set_req for that resource has been sent and handled
 * successfully.
 *
 * typedef sl_server_obj_ref_t sl_resp_server_delete_resp_set_req
*/
typedef sl_server_obj_ref_t sl_resp_server_delete_resp_set_req;

/******************************************************************************/
/**
 * \struct sl_resp_server_delete_resp_set_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_DELETE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_DELETE_REQ mail
 * message to delete a \ref SL_OBJ_ID_X_RSPS_X (Response Set or
 * RSPS). The confirmation provides a status of the operation and contains
 * the ref structure for the deleted RSPS. It uses the generic
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_resp_server_delete_resp_set_cnf will be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_RSPS_X\n
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 * ref.instanceIDs[1] = The unique ID for the RSPS\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_resp_server_delete_resp_set_cnf
*/
typedef sl_server_obj_cnf_t sl_resp_server_delete_resp_set_cnf;

/******************************************************************************/
/**
 * \struct sl_resp_server_resp_ind
 * This indication is sent to the Customer Application to indicate that a
 * response has been posted to the server.
 *
 * Dependencies: None
*/
typedef struct {
  /**
   * Unique instance ID of the response.
   */
  u16_t                     respId;
  /**
   * Unique instance ID of the associated response set.
   */
  u16_t                     respSetId;
  /**
   * Creation time associated with the response.
   */
  sl_xsd_time_type_t        creationTime;
  /**
   * boolean indicating whether the creation time is included in the indication.
   */
  bool                      creationTimeExists;
  /**
   * LFDI of the device creating the response.
   */
  u8_t                      endDeviceLFDI[SL_XSD_LFDI_LEN];
  /**
   * Status included in the response.
   */
  sl_xsd_resp_status_type_t status;
  /**
   * Boolean indicating whether the status is valid.
   */
  bool                      statusExists;
  /**
   * MRID of the resource that is the subject of the response.
   */
  u8_t                      subj[SL_XSD_RESP_SUBJ_LEN];
  /**
   * Type of response.
   */
  sl_resp_type_t            type;
  /**
   * In case the type is SL_RESP_TYPE_DR, the drRespData is required.
   */
  sl_resp_type_drresp_t     drRespData;
} sl_resp_server_resp_ind;

/******************************************************************************/
/**
 * \struct sl_resp_client_send_resp_req
 * This request is used by the Customer Application to tell the SL CLient to
 * send a response to the server.
 *
 * Dependencies: None
*/
typedef struct {
  /**
   * Defines server to post response to.
   */
  sl_cmn_server_info_t      serverInfo;
  /**
   * This is the URI to reply to (note that it is assumed to be relative at this point).
   */
  u8_t                      replyToHref[SL_CMN_REPLY_TO_HREF_LEN];
  /**
   * Creation time associated with the response.
   */
  sl_xsd_time_type_t        creationTime;
  /**
   * boolean indicating whether the creation time is included in the request. If it is,
   * that creationTime is used in posting the response. If it is not, the current time of
   * the Client is used as the creationTime for the response.
   */
  bool                      creationTimeExists;
  /**
   * LFDI of the device creating the response. If LFDI is set to all zeroes, the LFDI
   * of this device will be used.
   */
  u8_t                      endDeviceLFDI[SL_XSD_LFDI_LEN];
  /**
   * Status to be included in the response.
   */
  sl_xsd_resp_status_type_t status;
  /**
   * Boolean indicating whether the status is valid and should be included in the response.
   */
  bool                      statusExists;
  /**
   * MRID of the resource that is the subject of the response.
   */
  u8_t                      subj[SL_XSD_RESP_SUBJ_LEN];
  /**
   * Type of response.
   */
  sl_resp_type_t            type;
  /**
   * In case the type is SL_RESP_TYPE_DR, the drRespData is required.
   */
  sl_resp_type_drresp_t     drRespData;
} sl_resp_client_send_resp_req;

/******************************************************************************/
/**
 * \struct sl_resp_client_send_resp_cnf
 * This confirmation is sent to the Customer Application to indicate whether
 * the response was successfully sent to the server or not.
 *
 * Dependencies: None
*/
typedef struct {
  /**
   * LFDI of the device creating the response. If the request LFDI was all zeroes,
   * the confirmation will include the LFDI of this device.
   */
  u8_t           endDeviceLFDI[SL_XSD_LFDI_LEN];
  /**
   * MRID of the resource that is the subject of the response.
   */
  u8_t           subj[SL_XSD_RESP_SUBJ_LEN];
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t    status;
} sl_resp_client_send_resp_cnf;

/** @} */
// end addtogroup RESP_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup RESP_GROUP

/** \cond NOTRELEASED */

// -------------------- SDER ---------------------

/******************************************************************************/
/**
 * \struct sl_sder_services_t
 * This structure contains a boolean for each service that is supported by a
 * particular DER instance.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Boolean indicating whether DER Availability is supported.
   */
  bool                    dera;
  /**
   * Boolean indicating whether SDER Capability is supported.
   */
  bool                    dercap;
  /**
   * Boolean indicating whether DER Settings is supported.
   */
  bool                    dersett;
  /**
   * Boolean indicating whether DER Settings is supported.
   */
  bool                    ders;
} sl_sder_services_t;


/** @} */
// end addtogroup SDER_SDER_GROUP_STRUCTS

/**
 * \defgroup SDER_SDER_GROUP_MAIL_STRUCTS SDER/SDER Mail Structures
 * This section contains mail structures used by the SDER/SDER function sets.
 */
/** \addtogroup SDER_SDER_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_sder_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the SDER Client to indicate that a SDER server has been found.
 *
 * The client application may use this indication as a trigger to start
 * putting SDER information to the server. The included server/source
 * information is used to send DER Settings, DER Availability, DER Capability, and
 * DER Status resources to the server.  If a request is made to send a resource
 * to the SDER server before this indication is sent, the SDER client will respond
 * with a status of \ref SL_CMN_RC_NO_SERVER.
 *
 * Note that although a list of multiple End Device DER resources may exist on the server,
 * the SDER client will only support sending DER Settings, DER Availability, DER
 * Capability, and DER Status to the locations indicated in the first End Device DER
 * resource in the list.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * This structure indicates which services are available as part of this SDER instance.
   * The possible services are DER Settings, DER Availability, DER Capability, and
   * DER Status.
   */
  sl_sder_services_t                  services;
  /**
   * This structure contains the detailed information regarding the server.
   */
  sl_cmn_client_server_ind_t          serverDetails;
} sl_sder_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_sder_client_get_dersett_req
 * This request is used by the client Customer Application to request the Self
 * Device's DERSettings. Once the request is handled the SL Task responds with
 * a \ref SL_SDER_CLIENT_GET_DERSETT_CNF.
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * Server and source information that this information is to be sent to. This set of available
   * servers/sources is provided by the SEP Client in the \ref sl_cmn_client_server_ind_t.
   */
  sl_cmn_client_server_source_info_t   serverSourceInfo;
} sl_sder_client_get_dersett_req;

/******************************************************************************/
/**
 * \struct sl_sder_client_get_dersett_cnf
 * Response to the sl_sder_client_get_dersett_req
 *
 * Dependencies: None.
 */
typedef struct {
  /**
   * transactionId is used to match the confirm message with the original request
   * message.
   */
  u32_t                                transactionId;
  /**
   * The DER Settings information to be sent to the server.
   */
  sl_der_settings_t                    dersett;
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t                          status;
} sl_sder_client_get_dersett_cnf;

/******************************************************************************/
/**
 * \struct sl_sder_server_store_dersett_req
 * This request is used by the Customer Application to store a Distributed
 * Energy Resource (DER) within the SDER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SDER_SERVER_STORE_DERSETT_CNF.
 *
 *The ref field of the sl_sder_server_store_dersett_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_DER_X_DERG
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  sl_server_obj_ref_t   ref;
  sl_der_settings_t     der;
} sl_sder_server_store_dersett_req;

/******************************************************************************/
/**
 * \struct sl_sder_server_store_dersett_cnf
 * This confirmation is sent in response to the \ref SL_SDER_SERVER_STORE_DERSETT_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */

typedef sl_server_obj_cnf_t sl_sder_server_store_dersett_cnf;
/******************************************************************************/
/**
 * \struct sl_sder_server_store_dera_req
 * This request is used by the Customer Application to store a Distributed
 * Energy Resource Availability (DERA) within the SDER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SDER_SERVER_STORE_DERA_CNF.
 *
 *The ref field of the sl_sder_server_store_dera_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_DER_X_DERA
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  sl_server_obj_ref_t   ref;
  sl_dera_t             dera;
} sl_sder_server_store_dera_req;

/******************************************************************************/
/**
 * \struct sl_sder_server_store_dera_cnf
 * This confirmation is sent in response to the \ref SL_SDER_SERVER_STORE_DERA_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */

typedef sl_server_obj_cnf_t sl_sder_server_store_dera_cnf;
/******************************************************************************/
/**
 * \struct sl_sder_server_store_dercap_req
 * This request is used by the Customer Application to store a Distributed
 * Energy Resource Capability (DERCAP) within the SDER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SDER_SERVER_STORE_DERCAP_CNF.
 *
 *The ref field of the sl_sder_server_store_dercap_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_DER_X_DERCAP
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  sl_server_obj_ref_t   ref;
  sl_dercap_t           dercap;
} sl_sder_server_store_dercap_req;

/******************************************************************************/
/**
 * \struct sl_sder_server_store_dercap_cnf
 * This confirmation is sent in response to the \ref SL_SDER_SERVER_STORE_DERCAP_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */

typedef sl_server_obj_cnf_t sl_sder_server_store_dercap_cnf;
/******************************************************************************/
/**
 * \struct sl_sder_server_store_ders_req
 * This request is used by the Customer Application to store a Distributed
 * Energy Resource Status (DERS) within the SDER Server. Once the request is handled
 * the SL Task responds with a \ref SL_SDER_SERVER_STORE_DERS_CNF.
 *
 *The ref field of the sl_sder_server_store_ders_req must be defined as
 * follows:\n
 * ref.objId          = \ref SL_OBJ_ID_X_SDEV_DER_X_DERS
 * ref.numInstanceIDs = 2\n
 * ref.instanceIDs[0] = Group Id or \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 */
typedef struct {
  sl_server_obj_ref_t   ref;
  sl_ders_t             ders;
} sl_sder_server_store_ders_req;

/******************************************************************************/
/**
 * \struct sl_sder_server_store_ders_cnf
 * This confirmation is sent in response to the \ref SL_SDER_SERVER_STORE_DERS_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
 */

typedef sl_server_obj_cnf_t sl_sder_server_store_ders_cnf;

// -------------------- SFILE -------------------

#define SL_XSD_SFILE_FILENAME_LEN               64

#define SL_XSD_SFILE_STATUS_NO_LOAD_IN_PROGRESS 0
#define SL_XSD_SFILE_STATUS_LOAD_IN_PROGESS     1
#define SL_XSD_SFILE_STATUS_LOAD_FAILED         2
#define SL_XSD_SFILE_STATUS_VERIFY_IN_PROGRESS  3
#define SL_XSD_SFILE_STATUS_VERIFY_FAILED       4
#define SL_XSD_SFILE_STATUS_VERIFIED            5
#define SL_XSD_SFILE_STATUS_ACTIVATION_FAILED   6

/******************************************************************************/
/**
 * \struct sl_sfile_server_store_filestat_req
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_REQ mail message.
 *
 * This structure is used by the Customer Application to create a new Self Device (SDEV)
 * File Status Resource (\ref SL_OBJ_ID_X_SDEV_FILE). Once the
 * request is handled the SL Task responds with a \ref SL_SERVER_OBJ_CREATE_CNF using
 * the \ref sl_sfile_server_store_filestat_cnf structure.
 *
 * The ref field of the sl_sfile_server_store_filestat_req must be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_FILE\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 */
typedef struct
{
  /**
   * References the SEP object.
   */
  sl_server_obj_ref_t    ref;
  char          filename[SL_XSD_SFILE_FILENAME_LEN];
  sl_xsd_time_type_t  statusTime;
  u8_t          status;
} sl_sfile_server_store_filestat_req;

/******************************************************************************/
/**
 * \struct sl_sfile_server_store_filestat_cnf
 * This structure is sent with the \ref SL_SERVER_OBJ_CREATE_CNF mail message.
 *
 * This confirmation is sent in response to the \ref SL_SERVER_OBJ_CREATE_REQ
 * mail message to create a \ref SL_OBJ_ID_X_SDEV_FILE (Self Device File
 * Status Resource or FILE). The confirmation provides a status of the operation and contains
 * the ref structure of the created FILE. It uses the generic create confirmation
 * structure \ref sl_server_obj_cnf_t.
 *
 * The ref field of the sl_sfile_server_store_filestat_cnf will be defined as
 * follows:\n
 * ref.objId    = \ref SL_OBJ_ID_X_SDEV_FILE\n
 * ref.numInstanceIDs = 1\n
 * ref.instanceIDs[0] = \ref SL_OBJ_INSTANCE_DEF_GRP_ID\n
 *
 * Dependencies: None.
 *
 * typedef sl_server_obj_cnf_t sl_sfile_server_store_filestat_cnf
 */
typedef sl_server_obj_cnf_t sl_sfile_server_store_filestat_cnf;

// -------------------- Subscription ------------

typedef struct {
  u16_t         id;
  u8_t          ipAddr[SL_XSD_IPADDR_LEN];
  char          subscribedResource[SL_XSD_LINK_LEN];
} sl_subs_server_post_subs_ind;

/** \endcond */

// -------------------- Time --------------------

/**
 * \defgroup TIME_GROUP Time Definitions and Structures
 * This section contains definitions and structures used by the Time function set.
 */
// begin addtogroup TIME_GROUP
/** \addtogroup TIME_GROUP
 * @{ */

/**
 * \defgroup TIME_GROUP_MAIL_STRUCTS Time Mail Structures
 * This section contains mail structures used by the Time function set.
 */
/** \addtogroup TIME_GROUP_MAIL_STRUCTS
* @{ */

/******************************************************************************/
/**
 * \struct sl_time_server_set_time_req
 * This request is used to set the timebase used by the SEP server. This information
 * is also served to clients in the time link.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * The current time.
   */
  sl_xsd_time_type_t utcTime;
  /**
   * Time at which daylight savings begins (apply dstOffset).
   */
  sl_xsd_time_type_t daylightSavingsStartTime;
  /**
   * Time at which daylight savings ends (dstOffset is no longer applied).
   */
  sl_xsd_time_type_t daylightSavingsEndTime;
  /**
   * Daylight savings time offset from local standard time.
   */
  i32_t             daylightSavingsOffset;
  /**
   * Local time zone offset from currentTime, not including any daylight savings
   * time offsets.
   */
  i32_t             timeZoneOffset;
  /**
   * Quality of the time source.
   */
  sl_xsd_quality_t  quality;
} sl_time_server_set_time_req;

/******************************************************************************/
/**
 * \struct sl_time_server_set_time_cnf
 * This confirmation is used to indicate to the Customer Application whether
 * the requested time was successfully applied.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  i8_t          status;
} sl_time_server_set_time_cnf;

/******************************************************************************/
/**
 * \struct sl_time_client_server_ind
 * This indication is sent to the Customer Client application unsolicited from
 * the Time Client to indicate that a new Time server has been found. Note
 * that multiple indications may be sent if there are multiple servers and/or
 * sources of Time information available.
 *
 * Dependencies: None.
 *
 * typedef sl_cmn_client_server_ind_t sl_time_client_server_ind
*/
typedef sl_cmn_client_server_ind_t sl_time_client_server_ind;

/******************************************************************************/
/**
 * \struct sl_time_client_server_time_ind
 * This indication is sent anytime the SL Client receives a time update from
 * the primary time server.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * The current time.
   */
  sl_xsd_time_type_t utcTime;
  /**
   * Time at which daylight savings begins (apply dstOffset).
   */
  sl_xsd_time_type_t daylightSavingsStartTime;
  /**
   * Time at which daylight savings ends (dstOffset is no longer applied).
   */
  sl_xsd_time_type_t daylightSavingsEndTime;
  /**
   * Daylight savings time offset from local standard time.
   */
  i32_t              daylightSavingsOffset;
  /**
   * Local time zone offset from currentTime, not including any daylight savings
   * time offsets.
   */
  i32_t              timeZoneOffset;
  /**
   * Quality of the time source.
   */
  sl_xsd_quality_t   quality;
} sl_time_client_server_time_ind;

/** @} */
// end addtogroup TIME_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup TIME_GROUP

// -------------------- DNS ---------------------

/**
 * \defgroup DNS_GROUP DNS Definitions and Structures
 * This section contains definitions and structures used for DNS by the Services Layer.
 */
/** \addtogroup DNS_GROUP
 * @{ */

/**
 * \defgroup DNS_GROUP_DEFINES DNS Definitions
 * This section contains definitions used for DNS by the Services Layer.
 */
/** \addtogroup DNS_GROUP_DEFINES
 * @{ */

/**
 * Max length of the DNS server instance name.
 */
#define SL_DNS_INSTANCE_NAME_LEN              (48)

/**
 * Max length of the service name used by the DNS client.
 */
#define SL_DNS_CLIENT_SERVICE_NAME_LEN        (64)

/**
 * Max length of the top level domain name used by the DNS client.
 */
#define SL_DNS_CLIENT_TOP_LEVEL_DOMAIN_LEN    (64)

/**
 * Defines the service name used by the Services Layer if the service name is
 * not configured by the application.
 */
#define SL_DNS_DEFAULT_SERVICE_NAME           "_smartenergy."

/**
 * Defines the top level domain name used by the Services Layer for XMDNS if the
 * top level domain name is not configured by the application.
 */
#define SL_DNS_DEFAULT_XMDNS_TOP_LEVEL_DOMAIN_NAME   "site."

/**
 * Defines the top level domain name used by the Services Layer for MDNS if the
 * top level domain name is not configured by the application.
 */
#define SL_DNS_DEFAULT_MDNS_TOP_LEVEL_DOMAIN_NAME    "local."

/**
 * Defines the top level domain name used by the Services Layer for DNS-SD if the
 * top level domain name is not configured by the application.
 */
#define SL_DNS_DEFAULT_DNSSD_TOP_LEVEL_DOMAIN_NAME   "com."

/**
 * Defines the IPv4 address used by the Services Layer for xmDNS if the IP address
 * is not configured by the application.
 */
#define SL_DNS_DEFAULT_XMDNS_V4_ADDR          "239.255.255.251"

/**
 * Defines the IPv6 address used by the Services Layer for xmDNS if the IP address
 * is not configured by the application.
 */
#define SL_DNS_DEFAULT_XMDNS_V6_ADDR          "ff05::fb"

/**
 * Defines the IPv4 address used by the Services Layer for mDNS if the IP address
 * is not configured by the application.
 */
#define SL_DNS_DEFAULT_MDNS_V4_ADDR           "224.0.0.251"

/**
 * Defines the IPv6 address used by the Services Layer for mDNS if the IP address
 * is not configured by the application.
 */
#define SL_DNS_DEFAULT_MDNS_V6_ADDR           "ff02::fb"

/**
 * Defines the DNS instance name used by the Services Layer on non-Linux platforms
 * if the instance name is not configured by the application.
 */
#ifndef SL_DNS_SERVER_DEFAULT_INSTANCE_NAME
#define SL_DNS_SERVER_DEFAULT_INSTANCE_NAME          "KituDnsServer"
#endif

/** @} */
// end addtogroup DNS_GROUP_DEFINES

/**
 * \defgroup DNS_GROUP_TYPES DNS Types
 * This section contains type used for DNS by the Services Layer.
 */
/** \addtogroup DNS_GROUP_TYPES
 * @{ */

/******************************************************************************/
/**
 * \defgroup SL_DNS_STANDARD_XXX DNS Standard Type: sl_dns_standard_t (SL_DNS_STANDARD_XXX)
 * Defines the DNS standards that SL may be configured to support.
 *
 * Values are SL_DNS_STANDARD_XXX as defined below.
 */
/** \addtogroup SL_DNS_STANDARD_XXX
* @{ */
/**
 * \var typedef u8_t sl_dns_standard_t
 * Acceptable values are SL_DNS_STANDARD_XXX.
 */
typedef u8_t sl_dns_standard_t;
/**
 * The Extended Multicast DNS (xmDNS) standard IEEE draft-lynn-dnsext-site-mdns-01.
 */
#define SL_DNS_STANDARD_XMDNS     (0)
/**
 * The multicast DNS (mDNS) standard IEEE RFC 6762.
 */
#define SL_DNS_STANDARD_MDNS      (1)
/**
 * The DNS-Based Service Discovery (DNS-SD) standard IEEE RFC 6763.
 */
#define SL_DNS_STANDARD_DNSSD     (2)
/** @} */

/** @} */
// end addtogroup DNS_GROUP_Types

/**
 * \defgroup DNS_GROUP_STRUCTS DNS Structures
 * This section contains structures used for DNS by the Services Layer.
 */
/** \addtogroup DNS_GROUP_STRUCTS
* @{ */

/******************************************************************************/
/**
 * \struct sl_dns_client_config_dnssd_t
 * Contains configuration parameters for the DNS Client when it is configured to
 * support DNS-SD.
 */
typedef struct {
  /**
   * Character string containing the top level domain name.  Character string must
   * be null terminated.
   */
  char                topLevelDomainName[SL_DNS_CLIENT_TOP_LEVEL_DOMAIN_LEN];
  /**
   * Flag indicating whether the \ref topLevelDomainName configuration parameter
   * is set. If the \ref topLevelDomainName configuration parameter is not set,
   * the top level domain name shall default to \ref SL_DNS_DEFAULT_XMDNS_TOP_LEVEL_DOMAIN_NAME
   * for xmDNS, \ref SL_DNS_DEFAULT_MDNS_TOP_LEVEL_DOMAIN_NAME for mDNS, and
   * \ref SL_DNS_DEFAULT_DNSSD_TOP_LEVEL_DOMAIN_NAME for DNS-SD.
   */
  bool                topLevelDomainNameExists;
  /**
   * IP Address of the DNS server. This may be a v4 address or v6 address.
   */
  u8_t                addr[SL_CMN_IP_ADDR_LEN];
  /**
   * Flag indicating whether the \ref addr configuration parameter is set.  If
   * the \ref addr configuration parameter is not set, the IP address shall
   * default to \ref SL_DNS_DEFAULT_XMDNS_V4_ADDR for IPv4 and
   * \ref SL_DNS_DEFAULT_XMDNS_V4_ADDR for IPv6 with xmDNS.  With mDNS,
   * the IP address shall default to \ref SL_DNS_DEFAULT_MDNS_V4_ADDR for
   * IPv4 and \ref SL_DNS_DEFAULT_MDNS_V4_ADDR for IPv6.  With DNS-SD,
   * the addr shall default to 0.
   */
  bool                addrExists;
} sl_dns_client_config_dnssd_t;

/******************************************************************************/
/**
 * \struct sl_dns_server_config_dnssd_t
 * Contains configuration parameters for the DNS Server when it is configured to
 * support DNS-SD.
 */
typedef struct {
  /**
   * Character string containing the top level domain name.  Character string must
   * be null terminated.
   */
  char                topLevelDomainName[SL_DNS_CLIENT_TOP_LEVEL_DOMAIN_LEN];
  /**
   * Flag indicating whether the \ref topLevelDomainName configuration parameter
   * is set. If the \ref topLevelDomainName configuration parameter is not set,
   * the top level domain name shall default to \ref SL_DNS_DEFAULT_XMDNS_TOP_LEVEL_DOMAIN_NAME
   * for xmDNS, \ref SL_DNS_DEFAULT_MDNS_TOP_LEVEL_DOMAIN_NAME for mDNS, and
   * \ref SL_DNS_DEFAULT_DNSSD_TOP_LEVEL_DOMAIN_NAME for DNS-SD.
   */
  bool                topLevelDomainNameExists;
} sl_dns_server_config_dnssd_t;

/** @} */
// end addtogroup DNS_GROUP_STRUCTS

/**
 * \defgroup DNS_GROUP_MAIL_STRUCTS DNS Mail Structures
 * This section contains mail structures used for DNS by the Services Layer.
 */
/** \addtogroup DNS_GROUP_MAIL_STRUCTS
* @{ */

/******************************************************************************/
/**
 * \struct sl_dns_client_config_req
 * This request is used to set DNS client configuration parameters. If this
 * message is not sent, default parameters are used.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
*/
typedef struct {
  /**
   * The DNS standard to be used for DNS.  Note that only \ref SL_DNS_STANDARD_XMDNS
   * meets the SEP2.0 requirements.
   */
  sl_dns_standard_t             standard;
  /**
   * Flag indicating whether the \ref standard configuration parameter is set.
   * If the \ref standard configuration parameter is not set, the DNS standard
   * shall default to \ref SL_DNS_STANDARD_XMDNS.
   */
  bool                          standardExists;
  /**
   * Character string containing the DNS service name.  Character string must be
   * null terminated.  Note that only \ref SL_DNS_DEFAULT_SERVICE_NAME meets the
   * SEP2.0 requirements.
   */
  char                          serviceName[SL_DNS_CLIENT_SERVICE_NAME_LEN];
  /**
   * Flag indicating whether the \ref serviceName configuration parameter is set.
   * If the \ref serviceName configuration parameter is not set, the DNS service
   * name shall default to \ref SL_DNS_DEFAULT_SERVICE_NAME.
   */
  bool                          serviceNameExists;
  /**
   * Configuration parameters used only when \ref standard is configured
   * for \ref SL_DNS_STANDARD_DNSSD.
   */
  sl_dns_client_config_dnssd_t  dnsSD;
} sl_dns_client_config_req;

/******************************************************************************/
/**
 * \struct sl_dns_client_config_cnf
 * This confirmation indicates whether or not the \ref SL_DNS_CLIENT_CONFIG_REQ
 * was successfully handled or not.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;
} sl_dns_client_config_cnf;

/******************************************************************************/
/**
 * \struct sl_dns_server_config_req
 * This request is used to set DNS server configuration parameters. If this
 * message is not sent, default parameters are used.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
*/
typedef struct {
  /**
   * The DNS standard to be used for DNS.  Note that only \ref SL_DNS_STANDARD_XMDNS
   * meets the SEP2.0 requirements.
   */
  sl_dns_standard_t             standard;
  /**
   * Flag indicating whether the \ref standard configuration parameter is set.
   * If the \ref standard configuration parameter is not set, the DNS standard
   * shall default to \ref SL_DNS_STANDARD_XMDNS.
   */
  bool                          standardExists;
  /**
   * Character string containing the DNS server instance name. Character string must be
   * null terminated.
   */
  char                          instanceName[SL_DNS_INSTANCE_NAME_LEN];
  /**
   * Flag indicating whether the \ref instanceName configuration parameter is set.
   * If the \ref instanceName configuration parameter is not set, the DNS server
   * instance name shall default to the machine host name on Linux platforms.  On
   * all other platforms the instanceName shall default to \ref SL_DNS_SERVER_DEFAULT_INSTANCE_NAME.
   */
  bool                          instanceNameExists;
  /**
   * Character string containing the DNS service name.  Character string must be
   * null terminated.  Note that only \ref SL_DNS_DEFAULT_SERVICE_NAME meets the
   * SEP2.0 requirements.
   */
  char                          serviceName[SL_DNS_CLIENT_SERVICE_NAME_LEN];
  /**
   * Flag indicating whether the \ref serviceName configuration parameter is set.
   * If the \ref serviceName configuration parameter is not set, the DNS service
   * name shall default to \ref SL_DNS_DEFAULT_SERVICE_NAME.
   */
  bool                          serviceNameExists;
  /**
   * Configuration parameters used only when \ref standard is configured
   * for \ref SL_DNS_STANDARD_DNSSD.
   */
  sl_dns_server_config_dnssd_t  dnsSD;
} sl_dns_server_config_req;

/******************************************************************************/
/**
 * \struct sl_dns_server_config_cnf
 * This confirmation indicates whether or not the \ref SL_DNS_SERVER_CONFIG_REQ
 * was successfully handled or not.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;
} sl_dns_server_config_cnf;

/** @} */
// end addtogroup DNS_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup DNS_GROUP


// -------------------- General -----------------

/**
 * \defgroup GENERAL_GROUP General Definitions and Structures
 * This section contains definitions and structures used by the Services Layer in general. These are not
 * function set specific.
 */
/** \addtogroup GENERAL_GROUP
 * @{ */

//typedef struct {
//} sl_startup_req;  // empty

/******************************************************************************/
/**
 * \struct sl_startup_cnf
 * This confirmation is sent in response to an \ref SL_STARTUP_REQ. It provides
 * client and server status information, based on whether the device is
 * configured as a client or server.
 *
 * Dependencies: None.
 */
typedef struct {
  i8_t          serverStatus;
  i8_t          clientStatus;
} sl_startup_cnf;

//typedef struct {
// This is an empty structure.
//} sl_client_discover_resources_req;

/******************************************************************************/
/**
 * \struct sl_client_discover_resources_cnf
 * This confirmation is sent in response to the \ref SL_CLIENT_DISCOVER_RESOURCES_REQ
 * and provides a status of the operation.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t    status;
} sl_client_discover_resources_cnf;

/******************************************************************************/
/**
 * \struct sl_client_set_server_req
 * This request is used to hard-code server information in the client. This
 * request MUST be sent prior to the \ref SL_STARTUP_REQ. Also, this request
 * is only valid in case DNS is not enabled. When DNS is enabled, if this
 * request is sent the SL will respond with a status of \ref SL_CMN_RC_NOT_ALLOWED.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
 */
typedef struct {
  /**
   * IP Address of the server. This may be a v4 address or v6 address.
   */
  u8_t                addr[SL_CMN_IP_ADDR_LEN]; // Supports IPv4 and IPv6 addressing
  /**
   * Port to use on the server.
   */
  u16_t               port;
  /**
   * Scheme to use when accessing the server (either HTTP or HTTPS).
   */
  sl_cmn_scheme_t     scheme;
  /**
   * IP Version, used to properly decode the address bytes.
   */
  sl_cmn_ip_version_t ipVersion;
  /**
   * Relative URI for the server device capabilities resource. This
   * URI must start with "/". In case a Kitu server is used, the
   * dcap URI can be set to \ref SL_CMN_DCAP_DEFAULT_URI.
   */
  char                dcapRelativeUri[SL_CMN_DCAP_PATH_LEN];
  /**
   * Interface id to use when accessing the server. Set to 0 if not
   * using link local address.
   */
  u32_t               interfaceId;
} sl_client_set_server_req;

/******************************************************************************/
/**
 * \struct sl_client_set_server_cnf
 * This confirmation is sent in response to the \ref SL_CLIENT_SET_SERVER_REQ and
 * provides a status of the operation.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t    status;
} sl_client_set_server_cnf;

/******************************************************************************/
/**
 * \struct sl_sec_store_private_key_req
 * This request is used to load device private key data in the selected format.
 * The SL will copy the private key into its own structure based on this request. 
 * It will then send the \ref SL_SEC_STORE_PRIVATE_KEY_CNF to indicate it is done 
 * using the pointers passed in the request.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
*/
typedef struct {
  /**
   * Format of the private key
   */
  u8_t privKeyFormat;
  /**
   * Length of the private key data
   */
  u16_t privKeyLength;
  /**
   * Pointer to the private key data
   */
  u8_t  privKeyData[];
} sl_sec_store_private_key_req;

/******************************************************************************/
/**
 * \struct sl_sec_store_private_key_cnf
 * This confirmation is sent by the SL to indicate that it has finished
 * processing the \ref SL_SEC_STORE_PRIVATE_KEY_REQ.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status indicating whether or not the certificate data was successfully
   * stored.
   */
  sl_cmn_rc_t  status;
} sl_sec_store_private_key_cnf;

/**
 * Max length of the device certificate. This number is based on having a
 * maximum of 4 certificates of 600 bytes each chained together plus some
 * header information.
 */
#define SL_SEC_MAX_CERT_FILE_LEN     (4600)

/******************************************************************************/
/**
 * \struct sl_sec_store_cert_req
 * This request is used to load device certificate chain in the selected format. 
 * It can be used by either client or server. The SL will copy the certificate 
 * chain data into its own structure based on this request. It will will send 
 * the \ref SL_SEC_STORE_CERT_CNF using the \ref sl_sec_store_cert_cnf structure
 * to indicate it is done handling the request. 
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
*/
typedef struct {
  /**
   * Format of the certificate chain data.
   */
  u8_t    chainFormat;
  /**
   * Length of the certificate chain data.
   */
  u16_t   chainLength;
  /**
   * Variable length array chainLength containing the device certificate 
   * chain. The maximum size of this array will be on the order of 4600
   * bytes. The max array length is \ref SL_SEC_MAX_CERT_FILE_LEN.
   */
  u8_t   chainData[]; // Variable length up to SL_SEC_MAX_CERT_FILE_LEN
} sl_sec_store_cert_req;

/******************************************************************************/
/**
 * \struct sl_sec_store_cert_cnf
 * This confirmation is sent by the SL to indicate that it has finished
 * processing the \ref SL_SEC_STORE_CERT_REQ.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status indicating whether or not the certificate data was successfully
   * stored.
   */
  sl_cmn_rc_t  status;
  /**
   * SFDI of the device, including the check digit. This is only valid if the
   * status is SL_CMN_RC_SUCCESS
   */
  u64_t   sfdi;                   // 8 Bytes
  /**
   * LFDI of the device. This is only valid if the status is SL_CMN_RC_SUCCESS
   */
  u8_t    lfdi[SL_XSD_LFDI_LEN];
} sl_sec_store_cert_cnf;

/******************************************************************************/
/**
 * \struct sl_sec_store_root_ca_cert_req
 * This request is used to load a new Root CA certificate in x509 DER format. 
 * It can be used by either client or server. The SL will copy the new Root 
 * cert into its own structure based on this request. It will send the 
 * \ref SL_SEC_STORE_ROOT_CA_CERT_CNF using the 
 * \ref sl_sec_store_root_ca_cert_cnf structure to indicate it is done handling
 * the request. 
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
*/
typedef struct {
  /**
   * The length of the ASN.1 encoded EC public key object
   */
  u16_t certLength;
  /**
   * The ASN.1 encoded EC public key data
   */
  u8_t certData[];      // variable-length
} sl_sec_store_root_ca_cert_req;

/******************************************************************************/
/**
 * \struct sl_sec_store_root_ca_cert_cnf
 * This confirmation is sent by the SL to indicate that it has finished
 * processing the \ref SL_SEC_STORE_ROOT_CA_CERT_REQ.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status indicating whether or not the Root CA Public Key data was successfully
   * stored.
   */
  sl_cmn_rc_t  status;
} sl_sec_store_root_ca_cert_cnf;

// SPRK-370
/******************************************************************************/
/**
 * \struct sl_sec_store_lfdi_whitelist_t
 * This structure contains information about the LFDI whitelist.
 *
*/
typedef struct
{
  u8_t    lfdi[SL_XSD_LFDI_LEN];
} sl_sec_store_lfdi_whitelist_t;

// SPRK-370
/******************************************************************************/
/**
 * \struct sl_sec_store_server_white_list_req
 * This request is used to load the white list of server LFDI's. Servers whose 
 * LFDI is not in the white list will be rejected in the TLS authentication. 
 *
*/
typedef struct {
  /**
   * The number of server LFDI's in the white list
   */
  u8_t numServers;
  /**
   * A list of LFDI's
   */
  sl_sec_store_lfdi_whitelist_t whiteList[];      // variable-length
} sl_sec_store_server_white_list_req;

// (SPRK-370)
/******************************************************************************/
/**
 * \struct sl_sec_store_server_white_list_cnf
 * This confirmation is sent by the SL to indicate that it has finished
 * processing the \ref SL_SEC_STORE_ROOT_CA_CERT_REQ.  *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status indicating whether or not the white list of server LFDI's was 
   * sucessfully stored.
   */
  sl_cmn_rc_t  status;
} sl_sec_store_server_white_list_cnf;

// SPRK-1493
/******************************************************************************/
/**
 * \struct sl_sec_store_client_white_list_req
 * This request is used to load the white list of client LFDI's. Chients whose 
 * LFDI is not in the white list will be rejected in the TLS authentication. 
 *
*/
typedef struct {
  /**
   * The number of client LFDI's in the white list
   */
  u8_t numClients;
  /**
   * A list of LFDI's
   */
  sl_sec_store_lfdi_whitelist_t whiteList[];      // variable-length
} sl_sec_store_client_white_list_req;

// SPRK-1493
/******************************************************************************/
/**
 * \struct sl_sec_store_client_white_list_cnf
 * This confirmation is sent by the SL to indicate that it has finished
 * processing the \ref SL_SEC_STORE_ROOT_CA_CERT_REQ.  *
 * Dependencies: None.
*/
typedef struct {
  /**
   * Status indicating whether or not the white list of client LFDI's was 
   * sucessfully stored.
   */
  sl_cmn_rc_t  status;
} sl_sec_store_client_white_list_cnf;

/******************************************************************************/
/**
 * \struct sl_sec_get_sfdi_req
 * This request is sent to the SL to get the device SFDI (Short Form Device
 * Identifier) including the check digit, which is returned in the
 * \ref sl_sec_get_sfdi_cnf.
 *
 * Dependencies: This request should be sent AFTER the \ref SL_STARTUP_REQ.
*/
//typedef struct {
  // empty
//} sl_sec_get_sfdi_req;

/******************************************************************************/
/**
 * \struct sl_sec_get_sfdi_cnf
 * This confirmation is sent by the SL in response to the SL_SEC_GET_SFDI_REQ
 * and contains the device SFDI (Short Form Device Identifier) including the
 * check digit.
 *
 * Dependencies: None.
*/
typedef struct {
  /**
   * SFDI of the device, including the check digit.
   */
  u64_t   sfdi;                   // 8 Bytes
} sl_sec_get_sfdi_cnf;

/******************************************************************************/
/**
 * \struct sl_server_config_dsp_req
 * This request is used to change the state of the Default Security Policy in
 * the server. This interface may only be used if the server is not built with
 * DSP enabled. If it is built to allow the DSP to be disabled, this interface
 * may be used to change the DSP state to enabled prior to send the SL_STARTUP_REQ.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
*/
typedef struct {
  /**
   * Boolean flag that should be set to TRUE to enable the DSP, otherwise to FALSE.
   */
  bool   enable;
} sl_server_config_dsp_req;

/******************************************************************************/
/**
 * \struct sl_server_config_dsp_cnf
 * This confirmation is sent in response to the SL_SERVER_CONFIG_DSP_REQ. It
 * provides a status of the operation as well as the current state of the DSP.
 * Possible return status values are:
 * SL_CMN_RC_SUCCESS: Indicates that the DSP state was successfully updated.
 * SL_CMN_RC_FAIL: Indicates that the DSP state may NOT be modified in this build.
 * SL_CMN_RC_NOT_ALLOWED: Indicates that the request failed because it must be
 *   sent prior to the SL_STARTUP_REQ.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t  status;
  /**
   * Current state of the DSP. Enabled if true, otherwise disabled.
   */
  bool         enabled;
} sl_server_config_dsp_cnf;

/** @} */
// end addtogroup GENERAL_GROUP


// -------------------- Zigbee --------------------

/**
 * \defgroup ZB_GROUP Zigbee Definitions and Structures
 * \brief This section contains definitions and structures used when the Services
 * Layer task is built with the Kitu Zigbee protocol stack.
 */
/** \addtogroup ZB_GROUP
 * @{ */

/**
 * \defgroup ZB_GROUP_TYPES Zigbee Types
 * This section contains types used with the Zigbee protocol stack.
 */
/** \addtogroup ZB_GROUP_TYPES
 * @{ */

/******************************************************************************/
/**
 * The value represents the Zigbee channel number.  The range of valid values in
 * the 2.4 Ghz band is 11-26.
 */
typedef u8_t sl_zb_chan_num_t;

/******************************************************************************/
/**
 * \defgroup SL_ZB_SLEEP_CAPABILITY_XXX SL Zigbee Sleep Capability: sl_zb_sleep_capability_t (SL_ZB_SLEEP_CAPABILITY_XXX)
 * SL Zigbee Sleep Capability. This defines whether or not a device operates in
 * sleepy or non-sleepy mode.
 */
/** \addtogroup SL_ZB_SLEEP_CAPABILITY_XXX
* @{ */
/**
 * \var typedef u8_t sl_zb_sleep_capability_t
 * Acceptable values are SL_ZB_SLEEP_CAPABILITY_XXX.
 */
typedef u8_t sl_zb_sleep_capability_t;
/**
 * A non-sleepy device does not go to sleep and is always active.
 */
#define SL_ZB_SLEEP_CAPABILITY_NON_SLEEPY  (0)
/**
 * A sleepy device periodically goes into sleep mode.
 */
#define SL_ZB_SLEEP_CAPABILITY_SLEEPY  (1)
/** @} */

/** @} */
// end addtogroup ZB_GROUP_TYPES

/**
 * \defgroup ZB_GROUP_DEFINES Zigbee Definitions
 * This section contains definitions used with the Zigbee protocol stack.
 */
/** \addtogroup ZB_GROUP_DEFINES
 * @{ */

/**
 * Defines the channel number used by the Zigbee stack if the channel number is
 * not configured by the application.
 */
#define SL_ZB_DEFAULT_CHAN_NUM                     15
/**
 * Defines the IEEE address used by the Zigbee stack if the IEEE address is
 * not configured by the application.
 */
#define SL_ZB_DEFAULT_IEEE_ADDR                    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xde, 0xac }
/**
 * Defines the IP address prefix used by the Zigbee stack if the IP address prefix
 * is not configured by the application.
 */
#define SL_ZB_DEFAULT_IP_ADDR_PREFIX               { 0x20, 0x02, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00 }
/**
 * Defines the IP address prefix used by the Zigbee stack if the IP address prefix
 * is not configured by the application.  Note that this value only applies if
 * the device is configured as a border router.
 */
#define SL_ZB_DEFAULT_IP_ADDR_PREFIX_LENGTH_VALUE  64
/**
 * Defines the MAC Key used by the Zigbee stack if the MAC Key is not configured
 * by the application.  Note that this value only applies if the device is
 * configured as a border router.
 */
#define SL_ZB_DEFAULT_MAC_KEY                      { 0xbf, 0xbe, 0xbd, 0xbc, 0xbb, 0xba, 0xb9, 0xb8, 0xb7, 0xb6, 0xb5, 0xb4, 0xb3, 0xb2, 0xb1, 0xb0 }
/**
 * Defines the network id used by the Zigbee stack if the network id is not
 * configured by the application.
 */
#define SL_ZB_DEFAULT_NETWORK_ID                   { 'G', 'r', 'i', 'd', '2', 'H', 'o', 'm', 'e', 0, 0, 0, 0, 0, 0, 0 }
/**
 * Defines the number of whiteboard entries used by the Zigbee stack if the number
 * of whiteboard entries is not configured by the application.  The number of
 * whiteboard entries should be equivalent to the maximum number of devices on
 * the subnet.  Note that this value only applies if the device is configured as
 * a border router.
 */
#define SL_ZB_DEFAULT_NUM_WHITEBOARD_ENTRIES       20
/**
 * Defines the PAN id used by the Zigbee stack if the PAN id is not configured
 * by the application.  Note that this value only applies if the device is
 * configured as a border router.
 */
#define SL_ZB_DEFAULT_PAN_ID                       0x1baa
/**
 * Defines the polling interval used by the Zigbee stack if the polling interval
 * is not configured by the application.  Note that this value only applies if
 * the device is configured as a host and the sleep capability is configured as
 * non-sleepy.
 */
#define SL_ZB_DEFAULT_POLLING_INTERVAL_NON_SLEEPY  0
/**
 * Defines the polling interval used by the Zigbee stack if the polling interval
 * is not configured by the application.  Note that this value only applies if
 * the device is configured as a host and the sleep capability is configured as
 * sleepy.
 */
#define SL_ZB_DEFAULT_POLLING_INTERVAL_SLEEPY      10
/**
 * Defines the short address used by the Zigbee stack if the short address
 * is not configured by the application.
 */
#define SL_ZB_DEFAULT_ROOT_SHORT_ADDR              0x1122
/**
 * Defines the sleep capability used by the Zigbee stack if the sleep capability
 * is not configured by the application.  Note that this value only applies if
 * the device is configured as a host.
 */
#define SL_ZB_DEFAULT_SLEEP_CAPABILITY             SL_ZB_SLEEP_CAPABILITY_NON_SLEEPY
/**
 * Defines maximum length of a Zigbee IP address prefix.
 */
#define SL_ZB_IP_ADDR_PREFIX_LEN                   8
/**
 * Defines maximum length of a Zigbee IEEE address.
 */
#define SL_ZB_IEEE_ADDR_LEN                        8
/**
 * Defines maximum length of a Zigbee MAC key.
 */
#define SL_ZB_MAC_KEY_LEN                          16
/**
 * Defines maximum length of a Zigbee network id.
 */
#define SL_ZB_NETWORK_ID_LEN                       16

/** @} */
// end addtogroup ZB_GROUP_DEFINES

/**
 * \defgroup ZB_GROUP_MAIL_STRUCTS Zigbee Mail Structures
 * This section contains mail structures used with the Zigbee protocol stack.
 */
/** \addtogroup ZB_GROUP_MAIL_STRUCTS
 * @{ */

/******************************************************************************/
/**
 * \struct sl_zb_config_border_router_req
 * This request is used to configure the parameters that are used by the SL Task
 * to start up the Zigbee stack as a Border Router.  If this request is not
 * sent by the application, the Zigbee protocol stack will be started by default
 * as a border router using default parameters.  This request is only valid when
 * the SL Task has been built with the Kitu Zigbee protocol stack.  This
 * request MUST be sent prior to the \ref SL_STARTUP_REQ.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
 */
typedef struct
{
  /**
   * Flag indicating if the Zigbee channel number should be set using the value
   * \ref channelNumber.
   */
  bool              setChannelNumber;
  /**
   * Flag indicating if the IEEE address should be set using the value
   * \ref ieeeAddress.
   */
  bool              setIeeeAddress;
  /**
   * Flag indicating if the IP address prefix should be set using the value
   * \ref ipAddrPrefix.
   */
  bool              setIpAddrPrefix;
  /**
   * Flag indicating if the IP address prefix length should be set using the value
   * \ref ipAddrPrefixLengthValue.
   */
  bool              setIpAddrPrefixLengthValue;
  /**
   * Flag indicating if the MAC Key should be set using the value \ref macKey.
   */
  bool              setMacKey;
  /**
   * Flag indicating if the beacon network id should be set using the value
   * \ref networkId.
   */
  bool              setNetworkId;
  /**
   * Flag indicating if the number of whiteboard entries should be set using the
   * value \ref numWhiteboardEntries.
   */
  bool              setNumWhiteboardEntries;
  /**
   * Flag indicating if the PAN (Person Area Network) Id should be set using the
   * value \ref panId.
   */
  bool              setPanId;
  /**
   * Flag indicating if the short address should be set using the value
   * \ref shortAddress.
   */
  bool              setShortAddress;
  /**
   * The channel number to be used by the Zigbee protocol stack.  This value is
   * only used if \ref setChannelNumber is set to true.  The default value if this
   * value is not set by the application is \ref SL_ZB_DEFAULT_CHAN_NUM.
   */
  sl_zb_chan_num_t  channelNumber;
  /**
   * The 64-bit IEEE address to be used by the Zigbee protocol stack.  This
   * value is only used if \ref setIeeeAddress is set to true.  If this value is
   * not set by the application the default value is \ref SL_ZB_DEFAULT_IEEE_ADDR.
   */
  u8_t              ieeeAddress[SL_ZB_IEEE_ADDR_LEN];
  /**
   * The 64-bit IP address prefix to be used by the Zigbee protocol stack.  This
   * value is only used if \ref setIpAddrPrefix is set to true.  If this value is
   * not set by the application the default value is \ref SL_ZB_DEFAULT_IP_ADDR_PREFIX.
   */
  u8_t              ipAddrPrefix[SL_ZB_IP_ADDR_PREFIX_LEN];
  /**
   * The IP address prefix length to be used by the Zigbee protocol stack.  This
   * value is only used if \ref setIpAddrPrefixLengthValue is set to true.  If this
   * value is not set by the application the default value is
   * \ref SL_ZB_DEFAULT_IP_ADDR_PREFIX_LENGTH_VALUE.
   */
  u8_t              ipAddrPrefixLengthValue;
  /**
   * The MAC Key to be used by the Zigbee protocol stack.  This value is only
   * used if \ref setMacKey is set to true.  The default value if this
   * value is not set by the application is \ref SL_ZB_DEFAULT_MAC_KEY.
   */
  u8_t              macKey[SL_ZB_MAC_KEY_LEN];
  /*
   * The beacon network id to be used by the Zigbee protocol stack.  This value
   * is only used if \ref setNetworkId is set to true.  If this value is not set
   * by the application the default value is \ref SL_ZB_DEFAULT_NETWORK_ID.
   */
  u8_t              networkId[SL_ZB_NETWORK_ID_LEN];
  /**
   * The number of whiteboard entries to be used by the Zigbee protocol stack.
   * This value should be set to the maximum number of devices on the subnet.
   * This value is only used if \ref setNumWhiteboardEntries is set to true.
   * If this value is not set by the application the default value is
   * \ref SL_ZB_DEFAULT_NUM_WHITEBOARD_ENTRIES.
   */
  u16_t             numWhiteboardEntries;
  /**
   * The PAN (Personal Area Network) Id to be used by the Zigbee protocol stack.
   * This value is only used if \ref setPanId is set to true.  If this value is
   * not set by the application The default value is \ref SL_ZB_DEFAULT_PAN_ID.
   */
  u16_t             panId;
  /**
   * The short address to be used by the Zigbee protocol stack.  This value is
   * only used if \ref setShortAddress is set to true.  If this value is not set
   * by the application the default value is \ref SL_ZB_DEFAULT_ROOT_SHORT_ADDR.
   */
  u16_t             shortAddress;
} sl_zb_config_border_router_req;

/******************************************************************************/
/**
 * \struct sl_zb_config_border_router_cnf
 * This confirmation indicates whether or not the \ref SL_ZB_CONFIG_BORDER_ROUTER_REQ
 * was successfully handled or not.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;
} sl_zb_config_border_router_cnf;

/******************************************************************************/
/**
 * \struct sl_zb_config_router_req
 * This request is used to configure the parameters that are used by the SL Task
 * to start up the Zigbee stack as a Router.  If this request is not sent by
 * the application, the Zigbee protocol stack will be started by default as a border
 * router.  This request is only valid when the SL Task has been built with the
 * Kitu Zigbee protocol stack.  This request MUST be sent prior to the
 * \ref SL_STARTUP_REQ.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
 */
typedef struct
{
/**
 * Flag indicating if the Zigbee channel number should be set using the value
 * \ref channelNumber.
 */
bool              setChannelNumber;
/**
 * Flag indicating if the IEEE address should be set using the value
 * \ref ieeeAddress.
 */
bool              setIeeeAddress;
/**
 * Flag indicating if the short address should be set using the value
 * \ref shortAddress.
 */
bool              setShortAddress;
/**
 * The channel number to be used by the Zigbee protocol stack.  This value is
 * only used if \ref setChannelNumber is set to true.  If this value is not set
 * by the application the default value is \ref SL_ZB_DEFAULT_CHAN_NUM.
 */
sl_zb_chan_num_t  channelNumber;
/**
 * The 64-bit IEEE address to be used by the Zigbee protocol stack.  This
 * value is only used if \ref setIeeeAddress is set to true.  If this value is
 * not set by the application The default value is \ref SL_ZB_DEFAULT_IEEE_ADDR.
 */
u8_t              ieeeAddress[SL_ZB_IEEE_ADDR_LEN];
/**
 * The short address to be used by the Zigbee protocol stack.  This value is
 * only used if \ref setShortAddress is set to true.  If this value is not set
 * by the application The default value is \ref SL_ZB_DEFAULT_ROOT_SHORT_ADDR.
 */
u16_t             shortAddress;
} sl_zb_config_router_req;

/******************************************************************************/
/**
 * \struct sl_zb_config_router_cnf
 * This confirmation indicates whether or not the \ref SL_ZB_CONFIG_ROUTER_REQ
 * was successfully handled or not.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;
} sl_zb_config_router_cnf;

/******************************************************************************/
/**
 * \struct sl_zb_config_host_req
 * This request is used to configure the parameters that are used by the SL Task
 * to start up the Zigbee stack as a Host.  If this request is not sent by
 * the application, the Zigbee protocol stack will be started by default as a border
 * router.  This request is only valid when the SL Task has been built with the
 * Kitu Zigbee protocol stack.This request MUST be sent prior to the
 * \ref SL_STARTUP_REQ.
 *
 * Dependencies: MUST be sent prior to the \ref SL_STARTUP_REQ.
 */
typedef struct
{
  /**
   * Flag indicating if the Zigbee channel number should be set using the value
   * \ref channelNumber.
   */
  bool              setChannelNumber;
  /**
   * Flag indicating if the IEEE address should be set using the value
   * \ref ieeeAddress.
   */
  bool              setIeeeAddress;
  /**
   * Flag indicating if the polling interval should be set using the value
   * \ref pollingInterval.
   */
  bool              setPollingInterval;
  /**
   * Flag indicating if the short address should be set using the value
   * \ref shortAddress.
   */
  bool              setShortAddress;
  /**
   * Flag indicating if the sleep capability should be set using the value
   * \ref sleepCapability.
   */
  bool              setSleepCapability;
  /**
   * The channel number to be used by the Zigbee protocol stack.  This value is
   * only used if \ref setChannelNumber is set to true.  If this value is not set
   * by the application the default value is \ref SL_ZB_DEFAULT_CHAN_NUM.
   */
  sl_zb_chan_num_t  channelNumber;
  /**
   * The 64-bit IEEE address to be used by the Zigbee protocol stack.  This
   * value is only used if \ref setIeeeAddress is set to true.  If this value is
   * not set by the application the default value is \ref SL_ZB_DEFAULT_IEEE_ADDR.
   */
  u8_t              ieeeAddress[SL_ZB_IEEE_ADDR_LEN];
  /**
   * The polling interval to be used by the Zigbee protocol stack.  The polling
   * interval is in units of 1/10 seconds (e.g., 20 = 2 seconds).  This value is
   * only used if \ref setPollingInterval is set to true.  If this value is not
   * set by the application the default value is \ref SL_ZB_DEFAULT_POLLING_INTERVAL_SLEEPY
   * when \ref sleepCapability is set to \ref SL_ZB_SLEEP_CAPABILITY_SLEEPY, else
   * the default value is \ref SL_ZB_DEFAULT_POLLING_INTERVAL_NON_SLEEPY when
   * \ref sleepCapability is set to \ref SL_ZB_SLEEP_CAPABILITY_NON_SLEEPY.
   */
  u32_t             pollingInterval;
  /**
   * The short address to be used by the Zigbee protocol stack.  This value is
   * only used if \ref setShortAddress is set to true.  If this value is not set
   * by the application the default value is \ref SL_ZB_DEFAULT_ROOT_SHORT_ADDR.
   */
  u16_t             shortAddress;
  /**
   * The sleep capability to be used by the Zigbee protocol stack.  This value is
   * only used if \ref setSleepCapability is set to true.  If this value is not set
   * by the application the default value is \ref SL_ZB_DEFAULT_SLEEP_CAPABILITY.
   */
  sl_zb_sleep_capability_t  sleepCapability;
} sl_zb_config_host_req;

/******************************************************************************/
/**
 * \struct sl_zb_config_host_cnf
 * This confirmation indicates whether or not the \ref SL_ZB_CONFIG_HOST_REQ
 * was successfully handled or not.
 *
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;
} sl_zb_config_host_cnf;

/** @} */
// end addtogroup ZB_GROUP_MAIL_STRUCTS

/** @} */
// end addtogroup ZB_GROUP

/**
 * \defgroup SL_STACK_INFO Mail Structures
 * This section contains mail structures used with the Zigbee protocol stack.
 */
/** \addtogroup SL_STACK_INFO
 * @{ */
/******************************************************************************/
/**
 * \struct sl_stack_info_req
 * This request is used to retrieve stack information by the application layer.
 * 
 * \ref SL_STACK_INFO_CNF
 * 
 * Dependencies: none.
*/
typedef sl_server_obj_ref_t sl_stack_info_req;


/******************************************************************************/
/**
 * \struct sl_stack_info_cnf
 * This request is used to return stack information to the application layer.
 * 
 * \ref SL_STACK_INFO_REQ
 * 
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;

  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
  u32_t       transactionId;

  u16_t       sepStatsCounterRxEdcListOK;     // in some Apps, used for loss of server detection
  u16_t       sepStatsCounterRxDercListOK;    // in some Apps, used for loss of server detection
} sl_stack_info_cnf;

/** @} */
// end addtogroup SL_STACK_INFO

/**
 * \defgroup SL_DER_CLIENT_SET_DEVICE_TYPE Mail Structures
 * This section contains mail structures used with the Zigbee protocol stack.
 */
/** \addtogroup SL_DER_CLIENT_SET_DEVICE_TYPE
 * @{ */
/******************************************************************************/
/**
 * \struct sl_der_client_set_device_type_req
 * This request is used to retrieve stack information by the application layer.
 * 
 * \ref SL_DER_CLIENT_SET_DEVICE_TYPE_CNF
 * 
 * Dependencies: none.
*/
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
  u32_t                   transactionId;

  /**
   * The device category is a bitmap with each bit defined as below. Note that bits
   * 26-31 are reserved.
   */
  sl_xsd_dev_cat_bitmap_t devicetype;
} sl_der_client_set_device_type_req;


/******************************************************************************/
/**
 * \struct sl_der_client_set_device_type_cnf
 * This request is used to return stack information to the application layer.
 * 
 * \ref SL_DER_CLIENT_SET_DEVICE_TYPE_REQ
 * 
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;

  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
  u32_t       transactionId;
} sl_der_client_set_device_type_cnf;

/** @} */
// end addtogroup SL_DER_CLIENT_SET_DEVICE_TYPE


/**
 * \defgroup SL_DRLC_CLIENT_SET_DEVICE_TYPE Mail Structures
 * This section contains mail structures used with the Zigbee protocol stack.
 */
/** \addtogroup SL_DRLC_CLIENT_SET_DEVICE_TYPE
 * @{ */
/******************************************************************************/
/**
 * \struct sl_drlc_client_set_device_type_req
 * This request is used to retrieve stack information by the application layer.
 * 
 * \ref SL_DRLC_CLIENT_SET_DEVICE_TYPE_CNF
 * 
 * Dependencies: none.
*/
typedef struct {
  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
  u32_t                   transactionId;

  /**
   * The device category is a bitmap with each bit defined as below. Note that bits
   * 26-31 are reserved.
   */
  sl_xsd_dev_cat_bitmap_t devicetype;
} sl_drlc_client_set_device_type_req;



/******************************************************************************/
/**
 * \struct sl_drlc_client_set_device_type_cnf
 * This request is used to return stack information to the application layer.
 * 
 * \ref SL_DRLC_CLIENT_SET_DEVICE_TYPE_REQ
 * 
 * Dependencies: none.
*/
typedef struct {
  /**
   * Status of the operation.
   */
  sl_cmn_rc_t status;

  /**
   * transactionId is used to match the associated confirmation and indication
   * messages with the initial request message.
   */
  u32_t       transactionId;
} sl_drlc_client_set_device_type_cnf;

/** @} */
// end addtogroup SL_DRLC_CLIENT_SET_DEVICE_TYPE


/*******************************************************************************
 * Public Functions
 ******************************************************************************/
/** \addtogroup GENERAL_GROUP
 * @{ */
/******************************************************************************/
/* SL_ActivateSLTask
*/

/** \brief This function is called at initialization time  (i.e., from main())
 *         to create the SL task as a KAL task. No SL services are available
 *         until this function is called.
 */
void SL_ActivateSLTask(void);

/******************************************************************************/
/* SL_TaskHandle
*/
/** \brief The variable SL_TaskHandle stores the handle given to the SL task
 *         when it is created with KAL_TaskCreate().
 */
extern u8_t SL_TaskHandle;
/** @} */


/*******************************************************************************
 * Events
 ******************************************************************************/
// NOTE: Not released.
#define SL_STARTUP_COMPLETE_IND_BIT       (40)
#define SL_STARTUP_COMPLETE_IND_MASK      ((kal_event_t) (1ULL << SL_STARTUP_COMPLETE_IND_BIT))

/** \mainpage Services Layer Application Program Interface (G2H_0030)
 *
 * \section intro_sec Introduction
 *
 * This is the web interface to the SL API documentation, which defines the mail
 * messages and structures used on the SL API. Previously this information was
 * available as part of the "Services Layer API" document. It defines all of the mail
 * interfaces and structures that are used on the SL API. The interface is grouped by
 * commonly used structures and definitions, structures and definitions that are based
 * upon the CSEP sep.xsd, and structures and definitions used by each function set.
 *
 * <b>Please note that this interface is still under development and as such it is subject
 * to change.</b>
 *
 * \section version_sec Version
 *
 * This is version 1.23 of the SL API, and should be used in conjunction with version
 * 1.23 of the "Services Layer API" document, which contains general information about the interface
 * and use case diagrams. This version of the API is based upon:
 *   - IEEE Standard for Smart Energy Profile Application Protocol, IEEE 2030.5-2018, December 2018. 
 *
 * \section contents_sec Contents
 *
 * The API is divided in the following sections:
 * - \ref MAIL_IDS "List of all mail messages that are supported on the SL interface, and their mail IDs."
 * - \ref COMMON_GROUP "Common Definitions and Structures"
 * - \ref XSD_GROUP "XSD Definitions and Structures"
 * - \ref OBJ_GROUP "Server Object Definitions and Structures"
 * - \ref DCAP_GROUP "Device Capabilities: Definitions, structures, and mail structures used by the DCAP function set."
 * - \ref DER_GROUP "Distributed Energy Resource: Definitions, structures, and mail structures used by the DER function set."
 * - \ref EDER_SDER_GROUP "Self DER / EndDevice DER: Definitions, structures, and mail structures used by the EDER and SDER function sets."
 * - \ref DINFO_GROUP "Device Info: Definitions, structures, and mail structures used by the EDINFO and SDINFO function set."
 * - \ref DRLC_GROUP "Demand Response Load Control: Definitions, structures, and mail structures used by the DRLC function set."
 * - \ref DSTAT_GROUP "Device Status: Definitions, structures, and mail structures used by the EDSTAT and SDSTAT function sets."
 * - \ref EDEV_GROUP "End Device: Definitions, structures, and mail structures used by the EDEV function set."
 * - \ref FLOW_GROUP "Flow: Definitions, structures, and mail structures used by the Flow function set."
 * - \ref FSA_GROUP "Function Set Assignment: Definitions, structures, and mail structures used by the FSA function set."
 * - \ref METER_GROUP "Meter: Definitions, structures, and mail structures used by the Meter function set."
 * - \ref METER_MIRROR_GROUP "Meter Mirror: Definitions, structures, and mail structures used by the Meter Mirror function set."
 * - \ref MSG_GROUP "Message: Definitions, structures, and mail structures used by the Messaging function set."
 * - \ref PRICE_GROUP "Price: Definitions, structures, and mail structures used by the Pricing function set."
 * - \ref PWRSTAT_GROUP "Power Status: Definitions, structures, and mail structures used by the EPWRSTAT and SPWRSTAT function sets."
 * - \ref RESP_GROUP "Response: Definitions, structures, and mail structures used by the Response function set."
 * - \ref TIME_GROUP "Time: Definitions, structures, and mail structures used by the Time function set."
 * - \ref GENERAL_GROUP "General: Definitions, structures, and mail structures for general services like startup, mDNS, and security."
 * - \ref ZB_GROUP "Zigbee: Definitions, structures, and mail structures for configuring the Kitu Zigbee protocol stack."
 *
 * Note that a good starting point for those developers unfamiliar with the interface is
 * \ref MAIL_IDS "the list of supported mail messages and their associated mail IDs."
 *
 * \section doc_history_sec Document History
 *
 * <table>
 * <tr>
 *      <th>Version</th> <th>Modified By</th> <th>Description</th> <th>Date</th>
 * </tr>
 * <tr>
 *      <td>1.5</td>  <td>Kate Palumbo</td>
 *      <td>Initial release of HTML formatted API.</td>
 *      <td>3/19/2013</td>
 * </tr>
 * <tr>
 *      <td>1.6</td>  <td>Chris Leclercq</td>
 *      <td>Added sl_xsd_time_type_t, Flow APIs.</td>
 *      <td>3/28/2013</td>
 * </tr>
 * <tr>
 *      <td>1.7</td>  <td>Chris Leclercq</td>
 *      <td>Added DER APIs, updating to UML 13-0201</td>
 *      <td>5/17/2013</td>
 * </tr>
 * <tr>
 *      <td>1.8</td>  <td>Kate Palumbo</td>
 *      <td>FLOW/DER Server API changes.\n Added server event inds.</td>
 *      <td>6/17/2013</td>
 * </tr>
 * <tr>
 *      <td>1.9</td>  <td>Kate Palumbo</td>
 *      <td>Added dcap URI to sl_client_set_server_req.\n
 *          Added support for SL_SERVER_OBJ_DELETE_REQ/CNF.\n
 *          Modified DRLC to use SL_SERVER_OBJ* APIs.\n
 *          Reorganized DRLC server API data structures.\n
 *          Added FSA server APIs.\n
 *          Added Meter client APIs.\n
 *          Added new sl_sec_store_cert_req for use with clients and servers.</td>
 *      <td>6/27/2013</td>
 * </tr>
 * <tr>
 *      <td>1.10</td>  <td>Chris Leclercq</td>
 *      <td>Added Zigbee configuration APIs.\n</td>
 *      <td>7/08/2013</td>
 * </tr>
 * <tr>
 *      <td>1.11</td>  <td>Kate Palumbo</td>
 *      <td>Modified DRLC client interfaces to use generic list handling and to support FSA.\n
 *          Modified sl_xsd_read_qual_flags_type_t from u8_t to u16_t to match XSD.\n</td>
 *      <td>7/30/2013</td>
 * </tr>
 * <tr>
 *      <td>1.12</td>  <td>Kate Palumbo</td>
 *      <td>Added DER client list interfaces (using generic list handling interfaces).\n
 *          Modified DER structures for client and server.\n</td>
 *      <td>8/28/2013</td>
 * </tr>
 * <tr>
 *      <td>1.13</td>  <td>Kate Palumbo</td>
 *      <td>Added Flow client list interfaces (using generic list handling interfaces).\n
 *          Added Flow server delete functionality.\n
 *          Modified Flow structures for client and server.\n</td>
 *      <td>9/10/2013</td>
 * </tr>
 * <tr>
 *      <td>1.14</td>  <td>Kate Palumbo</td>
 *      <td>Added support for SL_SERVER_OBJ_STORE_REQ_CNF.\n
 *          Modified METER server to use SL_SERVER_OBJ* APIs including CREATE, DELETE, and STORE.\n
 *          Added support for multiple interfaces on the client.\n</td>
 *      <td>9/10/2013</td>
 * </tr>
 * <tr>
 *      <td>1.15</td>  <td>Chris Leclercq</td>
 *      <td>Modified Edev, Response, Message and Price servers to use SL_SERVER_OBJ* APIs.\n
 *          Modified Message client to use generic list handling interfaces.\n
 *          Added Message server support for object delete.\n
 *          Added DRLC client APIs to enable application selection of programs for event processing.</td>
 *      <td>12/9/2013</td>
 * </tr>
 * <tr>
 *      <td>1.16</td>  <td>Kate Palumbo</td>
 *      <td>Added delete interfaces for Price, EDEV, and response.\n
 *          Modified Price client and EDEV client to use generic list handling interfaces.\n
 *          Modified Price data structures to match other function sets.\n
 *          Added server name in server indications.\n
 *          Added server indication structure for Meter client.\n
 *          Send sl_flow_server_event_status_ind when FRQs are deleted from the flow server.\n
 *          Added status field to sl_meter_mirror_client_mup_ind. \n
 *          If the LFDI in the sl_resp_client_send_resp_req is all zeroes, use the LFDI of the client.\n
 *          Added support for run-time enable/disable of Default Security Policy.</td>
 *      <td>5/6/2014</td>
 * </tr>
 * <tr>
 *      <td>1.17</td>  <td>Kate Palumbo</td>
 *      <td>Added new SL_SEC_GET_SFDI_REQ/CNF interface to provide the SFDI and check digit to App. Also
 *          added the SFDI to the SL_SEC_STORE_CERT_CNF.\n
 *      <td>5/15/2014</td>
 * </tr>
 * <tr>
 *      <td>1.18</td>  <td>Kate Palumbo</td>
 *      <td>Released EDEV device info (EDINFO) interfaces.\n
 *      <td>6/24/2014</td>
 * </tr>
 * <tr>
 *      <td>1.19</td>  <td>Chris Leclercq</td>
 *      <td>Modified \ref SL_METER_MIRROR_CLIENT_SEND_MUP_REQ and \ref SL_METER_MIRROR_CLIENT_SERVER_IND to support
 *          multi-server.\n
 *          Added \ref SL_DRLC_CLIENT_SET_EVENT_ROOTS_REQ, \ref SL_DRLC_CLIENT_SET_EVENT_ROOTS_REQ, and
 *          \ref SL_DRLC_CLIENT_EVENT_ROOTS_IND interfaces to allow the app to select the root(server/source)
 *          for DRLC event handling.\n
 *          Added registration and status information to sl_cmn_client_server_ind_t.\n
 *          Added drpExists flag to \ref sl_drlc_client_drp_ind to indicate if the drp data exists in the
 *          message.\n
 *          Added status field to \ref sl_edev_client_send_enddev_cnf.\n
 *          Added transactionId field to \ref sl_edev_client_send_enddev_req  and \ref sl_edev_client_send_enddev_cnf.\n
 *          Added server information field to \ref sl_edinfo_client_send_dinfo_req, \ref sl_edev_client_server_found_ind
 *          and \ref sl_edev_client_send_enddev_req.\n
 *          Added \ref SL_EDEV_CLIENT_SERVER_STATUS_UNDETERMINED define to \ref sl_edev_client_server_status_t to
 *          indicate that SL was unable to determine the device's registration status.\n
 *          Added \ref SL_EDEV_SERVER_POST_EDEV_PENDING_IND and \ref SL_EDEV_SERVER_POST_EDEV_PENDING_RSP to allow app to accept or
 *          deny in-band edev registration.\n
 *          Added \ref SL_MSG_CLIENT_SET_EVENT_ROOTS_REQ, \ref SL_MSG_CLIENT_SET_EVENT_ROOTS_REQ and \ref SL_MSG_CLIENT_EVENT_ROOTS_IND
 *          interfaces to allow the app to select the root(server/source) for MSG event handling.\n
 *          Added \ref SL_MSG_CLIENT_SET_EVENT_PROGRAMS_REQ, \ref SL_MSG_CLIENT_SET_EVENT_PROGRAMS_REQ and \ref SL_MSG_CLIENT_EVENT_PROGRAMS_IND
 *          interfaces to allow the app to select the Message Programs for event handling.\n
 *          Added msgpExists flag to \ref sl_msg_client_msgp_ind to indicate if the msgp data exists in the message.\n
 *          Added \ref SL_DER_CLIENT_SET_EVENT_ROOTS_REQ, \ref SL_DER_CLIENT_SET_EVENT_ROOTS_REQ and \ref SL_DER_CLIENT_EVENT_ROOTS_IND
 *          interfaces to allow the app to select the root(server/source) for DER event handling.\n
 *          Added \ref SL_DER_CLIENT_SET_EVENT_PROGRAMS_REQ, ref SL_DER_CLIENT_SET_EVENT_PROGRAMS_REQ and \ref SL_DER_CLIENT_EVENT_PROGRAMS_IND
 *          interfaces to allow the app to select the DER Programs for event handling.\n
 *          Added derpExists flag to \ref sl_der_client_derp_ind to indicate if the derp data exists in the message.\n
 *          Added \ref SL_PRICE_CLIENT_SET_EVENT_ROOTS_REQ, \ref SL_PRICE_CLIENT_SET_EVENT_ROOTS_REQ and \ref SL_PRICE_CLIENT_EVENT_ROOTS_IND
 *          interfaces to allow the app to select the root(server/source) for Price event handling.\n
 *          Added \ref SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_REQ, \ref SL_PRICE_CLIENT_SET_EVENT_PROGRAMS_REQ and \ref SL_PRICE_CLIENT_EVENT_PROGRAMS_IND
 *          interfaces to allow the app to select the Rate Components for event handling.\n
 *          Added tpExists flag to \ref sl_price_client_tp_ind to indicate if the tp data exists in the message.\n
 *          Added rcExists flag to \ref sl_price_client_rc_ind to indicate if the rc data exists in the message.\n
 *          Added \ref SL_DCAP_CLIENT_GET_DCAP_REQ, \ref SL_DCAP_CLIENT_GET_DCAP_CNF, and \ref SL_DCAP_CLIENT_SERVER_IND interfaces
 *          to allow the app to request DCAP resource availability information from the Server. \n
 *      <td>7/30/2014</td>
 * </tr>
 * <tr>
 *      <td>1.20</td>  <td>Chris Leclercq</td>
 *      <td>Release epwrstat, edstat, and eder client interfaces.\n
 *          Added \ref sl_cmn_client_server_ind_t to \ref sl_flow_client_server_ind.\n
 *          Added server and source information to \ref sl_meter_mirror_client_mup_ind.\n
 *          Added client \ref SL_DER_CLIENT_SET_EVENT_POLL_RATE_REQ, \ref SL_DRLC_CLIENT_SET_EVENT_POLL_RATE_REQ, \ref SL_FLOW_CLIENT_SET_EVENT_POLL_RATE_REQ, \ref SL_MSG_CLIENT_SET_EVENT_POLL_RATE_REQ, \ref SL_PRICE_CLIENT_SET_EVENT_POLL_RATE_REQ interfaces.\n
 *          Added \ref SL_TIME_CLIENT_SERVER_IND interface.\n
 *          Added \ref SL_DRLC_CLIENT_SET_APPLIED_VALUES_REQ interface.\n
 *          Added userAck flag to \ref sl_drlc_client_opt_out_edc_req.\n
 *          Corrected \ref sl_drlc_edc_t coolSetpoint and heatSetpoint fields from unsigned to signed.
 *      <td>10/1/2014</td>
 * </tr>
 * <tr>
 *      <td>1.21</td>  <td>Chris Leclercq</td>
 *      <td>Changed sl_edev_client_post_enddev_req to \ref sl_edev_client_send_enddev_req and added functionality for PUTing to an existing edev resource.\n
 *          Added \ref SL_EDER_SERVER_DERA_IND, \ref SL_EDER_SERVER_DERCAP_IND, \ref SL_EDER_SERVER_DERS_IND, \ref SL_EDER_SERVER_DERSETT_IND.\n
 *      <td>12/4/2014</td>
 * </tr>
 * <tr>
 *      <td>1.22</td>  <td>Ming Zeng</td>
 *      <td>Added data member 'edevId' into sl_eder_server_dera_ind, sl_eder_server_dercap_ind, sl_eder_server_ders_ind and sl_eder_server_dersett_ind for client indentification.\n
 *      <td>9/20/2016</td>
 * </tr>
 * <tr>
 *      <td>1.23</td>  <td>Alex Kagan</td>
 *      <td>General cleanup, renamings, formatting.\n
 *      <td>7/20/2020</td>
 * </tr>
 * </tr>
 * </table>
 *
 * \section copyright_sec Copyright
 *
 * <p>Copyright (C) 2020 Kitu Systems, Inc. All rights reserved.
 * This documentation is the proprietary
 * information of Kitu Systems, Inc and is confidential in nature.
 */


#endif
