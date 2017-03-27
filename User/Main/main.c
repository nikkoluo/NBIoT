/******************** (C) COPYRIGHT 2016 ***************************************
* File Name          :  Main.c
* Author             :  陆超
* CPU Type           :  Nrf51802
* IDE                :  IAR 7.8
* Version            :  V1.0  
* Date               :  12/25/2016
* Description        :  Main program body
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "nrf51.h"
#include "nrf_delay.h"
#include "SysInit.h"
#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_soc.h"
#include "app_scheduler.h"


#include <stdbool.h>
#include <stdint.h>
#include "nordic_common.h"
#include "softdevice_handler.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DEAD_BEEF                       0xDEADBEEF                      // 错误码
           

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Power_Manage(void);                                                // 电源管理 进入低功耗模式

/* Private functions ---------------------------------------------------------*/

/**@brief Callback function for asserts in the SoftDevice.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in]   line_num   Line number of the failing ASSERT call.
 * @param[in]   file_name  File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}
/*******************************************************************************
*                           陆超@2016-12-25
* Function Name  : Power_Manage
* Description    : 电源管理      
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Power_Manage(void)
{

#ifdef BLE_OPEN
    uint32_t err_code;
    
    app_sched_execute();
    err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
        
#else
        __WFE();
        
#endif

}// End of static void Power_Manage(void)

/*******************************************************************************
*                           陆超@2016-12-25
* Function Name  : main
* Description    : Main program      
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{

    
    // 系统初始化
    System_Init();

    for ( ;; )
    {

        Power_Manage();

    }

}// End of int main(void)


/******************* (C) COPYRIGHT 2016 ********************END OF FILE********/

