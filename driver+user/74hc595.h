#ifndef _74HC595_H
#define _74HC595_H

#ifndef _74HC595_C
#define _74HC595_C

extern void tube_driver(unsigned char *tube_bit);
extern void tube_shutdown();
extern void tube_monitor();

extern bit tube_switch,date_switch,random_switch;
extern unsigned char tube_cnt;

#endif

#endif
