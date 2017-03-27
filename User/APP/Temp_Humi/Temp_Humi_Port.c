/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Temp_Humi_Port.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  温湿度驱动程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Temp_Humi_Port.h"
#include "nrf_gpio.h"



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Temp_Humi_Delay(void);                                             // 延时
void Temp_Humi_Delay_us(void);                                          // us延时
void Temp_Humi_Pin_Init(void);                                          // 管脚初始化
void Temp_Humi_SDA_High(void);                                          // 拉高数据线
void Temp_Humi_SDA_Low(void);                                           // 拉低数据线
void Temp_Humi_SCL_High(void);                                          // 拉高时钟
void Temp_Humi_SCL_Low(void);                                           // 拉低时钟
void Temp_Humi_Set_SDA_Input(void);                                     // 设置SDA为输入模式
void Temp_Humi_Set_SDA_Output(void);                                    // 设置SDA为输出模式
void Temp_Humi_Set_SCL_Output(void);                                    // 设置SCL为输出模式
u8   Temp_Humi_SDA_Read(void);                                          // 读取SDA电平
u8   Temp_Humi_SCL_Read(void);                                          // 读取SCL电平

void Temp_Humi_Variable_Init(void);                                     // Temp_Humi变量初始化
u8   Temp_Humi_Port_Init(void);                                         // Temp_Humi端口初始化    
u8 Temp_Humi_Read_Register(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);// 读寄存器
u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);// 写寄存器
/* Private functions ---------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Delay
* Description    :  Temp_Humi延时
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Delay(void)
{
    nrf_delay_us(1);
    
}// End of void Temp_Humi_Delay(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Delay_us
* Description    :  Temp_Humi us延时
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Delay_us(void)
{
    nrf_delay_us(1);
    
}// End of void Temp_Humi_Delay_us(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Pin_Init
* Description    :  管脚初始化                   
* Input          :  P0.12   -->   SHT30_SCL_PIN
*                   P0.13   -->   SHT30_SDA_PIN
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
void Temp_Humi_Pin_Init(void)
{
    
    // 设置管脚为开漏模式
    NRF_GPIO->PIN_CNF[SHT30_SCL_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                                        | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                        | (GPIO_PIN_CNF_PULL_Disabled  << GPIO_PIN_CNF_PULL_Pos)  \
                                        | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                        | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

    NRF_GPIO->PIN_CNF[SHT30_SDA_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                                        | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                        | (GPIO_PIN_CNF_PULL_Disabled  << GPIO_PIN_CNF_PULL_Pos)  \
                                        | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                        | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

}// End of u8  Temp_Humi_Pin_Init(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_SDA_High
* Description    :  Temp_Humi拉高SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SDA_High(void)
{
    NRF_GPIO->OUTSET = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_SDA_High(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_SDA_Low
* Description    :  Temp_Humi拉低SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SDA_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_SDA_Low(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_SCL_High
* Description    :  Temp_Humi拉高SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SCL_High(void)
{
    NRF_GPIO->OUTSET = (1UL << SHT30_SCL_PIN);
    
}// End of void Temp_Humi_SCL_High(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_SCL_Low
* Description    :  Temp_Humi拉低SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SCL_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << SHT30_SCL_PIN);
    
}// End of void Temp_Humi_SCL_Low(void)


/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Set_SDA_Input
* Description    :  设置SDA管脚为输入模式
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Set_SDA_Input(void)
{
    NRF_GPIO->DIRCLR = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_Set_SDA_Input(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Set_SDA_Output
* Description    :  设置SDA管脚为输出模式
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Set_SDA_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_Set_SDA_Output(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Set_SCL_Output
* Description    :  设置SCL管脚为输出模式
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Set_SCL_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << SHT30_SCL_PIN);
    
}// End of void Temp_Humi_Set_SCL_Output(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_SDA_Read
* Description    :  读取SDA管脚电平
* Input          :  None
* Output         :  None
* Return         :  高电平返回1 低电平返回0
*******************************************************************************/
u8 Temp_Humi_SDA_Read(void)
{
    return((NRF_GPIO->IN >> SHT30_SDA_PIN) & 0x1UL);
    
}// End of u8 Temp_Humi_SDA_Read(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_SCL_Read
* Description    :  读取SCL管脚电平
* Input          :  None
* Output         :  None
* Return         :  高电平返回1 低电平返回0
*******************************************************************************/
u8 Temp_Humi_SCL_Read(void)
{
    return((NRF_GPIO->IN >> SHT30_SCL_PIN) & 0x1UL);
    
}// End of u8 Temp_Humi_SCL_Read(void)

