#include <12864.h>
#include <snake_resource.h>
#define num 7

//������������Һ������һ����Ľṹ��
struct she
{
	unsigned char x,y;
	unsigned int value;
	unsigned char direction;	
};

struct loop_queue  //��������ʵ��ѭ�����У��յ㲻�ᳬ��15�������Դ�Сѡ15���ԡ�
{    
	unsigned int front;
	unsigned int rear;
	unsigned int count;
	struct she dat[num];
};
//����Ϥ����ʵ��ѭ�����еĿ�����ֽ�ϻ�һ�²�������

struct she tou,wei,food; //�ߵ�ͷβ�ڵ�  ��ʳ��� 
struct loop_queue queue;//ѭ������  ��ת�����γɹյ� ���յ������  β�͵���յ���յ������ 

unsigned char flag_exit_game; //���ر�־  Ϊ1ʱ  ��̰������Ϸ���ز˵�
unsigned char flag_game_over; //������־  Ϊ1ʱ  ��ʾ��Ϸ�������� ͬʱʹ���ر�־Ϊ1
unsigned char tcs_key_flag;  //̰������һ���ƶ���   ֻ������һ�ΰ���  Ҳ����ֻ�ܲ���һ���յ�
unsigned char tcs_key_state; //���ڰ���״̬����ʵ��
unsigned int  tcs_df;  //̰���ߵ÷�
unsigned char tcs_stop;//̰�����ݶ����ܵ�ʵ��

unsigned char tcs_nd=2;  //̰�����Ѷȵ�ѡ��
unsigned char tcs_dt;  //̰���ߵ�ͼ��ѡ�� ��2����ȫ�ֱ���  ��menu����Ҫ�õ� 


void tcs_bianjie(unsigned int he);//̰������Ϸ��ͼ��ʵ�ֺͱ߽�
void timer0_initial();
void timer1_initial();

//ѭ�����еĻ�������
void queue_initial(struct loop_queue *q);  
void queue_in(struct loop_queue *q,struct she h)  ;
struct she queue_out(struct loop_queue *q)  ;

void tcs_game_initial();
void food_produce();

