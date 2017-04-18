/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Global_Cfg.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  Global header file
* Description        :  全局定义
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_CFG_H
#define __GLOBAL_CFG_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
//----------------------- System ----------------------------------------------/
#define     DEBUG
#ifdef      DEBUG
#define     ENABLE_DEBUG_LOG_SUPPORT                                    // 使能系统调试
#endif
//#define     SYS_WDT                                                     // 使能看门狗
//#define     BLE_OPEN                                                    // 使能BLE



#define     SYS_STATUS_IDLE             0x00                            // 默认状态
#define     SYS_STATUS_ADV              0x01                            // 广播态
#define     SYS_STATUS_CONNECT          0x02                            // 连接态



#define     APP_TIMER_DIV               0                               // APP定时器分频
#define     SYS_MAX_TIMERS              2 + 10                          // 最多定时器个数   GPIOE占用一个  m_conn_params_timer_id 占用一个   
#define     SYS_MAX_OP_QUEUE_SIZE       12                              // 最多操作队列数
#define     MAX_EVENT_QUEUE_SIZE        (2 * SYS_MAX_OP_QUEUE_SIZE)     // 最大待处理事件队列大小


#define     TICK_TO_MS                  33                              // tick数转成ms

//----------------------- Task ------------------------------------------------/
#define     TASK_BATTERY_PERIOD         (10 * 1000)                     // 电量检测任务周期
#define     TASK_TEMP_HUMI_PERIOD       (1 * 1000)                      // 温湿度检测任务周期
#define     TASK_TVOC_PERIOD      	    (1 * 1000)                      // tVOC检测任务周期
#define     TASK_BLE_PERIOD             (1 * 1000)                      // BLE任务周期
#define     TASK_LCD_PERIOD             (1 * 1000)                      // LCD任务周期
#define     TASK_COMMUNAL_TIMER_PERIOD  (1 * 100)                       // 公用定时器任务周期
#define     TASK_COMMUNAL_TIMER_FREQ    (1000 / TASK_COMMUNAL_TIMER_PERIOD) // 公用定时器任务频率
#define     TASK_MAGNET_CHECK_PERIOD    (1 * TASK_COMMUNAL_TIMER_FREQ)  // 磁铁检测周期

//----------------------- BLE -------------------------------------------------/
#define     CENTRAL_LINK_COUNT          0                               // 连接的主机数量    
#define     PERIPHERAL_LINK_COUNT       1                               // 连接的从机数量
#define     BLE_DEVICE_NAME             "NBIOT"                         // BLE设备名称

#define     BLE_MANUFACTURER_NAME       "Cleargrass Inc"                // 制造商          
#define     BLE_FW_REV_STR              "00.00.17"                       // 软件版本
#define     BLE_MODULE_NUM              "Duck"                          // 型号 
#define     DEFAULT_HARDWARE_VERSION    "2.00"                          // 默认硬件版本  

#define     BLE_ADV_INTERVAL            MSEC_TO_UNITS(1000, UNIT_0_625_MS) // 广播间隔                          // BLE设备名称
#define     MIN_CONN_INTERVAL           MSEC_TO_UNITS(20, UNIT_1_25_MS)             /**< Minimum acceptable connection interval (20 ms), Connection interval uses 1.25 ms units. */
#define     MAX_CONN_INTERVAL           MSEC_TO_UNITS(75, UNIT_1_25_MS)             /**< Maximum acceptable connection interval (75 ms), Connection interval uses 1.25 ms units. */
#define     SLAVE_LATENCY               0                                           /**< Slave latency. */
#define     CONN_SUP_TIMEOUT            MSEC_TO_UNITS(4000, UNIT_10_MS)             /**< Connection supervisory timeout (4 seconds), Supervision Timeout uses 10 ms units. */

#define     DUCK_FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000, APP_TIMER_DIV)  /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define     DUCK_NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000, APP_TIMER_DIV) /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define     DUCK_MAX_CONN_PARAMS_UPDATE_COUNT    3  

//----------------------- flash -----------------------------------------------/
#define     MAC_FLASH_SIZE              6                               // mac flash储存字节
#define     TOKEN_FLASH_SIZE            8                               // token flash储存字节

//----------------------- BLE MIOT --------------------------------------------/
#define     MIOT_EVENT_ID_TH            0x100D                          // 温湿度事件ID
#define     MIOT_EVENT_TH_LEN           3                               // 温湿度事件长度 

