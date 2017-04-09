/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "LCD_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void LCD_Timer_Handle(void *p_arg);                             // LCD任务
extern  void LCD_Task_Create(void);                                     // 创建LCD任务
extern  void LCD_Get(void);                                             // 获取温湿度

#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2017 陆超 **** END OF FILE *****************/

