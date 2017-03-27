/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  Duck_DFU.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/28/2017
* Description        :  Duck_DFU 任务
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_DFU.h"
#include "device_manager.h"
#include "ble_hci.h"
#include "ble_dfu.h"
#include "dfu_app_handler.h"
#include "ble_conn_params.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void Duck_DFU_Advertising_Stop(void);                                   // 停止广播
void Duck_DFU_Reset_Prepare(void);                                      // 重启前准备
void DFU_App_Context_Load(dm_handle_t const * p_handle);                // 绑定模式下att table切换
void Duck_BLE_DFU_Services_Init(void);                                  // DFU服务初始化

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-02-28
* Function Name  :  Duck_DFU_Advertising_Stop
* Description    :  停止广播
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_DFU_Advertising_Stop(void)
{
    uint32_t err_code;

    err_code = sd_ble_gap_adv_stop();
    APP_ERROR_CHECK(err_code);

}// End of void Duck_DFU_Advertising_Stop(void)

/*******************************************************************************
*                           陆超@2017-02-28
* Function Name  :  DFU_App_Context_Load
* Description    :  绑定模式下att table切换
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void DFU_App_Context_Load(dm_handle_t const * p_handle)
{
    uint32_t                 err_code;
    static uint32_t          context_data;
    dm_application_context_t context;

    context.len    = sizeof(context_data);
    context.p_data = (uint8_t *)&context_data;

    err_code = dm_application_context_get(p_handle, &context);
    if (err_code == NRF_SUCCESS)
    {
        // Send Service Changed Indication if ATT table has changed.
        if ((context_data & (DFU_APP_ATT_TABLE_CHANGED << DFU_APP_ATT_TABLE_POS)) != 0)
        {
            err_code = sd_ble_gatts_service_changed(BLE_Connect_Handle, APP_SERVICE_HANDLE_START, BLE_HANDLE_MAX);
            if ((err_code != NRF_SUCCESS) &&
                (err_code != BLE_ERROR_INVALID_CONN_HANDLE) &&
                (err_code != NRF_ERROR_INVALID_STATE) &&
                (err_code != BLE_ERROR_NO_TX_BUFFERS) &&
                (err_code != NRF_ERROR_BUSY) &&
                (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING))
            {
                APP_ERROR_HANDLER(err_code);
            }
        }

        err_code = dm_application_context_delete(p_handle);
        APP_ERROR_CHECK(err_code);
    }
    else if (err_code == DM_NO_APP_CONTEXT)
    {
        // No context available. Ignore.
    }
    else
    {
        APP_ERROR_HANDLER(err_code);
    }
    
}// End of void DFU_App_Context_Load(dm_handle_t const * p_handle)


/** @snippet [Duck_DFU BLE Reset prepare] */
/**@brief Function for preparing for system reset.
 *
 * @details This function implements @ref Duck_DFU_app_reset_prepare_t. It will be called by 
 *          @ref Duck_DFU_app_handler.c before entering the bootloader/Duck_DFU.
 *          This allows the current running application to shut down gracefully.
 */

/*******************************************************************************
*                           陆超@2017-02-28
* Function Name  :  Duck_DFU_Reset_Prepare
* Description    :  重启前准备  被Duck_DFU_app_handler.c 调用
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_DFU_Reset_Prepare(void)
{
    uint32_t err_code;

    // 有连接
    if (BLE_Connect_Handle != BLE_CONN_HANDLE_INVALID)
    {
        // Disconnect from peer.
        err_code = sd_ble_gap_disconnect(BLE_Connect_Handle, BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
        APP_ERROR_CHECK(err_code);

    }
    else
    {
        // 停止广播
        Duck_DFU_Advertising_Stop();
    }

    err_code = ble_conn_params_stop();
    APP_ERROR_CHECK(err_code);

    nrf_delay_ms(500);
    
}// End of void Duck_DFU_Reset_Prepare(void)

/*******************************************************************************
*                           陆超@2017-02-28
* Function Name  :  Duck_BLE_DFU_Services_Init
* Description    :  Duck BLE DFU服务初始化    
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_DFU_Services_Init(void)
{
    u32 err_code;
    ble_dfu_init_t   dfus_init;

    // Initialize the Device Firmware Update Service.
    memset(&dfus_init, 0, sizeof(dfus_init));

    dfus_init.evt_handler   = dfu_app_on_dfu_evt;
    dfus_init.error_handler = NULL;
    dfus_init.evt_handler   = dfu_app_on_dfu_evt;
    dfus_init.revision      = DFU_REVISION;

    err_code = ble_dfu_init(&Duck_DFU_Services, &dfus_init);
    APP_ERROR_CHECK(err_code);

    dfu_app_reset_prepare_set(Duck_DFU_Reset_Prepare);
    dfu_app_dm_appl_instance_set(DM_App_Handle);
 

}// End of void Duck_BLE_DFU_Services_Init(void)

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/




