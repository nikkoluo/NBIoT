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

	OLED_CLS();

    OLED_String_8x16(0,  1,     "Unix: ", 6);
	LCD.Page_Now = LCD_PAGE_BASELINE;
	
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
	u32 Unix;


	// 判断当前是否Baseline页面
	if (LCD.Page_Now != LCD_PAGE_BASELINE)
	{
		LCD_Page_Baseline_Prepare();
	}

//	// baseline
//	if (sgp_get_iaq_baseline(&uiBaseline) == STATUS_OK)
//	{
//		ucLen= sprintf((char *)Temp, "0x%08X", uiBaseline);
//		OLED_String_8x16(48,  LCD_BASELINE_Y_ADDR, Temp, ucLen);	

//		if (Log_Sign < (1000 / TASK_COMMUNAL_BASELINER_PERIOD))
//		{
//			app_trace_log("-------------------baseline = 0x%08X\r\n", uiBaseline);
//		}
//	}
//	else
//	{
//		OLED_String_8x16(48,  LCD_BASELINE_Y_ADDR, "ERROR   ", 8);	
//	}
	
	
}// End of void LCD_Page_Baseline(void)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




