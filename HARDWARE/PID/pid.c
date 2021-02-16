#include "pid.h"

PID pid;

void PID_Init()         //PID参数初始化
{
    pid.Sv = 120;       //用户设定温度
    pid.Kp = 30;        //PID系数
    pid.T = 500;        //PID计算周期
    pid.Ti = 5000000;   //积分时间
    pid.Td = 1000;      //微分时间
    pid.pwmcycle = 200; //pwn周期1000
    pid.OUT0 = 1;
}  

void PId_calc(void)    //PID计算
{
    float DelEk;
	float ti,ki;
//	float Iout;
//	float Pout;
//	float Dout;
	float td;
	float kd;
	float out;

    pid.Ek = pid.Sv - pid.Pv;   //得到当前的偏差值
    pid.Pout = pid.Kp * pid.Ek; //比例输出
     
    pid.Sek += pid.Ek;          //历史总偏差
    DelEk = pid.Ek - pid.Ek_1   //最近两次偏差之和

    ti = pid.T / pid.Ti;
    ki = ti * pid.Kp;
    pid.Iout = ki * pid.Sek * pid.Kp;   //积分输出

    td = pid.Td / pid.T;
    kd = pid.Kp * td;   
    pid.Dout = kd * DelEk;          //微分输出

    out = pid.Pout + pid.Iout + pid.Dout;
}


void PIDOUT_init()     //pid输出引脚
{

}



void PID_out()  //输出PID运算结果到负载---每1ms被调用一次算
{

}
