#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "24cxx.h"
#include "max6675.h"

/************************************************
PID 控制实验
作者：何蔚
IO引脚分配如下
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

//要写入到24c02的字符串数组
const u8 TEXT_Buffer[] = {"PID TEST"};
#define SIZE sizeof(TEXT_Buffer)

int main(void)
{
	u16 i=0;
	u8 datatemp[SIZE];
	
    delay_init();
    LCD_Init();
    LED_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);                              //串口初始化为115200
	Max6675_Init();
	AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
	AT24CXX_Read(0,datatemp,SIZE);
	LCD_ShowString(30, 80, 200, 16, 16, datatemp);
    LCD_ShowString(30, 50, 200, 16, 16, (u8 *)"PID TEST");

    while (1)
    {
		read_temper(); 
		
		
    }
}

#if 0

#endif
