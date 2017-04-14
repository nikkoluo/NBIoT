/******************** (C) COPYRIGHT 2017 Â½³¬ **********************************
* File Name          :  nRF51_BLE_Peer.h
* Author             :  Â½³¬
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  nRF51_BLE_Peer header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_PEER_H
#define __NRF51_BLE_PEER_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     SEC_PARAM_BOND              1                               /**< Perform bonding. */
#define     SEC_PARAM_MITM              0                               /**< Man In The Middle protection not required. */
#define     SEC_PARAM_IO_CAPABILITIES   BLE_GAP_IO_CAPS_NONE            /**< No I/O capabilities. */
#define     SEC_PARAM_OOB               0                               /**< Out Of Band data not available. */
#define     SEC_PARAM_MIN_KEY_SIZE      7                               /**< Minimum encryption key size. */
#define     SEC_PARAM_MAX_KEY_SIZE      16                              /**< Maximum encryption key size. */


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_BLE_Peer_Manager_Init(bool erase_bonds);             // °ó¶¨¹ÜÀí³õÊ¼»¯



#endif /* __NRF51_BLE_PEER_H */

/******************* (C) COPYRIGHT 2017 Â½³¬ *****END OF FILE******************/

