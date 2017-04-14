/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  SW_I2C.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/26/2016
* Description        :  软I2C
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "SW_I2C.h"

/* Private define ------------------------------------------------------------*/
#define     SW_I2C_ACK                  0x00                            // 有应答
#define     SW_I2C_NACK                 0x01                            // 无应答

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C);                              // 管脚初始化
unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData);  // IIC写字节
unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Need_Ack);   // IIC读字节
unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C);           // 产生起始信号
unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C);            // 产生停止信号
unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition); // 发送数据

static unsigned char SW_I2C_Wait_SCL_Turn_High(SW_I2C_Typedef *SW_I2C); // 等待SCL被从机释放
static unsigned char SW_I2C_Clear_Bus(SW_I2C_Typedef *SW_I2C);          // 清空总线


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_I2C_Init
* Description    :  I2C端口初始化 
* Input          :  SW_I2C_Typedef *SW_I2C  I2C参数
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C)
{
    // 防止多次初始化
    if (SW_I2C->Inited)
    {
        return 1;
    }

    SW_I2C->Inited = 1;

    // 管脚初始化
    SW_I2C->Pin_Init();
    
    return SW_I2C_Clear_Bus(SW_I2C);
       
}// End of unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_I2C_Wait_SCL_Turn_High
* Description    :  等待SCL被从机释放
* Input          :  SW_I2C_Typedef *SW_I2C  操作结构体指针
*                   unsigned char ucData    要发送的数据       
* Output         :  None
* Return         :  成功返回1 失败返回0
*******************************************************************************/
static unsigned char SW_I2C_Wait_SCL_Turn_High(SW_I2C_Typedef *SW_I2C)
{

    unsigned int volatile Timeout_Counter = SW_I2C->Wait_Scl_Free_Timeout;


    // 释放SCL
    SW_I2C->SCL_High();

    // 等待时钟为高
    while (SW_I2C->SCL_Read() == 0)
    {
        if (Timeout_Counter == 0)
        {
            // 超时
            return 0;
        }
        else
        {
            Timeout_Counter--;
            SW_I2C->Dealy_us();
        }
    }
    SW_I2C->Dealy();
    return 1;
    
}// End of static unsigned char SW_I2C_Wait_SCL_Turn_High(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_IIC_Write_Byte
* Description    :  IIC写数据
* Input          :  SW_I2C_Typedef *SW_I2C  操作结构体指针
*                   unsigned char ucData    要发送的数据       
* Output         :  None
* Return         :  成功返回1 失败返回0
*******************************************************************************/
unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData)
{
    unsigned char Transfer_Succeeded = 1;
    unsigned char i;
    
    // 设置SDA为输出模式
    SW_I2C->Set_SDA_Output();

    // 拉低时钟
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    // 先发送高字节
    for (i = 0x80; i > 0; i >>= 1)
    {
        if (ucData & i)
        {
            SW_I2C->SDA_High();
        }
        else
        {
            SW_I2C->SDA_Low();
        }

        // 等待Scl释放
        if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
        {
            // 超时
            Transfer_Succeeded = 0; 
            break;
        }

        // 拉低时钟
        SW_I2C->SCL_Low();
        SW_I2C->Dealy();
    }

    // 设置为输入模式
    SW_I2C->Set_SDA_Input();
    SW_I2C->Dealy();

    // 等待时钟空闲
    Transfer_Succeeded &= SW_I2C_Wait_SCL_Turn_High(SW_I2C);

    // 读取ACK
    if (SW_I2C->SDA_Read() & SW_I2C_NACK)
    {
        // 无应答
        Transfer_Succeeded = 0x00;    
    }
    else
    {
        // 有应答
        Transfer_Succeeded &= 0x01;    
    }

    // 产生最后时钟
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    // 还原为输入模式
    SW_I2C->Set_SDA_Output();

    return Transfer_Succeeded;
    
}// End of unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData)


/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_IIC_Read_Byte
* Description    :  IIC读取一个字节数据
* Input          :  SW_I2C_Typedef *SW_I2C      操作结构体指针
*                   unsigned char *Data_Byte    读取数据缓存
*                   unsigned char Need_Ack      置一是发送ACK
* Output         :  None
* Return         :  成功返回1 失败返回0
*******************************************************************************/
unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Send_Ack)
{
    unsigned char Byte_Read          = 0;
    unsigned char Transfer_Succeeded = 1;
    unsigned char i;

    // 设置SDA为输入模式并拉高
    SW_I2C->Set_SDA_Input();

    // 高位在前
    for (i = 0x80; i > 0; i >>= 1)
    {
        // 等待IIC释放
        if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
        {
            Transfer_Succeeded = 0;
            break;
        }

        if (SW_I2C->SDA_Read())
        {
            Byte_Read |= i;
        }

        SW_I2C->SCL_Low();
        SW_I2C->Dealy();
    }

    // 恢复SDA为输出模式
    SW_I2C->Set_SDA_Output();

    // 记录数据
    *Data_Byte = Byte_Read;
    
    // 发送ACK
    if (Send_Ack == SW_I2C_SEND_ACK)
    {
        SW_I2C->SDA_Low();
    }
    else
    {
        SW_I2C->SDA_High();
    }

    // 延时
    SW_I2C->Dealy();

    // 等待从机响应
    if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
    {
        // 超时
        Transfer_Succeeded = 0; 
    }

    // 完成最后时钟
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    return Transfer_Succeeded;
    
}// End of unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Need_Ack)

