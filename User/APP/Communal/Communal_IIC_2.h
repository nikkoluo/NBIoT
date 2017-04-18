/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Communal_IIC_2.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/19/2017
* Description        :  Communal_IIC_2 header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMUNAL_IIC_2_H
#define __COMMUNAL_IIC_2_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     COMMUNAL_IIC_2_MAX_LPPOS    (5 * 1000)                      // 超时周期




/* Private typedef -----------------------------------------------------------*/
// Sensor Commands


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  u8 Communal_IIC_2_Init(void);                                   // 管脚初始化


#endif /* __COMMUNAL_IIC_2_H */

/******************* (C) COPYRIGHT 2017 陆超 **** END OF FILE *****************/
