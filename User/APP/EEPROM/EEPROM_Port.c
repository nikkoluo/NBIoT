/******************** (C) COPYRIGHT 2015 陆超 **********************************
* File Name          :  EEPROM_Port.c
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROM驱动程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "EEPROM_Port.h"
#include "nrf_gpio.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_delay.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);    // EEPROM读取数据
u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);   // 写页命令
u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len); // EEPROM写数据
u8 EEPROM_Chip_Init(void);                                              // 芯片初始化
void EEPROM_Variable_Init(void);                                        // EEPROM变量初始化
u8   EEPROM_Port_Init(void);                                            // EEPROM端口初始化  

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2015-04-26
* Function Name  :  EEPROM_Read_Buffer
* Description    :  EEPROM读数据
* Input          :  u16 usRead_Addr 要读取的地址
*                   u8* pBuffer     缓存指针
*                   u16 usRead_Len  读取长度
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)
{
    u8 Transfer_Succeeded = 1;
    u8 ucRead_Addr[2];
    
    if(usRead_Len == 0)
    {
        return 1;
    }
    
    // 准备地址数据
    ucRead_Addr[0] = (usRead_Addr >> 8) & 0xFF;
    ucRead_Addr[1] = (usRead_Addr >> 0) & 0xFF;
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, EEPROM_WRITE_ADDR, ucRead_Addr, 2, SW_I2C_DONT_SEND_STOP);
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, EEPROM_READ_ADDR, pBuffer, usRead_Len, SW_I2C_NEED_SEND_STOP);

    if (Transfer_Succeeded == 0)
    {
        System_Err.EEPROM = 1;
  
    }
    else
    {
        System_Err.EEPROM = 0;
    }
    return Transfer_Succeeded;
    
}// End of u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)

/*******************************************************************************
*                           陆超@2015-04-26
* Function Name  :  EEPROM_Write_Page
* Description    :  EEPROM写页数据
* Input          :  u16 usWrite_Addr    要读取的地址
*                   u8* pBuffer         缓存指针
*                   u16 usWrite_Len     写入长度 < EEPROM_PAGE_SIZE;
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
    u8 Transfer_Succeeded = 1;
    u8 ucWrite_Addr[2];

    // 长度保护
    if(usWrite_Len == 0)
    {
        return 1;
    }

    // 准备地址数据
    ucWrite_Addr[0] = (usWrite_Addr >> 8) & 0xFF;
    ucWrite_Addr[1] = (usWrite_Addr >> 0) & 0xFF;

    // 发送写命令
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, EEPROM_WRITE_ADDR, ucWrite_Addr, 2, SW_I2C_DONT_SEND_STOP);

    // 写数据
    while (usWrite_Len-- && Transfer_Succeeded)
    {
        Transfer_Succeeded &= SW_IIC_Write_Byte(&Communal_IIC_2, *pBuffer);
        pBuffer++;
    }

    // 发送停止命令
    Transfer_Succeeded &= SW_I2C_Stop_Condition(&Communal_IIC_2);
    
  
    // 延时 保证写命令完成
    nrf_delay_ms(EEPROM_WRITE_PAGE_TIME);

    return Transfer_Succeeded;

}// End of u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/*******************************************************************************
*                           陆超@2015-04-26
* Function Name  :  EEPROM_Write_Buffer
* Description    :  EEPROM写数据
* Input          :  u16 usWrite_Addr    要读取的地址
*                   u8* pBuffer         缓存指针
*                   u16 usWrite_Len     写入长度 
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
    u8 Transfer_Succeeded = 1;  
    u16 usTemp;

    // 声明读写指针和地址
    u8 Read_Buffer[36];
    u8 *Write_Buffer = pBuffer;
    u16 usRead_Addr  = usWrite_Addr;
    u16 usRead_Len   = usWrite_Len;

    // 长度保护
    if (usWrite_Len == 0)
    {
        return 1;
    }
    else 
    {
        // 长度越界
        if (usWrite_Addr + usWrite_Len > EEPROM_CHIP_SIZE)
        {
            return 0;
        }
    }
   
    while(usWrite_Len && Transfer_Succeeded)
    {

        // 分页写入数据
        usTemp = usWrite_Addr % EEPROM_PAGE_SIZE;
        if (usTemp + usWrite_Len < EEPROM_PAGE_SIZE)
        {
            Transfer_Succeeded &= EEPROM_Write_Page(usWrite_Addr, pBuffer, usWrite_Len);
            usWrite_Len = 0;
        }
        else
        {
            // 计算写入长度
            usTemp = EEPROM_PAGE_SIZE - usTemp; 
            Transfer_Succeeded &= EEPROM_Write_Page(usWrite_Addr, pBuffer, usTemp);  
            usWrite_Addr += usTemp;
            pBuffer      += usTemp;
            usWrite_Len  -= usTemp;
        }
    }
   
    // 比较写入数据
    if (Transfer_Succeeded)
    {
        if (Read_Buffer)
        {
            // 读取写入数据并比较
            Transfer_Succeeded &= EEPROM_Read_Buffer(usRead_Addr, Read_Buffer, usRead_Len);
               
            if (Transfer_Succeeded)
            {
                for (usTemp = 0; usTemp < usRead_Len; usTemp++)
                {
                    if (Read_Buffer[usTemp] != Write_Buffer[usTemp])
                    {
                        Transfer_Succeeded = 0;
                        break;
                    }
                }
            }
        }
        else
        {
            Transfer_Succeeded = 0;  
        }  

          
    }

    if (Transfer_Succeeded == 0)
    {
        System_Err.EEPROM = 1;
        app_trace_log("EEPROM Write Err!");   
    }
    else
    {
        System_Err.EEPROM = 0;
    }
    
    return Transfer_Succeeded;
    
}// End of u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/*******************************************************************************
*                           陆超@2015-05-05
* Function Name  :  EEPROM_Chip_Init
* Description    :  EEPROM芯片初始化
* Input          :  None
* Output         :  None
* Return         :  返回1成功 返回0失败
*******************************************************************************/
u8 EEPROM_Chip_Init(void)
{

    u8 ucResult = 1;

    // 变量初始化
    EEPROM_Variable_Init();

    // 管脚初始化
    ucResult &= EEPROM_Port_Init();

        
// 无EEPROM
#ifdef DONT_USE_EEPROM


    
#else

    const u8 EEPROM_Test_Data = 0x55;
    
    // 管脚初始化成功
    if (ucResult)
    {
        ucResult &= EEPROM_Write_Buffer(EEPROM_TEST_ADDR, (u8*)&EEPROM_Test_Data, 1);      
    }
    

#endif


    System_Err.EEPROM = ucResult ^ 0x01;
    
    if (System_Err.EEPROM == 0)
    {
        app_trace_log("EEPROM Init Success!\r\n");
    }

    return ucResult;
    
}// End of u8 EEPROM_Chip_Init(void)

/*******************************************************************************
*                           陆超@2014-09-04
* Function Name  :  EEPROM_Variable_Init
* Description    :  EEPROM变量初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void EEPROM_Variable_Init(void)
{


    
}// End of void EEPROM_Variable_Init(void)

/*******************************************************************************
*                           陆超@2015-04-23
* Function Name  :  EEPROM_Port_Init
* Description    :  EEPROM端口初始化
* Input          :  None
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 EEPROM_Port_Init(void)
{
    u8 Transfer_Succeeded = 1; 

    
    return (Transfer_Succeeded);
       
}// End of u8  EEPROM_Port_Init(void)

/******************* (C) COPYRIGHT 2015 陆超 **************END OF FILE*********/

