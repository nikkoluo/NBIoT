/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Global.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  Global header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_H
#define __GLOBAL_H
/* Includes ------------------------------------------------------------------*/
#include "Global_Cfg.h"
#include "Struct.h"
#include "nrf51.h"
#include "ble.h"
#include "nrf_delay.h"
#include "Global_Typedef.h"
#include "SW_I2C.h"
#include "nordic_common.h"
#include "stdio.h"
#include "app_button.h"
#include "Task.h"
#include "ble_bas.h"
#include "GPIO.h"
#include "nrf_drv_wdt.h"
#include "app_trace.h"
#include "device_manager.h"
#include "ble_dfu.h"
#include "pstorage.h"

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
//----------------------- System ----------------------------------------------/
extern  u8                      Root_Access;                            // 超级权限
extern  u8                      Sys_Status;                             // 系统状态
extern  u8                      Sys_Init;                               // 置一完成初始化 
extern  Task_Typedef            Button_Task;                            // 按键任务
extern  Task_Typedef            LCD_Task;                               // LCD任务
extern  Task_Typedef            tVOC_Task;                              // tVOC任务
extern  Task_Typedef            Communal_Timer_Task;                    // 公用定时器任务
extern  Task_Typedef            Battery_Task;                           // 电池任务
extern  Task_Typedef            Temp_Humi_Task;                         // 温湿度任务
extern  Task_Typedef            BLE_Task;                               // BLE任务
extern  Task_Typedef            WDT_Task;                               // WDT任务
extern  Task_Typedef            Debug_Rx_Task;                          // 调试口接收任务
extern  Bond_Typedef            Sys_Bond;                               // 绑定
extern  UART_Typedef            Debug_UART;                             // 调试串口
extern  Button_Typedef          Button;                                 // 按键结构体
extern  Sensor_Typedef          Sensor;                                 // Sensor
extern  Time_Base_Typedef       System_Time_Base;                       // 系统时间基准
extern  System_ERR_Typedef      System_Err;                             // 系统错误结构体
extern  BLE_Service_Typedef     nRF51_BLE_Service;                      // nRF51 BLE私有服务
extern  nrf_drv_wdt_channel_id  WDT_Channel;                            // 声明看门狗通道变量

//----------------------- BLE -------------------------------------------------/
extern  u16                     BLE_Connect_Handle;                     // 当前连接处理状态
extern  ble_bas_t               Bat_Level_Service;                      // 电量服务
extern  dm_application_instance_t   DM_App_Handle;                      // dm handle
extern  ble_dfu_t               nRF51_DFU_Services;                     // DFU service

//----------------------- flash -----------------------------------------------/
extern  u8                      Flash_Used;                             // 置一时flash被占用
extern  pstorage_handle_t       MAC_Flash_Handle;                       // mac flash处理
extern  pstorage_handle_t       Token_Flash_Handle;                     // Token lash地址

//----------------------- Button ----------------------------------------------/
extern  app_button_cfg_t        Button_Cfg[MAX_INTERRUPT_PIN_NUM];      // Button配置结构体

//----------------------- Software IIC ----------------------------------------/
extern  SW_I2C_Typedef          Temp_Humi_I2C;                          // 温湿度的IIC
extern  SW_I2C_Typedef          Communal_IIC;                           // 通用IIC

/* Private function prototypes -----------------------------------------------*/
extern  u32  Timestamp_Interval_Get(u32 Time1, u32 Time2);              // 计算时间差值
extern  u32  Timestamp_Get(void);                                       // 获取时间戳
extern  u8   Timestamp_Timeout(u32 Time, u32 Timeout);                  // 超时计算
extern  u8   System_ms_Base_Timeout(u32 Time, u32 Timeout);             // ms超时
extern  u32  System_ms_Base_Update(void);                               // ms时间戳更新
extern  void Power_Manage(void);                                        // 电源管理 进入低功耗模式

#endif /* __GLOBAL_H */

/******************* (C) COPYRIGHT 2016 陆超 ********END OF FILE***************/
