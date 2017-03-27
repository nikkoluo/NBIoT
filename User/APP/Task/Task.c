/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Task.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  定时器
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Task.h"
#include "nrf51.h"

#include "app_scheduler.h"
#include "app_timer_appsh.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
u32 Task_Timer_Start(Task_Typedef *Task, void * p_context);             // 任务启动
u32 Task_Timer_Stop(Task_Typedef *Task);                                // 任务停止

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Task_Timer_Start
* Description    :  任务启动
* Input          :  Task_Typedef *Task  相关任务参数
*                   u32 Period                  周期
*                   void * p_context            启动时传递个任务的参数
* Output         :  None
* Return         :  启动成功或者失败的原因
*******************************************************************************/
u32 Task_Timer_Start(Task_Typedef *Task, void * p_context)
{
    u32 Err_Code;

    
    Err_Code = app_timer_start(Task->p_ID, APP_TIMER_TICKS(Task->Period, APP_TIMER_DIV), p_context);


    return Err_Code;
    
}// End of void Task_Timer_Start(Task_Typedef *Task, void * p_context)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Task_Timer_Stop
* Description    :  任务停止
* Input          :  Task_Typedef *Task  相关任务参数
* Output         :  None
* Return         :  停止成功或者失败的原因
*******************************************************************************/
u32 Task_Timer_Stop(Task_Typedef *Task)
{
    u32 Err_Code;


    // 停止定时器 清空变量
    Err_Code = app_timer_stop(Task->p_ID);


    return Err_Code;
    
}// End of void Task_Timer_Stop(Task_Typedef *Task)


/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/




