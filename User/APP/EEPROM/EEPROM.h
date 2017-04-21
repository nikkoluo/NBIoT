/******************** (C) COPYRIGHT 2015 陆超 **********************************
* File Name          :  EEPROM.h
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROM header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H
#define __EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "EEPROM_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void EEPROM_Task_Handle(void *p_arg);                           // EEPROM任务
extern  void EEPROM_Task_Create(void);                                  // 创建EEPROM任务


#endif /* __EEPROM_H */

/******************* (C) COPYRIGHT 2015 陆超 *****END OF FILE******************/

