/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Mi_Bond.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/15/2017
* Description        :  Duck_BLE 绑定
*                       绑定成功 延时5s
*                       绑定失败 延时30s超时退出
*                       长按时长不计算入超时时间
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Mi_Bond.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "pstorage.h"
#include "app_trace.h"
#include "ble_mis.h"
#include "mibeacon.h"
#include "LCD_BT.h"
#include "Communal_Flash.h"
#include <string.h>

/* Private variables ---------------------------------------------------------*/
static pstorage_handle_t Mi_Bond_Flash_Handler;                         // 小米连接flash服务

/* Private function prototypes -----------------------------------------------*/
void Mi_Bond_Start(void);                                               // 启动绑定
void Mi_Bond_Stop(void);                                                // 结束绑定
void Duck_BLE_Mi_Services_Init(void);                                   // 小米服务初始化
void Mi_Bond_Status_Handler(ble_mis_evt_type_t evt);                    // 绑定状态处理
void Mi_Bond_Timeout_Check(void);                                       // 绑定超时出判断
static void Mi_Bond_Flash_Init(void);                                   // miflash初始化
static void Mi_Bond_Flash_Callback(pstorage_handle_t *  handle, u8   OP_Code, u32  Err_Code, u8*  pData, u32 uiData_Len); // 回调
int Mi_Bond_Flash_Write(u32 uiAddr, u8* pData, u16 usLen);              // 写flash
int Mi_Bond_Flash_Read(u32 uiAddr, u8* pData, u16 usLen);               // 读flash

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Mi_Bond_Status_Handler
* Description    :  mi绑定状态处理
* Input          :  ble_mis_evt_type_t evt 状态
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Status_Handler(ble_mis_evt_type_t evt)
{
    if (evt == BLE_MIS_EVT_BOND_SUCC) 
    {
        // 绑定成功 延时退出绑定状态
        Sys_Bond.Time_Left = MIOT_BOND_STOP_DELAY;
        Sys_Bond.Count++;
        app_trace_log("app bond succ\r\n");
    } 
    else 
    {

        app_trace_log("app bond fail\r\n");
  
    }
    
}// End of void Mi_Bond_Status_Handler(ble_mis_evt_type_t evt)


/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Mi_Bond_Flash_Write
* Description    :  mi绑定写flash
* Input          :  u32 uiAddr 操作基址
*                   u8* pData  要写入的数据
*                   u16 usLen  长度
* Output         :  None
* Return         :  None
*******************************************************************************/
int Mi_Bond_Flash_Write(u32 uiAddr, u8* pData, u16 usLen)
{
    u32  Err_Code;
    pstorage_handle_t *Base_Handle = (pstorage_handle_t*)uiAddr;

    // 写数据
    Err_Code = Communal_Flash_Update(Base_Handle, pData, usLen, 0);
    return Err_Code;
    
}// End of int Mi_Bond_Flash_Write(u32 uiAddr, u8* pData, u16 usLen)


/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Mi_Bond_Flash_Write
* Description    :  mi绑定写flash
* Input          :  u32 uiAddr 操作基址
*                   u8* pData  数据缓存
*                   u16 usLen  长度
* Output         :  None
* Return         :  None
*******************************************************************************/
int Mi_Bond_Flash_Read(u32 uiAddr, u8* pData, u16 usLen)
{
    u32  Err_Code;
    pstorage_handle_t *Base_Handle = (pstorage_handle_t*)uiAddr;

    // 读取
    Err_Code = Communal_Flash_Load(pData, Base_Handle, usLen, 0);
    return Err_Code;
    
}// End of int Mi_Bond_Flash_Read(u32 uiAddr, u8* pData, u16 usLen)

/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Mi_Bond_Flash_Callback
* Description    :  mi绑定flash回调
* Input          :  u32  Err_Code   操作结果
*                   u8   OP_Code    命令码(错误原因) 
*                   u8*  pData      要写入的值
*                   u32  Data_Len   数据长度
* Output         :  None
* Return         :  None
*******************************************************************************/
static void Mi_Bond_Flash_Callback(pstorage_handle_t *  handle,
                                   u8   OP_Code,
                                   u32  Err_Code,
                                   u8*  pData,
                                   u32  uiData_Len)
{
    if (Err_Code != NRF_SUCCESS)
    {
        // Load operation failed.
        app_trace_log("[E]: flash operation error, opcode:%d\r\n", OP_Code);
        return ;
    }
    
    app_trace_log("Mi_Bond_Flash_Callback!\r\n");


    switch (OP_Code) 
    {
        case PSTORAGE_LOAD_OP_CODE:
        {
        
            // Load operation successful.
            app_trace_log("[D]: load succ, len = %d\r\n", uiData_Len);
            // memcpy(mis_token, p_data, MIIO_BLE_TOKEN_LEN);
            //memcpy(mis_sn, p_data + MIIO_BLE_TOKEN_LEN, MIIO_BLE_SN_LEN);
            //memcpy(mis_beaconKey, p_data + MIIO_BLE_TOKEN_LEN + MIIO_BLE_SN_LEN, MIIO_BLE_BEACONKEY_LEN);
            //LOG_DEBUG("retrive token, %02x %02x\r\n", mis_token[10], mis_token[11]);
            // Source memory can now be reused or freed.

        }break;

        case PSTORAGE_STORE_OP_CODE:
        {
            app_trace_log("[D]: store succ. len = %d\r\n", uiData_Len);
            
        }break;

        case PSTORAGE_UPDATE_OP_CODE:
        {
            app_trace_log("[D]: update succ. len = %d\r\n", uiData_Len);
            
        }break;

        case PSTORAGE_CLEAR_OP_CODE:
        {
            app_trace_log("[D]: clear succ. len = %d\r\n", uiData_Len);
            
        }break;

        default:
            break;
            
    }

    // 释放flash占用
    Flash_Used = 0;
    
}// End of static void Mi_Bond_Flash_Callback

