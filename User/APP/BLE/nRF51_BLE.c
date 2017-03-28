/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  nRF51_BLE 任务
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "nRF51_BLE_Init.h"
#include "nRF51_BLE_Adv_Port.h"
#include "nRF51_BLE_Adv.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void nRF51_BLE_Task_Create(void);                                        // BLE任务创建
void nRF51_BLE_Task_Handle(void *p_arg);                                 // BLE任务
void nRF51_BLE_Slave_Evt_Handle(void *p_arg);                            // 从任务  
void nRF51_BLE_Master_Evt_Handle(void *p_arg);                           // 主任务
void nRF51_BLE_Int_Evt_Handle(void *p_arg);                              // 特殊任务
void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID);                              // 特殊任务设置
void nRF51_BLE_Cycle_Evt_Handle(void *p_arg);                            // 周期任务处理

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-11
* Function Name  :  nRF51_BLE_Task_Create
* Description    :  创建BLE任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 初始化BLE
    nRF51_BLE_Init();
    
    // 配置参数 周期模式运行
    BLE_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    BLE_Task.Timeout_handler = nRF51_BLE_Task_Handle;
    BLE_Task.Period          = TASK_BLE_PERIOD;

    err_code |= app_timer_create(&BLE_Task.p_ID,
                                 BLE_Task.Run_Mode,
                                 BLE_Task.Timeout_handler);

    // 开始任务
    err_code |= Task_Timer_Start(&BLE_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Temp&Humi create failed!\r\n");    
    }


    
    
}// End of void nRF51_BLE_Task_Create(void)


/*******************************************************************************
*                           陆超@2017-01-11
* Function Name  :  nRF51_BLE_Task_Handle
* Description    :  BLE任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Task_Handle(void *p_arg)
{

   
}// End of void nRF51_BLE_Task_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-03-02
* Function Name  :  nRF51_BLE_Int_Evt_Handle
* Description    :  特殊任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Int_Evt_Handle(void *p_arg)
{

                                                                 
}// End of void nRF51_BLE_Int_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-03-02
* Function Name  :  nRF51_BLE_Int_Evt_Set
* Description    :  特殊任务设置
* Input          :  u16 usEvent_ID
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID)
{

    
}// End of void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID)

/*******************************************************************************
*                           陆超@2017-03-02
* Function Name  :  nRF51_BLE_Cycle_Evt_Handle
* Description    :  周期性任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Cycle_Evt_Handle(void *p_arg)
{
    
}// End of void nRF51_BLE_Cycle_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-01-13
* Function Name  :  nRF51_BLE_Master_Evt_Handle
* Description    :  主任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Master_Evt_Handle(void *p_arg)
{

   

    
}// End of void nRF51_BLE_Master_Evt_Handle(void *p_arg)



/*******************************************************************************
*                           陆超@2017-01-13
* Function Name  :  nRF51_BLE_Slave_Evt_Handle
* Description    :  从任务处理
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Slave_Evt_Handle(void *p_arg)
{

    
}// End of void nRF51_BLE_Slave_Evt_Handle(void *p_arg)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