#define     MIOT_EVENT_ID_BAT           0x100A                          // 电量事件ID 
#define     MIOT_EVENT_BAT_LEN          1                               // 电量事件长度 

#define     MIOT_EVENT_ID_HALL          0x2400                          // hall事件ID 
#define     MIOT_EVENT_HALL_LEN         1                               // hall事件长度 

#define     MIOT_EVENT_ID_BOND          0x0002                          // 绑定事件 
#define     MIOT_EVENT_BOND_LEN         2                               // 绑定事件长度  


#define     MIOT_SERVICE_ID             0xFE95                          // MIOT服务ID 
#define     MIOT_PRODUCT_ID             0x01AA                          // MIOT产品ID 
#define     MIOT_VERSION                (0x02 & 0x0F)                   // 协议版本  
#define     MIOT_NEED_BOND              0x01                            // 需要绑定  

#define     MIOT_MAX_SIZE               (BLE_GAP_ADV_MAX_SIZE - 3 - 4)  // 最大字节数 flag 3字节 MIOT 4字节

#define     MIOT_MASTER_EVENT_INTERVAL  10                              // 主任务间隔
#define     MIOT_SLAVE_EVENT_INTERVAL   (1 + MIOT_MASTER_EVENT_INTERVAL)// 从任务间隔

#define     MIOT_HALL_EVENT_INTERVAL    5                               // 霍尔间隔
#define     MIOT_BAT_EVENT_INTERVAL     10                              // 电池间隔

//----------------------- BLE Bond --------------------------------------------/
#define     MIOT_EVENT_ID_BOND_DURATION 30 * TASK_COMMUNAL_TIMER_FREQ   // 绑定事件持续时间 
#define     MIOT_BOND_BLINK             (500 / TASK_COMMUNAL_TIMER_PERIOD)// 500ms 闪烁一次
#define     MIOT_BOND_STOP_DELAY        5 * TASK_COMMUNAL_TIMER_FREQ    // 5s 绑定后继续闪烁一次

//----------------------- LCD -------------------------------------------------/
#define     LCD_BUFFER_SIZE             13                              // LCD缓存大小

//----------------------- Sensor ----------------------------------------------/
#define     MAX_GET_SENSOR_ERROR        10                              // 最大采集传感器错误数

//----------------------- Special Code ----------------------------------------/
#define     SPECIAL_CODE_RESET          0x10000000                      // 人为复位

//----------------------- Pin Config ------------------------------------------/
#define     GPIO_TEST_PIN               1                               // 速度测试 管脚

#define     BAT_ADC_PIN                 3                             	// 电池ADC 管脚

#define     COMMUNAL_IIC_2_SCL_PIN      7                              	// 通用IIC时钟
#define     COMMUNAL_IIC_2_SDA_PIN      8                              	// 通用IIC数据


#define     UART_TX_PIN                 9                               // 串口
#define     UART_RX_PIN                 11


#define     SHT30_SCL_PIN               12                              // 温湿度时钟
#define     SHT30_SDA_PIN               13                              // 温湿度数据

#define     COMMUNAL_IIC_SCL_PIN        14                              // 通用IIC时钟
#define     COMMUNAL_IIC_SDA_PIN        15                              // 通用IIC数据

#define     OLED_SCL_PIN                25                              // OLED SCL 管脚
#define     OLED_SDA_PIN               	24                              // OLED SDA 管脚
#define     OLED_RST_PIN               	23                              // OLED RST 管脚
#define     OLED_DC_PIN               	22                              // OLED DC 管脚 数据命令选择管脚






#define     BOUTTON_PIN                 17                              // 按键管脚




#define     MAX_INTERRUPT_PIN_NUM       1                               // 中断管脚数据
#define     BUTTEN_EVENT_DELAY_MS       10                              // 按键事件延时时间

//----------------------- Battery ---------------------------------------------/

#define     BAT_ADC_CHANNEL             NRF_ADC_CONFIG_INPUT_4          // 电池ADC通道
#define     BAT_ADC_BUFFER_SIZE         8                               // ADC缓存深度


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

#endif /* __GLOBAL_CFG_H */

/******************* (C) COPYRIGHT 2016 陆超 ********END OF FILE***************/
