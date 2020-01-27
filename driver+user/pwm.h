#ifndef _PWM_H
#define _PWM_H

#ifndef _PWM_C
#define _PWM_C

extern void ini_pwm(unsigned char mode);
extern void pwm3_config(unsigned int r_dc);
extern void pwm4_config(unsigned int g_dc);
extern void pwm5_config(unsigned int b_dc);

extern unsigned char pwm_state;
extern bit rgb_change;

#endif

#endif


