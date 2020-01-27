#ifndef _ISP_IAP_C
#define _ISP_IAP_C

#include "config.h"
#include "ISP_IAP.h"

#endif

void ISP_IAP_enable()
{
    EA=0;
    IAP_CONTR&=0x18;
    IAP_CONTR|=0x82;
} 

void ISP_IAP_disable()
{
    IAP_CONTR&=0x7f;
    IAP_TRIG=0x00;
    EA=1;
}

void IAPgoon()									  //IAP´¥·¢Æ÷
{
    ISP_IAP_enable();
    IAP_TRIG=0x5a;
    IAP_TRIG=0xa5;
    _nop_();
}

unsigned char rom_byte_read(unsigned int addr)
{
    IAP_ADDRH=(unsigned char)(addr>>8);
    IAP_ADDRL=(unsigned char)(addr&0xff);
    IAP_CMD&=0xfc;
    IAP_CMD|=0x01;
    IAPgoon();
    ISP_IAP_disable();
    return (IAP_DATA);
}

void rom_byte_write(unsigned int addr,unsigned char dat)
{
    IAP_ADDRH=(unsigned char)(addr>>8);
    IAP_ADDRL=(unsigned char)(addr&0xff);
    IAP_CMD&=0xfc;
    IAP_CMD|=0x02;
    IAP_DATA=dat;
    IAPgoon();
    ISP_IAP_disable();
}

void rom_sector_erase(unsigned int addr)
{
    IAP_ADDRH=(unsigned char)((addr&0xfe00)>>8);
    IAP_ADDRL=0x00;
    IAP_CMD&=0xfc;
    IAP_CMD|=0x03;
    IAPgoon();
    ISP_IAP_disable();
}
