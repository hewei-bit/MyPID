#include "time_init.h"

#include "stm32f10x_conf.h"
#include "led.h"
#include "pid.h"

extern u16 Kms10;

void Timer4_init() //T4 10msʱ��
{                  //72000000/7200=100us

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;               //��������     //100us*10=1000us=10ms
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;               //��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;              //�ָ�ʱ��
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
    TIM_DeInit(TIM4);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    /*���¶�ʱ��4�жϳ�ʼ��*/
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //���ϼ�����������ж�

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // TIM4_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��4
}

void Timer3_init() //T3 1msʱ��
{                  //72000000/7200=100us
    //
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    //��ʱ��TIM3��ʼ��
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;                //��������     //10ms
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;               //��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;              //�ָ�ʱ��
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
    TIM_DeInit(TIM3);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /*���¶�ʱ��4�жϳ�ʼ��*/
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //���ϼ�����������ж�

    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);                           //��ʼ��NVIC�Ĵ���

    TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��3
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void) //TIM3�ж� 1ms 1��
{
    u8 st;
    st = TIM_GetFlagStatus(TIM3, TIM_IT_Update);
    if (st != 0)
    {
        pid.C10ms++;
        TIM_ClearFlag(TIM3, TIM_IT_Update);
        PID_out(); //���PID������������
    }
}

void TIM4_IRQHandler() //10ms 1��
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