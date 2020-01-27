#ifndef _ALARM_SET_C
#define _ALARM_SET_C

#include "config.h"
#include "alarm_set.h"
#include "ISP_IAP.h"
#include "buzz.h"
#include "DS1302.h"

#endif

#define ALARM_NUMBER 3

unsigned char xdata alarm1[4],alarm2[4],alarm3[4];
unsigned char xdata *ptr_alarm[]={alarm1,alarm2,alarm3};
unsigned char alarm_state[2]={0};

bit alarm_flag=0;

void ini_alarm()
{
    unsigned char i,j;

	for(i=0;i<ALARM_NUMBER;i++)
	{
	    for(j=0;j<4;j++)
		{
		    ptr_alarm[i][j]=rom_byte_read(i*4+j);
		}
	}
}

void alarm_set(unsigned char *alarm,unsigned char num)
{
    unsigned char i,j;

	for(i=0;i<4;i++) ptr_alarm[num-1][i]=alarm[i]-'0';

	rom_sector_erase(0x0000);
	for(i=0;i<ALARM_NUMBER;i++)
	{
		for(j=0;j<4;j++) rom_byte_write(i*4+j,ptr_alarm[i][j]);
	}
}

void alarm_detect()
{
	unsigned char i;
	static unsigned char index=0;

	if((1==song_finished)&&(0==alarm_state[0])) 				    //闹钟归位
	{
	    alarm_flag=0;
		alarm_state[0]=0;
	}		

    if((0==alarm_flag)&&(0==figure[4])&&(0==figure[5])) 
	{
		for(i=0;i<4;i++)											//闹钟比较
    	{
	    	if(ptr_alarm[index][i]!=figure[i]) break;
    	}
    	if(i==4)													//打开闹钟
	    {
		    alarm_state[0]=index+1;
			alarm_state[1]=2;
		    alarm_flag=1;
	    } 		
	}	
	
	if(alarm_state[1]!=0)
	{
	    if(song_finished)
		{
		    start_song(alarm_state[0]);
			alarm_state[1]--;
		}

		if(0==alarm_state[1]) alarm_state[0]=0;
	}	


	index++;
	if(index>ALARM_NUMBER-1) index=0;					 //
}