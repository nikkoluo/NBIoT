/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Private_Service.c
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/13/2017
* Description        :  私有服务应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Private_Service.h"
#include "Duck_BLE_Test_Ack.h"
#include <stdlib.h>
#include <string.h>


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_Private_Services_Init(void);                              // 私有服务初始化  
void Duck_BLE_Receive_Data_Handler(u8 * p_data, u16 length);            // Duck接收数据处理
u32 Duck_Temp_Characteristic_Add(BLE_Service_Typedef * pDuck);          // 增加温度服务
u32 Duck_Message_Characteristic_Add(BLE_Service_Typedef * pDuck);       // 增加通讯服务
u8 Duck_Temp_Humi_Encode(s16 sTemp, u16 usHumi, u8 * pBuffer);          // 温湿度数据打包
void Duck_BLE_Private_Evt(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt);   // Duck事件处理
void Duck_BLE_ON_Write(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt);      // Duck接收处理
void Duck_BLE_ON_Disconnect(BLE_Service_Typedef * pDuck);               // 断开连接
void Duck_BLE_ON_Connect(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt);    // 连接
u32 Duck_BLE_String_Send(BLE_Service_Typedef * pDuck, u16 usValue_Handle, u8 * pString, u16 usLen); // 发送数据
void Temp_BLE_Service_Update(BLE_Service_Typedef * pDuck);              // 更新温度

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-15
* Function Name  :  Duck_BLE_Receive_Data_Handler
* Description    :  Duck接收数据处理
* Input          :  u8* p_data          接收数据指针
*                   u16 length          数据长度
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Receive_Data_Handler(u8 * p_data, u16 length)
{

    app_trace_log("    收到消息!\r\n");
    
}// End of void Duck_BLE_Receive_Data_Handler(u8 * p_data, u16 length)

