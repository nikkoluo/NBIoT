/******************** (C) COPYRIGHT 2017 Â½³¬ **********************************
* File Name          :  Communal_Flash.h
* Author             :  Â½³¬
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/22/2017
* Description        :  Communal_Flash header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMUNAL_FLASH_H
#define __COMMUNAL_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  u32 Communal_Flash_Load(uint8_t           * p_dest,
                                pstorage_handle_t * p_src,
                                pstorage_size_t     size,
                                pstorage_size_t     offset);            // ¶ÁÈ¡
                                                     

extern  u32 Communal_Flash_Update(pstorage_handle_t * p_dest,
                                  uint8_t           * p_src,
                                  pstorage_size_t     size,
                                  pstorage_size_t     offset);          // Ð´Èë
extern  u32 Communal_Flash_Clear(pstorage_handle_t * p_dest, pstorage_size_t size); // É¾³ý    

#endif /* __COMMUNAL_FLASH_H */

/******************* (C) COPYRIGHT 2017 Â½³¬ *****END OF FILE******************/

