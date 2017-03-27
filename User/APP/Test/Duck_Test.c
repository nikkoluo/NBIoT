/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_Test.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/08/2017
* Description        :  测试程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_Test.h"
#include "Duck_Storage_Token.h"
#include "Battery.h"
#include "Duck_Storage_MAC.h"
#include "Debug.h"
#include "WDT.h"
#include "Temp_Humi.h"
#include "Hall.h"
#include "Temp_Humi_SHT30.h"
#include <string.h>
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_Test_Handler(u8* ucData, u16 usLen);                          // 测试数据处理
void Duck_Test_Ack(u8 *ucCMD, u8* ucData, u16 usLen);                   // 命令应答
void Duck_CMD_Test_Handler(void);                                       // 测试命令处理
void Duck_CMD_MAC_Handler(u8 *ucMAC);                                   // 测试写mac命令处理

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Duck_Test_Handler
* Description    :  测试数据处理
* Input          :  u8* ucData  待处理数据
*                   u16 usLen   数据长度
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_Test_Handler(u8* ucData, u16 usLen)
{
    u16 usAdd_Sun = 0;
    u8 i;
    usLen -= 2;
    u8 ucCMD[16];
    u8 ucCMD_Len = 0;
    u8 ucBuffer[16];

    // 喂狗
    WDT_Feed();
    
    // 累加
    for (i = 0; i < usLen; i++)
    {
        usAdd_Sun += ucData[i];
    }

    //　累加校验
    if ((ucData[usLen] << 8) + ucData[usLen + 1] != usAdd_Sun)
    {
        app_trace_log("测试命令累加校验错误!\r\n");
        return;
    }

    // 提取命令码
    ucCMD_Len = ucData[2];
    memcpy(ucCMD, &ucData[3], ucCMD_Len);

    // 开始测试  
    if (memcmp(ucCMD, TEST_CMD_START, ucCMD_Len) == 0)
    {
        // 应答
        Duck_Test_Ack(TEST_CMD_START, "Success", strlen("Success"));    
    }

    // 写mac
    else if (memcmp(ucCMD, TEST_CMD_MAC, ucCMD_Len) == 0)
    {
        // 提取mac
        memcpy(ucBuffer, &ucData[3 + 1 + ucCMD_Len], MAC_FLASH_SIZE);
        
        Duck_CMD_MAC_Handler(ucBuffer);
        
    }
    // 删除mac
    else if (memcmp(ucCMD, TEST_CMD_DELETE_MAC, ucCMD_Len) == 0)
    {
        // 写成功
        if (MAC_Delete())
        {
            Duck_Test_Ack(TEST_CMD_DELETE_MAC, "Success", strlen("Success"));  
        }
        else
        {
            // 失败
            Duck_Test_Ack(TEST_CMD_DELETE_MAC, "Error", strlen("Error"));  
        }
        
    }
    // 写token
    else if (memcmp(ucCMD, TEST_CMD_TOKEN, ucCMD_Len) == 0)
    {
        // 提取token
        memcpy(ucBuffer, &ucData[3 + 1 + ucCMD_Len], TOKEN_FLASH_SIZE);

        // 写成功
        if (Token_Save(ucBuffer))
        {
            Duck_Test_Ack(TEST_CMD_TOKEN, "Success", strlen("Success"));  
        }
        else
        {
            // 失败
            Duck_Test_Ack(TEST_CMD_TOKEN, "Error", strlen("Error"));  
        }
        
    }
    // 正式测试
    else if (memcmp(ucCMD, TEST_CMD_TEST, ucCMD_Len) == 0)
    {

        Duck_CMD_Test_Handler();
    }
    
    
}// End of void Duck_Test_Handler(u8* ucData, u16 usLen)

/*******************************************************************************
*                           陆超@2017-03-09
* Function Name  :  Duck_CMD_MAC_Handler
* Description    :  测试写mac命令处理
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_CMD_MAC_Handler(u8 *ucMAC)
{
    // 无mac
    if (System_Err.MAC == 1)
    {

        // 写成功
        if (MAC_Save(ucMAC))
        {
            Duck_Test_Ack(TEST_CMD_MAC, "Success", strlen("Success"));  
        }
        else
        {
            // 失败
            Duck_Test_Ack(TEST_CMD_MAC, "Error", strlen("Error"));  
        }
    }
    else
    {
        // 返回mac锁定
        Duck_Test_Ack(TEST_CMD_MAC, "Lock", strlen("Lock"));  
    }
    
}// End of void Duck_CMD_MAC_Handler(u8 *ucMAC)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Duck_CMD_Test_Handler
* Description    :  测试命令处理
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_CMD_Test_Handler(void)
{

    u8 *Buffer;
    u8 Buffer_Len = 0;
    float fTemp, fHumi;
    s16 Temp, Humi;
    
    Buffer = malloc(128);
    
    // 获取电压
    Battery_Handle();

    // 获取霍尔状态
    Hall_Update();

    // 获取温度
    if (SHT3x_Get_Temp_Humi(&fTemp, &fHumi))
    {
        fTemp = (fTemp + 0.05) * 10;
        Temp  = (s16)fTemp;
        fHumi = (fHumi + 0.05) * 10;
        Humi  = (s16)fHumi;
        Buffer_Len = sprintf((char *)Buffer, "Temp = %d.%01d, Humi = %d.%01d, ", Temp / 10, abs(Temp) % 10, Humi / 10, Humi % 10);    
    }
    else
    {
        Buffer_Len = sprintf((char *)Buffer, "Temp = --, Humi = --, ");      
    }

    // 电压霍尔数据
    Buffer_Len += sprintf((char *)&Buffer[Buffer_Len], "Vol = %dmV, Hall = %d", Battery_ADC.Vol_mv, Hall.Magnet_Near); 

    // ack
    Duck_Test_Ack(TEST_CMD_TEST, Buffer, Buffer_Len);
    
    // 释放缓存
    free(Buffer);
    
}// End of void Duck_CMD_Test_Handler(void)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Duck_Test_Ack
* Description    :  测试命令应答
* Input          :  u8 *ucCMD   待回复命令
*                   u8* ucData  待回复数据
*                   u16 usLen   数据长度
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_Test_Ack(u8 *ucCMD, u8* ucData, u16 usLen)
{
    u8 Buffer[128];
    u8 Buffer_Len = 0;
    u8 i;
    u16 usAdd_Sun = 0;

    // 包头
    Buffer[Buffer_Len++] = 'C';
    Buffer[Buffer_Len++] = 'G';

    // 命令码
    Buffer[Buffer_Len++] = strlen((const char *)ucCMD);
    memcpy(&Buffer[Buffer_Len], ucCMD, Buffer[Buffer_Len - 1]);
    Buffer_Len += Buffer[Buffer_Len - 1];

    // 数据实体
    Buffer[Buffer_Len++] = usLen;
    if (usLen)
    {
        memcpy(&Buffer[Buffer_Len], ucData, Buffer[Buffer_Len - 1]);
    }
    Buffer_Len += Buffer[Buffer_Len - 1];

    // 累加
    for (i = 0; i < Buffer_Len; i++)
    {
        usAdd_Sun += Buffer[i];
    }
    Buffer[Buffer_Len++] = (usAdd_Sun >> 8) & 0xFF;
    Buffer[Buffer_Len++] = (usAdd_Sun >> 0) & 0xFF;


    // 延时 清空数据
    

    // 发送数据
    Debug_Send(Buffer, Buffer_Len);

}// End of void Duck_Test_Ack(u8 *ucCMD, u8* ucData, u16 usLen)

/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/




