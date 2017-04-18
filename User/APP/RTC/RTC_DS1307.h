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


//structures
typedef struct clock {
	uint8_t month;
	uint8_t day;
	uint8_t year;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} time_t;

//definitions
#define DS1307_ADDR (0x68<<1) //device address shifted over one

//functions
uint8_t ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
uint8_t ds1307_setdate_s(time_t time);
uint8_t ds1307_getdayofweek(uint8_t y, uint8_t m, uint8_t d);
bool ds1307_isleapyear(uint8_t year);
void ds1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);
void ds1307_getdate_s(time_t *time);
#endif /* __TVOC_SGPC_H */

/******************* (C) COPYRIGHT 2017 Â½³¬ **** END OF FILE *****************/

