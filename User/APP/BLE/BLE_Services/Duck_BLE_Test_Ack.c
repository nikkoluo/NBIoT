/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Test_Ack.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/10/2017
* Description        :  测试服务应答
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Test_Ack.h"
#include "LCD_Battery.h"
#include "LCD_Temp_Humi.h"
#include "LCD_BT.h"
#include "LCD_BU9795AF.h"
#include "Duck_BLE_Private_Service.h"
#include "Duck_Storage_Token.h"
#include "Hall.h"
#include <stdlib.h>
#include <string.h>


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen);                  // Duckps服务应答处理
void Duck_BLE_App_Ack_Handler(u8 * p_data, u16 usLen);                 // Duck测试数据
void Duck_App_Ack(u8 *ucCMD, u8* ucData, u16 usLen);                   // 应答
void Duck_BLE_CMD_Table_Handler(u8 * p_data);
u8 Duck_BLE_Test_LCD_Prepare(void);                                     // 准备测试显示数据

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-03-10
* Function Name  :  Duck_BLE_PS_Ack_Handler
* Description    :  Duck测试数据处理
* Input          :  u8* p_data          接收数据指针
*                   u16 usLen           数据长度
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen)
{

    app_trace_log("    收到消息!\r\n");

    // Duck测试命令
    if (p_data[0] == 'C' && p_data[1] == 'G')
    {
        Duck_BLE_App_Ack_Handler(&p_data[2], usLen - 2);
    }
    else
    {
        Duck_BLE_CMD_Table_Handler(p_data);   
    }
    
}// End of void Duck_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen)



