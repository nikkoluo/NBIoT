/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  SW_I2C.h
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/26/2016
* Description        :  SW_I2C header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SW_I2C_H
#define __SW_I2C_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define     SW_I2C_SEND_ACK             0x01                            // 发送应答
#define     SW_I2C_DONT_SEND_ACK        0x00                            // 不发送应答
#define     SW_I2C_NEED_SEND_STOP       1                               // 需要发送停止位
#define     SW_I2C_DONT_SEND_STOP       0                               // 无需发送停止位

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    void                (*Dealy)(void);                                 // 延时
    void                (*Dealy_us)(void);                              // us延时
    void                (*Pin_Init)(void);                              // 管脚初始化
    void                (*SDA_High)(void);                              // 拉高SDA
    void                (*SDA_Low)(void);                               // 拉低SDA
    void                (*SCL_High)(void);                              // 拉高SCL
    void                (*SCL_Low)(void);                               // 拉低SCL                
    void                (*Set_SDA_Input)(void);                         // 设置数据位输入管脚
    void                (*Set_SDA_Output)(void);                        // 设置数据位输出管脚
    void                (*Set_SCL_Output)(void);                        // 设置时钟位输出管脚
    unsigned char       (*SDA_Read)(void);                              // 读SDA管脚
    unsigned char       (*SCL_Read)(void);                              // 读SCL管脚  
    unsigned char       Inited;                                         // 置一表示已经初始化
    unsigned int        Wait_Scl_Free_Timeout;                          // 等待SCL被释放超时时间                             
    
} SW_I2C_Typedef;

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C);                              // 管脚初始化
extern  unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData);  // IIC写字节
extern  unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Need_Ack);   // IIC读字节
extern  unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C);           // 产生起始信号
extern  unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C);            // 产生停止信号
extern  unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition); // 发送数据

#endif /* __SW_I2C_H */

/******************* (C) COPYRIGHT 2016 陆超 *****END OF FILE******************/

