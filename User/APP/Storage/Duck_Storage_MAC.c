/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_Storage_MAC.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  mac地址处理
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_Storage_MAC.h"
#include "Duck_Storage.h"
#include "nrf_soc.h"
#include "Communal_Flash.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Get_MAC(void);                                                     // 获取MAC地址
void MAC_Flash_Init(void);                                              // mac flash初始化
u8 MAC_Save(u8 *ucMAC);                                                 // 保存mac地址
u8 MAC_Read(u8 *ucMAC);                                                 // 读取mac地址
u8 MAC_Delete(void);                                                    // 删除mac地址


                                               
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-10
* Function Name  :  Get_MAC
* Description    :  获取MAC地址
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Get_MAC(void)
{

    u32 Err_Code;
    ble_gap_addr_t MAC_Addr;
    u8 ucTemp[MAC_FLASH_SIZE + 1];

    // 没有MAC存在
    if (MAC_Read(ucTemp) == 0)
    {
        

        Err_Code = sd_ble_gap_address_get(&MAC_Addr);
        APP_ERROR_CHECK(Err_Code); 

        // 采用虚假mac
        MIOT_Adv.MAC[0] = MAC_Addr.addr[5];
        MIOT_Adv.MAC[1] = MAC_Addr.addr[4];
        MIOT_Adv.MAC[2] = MAC_Addr.addr[3];
        MIOT_Adv.MAC[3] = MAC_Addr.addr[2];
        MIOT_Adv.MAC[4] = MAC_Addr.addr[1];
        MIOT_Adv.MAC[5] = MAC_Addr.addr[0];

        MAC_Addr.addr[5]  &= 0x3F;

            
        app_trace_log("\r\n未烧录mac地址!\r\n");
        
    }
    else
    {
        // 设置mac地址
        MAC_Addr.addr[5] = ucTemp[0];
        MAC_Addr.addr[4] = ucTemp[1];
        MAC_Addr.addr[3] = ucTemp[2];
        MAC_Addr.addr[2] = ucTemp[3];
        MAC_Addr.addr[1] = ucTemp[4];
        MAC_Addr.addr[0] = ucTemp[5]; 
        
        MIOT_Adv.MAC[0] = MAC_Addr.addr[5];
        MIOT_Adv.MAC[1] = MAC_Addr.addr[4];
        MIOT_Adv.MAC[2] = MAC_Addr.addr[3];
        MIOT_Adv.MAC[3] = MAC_Addr.addr[2];
        MIOT_Adv.MAC[4] = MAC_Addr.addr[1];
        MIOT_Adv.MAC[5] = MAC_Addr.addr[0];    
    }
    
    // 写入mac地址
    MIOT_Adv.Frame_Control_Bit.MAC_Include = 1;
    MAC_Addr.addr_type =  BLE_GAP_ADDR_TYPE_PUBLIC; 
    Err_Code = sd_ble_gap_address_set(BLE_GAP_ADDR_CYCLE_MODE_NONE, &MAC_Addr);
    APP_ERROR_CHECK(Err_Code); 
        
    app_trace_log("Current MAC = %02X:%02X:%02X:%02X:%02X:%02X\r\n", MIOT_Adv.MAC[0],
                                                                     MIOT_Adv.MAC[1],
                                                                     MIOT_Adv.MAC[2],
                                                                     MIOT_Adv.MAC[3],
                                                                     MIOT_Adv.MAC[4],
                                                                     MIOT_Adv.MAC[5]);


    
    
}// End of void Get_MAC(void)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  MAC_Save
* Description    :  保存MAC地址
* Input          :  u8 *ucMAC 待保存的mac
* Output         :  None
* Return         :  1 成功 0 失败
*******************************************************************************/
u8 MAC_Save(u8 *ucMAC)
{
    u8 ucTemp[MAC_FLASH_SIZE + 2];
    u32 Err_Code;
    u8 ucReturn = 0;

    // 保存mac
    ucTemp[0] = 0xAA;
    memcpy(&ucTemp[1], ucMAC, MAC_FLASH_SIZE);

    // 写flash
    Err_Code = Communal_Flash_Update(&MAC_Flash_Handle, ucTemp, MAC_FLASH_SIZE + 2, 0);
    APP_ERROR_CHECK(Err_Code);

    // 读取
    if (MAC_Read(ucTemp))
    {
        if (memcmp(ucTemp, ucMAC, MAC_FLASH_SIZE) == 0)
        {
            ucReturn = 1;
        }
    }

    return ucReturn;

}// End of u8 MAC_Save(u8 *ucMAC)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  MAC_Delete
* Description    :  删除MAC地址
* Input          :  None
* Output         :  None
* Return         :  1 成功 0 失败
*******************************************************************************/
u8 MAC_Delete(void)
{
    u32 Err_Code;
    u8 ucReturn = 0;
    u8 ucBuffer[MAC_FLASH_SIZE];

    // 写flash
    Err_Code = Communal_Flash_Clear(&MAC_Flash_Handle, MAC_PSM_SIZE);
    APP_ERROR_CHECK(Err_Code);

    // 删除成功
    if (Err_Code == NRF_SUCCESS)
    {

        ucReturn = 1;

        MAC_Read(ucBuffer);

    }

    return ucReturn;

}// End of u8 MAC_Delete(void)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  MAC_Read
* Description    :  读取MAC地址
* Input          :  u8 *ucMAC 待保存的mac
* Output         :  None
* Return         :  1 成功 0 失败
*******************************************************************************/
u8 MAC_Read(u8 *ucMAC)
{
    u8 ucTemp[MAC_FLASH_SIZE + 1];
    u32 Err_Code;
    u8 ucReturn = 0;

    // 读
    System_Err.MAC = 1;
    Err_Code = Communal_Flash_Load(ucTemp, &MAC_Flash_Handle, MAC_FLASH_SIZE + 1, 0);

    // 读取成功
    if ((Err_Code == NRF_SUCCESS) && ucTemp[0] == 0xAA)
    {
        memcpy(ucMAC, &ucTemp[1], MAC_FLASH_SIZE); 
        System_Err.MAC = 0;

        ucReturn = 1;
    }

    return ucReturn;
    
}// End of u8 MAC_Read(u8 *ucMAC)

/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  MAC_Flash_Init
* Description    :  MAC flash初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void MAC_Flash_Init(void)
{
    u32 Err_Code;    
    pstorage_module_param_t param;
    
    // Register
    param.block_size  = MAC_PSM_SIZE;
    param.block_count = MAC_PSM_BLOCK;
    param.cb          = Duck_Storage_Callback;

    Err_Code = pstorage_register(&param, &MAC_Flash_Handle);
    if (Err_Code == NRF_SUCCESS) 
    {
        app_trace_log("MAC flash register succ\r\n");
    } 
    else 
    {
        app_trace_log("MAC flash register fail\r\n");
    }

    
}// End of static void MAC_Flash_Init(void)


/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/










