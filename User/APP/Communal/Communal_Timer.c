/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Communal_Timer.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/12/2017
* Description        :  公用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Communal_Timer.h"


/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void Communal_Timer_Task_Handle(void *p_arg);                           // Communal_Timer任务
void Communal_Timer_Task_Create(void);                                  // 创建Communal_Timer任务

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-02-22
* Function Name  :  Communal_Timer_Task_Create
* Description    :  创建Communal_Timer任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_Timer_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 配置参数 周期模式运行
    Communal_Timer_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    Communal_Timer_Task.Timeout_handler = Communal_Timer_Task_Handle;
    Communal_Timer_Task.Period          = TASK_COMMUNAL_TIMER_PERIOD;

    err_code |= app_timer_create(&Communal_Timer_Task.p_ID,
                                 Communal_Timer_Task.Run_Mode,
                                 Communal_Timer_Task.Timeout_handler);
    err_code |= Task_Timer_Start(&Communal_Timer_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Communal_Timer create failed!\r\n");    
    }
    else
    {
        app_trace_log("Task Communal_Timer create Success!\r\n"); 
    }

}// End of void Communal_Timer_Task_Create(void)



/*******************************************************************************
*                           陆超@2017-02-22
* Function Name  :  Communal_Timer_Task_Handle
* Description    :  Communal_Timer任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_Timer_Task_Handle(void *p_arg)
{

    
}// End of void Communal_Timer_Task_Handle(void *p_arg)


/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




