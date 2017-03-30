/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Global.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  全局变量
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Global.h"

/* Private variables ---------------------------------------------------------*/
//----------------------- System ----------------------------------------------/
u8                      Root_Access;                                    // 超级权限
u8                      Sys_Status;                                     // 系统状态
u8                      Sys_Init;                                       // 置一完成初始化 
Task_Typedef            Button_Task;                                    // 按键任务
Task_Typedef            tVOC_Task;                                      // tVOC任务
Task_Typedef            Communal_Timer_Task;                            // 公用定时器任务
Task_Typedef            Battery_Task;                                   // 电池任务
Task_Typedef            Temp_Humi_Task;                                 // 温湿度任务
Task_Typedef            BLE_Task;                                       // BLE任务
Task_Typedef            WDT_Task;                                       // WDT任务
Task_Typedef            Debug_Rx_Task;                                  // 调试口接收任务
Test_Typedef            Test;                                           // 测试
Bond_Typedef            Sys_Bond;                                       // 绑定
UART_Typedef            Debug_UART;                                     // 调试串口
Button_Typedef          Button;                                         // 按键结构体
Sensor_Typedef          Sensor;                                         // Sensor
Time_Base_Typedef       System_Time_Base;                               // 系统时间基准
System_ERR_Typedef      System_Err;                                     // 系统错误结构体
BLE_Service_Typedef     nRF51_BLE_Service;                              // nRF51 BLE私有服务
nrf_drv_wdt_channel_id  WDT_Channel;                                    // 声明看门狗通道变量

//----------------------- BLE -------------------------------------------------/
u16                     BLE_Connect_Handle;                             // 当前连接处理状态
ble_bas_t               Bat_Level_Service;                              // 电量服务
dm_application_instance_t   DM_App_Handle;                              // dm handle
ble_dfu_t               nRF51_DFU_Services;                             // DFU service

//----------------------- flash -----------------------------------------------/
u8                      Flash_Used;                                     // 置一时flash被占用
pstorage_handle_t       MAC_Flash_Handle;                               // mac flash处理
pstorage_handle_t       Token_Flash_Handle;                             // Token lash地址

//----------------------- Button ----------------------------------------------/
app_button_cfg_t        Button_Cfg[MAX_INTERRUPT_PIN_NUM];              // Button配置结构体


//----------------------- Software IIC ----------------------------------------/
SW_I2C_Typedef          Temp_Humi_I2C;                                  // 温湿度的IIC
SW_I2C_Typedef          Communal_IIC;                                   // 通用IIC

/* Private function prototypes -----------------------------------------------*/
u32  Timestamp_Interval_Get(u32 Time1, u32 Time2);                      // 计算时间差值
u32  Timestamp_Get(void);                                               // 获取时间戳
u8   Timestamp_Timeout(u32 Time, u32 Timeout);                          // 超时计算
u8   System_ms_Base_Timeout(u32 Time, u32 Timeout);                     // ms超时
u32  System_ms_Base_Update(void);                                       // ms时间戳更新

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  Timestamp_Interval_Get
* Description    :  计算时间戳间隔
* Input          :  u32 Time1   后者时间
*                   u32 Time2   前者时间
* Output         :  None
* Return         :  后者和前者差值
*******************************************************************************/
u32 Timestamp_Interval_Get(u32 Time1, u32 Time2)
{
    u32 Time_Interval;
    

    Time_Interval = (Time1 - Time2) & 0x00FFFFFF; 

    return Time_Interval;
    
}// End of u32 Timestamp_Interval_Get(u32 Time1, u32 Time2)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  Timestamp_Timeout
* Description    :  计算时间戳间隔
* Input          :  u32 Time    待比较时间
*                   u32 Timeout 超时时间 ms
* Output         :  None
* Return         :  超时返回1 否则返回0
*******************************************************************************/
u8 Timestamp_Timeout(u32 Time, u32 Timeout)
{
    u32 Time_Interval;
    u32 Current_Time = Timestamp_Get();

    Time_Interval = (Current_Time - Time) & 0x00FFFFFF; 

    Time_Interval /= TICK_TO_MS;
    if (Time_Interval > Timeout)
    {
        return 1;    
    }
    else
    {
        return 0;
    }

    
}// End of u8 Timestamp_Timeout(u32 Time, u32 Timeout)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  System_ms_Base_Timeout
* Description    :  计算时间戳间隔 ms
* Input          :  u32 Time    待比较时间
*                   u32 Timeout 超时时间 ms
* Output         :  None
* Return         :  超时返回1 否则返回0
*******************************************************************************/
u8 System_ms_Base_Timeout(u32 Time, u32 Timeout)
{
    System_ms_Base_Update();
    if ((System_Time_Base.ms - Time)  >= Timeout)
    {
        return 1;    
    }
    else
    {
        return 0;
    }

    
}// End of u8 System_ms_Base_Timeout(u32 Time, u32 Timeout)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  System_ms_Base_Update
* Description    :  毫秒时间戳更新
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 System_ms_Base_Update(void)
{
    u32 Current_Time            = NRF_RTC1->COUNTER;
    u32 Time_Interval           = (Current_Time - System_Time_Base.Last_Tick) & 0x00FFFFFF;
    
    Time_Interval              /= TICK_TO_MS;
    System_Time_Base.ms        += Time_Interval;
    System_Time_Base.Last_Tick  = Current_Time;
    
    return System_Time_Base.ms;
    
}// End of u32 System_ms_Base_Update(void)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  Timestamp_Get
* Description    :  获取时间戳
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Timestamp_Get(void)
{
    return NRF_RTC1->COUNTER;
    
}// End of u32 Timestamp_Get(void)

/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/
