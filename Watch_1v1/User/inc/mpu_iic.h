#ifndef MPU_IIC_H
#define MPU_IIC_H
#include "stm32f4xx.h"

void IIC_init(void);
void IIC_start(void);
void IIC_stop(void);
u8 IIC_waitAck(void);
void IIC_ack(void);
void IIC_nAck(void);
void IIC_sendByte(u8 txd);
u8 IIC_readByte(unsigned char ack);

#endif

