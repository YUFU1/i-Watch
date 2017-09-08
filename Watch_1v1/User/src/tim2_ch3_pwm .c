#include "includes.h"
//PB10      实现motor震荡频率
void TIM2_CH3_PWM_Init(u16 psc,u16 arr)
{
       /********通道管脚复用功能配置*****/
	//打开PB的外设时钟
	RCC->AHB1ENR |=(1<<1);
	//模式寄存器
	GPIOB->MODER &=~(0x3<<20); //清零
	GPIOB->MODER |=(0x2<<20);  //复用功能
	//复用功能选择
	GPIOB->AFR[1] &=~((unsigned int)0xf<<8); //清零
	GPIOB->AFR[1] |= ((unsigned int)0x1<<8);   //复用成TIM2
	
	/******TIM2计数器工作配置********/
	//打开定时器外设时钟
	 RCC->APB1ENR |=(1<<0);
	//选择内部时钟作为计数器时钟源
	TIM2->SMCR &=~(0x7<<0);
	//写入分频值
	TIM2->PSC =psc-1;
	//写入重装载值
	TIM2->ARR =arr;
	//选择计数方式 向上计数
	TIM2->CR1 &=~(1<<4);
	
	/******输出通道功能配置*****/
	//写入捕获/比较寄存器中的数值
	TIM2->CCR3= arr/4; 
	
	//把通道配置为输出
	TIM2->CCMR2 &=~(0x3<<0);
	
	//选择是否打开影子功能
	TIM2->CCMR2 &=~(0x1<<3);
	
	//选择pwm波的输出模式
	TIM2->CCMR2 &=~(0x7<<4);
	TIM2->CCMR2 |=(0x6<<4);
	
	//选择通道的有效电平
	TIM2->CCER &=~(0x1<<9);
	
	//通道2输出使能
	TIM2->CCER |=(0x1<<8);
	
	//计数器使能
	TIM2->CR1  |=(0x1<<0);

}
