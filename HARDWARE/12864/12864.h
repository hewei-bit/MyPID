#ifndef _12864_
#define _12864_
 #include"stm32f10x_conf.h"
 #include "stdio.h"
extern void delay_us(u16 us);
extern void LCD_drive(char x,unsigned  char y);	//lcd控制子函数 
//extern void re_waite(u8 y,u8 x,u8 w);  //反白//反白         行  开始列 宽度
extern void re_white(u8 H,u8 L,u8 w );   //反白子函数
//不反白         行  开始列 宽度
//extern void no_waite(u8 y,u8 x,u8 w);  //不反白
 //                行  列  字符  反白否 反白宽度
extern void show_string(u8 y,u8 x, u8 *p,char k,u8 w) ; //显示字符串

extern void CGRAM_fill(u16 d);  //绘图缓冲区填充
extern void LCD_Init(void);
extern void show_data(unsigned char add,  int n);//
extern void cancle_rewhite(char H) ; //取消某一行的所有反白
extern  void LCDcon(u8 a,u8 d);
extern void Show_string1(u8 add,const u8 *p);
void Show_float(u8 add,float t);
void Show_string(unsigned char add,  char *p);
void LCD_Clean(void);
#define LCDcon(a,d) LCD_drive(a,d)
void delay(u32 x);
void delay_us(u16 us);
void Show_number(u8 add,u16 t);


#endif