/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_I2C_Clear_Bus
* Description    :  清空总线
* Input          :  SW_I2C_Typedef *SW_I2C  操作指针
* Output         :  None
* Return         :  成功返回1 失败返回0
*******************************************************************************/
static unsigned char SW_I2C_Clear_Bus(SW_I2C_Typedef *SW_I2C)
{
    unsigned char  Bus_Clear;
    unsigned char  i;

    // 释放总线
    SW_I2C->SDA_High();
    SW_I2C->SCL_High();
    SW_I2C->Dealy();

    if (SW_I2C->SDA_Read() == 1 && SW_I2C->SCL_Read() == 1)
    {
        Bus_Clear = 1;
    }
    else if (SW_I2C->SCL_Read() == 1)
    {
        Bus_Clear = 0;
      
        for(i = 0; i < 18; i++)
        {
            SW_I2C->SCL_Low();
            SW_I2C->Dealy();
            SW_I2C->SCL_High();
            SW_I2C->Dealy();

            if (SW_I2C->SDA_Read() == 1)
            {
                Bus_Clear = 1;
                break;
            }
        }
    }
    else
    {
        Bus_Clear = 0;
    }

    return Bus_Clear;
    
}// End of static unsigned char SW_I2C_Clear_Bus(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_I2C_Start_Condition
* Description    :  产生I2C起始信号
* Input          :  SW_I2C_Typedef *SW_I2C  操作指针
* Output         :  None
* Return         :  成功返回1 失败返回0
*******************************************************************************/
unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C)
{


    // 拉高SDA SCL
    SW_I2C->SDA_High();
    SW_I2C->Dealy();

    // 等待SCL变高
    if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
    {
        return 0;
    }

    // 拉低数据和时钟产生起始条件
    SW_I2C->SDA_Low();
    SW_I2C->Dealy();
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    return 1;
    
}// End of unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C)


/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_I2C_Stop_Condition
* Description    :  产生I2C停止信号
* Input          :  SW_I2C_Typedef *SW_I2C  操作指针
* Output         :  None
* Return         :  成功返回1 失败返回0
*******************************************************************************/
unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C)
{

    // 先低后高产生停止信号
    SW_I2C->SDA_Low();
    SW_I2C->Dealy();
    if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
    {
        return 0;
    }

    SW_I2C->SDA_High();
    SW_I2C->Dealy();

    return 1;
    
}// End of unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           陆超@2016-12-26
* Function Name  :  SW_I2C_Transfer
* Description    :  I2C发送数据
* Input          :  SW_I2C_Typedef *SW_I2C  操作指针
*                   unsigned char Chip_Addr 芯片地址
*                   unsigned char  *Data    数据指针
*                   unsigned short Data_Len 数据长度
*                   unsigned char Stop_Condition    置一时发送停止信号
* Output         :  None
* Return         :  成功返回1 失败返回0
*******************************************************************************/
unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition)
{
    unsigned char Transfer_Succeeded = 1;

    Transfer_Succeeded &= SW_I2C_Start_Condition(SW_I2C);
    Transfer_Succeeded &= SW_IIC_Write_Byte(SW_I2C, Chip_Addr);

    // 长度保护
    if (Data_Len == 0)
    {
        return 0;
    }
    if (Chip_Addr & 0x01)
    {
        /* Transfer direction is from Slave to Master */
        while (Data_Len-- && Transfer_Succeeded)
        {
            // 最后一个字节发送NO ACK
            if (Data_Len == 0)
            {
                Transfer_Succeeded &= SW_IIC_Read_Byte(SW_I2C, Data, SW_I2C_DONT_SEND_ACK);
            }
            else
            {
                Transfer_Succeeded &= SW_IIC_Read_Byte(SW_I2C, Data, SW_I2C_SEND_ACK);
            }
            Data++;
        }
    }
    else
    {
        // 发送数据
        while (Data_Len-- && Transfer_Succeeded)
        {
            Transfer_Succeeded &= SW_IIC_Write_Byte(SW_I2C, *Data);
            Data++;
        }
    }

    // 有停止信号或者发送失败
    if (Stop_Condition || (Transfer_Succeeded == 0))
    {
        Transfer_Succeeded &= SW_I2C_Stop_Condition(SW_I2C);
    }

    return Transfer_Succeeded;
    
}// End of unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition)

/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/






