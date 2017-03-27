/******************** (C) COPYRIGHT 2017 Â½³¬ **********************************
* File Name          :  WDT.h
* Author             :  Â½³¬
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/24/2017
* Description        :  WDT header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WDT_H
#define __WDT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void WDT_Task_Init(void);                                       // ¿´ÃÅ¹·³õÊ¼»¯
extern  void WDT_Feed(void);                                            // Î¹¹·

#endif /* __WDT_H */

/******************* (C) COPYRIGHT 2017 Â½³¬ *****END OF FILE******************/

