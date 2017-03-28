/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_BLE_Peer.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  nRF51_BLE 绑定
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE_Peer.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "pstorage.h"
#include "app_trace.h"
#include "device_manager.h"

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
u32 nRF51_BLE_Peer_Manager_Evt_Handler(dm_handle_t const * p_handle, dm_event_t const  * p_event, ret_code_t event_result);
void nRF51_BLE_Peer_Manager_Init(bool erase_bonds);                      // 绑定管理初始化

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2017-02-14
* Function Name  :  nRF51_BLE_Peer_Manager_Init
* Description    :  绑定初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Peer_Manager_Init(bool erase_bonds)
{
    uint32_t               err_code;
    dm_init_param_t        init_param = {.clear_persistent_data = erase_bonds};
    dm_application_param_t register_param;

    // Initialize persistent storage module.
    err_code = pstorage_init();
    APP_ERROR_CHECK(err_code);

    err_code = dm_init(&init_param);
    APP_ERROR_CHECK(err_code);

    memset(&register_param.sec_param, 0, sizeof(ble_gap_sec_params_t));

    register_param.sec_param.bond         = SEC_PARAM_BOND;
    register_param.sec_param.mitm         = SEC_PARAM_MITM;
    register_param.sec_param.io_caps      = SEC_PARAM_IO_CAPABILITIES;
    register_param.sec_param.oob          = SEC_PARAM_OOB;
    register_param.sec_param.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
    register_param.sec_param.max_key_size = SEC_PARAM_MAX_KEY_SIZE;
    register_param.evt_handler            = nRF51_BLE_Peer_Manager_Evt_Handler;
    register_param.service_type           = DM_PROTOCOL_CNTXT_GATT_SRVR_ID;

    err_code = dm_register(&DM_App_Handle, &register_param);
    APP_ERROR_CHECK(err_code);
    
}// End of void nRF51_BLE_Peer_Manager_Init(bool erase_bonds)

/*******************************************************************************
*                           陆超@2017-02-14
* Function Name  :  nRF51_BLE_Peer_Manager_Evt_Handler
* Description    :  绑定回调
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 nRF51_BLE_Peer_Manager_Evt_Handler(dm_handle_t const * p_handle, dm_event_t const  * p_event, ret_code_t event_result)
{
    APP_ERROR_CHECK(event_result);

#ifdef BLE_DFU_APP_SUPPORT
    if (p_event->event_id == DM_EVT_LINK_SECURED)
    {
        app_context_load(p_handle);
    }
#endif // BLE_DFU_APP_SUPPORT

    return NRF_SUCCESS;
}

/******************* (C) COPYRIGHT 2017 陆超 **************END OF FILE*********/