void tcs_game()
{
	struct she check;  //�����ݴ��߼����ƶ��ĵ�  �Ӷ������ж�
	unsigned int he;
	unsigned char flag;//flag��Ϊ�Ե�ʳ��ı�־

	flag_exit_game=0; 
	flag_game_over=0;
	tcs_key_state=0;
	tcs_df=0;
	tcs_stop=1;

//	draw_lcd_picture(&tcs_picture[0]); //̰������Ϸ����
//	delay_ms(2000);

	tcs_bianjie(tcs_dt); //̰������Ϸ�߽�
	tcs_game_initial();//̰���߳�ʼ��  ��Ҫ���趨��ͷ��β  ����ʾ��
	timer0_initial(); //��ʱ��0�����ڷ�ʽ2  8λ�Զ�װ��ֵ  ֻ�������ж� �������������
	timer1_initial(); //��ʱ��1�����ڷ�ʽ1	16λ     10ms�ж�һ��ɨ�����

	do
	{
		food_produce();//����һ������� ���漴����x y value3��ֵȷ��һ����Ϊʳ��
		he=test_point_exist(food.x,food.y,food.value);//�������ĵ�ĵط��Ƿ��Ѿ��е����
	}
	while(he==food.value);//���������������ߵ������Լ��߽��� �������ٲ���һ��  
	draw_lcd_point(food.x,food.y,food.value);//��ʾʳ�� �ȶ�ȡ���������xy����� �����ƻ��ֳ�
	
	queue_initial(&queue);//��ʼ��ѭ������  ʹ���п�  front rear ��ͷβָ��Ϊ0

	while(1)
	{
		if(flag_exit_game==1)//�����Ϸ�����а��·��ؼ�  ������������Ϸ  ���ز˵�
			break;
		if(flag_game_over==1)//�����Ϸ������������  ������������Ϸ ��ʾ�������� �����󷵻ز˵�
			break;
		
		ET1=1;   //����ɨ�谴��	  ̰������Ϸ�ѶȾ�����2���ƶ�֮��ļ��ʱ��  Ҳ���Ǽ�ⰴ����ʱ��
		tcs_key_flag=0; //�����񰴼�  �ڼ�ⰴ��ʱ����  ֻ��������һ���յ�  ������һ����Ч��
						//�����Ժ�  ����һ������� �����������ӹյ�
		while(tcs_stop==0);//�ݶ������»�ȡ��tcs_stop��ֵ  �Ӷ�ʵ����ͣ����
		switch(tcs_nd)
		{
			case 0:  {delay_ms(50); break;}//0�����̬�Ѷ�  �ߵ�2���ƶ�֮��ֻ��10ms�Ļ�������̰���
			case 1:  {delay_ms(100); break;}//�Ѷȼ�С  2���ƶ��������
			case 2:  {delay_ms(150); break;}
		}
		ET1=0; 

		switch(tou.direction)//���switch����������ͷ��x y valueֵ�Լ���ǰ��ͷ�ƶ��ķ��� 
							 //ȡ����ͷҪ�������һ����  ����check��  ���ж��Ƿ�ײǽ �Ե�ʳ�� ʲô�ġ�����
		{	
			case 0: { 	
						check.y=tou.y; 
						if(tou.value==0x0001)//x��ֵҪ�����ı�
						{
							if(tou.x==3)//����������Ļ���ұ߽�  ��ص���߽� 
								check.x=0;
							else if(tou.x==11)//����������Ļ���ұ߽�  ��ص���߽�
								check.x=8;
							else
								check.x=tou.x+1;
							check.value=0x8000;
						}
						else
						{
							check.x=tou.x;
							check.value=tou.value>>1;
						}
						 break ;
					}//->����y���� 

			case 1: {//����valueֵ���� 					 
						check.value=tou.value;
						if(tou.y==31) //��ͷ����������֮���ƶ�
						{
							if(tou.x<=3)//��ͷ�������ƶ�������
								check.x=tou.x+8;
							else 		//��ͷ�������ƶ�������
								check.x=tou.x-8;
							check.y=0;
						}
						else
						{
							check.y=tou.y+1;
							check.x=tou.x;  //��ͷ��xֵ����
					    }
						break ;
					}

			case 2: {//<-����y���� 	
						check.y=tou.y; 
						if(tou.value==0x8000)//x��ֵҪ�����ı�
						{
							if(tou.x==0)//����������Ļ����߽�  ��ص��ұ߽� 
								check.x=3;
							else if(tou.x==8)//����������Ļ����߽�  ��ص��ұ߽�
								check.x=11;
							else
								check.x=tou.x-1;
							check.value=0x0001;
						}
						else
						{
							check.x=tou.x;
							check.value=tou.value<<1;
						}
						 break ;
					}

			case 3: { //��	 ����value����
						check.value=tou.value;
						if(tou.y==0) //��ͷ����������֮���ƶ�
						{
							if(tou.x<=3)//��ͷ�������ƶ�������
								check.x=tou.x+8;
							else 		//��ͷ�������ƶ�������
								check.x=tou.x-8;
							check.y=31;
						}
						else
						{
							check.y=tou.y-1;
							check.x=tou.x;  //��ͷ��xֵ����
					    }
						break ;
					}	
		}			
		flag=0;//��ʼ���Ե�ʳ���־  ��ʾû�гԵ�	
		he=test_point_exist(check.x,check.y,check.value); // �����ͷ�ƶ�����һ�����Ƿ񼸾��е����
		if(he==check.value) //���ǰ��ĵ��Ѿ�����	�������ʳ�� ������ǽ������
		{
			if(	(check.x==food.x) && (check.y==food.y) && (check.value==food.value) )//�Ե�ʳ��
			{
				flag=1;//�Ե�ʳ��
				tcs_df++;
				write_lcd_shuzi(5,16,tcs_shuzi[tcs_df/100]       ); 			//��ʾ�����İ�λ
				write_lcd_shuzi(6,16,tcs_shuzi[ (tcs_df%100)/10] );				//			ʮ
				write_lcd_shuzi(7,16,tcs_shuzi[tcs_df%10]        );				//          ��
			
				food.direction=tou.direction;//ʳ�ﱾû�з��� ����Ϊ����������
				tou=food; //ʳ��ͳ�����ͷ��������ͷ�ķ�����Ȼ����
				 
				do
				{
					food_produce();
					he=test_point_exist(food.x,food.y,food.value);
				}
				while(he==food.value);  
				draw_lcd_point(food.x,food.y,food.value);//������˵��  ����ǲ�������ʾʳ��
			}
			else//ײ���������ǽ
			{
				flag_game_over=1; // ��Ϸ����
			}
		}
		else  //ʲô��ô������ ����ǰ��
		{
			check.direction=tou.direction;//��ô��������ͬ�� Ϊ�˱�����ͷ��ǰ���ƶ�����
			tou=check;
			draw_lcd_point(tou.x,tou.y,tou.value);//������ʱ����ͷ
		}

		//�����Ƕ�β�͵Ĳ���		
		
		if(flag==1)//����Ե�ʳ�� ֱ�ӽ�������ѭ�� β�Ͳ����κβ���
		{
		
		}
		else
		{
			if (  (wei.x == queue.dat[queue.front].x) && ( wei.y==queue.dat[queue.front].y ) && ( wei.value== queue.dat[queue.front].value)  ) //���β�͵���յ�
			{
			 	check=queue_out(&queue); 	
				wei.direction=check.direction; //β�Ͱ��չյ�ָʾ�ķ�����
			}
			else //���û�е���յ� β���ƶ��ķ��򲻱�
			{
					
			}						
									
			switch( wei.direction ) //�����β�͵��ƶ�  �Լ�β�ͽڵ����ݵ��޸�
			{
				case 0:	{//->����y����	
							clear_lcd_point(wei.x,wei.y,wei.value);
							if(wei.value==0x0001)//x��ֵҪ�����ı�
							{
								if(wei.x==3)//����������Ļ���ұ߽�  ��ص���߽� 
									wei.x=0;
								else if(wei.x==11)//����������Ļ���ұ߽�  ��ص���߽�
									wei.x=8;
								else
									wei.x=wei.x+1;
								wei.value=0x8000;
							}
							else
							{
								wei.value=wei.value>>1;
							}
							break;
						}
				case 1:	{//����valueֵ����	
							clear_lcd_point(wei.x,wei.y,wei.value);
							if(wei.y==31) //�ߴ���������֮���ƶ�
							{
								if(wei.x<=3)//�ߴ������ƶ�������
									wei.x=wei.x+8;
								else 		//�ߴ������ƶ�������
									wei.x=wei.x-8;
								wei.y=0;
							}
							else
							{
								wei.y=wei.y+1;
						    }
							break ;
							
					   	 }										
				case 2:	{//<-����y����   
							clear_lcd_point(wei.x,wei.y,wei.value);
							if(wei.value==0x8000)//x��ֵҪ�����ı�
							{
								if(wei.x==0)//����������Ļ����߽�  ��ص��ұ߽� 
									wei.x=3;
								else if(wei.x==8)//����������Ļ����߽�  ��ص��ұ߽�
									wei.x=11;
								else
									wei.x=wei.x-1;
								wei.value=0x0001;
							}
							else
							{
								wei.value=wei.value<<1;
							}
							break;
						 }
				case 3:	{//��	 ����value����  
							clear_lcd_point(wei.x,wei.y,wei.value); 
							if(wei.y==0) //�ߴ���������֮���ƶ�
							{
								if(wei.x<=3)//�ߴ������ƶ�������
									wei.x=wei.x+8;
								else 		//�ߴ������ƶ�������
									wei.x=wei.x-8;
								wei.y=31;
							}
							else
							{
								wei.y=wei.y-1;
					   		 }
							break;
						 }	
  			}
		}							
	}	
	TR0=0;
	TR1=0;
	ET1=0;  //�˳���Ϸʱ �ر���Ϸ�������õ��Ķ�ʱ��0��1  Ȼ��ʱ���ж�ҲҪ�ر�


}

