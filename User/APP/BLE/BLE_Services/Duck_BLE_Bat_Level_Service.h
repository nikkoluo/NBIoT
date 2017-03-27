/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Bat_Level_Service.h
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/12/2017
* Description        :  BLE 电量服务 header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_BAT_LEVEL_SERVICE_H
#define __DUCK_BLE_BAT_LEVEL_SERVICE_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Duck_BLE_Bat_Level_Services_Init(void);                    // Duck BLE 电量服务初始化    
extern  void Battery_BLE_Service_Update(void);                          // 更新BLE电量

#endif /* __DUCK_BLE_BAT_LEVEL_SERVICE_H */

/******************* (C) COPYRIGHT 2017 陆超 **** END OF FILE *****************/

