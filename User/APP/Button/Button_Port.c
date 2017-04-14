/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Button_Port.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  按键驱动程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button_Port.h"
#include "nrf_gpio.h"
#include "Button.h"
#include "app_button.h"


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Button_Variable_Init(void);                                        // 按键屏变量初始化
void Button_Pin_Handler(u8 ucPin_No, u8 ucAction);                      // 按键管脚处理


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2014-09-04
* Function Name  :  Button_Variable_Init
* Description    :  按键变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Variable_Init(void)
{
    Button.Free_Timestamp = 0;
    Button.Push_Timestamp = 0;
    Button.Status         = 0;
    Button.Long           = 0;
    
}// End of void Button_Variable_Init(void)


/*******************************************************************************
*                           陆超@2016-05-10
* Function Name  :  Button_Pin_Handler
* Description    :  按键管脚处理
* Input          :  u8 ucPin_No     管脚号
*                   u8 ucAction     行为
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Pin_Handler(u8 ucPin_No, u8 ucAction)
{
    // 触发
    if(ucAction == APP_BUTTON_PUSH)
    {
//        app_trace_log("Key1按下!\r\n");

        Button_Push_ISR();
    }
    // 释放
    else
    {
        // 下降沿处理
//        app_trace_log("Key1释放!\r\n");

        Button_Free_ISR();

    }

}// End of void Button_Pin_Handler(u8 ucPin_No, u8 ucAction)



/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/

