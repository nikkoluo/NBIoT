/******************** (C) COPYRIGHT 2015 陆超 **********************************
* File Name          :  EEPROM.c
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROM应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "EEPROM.h"
#include "nrf_gpio.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void EEPROM_Task_Handle(void *p_arg);                                   // EEPROM任务
void EEPROM_Task_Create(void);                                          // 创建EEPROM任务
u8 EEPROM_Write_Data(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);	// 写数据
u16 EEPROM_Read_Data(u16 usRead_Addr, u8* pBuffer);           			// 读数据

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  EEPROM_Task_Create
* Description    :  创建EEPROM任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void EEPROM_Task_Create(void)
{
//    u32 err_code = NRF_SUCCESS;

//    // 初始化变量和IO
//    EEPROM_Variable_Init();
//    EEPROM_Port_Init();
//    
//    // 配置参数 周期模式运行
//    EEPROM_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
//    EEPROM_Task.Timeout_handler = EEPROM_Task_Handle;
//    EEPROM_Task.Period          = TASK_TVOC_PERIOD;

//    err_code |= app_timer_create(&EEPROM_Task.p_ID,
//                                 EEPROM_Task.Run_Mode,
//                                 EEPROM_Task.Timeout_handler);
//    // 芯片初始化
//    err_code |= EEPROM_Chip_Init();

//    if (err_code != NRF_SUCCESS)
//    {
//        app_trace_log("EEPROM芯片初始化失败!\r\n");    
//    }
//    else
//    {
//        err_code |= Task_Timer_Start(&EEPROM_Task, NULL);
//        if (err_code != NRF_SUCCESS)
//        {
//            app_trace_log("Task EEPROM create failed!\r\n");    
//        }
//    }


}// End of void EEPROM_Task_Create(void)

/*******************************************************************************
*                           陆超@2017-04-19
* Function Name  :  EEPROM_Task_Handle
* Description    :  EEPROM任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void EEPROM_Task_Handle(void *p_arg)
{


}// End of void EEPROM_Task_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-04-22
* Function Name  :  EEPROM_Write_Data
* Description    :  EEPROM写数据
* Input          :  u16 usWrite_Addr    要写的地址
*                   u8* pBuffer         缓存指针
*                   u16 usWrite_Len     写入长度 
* Output         :  None
* Return         :  1成功 0失败
*******************************************************************************/
u8 EEPROM_Write_Data(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
	u16 usADD = 0;
	u32 uiLen = 0;
	u16 i;
	u8 Result = 1;
	u8 *Write_Buffer;

	Write_Buffer = malloc(usWrite_Len + 4);

	// 长度地址
	Write_Buffer[uiLen++] = (usWrite_Len >> 8) & 0xFF;
	Write_Buffer[uiLen++] = (usWrite_Len >> 0) & 0xFF;

	// 数据实体
	memcpy(&Write_Buffer[uiLen], pBuffer, usWrite_Len);
	uiLen += usWrite_Len;

	// 计算累加
	usADD = 0;
	for (i = 0; i < uiLen; i++)
	{
		usADD += Write_Buffer[i];	
	}
	Write_Buffer[uiLen++] = (usADD >> 8) & 0xFF;
	Write_Buffer[uiLen++] = (usADD >> 0) & 0xFF;

	// 存 长度 数据 校验
	Result = EEPROM_Write_Buffer(usWrite_Addr, Write_Buffer, uiLen);


	free(Write_Buffer);
	return (Result);

}// ENd of u8 EEPROM_Write_Data(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/*******************************************************************************
*                           陆超@2017-04-22
* Function Name  :  EEPROM_Write_Buffer
* Description    :  EEPROM写数据
* Input          :  u16 usRead_Addr    	要读取的地址
*                   u8* pBuffer         缓存指针
* Output         :  None
* Return         :  成功返回读取长度 0失败
*******************************************************************************/
u16 EEPROM_Read_Data(u16 usRead_Addr, u8* pBuffer)
{
	u16 usADD = 0;
	u8 Buffer[4];
	u16 i;
	u16 usReadLen = 0;

	// 读取长度
	EEPROM_Read_Buffer(usRead_Addr, Buffer, 2);
	usRead_Addr += 2;

	// 长度
	usReadLen = (Buffer[0] << 8) + Buffer[1];
    
    if (usReadLen > EEPROM_CHIP_SIZE)
    {
        return 0;
    }

	// 读取数据和累加
	EEPROM_Read_Buffer(usRead_Addr, pBuffer, usReadLen);
	EEPROM_Read_Buffer(usRead_Addr + usReadLen, &Buffer[2], 2);
	
	// 计算累加
	usADD += Buffer[0];
	usADD += Buffer[1];
	for (i = 0; i < usReadLen; i++)
	{
		usADD += pBuffer[i];	
	}

	// 是否校验失败
	if (usADD != ((Buffer[2] << 8) + Buffer[3])) 
	{
		usReadLen = 0;
	}


	return (usReadLen);

}// End of u16 EEPROM_Read_Data(u16 usRead_Addr, u8* pBuffer)


/******************* (C) COPYRIGHT 2015 陆超 **************END OF FILE*********/




