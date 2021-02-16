#include "time_init.h"

#include "stm32f10x_conf.h"
#include "led.h"
#include "pid.h"

extern u16 Kms10;

void Timer4_init() //T4 10ms时钟
{                  //72000000/7200=100us

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;               //计数个数     //100us*10=1000us=10ms
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;               //分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;              //分割时钟
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
    TIM_DeInit(TIM4);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    /*以下定时器4中断初始化*/
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //向上计数溢出产生中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // TIM4_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM4, ENABLE); //使能定时器4
}

void Timer3_init() //T3 1ms时钟
{                  //72000000/7200=100us
    //
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    //定时器TIM3初始化
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;                //计数个数     //10ms
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;               //分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;              //分割时钟
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
    TIM_DeInit(TIM3);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /*以下定时器4中断初始化*/
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //向上计数溢出产生中断

    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);                           //初始化NVIC寄存器

    TIM_Cmd(TIM3, ENABLE); //使能定时器3
}

//定时器3中断服务程序
void TIM3_IRQHandler(void) //TIM3中断 1ms 1次
{
    u8 st;
    st = TIM_GetFlagStatus(TIM3, TIM_IT_Update);
    if (st != 0)
    {
        pid.C10ms++;
        TIM_ClearFlag(TIM3, TIM_IT_Update);
        PID_out(); //输出PID运算结果到负载
    }
}

void TIM4_IRQHandler() //10ms 1次
{
    static u8 tsec;
    u8 st;
    st = TIM_GetFlagStatus(TIM4, TIM_IT_Update);
    if (st != 0)
    {
        TIM_ClearFlag(TIM4, TIM_IT_Update);
        Kms10++;
        //pid.C10ms++;
        if (tsec++ >= 100)
        {
            tsec = 0;
        }
    }
}