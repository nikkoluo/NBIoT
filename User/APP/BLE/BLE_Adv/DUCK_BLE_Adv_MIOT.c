/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_Adv_MIOT.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  蓝牙广播配置
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Adv_MIOT.h"
#include <stdlib.h>
#include <string.h>
#include "Duck_BLE_Adv.h"
#include "ble_srv_common.h"


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
u8 BLE_MIOT_Service_Package(u16 usEvent, u8* pService_Data, MIOT_Typedef *MIOT);// MIOT数据打包

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-10
* Function Name  :  BLE_MIOT_Service_Package
* Description    :  MIOT数据打包
* Input          :  u16 usEvent         待打包的事件
*                   u8* pService_Data   缓存
*                   MIOT_Typedef *MIOT  源数据
* Output         :  None
* Return         :  打包数据长度
*******************************************************************************/
u8 BLE_MIOT_Service_Package(u16 usEvent, u8* pService_Data, MIOT_Typedef *MIOT)
{
    u8 ucLen = 0;

    // Frame_Control数据
    ucLen += uint16_encode(MIOT->Frame_Control, &pService_Data[ucLen]);

    // Product ID
    ucLen += uint16_encode(MIOT_PRODUCT_ID, &pService_Data[ucLen]);

    // Frame_Counter
    pService_Data[ucLen++] = MIOT->Frame_Counter;

    // MAC
    if (MIOT->Frame_Control_Bit.MAC_Include)
    {
        pService_Data[ucLen++] = MIOT->MAC[5];
        pService_Data[ucLen++] = MIOT->MAC[4];
        pService_Data[ucLen++] = MIOT->MAC[3];
        pService_Data[ucLen++] = MIOT->MAC[2];
        pService_Data[ucLen++] = MIOT->MAC[1];
        pService_Data[ucLen++] = MIOT->MAC[0];
    }

    // Capability
    if (MIOT->Frame_Control_Bit.Capability_Include)
    {
        pService_Data[ucLen++] = MIOT->Capability;
    }

    // 事件
    if (MIOT->Frame_Control_Bit.Event_Include)
    {
        // 事件ID
        ucLen += uint16_encode(MIOT->Event_ID, &pService_Data[ucLen]); 

        // 温湿度
        if (usEvent == MIOT_EVENT_ID_TH)
        {   
            // 事件长度 温度 湿度
            pService_Data[ucLen++] = MIOT_EVENT_TH_LEN;
            ucLen += uint16_encode(MIOT->Temp_Val, &pService_Data[ucLen]);
            pService_Data[ucLen++] = MIOT->Humi_Val;
        }
        // 电量
        else if (usEvent == MIOT_EVENT_ID_BAT)
        {
            // 事件长度 电量
            pService_Data[ucLen++] = MIOT_EVENT_BAT_LEN;
            pService_Data[ucLen++] = MIOT->Bat_Percent;
        }
        // 绑定
        else if (usEvent == MIOT_EVENT_ID_BOND)
        {
            // 事件长度 绑定
            pService_Data[ucLen++] = MIOT_EVENT_BOND_LEN;
            ucLen += uint16_encode(MIOT_EVENT_ID_TH, &pService_Data[ucLen]);
        }
        // hall
        else if (usEvent == MIOT_EVENT_ID_HALL)
        {
            // hall事件长度内容 
            pService_Data[ucLen++] = MIOT_EVENT_HALL_LEN;
            pService_Data[ucLen++] = Hall.Magnet_Near;
        }
    }
    
    return ucLen;
    
}// End of u8 BLE_MIOT_Service_Package(u16 usEvent, u8* pService_Data, MIOT_Typedef *MIOT)





/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




