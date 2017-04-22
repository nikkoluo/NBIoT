/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD_Page_Time.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/20/2017
* Description        :  LCD_Page_Time应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Page_Time.h"
#include "nrf_gpio.h"
#include "OLED.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
static const u8 Week[][7] = {"Mon", "Tues", "Wed", "Thur", "Fri", "Sat", "Sun" };    
/* Private function prototypes -----------------------------------------------*/
void LCD_Page_Time_Prepare(void);									    // 准备Time页面
void LCD_Page_Time(void);											    // 显示Time页面


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  LCD_Page_Time_Prepare
* Description    :  准备Time页面
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Time_Prepare(void)
{

	OLED_CLS();
	
//    OLED_String_8x16(0,  LCD_BASELINE_Y_ADDR, "Base: ", 6);
    OLED_String_8x16(0,  LCD_UNIX_Y_ADDR,     "Unix: ", 6);
	LCD.Page_Now = LCD_PAGE_TIME;
	
}// End of void LCD_Page_Time_Prepare(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  LCD_Page_Time
* Description    :  显示Time页面
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Time(void)
{
	u8 Temp[16];
	u8 ucLen;


	// 判断当前是否Time页面
	if (LCD.Page_Now != LCD_PAGE_TIME)
	{
		LCD_Page_Time_Prepare();
	}

	// 显示时间
	if (System_Err.RTC == 0)
	{
		// 年月日星期
		ucLen = sprintf((char *)Temp, "20%02d-%02d-%02d %s", 
										System.Time.Year, System.Time.Month,  System.Time.Day, (u8*)&Week[System.Time.Week - 1]);

		OLED_String_8x16(OLED_Pos_Center(ucLen << 3),  0, Temp, ucLen);	

		ucLen = sprintf((char *)Temp, "%02d:%02d:%02d",System.Time.Hour, System.Time.Minute, System.Time.Second );

		OLED_String_8x16(OLED_Pos_Center(ucLen << 3),  16, Temp, ucLen);	

		// UNIX
		ucLen= sprintf((char *)Temp, "0x%08X", System.Unix_Sec);
		OLED_String_8x16(48,  LCD_UNIX_Y_ADDR, Temp, ucLen);

		if (Log_Sign < (1000 / TASK_COMMUNAL_TIMER_PERIOD))
		{
			app_trace_log("-------------------Unix = 0x%08X\r\n", System.Unix_Sec);
		}
		
	}


	
	
}// End of void LCD_Page_Time(void)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




