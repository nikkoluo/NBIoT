/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Struct.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/25/2016
* Description        :  结构体定义
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STRUCT_H
#define __STRUCT_H

#if defined(__CC_ARM)
#pragma anon_unions
#endif

/* Includes ------------------------------------------------------------------*/
#include "Global_Cfg.h"
#include "app_timer.h"
#include "ble_gatts.h"
#include "nrf_adc.h"

/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/

typedef struct
{

    unsigned int        ms;                                             // 时间基准
    unsigned int        Last_Tick;                                      // 上次Tick
    
} Time_Base_Typedef;                                                // 时间基准结构体

typedef struct
{

    unsigned char       Adv_En;                                         // 置一使能绑定广播
    unsigned char       Blink_Interval;                                 // 闪烁间隔
    unsigned short      Count;                                          // 绑定计数
    unsigned short      Time_Left;                                      // 剩余时间 s
    
    
} Bond_Typedef;                                                     // 时间基准结构体

typedef struct
{

    unsigned char       Magnet_Near;                                    // 置一使靠近磁铁
    unsigned char       Magnet_Last;                                    // 上次状态
    unsigned short      Timestamp;                                      // 时间戳
    
    
} Hall_Typedef;                                                     // 时间基准结构体

typedef struct
{
    unsigned char       Status;                                         // 状态
    unsigned char       Long;                                           // 长按
    unsigned int        Push_Timestamp;                                 // 按下时间戳
    unsigned int        Free_Timestamp;                                 // 释放时时间戳

} Button_Typedef;   

typedef struct
{
    float               fTemp;                                          // 温度
    float               fHumi;                                          // 湿度
    short               sTemp;                                          // 温度整型 * 0.1
    unsigned short      usHumi;                                         // 湿度整型 * 0.1
    unsigned short      Bat_Val_mv;                                     // 电池电压 mv
    unsigned char       Bat_Percent;                                    // 电量百分比
    
    
    
} Sensor_Typedef;                                                // 传感器结构体

typedef struct
{
    unsigned char       Running;                                        // 置一时表示正在运行
    app_timer_mode_t    Run_Mode;                                       // 运行模式，单次或者周期
    unsigned int        Period;                                         // 运行周期(ms) 最大512000
    app_timer_id_t      p_ID;
    app_timer_timeout_handler_t Timeout_handler;                        // 超时运行程序

} Task_Typedef;                                                      // 任务结构体

typedef struct
{
    nrf_adc_config_t    Channel_Config;                                 // 通道配置
    unsigned int        Vol_mv;                                         // 电压 mv   

} ADC_Typedef;                                                        // 任务结构体

typedef struct
{
    
    unsigned char       Frame_Counter;                                  // 帧计数
    unsigned char       MAC[MAC_FLASH_SIZE];                            // MAC地址
    unsigned char       Token[TOKEN_FLASH_SIZE];                        // MAC地址
    unsigned char       MACToken[MAC_FLASH_SIZE + TOKEN_FLASH_SIZE];    // MAC地址
    unsigned char       Int_Event;                                      // 特殊EvEnt事件
    unsigned char       Int_Event_ID;                                   // 特殊EvEnt事件ID
    unsigned short      Timestamp_Hall;                                 // 霍尔时间戳
    unsigned short      Timestamp_Bat;                                  // 电量时间戳
    
    unsigned short      Event_ID;                                       // 事件ID
    unsigned short      Current_Event_ID;                               // 当前事件ID
    short               Temp_Val;                                       // 温湿度 0.1摄氏度
    unsigned char       Humi_Val;                                       // 湿度值
    unsigned char       Temp_Humi_Refresh;                              // 置一时刷新数据
    unsigned char       Bat_Percent;                                    // 电量 0~100%
    unsigned char       Need_Update;                                    // 置一时需要更新数据

    union
    {
        unsigned short  Frame_Control;
        struct
        {
            unsigned short  Factory_New             : 1;                // 1 未绑定 还在出厂设置        0 已经跟绑定过用户或不需要绑定
            unsigned short  Connected               : 1;                // 1 已结连接                   0 未连接
            unsigned short  Central                 : 1;                // 1 当前是Central              0 当前是Peripheral 如果Cennected 为1则此bit无效
            unsigned short  Encrypted               : 1;                // 1 已经加密                   0 当前未加密
            unsigned short  MAC_Include             : 1;                // 1 Frame_Control后包含mac地址 0 不包含MAC地址
            unsigned short  Capability_Include      : 1;                // 1 包含Capability数据         0 不包含Capability数据
            unsigned short  Event_Include           : 1;                // 1 包含Event数据              0 不包含Event数据
            unsigned short  Private_Include         : 1;                // 1 包含厂商私有数据           0 不包含厂商私有数据
            unsigned short  Subheading_Include      : 1;                // 1 包含副标题                 0 不包含副标题
            unsigned short  Band_Confirm            : 1;                // 1 绑定确认包                 0 非绑定确认包  
            unsigned short  Reserved                : 2;                // 预留
            unsigned short  Version                 : 4;                // 协议版本号
     
        }Frame_Control_Bit;
    };
    
    union
    {
        unsigned char   Capability;
        struct
        {
            unsigned char   Connectable             : 1;                // 1 设备有连接能力             0 设备没有连接能力 
            unsigned char   Be_Central              : 1;                // 1 设备有做网关能力           0 设备没有做网关能力
            unsigned char   Encrypt_Ability         : 1;                // 1 设备有加密能力             0 设备没有加密能力
            unsigned char   Bond_Ability            : 2;                // 0x00 无需绑定 0x01 使用MIOT前绑定 0x10 使用MIOT后绑定 0x11 预留
            unsigned char   Reserved                : 3;                // 预留

            
        }Capability_Bit;
    };

    union
    {
        unsigned char   Adv_En;                                         // 0 不允许广播
        struct
        {
            unsigned char   Temp_Humi               : 1;                // 允许温度广播
            unsigned char   Bat_Percent             : 1;                // 允许电量广播
            unsigned char   Reserved                : 6;                // 预留

            
        }Adv_En_Bit;
    };

}MIOT_Typedef;    

