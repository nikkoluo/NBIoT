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
#include "nrf_gpio.h"
#include "nRF51_BLE_Private_Service.h"
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

    // 显示温湿度标号
	OLED_String_8x16(0,0, "Temp: ", sizeof("Temp: ") - 1);
	OLED_String_8x16(0,16, "Humi: ", sizeof("humi: ") - 1);

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
//	u8 i, j;
//	u8 temp[2] = {'1', 0xAA};
//	for (i = 0; i < 128; i+=8)
//	{
//		j += 1;
//		if (j >= 64)
//		{
//			j = 0;
//		}

//		OLED_String_6x8(i, j, &temp[0], 1);
//		OLED_String_8x16(i, j + 16, &temp[0], 1);
//        temp[0]++;

//	}

	u8 ucTemp[5];

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
	
	//OLED_DrawPixel(x,y++,1);
   
}// End of void LCD_Task_Handle(void *p_arg)

/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




