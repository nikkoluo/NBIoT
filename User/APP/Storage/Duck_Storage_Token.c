/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_Storage_Token.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  Token地址处理
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_Storage_Token.h"
#include "Duck_Storage.h"
#include "nrf_soc.h"
#include "Communal_Flash.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Get_Token(void);                                                   // 获取Token地址
u8 Token_Save(u8 *ucToken);                                             // 保存Token地址
u8 Token_Read(u8 *ucToken);                                             // 读取Token地址
void Token_Flash_Init(void);                                            // Token flash初始化
                                               
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-01-10
* Function Name  :  Get_Token
* Description    :  获取Token地址
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Get_Token(void)
{
    u8 ucTemp[TOKEN_FLASH_SIZE];

    // 没有Token存在
    if (Token_Read(ucTemp) == 0)
    {

        memset(MIOT_Adv.Token, 0xFF, TOKEN_FLASH_SIZE);
        app_trace_log("\r\n未烧录Token!\r\n");
        
    }
    else
    {

        
        memcpy(MIOT_Adv.Token, ucTemp, TOKEN_FLASH_SIZE);
        app_trace_log("Current Token = 0x%02X%02X%02X%02X%02X%02X%02X%02X\r\n", 
                                                                    MIOT_Adv.Token[0],
                                                                    MIOT_Adv.Token[1],
                                                                    MIOT_Adv.Token[2],
                                                                    MIOT_Adv.Token[3],
                                                                    MIOT_Adv.Token[4],
                                                                    MIOT_Adv.Token[5],
                                                                    MIOT_Adv.Token[6],
                                                                    MIOT_Adv.Token[7]);
    } 
    
}// End of void Get_Token(void)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Token_Save
* Description    :  保存Token地址
* Input          :  u8 *ucToken 待保存的Token
* Output         :  None
* Return         :  1 成功 0 失败
*******************************************************************************/
u8 Token_Save(u8 *ucToken)
{
    u8 ucTemp[TOKEN_FLASH_SIZE * 2];
    u32 Err_Code;
    u8 ucReturn = 0;

    // 保存Token
    ucTemp[0] = 0xAA;
    memcpy(&ucTemp[1], ucToken, TOKEN_FLASH_SIZE);

    // 写flash
    Err_Code = Communal_Flash_Update(&Token_Flash_Handle, ucTemp, TOKEN_FLASH_SIZE * 2, 0);
    APP_ERROR_CHECK(Err_Code);

    // 读取成功
    if (Token_Read(ucTemp))
    {
        if (memcmp(ucTemp, ucToken, TOKEN_FLASH_SIZE) == 0)
        {
            ucReturn = 1;
        }
    }

    return ucReturn;

}// End of u8 Token_Save(u8 *ucToken)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Token_Read
* Description    :  读取Token地址
* Input          :  u8 *ucToken 待保存的Token
* Output         :  None
* Return         :  1 成功 0 失败
*******************************************************************************/
u8 Token_Read(u8 *ucToken)
{
    u8 ucTemp[TOKEN_FLASH_SIZE + 1];
    u32 Err_Code;
    u8 ucReturn = 0;

    // 读
    System_Err.Token = 1;
    Err_Code = Communal_Flash_Load(ucTemp, &Token_Flash_Handle, TOKEN_FLASH_SIZE + 1, 0);

    // 读取成功
    if ((Err_Code == NRF_SUCCESS) && ucTemp[0] == 0xAA)
    {
        memcpy(ucToken, &ucTemp[1], TOKEN_FLASH_SIZE); 
        System_Err.Token = 0;

        ucReturn = 1;
    }

    return ucReturn;
    
}// End of u8 Token_Read(u8 *ucToken)

/*******************************************************************************
*                           陆超@2017-02-15
* Function Name  :  Token_Flash_Init
* Description    :  Token flash初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Token_Flash_Init(void)
{
    u32 Err_Code;    
    pstorage_module_param_t param;
    
    // Register
    param.block_size  = TOKEN_PSM_SIZE;
    param.block_count = TOKEN_PSM_BLOCK;
    param.cb          = Duck_Storage_Callback;

    Err_Code = pstorage_register(&param, &Token_Flash_Handle);
    if (Err_Code == NRF_SUCCESS) 
    {
        app_trace_log("Token flash register succ\r\n");
    } 
    else 
    {
        app_trace_log("Token flash register fail\r\n");
    }

    
}// End of void Token_Flash_Init(void)



/******************* (C) COPYRIGHT 2017 陆超 ************* END OF FILE ********/










