/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD_Port.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_PORT_H
#define __LCD_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void LCD_Variable_Init(void);                                   // LCD变量初始化
extern  u8 LCD_Port_Init(void);                                         // 管脚初始化


#endif /* __LCD_PORT_H */

/******************* (C) COPYRIGHT 2017 陆超 **** END OF FILE *****************/
