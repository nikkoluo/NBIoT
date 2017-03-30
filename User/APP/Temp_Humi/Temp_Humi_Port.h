/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Temp_Humi_Port.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Temp_Humi_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMP_HUMI_PORT_H
#define __TEMP_HUMI_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     SHT3x_ADDR                  0x44                            // SHT3x地址
#define     SHT3x_WRITE_ADDR            (SHT3x_ADDR << 1)               // SHT3x写地址
#define     SHT3x_READ_ADDR             (SHT3x_WRITE_ADDR | 0x01)       // SHT3x读地址
#define     TEMP_HUMI_MAX_TIMEOUT_LOOPS (5 * 1000)                      // 超时周期us


/* Private typedef -----------------------------------------------------------*/
// Sensor Commands


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Temp_Humi_Variable_Init(void);                             // 温湿度变量初始化
extern  u8 Temp_Humi_Port_Init(void);                                   // 管脚初始化
extern  u8 Temp_Humi_Read_Register(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);// 读寄存器
extern  u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);// 写寄存器

#endif /* __TEMP_HUMI_PORT_H */

/******************* (C) COPYRIGHT 2016 陆超 **** END OF FILE *****************/
