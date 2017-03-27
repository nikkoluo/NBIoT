/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Hall.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/27/2017
* Description        :  Hall应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Hall.h"
#include "Duck_BLE.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Hall_Open(void);                                                   // 开hall
void Hall_Close(void);                                                  // 关hall
void Hall_Magnet_Check(void);                                           // 霍尔磁铁判断 
void Hall_Update(void);                                                 // 霍尔状态刷新
u8 Is_Magnet_Near(void);                                                // 是否有磁铁在附近

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-02-27
* Function Name  :  Hall_Open
* Description    :  Hall打开
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Open(void)
{
    // 开霍尔
    nrf_gpio_pin_set(HALL_EN_PIN);
 
    
}// End of void Hall_Open(void)

/*******************************************************************************
*                           陆超@2017-02-27
* Function Name  :  Hall_Close
* Description    :  Hall关闭
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Close(void)
{
    // 关霍尔
    nrf_gpio_pin_clear(HALL_EN_PIN);

    
}// End of void Hall_Close(void)

/*******************************************************************************
*                           陆超@2017-03-15
* Function Name  :  Hall_Update
* Description    :  Hall关闭
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Update(void)
{
    // 获取霍尔状态
    Hall_Open();
    nrf_delay_ms(100);
    
    // 获取磁铁状态
    Hall.Magnet_Near = Is_Magnet_Near();
    Hall.Magnet_Last = Hall.Magnet_Near;

    // 关霍尔
    Hall_Close();
    
}// End of void Hall_Update(void)

/*******************************************************************************
*                           陆超@2017-02-27
* Function Name  :  Is_Magnet_Near
* Description    :  是否磁铁在附近
* Input          :  None
* Output         :  None
* Return         :  1 有磁铁 0 无磁铁
*******************************************************************************/
u8 Is_Magnet_Near(void)
{
    u8 ucReturn = 0;

    // 磁铁存在 低电平
    if (nrf_gpio_pin_read(HALL_OUT_PIN) == 0)
    {
        ucReturn = 1;
    }
    else
    {
        ucReturn = 0;

    }

    return (ucReturn);
    
}// End of u8 Is_Magnet_Near(void)

/*******************************************************************************
*                           陆超@2017-02-27
* Function Name  :  Hall_Magnet_Check
* Description    :  hall磁铁判断
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Magnet_Check(void)
{
    Hall.Timestamp++;

    // 是否到检测时间到
    if (Hall.Timestamp == TASK_MAGNET_CHECK_PERIOD)
    {
        // 开霍尔
        Hall_Open();

    }
    else if (Hall.Timestamp > TASK_MAGNET_CHECK_PERIOD)
    {
              
        Hall.Timestamp = 0;
        
        // 获取磁铁状态
        Hall.Magnet_Near = Is_Magnet_Near();

        // 关霍尔
        Hall_Close();

        // 霍尔状态变化
        if (Hall.Magnet_Last != Hall.Magnet_Near)
        {
            // 发送突变事件
            Duck_BLE_Int_Evt_Set(MIOT_EVENT_ID_HALL);

            app_trace_log("Hall = %d !\r\n", Hall.Magnet_Near); 
            
        }

        Hall.Magnet_Last = Hall.Magnet_Near;
    }
    
}// End of void Hall_Magnet_Check(void)


/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




