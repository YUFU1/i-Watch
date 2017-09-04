#include "includes.h"

//PA0

void Key_Init()
{
                   //打开PA的时钟线
	RCC->AHB1ENR |=(0x1<<0);
	
   //配置输入模式
	GPIOA->MODER &=~(0x3<<0);
	
	//配置无上下拉  上拉
	GPIOA->PUPDR &=~(0x3<<0);
	GPIOA->PUPDR |=(0x1<<0);
}