/*******************************************************************************
*                           陆超@2017-03-10
* Function Name  :  Duck_BLE_App_Ack_Handler
* Description    :  Duck测试数据处理
* Input          :  u8* p_data          接收数据指针
*                   u16 usLen           数据长度
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_App_Ack_Handler(u8 * p_data, u16 usLen)
{
    u16 usCMD;
    u8 ucBuffer[8];
    u8 ucLen = 0;


    // 提取命令码
    usCMD  = (p_data[0] << 8) + p_data[1];
    usLen -= 2;

    switch(usCMD)
    {
        // 段码屏
        case PS_CMD_LCD_TEST:
        {
            if (p_data[2] == 0x04)
            {
                Test.LCD_Mode = 1;
            }
            else if (p_data[2] == 0x05)
            {
                Test.LCD_Mode = 0;

                // 重新显示LOGO
                LCD_BT_Update_Signal(1);
            }

            // 返回值
            ucLen             = 0;
            ucBuffer[ucLen++] = 1;
            
        }break;

        // 霍尔
        case PS_CMD_HALL_TEST:
        {
            // 更新hall
            Hall_Update();
            
            // 返回值
            ucLen             = 0;
            ucBuffer[ucLen++] = Hall.Magnet_Near;
            
        }break;

        // 获取token
        case PS_CMD_GET_TOKEN:
        {
            // 获取token
            memcpy(ucBuffer, MIOT_Adv.Token, TOKEN_FLASH_SIZE);

            // 返回值
            ucLen = TOKEN_FLASH_SIZE;
            
        }break;

        // 设置token
        case PS_CMD_SET_TOKEN:
        {
            // 设置
            if (usLen == TOKEN_FLASH_SIZE)
            {
                ucBuffer[0] = Token_Save(&p_data[2]);

                // 刷新token
                Get_Token();
            }
            else
            {
                ucBuffer[0] = 0;
            }

            // 返回值
            ucLen = 1;
            
        }break;

        // reboot
        case PS_CMD_REBOOT:
        {
            
            NVIC_SystemReset();
            
        }break;
        
        default:
        break;
    }

    // 应答
    Duck_App_Ack(p_data, ucBuffer, ucLen);
    
    
}// End of void Duck_BLE_App_Ack_Handler(u8 * p_data, u16 usLen)

/*******************************************************************************
*                           陆超@2017-03-13
* Function Name  :  Duck_BLE_Test_LCD_Prepare
* Description    :  准备测试显示数据
* Input          :  None
* Output         :  None
* Return         :  1 成功 0 失败
*******************************************************************************/
u8 Duck_BLE_Test_LCD_Prepare(void)
{
    static u16 usTemp = 0;
    static u8 i = 0;
    static u8 ucBat_Per = 10;

    // 控制循环周期
    i++;
    if (i < 10)
    {
        return 0;
    }
    else
    {
        i = 0;
    }
    

    // 虚拟温度数据
    usTemp += 111;
    if (usTemp > 999)
    {
        usTemp = 0;   
    }
    Sensor.sTemp  = usTemp;
    Sensor.usHumi = usTemp;
    LCD_Temp_Humi_Update_Signal();

    // 准备BT logo
    LCD_BT_Update_Signal(usTemp & 0x01);

    // 电量数据
    ucBat_Per += 20;
    if (ucBat_Per > 100)
    {
        ucBat_Per = 10;    
    }
    Sensor.Bat_Percent = ucBat_Per;
    LCD_Bat_Update_Signal();

    return 1;
    
}// End of u8 Duck_BLE_Test_LCD_Prepare(void)

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
void Duck_App_Ack(u8 *ucCMD, u8* ucData, u16 usLen)
{
    u8 Buffer[32];
    u8 Buffer_Len = 0;
    u32 Err_Code;

    // 监听
    if (Duck_BLE_Service.Message_Listening_En != 1)
    {
        app_trace_log("    Message Service 未开启!\r\n");
        return;
    }

    // 包头
    Buffer[Buffer_Len++] = 'C';
    Buffer[Buffer_Len++] = 'G';

    // 2字节命令码
    memcpy(&Buffer[Buffer_Len], ucCMD, 2);
    Buffer_Len += 2;

    // 数据实体
    if (usLen)
    {
        memcpy(&Buffer[Buffer_Len], ucData, usLen);
    }
    Buffer_Len += usLen;
    app_trace_log("    ack!\r\n");
    Err_Code = Duck_BLE_String_Send(&Duck_BLE_Service, Duck_BLE_Service.Message_Handle.value_handle, Buffer, Buffer_Len);
    if ((Err_Code != NRF_SUCCESS))
    {
        APP_ERROR_HANDLER(Err_Code);
    }
    
//app_trace_log("    Message Service 回复\r\n");

}// End of void Duck_App_Ack(u8 *ucCMD, u8* ucData, u16 usLen)

/*******************************************************************************
*                           陆超@2017-03-15
* Function Name  :  Duck_BLE_CMD_Table_Handler
* Description    :  Duck测试数据处理
* Input          :  u8* p_data          接收数据指针
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_CMD_Table_Handler(u8 * p_data)
{
    u32 Err_Code;
    const char CMD_Table_1[] = {0x77, 0x68, 0x6F, 0x20, 0x61, 0x72, 0x65, 0x20, 0x79, 0x6F, 0x75};
    const char CMD_Table_2[] = {0x49, 0x27, 0x6D, 0x20, 0x44, 0x75, 0x63, 0x6B, 0x21};
    const char CMD_Table_3[] = {0x4C, 0x65, 0x6F, 0x20, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x20, 0x6D, 0x65, 0x21};

    if (memcmp(p_data, CMD_Table_1, strlen(CMD_Table_1)) == 0)
    {
        Err_Code = Duck_BLE_String_Send(&Duck_BLE_Service, Duck_BLE_Service.Message_Handle.value_handle, (u8 *)CMD_Table_2, strlen(CMD_Table_2));
        Err_Code = Duck_BLE_String_Send(&Duck_BLE_Service, Duck_BLE_Service.Message_Handle.value_handle, (u8 *)CMD_Table_3, strlen(CMD_Table_3));
        if ((Err_Code != NRF_SUCCESS))
        {
            APP_ERROR_HANDLER(Err_Code);
        }    
    }

}// End of void Duck_BLE_CMD_Table_Handler(u8 * p_data)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




