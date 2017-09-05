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

void TIM3_IRQHandler(void)
{	
	u8 hour,min,sec,ampm;
	u8 year,month,date,week;
	u8 tbuf[40];


	if(TIM3->SR&0X0001)//溢出中断
	{
      GPIOA->ODR	^= 1 << 7; //每按一次按键，就取反LED灯的状态
//			RTC_Get_Time(&hour,&min,&sec,&ampm);
//			sprintf((char*)tbuf,"%02d:%02d:%02d",hour,min,sec); 
//			OLED_showChString(0,0,tbuf,16);	
//			RTC_Get_Date(&year,&month,&date,&week);
//			sprintf((char*)tbuf,"20%02d-%02d-%02d",year,month,date); 
//			OLED_showChString(0,2,tbuf,16);		
//			sprintf((char*)tbuf,"NO: %d week",week); 
//			OLED_showChString(0,4,tbuf,16);	
	

	}	
	TIM3->SR&=~(1<<0);//清除中断标志位		
}
//通用定时器3中断初始化,定时器除2/3/4/5定时器为50M外，其余为100M
void TIM3_Init(u16 arr,u16 psc)
{
	u32 pro;
  RCC->APB1ENR|=1<<1; //TIM3时钟使能	  
  TIM3->ARR=arr;		//设定计数器自动重装值 
  TIM3->PSC=psc;		//预分频器	 
  TIM3->CNT = 0;        //Jahol Fan 重新初始化就会重新计数
  TIM3->DIER|=1<<0;	//允许更新中断	  
  TIM3->CR1|=0x01;	//使能定时器3
	//抢占优先级2bit  子优先级2bit
	NVIC_SetPriorityGrouping(5);//设置中断优先级分组
	pro = NVIC_EncodePriority(5, 2, 0);//抢占优先级的级别：2级 、子优先级级别：0级
	NVIC_SetPriority(TIM3_IRQn, pro);//设置优先级

	
	NVIC_EnableIRQ(TIM3_IRQn);//NVIC中断通道使能。							 
}
