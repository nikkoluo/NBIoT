/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  GPIO_Port.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIO驱动程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "GPIO_Port.h"
#include "nrf_gpio.h"



/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void GPIO_Variable_Init(void);                                          // GPIO变量初始化
void GPIO_Port_Init(void);                                              // GPIO端口初始化    
void GPIO_Set_Pin_High(u8 ucPin);                                       // 管脚置高
void GPIO_Set_Pin_Low(u8 ucPin);                                        // 管脚置低   

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-03
* Function Name  :  GPIO_Port_Init
* Description    :  GPIO端口初始化
* Input          :  P0.01   -->   GPIO_TEST_PIN
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Port_Init(void)
{
    // 配置管脚为输出
    nrf_gpio_cfg_output(GPIO_TEST_PIN);

       
}// End of void  GPIO_Port_Init(void)

/*******************************************************************************
*                           陆超@2017-01-03
* Function Name  :  GPIO_Variable_Init
* Description    :  GPIO变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Variable_Init(void)
{

  
}// End of void GPIO_Variable_Init(void)

/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  GPIO_Set_Pin_High
* Description    :  管脚置高
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Set_Pin_High(u8 ucPin)
{
    
    nrf_gpio_pin_set(ucPin);
       
}// End of void GPIO_Set_Pin_High(u8 ucPin)

/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  GPIO_Set_Pin_Low
* Description    :  管脚置低
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Set_Pin_Low(u8 ucPin)
{
    nrf_gpio_pin_clear(ucPin);
    
}// End of void GPIO_Set_Pin_Low(u8 ucPin)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/

