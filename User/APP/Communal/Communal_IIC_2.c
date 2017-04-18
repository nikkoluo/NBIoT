/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Communal_IIC_2.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/19/2017
* Description        :  通用IIC2驱动程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Communal_IIC_2.h"
#include "nrf_gpio.h"



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Communal_IIC_2_Delay(void);                                        // 延时
void Communal_IIC_2_Delay_us(void);                                     // us延时
void Communal_IIC_2_Pin_Init(void);                                     // 管脚初始化
void Communal_IIC_2_SDA_High(void);                                     // 拉高数据线
void Communal_IIC_2_SDA_Low(void);                                      // 拉低数据线
void Communal_IIC_2_SCL_High(void);                                     // 拉高时钟
void Communal_IIC_2_SCL_Low(void);                                      // 拉低时钟
void Communal_IIC_2_Set_SDA_Input(void);                                // 设置SDA为输入模式
void Communal_IIC_2_Set_SDA_Output(void);                               // 设置SDA为输出模式
void Communal_IIC_2_Set_SCL_Output(void);                               // 设置SCL为输出模式
u8   Communal_IIC_2_SDA_Read(void);                                     // 读取SDA电平
u8   Communal_IIC_2_SCL_Read(void);                                     // 读取SCL电平

void Communal_IIC_2_Variable_Init(void);                                  // Communal_IIC_2变量初始化
u8   Communal_IIC_2_Init(void);                                           // Communal_IIC_2端口初始化    

/* Private functions ---------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_Delay
* Description    :  Communal_IIC_2延时
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Delay(void)
{
    nrf_delay_us(1);
    
}// End of void Communal_IIC_2_Delay(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_Delay_us
* Description    :  Communal_IIC_2 us延时
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Delay_us(void)
{
    nrf_delay_us(1);
    
}// End of void Communal_IIC_2_Delay_us(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_Pin_Init
* Description    :  管脚初始化                   
* Input          :  P0.14   -->   COMMUNAL_IIC_2_SCL_PIN
*                   P0.15   -->   COMMUNAL_IIC_2_SDA_PIN
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
void Communal_IIC_2_Pin_Init(void)
{
    
    // 设置管脚为开漏模式
    NRF_GPIO->PIN_CNF[COMMUNAL_IIC_2_SCL_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled  << GPIO_PIN_CNF_SENSE_Pos) \
                                                | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                                | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                                                | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                                | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

    NRF_GPIO->PIN_CNF[COMMUNAL_IIC_2_SDA_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled  << GPIO_PIN_CNF_SENSE_Pos) \
                                                | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                                | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                                                | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                                | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

}// End of u8  Communal_IIC_2_Pin_Init(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_SDA_High
* Description    :  Communal_IIC_2拉高SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SDA_High(void)
{
    NRF_GPIO->OUTSET = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_SDA_High(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_SDA_Low
* Description    :  Communal_IIC_2拉低SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SDA_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_SDA_Low(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_SCL_High
* Description    :  Communal_IIC_2拉高SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SCL_High(void)
{
    NRF_GPIO->OUTSET = (1UL << COMMUNAL_IIC_2_SCL_PIN);
    
}// End of void Communal_IIC_2_SCL_High(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_SCL_Low
* Description    :  Communal_IIC_2拉低SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SCL_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << COMMUNAL_IIC_2_SCL_PIN);
    
}// End of void Communal_IIC_2_SCL_Low(void)


/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_Set_SDA_Input
* Description    :  设置SDA管脚为输入模式
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Set_SDA_Input(void)
{
    NRF_GPIO->DIRCLR = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_Set_SDA_Input(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_Set_SDA_Output
* Description    :  设置SDA管脚为输出模式
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Set_SDA_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_Set_SDA_Output(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_Set_SCL_Output
* Description    :  设置SCL管脚为输出模式
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Set_SCL_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << COMMUNAL_IIC_2_SCL_PIN);
    
}// End of void Communal_IIC_2_Set_SCL_Output(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_SDA_Read
* Description    :  读取SDA管脚电平
* Input          :  None
* Output         :  None
* Return         :  高电平返回1 低电平返回0
*******************************************************************************/
u8 Communal_IIC_2_SDA_Read(void)
{
    return((NRF_GPIO->IN >> COMMUNAL_IIC_2_SDA_PIN) & 0x1UL);
    
}// End of u8 Communal_IIC_2_SDA_Read(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_SCL_Read
* Description    :  读取SCL管脚电平
* Input          :  None
* Output         :  None
* Return         :  高电平返回1 低电平返回0
*******************************************************************************/
u8 Communal_IIC_2_SCL_Read(void)
{
    return((NRF_GPIO->IN >> COMMUNAL_IIC_2_SCL_PIN) & 0x1UL);
    
}// End of u8 Communal_IIC_2_SCL_Read(void)

/*******************************************************************************
*                           陆超@2017-12-23
* Function Name  :  Communal_IIC_2_Init
* Description    :  Communal_IIC_2端口初始化
* Input          :  None
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 Communal_IIC_2_Init(void)
{
    u8 Transfer_Succeeded; 

    // 变量初始化
    Communal_IIC_2_Variable_Init();
    
    Communal_IIC_2.Dealy                 = Communal_IIC_2_Delay;
    Communal_IIC_2.Dealy_us              = Communal_IIC_2_Delay_us;
    Communal_IIC_2.Pin_Init              = Communal_IIC_2_Pin_Init;
    Communal_IIC_2.SDA_High              = Communal_IIC_2_SDA_High;
    Communal_IIC_2.SDA_Low               = Communal_IIC_2_SDA_Low;
    Communal_IIC_2.SCL_High              = Communal_IIC_2_SCL_High;
    Communal_IIC_2.SCL_Low               = Communal_IIC_2_SCL_Low;
    Communal_IIC_2.Set_SDA_Input         = Communal_IIC_2_Set_SDA_Input; 
    Communal_IIC_2.Set_SDA_Output        = Communal_IIC_2_Set_SDA_Output; 
    Communal_IIC_2.Set_SCL_Output        = Communal_IIC_2_Set_SCL_Output;   
    Communal_IIC_2.SDA_Read              = Communal_IIC_2_SDA_Read; 
    Communal_IIC_2.SCL_Read              = Communal_IIC_2_SCL_Read;
    Communal_IIC_2.Wait_Scl_Free_Timeout = COMMUNAL_IIC_2_MAX_LPPOS;
    Transfer_Succeeded = SW_I2C_Init(&Communal_IIC_2);
    
    return (Transfer_Succeeded);
       
}// End of u8  Communal_IIC_2_Init(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  Communal_IIC_2_Variable_Init
* Description    :  通用IIC2初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Variable_Init(void)
{
    // 默认未初始化
    Communal_IIC_2.Inited = 0;
    
}// End of void Communal_IIC_2_Variable_Init(void)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/

