/******************** (C) COPYRIGHT 2015 陆超 **********************************
* File Name          :  Debug.h
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/14/2015
* Description        :  Debug header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H
#define __DEBUG_H

/* Includes ------------------------------------------------------------------*/
#include "Debug_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Debug_Task_Create(void);                                   // 创建调试任务
extern  void Receive_Data_Handler(u8* ucData, u16 usLen);               // 接收数据处理

#endif /* __DEBUG_H */

/******************* (C) COPYRIGHT 2015 陆超 *****END OF FILE******************/

