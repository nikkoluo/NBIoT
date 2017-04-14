/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE_Evt_Handler.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  BLE event 处理 任务
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE_Evt_Handler.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "ble_hci.h"
#include "ble_advertising.h"
#include "nRF51_BLE_Adv.h"
#include "nRF51_BLE_Private_Service.h"
#include "pstorage.h"
#include "device_manager.h"
#include "ble_conn_params.h"
#include "nRF51_BLE_Adv_Port.h"

/* Private variables ---------------------------------------------------------*/
#define APP_FEATURE_NOT_SUPPORTED       BLE_GATT_STATUS_ATTERR_APP_BEGIN + 2        /**< Reply when unsupported features are requested. */


/* Private function prototypes -----------------------------------------------*/
void ON_BLE_Event(ble_evt_t * p_ble_evt);                               // BLE事件处理
void nRF51_Sys_Evt_Handler(uint32_t sys_evt);                           // sys事件回调
void nRF51_BLE_Evt_Handler(ble_evt_t * p_ble_evt);                      // BLE事件回调

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  ON_BLE_EVENT
* Description    :  BLE事件回调函数
* Input          :  ble_evt_t * p_ble_evt   // 待处理的事件
* Output         :  None
* Return         :  None
*******************************************************************************/
void ON_BLE_Event(ble_evt_t * p_ble_evt)
{
    u32 err_code;
    switch (p_ble_evt->header.evt_id)
    {
        // 连接建立
        case BLE_GAP_EVT_CONNECTED:

            BLE_Connect_Handle = p_ble_evt->evt.gap_evt.conn_handle;
            app_trace_log("开始连接，ON_BLE_Event线程的信息!\r\n");

            // 进入连接态
            Sys_Status = SYS_STATUS_CONNECT;
//            LCD_BT_Update_Signal(1);

            break;

        // 断开连接
        case BLE_GAP_EVT_DISCONNECTED:

            BLE_Connect_Handle = BLE_CONN_HANDLE_INVALID;
            app_trace_log("结束连接，ON_BLE_Event线程的信息!\r\n");
//            LCD_BT_Update_Signal(0);

            // 重新发送广播包
            BLE_Adv_Start(0);

            break;
        
       case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            err_code = sd_ble_gatts_sys_attr_set(BLE_Connect_Handle, NULL, 0, 0);
            APP_ERROR_CHECK(err_code);
            break;
          
        default:
            // No implementation needed.
            break;
    }
    
}// End of void ON_BLE_Event(ble_evt_t * p_ble_evt)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  nRF51_Sys_Evt_Handler
* Description    :  Sys事件回调
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_Sys_Evt_Handler(uint32_t sys_evt)
{
    // 系统写flash事件回调
    pstorage_sys_event_handler(sys_evt);

//    // fds失败后再次广播
//    ble_advertising_on_sys_evt(sys_evt);
    
}// End of void nRF51_Sys_Evt_Handler(uint32_t sys_evt)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  nRF51_BLE_Evt_Handler
* Description    :  BLE事件回调
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Evt_Handler(ble_evt_t * p_ble_evt)
{

    // 绑定事件
    dm_ble_evt_handler(p_ble_evt);
    ble_conn_params_on_ble_evt(p_ble_evt);
    ble_bas_on_ble_evt(&Bat_Level_Service, p_ble_evt);
    ON_BLE_Event(p_ble_evt);
    BLE_Advertising_on_ble_evt(p_ble_evt);

    // dfu事件
    ble_dfu_on_ble_evt(&nRF51_DFU_Services, p_ble_evt);

    nRF51_BLE_Private_Evt(&nRF51_BLE_Service, p_ble_evt);
    



}// End of void nRF51_BLE_Evt_Handler(ble_evt_t * p_ble_evt)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




