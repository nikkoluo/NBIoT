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
#include "nRF51_BLE_Private_Service.h"
#include "OLED.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
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

	// 判断当前是否Time页面
	if (LCD.Page_Now != LCD_PAGE_TIME)
	{
		LCD_Page_Time_Prepare();
	}

	
}// End of void LCD_Page_Time(void)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




