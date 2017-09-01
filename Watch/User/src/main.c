#include "includes.h"
/*************************************
          智能手表项目开发
**************************************/
/************************************/

int main()
{
	//int i;
  SPI_Init();	
	LED_Init();
	LED_OFF;
//	Motor_Init();
//  Key_Init();	
	        
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);
	  OLED_Init();
	while(1)
	{		
//		 for(i=0;i<=100;i++)
//		 {
//		    TIM2->CCR3=i;
//			TIM3->CCR2=i; 
//		  Delay_ms(10);
//		 }
//		 for(i=100;i>=0;i--)
//		   {
//		    TIM2->CCR3=i;
//			TIM3->CCR2=i;	 
//		  Delay_ms(10);
//		 }
	  LED_ON;
		
    OLED_showHzString(0,0,"智能手表");
    OLED_showChString(0,3,"897",strlen("897"));		
	
	}            	 


}