/*******************************************************************************
*                           陆超@2016-12-23
* Function Name  :  Temp_Humi_Port_Init
* Description    :  Temp_Humi端口初始化
* Input          :  None
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 Temp_Humi_Port_Init(void)
{
    u8 Transfer_Succeeded; 

    Temp_Humi_I2C.Dealy                 = Temp_Humi_Delay;
    Temp_Humi_I2C.Dealy_us              = Temp_Humi_Delay_us;
    Temp_Humi_I2C.Pin_Init              = Temp_Humi_Pin_Init;
    Temp_Humi_I2C.SDA_High              = Temp_Humi_SDA_High;
    Temp_Humi_I2C.SDA_Low               = Temp_Humi_SDA_Low;
    Temp_Humi_I2C.SCL_High              = Temp_Humi_SCL_High;
    Temp_Humi_I2C.SCL_Low               = Temp_Humi_SCL_Low;
    Temp_Humi_I2C.Set_SDA_Input         = Temp_Humi_Set_SDA_Input; 
    Temp_Humi_I2C.Set_SDA_Output        = Temp_Humi_Set_SDA_Output; 
    Temp_Humi_I2C.Set_SCL_Output        = Temp_Humi_Set_SCL_Output;   
    Temp_Humi_I2C.SDA_Read              = Temp_Humi_SDA_Read; 
    Temp_Humi_I2C.SCL_Read              = Temp_Humi_SCL_Read;
    Temp_Humi_I2C.Wait_Scl_Free_Timeout = TEMP_HUMI_MAX_TIMEOUT_LOOPS;
    Transfer_Succeeded = SW_I2C_Init(&Temp_Humi_I2C);
    
    return (Transfer_Succeeded);
       
}// End of u8  Temp_Humi_Port_Init(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Variable_Init
* Description    :  温湿度变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Variable_Init(void)
{

    
}// End of void Temp_Humi_Variable_Init(void)




/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Read_Register
* Description    :  读寄存器
* Input          :  u16 usRead_Addr 要读取的地址
*                   u8* pBuffer     缓存指针
*                   u16 usRead_Len  读取长度
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 Temp_Humi_Read_Register(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)
{
    u8 Transfer_Succeeded = 1;
    u8 ucRead_Addr[2];
    if(usRead_Len == 0)
    {
        return 0;
    }
    ucRead_Addr[0] = (usRead_Addr >> 8) & 0xFF;
    ucRead_Addr[1] = (usRead_Addr >> 0) & 0xFF;
    Transfer_Succeeded &= SW_I2C_Transfer(&Temp_Humi_I2C, SHT3x_WRITE_ADDR, ucRead_Addr, 2, SW_I2C_DONT_SEND_STOP);
    Transfer_Succeeded &= SW_I2C_Transfer(&Temp_Humi_I2C, SHT3x_READ_ADDR, pBuffer, usRead_Len, SW_I2C_NEED_SEND_STOP);

    nrf_delay_us(100);

    return Transfer_Succeeded;
    
}// End of u8 Temp_Humi_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Write_Register
* Description    :  写芯片寄存器
* Input          :  u16 usWrite_Addr    要写入的地址
*                   u8* pBuffer         缓存指针
*                   u16 usWrite_Len     写入长度 
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
    unsigned char Transfer_Succeeded = 1;
    u8 ucWrite_Addr[2];

    ucWrite_Addr[0] = (usWrite_Addr >> 8) & 0xFF;
    ucWrite_Addr[1] = (usWrite_Addr >> 0) & 0xFF;
    
    // 发送写命令
    Transfer_Succeeded &= SW_I2C_Transfer(&Temp_Humi_I2C, SHT3x_WRITE_ADDR, ucWrite_Addr, 2, SW_I2C_DONT_SEND_STOP);
    
    // 长度保护
    if (usWrite_Len == 0)
    {
        return 0;
    }

    // 发送数据
    while (usWrite_Len-- && Transfer_Succeeded)
    {
        Transfer_Succeeded &= SW_IIC_Write_Byte(&Temp_Humi_I2C, *pBuffer);
        pBuffer++;
    }


    // 发送停止位
    Transfer_Succeeded &= SW_I2C_Stop_Condition(&Temp_Humi_I2C);

    nrf_delay_us(100);
    
    return Transfer_Succeeded;
    
}// End of u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/******************* (C) COPYRIGHT 2016 陆超 ************* END OF FILE ********/

