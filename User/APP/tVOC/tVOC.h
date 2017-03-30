/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  tVOC.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/29/2017
* Description        :  tVOC header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TVOC_H
#define __TVOC_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void tVOC_Timer_Handle(void *p_arg);                           // tVOC任务
extern  void tVOC_Task_Create(void);                                   // 创建tVOC任务
extern  void tVOC_Get(void);                                           // 获取温湿度

#endif /* __TVOC_H */

/******************* (C) COPYRIGHT 2017 陆超 **** END OF FILE *****************/

