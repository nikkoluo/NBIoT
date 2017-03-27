/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  Duck_BLE 任务
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "Duck_BLE_Init.h"
#include "Duck_BLE_Adv_Port.h"
#include "Duck_BLE_Adv.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_Task_Create(void);                                        // BLE任务创建
void Duck_BLE_Task_Handle(void *p_arg);                                 // BLE任务
void Duck_BLE_Slave_Evt_Handle(void *p_arg);                            // 从任务  
void Duck_BLE_Master_Evt_Handle(void *p_arg);                           // 主任务
void Duck_BLE_Int_Evt_Handle(void *p_arg);                              // 特殊任务
void Duck_BLE_Int_Evt_Set(u16 usEvent_ID);                              // 特殊任务设置
void Duck_BLE_Cycle_Evt_Handle(void *p_arg);                            // 周期任务处理

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-11
* Function Name  :  Duck_BLE_Task_Create
* Description    :  创建BLE任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 初始化BLE
    Duck_BLE_Init();
    
    // 配置参数 周期模式运行
    BLE_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    BLE_Task.Timeout_handler = Duck_BLE_Task_Handle;
    BLE_Task.Period          = TASK_BLE_PERIOD;

    err_code &= app_timer_create(&BLE_Task.p_ID,
                                 BLE_Task.Run_Mode,
                                 BLE_Task.Timeout_handler);

    // 开始任务
    err_code &= Task_Timer_Start(&BLE_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Temp&Humi create failed!\r\n");    
    }


    
    
}// End of void Duck_BLE_Task_Create(void)


/*******************************************************************************
*                           陆超@2017-01-11
* Function Name  :  Duck_BLE_Task_Handle
* Description    :  BLE任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Task_Handle(void *p_arg)
{

    // 是否在广播态
    if (Sys_Status != SYS_STATUS_ADV)
    {
        return;
    }

    // 是否发送绑定广播
    if (Sys_Bond.Adv_En)
    {
        Duck_BLE_Bond_Adv_Handle(p_arg);
    }
    else
    {
        // 是否特殊事件
        if (MIOT_Adv.Int_Event)
        {
            Duck_BLE_Int_Evt_Handle(p_arg);
        }
        else
        {
            // 周期广播
            Duck_BLE_Cycle_Evt_Handle(p_arg);    
        }
        
    }
   
}// End of void Duck_BLE_Task_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-03-02
* Function Name  :  Duck_BLE_Int_Evt_Handle
* Description    :  特殊任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Int_Evt_Handle(void *p_arg)
{
    MIOT_Adv.Int_Event = 0;

    BLE_Adv_Package(MIOT_Adv.Int_Event_ID, &MIOT_Adv);

    app_trace_log("特殊事件广播!\r\n"); 
                                                                 
}// End of void Duck_BLE_Int_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-03-02
* Function Name  :  Duck_BLE_Int_Evt_Set
* Description    :  特殊任务设置
* Input          :  u16 usEvent_ID
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Int_Evt_Set(u16 usEvent_ID)
{
    MIOT_Adv.Int_Event    = 1;
    MIOT_Adv.Int_Event_ID = usEvent_ID;
    
}// End of void Duck_BLE_Int_Evt_Set(u16 usEvent_ID)

/*******************************************************************************
*                           陆超@2017-03-02
* Function Name  :  Duck_BLE_Cycle_Evt_Handle
* Description    :  周期性任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Cycle_Evt_Handle(void *p_arg)
{
    if (MIOT_Adv.Timestamp_Hall++ > MIOT_HALL_EVENT_INTERVAL)
    {
        MIOT_Adv.Timestamp_Hall = 0;
        
        // 霍尔
        BLE_Adv_Package(MIOT_EVENT_ID_HALL, &MIOT_Adv);
        app_trace_log("广播霍尔事件!\r\n");
    }
    else if (MIOT_Adv.Timestamp_Bat++ > MIOT_BAT_EVENT_INTERVAL)
    {
        MIOT_Adv.Timestamp_Bat = 0;
        
        // 电量
        BLE_Adv_Package(MIOT_EVENT_ID_BAT, &MIOT_Adv);
        app_trace_log("广播电量事件!\r\n");
    }
    else
    {
        // 是否已经在广播温湿度事件
        if (MIOT_Adv.Current_Event_ID != MIOT_EVENT_ID_TH)
        {
            BLE_Adv_Package(MIOT_EVENT_ID_TH, &MIOT_Adv);
        }
        else
        {
            // 是否刷新
            if (MIOT_Adv.Temp_Humi_Refresh)
            {
                MIOT_Adv.Temp_Humi_Refresh = 0;
                BLE_Adv_Package(MIOT_EVENT_ID_TH, &MIOT_Adv);
            }
            else
            {
                app_trace_log("                                             已经在广播温度事件，不重复发送!\r\n");
            }
        } 
    }
    
}// End of void Duck_BLE_Cycle_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-01-13
* Function Name  :  Duck_BLE_Master_Evt_Handle
* Description    :  主任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Master_Evt_Handle(void *p_arg)
{

   

    
}// End of void Duck_BLE_Master_Evt_Handle(void *p_arg)



/*******************************************************************************
*                           陆超@2017-01-13
* Function Name  :  Duck_BLE_Slave_Evt_Handle
* Description    :  从任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Slave_Evt_Handle(void *p_arg)
{
    // 是否电池/ADC异常
    if (System_Err.Battery == 0)
    {
        // 是否已经在广播该事件
        if (MIOT_Adv.Current_Event_ID != MIOT_EVENT_ID_BAT)
        {
            BLE_Adv_Package(MIOT_EVENT_ID_BAT, &MIOT_Adv);
        }
        else
        {
            app_trace_log("已经在广播电量事件，不重复发送!\r\n");
        }
    }
    else
    {

        app_trace_log("Battery Err, 不广播电量事件!\r\n");
    }
    
    
}// End of void Duck_BLE_Slave_Evt_Handle(void *p_arg)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




