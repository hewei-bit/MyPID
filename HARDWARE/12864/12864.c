  

#include"stm32f10x_conf.h"
//#include"stm32f10x_lib.h"
#include"12864.h"
#include <stdio.H>
//PD8--4PIN(CS)
//PD9--5PIN(SID)
//PD10--6PIN(CLK)
extern u8 asc1[];
#define LCD_CS_1  	 GPIO_SetBits(GPIOC, GPIO_Pin_0) 	//	lcd4(cs)		
#define LCD_CS_0  	 GPIO_ResetBits(GPIOC, GPIO_Pin_0)

#define LCD_SID_1 	 GPIO_SetBits(GPIOC, GPIO_Pin_1)	//lcd5
#define LCD_SID_0    GPIO_ResetBits(GPIOC, GPIO_Pin_1)

#define LCD_CLK_1 	 GPIO_SetBits(GPIOC, GPIO_Pin_2) 	  //lcd6(clk)
#define LCD_CLK_0 	 GPIO_ResetBits(GPIOC, GPIO_Pin_2) 


#define LCD_RST_1 	 GPIO_SetBits(GPIOC, GPIO_Pin_4) 	  //lcd6(clk)
#define LCD_RST_0 	 GPIO_ResetBits(GPIOC, GPIO_Pin_4) 


#define LCD_PS_1 	 GPIO_SetBits(GPIOC, GPIO_Pin_5) 	  //lcd6(clk)
#define LCD_PS_0 	 GPIO_ResetBits(GPIOC, GPIO_Pin_5) 

// unsigned short lcd_buf[64][8];  //LCD缓冲区




// void 
//{
//     
//}   

unsigned char const ASC[]="0123456789ABCDEF";  



void send_8bit(u8 x)
{
 u8 i;
 for(i=0;i<8;i++)
 {
  LCD_CLK_0;
  if(x&0x80)
  LCD_SID_1;
  else
  LCD_SID_0;
  delay_us(5);
  LCD_CLK_1;
  delay_us(5);
  x<<=1;
 }			   
}

void LCD_drive(char x,unsigned  char y)	//lcd控制子函数
{
  unsigned char t;
  if(x==1)
  t=0xfa;
  else
  t=0xf8;
  LCD_CS_1;
 // delay(5);
  send_8bit(t);	 // delay(250);
  send_8bit(y&0xf0); //  delay(250);
  send_8bit((y<<4)&0xf0); // delay(250);
  LCD_CS_0;
  delay_us(200);
}


void Show_string(unsigned char add,  char *p)
{
 LCD_drive(0,0x30); 
 LCD_drive(0,add);	
 while((*p)!='\0')
 {
   LCD_drive(1,*p++);	
	 //delay_us(5); 
  }
}

void CGRAM_fill(u16 d)  //绘图缓冲区填充
{
  u8 x,y; 
  LCD_drive(0,0x34); 
  for(x=0;x<8;x++)
  {	
	  for(y=0;y<32;y++)
	  {        
	   
	        LCD_drive(0,0x80|y);
       LCD_drive(0,0x80|x);   
	    LCD_drive(1,d>>8);
	    LCD_drive(1,d&0xff);      	    
	  }      
  }
  for(x=8;x<16;x++)
  {	 
	  for(y=0;y<32;y++)
	  {        
	     LCD_drive(0,0x80|y);
         LCD_drive(0,0x80|x);
	    //    
	    LCD_drive(1,d>>8);
	    LCD_drive(1,d&0xff);      	    
	  }      
  }
 LCD_drive(0,0x36);
// delay(200000);
}

//////////////////////以下部分从AVR来

