#include "includes.h"
#include "bmp.h"
/*************************************
          智能手表项目开发
**************************************/
/************************************/

int main()
{
	u8 err;
  u8 uiBuf[40];
	u8 hour,min,sec,ampm;
	u8 pulseBuf[24] = {0};
	u8 BpBuf[24] = {0};
  TempHumiValue_t humi_temp_val ; 	//温湿度	
	accValue_t accValue;
	static sportsInfo_t userSportsInfo;
	static u8 time_cnt;
	static timeStamp_t timeStamp;
	static u8 tempSecond;
	short aacx,aacy,aacz;	
										//加速度传感器原始数据
	Delay_Init(100);
  SPI_Init();	
	LED_Init();
	SHT20_Init();	
  OLED_Init(); 
	MPU_Init();
	HP_Init();
	TIM3_Init(10000-1,5000-1);
	RTC_Init();		 			//初始化RTC
	RTC_Set_WakeUp(4,0);		//配置WAKE UP中断,1秒钟中断一次
//	OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_BP); 
//	delay_ms(5000);
//	HP_OpenRate();   //打开心率测量
//	HP_OpenBp();
//	delay_ms(1000);	
  OLED_clear();

	
//	Motor_Init();
//  Key_Init();	
	        
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);


    //OLED_showChString(0,2,"123ad897",16);
	  // OLED_drawBMP(0,0,54,7,(u8*)step_bmp);
	while(1)
	{		
//   HP_GetBpResult();                //获取血压测量状态
//	 HP_GetResultData(BpBuf);
//   if(0 == BpBuf[7])                   //byte 7是血压测量的状态:0测量中，1测量完成、2测量失败
//		 OLED_showChString(10,4,"testing",16);  
//	 else if(1 == BpBuf[7])  
//   {
//		OLED_showChString(10,4,"success",16);
//		sprintf((char*)uiBuf,"%03d/%03d MMGH", BpBuf[10], BpBuf[11]);//byte 10是血压测量结果的高压,byte 11是血压测量结果的低压	
//		OLED_showChString(10,6,uiBuf,16); 		 
//	 }		 
//	 else if(2 == BpBuf[7])                  
//		 OLED_showChString(10,4,"fail   ",16);
//	 else 
//		 //do nothing
//		delay_ms(1000);	
//	
//		
////		//获取温湿度
//  humi_temp_val = *SHT20_readTemAndHum();
//  humi_temp_val = *SHT20_readTemAndHum();//获取温度
//  sprintf((char*)uiBuf,"Tem %.2f       RH %.2f",humi_temp_val.temperature,humi_temp_val.humidity); // 以整数显示
//	OLED_showChString(0,0,uiBuf,16); 	 


     MPU_Get_Accelerometer(&aacx,&aacy,&aacz);			  //得到加速度传感器数据
		 
		 sprintf((char*)uiBuf,"cx:%d",aacx); // 显示传感器的数据
		 OLED_showChString(0,2,uiBuf,16);
		 sprintf((char*)uiBuf,"cy:%d",aacy); // 显示传感器的数据
		 OLED_showChString(0,4,uiBuf,16);
		 sprintf((char*)uiBuf,"cz:%d",aacz); // 显示传感器的数据
		 OLED_showChString(0,6,uiBuf,16);
		 RTC_Get_Time(&hour,&min,&sec,&ampm); 					  //获取当前RTC的值
		
		if(tempSecond != timeStamp.second)					 //秒更新
		{
			tempSecond = timeStamp.second;
			timeStamp.twentyMsCount = 0 ;//20ms计数变量清零
		}
		else												  //秒不更新，1秒等于50*20ms
		{
			timeStamp.twentyMsCount ++;//20ms计数变量++
		}
		
		timeStamp.hour	 = hour;
		timeStamp.minute = min;
		timeStamp.second = sec;
		
		
		if(tempSecond != timeStamp.second)					 //秒更新
		{
			tempSecond = timeStamp.second;
			timeStamp.twentyMsCount = 0 ;//20ms计数变量清零
		}
		else												  //秒不更新，1秒等于50*20ms
		{
			timeStamp.twentyMsCount ++;//20ms计数变量++
		}
		
		timeStamp.hour	 = hour;
		timeStamp.minute = min;
		timeStamp.second = sec;
		
		//将三轴数据转换为以g为单位的数据
		accValue.accX = ((float)(int)aacx/16384) *10;
		accValue.accY = ((float)(int)aacy/16384) *10;
		accValue.accZ = ((float)(int)aacz/16384) *10; 
		userSportsInfo = *onSensorChanged(&accValue,&timeStamp,WatchInfo_getUserInfo(&err)); //调用计数算法
		
		sprintf((char*)uiBuf,"Step:%05d ",userSportsInfo.stepCount); // 显示步数
		OLED_showChString(0,0,uiBuf,16); 
		
		
		if(accValue.accX>=0)
		{ 
			sprintf((char*)uiBuf,"X:%02d ",(char)accValue.accX); // 以整数显示
			OLED_showChString(88,2,uiBuf,16);				
		}
	  else
		{
			sprintf((char*)uiBuf,"X:-%02d",(char)(-accValue.accX)); // 以整数显示
			OLED_showChString(88,2,uiBuf,16);				
		}

		
		if(accValue.accY>=0)
		{
			sprintf((char*)uiBuf,"Y:%02d ",(char)accValue.accY); // 以整数显示
			OLED_showChString(88,4,uiBuf,16);				
		}
	  else
		{
			sprintf((char*)uiBuf,"Y:-%02d",(char)(-accValue.accY)); // 以整数显示
			OLED_showChString(88,4,uiBuf,16);				
		}
		
		
		if(accValue.accZ>=0)
		{
			sprintf((char*)uiBuf,"Z:%02d ",(char)accValue.accZ); // 以整数显示
			OLED_showChString(88,6,uiBuf,16);				
		}
	  else
		{
			sprintf((char*)uiBuf,"Z:-%02d",(char)(-accValue.accZ)); // 以整数显示
			OLED_showChString(88,6,uiBuf,16);				
		}		

		
		delay_ms(20);  //以50Hz的频率去读取三轴加速度的XYZ轴加速度值
	
	}            	 


}













