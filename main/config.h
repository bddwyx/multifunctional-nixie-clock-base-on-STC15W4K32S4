#ifndef _CONFIG_H
#define _CONFIG_H

#define mian main            //±£ÃüµÄ

#include <STC15F2K60S2.H>
#include <intrins.h>

#define Fosc 22118400
#define BAUD 115200

/* 5050rgb */
sbit led_r=P2^2;
sbit led_g=P2^3;
sbit led_b=P2^1;

/* DS1302 */
sbit io=P1^3;
sbit ce=P1^2;
sbit sclk=P1^5;

/* ºìÍâ */
sbit vs1838b=P3^2;

/* 74HC595 */
sbit ser=P0^1;	   //DS
sbit shcp=P0^2;
sbit stcp=P0^3;
sbit oe_595=P0^4;

/* Buzz	*/
sbit buzz=P0^0;

/* ¼üÅÌ */
sbit key_1=P2^4;
sbit key_2=P2^5;
sbit key_3=P2^6;
sbit key_4=P2^7;

/* DS18B20 */
sbit temp=P2^0;

/* ÄÊÅİ  */
sbit nixie=P0^6;

#endif