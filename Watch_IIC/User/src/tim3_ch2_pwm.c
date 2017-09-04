#include "includes.h"

//PA7      实现呼吸灯

void TIM3_CH2_PWM_Init(u16 psc,u16 arr)
{
       /********通道管脚复用功能配置*****/
	//打开PA的外设时钟
	RCC->AHB1ENR |=(1<<0);
	//模式寄存器
	GPIOA->MODER &=~(0x3<<14); //清零
	GPIOA->MODER |=(0x2<<14);  //复用功能
	//复用功能选择
	GPIOA->AFR[0] &=~((unsigned int)0xf<<28); //清零
	GPIOA->AFR[0] |=((unsigned int )0x2<<28);   //复用成TIM3
	
	/******TIM3计数器工作配置********/
	//打开定时器外设时钟
	 RCC->APB1ENR |=(1<<1);
	//选择内部时钟作为计数器时钟源
	TIM3->SMCR &=~(0x7<<0);
	//写入分频值
	TIM3->PSC =psc-1;
	//写入重装载值
	TIM3->ARR =arr;
	//选择计数方式 向上计数
	TIM3->CR1 &=~(1<<4);
	
	/******输出通道功能配置*****/
	//写入捕获/比较寄存器中的数值
	TIM3->CCR2= arr/4; 
	
	//把通道配置为输出
	TIM3->CCMR1 &=~(0x3<<8);
	
	//选择是否打开影子功能
	TIM3->CCMR1 &=~(0x1<<11);
	
	//选择pwm波的输出模式
	TIM3->CCMR1 &=~(0x7<<12);
	TIM3->CCMR1 |=(0x6<<12);
	
	//选择通道的有效电平
	TIM3->CCER &=~(0x1<<5);
	
	//通道2输出使能
	TIM3->CCER |=(0x1<<4);
	
	//计数器使能
	TIM3->CR1  |=(0x1<<0);

}
