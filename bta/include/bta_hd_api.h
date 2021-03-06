/******************************************************************************
 *
 *  Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *  Not a Contribution.
 *  Copyright (C) 2002-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/
#ifndef BTA_HD_API_H
#define BTA_HD_API_H

#include "bta_api.h"
#include "hidd_api.h"

/*****************************************************************************
**  Constants and Type Definitions
*****************************************************************************/
#ifndef BTA_HD_DEBUG
#define BTA_HD_DEBUG    FALSE
#endif

/* BTA HID Device callback events */
#define BTA_HD_ENABLE_EVT         0  /* BT-HD enabled */
#define BTA_HD_DISABLE_EVT        1  /* BT-HD disabled */
#define BTA_HD_REGISTER_APP_EVT   2  /* application registered */
#define BTA_HD_UNREGISTER_APP_EVT 3  /* application unregistered */
#define BTA_HD_OPEN_EVT           4  /* connection to host opened */
#define BTA_HD_CLOSE_EVT          5  /* connection to host closed */
#define BTA_HD_GET_REPORT_EVT     6  /* GET_REPORT request from host */
#define BTA_HD_SET_REPORT_EVT     7  /* SET_REPORT request from host */
#define BTA_HD_SET_PROTOCOL_EVT   8  /* SET_PROTOCOL request from host */
#define BTA_HD_INTR_DATA_EVT      9  /* DATA received from host on intr */
#define BTA_HD_VC_UNPLUG_EVT     10  /* Virtual Cable Unplug */
#define BTA_HD_API_ERR_EVT       99  /* BT-HD API error */

typedef UINT16 tBTA_HD_EVT;

enum
{
    BTA_HD_OK,
    BTA_HD_ERROR
};
typedef UINT8 tBTA_HD_STATUS;

typedef tHID_DEV_DSCP_INFO tBTA_HD_DEV_DESCR;

typedef struct
{
    const char          *p_name;
    const char          *p_description;
    const char          *p_provider;
    UINT8               subclass;
    tBTA_HD_DEV_DESCR   descriptor;
} tBTA_HD_APP_INFO;

typedef struct
{
    UINT8  service_type;
    UINT32 token_rate;
    UINT32 token_bucket_size;
    UINT32 peak_bandwidth;
    UINT32 access_latency;
    UINT32 delay_variation;
} tBTA_HD_QOS_INFO;

typedef struct
{
    BOOLEAN use_intr;
    UINT8   type;
    UINT8   id;
    UINT16  len;
    UINT8   *p_data;
} tBTA_HD_REPORT;

typedef struct
{
    tBTA_HD_STATUS  status;
    BOOLEAN         in_use;
    BD_ADDR         bda;
} tBTA_HD_REG_STATUS;

typedef struct
{
    BD_ADDR         bda;
    tBTA_HD_STATUS  status;
} tBTA_HD_CONN;

typedef struct
{
    UINT8   report_type;
    UINT8   report_id;
    UINT16  buffer_size;
} tBTA_HD_GET_REPORT;

typedef struct
{
    UINT8   report_type;
    UINT8   report_id;
    UINT16  len;
    UINT8   *p_data;
} tBTA_HD_SET_REPORT;

typedef UINT8 tBTA_HD_SET_PROTOCOL;

typedef struct
{
    UINT8   report_id;
    UINT16  len;
    UINT8   *p_data;
} tBTA_HD_INTR_DATA;

/* union of data associated with HD callback */
typedef union
{
    tBTA_HD_STATUS  status;  /* BTA_HD_ENABLE_EVT
                                BTA_HD_DISABLE_EVT
                                BTA_HD_UNREGISTER_APP_EVT */
    tBTA_HD_REG_STATUS reg_status; /* BTA_HD_REGISTER_APP_EVT */
    tBTA_HD_CONN    conn;    /* BTA_HD_OPEN_EVT
                                BTA_HD_CLOSE_EVT
                                BTA_HD_VC_UNPLUG_EVT
                                BTA_HD_OWN_VC_UNPLUG_EVT */
    tBTA_HD_GET_REPORT get_report; /* BTA_HD_GET_REPORT */
    tBTA_HD_SET_REPORT set_report; /* BTA_HD_SET_REPORT */
    tBTA_HD_SET_PROTOCOL set_protocol; /* BTA_HD_SETPROTOCOL */
    tBTA_HD_INTR_DATA    intr_data;    /* BTA_HD_INTR_DATA_EVT */
} tBTA_HD;

/* BTA HD callback function */
typedef void (tBTA_HD_CBACK) (tBTA_HD_EVT event, tBTA_HD *p_data);

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         BTA_HhRegister
**
** Description      This function enable HID host and registers HID-Host with
**                  lower layers.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdEnable(tBTA_HD_CBACK *p_cback);

/*******************************************************************************
**
** Function         BTA_HhDeregister
**
** Description      This function is called when the host is about power down.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdDisable(void);

/*******************************************************************************
**
** Function         BTA_HdRegisterApp
**
** Description      This function is called when application should be registered
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdRegisterApp(tBTA_HD_APP_INFO *p_app_info,
                                tBTA_HD_QOS_INFO *p_in_qos, tBTA_HD_QOS_INFO *p_out_qos);

/*******************************************************************************
**
** Function         BTA_HdUnregisterApp
**
** Description      This function is called when application should be unregistered
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdUnregisterApp(void);

/*******************************************************************************
**
** Function         BTA_HdSendReport
**
** Description      This function is called when report is to be sent
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdSendReport(tBTA_HD_REPORT *p_report);

/*******************************************************************************
**
** Function         BTA_HdVirtualCableUnplug
**
** Description      This function is called when VCU shall be sent
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdVirtualCableUnplug(void);

/*******************************************************************************
**
** Function         BTA_HdConnect
**
** Description      This function is called when connection to host shall be made
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdConnect(void);

/*******************************************************************************
**
** Function         BTA_HdDisconnect
**
** Description      This function is called when host shall be disconnected
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdDisconnect(void);

/*******************************************************************************
**
** Function         BTA_HdAddDevice
**
** Description      This function is called when a device is virtually cabled
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdAddDevice(BD_ADDR addr);

/*******************************************************************************
**
** Function         BTA_HdRemoveDevice
**
** Description      This function is called when a device is virtually uncabled
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdRemoveDevice(BD_ADDR addr);

/*******************************************************************************
**
** Function         BTA_HdReportError
**
** Description      This function is called when reporting error for set report
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_HdReportError(UINT8 error);

#ifdef __cplusplus
}
#endif

#endif  /* BTA_HD_API_H */