/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Mi_Bond_Flash_Init
* Description    :  mi服务flash初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
static void Mi_Bond_Flash_Init(void)
{
    u32 Err_Code;    
    pstorage_module_param_t param;
    
    // Register
    param.block_size  = MISERVICE_PSM_SIZE;
    param.block_count = MISERVICE_PSM_BLOCK;
    param.cb          = Mi_Bond_Flash_Callback;

    Err_Code = pstorage_register(&param, &Mi_Bond_Flash_Handler);
    if (Err_Code == NRF_SUCCESS) 
    {
        app_trace_log("[D]: miio ble flash register succ\r\n");
    } 
    else 
    {
        app_trace_log("[E]: miio ble flash register fail\r\n");
    }
    
}// End of static void Mi_Bond_Flash_Init(void)

/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Duck_BLE_Mi_Services_Init
* Description    :  绑定服务初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Mi_Services_Init(void)
{
    uint32_t       Err_Code;
    ble_mis_init_t Mi_Bond_Init;
    char ver[MIIO_BLE_VER_LEN] = {"1.0.1_1"};

    // Init FLASH
    Mi_Bond_Flash_Init();

    // Init Mi Service
    Mi_Bond_Init.productId     = MIOT_PRODUCT_ID;
    Mi_Bond_Init.relation      = MIIO_BLE_DEV_RELATION_WEAK;
    Mi_Bond_Init.evt_handler   = (ble_mis_evt_handler_t)Mi_Bond_Status_Handler;

    Mi_Bond_Init.flashBaseAddr = (uint32_t)&Mi_Bond_Flash_Handler;
    Mi_Bond_Init.flashWriteFn  = Mi_Bond_Flash_Write;
    Mi_Bond_Init.flashReadFn   = Mi_Bond_Flash_Read;
    memcpy(Mi_Bond_Init.version, ver, MIIO_BLE_VER_LEN); 
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&Mi_Bond_Init.mis_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&Mi_Bond_Init.mis_attr_md.write_perm);

    Err_Code = ble_mis_init(&Mi_Bond_Init);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void Duck_BLE_Mi_Services_Init(void)

/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Mi_Bond_Start
* Description    :  启动绑定
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Start(void)
{

    // 刷新绑定时间
    Sys_Bond.Time_Left = MIOT_EVENT_ID_BOND_DURATION; 

    // 非绑定态
    if (Sys_Bond.Adv_En == 0)
    {
        // 进入绑定态
        Sys_Bond.Adv_En = 1;
        Sys_Bond.Count  = 0;

        // 准备数据
        MIOT_Adv.Frame_Control_Bit.Factory_New        = MIBEACON_ITEM_FACTORY_NEW;
        MIOT_Adv.Frame_Control_Bit.Capability_Include = 1;


        // 可连接 可加密 可绑定
        MIOT_Adv.Capability_Bit.Connectable           = 1;
        MIOT_Adv.Capability_Bit.Encrypt_Ability       = 1;
        MIOT_Adv.Capability_Bit.Bond_Ability          = MIBEACON_BOND_PREBINDING;


        // 置位LED闪烁
        Sys_Bond.Blink_Interval = 0;
        LCD_BT_Update_Blink();

        app_trace_log("---------------------开始绑定任务!\r\n");
    }
    else
    {
        app_trace_log("---------------------继续绑定任务!\r\n");    
    }

    

}// End of void Mi_Bond_Start(void)

/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Mi_Bond_Stop
* Description    :  结束绑定
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Stop(void)
{

    // 刷新绑定时间
    Sys_Bond.Time_Left = 0; 

    // 非绑定态
    Sys_Bond.Adv_En =0;


    // 取消绑定允许位
    MIOT_Adv.Frame_Control_Bit.Factory_New        = 0;
    MIOT_Adv.Frame_Control_Bit.Capability_Include = 0;

    // 重新显示LOGO
    LCD_BT_Update_Signal(1);
    
    app_trace_log("---------------------结束绑定任务!\r\n");

}// End of void Mi_Bond_Stop(void)

/*******************************************************************************
*                           陆超@2017-02-24
* Function Name  :  Mi_Bond_Timeout_Check
* Description    :  绑定超时判断
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Timeout_Check(void)
{
    // 在广播绑定
    if (Sys_Bond.Adv_En)
    {
        // 长按途中不计算超时
        if (Button.Long == 0)
        {
            if (Sys_Bond.Time_Left)
            {
                Sys_Bond.Time_Left--;   
            }
        }
        // 超时退出绑定广播
        if (Sys_Bond.Time_Left == 0)
        {
            // 结束绑定
            Mi_Bond_Stop();
            app_trace_log("超时退出绑定广播!\r\n"); 
        }


        // blink
        if (Sys_Bond.Blink_Interval == 0)
        { 
            LCD_BT_Update_Blink();
        }
    }

}// End of void Mi_Bond_Timeout_Check(void)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




