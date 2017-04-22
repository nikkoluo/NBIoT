/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD_Page_Baseline.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/20/2017
* Description        :  LCD_Page_Baseline应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Page_Baseline.h"
#include "nrf_gpio.h"
#include "OLED.h"
#include "sensirion_common.h"
#include "sgpc1x.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void LCD_Page_Baseline_Prepare(void);									    // 准备Baseline页面
void LCD_Page_Baseline(void);											    // 显示Baseline页面


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  LCD_Page_Baseline_Prepare
* Description    :  准备Baseline页面
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Baseline_Prepare(void)
{
    u8 ucLen;
	OLED_CLS();
    ucLen = strlen("Baseline");
    OLED_String_8x16(OLED_Pos_Center(ucLen << 3),  0,     "Baseline", ucLen);
    OLED_String_8x16(0,  LCD_BASE_NOW_Y_ADDR,  "Now : ", strlen("Now : "));
    OLED_String_8x16(0,  LCD_BASE_SAVE_Y_ADDR, "Save: ", strlen("Save: "));
	LCD.Page_Now = LCD_PAGE_BASELINE;
    tVOC.Baseline_Refresh = 1;
	
}// End of void LCD_Page_Baseline_Prepare(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  LCD_Page_Baseline
* Description    :  显示Baseline页面
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Baseline(void)
{
	u8 Temp[16];
	u8 ucLen;
	u32 uiSub_Value;
	u8 ucDay = 0, ucHour = 0, ucMin = 0;


	// 判断当前是否Baseline页面
	if (LCD.Page_Now != LCD_PAGE_BASELINE)
	{
		LCD_Page_Baseline_Prepare();
	}

	// baseline
	ucLen= sprintf((char *)Temp, "0x%08X", tVOC.Baseline_Now);
	OLED_String_8x16(6 * 8,  LCD_BASE_NOW_Y_ADDR, Temp, ucLen);	

	if (Log_Sign < (1000 / TASK_COMMUNAL_TIMER_PERIOD))
	{
		app_trace_log("-------------------baseline = 0x%08X\r\n", tVOC.Baseline_Now);
//		if (tVOC.Baseline_Now)
//		{
//			tVOC_Save_Baseline(System.Unix_Sec, tVOC.Baseline_Now);
//		}
	}

	// 保存过baseline
	if (tVOC.Baseline_LastSave_Timestamp != 0)
	{
		// 是否要刷新数据
		if (tVOC.Baseline_Refresh)
		{
			tVOC.Baseline_Refresh = 0;

			// baseline
			ucLen= sprintf((char *)Temp, "0x%08X", tVOC.Baseline_Saved);
			OLED_String_8x16(6 * 8,  LCD_BASE_SAVE_Y_ADDR, Temp, ucLen);vs16

			// baseline 时间
			uiSub_Value = System.Unix_Sec - tVOC.Baseline_LastSave_Timestamp;
			ucDay       = uiSub_Value / (24 * 60 * 60);
			if (ucDay)
			{
				uiSub_Value -= 	ucDay * 24 * 60 * 60;
			}

			ucHour = uiSub_Value / (60 * 60);
			if (ucHour)
			{
				uiSub_Value -= 	ucHour * 60 * 60;	
			}
			ucMin  = uiSub_Value / 60;
			ucLen  = sprintf((char *)Temp, "%01dd %02dh %02dm ago", ucDay, ucHour, ucMin);
			OLED_String_8x16(OLED_Pos_Center(ucLen << 3),  LCD_BASE_SAVETIME_Y_ADDR, Temp, ucLen);
		}
	}
	else
	{
		OLED_String_8x16(6 * 8,  LCD_BASE_SAVE_Y_ADDR,     "unsaved ", 8);	
		OLED_String_8x16(0,  LCD_BASE_SAVETIME_Y_ADDR, "                 ", 16);	
	}

	
}// End of void LCD_Page_Baseline(void)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




