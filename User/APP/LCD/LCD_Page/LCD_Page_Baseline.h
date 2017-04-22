/******************** (C) COPYRIGHT 2017 陆超 **********************************
* File Name          :  LCD_Page_Baseline.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD_Page_Baseline header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_PAGE_BASELINE_H
#define __LCD_PAGE_BASELINE_H

/* Includes ------------------------------------------------------------------*/
#include "LCD_Port.h"


/* Private define ------------------------------------------------------------*/
#define     LCD_BASE_NOW_Y_ADDR  		16                            	// 当前baseline显示地址
#define     LCD_BASE_SAVE_Y_ADDR  		32                              // 保存的baseline显示地址
#define     LCD_BASE_SAVETIME_Y_ADDR  	48                              // 保存的baseline 时间显示地址





/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern	void LCD_Page_Baseline_Prepare(void);						    // 准备Baseline页面
extern	void LCD_Page_Baseline(void);								    // 显示Baseline页面


#endif /* __LCD_PAGE_BASELINE_H */

/******************* (C) COPYRIGHT 2017 陆超 **** END OF FILE *****************/

