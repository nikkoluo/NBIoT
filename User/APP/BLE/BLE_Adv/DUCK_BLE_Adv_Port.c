/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Adv_Port.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  蓝牙广播配置
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Adv_Port.h"
#include "Duck_BLE_Adv.h"
#include "ble_srv_common.h"
#include "Duck_BLE_Adv_MIOT.h"
#include "Duck_BLE_Private_Service.h"
#include "ble_advdata.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

                                
/* Private function prototypes -----------------------------------------------*/

void BLE_Adv_Start(u32 uiTimeout);                                      // 启动广播
void BLE_Adv_Package(void);                                             // 广播数据打包

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
*                           陆超@2017-01-10
* Function Name  :  BLE_Adv_Package
* Description    :  广播配置初始化
* Input          :  u16 usEvent 待打包的事件
*                   MIOT_Typedef *MIOT
* Output         :  None
* Return         :  None
*******************************************************************************/
void BLE_Adv_Package(void)
{
    u32           Err_Code;
//    u8            ucService_Data[MIOT_MAX_SIZE];
    ble_advdata_t Adv_Data;
    ble_advdata_t Scan_Rsp;
//    ble_advdata_service_data_t Service_Data;
    ble_uuid_t Scan_UUIDs[] = {{BLE_UUID_BATTERY_SERVICE, BLE_UUID_TYPE_BLE},
                               {BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}};
    // 清空缓存    
    memset(&Adv_Data, 0, sizeof(Adv_Data));
//    memset(&ucService_Data, 0, MIOT_MAX_SIZE);

//    Scan_Rsp.name_type               = BLE_ADVDATA_FULL_NAME;
    
    // 1组私有服务
//    Adv_Data.service_data_count   = 1;
//    Service_Data.data.p_data      = ucService_Data;
//    Adv_Data.p_service_data_array = &Service_Data;


    // 广播类型
    Adv_Data.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    

//    // 服务UUID
//    Service_Data.service_uuid   = MIOT_SERVICE_ID;

//    // 准备要发送的数据
//    MIOT->Frame_Control_Bit.Event_Include = 1;
//    MIOT->Event_ID         = usEvent; 
//    MIOT->Current_Event_ID = MIOT->Event_ID;
//    Service_Data.data.size = BLE_MIOT_Service_Package(MIOT->Event_ID, ucService_Data, MIOT);
//    (MIOT->Frame_Counter)++;

    // 清空缓存
    memset(&Scan_Rsp, 0, sizeof(Scan_Rsp)); 
    Scan_Rsp.name_type               = BLE_ADVDATA_FULL_NAME;
    Scan_Rsp.uuids_complete.uuid_cnt = sizeof(Scan_UUIDs) / sizeof(Scan_UUIDs[0]);
    Scan_Rsp.uuids_complete.p_uuids  = Scan_UUIDs;
    Err_Code = ble_advdata_set(&Adv_Data, &Scan_Rsp);

    
    APP_ERROR_CHECK(Err_Code);
    
}// End of void BLE_Adv_Package(void)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  BLE_Adv_Start
* Description    :  启动广播
* Input          :  u32 uiTimeout   超时时间
* Output         :  None
* Return         :  None
*******************************************************************************/
void BLE_Adv_Start(u32 uiTimeout)
{
    u32                  Err_Code;    
    ble_gap_adv_params_t Adv_Params;


    BLE_Adv_Package();
    
    // Start advertising.
    memset(&Adv_Params, 0, sizeof(Adv_Params));
    
    Adv_Params.type        = BLE_GAP_ADV_TYPE_ADV_IND;                  // 非定向可连接模式
    Adv_Params.p_peer_addr = NULL;
    Adv_Params.fp          = BLE_GAP_ADV_FP_ANY;                        // 不过滤
    Adv_Params.interval    = BLE_ADV_INTERVAL;                          // 广播间隔
    Adv_Params.timeout     = uiTimeout;                                 // 广播超时时间
 
    Err_Code = sd_ble_gap_adv_start(&Adv_Params);

    if (Err_Code != NRF_SUCCESS)
    {
        app_trace_log("广播启动错误码 %d!\r\n", Err_Code);

    }
    else
    {
        // 进入广播态
        Sys_Status = SYS_STATUS_ADV;
    }


}// End of void BLE_Adv_Start(u32 uiTimeout)


/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




