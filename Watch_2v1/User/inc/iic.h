#ifndef  MCU_IIC_H
#define  MCU_IIC_H

#include "stm32f4xx.h"

//SCL :PB8
#define SCL_L  GPIOB->ODR &=~(1<<8)
#define SCL_H  GPIOB->ODR |=(1<<8)

//SDA :PB9
#define SDA_L  GPIOB->ODR &=~(1<<9)
#define SDA_H  GPIOB->ODR |=(1<<9)


void IIC_SDAOut_init(void);
void IIC_SDAIn_init(void);
void  IIC_Delay_us(u32 xus);


void IIC_Start(void);
void IIC_Stop(void);
void MCU_IIC_Senddata(u8 data);
u8 MCU_IIC_Receivedata(void);
void MCU_IIC_Sendack(u8 ack);
u8 MCU_IIC_Receiveack(void);

#endif


