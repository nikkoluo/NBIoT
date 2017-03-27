/******************** (C) COPYRIGHT 2017 Â½³¬ **********************************
* File Name          :  Hall.h
* Author             :  Â½³¬
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/27/2017
* Description        :  Hall header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HALL_H
#define __HALL_H

/* Includes ------------------------------------------------------------------*/
#include "GPIO_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Hall_Open(void);                                           // ¿ªhall
extern  void Hall_Close(void);                                          // ¹Øhall
extern  void Hall_Magnet_Check(void);                                   // »ô¶û´ÅÌúÅÐ¶Ï 
extern  void Hall_Update(void);                                         // »ô¶û×´Ì¬Ë¢ÐÂ
extern  u8 Is_Magnet_Near(void);                                        // ÊÇ·ñÓÐ´ÅÌúÔÚ¸½½ü

#endif /* __HALL_H */

/******************* (C) COPYRIGHT 2017 Â½³¬ **** END OF FILE *****************/

