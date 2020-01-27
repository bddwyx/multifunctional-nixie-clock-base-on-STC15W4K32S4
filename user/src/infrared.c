#ifndef _INFRARED_C
#define _INFRARED_C

#include "config.h"
#include "infrared.h"
#include "VS1838B.h"
#include "74hc595.h"
#include "alarm_set.h"
#include "buzz.h"
#include "UART.h"
#include "pwm.h"
#include "ISP_IAP.h"

#endif

unsigned int pre;				 //时刻缓存
unsigned char volatile environment=0;	 //功能
unsigned char vs_cnt=0;

bit vs_push=0;					 //按键按下标志

void ini_vs()
{
    EA=1;

	TMOD&=0X0F;
	TH0=0;
	TL0=0;

	ET0=1;
	EX0=1;
	PX0=1;	
	
	TR0=1;	 	
}

void ex0_isr() interrupt 0
{
	unsigned int T0;
	
	TR0=0;
	T0=TH0*256+TL0;
	vs_figure(T0);
	TR0=1;
}

void inter0() interrupt 1
{
    vs_cnt++;
			
	if(vs_cnt==5) 
	{
		vs_cnt=0;
		vs_flag=0;
		repeat_flag=0;
		vs_push=0;

		r_flag=0;									 //这两句非常关键，强干扰下的自动复位，没有的话会导致红外卡死
		pre_flag=0;
	}
}

/*
  以上是配合红外接收
                    */

unsigned char code vs_code[]={
    104,48,24,122,16,56,90,66,74,82,
	162,			//电源
	2,194,          //慢进快进
	168,144,		//-  +
	98,             //mode
	226,            //mute
	224,			//EQ
	152,			//RPT
    };

void vs_detect()											//红外信号检测
{
    static unsigned char vs_value=255;    

    if(vs_complete)
	{	
	    if((vs_value!=144)&&(vs_value!=168)&&(vs_value!=255))
		{
		    tube_switch=1;
		    tube_cnt=0;
		}

		if(255==vs_value) 
		{
		    vs_value=vs_value_get(vs);
			vs_push=1;
		}

		switch(vs_value)
		{
		    case 162:
				tube_shutdown();
				tube_cnt=0;

				break;

			case 98:
				if(vs_push)
				{
			    	vs_push=0;

			    	environment++;
			    	if(environment>3) environment=0;

			    	switch(environment)
					{
					    case 0:
						    date_switch=0; 
							random_switch=0;

							break;

                        case 1:
						    date_switch=1; 
							random_switch=0;

							break;

						case 2:
						    date_switch=0; 
							random_switch=1;
							nixie=0;

							break;

						case 3:
							date_switch=0; 
							random_switch=0;
							environment=0;
							tube_switch=0;
							//tube_shutdown();

							break;

					}
				}
				
			    break;

			case 226:
			    alarm_flag=0;
				alarm_state[1]=0;
				alarm_state[0]=0;
				stopbuzz();

				break;

			case 224:
			    if(vs_times>5)
				{
				    vs_times=5;
					uart_write("224");
				}

				if(vs_push)
				{
				    vs_push=0;
					uart_write("start");
					rgb_change=~rgb_change;
				}

				break;

			case 144:
			    if(vs_times>5)
				{
				    if(pwm_state<15)
					{
					    pwm_state++;
						ini_pwm(pwm_state);
						rom_sector_erase(0x0200);
	                    rom_byte_write(0x0200,pwm_state);
					}
					vs_times=5;
				}

				if(vs_push)
				{
				    vs_push=0;
					if(pwm_state<15)
					{
					    pwm_state++;
						ini_pwm(pwm_state);
						rom_sector_erase(0x0200);
	                    rom_byte_write(0x0200,pwm_state);
					}
				}

				break;

			case 168:
			    if(vs_times>5)
				{
				    if(pwm_state>1)
					{
					    pwm_state--;
						ini_pwm(pwm_state);
						rom_sector_erase(0x0200);
	                    rom_byte_write(0x0200,pwm_state);
					}
					vs_times=5;
				}

				if(vs_push)
				{
				    vs_push=0;
					if(pwm_state>1)
					{
					    pwm_state--;
						ini_pwm(pwm_state);
						rom_sector_erase(0x0200);
	                    rom_byte_write(0x0200,pwm_state);
					}
				}

				break;

			case 0:
			    uart_write("0");
				break;

			case 255:
			    uart_write("255");

			default :uart_write("default");
			         vs_value=255;

		}
		
		if(!repeat_flag)
		{
		    vs_value=255;
			vs_complete=0;
			vs_times=0;
			vs_push=0;
		}
			

	} 	
}
