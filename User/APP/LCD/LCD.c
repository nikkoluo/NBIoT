/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD.h"
#include "LCD_Page_Sensor.h"
#include "LCD_Page_Time.h"
#include "nrf_gpio.h"
#include "OLED.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void LCD_Task_Handle(void *p_arg);                                      // LCD任务
void LCD_Task_Create(void);                                             // 创建LCD任务
u32 LCD_Chip_Init(void);                                                // 芯片初始化


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-04-09
* Function Name  :  LCD_Task_Create
* Description    :  创建LCD任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 初始化变量和IO
    LCD_Variable_Init();
    LCD_Port_Init();
    
    // 配置参数 周期模式运行
    LCD_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    LCD_Task.Timeout_handler = LCD_Task_Handle;
    LCD_Task.Period          = TASK_LCD_PERIOD;

    err_code |= app_timer_create(&LCD_Task.p_ID,
                                 LCD_Task.Run_Mode,
                                 LCD_Task.Timeout_handler);
    // 芯片初始化
    err_code |= LCD_Chip_Init();

    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("LCD芯片初始化失败!\r\n");    
    }
    else
    {
        err_code |= Task_Timer_Start(&LCD_Task, NULL);
        if (err_code != NRF_SUCCESS)
        {
            app_trace_log("Task LCD create failed!\r\n");    
        }
    }

	// 准备首页数据
	LCD_Page_Sensor_Prepare();

}// End of void LCD_Task_Create(void)

/*******************************************************************************
*                           陆超@2017-04-09
* Function Name  :  LCD_Chip_Init
* Description    :  芯片初始化
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS 成功 1失败
*******************************************************************************/
u32 LCD_Chip_Init(void)
{
    u32 Err_Code = NRF_SUCCESS;

	OLED_Init();

    return Err_Code;
        
}// End of u32 LCD_Chip_Init(void)

/*******************************************************************************
*                           陆超@2017-04-09
* Function Name  :  LCD_Task_Handle
* Description    :  LCD任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Task_Handle(void *p_arg)
{

	switch(LCD.Page_Show)
	{
		case LCD_PAGE_SENSOR:
		{
			LCD_Page_Sensor();
			
		}break;

		case LCD_PAGE_TIME:
		{
			LCD_Page_Time();
			
		}break;

		default:
		break;
		
	}

   
}// End of void LCD_Task_Handle(void *p_arg)



/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




