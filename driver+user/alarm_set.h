#ifndef _ALARM_SET_H
#define _ALARM_SET_H

#ifndef _ALARM_SET_C
#define _ALARM_SET_C

extern void ini_alarm();
extern void alarm_set(unsigned char *alarm,unsigned char num);
extern void alarm_detect();

extern unsigned char xdata *ptr_alarm[];
extern unsigned char alarm_state[];
extern bit alarm_flag;

#endif

#endif
