/*需要外部函数防止超时，大概是180ms一个周期，重复码的位置重置计时器
  电平变化时调用figure_get()
  vs_complete=1且repeat_flag=0时，vs_value与vs_time有效
																	*/

/*
    高能预警
	前方逻辑炸弹
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

unsigned char vs_value_get(unsigned char *ptr)			   //得到红外码
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

	if((0x300<temp)&&(temp<0x4F0)) return 0;							   //写0
	    else if((0xA00<temp)&&(temp<0xE80)) return 1;					   //写1
	    	else if((0xE80<temp)&&(temp<0x1F00)) return 2;				   //重复码
		        else return 3;											   //鬼知道是啥
}

void vs_figure(unsigned int fig)	  //在中断中调用，处理红外信号
{
    static unsigned char index=0;
	static unsigned int pre,temp;

	r_flag=~r_flag;				 //奇偶标志
	if(0==r_flag) pre=fig;	 //下降沿捕捉
    else if(1==pre_flag)	     //开始捕捉
	    {
		    if(1==vs_flag)		 //检测正式开始标志
			{
			    if(0==repeat_flag)	  //重复码以前
				{
				    vs[index++]=time_process(fig,pre); 
				}
			}
			else if((0x1C00<fig-pre)&&(fig-pre<0x2400)) vs_flag=1;	   //检测起始码
		}
		else if(0==repeat_flag) pre_flag=1;		 //排除第一次的乱码
			else 
			{
			    temp=time_process(fig,pre);
				if(2==temp) 								 //重复码次数检测(由其他中断终止)
			    {
			        vs_times++;								 //刷新外部防超时定时器
		    		vs_cnt=0;
		    	}
			}

	if(index==32)
	{
	    index=0;
		pre_flag=0;
		repeat_flag=1;			 
		vs_complete=1;										  //通知外部函数
	}
}
