/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  GPIO_Port.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIO_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_PORT_H
#define __GPIO_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/




/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void GPIO_Variable_Init(void);                                  // 温湿度变量初始化
extern  void GPIO_Port_Init(void);                                      // 管脚初始化
extern  void GPIO_Set_Pin_High(u8 ucPin);                               // 管脚置高
extern  void GPIO_Set_Pin_Low(u8 ucPin);                                // 管脚置低   

#endif /* __GPIO_PORT_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/
