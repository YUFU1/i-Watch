#include "includes.h"
//PB10
void Motor_Init()
{
	//打开PB时钟线
	RCC->AHB1ENR |=(0x1<<1);
	
	//配置PB的输出模式
	GPIOB->MODER &=~(0x3<<20);
	GPIOB->MODER |=(0x1<<20);
	
	//配置输出类型
	GPIOB->OTYPER &=~(0x1<<10);
	
	//配置输出速率
	GPIOB->OSPEEDR &=~(0x3<<20);
	GPIOB->OSPEEDR |=(0x2<<20);
	
	//配置无上下拉
	GPIOB->PUPDR &=~(0x3<<20);
	GPIOB->PUPDR |=(0x1<<20);
	
}



