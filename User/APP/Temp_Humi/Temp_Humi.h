/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Temp_Humi.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Temp_Humi header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMP_HUMI_H
#define __TEMP_HUMI_H

/* Includes ------------------------------------------------------------------*/
#include "Temp_Humi_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Temp_Humi_Timer_Handle(void *p_arg);                           // Temp_Humi任务
extern  void Temp_Humi_Task_Create(void);                                   // 创建Temp_Humi任务
extern  void Temp_Humi_Get(void);                                           // 获取温湿度

#endif /* __TEMP_HUMI_H */

/******************* (C) COPYRIGHT 2016 陆超 **** END OF FILE *****************/

