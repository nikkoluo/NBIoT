/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE_Adv.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  蓝牙广播包处理
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE_Adv.h"
#include <stdlib.h>
#include <string.h>
#include "nrf_soc.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void BLE_Advertising_on_ble_evt(ble_evt_t const * p_ble_evt);           // 广播事件处理
void nRF51_BLE_Bond_Adv_Handle(void *p_arg);                            // 绑定广播

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  BLE_Advertising_on_ble_evt
* Description    :  广播事件处理
* Input          :  ble_evt_t const * p_ble_evt 时间参数
* Output         :  None
* Return         :  None
*******************************************************************************/
void BLE_Advertising_on_ble_evt(ble_evt_t const * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
//        case BLE_GAP_EVT_CONNECTED:
//        {
//            app_trace_log("开始连接，广播线程的信息!\r\n");
//        }
//        break;

//        // Upon disconnection, whitelist will be activated and direct advertising is started.
//        case BLE_GAP_EVT_DISCONNECTED:
//        {
//            app_trace_log("结束连接，广播线程的信息!\r\n");
//            
//        }break;

        
        // Upon time-out, the next advertising mode is started, i.e. go from fast to slow or from slow to idle.
        case BLE_GAP_EVT_TIMEOUT:
        {
            if (p_ble_evt->evt.gap_evt.params.timeout.src == BLE_GAP_TIMEOUT_SRC_ADVERTISING)
            {
                app_trace_log("广播超时，广播线程的信息!\r\n"); 


            }
            
        }break;

        default:
        break;
    }
    
}// End of void BLE_Advertising_on_ble_evt(ble_evt_t const * p_ble_evt)

/*******************************************************************************
*                           陆超@2017-02-22
* Function Name  :  nRF51_BLE_Bond_Adv_Handle
* Description    :  绑定广播处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Bond_Adv_Handle(void *p_arg)
{


}// End of void nRF51_BLE_Bond_Adv_Handle(void *p_arg)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/










