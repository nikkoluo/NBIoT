/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  tVOC.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/29/2017
* Description        :  tVOC应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "tVOC.h"
#include "nrf_gpio.h"
#include "sgpc1x.h"


#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void tVOC_Task_Handle(void *p_arg);                                     // tVOC任务
void tVOC_Task_Create(void);                                            // 创建tVOC任务
void tVOC_Get(void);                                                    // 获取tVOC
void tVOC_Port_Init(void);                                              // tVOC管脚初始化
void tVOC_Variable_Init(void);                                          // 变量初始化
u32 tVOC_Chip_Init(void);                                               // 芯片初始化

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-03-29
* Function Name  :  tVOC_Task_Create
* Description    :  创建tVOC任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 初始化变量和IO
    tVOC_Variable_Init();
    tVOC_Port_Init();
    
    // 配置参数 周期模式运行
    tVOC_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    tVOC_Task.Timeout_handler = tVOC_Task_Handle;
    tVOC_Task.Period          = TASK_TVOC_PERIOD;

    err_code |= app_timer_create(&tVOC_Task.p_ID,
                                 tVOC_Task.Run_Mode,
                                 tVOC_Task.Timeout_handler);
    // 芯片初始化
    err_code |= tVOC_Chip_Init();

    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("tVOC芯片初始化失败!\r\n");    
    }
    else
    {
        err_code |= Task_Timer_Start(&tVOC_Task, NULL);
        if (err_code != NRF_SUCCESS)
        {
            app_trace_log("Task tVOC create failed!\r\n");    
        }
    }


}// End of void tVOC_Task_Create(void)

/*******************************************************************************
*                           陆超@2017-01-03
* Function Name  :  tVOC_Chip_Init
* Description    :  芯片初始化
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS 成功 1失败
*******************************************************************************/
u32 tVOC_Chip_Init(void)
{
    u32 Err_Code = NRF_SUCCESS;


    // 默认传感器error
    System_Err.tVOC = 1;

	if (sgp_probe() != STATUS_OK) 
	{
		app_trace_log("tVOC芯片初始化失败!\r\n"); 
		Err_Code = 0xFFFFFFFF;
	}
	else
	{
		System_Err.tVOC = 0;
	}

    return Err_Code;
        
}// End of u32 tVOC_Chip_Init(void)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  tVOC_Get
* Description    :  获取tVOC
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Get(void)
{

   
}// End of void tVOC_Get(void)

/*******************************************************************************
*                           陆超@2017-03-29
* Function Name  :  tVOC_Task_Handle
* Description    :  tVOC任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Task_Handle(void *p_arg)
{
    u8 err;
    u16 tvoc_ppb, co2_eq_ppm;

	err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
	if (err == STATUS_OK) 
	{
		 app_trace_log("tVOC  Concentration: %dppb\n", tvoc_ppb);
		 app_trace_log("CO2eq Concentration: %dppm\n", co2_eq_ppm);

	} 
	else 
	{
		 app_trace_log("error reading IAQ values\n"); 
	}


}// End of void tVOC_Task_Handle(void *p_arg)



/*******************************************************************************
*                           陆超@2016-03-29
* Function Name  :  tVOC_Port_Init
* Description    :  tVOC端口初始化
* Input          :  None
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
void tVOC_Port_Init(void)
{

       
}// End of void tVOC_Port_Init(void)

/*******************************************************************************
*                           陆超@2017-03-29
* Function Name  :  tVOC_Variable_Init
* Description    :  tVOC变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Variable_Init(void)
{

    
}// End of void tVOC_Variable_Init(void)

/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




