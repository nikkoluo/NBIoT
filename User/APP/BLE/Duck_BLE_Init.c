/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Duck_BLE_Init.c
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/26/2016
* Description        :  Duck_BLE初始化
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Init.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "ble_hci.h"
#include "ble_gap.h"
#include "ble_advertising.h"
#include "Duck_BLE_Adv.h"
#include "Duck_BLE_Evt_Handler.h"
#include "Duck_BLE_DevInfo_Service.h"
#include "Duck_BLE_Private_Service.h"
#include "Duck_BLE_Peer.h"
#include "ble_conn_params.h"
#include "pstorage.h"
#include "nRF51_DFU.h"
#include "nRF51_Storage.h"
#include "Duck_BLE_Adv_Port.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_Init(void);                                               // Duck_BLE初始化
void Duck_BLE_Stack_Init(void);                                         // Duck_BLE栈初始化
void Duck_BLE_Tx_Power_Set(s32 iPower);                                 // 设置发射功率

void GAP_Parameters_Init(void);                                         // GAP参数设置

void BLE_Services_Init(void);                                           // BLE服务初始化


void Connect_Parameters_Init(void);                                     // 连接参数初始化
void Connect_Parameters_Event_Handler(ble_conn_params_evt_t * p_evt);   // 连接参数处理事件
void Connect_Parameters_Error_Handler(u32 Nrf_Error);                   // 连接参数错误处理

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  Duck_BLE_Init
* Description    :  Duck_BLE初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Init(void)
{
#ifndef BLE_OPEN


    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_RC_250_PPM_8000MS_CALIBRATION, NULL);

#else

    // BLE堆初始化
    Duck_BLE_Stack_Init();

    // 先初始化flash
    Duck_BLE_Peer_Manager_Init(0);

    // 储存初始化
    nRF51_Storage_Init();

    // 通用访问配置初始化
    GAP_Parameters_Init();

    // 设置发射功率
    Duck_BLE_Tx_Power_Set(0);

    // BLE服务初始化
    BLE_Services_Init();

    // 连接参数初始化
    Connect_Parameters_Init();

    BLE_Adv_Start(0);

#endif

}// End of void Duck_BLE_Init(void)


/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  Duck_BLE_Stack_Init
* Description    :  Duck_BLE栈初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Stack_Init(void)
{
    u32 err_code;

#ifdef NRF51DK

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, softdevice_evt_schedule);
    
#else

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_RC_250_PPM_8000MS_CALIBRATION, softdevice_evt_schedule);
    
#endif

    // Enable BLE stack.
    ble_enable_params_t ble_enable_params;
    memset(&ble_enable_params, 0, sizeof(ble_enable_params));

    ble_enable_params.gatts_enable_params.service_changed = 1;
    err_code = sd_ble_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);


    // 注册BLE事件回调
    err_code = softdevice_ble_evt_handler_set(Duck_BLE_Evt_Handler);
    APP_ERROR_CHECK(err_code);

    // 注册sys事件回调
    err_code = softdevice_sys_evt_handler_set(Duck_Sys_Evt_Handler);
    APP_ERROR_CHECK(err_code);


    
}// End of void Duck_BLE_Stack_Init(void)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  Connect_Parameters_Init
* Description    :  连接参数初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Connect_Parameters_Init(void)
{
    u32                    Err_Code;
    ble_conn_params_init_t CP_Init;
    
    memset(&CP_Init, 0, sizeof(CP_Init));

    CP_Init.p_conn_params                  = NULL;
    CP_Init.first_conn_params_update_delay = DUCK_FIRST_CONN_PARAMS_UPDATE_DELAY;  // 首次刷新时间
    CP_Init.next_conn_params_update_delay  = DUCK_NEXT_CONN_PARAMS_UPDATE_DELAY;   // 两帧间隔 4.0规范是30s
    CP_Init.max_conn_params_update_count   = DUCK_MAX_CONN_PARAMS_UPDATE_COUNT;
    CP_Init.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
    CP_Init.disconnect_on_fail             = false;
    CP_Init.evt_handler                    = Connect_Parameters_Event_Handler;
    CP_Init.error_handler                  = Connect_Parameters_Error_Handler;
    
    Err_Code = ble_conn_params_init(&CP_Init);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void Connect_Parameters_Init(void)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  Connect_Parameters_Error_Handler
* Description    :  连接参数错误处理
* Input          :  u32 Nrf_Error  错误编号
* Output         :  None
* Return         :  None
*******************************************************************************/
void Connect_Parameters_Error_Handler(u32 Nrf_Error)
{
    APP_ERROR_HANDLER(Nrf_Error);
    
}// End of void Connect_Parameters_Error_Handler(u32 Nrf_Error)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  Connect_Parameters_Event_Handler
* Description    :  连接参数事件处理
* Input          :  ble_conn_params_evt_t * p_evt   待处理事件
* Output         :  None
* Return         :  None
*******************************************************************************/
void Connect_Parameters_Event_Handler(ble_conn_params_evt_t * p_evt)
{
    uint32_t err_code;
    
    if(p_evt->evt_type == BLE_CONN_PARAMS_EVT_FAILED)
    {
        err_code = sd_ble_gap_disconnect(BLE_Connect_Handle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
        APP_ERROR_CHECK(err_code);
    }
    
}// End of void Connect_Parameters_Event_Handler(ble_conn_params_evt_t * p_evt)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  Duck_BLE_Tx_Power_Set
* Description    :  设置发射功率
* Input          :  s32 iPower 发射功率
*                   -40, -30, -20, -16, -12, -8, -4, 0, 4  (dBm)
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Tx_Power_Set(s32 iPower)
{
    u32  err_code;
    
    // 设置发射功率
    err_code = sd_ble_gap_tx_power_set(0);
    APP_ERROR_CHECK(err_code);
    
}// End of void Duck_BLE_Tx_Power_Set(s32 iPower)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  GAP_Parameters_Init
* Description    :  GAP协议初始化 GAP(Generic Access Profile)
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GAP_Parameters_Init(void)
{
    u32  err_code;
    ble_gap_conn_params_t   gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;

    // 配置加密模式为不加密
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    // 配置设备名称
    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *) BLE_DEVICE_NAME,
                                          strlen(BLE_DEVICE_NAME));
    APP_ERROR_CHECK(err_code);

    // 产品描述
    err_code = sd_ble_gap_appearance_set(BLE_APPEARANCE_GENERIC_THERMOMETER);
    APP_ERROR_CHECK(err_code);

    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    // 设置PPCP(Peripheral Preferred Connection Parameters)
    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);


    
}// End of void GAP_Parameters_Init(void)




/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  BLE_Services_Init
* Description    :  BLE服务初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void BLE_Services_Init(void)
{
  
    // 私有服务初始化
    Duck_BLE_Private_Services_Init();

    // 设备信息初始化
    Duck_BLE_DevInfo_Services_Init();

    // DFU服务
    nRF51_BLE_DFU_Services_Init();


    
}// End of void BLE_Services_Init(void)



/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/




