/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE_Adv.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  蓝牙广播包处理头文件
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_ADV_H
#define __NRF51_BLE_ADV_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "nRF51_BLE_Adv_Port.h"

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void BLE_Advertising_on_ble_evt(ble_evt_t const * p_ble_evt);   // 广播事件处理
extern  void nRF51_BLE_Bond_Adv_Handle(void *p_arg);                    // 绑定广播

#endif /* __NRF51_BLE_ADV_H */

/******************* (C) COPYRIGHT 2017 陆超 ***** END OF FILE ****************/




