#include "includes.h"

//SPI PB3 PB4 PB5

void SPI_Init()
{
//  //打开SPI的时钟线
	RCC->APB2ENR |=(0x1<<12);
	//打开PB的时钟线
	RCC->AHB1ENR |=(0x1<<1);
	
	//配置为输出
	GPIOB->MODER &=~(0x3f<<6);
	GPIOB->MODER |=(0x2a<<6);
	
	GPIOB->OSPEEDR &=~(0x3f<<6);
	GPIOB->OSPEEDR |=(0x2a<<6);
	
	GPIOB->AFR[0] &= ~(0xfff<< 12);
	GPIOB->AFR[0] |=  0x555 << 12; // af5功能
		
	//配置SPI工作在主模式
	SPI1->CR1 |=(0x1<<2);
	//配置SPI的软件从设备管理
	SPI1->CR1 |=(0x1<<9);
	SPI1->CR1 |=(0x1<<8);
	//配置波特率
	SPI1->CR1 |=(0x4<<3);
	//数据位数
	SPI1->CR1 &= ~(0x1<<11);
	//MSB在前
	SPI1->CR1 &=~(0x1<<7);
	//时钟极性 相位
	SPI1->CR1 &=~(0x3<<0);
	//SPI使能
	SPI1->CR1 |=(0x1<<6);


}
u8 SPI_ReceiveByte(u8 data)
{
	//等待发送缓冲区为空
  while((SPI1->SR &(0x1<<1))==0);
	
	SPI1->DR = data;
	//等待接收缓冲区为空
  while((SPI1->SR &(0x1<<0))==0);
	
	return (SPI1->DR);

}

