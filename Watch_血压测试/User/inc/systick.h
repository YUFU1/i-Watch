#ifndef SYSTICK_H
#define SYSTICK_H
#include "includes.h"

 void Delay_Init(u8 SYSCLK);
 void delay_us(u32 nus);
 void delay_xms(u16 nms);
 void delay_ms(u16 nms);
#endif

