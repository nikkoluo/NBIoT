/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_Storage_MAC.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  mac地址处理头文件
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_STORAGE_MAC_H
#define __DUCK_STORAGE_MAC_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "ble_advdata.h"
#include "ble_advertising.h"

/* Private define ------------------------------------------------------------*/
#define     MAC_PSM_SIZE                64                              // mac储存大小
#define     MAC_PSM_BLOCK               1                               // 块数

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Get_MAC(void);                                             // 获取MAC地址
extern  void MAC_Flash_Init(void);                                      // mac flash初始化
extern  u8 MAC_Delete(void);                                            // 删除mac地址
extern  u8 MAC_Save(u8 *ucMAC);                                         // 保存mac地址

#endif /* __DUCK_STORAGE_MAC_H */

/******************* (C) COPYRIGHT 2017 陆超 ***** END OF FILE ****************/




