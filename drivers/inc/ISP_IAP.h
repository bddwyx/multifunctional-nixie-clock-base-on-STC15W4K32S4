#ifndef _ISP_IAP_H
#define _ISP_IAP_H

/*
sfr ISP_DATA=0xe2;
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;								   \\stc89c52里面已经定义了
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
*/

#ifndef _ISP_IAP_C
#define _ISP_IAP_C

extern unsigned char rom_byte_read(unsigned int addr);
extern void rom_byte_write(unsigned int addr,unsigned char dat);
extern void rom_sector_erase(unsigned int addr);

#endif

#endif
