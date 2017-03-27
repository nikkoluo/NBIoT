/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_BLE_DevInfo_Service.c
* Author             :  陆超
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/12/2017
* Description        :  蓝牙DevInfo服务应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_DevInfo_Service.h"
#include <stdlib.h>
#include <string.h>
#include "ble_dis.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_DevInfo_Services_Init(void);                              // 系统信息服务初始化


/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           陆超@2017-01-12
* Function Name  :  Duck_BLE_DevInfo_Services_Init
* Description    :  DevInfo服务初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_DevInfo_Services_Init(void)
{
    u32             Err_Code;

    // BLE设备信息
    ble_dis_init_t  BLE_Dis; 
    
    // 清空变量
    memset(&BLE_Dis, 0, sizeof(BLE_Dis));

    // 初始化模块信息
    ble_srv_ascii_to_utf8(&BLE_Dis.manufact_name_str,   BLE_MANUFACTURER_NAME);
    ble_srv_ascii_to_utf8(&BLE_Dis.fw_rev_str,          BLE_FW_REV_STR);
    ble_srv_ascii_to_utf8(&BLE_Dis.model_num_str,       BLE_MODULE_NUM);

    
    
    // 配置硬件版本
    ble_srv_ascii_to_utf8(&BLE_Dis.hw_rev_str,          DEFAULT_HARDWARE_VERSION);    


    
    // 设置读写权限
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&BLE_Dis.dis_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&BLE_Dis.dis_attr_md.write_perm);


    Err_Code = ble_dis_init(&BLE_Dis);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void Duck_BLE_DevInfo_Services_Init(void)



/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




