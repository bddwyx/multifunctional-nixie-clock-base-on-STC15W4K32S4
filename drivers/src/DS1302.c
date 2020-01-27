#ifndef _DS1302_C
#define _DS1302_C

#include "config.h"
#include "DS1302.h"
#include "74hc595.h"

#endif

unsigned char time[8],figure[6];

void ds_bytewrite(unsigned char dat)
{
    unsigned char mask;
    for(mask=0x01;mask!=0;mask<<=1)
    {
        if((mask&dat)==0) io=0;
  	    else io=1;
	    sclk=1;
	    sclk=0;
    }
    io=1;
}

unsigned char ds_byteread()
{
    unsigned char mask;
    unsigned char dat=0;

    for(mask=0x01;mask!=0;mask<<=1)
    {
        if(io!=0) dat|=mask;
	    sclk=1;
	    sclk=0;
    }
    return dat;
}

void ds_write(unsigned char reg,unsigned char dat)
{
    ce=0;
    sclk=0;
    ce=1;
    ds_bytewrite((reg<<1)|0x80);
    ds_bytewrite(dat);
    ce=0;
}

void ds_burst_write(unsigned char *dat)
{
    unsigned char i;

    ce=0;
    sclk=0;
    ce=1;
    ds_bytewrite(0xbe);
    for(i=0;i<=7;i++) ds_bytewrite(dat[i]);
    ce=0;
}

unsigned char ds_read(unsigned char reg)
{
    unsigned char dat;

    ce=0;
    sclk=0;
    ce=1;
    ds_bytewrite((reg<<1)|0x81);
    dat=ds_byteread();
    ce=0;
    sclk=1;
    io=0;													   //大家都冷静冷静
    io=1;

    return dat;
}

void ds_burst_read(unsigned char *dat)
{
    unsigned char i;

    ce=0;
    sclk=0;
    ce=1;
    ds_bytewrite(0xbf);
    for(i=0;i<=7;i++) dat[i]=ds_byteread();
    ce=0;
    sclk=1;
    io=0;													   //大家都冷静冷静
    io=1;
}

void time_get()
{
    if(!random_switch) ds_burst_read(time);
    
	if(!date_switch)
   	{
        figure[0]=(time[2]>>4);								 //获取时间
	    figure[1]=(time[2]&0x0f);
	        figure[2]=(time[1]>>4);
	        figure[3]=(time[1]&0x0f);
	        figure[4]=(time[0]>>4);
	        figure[5]=(time[0]&0x0f);
				 												 

            tube_driver(figure);										 //输出时间
	}

	else 
	{
	    figure[0]=(time[6]>>4);										 //凑合用月日星期
        figure[1]=(time[6]&0x0f);       
        figure[2]=(time[4]>>4);
        figure[3]=(time[4]&0x0f);
        figure[4]=(time[3]>>4);
        figure[5]=(time[3]&0x0f);

        tube_driver(figure);
	}

}

/*
void ini_ds()
{
   unsigned char dat;
   unsigned char code ini_time[]={
                                  0x00,0x08,0x22,0x26,0x08,0x05,0x19   };
   
   ce=0;
   sclk=0;
   dat=ds_read(0);
   if((dat&0x80)!=0)
   {
      ds_write(7,0x00);
	  ds_burst_write(ini_time);
   }			
}	   */
