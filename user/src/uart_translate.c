#ifndef _UART_TRANSLATE_C
#define _UART_TRANSLATE_C

#include "config.h"
#include "uart_translate.h"
#include "UART.h"
#include "alarm_set.h"
#include "DS1302.h"
#include "74hc595.h"
#include "5050rgb.h"
#include "pwm.h"

#endif

unsigned char str[RXD_MAX];

unsigned char code str0[]="return";
unsigned char code str1[]="set alarm";
unsigned char code str2[]="set time";
unsigned char code str3[]="date";
unsigned char code str4[]="on";
unsigned char code str5[]="off"; 
unsigned char code str6[]="random";
unsigned char code str7[]="led";
unsigned char code str8[]="pwm";  
unsigned char code *ptr[]={str0,str1,str2,str3,str4,str5,str6,str7,str8};
unsigned char code len[]={sizeof(str0)-1,sizeof(str1)-1,sizeof(str2)-1,sizeof(str3)-1,sizeof(str4)-1,
                          sizeof(str5)-1,sizeof(str6)-1,sizeof(str7)-1,sizeof(str8)-1};

unsigned char cmp_memory(unsigned char *str0,unsigned char *new,unsigned char len)
{
    unsigned char i;

	for(i=0;i<len;i++)
	{
	    if(str0[i]!=new[i]) break;
	}

	if(len==i) return 1;
	else return 0;
}

void uart_process()
{
    if((!rxd_flag)&&(rxd_complete)) 
	{
    	uart_read(str);
		if(cmp_memory(ptr[0],str,len[0])) uart_write(str);
		if(cmp_memory(ptr[1],str,len[1]))
		{
		    alarm_set(str+10,*(str+9)-'0');
			uart_write("alarm has been set at ");
			uart_write(str+10);
			uart_write("\r\n");
		}
		if(cmp_memory(ptr[2],str,len[2]))
		{

		}
		if(cmp_memory(ptr[3],str,len[3])) 
		{
		    date_switch=1;
			tube_switch=1;
			random_switch=0;
		}
		if(cmp_memory(ptr[4],str,len[4])) 
		{
		    tube_switch=1;
		}
		if(cmp_memory(ptr[5],str,len[5])) 
		{	
		    tube_shutdown(); 
		}
		if(cmp_memory(ptr[6],str,len[6]))
		{
		    date_switch=0;
			tube_switch=1;
			random_switch=1;
		}		
		if(cmp_memory(ptr[7],str,len[7]))
		{
		    configpwm((int)((str[3]-'0')*200+1),(int)((str[4]-'0')*200+1),(int)((str[5]-'0')*200+1));
			uart_write("yes\r\n");
		}
		if(cmp_memory(ptr[8],str,len[8]))
		{			
			pwm_state=(str[3]-'0')*10+(str[4]-'0');
			ini_pwm(pwm_state);
			uart_write("yes\r\n");									
		}
			
		rxd_complete=0;
	}
}