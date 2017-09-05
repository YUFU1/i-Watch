#include "includes.h"
/**
	1、中断分组
	2、写入具体的抢占值、响应值
	3、把具体的抢占值写入到寄存器
	4、使能
**/

/******************************************
函数名：MY_NVIC_init
函数参数：
u8 group :中断分组值  写入的参数为：7-组标号
    组标号 范围： 0---4
u8 PreemptVal :具体的抢占优先级数值
u8 SubVal  : 具体的响应优先级数值
IRQn_Type IRQn : 设置哪个中断的中断号
函数返回值：无
函数功能：实现自定义的NVIC中断触发配置函数
*******************************************/
void My_NVIC_Init(u8 group, u8 PreemptVal, u8 SubVal, IRQn_Type IRQn )
{
	u8 priority;//表示抢占、响应的合成值
	//设置中断分组值
	SCB->AIRCR &=~(((unsigned int)0XFFFF<<16)|(0X7<<8));//清零
	SCB->AIRCR |=(0X5FA<<16 | group <<8);
	//设置具体的抢占、响应数值
	priority =((PreemptVal & ((1<<(7-group))-1))<<(group-3)) |(SubVal &((1<<(group-3))-1));
	//把抢占、响应合成值写入寄存器
	NVIC->IP[(uint32_t)(IRQn)] = (priority << 4);    
  //中断号使能
	NVIC->ISER[(uint32_t)((int32_t)IRQn) >> 5] = (uint32_t)(1 << ((uint32_t)((int32_t)IRQn) & (uint32_t)0x1F)); 

}