/*******************************************************************************
*                           陆超@2017-01-13
* Function Name  :  Duck_BLE_Private_Services_Init
* Description    :  Duck BLE 私有服务初始化    
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Private_Services_Init(void)
{
    u32             Err_Code;
    ble_uuid128_t   Duck_Base_UUID = DUCK_BASE_UUID;
    ble_uuid_t      BLE_UUID;


    // 服务参数初始化
    Duck_BLE_Service.Conn_Handle  = BLE_CONN_HANDLE_INVALID;

    

    // 增加服务UUID
    Err_Code = sd_ble_uuid_vs_add(&Duck_Base_UUID, &Duck_BLE_Service.UUID_Type);
    APP_ERROR_CHECK(Err_Code);

    // 声明UUID类型和值 
    BLE_UUID.type = Duck_BLE_Service.UUID_Type;
    BLE_UUID.uuid = BLE_UUID_DUCK;

    // 增加一个服务
    Err_Code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &BLE_UUID,
                                        &Duck_BLE_Service.Service_Handle);
                                        
    APP_ERROR_CHECK(Err_Code);
    

    // 增加发送服务
    Duck_BLE_Service.Temp_Humi_Listening_En = false;
    Err_Code = Duck_Temp_Characteristic_Add(&Duck_BLE_Service);
    APP_ERROR_CHECK(Err_Code);

    Duck_BLE_Service.Message_Listening_En = false;
    Err_Code = Duck_Message_Characteristic_Add(&Duck_BLE_Service);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void Duck_BLE_Private_Services_Init(void)


/*******************************************************************************
*                           陆超@2017-01-15
* Function Name  :  Duck_Temp_Characteristic_Add
* Description    :  增加温度发送服务
* Input          :  BLE_Service_Typedef * pDuck 服务参数
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u32 Duck_Temp_Characteristic_Add(BLE_Service_Typedef * pDuck) 
{
    // 增加所有权特征
    ble_gatts_char_md_t char_md;
    ble_gatts_char_pf_t accel_pf;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          BLE_UUID;
    ble_gatts_attr_md_t attr_md;
    u8 ucEncode[BLE_DUCK_MAX_DATA_LEN];
    static char User_Desc[] = "Temp&Humi";

    // 客户端特征值配置描述符 关于notify
    ble_gatts_attr_md_t cccd_md;
    
    memset(&cccd_md, 0, sizeof(cccd_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;
     
    
    // 设置内容格式
    memset(&accel_pf, 0, sizeof(accel_pf));
    accel_pf.format    = BLE_GATT_CPF_FORMAT_UTF8S;

    memset(&char_md, 0, sizeof(char_md));


    char_md.char_props.notify       = 1;                            // 监听权限
    char_md.char_props.read         = 0;                            // 读权限
    char_md.char_props.write        = 0;                            // 写权限
    char_md.p_char_user_desc        = (u8 *) User_Desc;             // 功能描述符
    char_md.char_user_desc_size     = strlen(User_Desc);
    char_md.char_user_desc_max_size = strlen(User_Desc);
    char_md.p_char_pf               = &accel_pf;                    // 格式
    char_md.p_user_desc_md          = NULL;
    char_md.p_cccd_md               = &cccd_md;                         // 客户端配置特征描述符权限 0x2902 查看Notify通知
    char_md.p_sccd_md               = NULL;

    // 声明类型和特征字
    BLE_UUID.type = pDuck->UUID_Type;
    BLE_UUID.uuid = DUCK_TEMP_CHARACTERISTIC;

    memset(&attr_md, 0, sizeof(attr_md));

    // 没有读写权限
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen    = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &BLE_UUID;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = Duck_Temp_Humi_Encode(Sensor.sTemp, Sensor.usHumi, ucEncode);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = BLE_DUCK_MAX_DATA_LEN;
    attr_char_value.p_value   = ucEncode;

    return sd_ble_gatts_characteristic_add(pDuck->Service_Handle,
                                           &char_md,
                                           &attr_char_value,
                                           &pDuck->Temp_Humi_Handle);
                                           
}// End of u32 Duck_Temp_Characteristic_Add(BLE_Service_Typedef * pDuck) 

/*******************************************************************************
*                           陆超@2017-03-09
* Function Name  :  Duck_Message_Characteristic_Add
* Description    :  增加通讯服务
* Input          :  BLE_Service_Typedef * pDuck 服务参数
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u32 Duck_Message_Characteristic_Add(BLE_Service_Typedef * pDuck) 
{
    // 增加所有权特征
    ble_gatts_char_md_t char_md;
//    ble_gatts_char_pf_t accel_pf;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          BLE_UUID;
    ble_gatts_attr_md_t attr_md;
    static char User_Desc[] = "Message";
    ble_gatts_attr_md_t cccd_md;
    
    memset(&cccd_md, 0, sizeof(cccd_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;
     
    // 设置内容格式
//    memset(&accel_pf, 0, sizeof(accel_pf));
//    accel_pf.format    = BLE_GATT_CPF_FORMAT_UTF8S;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.notify       = 1;                            // 监听权限
    char_md.char_props.read         = 0;                            // 读权限
    char_md.char_props.write        = 1;                            // 写权限
    char_md.p_char_user_desc        = (u8 *) User_Desc;             // 功能描述符
    char_md.char_user_desc_size     = strlen(User_Desc);
    char_md.char_user_desc_max_size = strlen(User_Desc);
    char_md.p_char_pf               = NULL;                         // 格式
    char_md.p_user_desc_md          = NULL;
    char_md.p_cccd_md               = &cccd_md;                     // 客户端配置特征描述符权限 0x2902 查看Notify通知
    char_md.p_sccd_md               = NULL;

    // 声明类型和特征字
    BLE_UUID.type = pDuck->UUID_Type;
    BLE_UUID.uuid = DUCK_MESSAGE_CHARACTERISTIC;

    memset(&attr_md, 0, sizeof(attr_md));

    // 只写不读
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen    = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &BLE_UUID;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = BLE_DUCK_MAX_DATA_LEN;

    return sd_ble_gatts_characteristic_add(pDuck->Service_Handle,
                                           &char_md,
                                           &attr_char_value,
                                           &pDuck->Message_Handle);
                                           
}// End of u32 Duck_Message_Characteristic_Add(BLE_Service_Typedef * pDuck) 

/*******************************************************************************
*                           陆超@2017-01-15
* Function Name  :  Duck_Temp_Humi_Encode
* Description    :  打包温度数据
* Input          :  s16 sData    温湿度度数据
*                   u8 * pBuffer  缓存
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u8 Duck_Temp_Humi_Encode(s16 sTemp, u16 usHumi, u8 * pBuffer)
{
    u8 ucLen = 0;

    // 16进制转ASCII
    ucLen            = sprintf((char*)pBuffer, "T=%d.%d H=%d.%d", sTemp/10 , sTemp % 10, usHumi / 10, usHumi % 10);

    // 磁铁信息
    if (Hall.Magnet_Near)
    {
        memcpy(&pBuffer[ucLen], " Near", 5);
        ucLen += 5;
    }
    else
    {
        memcpy(&pBuffer[ucLen], " Far", 4);
        ucLen += 4;
    }
    
    pBuffer[ucLen++] = 0;
    return ucLen;
    
}// End of u8 Duck_Temp_Humi_Encode(s16 sTemp, u16 usHumi, u8 * pBuffer))



/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  Duck_BLE_Private_Evt
* Description    :  Duck事件处理
* Input          :  BLE_Service_Typedef * pDuck 服务参数
*                   ble_evt_t * pBLE_Evt  BLE事件
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Private_Evt(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt)
{
    if ((pDuck == NULL) || (pBLE_Evt == NULL))
    {
        return;
    }

    switch (pBLE_Evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:

            Duck_BLE_ON_Connect(pDuck, pBLE_Evt);
            
            break;

        case BLE_GAP_EVT_DISCONNECTED:
        
            Duck_BLE_ON_Disconnect(pDuck);
            
            break;

        case BLE_GATTS_EVT_WRITE:
        
            Duck_BLE_ON_Write(pDuck, pBLE_Evt);
            
            break;
        
        default:
            // No implementation needed.
            break;
    }
    
}// End of void Duck_BLE_Private_Evt(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt)

/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  Duck_BLE_ON_Write
* Description    :  BLE_GATTS_EVT_WRITE         事件处理
* Input          :  BLE_Service_Typedef * pDuck 服务参数
*                   ble_evt_t * pBLE_Evt  BLE事件
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_ON_Write(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt)
{
    ble_gatts_evt_write_t * p_evt_write = &pBLE_Evt->evt.gatts_evt.params.write;

    // 监听通道
    if ((p_evt_write->handle == pDuck->Temp_Humi_Handle.cccd_handle))
    {
        if (ble_srv_is_notification_enabled(p_evt_write->data) && (p_evt_write->len == 2))
        {
            pDuck->Temp_Humi_Listening_En = true;
            app_trace_log("    开始监听 Duck Temp!\r\n");

        }
        else
        {
            pDuck->Temp_Humi_Listening_En = false;
            app_trace_log("    停止监听 Duck Temp!\r\n");
        }
    }
    else if ((p_evt_write->handle == pDuck->Message_Handle.cccd_handle))
    {
        if (ble_srv_is_notification_enabled(p_evt_write->data) && (p_evt_write->len == 2))
        {
            pDuck->Message_Listening_En = true;
            app_trace_log("    开始监听 Duck Message!\r\n");

        }
        else
        {
            pDuck->Message_Listening_En = false;
            app_trace_log("    停止监听 Duck Message!\r\n");
        }    
    }
    // massage接收
    else if (p_evt_write->handle == pDuck->Message_Handle.value_handle)
    {
        Duck_BLE_PS_Ack_Handler(p_evt_write->data, p_evt_write->len);
    }

    

}// End of void Duck_BLE_ON_Write(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt)

/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  Duck_BLE_ON_Disconnect
* Description    :  断开连接
* Input          :  BLE_Service_Typedef * pDuck 服务参数
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_ON_Disconnect(BLE_Service_Typedef * pDuck)
{
    pDuck->Conn_Handle            = BLE_CONN_HANDLE_INVALID;
    pDuck->Temp_Humi_Listening_En = false;
    pDuck->Message_Listening_En   = false;

}// End of void void Duck_BLE_ON_Disconnect(BLE_Service_Typedef * pDuck)

/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  Duck_BLE_ON_Connect
* Description    :  连接
* Input          :  BLE_Service_Typedef * pDuck 服务参数
*                   ble_evt_t * pBLE_Evt  BLE事件
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_ON_Connect(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt)
{
    pDuck->Conn_Handle = pBLE_Evt->evt.gap_evt.conn_handle;

}// End of void void Duck_BLE_ON_Connect(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt)

/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  Duck_BLE_String_Send
* Description    :  发送字符串
* Input          :  BLE_Service_Typedef * pDuck 服务参数
*                   u16 usValue_Handl           目的handle
*                   u8 * pString                待发送内容
*                   u16 usLen                   待发送长度
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u32 Duck_BLE_String_Send(BLE_Service_Typedef * pDuck, u16 usValue_Handle, u8 * pString, u16 usLen)
{
    ble_gatts_hvx_params_t hvx_params;
    u32 uiResult;
    u8 ucRetry = 3;
    static u8 i = 0;

    if (pDuck == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if ((pDuck->Conn_Handle == BLE_CONN_HANDLE_INVALID))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (usLen > BLE_DUCK_MAX_DATA_LEN)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    do
    {
        i++;
        pString[usLen++] = i;
        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = usValue_Handle;
        hvx_params.p_data = pString;
        hvx_params.p_len  = &usLen;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
    
        uiResult = sd_ble_gatts_hvx(pDuck->Conn_Handle, &hvx_params);
        if (uiResult != NRF_SUCCESS)
        {
            nrf_delay_ms(10);
            ucRetry--;
        }
//        app_trace_log("BLE Send Success!\r\n");
        
    }while((uiResult != NRF_SUCCESS) && ucRetry);
    
    if (uiResult != NRF_SUCCESS)
    {
        app_trace_log("BLE Send Failed = %d!\r\n", uiResult);
        APP_ERROR_CHECK(uiResult);

    }
    
    return uiResult;
    
    
}// End of u32 Duck_BLE_String_Send(BLE_Service_Typedef * pDuck, u16 usValue_Handle, u8 * pString, u16 usLen)

/*******************************************************************************
*                           陆超@2017-01-16
* Function Name  :  Temp_BLE_Service_Update
* Description    :  温度刷新
* Input          :  BLE_Service_Typedef * pDuck 服务参数
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_BLE_Service_Update(BLE_Service_Typedef * pDuck)
{
    u32 Err_Code;
    u8 ucEncode[BLE_DUCK_MAX_DATA_LEN];
    u16 usLen;
    
    // 在联网状态
    if (!pDuck->Temp_Humi_Listening_En)
    {
        return;
    }

    // 打包数据
    usLen = Duck_Temp_Humi_Encode(Sensor.sTemp, Sensor.usHumi, ucEncode);
    
    // 更新电量数据
    Err_Code = Duck_BLE_String_Send(pDuck, pDuck->Temp_Humi_Handle.value_handle, ucEncode, usLen);
    if ((Err_Code != NRF_SUCCESS))
    {
        APP_ERROR_HANDLER(Err_Code);
    }
    
}// End of void Temp_BLE_Service_Update(BLE_Service_Typedef * pDuck)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




