/******************** (C) COPYRIGHT 2015 陆超 **********************************
* File Name          :  Duck_Test.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/08/2017
* Description        :  Duck_Test header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_TEST_H
#define __DUCK_TEST_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     TEST_CMD_START              "Enter Test Mode"               // 进入测试模式
#define     TEST_CMD_MAC                "Set MAC"                       // 设置mac地址
#define     TEST_CMD_TEST               "Start Test"                    // 开始测试
#define     TEST_CMD_TOKEN              "Set Token"                     // 设置token
#define     TEST_CMD_DELETE_MAC         "Delete MAC"                    // 删除mac

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Duck_Test_Handler(u8* ucData, u16 usLen);                  // 测试数据处理

#endif /* __DUCK_TEST_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/

