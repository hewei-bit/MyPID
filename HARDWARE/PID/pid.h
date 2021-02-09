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

    float Ek;   //本次偏差
    float Ek_1; //上次偏差
    float Sek;  //历史偏差之和

    float Iout; //积分算法结果
    float Pout; //比例算法结果
    float Dout; //微分算法结果

    float OUT;
    float OUT0;

    u16 C10ms;
}PID;

#endif