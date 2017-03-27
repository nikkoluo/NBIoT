/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Temp_Humi.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  温湿度应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Temp_Humi.h"
#include "nrf_gpio.h"
#include "Temp_Humi_SHT30.h"
#include "Duck_BLE_Private_Service.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void Temp_Humi_Task_Handle(void *p_arg);                                // Temp_Humi任务
void Temp_Humi_Task_Create(void);                                       // 创建Temp_Humi任务
u32 Temp_Humi_Chip_Init(void);                                          // 芯片初始化
void Temp_Humi_Update(float fTemp, float fHumi);                        // 更新温湿度数据
void Temp_Humi_Get(void);                                               // 获取温湿度

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Task_Create
* Description    :  创建Temp_Humi任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 初始化变量和IO
    Temp_Humi_Variable_Init();
    Temp_Humi_Port_Init();
    
    // 配置参数 周期模式运行
    Temp_Humi_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    Temp_Humi_Task.Timeout_handler = Temp_Humi_Task_Handle;
    Temp_Humi_Task.Period          = TASK_TEMP_HUMI_PERIOD;

    err_code &= app_timer_create(&Temp_Humi_Task.p_ID,
                                 Temp_Humi_Task.Run_Mode,
                                 Temp_Humi_Task.Timeout_handler);
    // 芯片初始化
    err_code &= Temp_Humi_Chip_Init();
    err_code &= Task_Timer_Start(&Temp_Humi_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Temp&Humi create failed!\r\n");    
    }


}// End of void Temp_Humi_Task_Create(void)

/*******************************************************************************
*                           陆超@2017-01-03
* Function Name  :  Temp_Humi_Chip_Init
* Description    :  芯片初始化
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS 成功 1失败
*******************************************************************************/
u32 Temp_Humi_Chip_Init(void)
{
    u32 Err_Code = 0xFFFF;
    u8 ucSN[8];

    float Temp;
    float Humi;

    // 默认传感器error
    System_Err.Temp_Humi = 1;

    if (SHT3x_Soft_Reset() == 1)
    {
        if (SHT3x_Read_SN(ucSN))
        {
            Err_Code             = NRF_SUCCESS;
            System_Err.Temp_Humi = 0;
            
            app_trace_log("SHT3x_SN = 0x%02X%02X%02X%02X\r\n", ucSN[0], ucSN[1], ucSN[2], ucSN[3]);


            // 首次读取温湿度
            SHT3x_Get_Temp_Humi(&Temp, &Humi);
            Temp_Humi_Update(Temp, Humi);
        }
    }

    return Err_Code;
        
}// End of u32 Temp_Humi_Chip_Init(void)

/*******************************************************************************
*                           陆超@2017-03-08
* Function Name  :  Temp_Humi_Get
* Description    :  获取温湿度
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Get(void)
{

    float Temp;
    float Humi;
    static u8 ucError_Times = 0;

    if(SHT3x_Get_Temp_Humi(&Temp, &Humi))
    {
        // 清空出错次数
        ucError_Times = 0;

        // 更新温湿度数据
        Temp_Humi_Update(Temp, Humi);

        // 清空错误标志位
        System_Err.Temp_Humi = 0;
        
    }
    else
    {
        ucError_Times++;

        if (ucError_Times > MAX_GET_SENSOR_ERROR)
        {
            ucError_Times        = 0;

            // 置位错误标志位
            System_Err.Temp_Humi = 1;

            // 报错 并广播错误数据
            app_trace_log("SHT30 Sensor Error!\r\n");

        }
    }

   
}// End of void Temp_Humi_Get(void)

/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Temp_Humi_Task_Handle
* Description    :  Temp_Humi任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Task_Handle(void *p_arg)
{

    Temp_Humi_Get();
   
}// End of void Temp_Humi_Task_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2017-01-12
* Function Name  :  Temp_Humi_Update
* Description    :  更新温湿度数据
* Input          :  float fTemp  温度
*                   float fHumi  湿度 
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Update(float fTemp, float fHumi)
{

    short sTemp_Now = -99;
    u16   usHumi_Now;

    // 保存float数据
    Sensor.fTemp = fTemp;
    Sensor.fHumi = fHumi;
    
    // 四舍五入 精确到1位小数
    fTemp     += 0.05;
    fTemp     *= 10;
    sTemp_Now  = (s16)fTemp;
    
    fHumi     += 0.05;
    fHumi     *= 10;
    usHumi_Now = (s16)fHumi;


    // 有数据刷新
    if((sTemp_Now != Sensor.sTemp) || (usHumi_Now != Sensor.usHumi))
    {
        Sensor.sTemp               = sTemp_Now;
        Sensor.usHumi              = usHumi_Now;
        
    }
    else
    {
        app_trace_log("                                             温湿度数据无变化!\r\n");    
    }
   
   
}// End of void Temp_Humi_Update(float fTemp, float fHumi)



/******************* (C) COPYRIGHT 2016 陆超 ************* END OF FILE ********/




