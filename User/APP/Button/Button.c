/******************** (C) COPYRIGHT 2016 陆超 **********************************
* File Name          :  Button.c
* Author             :  陆超
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Button应用程序
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button.h"
#include "nrf_gpio.h"
#include "Button_Single.h"
#include "Button_Long.h"
#include "Button_Double.h"

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void Button_Task_Handle(void *p_arg);                                   // Button任务
void Button_Task_Create(void);                                          // 创建Button任务
void Button_Free_ISR(void);                                             // Button释放中断处理
void Button_Push_ISR(void);                                             // Button[按下中断处理


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Button_Task_Create
* Description    :  创建Button任务
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // 初始化变量和IO
    Button_Variable_Init();
    
    // 配置参数 周期模式运行
    Button_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    Button_Task.Timeout_handler = Button_Task_Handle;
    Button_Task.Period          = 50;

    err_code = app_timer_create(&Button_Task.p_ID,
                                 Button_Task.Run_Mode,
                                 Button_Task.Timeout_handler);
    
    if (err_code != NRF_SUCCESS)
    {
        
    }
    
}// End of void Button_Task_Create(void)



/*******************************************************************************
*                           陆超@2016-12-28
* Function Name  :  Button_Task_Handle
* Description    :  Button任务
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Task_Handle(void *p_arg)
{
    // 按键间隔, 时间戳
    u32 Time_Interval, Timestamp;

    // 记录时间
    Timestamp = Timestamp_Get();

    // 仅单次按下过
    if (Button.Status == 1)
    {
        // 获取时间戳
        Time_Interval  = Timestamp_Interval_Get(Timestamp, Button.Push_Timestamp);
        Time_Interval /= TICK_TO_MS;
        
        // 处理长按事件
        if ((Time_Interval >= LONG_CLICK_MIN_DURATION) && (Time_Interval < RESET_CLICK_MIN_DURATION))
        {
            // 避免多次触发
            if (Button.Long == 0)
            {
                Button.Long = 1;
                
                // 处理长按事件
                Long_Button_Handler();
            }
        }
//        else if (Time_Interval > RESET_CLICK_MIN_DURATION)
//        {
//            if (Button.Long)
//            {
//                app_trace_log("超长按，重启系统!\r\n");
//                nrf_delay_ms(100);
//                APP_ERROR_CHECK(SPECIAL_CODE_RESET);
//            }

//        }
    }
    else if (Button.Status == 2)
    {
        // 上次释放后经过的时间
        Time_Interval  = Timestamp_Interval_Get(Timestamp, Button.Free_Timestamp);
        Time_Interval /= TICK_TO_MS;  

        // 单击信号
        if ((Time_Interval < CLICK_MAX_DURATION) && (Time_Interval > DOUBLE_HIT_INTERVAL))
        {
            // 停止长按识别
            Task_Timer_Stop(&Button_Task);
            Button_Variable_Init();
            
            // 单击事件
            Single_Button_Handler();
        }
    }

   
}// End of void Button_Task_Handle(void *p_arg)

/*******************************************************************************
*                           陆超@2016-04-26
* Function Name  :  Button_Push_ISR
* Description    :  Button上升沿中断处理
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Push_ISR(void)
{

    
    Button.Long  = 0;

    // 记录触发时间
    Button.Push_Timestamp = Timestamp_Get(); 

    // 首次按下启动定时器
    if (Button.Status == 0)

    {
        Button.Status = 1;
        
        // 启动定时器
        Task_Timer_Start(&Button_Task, NULL);
    }
    // 二次按下
    else if (Button.Status == 2)
    {
        Button.Status = 3;   
    }

}// End of void Button_Push_ISR(void)

/*******************************************************************************
*                           陆超@2017-01-19
* Function Name  :  Button_Free_ISR
* Description    :  Button释放中断处理
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Free_ISR(void)
{
    // 按键时长
    u32 Time_Interval;

    if (Button.Status == 0)
    {
        return;    
    }

    // 记录时间戳
    Button.Free_Timestamp = Timestamp_Get(); 

    // 计算按键间隔
    Time_Interval  = Timestamp_Interval_Get(Button.Free_Timestamp, Button.Push_Timestamp);
    Time_Interval /= TICK_TO_MS;
    
    // 第一次抬起
    if (Button.Status == 1)
    {
        // 长按释放
        if (Button.Long)
        {
            Task_Timer_Stop(&Button_Task);

            Button_Variable_Init();

            app_trace_log("长按释放!\r\n");
        }
        else
        {
            Button.Status = 2;
        }
    }
    else if (Button.Status == 3)
    {

        Task_Timer_Stop(&Button_Task);

        Button_Variable_Init(); 
        
        // 误触发
        if (Time_Interval < CLICK_MIN_DURATION)
        {
            // 停止定时器 清空变量
            app_trace_log("小于最小触发时间!\r\n");
        }
        // 正常单次触发
        else if (Time_Interval < CLICK_MAX_DURATION)
        {
            // 双击任务
            Double_Button_Handler();
        }
        // 长短按之间的误触发
        else if (Time_Interval < LONG_CLICK_MIN_DURATION)
        {
            
            app_trace_log("介于长短按之间的误触发!\r\n");
        }
    
    }
    
    
}// End of void Button_Free_ISR(void)


/******************* (C) COPYRIGHT 2016 陆超 **************END OF FILE*********/




