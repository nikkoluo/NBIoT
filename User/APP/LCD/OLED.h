/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  OLED.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/10/2017
* Description        :  _OLED_H header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _OLED_H
#define _OLED_H


/* Includes ------------------------------------------------------------------*/

#include "Global.h"
#include "GPIO_Port.h"



/* Private define ------------------------------------------------------------*/				   
#define 	OLCD_SCL_CLR()				GPIO_Set_Pin_Low(OLED_SCL_PIN)	// SCL管脚
#define 	OLCD_SCL_SET()				GPIO_Set_Pin_High(OLED_SCL_PIN)

#define 	OLCD_SDA_CLR()				GPIO_Set_Pin_Low(OLED_SDA_PIN)
#define 	OLCD_SDA_SET()				GPIO_Set_Pin_High(OLED_SDA_PIN)

#define 	OLCD_RST_CLR()				GPIO_Set_Pin_Low(OLED_RST_PIN)
#define 	OLCD_RST_SET()				GPIO_Set_Pin_High(OLED_RST_PIN)

#define 	OLCD_DC_CLR()				GPIO_Set_Pin_Low(OLED_DC_PIN)
#define 	OLCD_DC_SET()				GPIO_Set_Pin_High(OLED_DC_PIN)

//汉字大小，英文数字大小
#define 	TYPE8X16					1
#define 	TYPE16X16					2
#define 	TYPE6X8						3



#define 	XLevelL						0x00
#define 	XLevelH						0x10
#define 	XLevel						((XLevelH & 0x0F) * 16 + XLevelL)
#define 	Max_Column					128
#define 	Max_Row		  				64
#define		Brightness					0xCF 


#define 	X_WIDTH 					128
#define 	Y_WIDTH 					64


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void OLED_Port_Init(void);										// 端口初始化
extern  void OLED_Set_Pos(u8 x, u8 y);									// 设置坐标

#endif /* _OLED_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/


