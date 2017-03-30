/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  nRF51_BLE header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_H
#define __NRF51_BLE_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_BLE_Task_Create(void);                               // BLE任务创建
extern  void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID);                     // 特殊任务设置



#endif /* __NRF51_BLE_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/

