#ifndef _TIMER_INIT_H
#define	_TIMER_INIT_H

#define TR0H 0xd8
#define TR0L 0xf0

#ifndef _TIMER_INIT_C
#define _TIMER_INIT_C

extern void timer0_config();
extern void configtimer1();

extern bit should_get_time_flag;

#endif

#endif
