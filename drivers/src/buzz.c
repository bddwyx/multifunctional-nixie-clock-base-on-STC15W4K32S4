/*
  添加曲谱后需要更改start_song()
								*/

#ifndef _BUZZ_C
#define _BUZZ_C

#include "config.h"
#include "buzz.h"

#endif

#define time_multiper 5  //25 ms each

unsigned char beatcontrol=0,beatcount=0;		 //频率与节拍
unsigned char beat_size;						 //乐曲长度
bit song_finished=1,buzz_switch=0;				 //完成标志，蜂鸣器开关（其实功能一样）

unsigned int code note_freq[]={					 //中音，高音，低音1-7频率
0  ,523 ,587 ,659 ,698 ,784 ,880 ,988 ,
    1047,1175,1319,1397,1568,1760,1976,
	262 ,294 ,330 ,349 ,392 ,440 ,494    };

unsigned char code song_note1[]={
     1,2,3,1,0,        1,2,3,1,       3,4,5,       3,4,5,0,       5,6,5,4,3,1,          5,6,5,4,3,1,0,           1,19,1,0,        1,19,1      };

unsigned char code song_beat1[]={
35,  24,24,24,23,1,    24,24,24,24,   24,24,48,    24,24,47,1,    12,12,12,12,24,24,    12,12,12,12,24,23,1,     24,24,47,1,      24,24,48    };

unsigned char code song_note2[]={
	 1,0,1,0,	  5,0,5,0,	    6,0,6,0,      5,	 4,0,4,0,	   3,0,3,0,	    2,0,2,0,      1		  };

unsigned char code song_beat2[]={
25,	 11,1,11,1,   11,1,11,1,    11,1,11,1,    24,    11,1,11,1,    11,1,11,1,    11,1,11,1,   24	  };

unsigned char code song_note3[]={
   	     5,0,     5,0,5,0,5,0,6,	   5,4,3,2,	      1,     8,0,8,0,8,0,8,       9,0,9,0,8,        5,      6,0,6,7,8,7,6,           5,0,5,0,5,0,	   	 6,8,3,	        2,0,2,0,2,0,6,0,6,0,        5,4,3,2,1,2,           
  3,0,3,0,3,0,3,0,         2,0,2,0,1,0,1,0,           5,0,5,0,5,0,6,0,        5,4,3,2,          8,0,8,0,8,0,8,0,        7,0,7,0,6,0,5,0,         6,7,6,          9,0,9,0,8,0,7,6,            5,0,5,0,5,0,6,8,        
  3,          2,0,2,0,2,0,6,0,6,0,             5,0,5,0,5,0,3,2,         1,         19,1,0,1,2,3,            19,0,19,0,19,0,19,0,            2,0,2,0,2,0,2,3,      2,      3,2,1,21,     20,     19,0,19,0,19,2,0,2,    
  20,21,1,      20,21,1   };

unsigned char code song_beat3[]={
183,	 11,1,    17,1,5,1,11,1,12,    24,24,24,24,   48,    17,1,5,1,11,1,12,    11,1,11,1,24,     96,     23,1,12,12,24,12,12,   	 11,1,5,1,5,1,       12,12,48,      11,1,5,1,5,1,11,1,11,1,     12,6,6,12,12,96,          
  17,1,5,1,11,1,11,1,      11,1,11,1,11,1,11,1,       17,1,5,1,11,1,11,1,     12,12,12,12,      17,1,5,1,11,1,11,1,     11,1,11,1,11,1,11,1,     36,12,48,       23,1,23,1,23,1,12,12,       11,1,5,1,5,1,12,12,   
  48,         11,1,5,1,5,1,11,1,11,1,          11,1,5,1,5,1,12,12,      96,        24,23,1,24,24,96,        17,1,5,1,11,1,11,1,             11,1,5,1,5,1,12,12,   96,     24,24,24,24,   96,     11,1,23,1,12,17,1,6,
  12,12,96,     48,48,192 };


unsigned char *song_beat,*song_note;   //曲谱选择指针
																													 
void freq_set(unsigned int freq)
{
    unsigned int temp;				   //调整频率

    temp=65536-Fosc/24/freq;  
    T3L=(unsigned char)temp;
    T3H=(unsigned char)(temp>>8);
}

void open_buzz()
{
    TMOD&=0XF0;				   //开T1中断
    EA=1;
    TH1=0X88;
    TL1=0XA4;
    ET1=1;
    TR1=1;

	T4T3M&=0XF0;			   //开T3中断
	T4T3M|=0X08;
	IE2|=0X20;
}

void stopbuzz()
{
    T4T3M&=0XF7;			   //关闭T3中断
	buzz_switch=0;
	song_finished=1;
	beatcontrol=0;
	buzz=1;
}

void start_song(unsigned char i)	   //外部调用，开始选定乐曲
{
    buzz_switch=1;
	switch(i)
	{
	    case 1:song_beat=song_beat1;
	           song_note=song_note1;
			   break;
		case 2:song_beat=song_beat2;
	           song_note=song_note2;
			   break;
		case 3:song_beat=song_beat3;
	           song_note=song_note3;
			   break;
	}
	beat_size=*song_beat++;
    freq_set(note_freq[song_note[0]]);
	song_finished=0;
	open_buzz();
}

void runbuzz() interrupt 19
{
    buzz=~buzz;
}

void BeatCtr() interrupt 3
{
    beatcount++;
	if(beatcount==song_beat[beatcontrol])
	{
	    beatcount=0;
	    beatcontrol++;
	    if(beatcontrol>beat_size) 
		{
			stopbuzz();
		}
	    else freq_set(note_freq[song_note[beatcontrol]]);
    }
}
