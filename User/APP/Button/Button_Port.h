/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Button_Port.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Button_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_PORT_H
#define __BUTTON_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Button_Variable_Init(void);                                // 按键屏变量初始化
extern  void Button_Pin_Handler(u8 ucPin_No, u8 ucAction);              // 按键管脚处理


#endif /* __BUTTON_PORT_H */

/******************* (C) COPYRIGHT 2016 陆超 *****END OF FILE******************/
