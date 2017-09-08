#include "includes.h"
#include "bmp.h"

//智能手表UI界面跳转 实现原理  结构体

// 具体页面功能函数实现


static struct SHOW s;
//static struct KEY k;
  
				struct KEY k;
void SHOWMENU()
{	
	
 /**************************************************************************/
if(k.flag==0)
{
	int i=3;
	while(i--)
	{
		OLED_clear();
	  OLED_showHzString(30,1,"加载中");
		OLED_showChString(8,3,"loading",16);
		delay_ms(100);
		OLED_showChString(68,3," *",16);
		delay_ms(100);
	  OLED_showChString(76,3," * ",16);
		delay_ms(100);
		OLED_showChString(84,3," *",16);
		delay_ms(100);
		
	}
	OLED_clear();
	OLED_showHzString(25,2,"智能手表");
	delay_ms(800);
	delay_ms(800);
	OLED_clear();
	OLED_showChString(32,3,"Welcome!",16);
	delay_ms(500);
	k.flag=1;
}

	
//时间	
if(k.flag==1)
{ 
  int i=0;
  u8 day;
  u8 hour,min,sec,ampm;
	u8 year,month,date,week;
	u8 tbuf[40];
	OLED_clear();	
      while(1)
			{				
			RTC_Get_Time(&hour,&min,&sec,&ampm);
			sprintf((char*)tbuf,"%02d:%02d:%02d",hour,min,sec); 
			OLED_showChString(25,0,tbuf,16);	
			RTC_Get_Date(&year,&month,&date,&week);
			sprintf((char*)tbuf,"20%02d-%02d-%02d",year,month,date); 
			OLED_showChString(20,2,tbuf,16);
			 day=(date+4)/7;
			if(day==0)
				 day=7;
switch(day)
  {
  case MONDAY:

	OLED_showChString(55,4,"Mon",16);
    break;
  case TUESDAY:
	OLED_showChString(55,4,"Tues",16);
    break;
  case WEDNESDAY:
	OLED_showChString(55,4,"Wed",16);
    break;
  case THURSDAY:
	OLED_showChString(55,4,"Thur",16);
    break;
  case FRIDAY:
	OLED_showChString(55,4,"Fri",16);
    break;
  case SATURDAY:
	OLED_showChString(55,4,"Sat",16);
    break;
  case SUNDAY:
	OLED_showChString(35,4,"Sun",16);
    break;
  default:
    break;		
  }	
			if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
						 k.flag=2;
						 return;
				}		
			}
			
		
}
/**************************************************************************/
//时间	
if(k.flag==6)
{ 
  int i=0;
  u8 day;
  u8 hour,min,sec,ampm;
	u8 year,month,date,week;
	u8 tbuf[40];
	OLED_clear();	
      while(1)
			{				
			RTC_Get_Time(&hour,&min,&sec,&ampm);
			sprintf((char*)tbuf,"%02d:%02d:%02d",hour,min,sec);
			OLED_showChString(40,6,tbuf,16);	                                                         
			if(hour>17 || hour <6 )
		  OLED_drawBMP(0,0,54,7,(u8*)snow);		
		else			
			OLED_drawBMP(0,0,54,7,(u8*)sun);	
			if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
						 k.flag=0;
						 return;
				}		
			}
			
		
}
/**************************************************************************/

	//心率
if(k.flag==2)
	{
		u8 uiBuf[40];
		u8 pulseBuf[24] = {0};
		OLED_clear();
		OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_BP); 
		delay_ms(1000);
		HP_OpenRate();   //打开心率测量
		//HP_OpenBp();
		delay_ms(1000);
		OLED_clear();	
		while(1)
				{	
					Ui_pulseDynamicUi();
					HP_GetRateResult();
					HP_GetResultData(pulseBuf);
					
					if(*pulseBuf==NULL)
					{ 
					TIM3_Init(10000-1,5000-1);  	
					OLED_showHzString(64,1,"测量中");
					delay_ms(100);
					OLED_showChString(76,2," *",16);
					delay_ms(100);
					OLED_showChString(84,2," * ",16);
					delay_ms(100);
					OLED_showChString(92,2," *",16);
					delay_ms(100);						
					}
					else
					{
					TIM3_Init(10000-1,5000-1);  	
					OLED_showChString(80,0,"test",16);
					delay_ms(100);
					OLED_showChString(76,2," *",16);
					delay_ms(100);
					OLED_showChString(84,2," * ",16);
					delay_ms(100);
					OLED_showChString(92,2," *",16);
					delay_ms(100);					
					}
					sprintf((char*)uiBuf,"plus:%03d",pulseBuf[7]); // //byte 7是心率结果
					OLED_showChString(55,5,uiBuf,16); 
      if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
						 k.flag=3;
						 return;
				}	
			}
		
	}
	
//血压
	
	/**************************************************************************/