void re_white(u8 H,u8 L,u8 w )   //反白子函数
{   //第H(0-3)行第L(0-7)列开始将相邻的w个字符反白(每个字符16列像素)
  u8 y_add;
  u8 x_add;
  u8 x,y;
  switch(H)
  {
   case 0:y_add=0; x_add=L;    break;
   case 1:y_add=16;x_add=L;    break;
   case 2:y_add=0; x_add=L+8;  break;
   case 3:y_add=16;x_add=L+8;  break;
   default :break;
  }
  LCD_drive(0,0x34); //扩充指令图形显示
  for(x=x_add;x<x_add+w;x++)
  {
    for(y=y_add;y<y_add+16;y++)
    {
	   	 LCD_drive(0,0x80|y);
		 LCD_drive(0,0x80|x);
	     LCD_drive(1,0xff);
		 LCD_drive(1,0xff); 
    }
  }
  LCD_drive(0,0x36);//扩充指令开图形显示
} 
 void cancle_rewhite(char H)  //取消某一行的所有反白
{
  u8 y_add;
  u8 x_add;
  u8 x,y;
  switch(H)
  {
   case 0:y_add=0; x_add=0; break;
   case 1:y_add=16;x_add=0; break;
   case 2:y_add=0; x_add=8;  break;
   case 3:y_add=16;x_add=8; break;
   default :break;
  }
  LCD_drive(0,0x34); //扩充指令关图形显示
  for(x=x_add;x<x_add+8;x++)
  {
    for(y=y_add;y<y_add+16;y++)
    {
	   	 LCD_drive(0,0x80|y);
		 LCD_drive(0,0x80|x);
	          LCD_drive(1,0x0);
		 LCD_drive(1,0x00); 
    }
  }
  LCD_drive(0,0x36);//扩充指令开图形显示
}


void clear_line(char i)  //清除1行的字符显示
{
  u8 add;
   switch(i)
   {
    case 0: add=0x80;    break;
    case 1: add=0x90;   break;
    case 2: add=0x88;  break;
    case 3: add=0x98;  break;
  }
   LCD_drive(0,0x30); //基本指令
   LCD_drive(0,add);
   for(i=0;i<16;i++)
      LCD_drive(1,' ');
}


 //                行  列  字符  反白否 反白宽度
void show_string(u8 y,u8 x, u8 *p,char k,u8 w)  //显示字符串
{  //x=0-7;y=0-3;k=0:不反白，k=1：要反白
   u8 add,d;
   //k=w=0;
   switch(y)
   {
    case 0: add=0x80;break;
    case 1: add=0x90;break;
    case 2: add=0x88;break;
    case 3: add=0x98;break;
   } 
   add+=x;//得到字符串显示的开始地址
   LCD_drive(0,0x30);  //基本指令
   clear_line(y);      //清除该行的所有字符
   LCD_drive(0,add);   //写入显示开始的地址
   d=0;
   LCD_drive(0,0x30); 
   while(*p!=0)
   {
     LCD_drive(1,*p++);
     d++;
   } 
   cancle_rewhite(y);  //取消某一行的所有反白 
   if(k==1)
    re_white(y,x,w);   //反白指定部分
}





void LCD_Init()
{  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //开A口时钟
	

   GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	LCD_PS_0;
	delay_us(10000);
  LCD_RST_0;
	delay_us(10000);
 LCD_RST_1;
	delay_us(10000);

  LCD_drive(0,0x30); 
  delay_us(500);
  LCD_drive(0,0x0c);//0000 1101
  delay_us(500);
	
	 LCD_Clean();
	
//  LCD_drive(0,0x01);
//  delay_us(5000); 
//   CGRAM_fill(0X0);  //绘图缓冲区填充
}





void Show_string1(u8 add,const u8 *p)
{
  LCDcon(0,0x30);
  LCDcon(0,add);
  while(*p)
  {
    LCDcon(1,*p++);
  }
}

void Show_float(u8 add,float t)
{
  char s[10];
	sprintf(s,"% .1f ",t);
	Show_string1(add,(u8*)s);
}
void Show_number(u8 add,u16 t)
{
  char s[10];
	sprintf(s,"%04d ",t);
	Show_string1(add,(u8*)s);
}

void LCD_Clean()
{
  LCD_drive(0,0x30);//扩充指令开图形显示
	delay_us(10000);
	CGRAM_fill(0X0);  //绘图缓冲区填充
}


