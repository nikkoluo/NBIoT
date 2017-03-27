/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_Storage.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  mac地址处理
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_Storage.h"
#include "nrf_soc.h"
#include "Communal_Flash.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Duck_Storage_Init(void);                                           // Duck_Storage初始化
void Duck_Storage_Callback(pstorage_handle_t *  handle, u8   OP_Code,
                           u32  Err_Code, u8*  pData, u32  uiData_Len); // 操作flash回调
                                               
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-03-09
* Function Name  :  Duck_Storage_Init
* Description    :  MAC flash初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_Storage_Init(void)
{


}// End of void Duck_Storage_Init(void)

/*******************************************************************************
*                           陆超@2017-03-09
* Function Name  :  Duck_Storage_Callback
* Description    :  flash操作回调
* Input          :  u32  Err_Code   操作结果
*                   u8   OP_Code    命令码(错误原因) 
*                   u8*  pData      要写入的值
*                   u32  Data_Len   数据长度
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_Storage_Callback(pstorage_handle_t *  handle, u8   OP_Code,
                           u32  Err_Code, u8*  pData, u32  uiData_Len)
{
    if (Err_Code != NRF_SUCCESS)
    {
        // Load operation failed.
        app_trace_log("[E]: flash operation error, opcode:%d Err_Code:%d\r\n", OP_Code, Err_Code);

        // 释放flash占用
        Flash_Used = 0;

        return ;
    }
    
//    app_trace_log("MAC_Flash_Callback!\r\n");


    switch (OP_Code) 
    {
        case PSTORAGE_LOAD_OP_CODE:
        {
//            app_trace_log("MAC地址读取成功!\r\n");
           
        }break;

        case PSTORAGE_STORE_OP_CODE:
        {
          
            
        }break;

        case PSTORAGE_UPDATE_OP_CODE:
        {
//            app_trace_log("MAC地址保存成功!\r\n");
               
        }break;

        case PSTORAGE_CLEAR_OP_CODE:
        {
            
            
        }break;

        default:
            break;
            
    }

    // 释放flash占用
    Flash_Used = 0;
    
}// End of static void Duck_Storage_Callback

/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/