if(k.flag==3)
{
	 int n=0;
   u8 BpBuf[24] = {0};
	 u8 uiBuf[40];
	  OLED_clear();
	  OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_BP); 
		delay_ms(1000);
		//HP_OpenRate();   //打开心率测量
		HP_OpenBp();
		delay_ms(1000);
		OLED_clear();
   while(1)
			{	
	 Ui_bpDynamicUi();		
	 HP_GetBpResult();                //获取血压测量状态
	 HP_GetResultData(BpBuf);
   if(0 == BpBuf[7])                   //byte 7是血压测量的状态:0测量中，1测量完成、2测量失败
	    {
					TIM3_Init(10000-1,5000-1);  	
          OLED_showHzString(64,0,"测量中");
					delay_ms(100);
					OLED_showChString(76,2," *",16);
					delay_ms(100);
					OLED_showChString(84,2," * ",16);
					delay_ms(100);
					OLED_showChString(92,2," *",16);
					delay_ms(100);
	     }		 
	 else if(1 == BpBuf[7])  
   { 
		 if(n==0)
		 OLED_clear();
		 OLED_showChString(60,0,"success",16);
		 sprintf((char*)uiBuf,"%03d/%03d", BpBuf[10], BpBuf[11]);//byte 10是血压测量结果的高压,byte 11是血压测量结果的低压	
		 OLED_showChString(60,2,uiBuf,16); 
		 n++;		 
	 }		 
	 else if(2 == BpBuf[7]) 
	 {		 
		 OLED_clear();
		 OLED_showChString(20,4,"    fail   ",16);
	 }
				if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
						{
						 k.flag=4;
             n=0;						
						 return;
				    }	  
				}
 }
	
}
 /**************************************************************************/

//温湿度

if(k.flag==4)
{
	
	TempHumiValue_t humi_temp_val ; 	//温湿度	
   u8 uiBuf[40];
	 OLED_clear();	
	while(1)
			{	
	//获取温湿度
  humi_temp_val = *SHT20_readTemAndHum();
  humi_temp_val = *SHT20_readTemAndHum();//获取温度
  sprintf((char*)uiBuf,"Tem %.1f",humi_temp_val.temperature); // 以整数显示
	OLED_showChString(56,0,uiBuf,16);
  sprintf((char*)uiBuf,"RH %.1f",humi_temp_val.humidity); // 以整数显示
	OLED_showChString(56,2,uiBuf,16);
  OLED_drawBMP(0,0,54,7,(u8*)sun);					
				
			 if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
					{
						 k.flag=5;
						 return;	
					}
				}	
			}

}
/**************************************************************************/

		 //计步
		if(k.flag==5)
		{
			
			u8 err;
			u8 hour,min,sec,ampm;
			u8 uiBuf[40];
			accValue_t accValue;
			static sportsInfo_t userSportsInfo;
			static u8 time_cnt;
			static timeStamp_t timeStamp;
			static u8 tempSecond;
			short aacx,aacy,aacz;
			OLED_clear();		
												//加速度传感器原始数据
			while(1)
					{	
			 Ui_stepDynamicUi();		
			 MPU_Get_Accelerometer(&aacx,&aacy,&aacz);			  //得到加速度传感器数据
 
			
		//		 sprintf((char*)uiBuf,"cx:%d",aacx); // 显示传感器的数据
		//		 OLED_showChString(0,2,uiBuf,16);
		//		 sprintf((char*)uiBuf,"cy:%d",aacy); // 显示传感器的数据
		//		 OLED_showChString(0,4,uiBuf,16);
		//		 sprintf((char*)uiBuf,"cz:%d",aacz); // 显示传感器的数据
		//		 OLED_showChString(0,6,uiBuf,16);

				RTC_Get_Time(&hour,&min,&sec,&ampm);		//获取当前RTC的值


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
				
				sprintf((char*)uiBuf,"sp:%04d ",userSportsInfo.stepCount); // 显示步数
				OLED_showChString(64,0,uiBuf,16); 
				
				
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
				 if(Key_ON==1)
						{
							delay_ms(50);
							if(Key_ON==1)
								 k.flag=6;
								 return;
						}	
			}


		}

}

static void Ui_pulseDynamicUi(void)
{
  static u8 shift_flag = 0;  //用于切换界面显示的标志位
  if(0 == shift_flag)
  {
	 shift_flag = 1;
     OLED_drawBMP(0,0,54,7,(u8*)Pulse_bmp_smll);	  //显示心率小图
  }
  else
  {
		shift_flag = 0;
    OLED_drawBMP(0,0,54,7,(u8*)Pulse_bmp_large);	  //显示心率大图
  }
  	 
}

static void Ui_bpDynamicUi(void)
{
  static u8 flag = 0;  //用于切换界面显示的标志位
  if(0 == flag)
  {
		 flag = 1;
     OLED_drawBMP(0,0,54,7,(u8*)bp1);	  //显示血压小图
  }
  else
  {
		flag = 0;
    OLED_drawBMP(0,0,54,7,(u8*)bp2);		//显示血压大图
  }
  	 
}

static void Ui_stepDynamicUi(void)
{
  static u8 stepFlag = 0;  //用于切换界面显示的标志位
  if(0 == stepFlag)
  {
		 stepFlag = 1;
     OLED_drawBMP(0,0,54,7,(u8*)step1);	 
  }
  else
  {
		stepFlag = 0;
    OLED_drawBMP(0,0,54,7,(u8*)step2);	 
  }
  	 
}


