/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_Storage_Token.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  Token地址处理头文件
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_STORAGE_TOKEN_H
#define __DUCK_STORAGE_TOKEN_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "ble_advdata.h"
#include "ble_advertising.h"

/* Private define ------------------------------------------------------------*/
#define     TOKEN_PSM_SIZE              64                              // Token储存大小
#define     TOKEN_PSM_BLOCK             1                               // 块数

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Get_Token(void);                                           // 获取Token地址
extern  u8 Token_Save(u8 *ucToken);                                     // 保存Token地址
extern  void Token_Flash_Init(void);                                    // Token flash初始化

#endif /* __DUCK_STORAGE_TOKEN_H */

/******************* (C) COPYRIGHT 2017 陆超 ***** END OF FILE ****************/




