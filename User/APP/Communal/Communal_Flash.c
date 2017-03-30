/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Communal_Flash.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/12/2017
* Description        :  公用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Communal_Flash.h"


/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
u32 Communal_Flash_Load(uint8_t           * p_dest,
                        pstorage_handle_t * p_src,
                        pstorage_size_t     size,
                        pstorage_size_t     offset);                    // 读取

                        
u32 Communal_Flash_Update(pstorage_handle_t * p_dest,
                          uint8_t           * p_src,
                          pstorage_size_t     size,
                          pstorage_size_t     offset);                  // 写入
                          
u32 Communal_Flash_Clear(pstorage_handle_t * p_dest, pstorage_size_t size); // 删除

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Communal_Flash_Load
* Description    :  flash读操作
* Input          :  uint8_t           * p_dest 读取缓存
*                   pstorage_handle_t * p_src  地址
*                   pstorage_size_t     size   长度
*                   pstorage_size_t     offset 偏移
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Communal_Flash_Load(uint8_t           * p_dest,
                        pstorage_handle_t * p_src,
                        pstorage_size_t     size,
                        pstorage_size_t     offset)
{
    u32 Err_Code;
    
    // 等待被释放
    while(Flash_Used)
    {
        Power_Manage();
    }

    // 占用flash
    Flash_Used = 1;
    Err_Code = pstorage_load(p_dest, p_src, size, offset);

    if (Err_Code == NRF_SUCCESS)
    {
        // 等待被释放
        while(Flash_Used)
        {
            Power_Manage();
        }
    }
    else
    {
        // 清空占用
        Flash_Used = 0;
    }

    return Err_Code;
    
}// End of u32 Communal_Flash_Load

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Communal_Flash_Update
* Description    :  flash写操作
* Input          :  pstorage_handle_t * p_dest 地址
*                   uint8_t           * p_src  待写入数据
*                   pstorage_size_t     size   长度
*                   pstorage_size_t     offset 偏移
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Communal_Flash_Update(pstorage_handle_t * p_dest,
                          uint8_t           * p_src,
                          pstorage_size_t     size,
                          pstorage_size_t     offset)
{
    u32 Err_Code;
    
    // 等待被释放
    while(Flash_Used)
    {
        Power_Manage();
    }

    // 占用flash
    Flash_Used = 1;
    Err_Code = pstorage_update(p_dest, p_src, size, offset);

    if (Err_Code == NRF_SUCCESS)
    {
        // 等待被释放
        while(Flash_Used)
        {
            Power_Manage();
        }
    }
    else
    {
        // 清空占用
        Flash_Used = 0;
    }

    return Err_Code;
    
}// End of u32 Communal_Flash_Update

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Communal_Flash_Clear
* Description    :  flash删除
* Input          :  pstorage_handle_t * p_dest 待删除地址
*                   pstorage_size_t     size   长度
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Communal_Flash_Clear(pstorage_handle_t * p_dest, pstorage_size_t size)
{
    u32 Err_Code;
    
    // 等待被释放
    while(Flash_Used)
    {
        Power_Manage();
    }

    // 占用flash
    Flash_Used = 1;
    Err_Code = pstorage_clear(p_dest, size);

    if (Err_Code == NRF_SUCCESS)
    {
        // 等待被释放
        while(Flash_Used)
        {
            Power_Manage();
        }
    }
    else
    {
        // 清空占用
        Flash_Used = 0;
    }

    return Err_Code;
    
}// End of u32 Communal_Flash_Clear(pstorage_handle_t * p_dest, pstorage_size_t size)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




