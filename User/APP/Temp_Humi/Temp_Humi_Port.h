/******************** (C) COPYRIGHT 2016 Â½³¬ **********************************
* File Name          :  Temp_Humi_Port.h
* Author             :  Â½³¬
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
#define     SHT3x_ADDR                  0x44                            // SHT3xµØÖ·
#define     SHT3x_WRITE_ADDR            (SHT3x_ADDR << 1)               // SHT3xÐ´µØÖ·
#define     SHT3x_READ_ADDR             (SHT3x_WRITE_ADDR | 0x01)       // SHT3x¶ÁµØÖ·
#define     TEMP_HUMI_MAX_TIMEOUT_LOOPS (5 * 1000)                      // ³¬Ê±ÖÜÆÚus


/* Private typedef -----------------------------------------------------------*/
// Sensor Commands


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Temp_Humi_Variable_Init(void);                             // ÎÂÊª¶È±äÁ¿³õÊ¼»¯
extern  u8 Temp_Humi_Port_Init(void);                                   // ¹Ü½Å³õÊ¼»¯
extern  u8 Temp_Humi_Read_Register(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);// ¶Á¼Ä´æÆ÷
extern  u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);// Ð´¼Ä´æÆ÷

#endif /* __TEMP_HUMI_PORT_H */

/******************* (C) COPYRIGHT 2016 Â½³¬ **** END OF FILE *****************/
