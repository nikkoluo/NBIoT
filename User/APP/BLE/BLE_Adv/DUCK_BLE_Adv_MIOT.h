/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Adv_MIOT.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/10/2017
* Description        :  MIOT头文件
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_ADV_MIOT_H
#define __DUCK_BLE_ADV_MIOT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  u8 BLE_MIOT_Service_Package(u16 usEvent, u8* pService_Data, MIOT_Typedef *MIOT);// MIOT数据打包

#endif /* __DUCK_BLE_ADV_MIOT_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/

