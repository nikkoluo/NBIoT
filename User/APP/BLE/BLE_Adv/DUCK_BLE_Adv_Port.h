/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Adv_Port.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  蓝牙广播配置头文件
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_ADV_PORT_H
#define __DUCK_BLE_ADV_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void BLE_Adv_Start(u32 uiTimeout);                              // 启动广播
extern  void BLE_Adv_Package(u16 usEvent, MIOT_Typedef *MIOT);          // 广播数据打包

#endif /* __DUCK_BLE_ADV_PORT_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/

