#include "includes.h"

//PA7
void LED_Init(void)
{
	//打开PA的时钟线
	RCC->AHB1ENR |=(0x1<<0);
	
   //配置输出模式
	GPIOA->MODER &=~(0x3<<14);
	GPIOA->MODER |=(0x1<<14);
	
	//配置输出类型
	GPIOA->OTYPER &=~(0x1<<7);
	
	//配置输出速率
	GPIOA->OSPEEDR &=~(0x3<<14);
	GPIOA->OSPEEDR |=(0x2<<14);
	
	//配置无上下拉  上拉
	GPIOA->PUPDR &=~(0x3<<14);
	GPIOA->PUPDR |=(0x1<<14);
}