//״̬��ʵ�ְ���   �ο��������ϱ��˵ļ�����
void timer1() interrupt 3
{	
	unsigned char tou_last_direction; //��¼��ͷԭ�����ƶ�����
	
	TR1=0;
	TH1=0xDC;		
	TL1=0x00;

	switch (tcs_key_state)
	{
		case 0:	{		// ������ʼ̬
					if ( (P2 & 0xfe) != 0xfe )   tcs_key_state = 1;	// �������£�״̬ת������ȷ��̬
						else	  tcs_key_state = 0;
					break;
				}
	
		case 1:	{			// ����ȷ��̬
					if ( (P2 & 0xfe) != 0xfe)
					{
						// �����԰��£���ʱȷ����¼һ����Ч����
							tcs_key_state = 2;	// ״̬ת�������ͷ�̬
							if(tcs_key_flag==0 )	 //�����ʱ�����񰴼�
							{
								tou_last_direction=tou.direction;
								if(tcs_stop == 1)
								{
									switch(P2 & 0xfe)
									{	
										case 0xfc:	break; // ȷ����  �������κβ���
										case 0xfa:	{  flag_exit_game=1;   break; }//���ؼ�  	 ������Ϸ ���ز˵�
										case 0xbe:	{  tou.direction=3;break; }//��
										case 0xee:	{  tou.direction=2;break; }//��
										case 0xde:	{  tou.direction=1;break; }//��
										case 0x7e:	{  tou.direction=0;break; }//->	 
										case 0xf6:  {  if(tcs_stop==0) tcs_stop=1; else tcs_stop=0; break;}//��ͣ��
									}
						
									if( (tou.direction==tou_last_direction) || (tou.direction+tou_last_direction==2) || (tou.direction+tou_last_direction==4) )
									//����������ǰ��˷����ƶ�   ���߰������ķ��������ƶ������෴ �����κβ��� �˴ΰ�����Ч
									{
										tou.direction=tou_last_direction; //   ��ԭ��ͷ���ƶ�����
									}
									else //�����¼��ͷ����Ϊ�յ�           
									{			
										queue_in(&queue,tou);
										tcs_key_flag=1; //�Ѿ�����һ�ΰ�����Ϣ ����ƶ��յ��Ѿ����� �رղ������ 
									}
								}
								else
								{
									if((P2 & 0xfe) == 0xf6)	tcs_stop = 1;
								}
							}

					}
					else
					{
						tcs_key_state = 0;	// ������̧��ת����������ʼ̬
						break;
					}
				}

		case 2:	{           //�ȴ���������״̬
						if ( (P2 & 0xfe) == 0xfe) tcs_key_state=0;	//�������ͷţ�ת����������ʼ̬
						else	  tcs_key_state = 2;
						break;
				}	
	}	 		
	TR1=1;
}

