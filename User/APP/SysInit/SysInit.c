/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  SysInit.c
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  系统初始化
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "SysInit.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "app_scheduler.h"
#include "app_timer_appsh.h"
#include "app_button.h"
#include "nrf_drv_clock.h"
#include "Communal_IIC.h"
#include "tVOC.h"

#include <stdbool.h>
#include <stdint.h>
#include "ble_advdata.h"
#include "nordic_common.h"
#include "softdevice_handler.h"

#include "nRF51_BLE_Init.h"
#include "Button_Port.h"
#include "Button.h"
#include "Temp_Humi.h"
#include "GPIO.h"
#include "nRF51_BLE.h"
#include "WDT.h"
#include "LCD.h"
#include "Communal_Timer.h"
#include "app_trace.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void System_Init(void);                                                 // 系统初始化
void Variable_Init(void);                                               // 变量初始化
void Peripheral_Init(void);                                             // 外设初始化
void GPIO_Low_Power_Init(void);                                         // 配置IO为最低功耗模式
void IO_Interrupt_Init(void);                                           // IO中断事件初始化
void Task_Init(void);                                                 	// 任务初始化

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2015-04-18
* Function Name  :  HFCLK_Crystal_Oscillato_Start
* Description    :  开启外部晶振 16M
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void HFCLK_Crystal_Oscillato_Start(void)
{
    // 开启外部时钟
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART    = 1;

    // 等待晶振启动
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);    

}// End of void HFCLK_Crystal_Oscillato_Start(void)

/*******************************************************************************
*                           陆超@2015-04-18
* Function Name  :  LFCLK_Crystal_Oscillato_Start
* Description    :  开启外部低速晶振 32k
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LFCLK_Crystal_Oscillato_Start(void)
{
    // 选择外部晶振为时钟源
//    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_RC << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;

     // 等待晶振启动
    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);

}// End of void LFCLK_Crystal_Oscillato_Start(void)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  System_Init
* Description    :  系统初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void System_Init(void)
{

    
    // 变量初始化
    Variable_Init();

    // 外设初始化
    Peripheral_Init();

    // 任务初始化
    Task_Init();
    
    app_trace_log("System init!!!\r\n");

    // 完成初始化
    Sys_Init = 1;


}// End of void System_Init(void)



/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  Variable_Init
* Description    :  变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Variable_Init(void)
{
    // 清空错误标志位
    System_Err.ALL     = 0;
    
    // 默认在空闲态
    Sys_Status         = SYS_STATUS_IDLE;

    // 初始化连接状态
    BLE_Connect_Handle = BLE_CONN_HANDLE_INVALID;


    // 默认未被占用
    Flash_Used = 0;

    // 默认未初始化
    Sys_Init = 0;

	// 无baseline复位
    Sensor.tVOC_Baseline_Timestamp = 0;
    Sensor.tVOC_Baseline_Reset     = 0;

}// End of void Variable_Init(void)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  GPIO_Low_Power_Init
* Description    :  配置IO为最低功耗模式
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Low_Power_Init(void)
{
    u8 i;
    for(i = 0; i < 32; i++ ) 
    {
        NRF_GPIO->PIN_CNF[i] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                             | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                             | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                             | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                             | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
    }
    
}// End of void GPIO_Low_Power_Init(void)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  Peripheral_Init
* Description    :  外设初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Peripheral_Init(void)
{


    // 配置IO为最低功耗模式
    GPIO_Low_Power_Init();
    
#ifndef BLE_OPEN


    APP_TIMER_INIT(APP_TIMER_DIV, SYS_MAX_TIMERS, SYS_MAX_OP_QUEUE_SIZE, NULL);

#else

    APP_TIMER_INIT(APP_TIMER_DIV, SYS_MAX_TIMERS, SYS_MAX_OP_QUEUE_SIZE, app_timer_evt_schedule);
    APP_SCHED_INIT(sizeof(app_timer_event_t) , MAX_EVENT_QUEUE_SIZE);
    
#endif

    // trace调试
    app_trace_init();  
      
    // IO中断事件初始化
    IO_Interrupt_Init();

    // 通讯IIC初始化
    Communal_IIC_Init();


    
}// End of void Peripheral_Init(void)

/*******************************************************************************
*                           陆超@2017-01-11
* Function Name  :  Task_Init
* Description    :  任务初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Task_Init(void)
{


    // 创建触摸任务
    Button_Task_Create();

    // 温湿度检测
    Temp_Humi_Task_Create();

    // tVOC
    tVOC_Task_Create();
    
    // GPIO
    GPIO_Task_Create();

	// LCD任务
	LCD_Task_Create();

    // 公用定时器任务
    Communal_Timer_Task_Create();

    // 开看门狗
    WDT_Task_Init();

    // BLE任务
    nRF51_BLE_Task_Create();




}// End of void Task_Init(void)
																				
/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  IO_Interrupt_Init
* Description    :  IO中断事件初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void IO_Interrupt_Init(void)
{
    u8 i = 0;
    
    // GPOUT 配置管脚 处理程序 有效电平和上下拉

    Button_Cfg[i].pin_no         = BOUTTON_PIN;
    Button_Cfg[i].button_handler = Button_Pin_Handler;
    Button_Cfg[i].active_state   = APP_BUTTON_ACTIVE_LOW;
    Button_Cfg[i].pull_cfg       = NRF_GPIO_PIN_PULLUP;
    i++;
    
    app_button_init(Button_Cfg, MAX_INTERRUPT_PIN_NUM, APP_TIMER_TICKS(BUTTEN_EVENT_DELAY_MS, APP_TIMER_DIV)); 
    app_button_enable();
    
}// End of void IO_Interrupt_Init(void)



/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/




