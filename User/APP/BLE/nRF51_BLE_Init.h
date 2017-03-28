/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  nRF51_BLE_Init.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/26/2016
* Description        :  nRF51_BLE_Init header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_INIT_H
#define __NRF51_BLE_INIT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
                         

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_BLE_Init(void);                                       // nRF51_BLE初始化
extern  void nRF51_BLE_Tx_Power_Set(s32 iPower);                         // 设置发射功率


#endif /* __NRF51_BLE_INIT_H */

/******************* (C) COPYRIGHT 2016 陆超 *****END OF FILE******************/

