/******************** (C) COPYRIGHT 2017 Â½³¬ **********************************
* File Name          :  tVOC_SGPC.h
* Author             :  Â½³¬
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/30/2017
* Description        :  tVOC_SGPC header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TVOC_SGPC_H
#define __TVOC_SGPC_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void sensirion_i2c_init(void);

int sensirion_i2c_read(u8 address, u8* data, u16 count);

int sensirion_i2c_write(u8 address, const u8* data, u16 count);
void sensirion_sleep_usec(u32 useconds);
#endif /* __TVOC_SGPC_H */

/******************* (C) COPYRIGHT 2017 Â½³¬ **** END OF FILE *****************/

