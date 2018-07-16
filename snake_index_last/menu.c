#include<12864.h>
#include<resource.h>

struct menu_index 	//�˵�ָ��
{
	unsigned char up_num;					//����
	unsigned char down_num;				//����
	unsigned char confirm_num;		//ȷ��
	unsigned char cansel_num;			//����
};


struct menu_index code menu_num[11]=
{
							//��һ��˵�
	{2,1,3,0},   	//0����ʼ��Ϸ
	{0,2,4,0},		//1��ѡ���ͼ
	{1,0,8,0},		//2��ѡ������

							//������Ϸ
	{0,0,0,0},		//3��������Ϸ
						
							
	{5,5,4,1},		//4���޵�ͼ
	{4,4,5,1},   	//5����ͼҼ
	//��ͼ3 4 δ��
	{5,7,6,1},		//6����ͼ��
	{6,4,7,1},		//7����ͼ��
						
							//ѡ���Ѷ�
	{10,9,8,2},		//8����̬
	{8,10,9,2},		//9������
	{9,8,10,2},		//10����
	
};


unsigned char present_menu_num; 			//�˵��ĳ�ʼ��
extern unsigned char flag_exit_game;	//���ر�־  Ϊ1ʱ  ��̰������Ϸ���ز˵�
extern unsigned char tcs_nd;					//̰�����Ѷȵ�ѡ��
extern unsigned char tcs_dt;					//̰���ߵ�ͼ��ѡ�� ��2����ȫ�ֱ��� 


void menu_change(unsigned char he);	//�����������ִ�е�ǰ�˵���ָʾ�Ĳ˵���Ҫ���еĲ���
void menu1();
void menu2();
void menu3();

void choose(unsigned char n);	//ѡ�еĶ���
void shadow(unsigned char n);	//Һ���ķ�����ʾ

void key_down(); 		//����
void tcs_game(); 		//��Ϸ
void game_over();		//��Ϸ����



void main()
{
	initial_lcd();	//��ʼ��

	clear_lcd();		//����
	
	present_menu_num = 0;
	menu_change(present_menu_num);//��ʾ�˵�

	while(1)
	{
		key_down();	
	}
	
}



void menu_change(unsigned char he)
{
	switch(he)
	{
		case 0 : { menu1();  shadow(0); break; }
		case 1 : { menu1();  shadow(1); break; }
		case 2 : { menu1();  shadow(2); break; }//0-2Ϊ�ڶ���˵�
															   
		case 3 : {
								tcs_game();
								if(flag_exit_game == 1)
								{
									present_menu_num = 0;
									menu1();  shadow(0);
									break;
								}  
								else
								{ 
									game_over();
									break;
								}
							}
		case 4 :  { menu2();  choose(0); tcs_dt = 0; break; }
		case 5 :  { menu2();  choose(1); tcs_dt = 1; break; }
	//	case 6 :  { menu2();  choose(2); tcs_dt = 2; break; }
		//case 7 :  { menu2();  choose(3); tcs_dt = 3; break; }    //4��7Ϊѡ��̰���ߵĵ�ͼ

		case 8  :  { menu3();  choose(0); tcs_nd = 0; break; }
		case 9  :  { menu3();  choose(1); tcs_nd = 1; break; }
		case 10 :  { menu3();  choose(2); tcs_nd = 2; break; }   //8-9Ϊѡ��̰���ߵ��Ѷ�
			
	}
}



void menu1()
{
	unsigned int i;
	clear_lcd();
	for(i=0;i<16;i++)
	{
		if(i<4)		write_lcd_hanzi(i,0,&ksyx[i][0]);
		if(i<4)		write_lcd_hanzi(i,16,&xzdt[i][0]);
		if( (i>=8) && (i<=11) )		write_lcd_hanzi(i,0,&xznd[i-8][0]);
	}
}


void menu2()
{
	unsigned int i;
	clear_lcd();
	for(i=0;i<16;i++)
	{
		if(	(i>=1) && (i<=3)  )		write_lcd_hanzi(i,0,&wdt[i-1][0]);
		if(	(i>=1) && (i<=3)  )		write_lcd_hanzi(i,16,&dty[i-1][0]);
//		if( (i>=9) && (i<=11) )		write_lcd_hanzi(i,0,&dte[i-9][0]);
//		if( (i>=9) && (i<=11) )		write_lcd_hanzi(i,16,&dts[i-9][0]);
	}
}


