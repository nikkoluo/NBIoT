/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Debug_Port.c
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/17/2017
* Description        :  Debug驱动程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Debug_Port.h"
#include "nrf_gpio.h"
#include "app_uart.h"
#include "app_error.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Debug_Variable_Init(void);                                         // Debug变量初始化
void Debug_Port_Init(void);                                             // Debug端口初始化  
void Debug_Uart_Event_Handle(app_uart_evt_t * Event_Ptr);               // 串口Handle处理

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-02-17
* Function Name  :  Debug_Uart_Event_Handle
* Description    :  串口Handle处理
* Input          :  app_uart_evt_t * Event_Ptr  待处理的事件指针
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Uart_Event_Handle(app_uart_evt_t * Event_Ptr)
{
    u8 ucTemp;
    
    // 判断事件类型
    switch (Event_Ptr->evt_type)
    {
        case APP_UART_DATA_READY:
        {

            while (app_uart_get(&ucTemp) != NRF_ERROR_NOT_FOUND)
            {
                // 非等待处理状态
                if (Debug_UART.Rx_State != UART_RX_STATE_PENDING)
                {
                    // 接收态
                    Debug_UART.Rx_State = UART_RX_STATE_BUSY;

                    // 非溢出
                    if (Debug_UART.Rx_Len < 128)
                    {
                        // 首次接收 启动定时器
                        if(Debug_UART.Rx_Len == 0)
                        {
                            Task_Timer_Start(&Debug_Rx_Task, NULL);
                        }
                        
                        Debug_UART.Rx_Data[Debug_UART.Rx_Len++] = ucTemp;
                    }

                    // 刷新接收超时
                    Debug_UART.Rx_Timeout = 2;
                }


            }
            
        }break;

        case APP_UART_COMMUNICATION_ERROR:
        {
            // 暂时排除接收错误
            if (Event_Ptr->data.error_communication & 0x03)
            {
                APP_ERROR_HANDLER(Event_Ptr->data.error_communication);
            }
            else
            {
                app_trace_log("---------------------------------------------- Rx Error = 0x%02X\r\n", Event_Ptr->data.error_communication);
            }
            
        }break;

        case APP_UART_FIFO_ERROR:
        {
            APP_ERROR_HANDLER(Event_Ptr->data.error_code);
            
        }break;

        default:
        break;
    }
    
}// End of void Debug_Uart_Event_Handle(app_uart_evt_t * Event_Ptr)


/*******************************************************************************
*                           陆超@2017-02-17
* Function Name  :  Debug_Variable_Init
* Description    :  Debug变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Variable_Init(void)
{
    Debug_UART.Rx_Len      = 0;
    Debug_UART.Rx_State    = UART_RX_STATE_IDLE;
    Debug_UART.Tx_Len      = 0;


    
}// End of void Debug_Variable_Init(void)

/*******************************************************************************
*                           陆超@2017-02-17
* Function Name  :  Debug_Port_Init
* Description    :  Debug端口初始化 
*                   P.25   <--   DEBUG_RX_PIN
*                   P.24    -->  DEBUG_TX_PIN
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Port_Init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    const app_uart_comm_params_t Debug_UART_Params =
    {
        UART_RX_PIN,
        UART_TX_PIN,
        0xFF,
        0xFF,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud115200
    };

    APP_UART_FIFO_INIT( &Debug_UART_Params,                 // 串口参数
                        UART_RX_BUF_SIZE,                   // 接收缓存大小
                        UART_TX_BUF_SIZE,                   // 发送缓存大小
                        Debug_Uart_Event_Handle,            // 回调处理中断
                        APP_IRQ_PRIORITY_LOW,               // 中断优先级
                        err_code);
                        
    APP_ERROR_CHECK(err_code);
    
    
}// End of void Debug_Port_Init(void)



/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/

