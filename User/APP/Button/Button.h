/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Button.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Button header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H

/* Includes ------------------------------------------------------------------*/
#include "Button_Port.h"


/* Private define ------------------------------------------------------------*/
#define     CLICK_MIN_DURATION          25                              // 单击最小持续时间ms
#define     CLICK_MAX_DURATION          800                             // 单击最大持续时间ms
#define     DOUBLE_HIT_INTERVAL         200                             // 单击识别间隔 两次单击在间隔内则视为连击
#define     LONG_CLICK_MIN_DURATION     1500                            // 长按最小持续时间ms
#define     RESET_CLICK_MIN_DURATION    10000                           // 重启系统

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Button_Timer_Handle(void *p_arg);                          // Button任务
extern  void Button_Task_Create(void);                                  // 创建Button任务
extern  void Button_Free_ISR(void);                                     // Button释放中断处理
extern  void Button_Push_ISR(void);                                     // Button下降沿中断处理

#endif /* __BUTTON_H */

/******************* (C) COPYRIGHT 2016 陆超 *****END OF FILE******************/

