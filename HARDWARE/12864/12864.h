#ifndef _12864_
#define _12864_
 #include"stm32f10x_conf.h"
 #include "stdio.h"
extern void delay_us(u16 us);
extern void LCD_drive(char x,unsigned  char y);	//lcd�����Ӻ��� 
//extern void re_waite(u8 y,u8 x,u8 w);  //����//����         ��  ��ʼ�� ���
extern void re_white(u8 H,u8 L,u8 w );   //�����Ӻ���
//������         ��  ��ʼ�� ���
//extern void no_waite(u8 y,u8 x,u8 w);  //������
 //                ��  ��  �ַ�  ���׷� ���׿��
extern void show_string(u8 y,u8 x, u8 *p,char k,u8 w) ; //��ʾ�ַ���

extern void CGRAM_fill(u16 d);  //��ͼ���������
extern void LCD_Init(void);
extern void show_data(unsigned char add,  int n);//
extern void cancle_rewhite(char H) ; //ȡ��ĳһ�е����з���
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

