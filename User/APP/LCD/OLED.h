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
#define 	OLED_SCL_CLR()				GPIO_Set_Pin_Low(OLED_SCL_PIN)	// SCL管脚
#define 	OLED_SCL_SET()				GPIO_Set_Pin_High(OLED_SCL_PIN)

#define 	OLED_SDA_CLR()				GPIO_Set_Pin_Low(OLED_SDA_PIN)
#define 	OLED_SDA_SET()				GPIO_Set_Pin_High(OLED_SDA_PIN)

#define 	OLED_RST_CLR()				GPIO_Set_Pin_Low(OLED_RST_PIN)
#define 	OLED_RST_SET()				GPIO_Set_Pin_High(OLED_RST_PIN)

#define 	OLED_DC_CLR()				GPIO_Set_Pin_Low(OLED_DC_PIN)
#define 	OLED_DC_SET()				GPIO_Set_Pin_High(OLED_DC_PIN)

#define 	OLED_CMD_Y_ADDR				0xB0							// Y轴地址


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


#define 	X_WIDTH 					128								// 横轴像素
#define 	Y_WIDTH 					64								// 纵轴像素
#define 	Y_PAGE 						(Y_WIDTH / 8)					// 纵轴像素


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
extern  void OLED_Port_Init(void);										// 端口初始化
extern  void OLED_Set_Pos(u8 x, u8 y);									// 设置坐标
extern  void OLED_Init(void);											// OLED初始化
extern  void OLED_Fill(u8 Data);										// 数据填充
extern  void OLED_DrawPixel(u8 x, u8 y, u8 Value);						// 画点
extern  void OLED_Draw_YPage(u8 x, u8 y, u8 *pData, u8 ucByte);			// 写Y轴

#endif /* _OLED_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/


