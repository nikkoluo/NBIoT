/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  nRF51_Storage.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  nRF51_Storage头文件
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_STORAGE_H
#define __NRF51_STORAGE_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "ble_advdata.h"
#include "ble_advertising.h"

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_Storage_Init(void);                                   // nRF51_Storage初始化
extern  void nRF51_Storage_Callback(pstorage_handle_t *  handle, u8   OP_Code,
                                   u32  Err_Code, u8*  pData, u32  uiData_Len); // 操作flash回调
                           
#endif /* __NRF51_STORAGE_H */

/******************* (C) COPYRIGHT 2017 陆超 ***** END OF FILE ****************/




