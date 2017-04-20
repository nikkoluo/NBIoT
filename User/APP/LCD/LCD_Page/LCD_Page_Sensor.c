/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD_Page_Sensor.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD_Page_Sensor应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Page_Sensor.h"
#include "nrf_gpio.h"
#include "nRF51_BLE_Private_Service.h"
#include "OLED.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void LCD_Page_Sensor_Prepare(void);									    // 准备sensor页面
void LCD_Page_Sensor(void);											    // 显示sensor页面


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  LCD_Page_Sensor_Prepare
* Description    :  准备sensor页面
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Sensor_Prepare(void)
{
	OLED_CLS();
	
    // 显示温湿度标号
	OLED_String_8x16(0,   0, "Temp: ", sizeof("Temp: ") - 1);
	OLED_String_8x16(0,   16, "Humi: ", sizeof("humi: ") - 1);
	OLED_String_16x16(96, 0, (u8*)Temp_Unit, 1);
	OLED_String_8x16(102, 16, "%", sizeof("%") - 1);

	// tVOC eCO2
	OLED_String_8x16(0,  32, "tVOC:  ...", sizeof("tVOC:  ...") - 1);
	OLED_String_8x16(0,  48, "eCO2:  ...", sizeof("eCO2:  ...") - 1);
	OLED_String_8x16(96, 32, "ppb", sizeof("ppb") - 1);
	OLED_String_8x16(96, 48, "ppm", sizeof("ppm") - 1);

	LCD.Page_Now = PAGE_SENSOR;
	
}// End of void LCD_Page_Sensor_Prepare(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  LCD_Page_Sensor
* Description    :  显示sensor页面
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Sensor(void)
{
	u8 ucTemp[6];
	u8 ucLen;

	// 判断当前是否sensor页面
	if (LCD.Page_Now != PAGE_SENSOR)
	{
		LCD_Page_Sensor_Prepare();
	}
	
	// 温度大于0
	if (Sensor.sTemp >= 0)
	{
		// 十度内
		if (Sensor.sTemp < 100)
		{
			sprintf((char *)ucTemp, "  %01d.%01d", Sensor.sTemp / 10, Sensor.sTemp % 10);
		}
		else
		{
			sprintf((char *)ucTemp, " %02d.%01d", Sensor.sTemp / 10, Sensor.sTemp % 10);
		}
		
	}
	else
	{
		Sensor.sTemp = abs(Sensor.sTemp);
		sprintf((char *)ucTemp, "-%02d.%01d", Sensor.sTemp / 10, Sensor.sTemp % 10);

	}
	OLED_String_8x16(6 * 8, 0, ucTemp, 5);
	
	// 湿度
	sprintf((char *)ucTemp, " %02d.%01d", Sensor.usHumi / 10, Sensor.usHumi % 10);
	OLED_String_8x16(6 * 8, 16, ucTemp, 5);
	
	// tVOC eCO2
	ucLen = sprintf((char *)ucTemp, " %4d", Sensor.tVOC);
	OLED_String_8x16(6 * 8, 32, ucTemp, ucLen);
	ucLen = sprintf((char *)ucTemp, " %4d", Sensor.eCO2);
	OLED_String_8x16(6 * 8, 48, ucTemp, ucLen);
	
}// End of void LCD_Page_Sensor(void)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




