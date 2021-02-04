#include "display.h"
#include "12864.h"
#include "pid.h"

extern u8 rtc[3];
void Show_clock()
{
 char s[10];
	sprintf(s,"%02d:%02d:%02d",rtc[0],rtc[1],rtc[2]);
	Show_string(0X9A,s) ; 
}


void Show_temperauter()
{
  char s[20];
  sprintf(s,"当前温度:% 3.1f ",pid.curr);	
	Show_string(0x90,s);
	sprintf(s,"设定温度:% 3.1f ",pid.set);	
	Show_string(0x88,s);
}





void Display()
{
  // Show_float(0x90,pid.Tcurr);
  Show_temperauter();
	//Show_clock();
	Show_number(0x98,pid.currpwm);
}



