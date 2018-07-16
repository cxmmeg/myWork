#include<reg52.h>

#define lcd  P1             //���ݿ�

sbit lcd_psb =  P3^5;            //��/����ʽ����  0=serial 1=parallel
sbit lcd_id  =  P3^2;            //�Ĵ���ѡ������ 0=IR 1=DR 
sbit lcd_wr  =  P3^3;            //Һ����/д����  0=write 1=read
sbit lcd_en  =  P3^4;            //Һ��ʹ�ܿ���	  1 valid

bit lcd_busy();			//��æ
void initial_lcd(); //LCD��ʼ��
void clear_lcd();		//LCD����

void write_lcd_com(unsigned char com);   	//дָ��
void write_lcd_dat(unsigned char dat);		//д����
unsigned char read_lcd_dat();             //������
	
void delay_ms(unsigned int z);   												//��ʱ
void set_lcd_xy(unsigned char  x,unsigned char  y);			//��������

void write_lcd_hanzi(unsigned char x,unsigned char y,unsigned char code *dat);   //д����
void write_lcd_shuzi(unsigned char x,unsigned char y,unsigned char code *dat);	 //д����	

unsigned int test_point_exist(unsigned char x, unsigned char y, unsigned int value);	//
void draw_lcd_point(unsigned char x, unsigned char y, unsigned int value);						//
void clear_lcd_point(unsigned char x, unsigned char y, unsigned int value);						//