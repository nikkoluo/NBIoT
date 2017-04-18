/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  RTC.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/19/2017
* Description        :  RTC应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "RTC.h"
#include "nrf_gpio.h"
#include "sgpc1x.h"


#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void RTC_Task_Handle(void *p_arg);                                     // RTC任务
void RTC_Task_Create(void);                                            // 创建RTC任务
void RTC_Port_Init(void);                                              // RTC管脚初始化
void RTC_Variable_Init(void);                                          // 变量初始化
u32 RTC_Chip_Init(void);                                               // 芯片初始化

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  RTC_Task_Create
* Description    :  创建RTC任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void RTC_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 初始化变量和IO
    RTC_Variable_Init();
    RTC_Port_Init();
    
    // 配置参数 周期模式运行
    RTC_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    RTC_Task.Timeout_handler = RTC_Task_Handle;
    RTC_Task.Period          = TASK_TVOC_PERIOD;

    err_code |= app_timer_create(&RTC_Task.p_ID,
                                 RTC_Task.Run_Mode,
                                 RTC_Task.Timeout_handler);
    // 芯片初始化
    err_code |= RTC_Chip_Init();

    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("RTC芯片初始化失败!\r\n");    
    }
    else
    {
        err_code |= Task_Timer_Start(&RTC_Task, NULL);
        if (err_code != NRF_SUCCESS)
        {
            app_trace_log("Task RTC create failed!\r\n");    
        }
    }


}// End of void RTC_Task_Create(void)

/*******************************************************************************
*                           陆超@2017-01-03
* Function Name  :  RTC_Chip_Init
* Description    :  芯片初始化
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS 成功 1失败
*******************************************************************************/
u32 RTC_Chip_Init(void)
{
    u32 Err_Code = NRF_SUCCESS;


    // 默认传感器error
    System_Err.RTC = 1;

	if (sgp_probe() != STATUS_OK) 
	{
		app_trace_log("RTC芯片初始化失败!\r\n"); 
		Err_Code = 0xFFFFFFFF;
	}
	else
	{
		System_Err.RTC = 0;
	}

    return Err_Code;
        
}// End of u32 RTC_Chip_Init(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  RTC_Task_Handle
* Description    :  RTC任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void RTC_Task_Handle(void *p_arg)
{
    u8 err;
    u16 tvoc_ppb, co2_eq_ppm;


    if (Sensor.RTC_Baseline_Reset == 0)
    {
    	Sensor.RTC_Baseline_Timestamp++;

		// 15分钟重启
    	if (Sensor.RTC_Baseline_Timestamp >= 15 * 60)
    	{
    		Sensor.RTC_Baseline_Reset = 1;

    		if (sgp_iaq_init() == STATUS_OK)
    		{
    			app_trace_log("RTC  sgp_iaq_init Success \r\n");	
    		}
    		else
    		{
    			app_trace_log("RTC  sgp_iaq_init Failed \r\n");		
    		}
    	}
    }

	err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
	if (err == STATUS_OK) 
	{
		 app_trace_log("RTC  Concentration: %dppb\n", tvoc_ppb);
		 app_trace_log("CO2eq Concentration: %dppm\n", co2_eq_ppm);

		 // 记录RTC eCO2
		 Sensor.RTC = tvoc_ppb;
		 Sensor.eCO2 = co2_eq_ppm;


	} 
	else 
	{
		 app_trace_log("error reading IAQ values\n"); 
	}


}// End of void RTC_Task_Handle(void *p_arg)



/*******************************************************************************
*                           陆超@2016-04-19
* Function Name  :  RTC_Port_Init
* Description    :  RTC端口初始化
* Input          :  None
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
void RTC_Port_Init(void)
{

       
}// End of void RTC_Port_Init(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  RTC_Variable_Init
* Description    :  RTC变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void RTC_Variable_Init(void)
{

    
}// End of void RTC_Variable_Init(void)

/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