void tcs_bianjie(unsigned int he)
{
	unsigned char i,j;
	clear_lcd();
	for(i=0;i<=31;i++)
		for(j=0;j<=3;j++)
		{
			set_lcd_xy(j,i);
			write_lcd_dat(tcs_map[he][i*8+j*2]); 
			write_lcd_dat(tcs_map[he][i*8+j*2+1]);
		}
	for(i=0;i<=31;i++)
		for(j=8;j<=11;j++)
		{
			set_lcd_xy(j,i);
			write_lcd_dat(tcs_map[he][256+i*8+(j-8)*2]);
			write_lcd_dat(tcs_map[he][256+i*8+(j-8)*2+1]);
		}
	//�������ǻ���ͼ	

	write_lcd_hanzi(4,0,df[0]);
	write_lcd_hanzi(5,0,df[1]);

	write_lcd_shuzi(5,16,tcs_shuzi[tcs_df/100]       ); 			//��ʾ�����İ�λ
	write_lcd_shuzi(6,16,tcs_shuzi[ (tcs_df%100)/10] );				//			ʮ
	write_lcd_shuzi(7,16,tcs_shuzi[tcs_df%10]        );				//          ��


	write_lcd_hanzi(12,0,jb[0]);
	write_lcd_hanzi(13,0,jb[1]);

	switch(tcs_nd)
	{ 
		case 0 :  { write_lcd_hanzi(14,16,tcs_bt[0]); write_lcd_hanzi(15,16,tcs_bt[1]);  break;}
		case 1 :  { write_lcd_hanzi(14,16,tcs_kn[0]); write_lcd_hanzi(15,16,tcs_kn[1]);  break;}
		case 2 :  { write_lcd_hanzi(14,16,tcs_jd[0]); write_lcd_hanzi(15,16,tcs_jd[1]);  break;}
	}
}
void timer0_initial()
{ 	
	TMOD=(0xf0 & TMOD) | 0x01; //��ʱ��0 8λ�Զ�װ��ֵ(TH0->TL0)��ʱ��ģʽ   �������������
	TH0=0x00;
	TL0=0x00;
	TR0=1;   
}

