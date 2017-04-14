/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Communal_Timer.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/22/2017
* Description        :  Communal_Timer header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMUNAL_TIMER_H
#define __COMMUNAL_TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Communal_Timer_Timer_Handle(void *p_arg);                  // Communal_Timer任务
extern  void Communal_Timer_Task_Create(void);                          // 创建Communal_Timer任务


#endif /* __COMMUNAL_TIMER_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/

