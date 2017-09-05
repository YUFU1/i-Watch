#include "includes.h"
#include "bmp.h"
/*************************************
          智能手表项目开发
**************************************/
/************************************/

int main()
{
	//int i;
  u8 uiBuf[40];
	u8 pulseBuf[24] = {0};
	u8 BpBuf[24] = {0};
  TempHumiValue_t humi_temp_val ; 	//温湿度	
	Delay_Init(100);
  SPI_Init();	
	LED_Init();
	SHT20_Init();	
  OLED_Init();
	HP_Init();
	TIM3_Init(10000-1,5000-1);
	OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_PULSE);  //显示“请将传感器放于手腕背部，平心静气，5秒后心率测量打开”
	delay_ms(5000);
	HP_OpenRate();   //打开心率测量
	HP_OpenBp();
	delay_ms(1000);	
  OLED_clear();
	
//	Motor_Init();
//  Key_Init();	
	        
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);


    //OLED_showChString(0,2,"123ad897",16);
	  // OLED_drawBMP(0,0,54,7,(u8*)step_bmp);
	while(1)
	{		
   HP_GetBpResult();                //获取血压测量状态
	 HP_GetResultData(BpBuf);
   if(0 == BpBuf[7])                   //byte 7是血压测量的状态:0测量中，1测量完成、2测量失败
		 OLED_showChString(10,4,"testing",16);  
	 else if(1 == BpBuf[7])  
   {
		OLED_showChString(10,4,"success",16);
		sprintf((char*)uiBuf,"%03d/%03d MMGH", BpBuf[10], BpBuf[11]);//byte 10是血压测量结果的高压,byte 11是血压测量结果的低压	
		OLED_showChString(10,6,uiBuf,16); 		 
	 }		 
	 else if(2 == BpBuf[7])                  
		 OLED_showChString(10,4,"fail   ",16);
	 else 
		 //do nothing
		delay_ms(1000);	
	
		
//		//获取温湿度
  humi_temp_val = *SHT20_readTemAndHum();
  humi_temp_val = *SHT20_readTemAndHum();//获取温度
  sprintf((char*)uiBuf,"Tem %.2f       RH %.2f",humi_temp_val.temperature,humi_temp_val.humidity); // 以整数显示
	OLED_showChString(0,0,uiBuf,16); 	 
	
	}            	 


}













