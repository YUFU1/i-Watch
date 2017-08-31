#include "includes.h"

void  Delay_ms(u16 xms)
{
	 // 1、选择外部时钟作为滴答定时器的时钟源
	 SysTick->CTRL &=~(1<<2);
   // 2、把计数初始值写入重装载寄存器
   SysTick->LOAD = 12500 *xms;
   // 3、对当前值寄存器清零，让重装载值加载到当前值寄存器
	 SysTick->VAL =0;
   //4、打开定时器时钟，开始计数
   SysTick->CTRL |=(1<<0);	
   //5、等待当前值寄存器递减到0(表示定时时间到了)
   while((SysTick->CTRL &(1<<16))==0);
	 //6、关闭定时器时钟，停止计数 
	 SysTick->CTRL &=~(1<<0);
}


void  Delay_us(u32 xus)
{
	 // 1、选择外部时钟作为滴答定时器的时钟源
	 SysTick->CTRL &=~(1<<2);
   // 2、把计数初始值写入重装载寄存器
   SysTick->LOAD = 25*xus/2;
   // 3、对当前值寄存器清零，让重装载值加载到当前值寄存器
	 SysTick->VAL =0;
   //4、打开定时器时钟，开始计数
   SysTick->CTRL |=(1<<0);	
   //5、等待当前值寄存器递减到0(表示定时时间到了)
   while((SysTick->CTRL &(1<<16))==0);
	 //6、关闭定时器时钟，停止计数 
	 SysTick->CTRL &=~(1<<0);
}   
// 自定义延时
void delay(int num)
{
  while(num--);
}