void menu3()
{
	unsigned int i;
	clear_lcd();
	for(i=0;i<16;i++)
	{
		if(	(i>=2) && (i<=3)  )		write_lcd_hanzi(i,0,&bt[i-2][0]);
		if(	(i>=2) && (i<=3)  )		write_lcd_hanzi(i,16,&kn[i-2][0]);
		if( (i>=10) && (i<=11) )		write_lcd_hanzi(i,0,&jd[i-10][0]);
	}
}



//������ 0 1 2 3 �ֱ�����ѡ�� 1  2 3 4�� ���жԹ��Ķ���
void choose(unsigned char n)
{
	unsigned char i,j,hui1,hui2;
	unsigned char x,y;
	unsigned int code he[16]={0x8000,0xc0000,0xe000,0xf000,	0xf800,0xfc00,0xfe00,0xff00,	0xff80,0xffc0,0xffe0,0xfff0,	0xfff8,0xfffc,0xfffe,0xffff};
	switch(n)
	{
		case 0:	{y=0;x=4;break;}
		case 1:	{y=16;x=4;break;}
		case 2:	{y=0;x=12;break;}
		case 3:	{y=16;x=12;break;}
	}
	write_lcd_hanzi(x-4,y,&jt[0]);
	for(i=0;i<=15;i++)
 	{
		delay_ms(20);
		hui1=he[i]>>8;
		hui2=he[i];
		for(j=y;j<=y+15;j++)
		{
			set_lcd_xy(x,j);
			write_lcd_dat(	(dg[(j-y)*2])&(hui1)	);
			write_lcd_dat(	(dg[(j-y)*2+1])&(hui2)	);
		}
	}
}


//������ 0 1 2 3   �ֱ�����������ʾ 1 2 3 4 ��
void shadow(unsigned char n)
{
	unsigned char he,hui,i,j;
	unsigned char x,y;
	switch(n)
	{
		case 0:	{y=0;x=0;break;}
		case 1:	{y=1;x=0;break;}
		case 2:	{y=0;x=1;break;}
		case 3:	{y=1;x=1;break;}
	}	
	for(i=0+y*16;i<=15+y*16;i++)	
		for(j=0+x*8;j<=7+x*8;j++)
		{
			set_lcd_xy(j,i);
			he=read_lcd_dat();
			he=read_lcd_dat();
			hui=read_lcd_dat();
			he=he^(0xff);
			hui=hui^(0xff);
			set_lcd_xy(j,i);
			write_lcd_dat(he);
		  write_lcd_dat(hui);
		}
}




void game_over()
{
	unsigned int i;
	clear_lcd();
	for(i=0;i<16;i++)
	{
		if(i<7)		write_lcd_hanzi(i,16,&sbnbjcs[i][0]);
		if( (i>=9) && (i<=15) )		write_lcd_hanzi(i,0,&dxqcxlg[i-9][0]);
	}	
}




void key_down()
{
	unsigned char h;
	if((P2&0xfe)!=0xfe)
	{
		delay_ms(10);
		if ((P2&0xfe)!=0xfe) 
		{
			h=P2&0xfe;
			switch(h)
			{
				case 0xfc:	{
								present_menu_num=menu_num[present_menu_num].confirm_num;
								menu_change(present_menu_num);
								break;
							}	// ȷ����
	
				case 0xfa:	{
								present_menu_num=menu_num[present_menu_num].cansel_num;
								menu_change(present_menu_num);
								break;
							}	//���ؼ�

				case 0xbe:	{
								present_menu_num=menu_num[present_menu_num].up_num;
								menu_change(present_menu_num);
								break;
							}	//��

				case 0xee: 	break;	//��

				case 0xde:  {
								present_menu_num=menu_num[present_menu_num].down_num;
								menu_change(present_menu_num);
								break;
							}		//��

				case 0x7e:  break;	//->
			}
			while( (P2&0xfe)!=0xfe );
			P2=0xff;
			delay_ms(10);
		}
				
	}
}

