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

    if(pid.C10ms < pid.T)
    {
        return;
    }

    pid.Ek = pid.Sv - pid.Pv;   //得到当前的偏差值
    pid.Pout = pid.Kp * pid.Ek; //比例输出
     
    pid.Sek += pid.Ek;          //历史总偏差
    DelEk = pid.Ek - pid.Ek_1;  //最近两次偏差之和

    ti = pid.T / pid.Ti;
    ki = ti * pid.Kp;
    pid.Iout = ki * pid.Sek * pid.Kp;   //积分输出

    td = pid.Td / pid.T;
    kd = pid.Kp * td;   
    pid.Dout = kd * DelEk;          //微分输出

    out = pid.Pout + pid.Iout + pid.Dout;

    //PID 计算结果归并
    if(out > pid.pwmcycle)
    {
        pid.OUT = pid.pwmcycle;
    }
    else if(out < 0)
    {
        pid.OUT = pid.OUT0;
    }
    else{
        pid.OUT = out;
    }

    pid.Ek_1 = pid.Ek;      //更新偏差

    pid.C10ms = 0;

}


void PIDOUT_init()     //pid输出引脚
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}



void PID_out()  //输出PID运算结果到负载---每1ms被调用一次算
{
    static u16 pw;
    pw++;
    if(pw >= pid.pwmcycle)
    {
        pw = 0;
    }

    if(pw < pid.OUT)
    {
        pwmout_0;       //加热
    }
    else
    {
        pwmout_1;   //停止加热
    }
}
