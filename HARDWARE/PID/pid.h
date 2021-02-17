#ifndef _pid_
#define _pid_

#include "sys.h"
#include "delay.h"


typedef struct 
{
    float Sv; //用户设定值
    float Pv; //传感器反馈值
    
    float Kp; //PID算法系数
    float Ti; //采样总时长
    float Td; //采样时间间隔
    float T;  //PID计算周期--采样周期

    float Ek;   //本次偏差
    float Ek_1; //上次偏差
    float Sek;  //历史偏差之和

    float Iout; //积分算法结果
    float Pout; //比例算法结果
    float Dout; //微分算法结果

    float OUT;
    float OUT0;

    u16 C10ms;

    u16 pwmcycle;//pwm周期
}PID;

extern PID pid; //存放PID算法所需要的数据

#define pwmout_1    GPIO_SetBits(GPIOB, GPIO_Pin_8)    //停止加热
#define pwmout_0    GPIO_ResetBits(GPIOB, GPIO_Pin_8)  //加热


void PID_Init(void);    //PID算法初始化
void PId_calc(void);    //PID计算
void PIDOUT_init();     //pid输出引脚
void PID_out();  //输出PID运算结果到负载---每1ms被调用一次


#endif