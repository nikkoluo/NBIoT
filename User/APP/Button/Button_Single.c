/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Button_Single.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  单击应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button_Single.h"
#include "nrf_gpio.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Single_Button_Handler(void);                                       // 单击处理


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Single_Button_Handler
* Description    :  处理单击事件
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Single_Button_Handler(void)
{
    // 非单击状态
    app_trace_log("单击任务\r\n");

}// End of void Single_Button_Handler(void)


/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/




