/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Button_Double.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/19/2016
* Description        :  双击应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button_Double.h"
#include "nrf_gpio.h"
#include "LCD.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Double_Button_Handler(void);                                       // 双击处理



/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-19
* Function Name  :  Double_Button_Handler
* Description    :  处理双击事件
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Double_Button_Handler(void)
{
    app_trace_log("双击任务!\r\n");

    // 动态切换
//    LCD_Temp_Humi_Change_Dynamic();
   
}// End of void Double_Button_Handler(void)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




