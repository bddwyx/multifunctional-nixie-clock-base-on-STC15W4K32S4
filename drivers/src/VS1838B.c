/*��Ҫ�ⲿ������ֹ��ʱ�������180msһ�����ڣ��ظ����λ�����ü�ʱ��
  ��ƽ�仯ʱ����figure_get()
  vs_complete=1��repeat_flag=0ʱ��vs_value��vs_time��Ч
																	*/

/*
    ����Ԥ��
	ǰ���߼�ը��
				   */

#ifndef _VS1838B_C
#define _VS1838B_C

#include "VS1838B.h"
#include "config.h"

#endif

extern unsigned char vs_cnt;

bit vs_flag=0,r_flag=0,vs_complete=0,repeat_flag=0,pre_flag=0;

unsigned char vs_times=0;
unsigned char vs[32]={0};

unsigned char vs_value_get(unsigned char *ptr)			   //�õ�������
{
    unsigned char i;
	unsigned char vs_value=0;

	for(i=16;i<24;i++)
	{
	    if(ptr[i]==ptr[i+8]) break;
	}
	if(24==i)
	{		   
	    for(i=16;i<24;i++)
		{
		    vs_value=vs_value*2+ptr[i];
		}
	}
	
	return vs_value;
}

unsigned char time_process(unsigned int fig,unsigned int pre)
{
	unsigned int temp;

	if(fig>pre) temp=(fig-pre); 
	    else temp=(fig-pre+65536);

	if((0x300<temp)&&(temp<0x4F0)) return 0;							   //д0
	    else if((0xA00<temp)&&(temp<0xE80)) return 1;					   //д1
	    	else if((0xE80<temp)&&(temp<0x1F00)) return 2;				   //�ظ���
		        else return 3;											   //��֪����ɶ
}

void vs_figure(unsigned int fig)	  //���ж��е��ã���������ź�
{
    static unsigned char index=0;
	static unsigned int pre,temp;

	r_flag=~r_flag;				 //��ż��־
	if(0==r_flag) pre=fig;	 //�½��ز�׽
    else if(1==pre_flag)	     //��ʼ��׽
	    {
		    if(1==vs_flag)		 //�����ʽ��ʼ��־
			{
			    if(0==repeat_flag)	  //�ظ�����ǰ
				{
				    vs[index++]=time_process(fig,pre); 
				}
			}
			else if((0x1C00<fig-pre)&&(fig-pre<0x2400)) vs_flag=1;	   //�����ʼ��
		}
		else if(0==repeat_flag) pre_flag=1;		 //�ų���һ�ε�����
			else 
			{
			    temp=time_process(fig,pre);
				if(2==temp) 								 //�ظ���������(�������ж���ֹ)
			    {
			        vs_times++;								 //ˢ���ⲿ����ʱ��ʱ��
		    		vs_cnt=0;
		    	}
			}

	if(index==32)
	{
	    index=0;
		pre_flag=0;
		repeat_flag=1;			 
		vs_complete=1;										  //֪ͨ�ⲿ����
	}
}
