/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE_Evt_Handler.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  nRF51_BLE_Evt_Handler header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_EVT_HANDLER_H
#define __NRF51_BLE_EVT_HANDLER_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_Sys_Evt_Handler(uint32_t sys_evt);                    // sys事件回调
extern  void nRF51_BLE_Evt_Handler(ble_evt_t * p_ble_evt);               // BLE事件回调



#endif /* __NRF51_BLE_EVT_HANDLER_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/

