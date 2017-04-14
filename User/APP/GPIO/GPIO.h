/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  GPIO.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIO header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "GPIO_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void GPIO_Timer_Handle(void *p_arg);                            // GPIO任务
extern  void GPIO_Task_Create(void);                                    // 创建GPIO任务
extern  void GPIO_TEST_High(void);                                      // Test Pin拉高
extern  void GPIO_TEST_Low(void);                                       // Test Pin拉低                      
extern  void GPIO_TEST_Toggle(void);                                    // Test Pin翻转

#endif /* __GPIO_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/

