/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Button_Long.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  长按应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button_Long.h"
#include "nrf_gpio.h"
#include "LCD.h"
#include "Duck_BLE_Mi_Bond.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Long_Button_Handler(void);                                         // 长按处理


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Long_Button_Handler
* Description    :  处理单击事件
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Long_Button_Handler(void)
{
    
    app_trace_log("长按任务\r\n");

//    // 亮灭切换
//    LCD_Temp_Humi_Change_On_Off();

    // 开始绑定的
    Mi_Bond_Start();

}// End of void Long_Button_Handler(void)


/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/




