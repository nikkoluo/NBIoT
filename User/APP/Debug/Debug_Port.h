/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Debug_Port.h
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/17/2017
* Description        :  Debug_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_PORT_H
#define __DEBUG_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/

#ifndef UART_TX_BUF_SIZE
    #define UART_TX_BUF_SIZE 256                                        // UART TX buffer size
#endif
#ifndef UART_RX_BUF_SIZE
    #define UART_RX_BUF_SIZE 16                                         //  UART RX buffer size
#endif

#define		UART_RX_STATE_IDLE		    0x00 							// 接口空闲
#define		UART_RX_STATE_BUSY			0x01 							// 接收中
#define		UART_RX_STATE_PENDING		0x02 							// 待处理

/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Debug_Port_Init(void);                                     // Debug端口初始化  
extern  void Debug_Variable_Init(void);                                 // Debug变量初始化


#endif /* __DEBUG_PORT_H */

/******************* (C) COPYRIGHT 2017 陆超 *****END OF FILE******************/
