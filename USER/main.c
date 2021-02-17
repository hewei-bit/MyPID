#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "24cxx.h"
#include "max6675.h"
#include "pid.h"

/************************************************
PID ����ʵ��
���ߣ���ε
IO���ŷ�������:

    PIDout      ----    PB8
	MAX6675 
		PD2 	---- 	SCK
		PC12 	---- 	SO
		PC11	----	CS
		
	AT24C02
		PB6		----	IIC
		PB7		----	IIC
		
	LED0 	----	PB5 
	LED1	----	PE5
	
	KEY0~2	---- 	PE2~4
	WK_UP	----	GPIOA.0
		

************************************************/
u16 Kms10;

//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[] = {"PID TEST"};
#define SIZE sizeof(TEXT_Buffer)


int main(void)
{
	u16 i=0;
	u8 datatemp[SIZE];
	
    delay_init();
    LCD_Init();
    LED_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);                              //���ڳ�ʼ��Ϊ115200
	Max6675_Init();
    PID_Init();
	PIDOUT_init();


	AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
	AT24CXX_Read(0,datatemp,SIZE);
	LCD_ShowString(30, 30, 200, 16, 16, datatemp);
    LCD_ShowString(30, 50, 200, 16, 16, (u8 *)"PID TEST");
    LCD_ShowString(30, 70, 200, 16, 16, (u8 *)"��ǰֵ:");
    LCD_ShowString(30, 90, 200, 16, 16, (u8 *)"�趨ֵ:");
    LCD_ShowString(30, 110, 200, 16, 16, (u8 *)"PIDOUT:");
    while (1)
    {
		read_temper(); 
		PId_calc();
        LCD_ShowxNum(86,70,pid.Sv,16,16,0);
        LCD_ShowxNum(86,50,pid.Pv,16,16,0);
        LCD_ShowxNum(86,90,pid.OUT,16,16,0);
        
        //Display()
    }
}


