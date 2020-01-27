#ifndef _74HC595_C
#define _74HC595_C

#include "config.h"
#include "74hc595.h"
#include "infrared.h"
#include <stdlib.h>

#endif

bit tube_switch=0,date_switch=0,random_switch=0;
unsigned char tube_cnt=0;
unsigned char psec=0xff;

unsigned char random_tube=0;random_cnt=0;
unsigned char random_bit[6];

void transmit(unsigned char temp)
{
    char i;
    for(i=3;i>=0;i--)
    {
        ser=temp&0x08;
	    shcp=0;								      //移位输入
	    temp<<=1;
	    shcp=1;
    }
}

void tube_driver(unsigned char *tube_bit)
{
	char i;

//	oe_595=0;

    if(tube_switch)
	{
	    if(!random_switch)
		{
		    if(*(tube_bit+5)!=psec)							  
			{
			    for(i=5;i>=0;i--) transmit(*(tube_bit+i));	  //将数据发送至595
				nixie=~nixie;
				psec=*(tube_bit+5);							  //更新秒记录
			}
		}

		else
		{
			
			if(random_cnt++==12)
			{
			    random_cnt=0;
				random_bit[random_tube]=rand()%9;
				if(random_tube<6) 
				{
				    random_tube++;
				}

				else nixie=1;
			}
			
			for(i=0;i<random_tube;i++) transmit(*(random_bit+i));
			for(i=6;i>random_tube;i--) transmit(rand());
		}

		stcp=0;								          //上升沿触发595输出
        stcp=1;

	}
}

void tube_shutdown()							  //关闭
{
    unsigned char i;
	
	for(i=0;i<6;i++) transmit(15);

	stcp=0;
	stcp=1;

	tube_switch=0;
	date_switch=0;
	random_switch=0;
    environment=0;
	nixie=0;
	psec=0xff;

	random_tube=0;
	random_cnt=0;
//	oe_595=1;
}

void tube_monitor()								  //定时器中调用，用来监控打开时间
{
    if(tube_switch)
	{
	    if(tube_cnt<230) tube_cnt++;
		else 
		{
		 	tube_shutdown();
			tube_cnt=0;
		}
	}
	else tube_cnt=0;
}		  
