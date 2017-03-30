/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE_Test_Ack.h
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/10/2017
* Description        :  测试应答 header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_TEST_ACK_H
#define __NRF51_BLE_TEST_ACK_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     PS_CMD_LCD_TEST             0x0001                          // 段码屏测试命令
#define     PS_CMD_HALL_TEST            0x0002                          // 霍尔测试命令
#define     PS_CMD_GET_TOKEN            0x0003                          // 获取token测试命令
#define     PS_CMD_SET_TOKEN            0x0004                          // 设置token测试命令
#define     PS_CMD_REBOOT               0x0005                          // 重启

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
 

/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen);          // nRF51测试数据处理
extern  u8 nRF51_BLE_Test_LCD_Prepare(void);                            // 准备测试显示数据

#endif /* __NRF51_BLE_TEST_ACK_H */

/******************* (C) COPYRIGHT 2017 陆超 **** END OF FILE *****************/

