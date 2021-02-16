# MyPID
基于PID算法的温控系统（基于STM32f103）

IO引脚分配如下：
    
    
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
