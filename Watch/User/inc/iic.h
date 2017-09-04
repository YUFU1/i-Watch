#ifndef IIC_H
#define IIC_H
#include "stm32f4xx.h"

//SCL  PB8
#define  SCL_H  GPIOB->ODR |=(1<<8)
#define  SCL_L  GPIOB->ODR &=~(1<<8)
//SDA PB9
#define  SDA_H  GPIOB->ODR |=(1<<9)
#define  SDA_L  GPIOB->ODR &=~(1<<9)

void  IIC_SDA_Out(void);
void  IIC_SDA_Int(void);
void  IIC_Start(void);
void  IIC_Stop(void);
void IIC_Senddate(u8 date);
u8  IIC_Receivedate(void);
void IIC_Sendack(u8 ack);
u8 IIC_Receiveack(void);

#endif