void timer1_initial()
{ 	
	EA=1;
	TMOD= (0x0f & TMOD) | 0x10 ; //��ʱ��һ16λ��ʱ��ģʽ 	10ms�ж�һ��  ����ɨ�����
	TH1=0xDC;//10ms�ж�һ��
	TL1=0x00;
	TR1=1;   
}

void queue_initial(struct loop_queue *q)   
{   
    struct she check;
	unsigned int i;
	q->front =q->rear=0;   
    q->count = 0;
	check.x=0;
	check.y=0;
	check.value=0;
	check.direction=0;
	for(i=0;i<num;i++)
		queue.dat[i]=check;   
}   

void queue_in(struct loop_queue *q,struct she h)  
{   
        q->dat[q->rear] = h;   
        q->rear = (q->rear + 1) % num;   
        q->count = q->count + 1;   
}   
  
struct she queue_out(struct loop_queue *q)   
{   
        struct she he;
		he = q->dat[q->front];   
        q->front = (q->front + 1) % num;   
        q->count = q->count - 1;
		return (he);   
}  

void tcs_game_initial()
{
	unsigned char he;
	tou.x=0;
	tou.y=5;
	tou.value=0x0001;      //��ʼ����ͷ
	tou.direction=0;    // ��ʼ����ͷ�ƶ�����Ϊ���� 

	wei.x=0;
	wei.y=5;
	wei.value=0x0080;		//��ʼ����β
	wei.direction=0;
	
	set_lcd_xy(0,5);
	he=read_lcd_dat();
	he=read_lcd_dat();
	set_lcd_xy(0,5);
	write_lcd_dat(he);
	write_lcd_dat(0xff);
}

void food_produce()
{
	unsigned char code a[16]={0x0001,0x0002,0x0004,0x0008,	0x0010,0x0020,0x0040,0x0080,	0x0100,0x0200,0x0400,0x0800,	0x1000,0x2000,0x4000,0x8000};
	unsigned char code b[16]={0,1,2,3,8,9,10,11,0,1,2,3,8,9,10,11};
	    	
	food.x=b[ TL0 & 0x0f];  //ȡTL0�ĵ���λ ��0-15����ȷ��ʳ���xֵ
	food.y= (TL0 & 0x0f) + (TL0 & 0xf0)>>4 + 1;// ��0-31����ȷ��ʳ���yֵ
	food.value=a[TL0 & 0x0f]; //��0-15����   ���������ҳ�value��ֵ
}


