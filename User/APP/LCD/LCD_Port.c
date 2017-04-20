/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD_Port.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  温湿度驱动程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Port.h"
#include "nrf_gpio.h"
#include "OLED.h"



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

void LCD_Variable_Init(void);                                           // LCD变量初始化
u8   LCD_Port_Init(void);                                               // LCD端口初始化    

/* Private functions ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           陆超@2017-04-09
* Function Name  :  LCD_Port_Init
* Description    :  LCD端口初始化
* Input          :  None
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 LCD_Port_Init(void)
{
    u8 Transfer_Succeeded = 0; 
	OLED_Port_Init();
    return (Transfer_Succeeded);
       
}// End of u8  LCD_Port_Init(void)

/*******************************************************************************
*                           陆超@2017-04-09
* Function Name  :  LCD_Variable_Init
* Description    :  LCD变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Variable_Init(void)
{
	LCD.Page_Now  = PAGE_SENSOR;	
	LCD.Page_Show = PAGE_SENSOR;
    
}// End of void LCD_Variable_Init(void)



/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/

