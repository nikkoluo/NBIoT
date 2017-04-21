/******************** (C) COPYRIGHT 2015 陆超 **********************************
* File Name          :  EEPROM_Port.h
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROM_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_PORT_H
#define __EEPROM_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "nrf_delay.h"

/* Private define ------------------------------------------------------------*/
#define     EEPROM_WRITE_ADDR           0xA0                            // EEPROM写地址
#define     EEPROM_READ_ADDR            (EEPROM_WRITE_ADDR + 1)         // EEPROM读地址
#define     EEPROM_PAGE_SIZE            32                              // EEPROM页大小
#define     EEPROM_CHIP_SIZE            0x2000                          // EEPROM总大小
#define     EEPROM_WRITE_PAGE_TIME      10                              // EEPROM写页时间 ms

#define     EEPROM_TEST_ADDR            EEPROM_CHIP_SIZE - 32           // EEPROM测试数据地址

#define     EEPROM_ADDR_BASELINE        (1 << 5)          				// EEPROMbaseline地址




/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);    // EEPROM读取数据
extern  u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);   // 写页命令
extern  u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len); // EEPROM写数据
extern  u8 EEPROM_Chip_Init(void);                                      // 芯片初始化

#endif /* __EEPROM_PORT_H */

/******************* (C) COPYRIGHT 2015 陆超 *****END OF FILE******************/
