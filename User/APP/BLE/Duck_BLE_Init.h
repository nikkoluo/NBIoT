/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Duck_BLE_Init.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/26/2016
* Description        :  Duck_BLE_Init header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_INIT_H
#define __DUCK_BLE_INIT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
                         

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Duck_BLE_Init(void);                                       // Duck_BLE初始化
extern  void Duck_BLE_Tx_Power_Set(s32 iPower);                         // 设置发射功率


#endif /* __DUCK_BLE_INIT_H */

/******************* (C) COPYRIGHT 2016 陆超 *****END OF FILE******************/

