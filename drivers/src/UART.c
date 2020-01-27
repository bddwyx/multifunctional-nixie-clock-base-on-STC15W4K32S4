#ifndef _UART_C
#define _UART_C

#include "config.h"
#include "UART.h"

#endif

#define RXD_MAX 30

bit txd_flag=0;								 //两者为1代表忙
bit rxd_flag=0;
bit rxd_complete=0;							 //rxd完成
bit rxd_overflow=0;							 //接收溢出
unsigned char rxd_index=0;					 //接收字符个数
unsigned char pdata buf_rxd[RXD_MAX];			 //接收缓冲

unsigned char TH2_ini,TL2_ini;
unsigned char cnt=0;						 //超时计数器

void uart_config(unsigned int baud)
{
    if(baud!=0x8400)
	{
	    TL2_ini=65536-Fosc/(baud*4);
	    TH2_ini=(65536-Fosc/baud/4)>>8;
	}
	else
	{
	    TL2_ini=0XF4;
		TH2_ini=0XFF;
	}
	
	EA=1;

	SCON=0X50;			  //开启接收
  	ES=1;			 
	AUXR|=0X15;			  //T2作为波特率发生器,T2速度加倍,T2开始计时

    T2L=TL2_ini;		  //初值
	T2H=TH2_ini;

}

void uart_write(unsigned char *buf)
{
    while(*buf!='\0')
    {
        while(txd_flag);
	    txd_flag=1;
	    SBUF=*buf++;	  
    }
}

void uart_read(unsigned char *buf)
{
    unsigned char i=0;	
    for(i=0;i<=rxd_index;i++)
    {
        *buf++=buf_rxd[i];
    }
	rxd_index=0;
}
			
void uart_inter() interrupt 4
{
    if(RI) 
    {
		buf_rxd[rxd_index++]=SBUF;
 	    RI=0;
		cnt=0;
	    rxd_flag=1;

		if(RXD_MAX==rxd_index) 
		{
		    rxd_overflow=1;	 //标记溢出
			buf_rxd[19]='\0';
		}
    }

    if(TI)
    {
        txd_flag=0;
	    TI=0;
    }
}
  
void uart_monitor()					  //串口空闲检测，在定时器中调用
{
	if(rxd_flag) cnt++;				  //串口1超时判定
	if(cnt>8)
	{
	    cnt=0;
	    rxd_flag=0;
		if(buf_rxd[rxd_index-1]!='\0') buf_rxd[rxd_index]='\0';
		rxd_complete=1;
	}				  
}											   

/*
extern void uart_action(unsigned char *buf,unsigned char len);		  //串口动作
*/
