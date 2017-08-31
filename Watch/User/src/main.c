#include "includes.h"
/*************************************
          智能手表项目开发
**************************************/
/************************************/

int main()
{
	int i;
	LED_Init();
	LED_OFF;
	Motor_Init();
  Key_Init();	        
  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
	TIM2_CH3_PWM_Init(1000,100);
	while(1)
	{		
		 for(i=0;i<=100;i++)
		 {
		  TIM2->CCR3=i;
			TIM3->CCR2=i; 
		  Delay_ms(10);
		 }
		 for(i=100;i>=0;i--)
		   {
		  TIM2->CCR3=i;
			TIM3->CCR2=i;	 
		  Delay_ms(10);
		 }
		 
	}            	 


}













