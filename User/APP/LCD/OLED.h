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


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

extern void OLCD_Init(void);
extern void OLCD_CLS(void);
extern void OLCD_CLS_y(char y);
extern void OLCD_CLS_line_area(u8 start_x,u8 start_y,u8 width);
extern void OLCD_P6x8Str(u8 x,u8 y,u8 *ch,const u8 *F6x8);
extern void OLCD_P8x16Str(u8 x,u8 y,u8 *ch,const u8 *F8x16);
extern void OLCD_P14x16Str(u8 x,u8 y,u8 ch[],const u8 *F14x16_Idx,const u8 *F14x16);
extern void OLCD_P16x16Str(u8 x,u8 y,u8 *ch,const u8 *F16x16_Idx,const u8 *F16x16);
extern void OLCD_PutPixel(u8 x,u8 y);
extern void OLCD_Print(u8 x, u8 y, u8 *ch,u8 char_size, u8 ascii_size);
extern void OLCD_Rectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 gif);
extern void Draw_BMP(u8 x,u8 y,const u8 *bmp); 
extern void OLCD_Fill(u8 dat);
#endif /* _OLED_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/


