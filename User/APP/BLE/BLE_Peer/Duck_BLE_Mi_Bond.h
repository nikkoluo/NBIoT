/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Mi_Bond.h
* Author             :  陆超 
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/15/2017
* Description        :  Duck_BLE_Mi_Bond header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_MI_BOND_H
#define __DUCK_BLE_MI_BOND_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     MISERVICE_PSM_SIZE          64                              // mi服务储存大小
#define     MISERVICE_PSM_BLOCK         1                               // 块数

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Mi_Bond_Start(void);                                       // 启动绑定
extern  void Mi_Bond_Stop(void);                                        // 结束绑定
extern  void Duck_BLE_Mi_Services_Init(void);                           // 小米绑定服务初始化
extern  void Mi_Bond_Timeout_Check(void);                               // 绑定超时出判断


#endif /* __DUCK_BLE_MI_BOND_H */

/******************* (C) COPYRIGHT 2017 陆超 ***** END OF FILE ****************/