typedef union
{
    unsigned long       ALL;                                            // 全局状态
    struct
    {
        unsigned long   Temp_Humi               : 1;                    // 温湿度
        unsigned long   tVOC                    : 1;                    // tVOC
        unsigned long   Reserved                : 30;
    };
    
}System_ERR_Typedef;


typedef void (*DUCK_BLE_Data_Handler_t) (unsigned char * pData, unsigned short usLength);

typedef struct 
{
    unsigned char       Temp_Humi_Listening_En;                         // 置一时使能通知
    unsigned char       Message_Listening_En;                           // 置一时使能通知
    unsigned char       UUID_Type;                                      // UUID类型 16Bit或者128Bit
    unsigned short      Service_Handle;                                 // SoftDevice提供的服务处理
    unsigned short      Conn_Handle;                                    // SoftDevice提供的当前连接处理
    
    ble_gatts_char_handles_t Temp_Humi_Handle;                          // SoftDevice提供温湿度度处理
    ble_gatts_char_handles_t Message_Handle;                            // SoftDevice提供温湿度度处理
    
}BLE_Service_Typedef;                                               // BLE Service 结构体

typedef struct 
{
    unsigned char       Buffer[LCD_BUFFER_SIZE];                        // LCD缓存 
    unsigned char       Main_Temp;                                      // 置一时主显示温度
    unsigned char       BT_LOGO_Show;                                   // 置一时显示蓝牙logo
    unsigned char       Bat_Empty_Show;                                 // 置一时显示电池空框logo
    unsigned char       Is_LCD_On;                                      // 置一时屏幕开
    short               Current_Show_Temp;                              // 当前显示温度
    short               Current_Show_Humi;                              // 当前显示湿度
    
    union
    {
        unsigned char   Need_Update;                                    // 是否需要刷新
        struct
        {
            unsigned char   Temp_Humi               : 1;                // 温度需要刷新
            unsigned char   Bat_Percent             : 1;                // 电量需要刷新
            unsigned char   BT_LOGO                 : 1;                // 蓝牙LOGO需要刷新
            unsigned char   Reserved                : 5;                // 预留

            
        }Need_Update_Bit;
    };
    
}LCD_Typedef;                                                        // LCD 结构体

typedef struct
{
    unsigned char       Rx_Data[128];                                   // 接收缓存
    unsigned char       Rx_State;                                       // 状态
    unsigned char       Rx_Timeout;                                     // 接收超时
    unsigned short      Rx_Len;                                         // 接收长度
    unsigned short      Tx_Len;                                         // 接收长度

    
}UART_Typedef;

typedef struct
{
    unsigned char       LCD_Mode;                                       // LCD模式

    
}Test_Typedef;


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

#endif /* __STRUCT_H */

/******************* (C) COPYRIGHT 2016 陆超 *****END OF FILE******************/
