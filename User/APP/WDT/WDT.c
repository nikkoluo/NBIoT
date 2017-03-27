/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  WDT.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/24/2017
* Description        :  定时器
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "WDT.h"
#include "nrf51.h"
#include "nrf_drv_wdt.h"
#include "nrf_drv_wdt.h"
#include "app_util_platform.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void WDT_Task_Init(void);                                               // 看门狗初始化
void WDT_Event_Handler(void);                                           // 看门狗中断处理
void WDT_Timeout_Handler(void *p_arg);                                  // WDT超时任务
void WDT_Feed(void);                                                    // 喂狗

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-24
* Function Name  :  WDT_Event_Handler
* Description    :  看门狗中断处理
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Event_Handler(void)
{

}// End of void WDT_Event_Handler(void)

/*******************************************************************************
*                           陆超@2017-01-24
* Function Name  :  WDT_Timeout_Handler
* Description    :  WDT超时任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Timeout_Handler(void *p_arg)
{

    
#ifdef SYS_WDT

    nrf_drv_wdt_channel_feed(WDT_Channel);
    
#endif


}// End of void WDT_Timeout_Handler(void *p_arg)

/*******************************************************************************
*                           陆超@2017-01-24
* Function Name  :  WDT_Task_Init
* Description    :  看门狗初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Task_Init(void)
{

    u32 Err_Code = NRF_SUCCESS;
    
#ifdef SYS_WDT


    nrf_drv_wdt_config_t WDT_Cfg;

    // 定义睡眠计数 超时时间 中断优先级
    WDT_Cfg.behaviour          = NRF_WDT_BEHAVIOUR_RUN_SLEEP;
    WDT_Cfg.reload_value       = 50000; 
    WDT_Cfg.interrupt_priority = APP_IRQ_PRIORITY_LOW;
    
    Err_Code = nrf_drv_wdt_init(&WDT_Cfg, WDT_Event_Handler);
    APP_ERROR_CHECK(Err_Code);
    Err_Code = nrf_drv_wdt_channel_alloc(&WDT_Channel);
    APP_ERROR_CHECK(Err_Code);
    nrf_drv_wdt_enable();

  
#endif

    // 配置参数 单次运行模式
    WDT_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    WDT_Task.Period          = 10000; 
    WDT_Task.Timeout_handler = WDT_Timeout_Handler;

    Err_Code = app_timer_create(&WDT_Task.p_ID,
                                 WDT_Task.Run_Mode,
                                 WDT_Task.Timeout_handler);
    APP_ERROR_CHECK(Err_Code);

    Task_Timer_Start(&WDT_Task, NULL);

}// End of void WDT_Task_Init(void)

/*******************************************************************************
*                           陆超@2017-01-24
* Function Name  :  WDT_Feed
* Description    :  喂狗
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Feed(void)
{

    
#ifdef SYS_WDT

    nrf_drv_wdt_channel_feed(WDT_Channel);
    
#endif


}// End of void WDT_Feed(void)

/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




