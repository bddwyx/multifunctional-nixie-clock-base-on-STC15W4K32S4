#ifndef _VS1838B_H
#define _VS1838B_H

extern void vs_figure(unsigned int fig);
extern unsigned char vs_value_get(unsigned char *ptr);

extern bit vs_flag,vs_complete,repeat_flag,r_flag,pre_flag;
extern unsigned char vs_times;
extern unsigned char vs[32];

#endif