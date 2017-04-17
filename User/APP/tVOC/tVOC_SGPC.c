/******************** (C) COPYRIGHT 2017 Â½³¬ **********************************
* File Name          :  tVOC_SGPC.c
* Author             :  Â½³¬
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/30/2017
* Description        :  tVOCÓ¦ÓÃ³ÌÐò
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "tVOC_SGPC.h"
#include "Communal_IIC.h"
#include "sensirion_common.h"
#include "nrf_delay.h"




/* Private variables ---------------------------------------------------------*/
     
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void sensirion_sleep_usec(u32 useconds)
{
	nrf_delay_ms(useconds / 1000);
}

static u8 sensirion_i2c_write_byte(u8 data)
{


    return SW_IIC_Write_Byte(&Communal_IIC, data);
}

static u8 sensirion_i2c_read_byte(u8 ack)
{
    u8 data = 0;

    SW_IIC_Read_Byte(&Communal_IIC, &data, ack);
    return data;
}

static void sensirion_i2c_start(void)
{
	SW_I2C_Start_Condition(&Communal_IIC);

}

static void sensirion_i2c_stop(void)
{
    SW_I2C_Stop_Condition(&Communal_IIC);
}

u8 sensirion_i2c_write(u8 address, const u8* data, u16 count)
{
    u8 ret;
    u16 i;
    sensirion_i2c_start();
    ret = sensirion_i2c_write_byte(address << 1);
    if (ret != STATUS_OK) {
        sensirion_i2c_stop();
        return ret;
    }
    for (i = 0; i < count; i++) {
        ret = sensirion_i2c_write_byte(data[i]);
        if (ret != STATUS_OK) {
            sensirion_i2c_stop();
            break;
        }
    }
    sensirion_i2c_stop();
    return ret;
}

u8 sensirion_i2c_read(u8 address, u8* data, u16 count)
{
    u8 ret;
    u16 i;
    sensirion_i2c_start();
    ret = sensirion_i2c_write_byte((address << 1) | 1);
    if (ret != STATUS_OK) {
        sensirion_i2c_stop();
        return ret;
    }
    for (i = 0; i < count; i++)
        data[i] = sensirion_i2c_read_byte(1);

    sensirion_i2c_stop();
    return ret;
}

void sensirion_i2c_init()
{

}



/******************* (C) COPYRIGHT 2017 Â½³¬ ************* END OF FILE ********/




