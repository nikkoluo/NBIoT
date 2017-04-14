/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  GPIO.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIO应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "GPIO.h"
#include "nrf_gpio.h"




/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void GPIO_Task_Handle(void *p_arg);                                     // GPIO任务
void GPIO_Task_Create(void);                                            // 创建GPIO任务
void GPIO_TEST_High(void);                                              // Test Pin拉高
void GPIO_TEST_Low(void);                                               // Test Pin拉低                      
void GPIO_TEST_Toggle(void);                                            // Test Pin翻转

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  GPIO_Task_Create
* Description    :  创建GPIO任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Task_Create(void)
{


    // 初始化变量和IO
    GPIO_Variable_Init();
    GPIO_Port_Init();

    // 默认拉低
    GPIO_TEST_Low();
    

    
    
}// End of void GPIO_Task_Create(void)



/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  GPIO_Task_Handle
* Description    :  GPIO任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Task_Handle(void *p_arg)
{

   
}// End of void GPIO_Task_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  GPIO_TEST_High
* Description    :  GPIO 拉高
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_TEST_High(void)
{
    GPIO_Set_Pin_High(GPIO_TEST_PIN);
   
}// End of void GPIO_TEST_High(void)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  GPIO_TEST_Low
* Description    :  GPIO 拉低
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_TEST_Low(void)
{
    GPIO_Set_Pin_Low(GPIO_TEST_PIN);
   
}// End of void GPIO_TEST_Low(void)

/*******************************************************************************
*                           陆超@2017-01-06
* Function Name  :  GPIO_TEST_Toggle
* Description    :  GPIO 翻转
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_TEST_Toggle(void)
{

    nrf_gpio_pin_toggle(GPIO_TEST_PIN);
    
}// End of void GPIO_TEST_Toggle(void)


/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




