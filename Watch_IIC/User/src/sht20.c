#include "includes.h"

 TempHumiValue_t temp_humi_Value;

static void SHT20_softReset(void)                    
{
	IIC_Start();                      //start I2C
	
	 IIC_Senddate(SHT20ADDR&0xfe);  //I2C address + write	
	if(IIC_Receiveack())
		return ;
	
	 IIC_Senddate(0xfe);                         //soft reset
		if(IIC_Receiveack())
		  return ;
		
	IIC_Stop();                       //stop I2C
}
 /*******************************************************************************
 * 函数名：SHT20_Init
 * 功能描述：初始化iic总线
 * 作者：Jahol Fan  
 * 参数说明：  
 * 返回值说明：成功返回测量的结果，失败返回 1
 * 修改记录：
*******************************************************************************/
 void SHT20_Init(void)
{
	SHT20_softReset();
}

/*******************************************************************************
 * 函数名：SHT20_setResolution
 * 功能描述：写寄存器，设置帧率
 * 作者：Jahol Fan  
 * 参数说明：  
 * 返回值说明：
 * 修改记录：
*******************************************************************************/
static void SHT20_setResolution(void)                    
{
  IIC_Start();                                                                        //Start I2C 
   
	 IIC_Senddate(SHT20ADDR&0xfe);            //I2C address + write + ACK
	 if(IIC_Receiveack())
		  return ;
  
	  IIC_Senddate(0xe6);                               //写用户寄存器
    if(IIC_Receiveack())
		  return ;
  
		 IIC_Senddate(0x83);  //设置分辨率   11bit RH% 测量时间：12ms(typ.) & 11bit T℃ 测量时间：9ms(typ.) 
    if(IIC_Receiveack())
		  return ;
   
		IIC_Stop();                                  //Stop I2C         
}
/*******************************************************************************
 * 函数名：SHT20_readTemOrHum
 * 功能描述：读取SHT20的温度或读取湿度测量值  
 * 作者：Jahol Fan  
 * 参数说明：  
 * 返回值说明：成功返回测量的结果，失败返回 1
 * 修改记录：
*******************************************************************************/
float SHT20_readTemOrHum(u8 commod)
{
	float temp;                 //温度
	u8  MSB,LSB;              //温度、相对湿度的寄存器数据
	float Humidity,Temperature; //温湿度的转换结果

	SHT20_setResolution();           //设置帧率8bit,9bit,10 bit,11bit ,12bit,13bit,14bit
	IIC_Start();                 //iic开始信号
	
    IIC_Senddate(SHT20ADDR&0xfe);   //写地址
     if(IIC_Receiveack())
		   return 0; 
		 
	  IIC_Senddate(commod);
     if(IIC_Receiveack())
		   return 0 ;  		 //写命令
		  do{
				IIC_Delay_us(6);                                    //延时
				IIC_Start();                                    //发送开始信号
			  IIC_Senddate(SHT20ADDR|0x01);      //无应答则整形，还在测量中，如果有应答，则结束当前循环
      
			}while(IIC_Receiveack());
			
			MSB = IIC_Receivedate();                          //读Data(MSB)，给应答ACK
      IIC_Sendack(0);	
			
			LSB = IIC_Receivedate();                          //读Data(LSB)，给应答ACK
			IIC_Sendack(0);
			
		   IIC_Receivedate();                               //读Checksum ，不给应答NACK 
			IIC_Sendack(1);	
			
			IIC_Stop();                                         //Stop I2C
			LSB &= 0xfc;                                       //Data (LSB) 的后两位在进行物理计算前前须置‘0’ 
			temp = MSB*256 + LSB;                              //十六进制转成十进制

			if (commod==((u8)READ_HUMI_COMD))                         //命令为读取湿度的命令
			{        
				/*-- calculate relative humidity [%RH] --*/ 
				Humidity =(temp*125)/65536-6;                   //公式: RH%= -6 + 125 * SRH/2^16
				return Humidity;                                //返回值：humidity
			}                                                                                                  
			else if(commod==((u8)READ_TEMP_COMD))                     //命令为读取温度的命令
			{        
				 /*-- calculate temperature [°C] --*/
				Temperature = (temp*175.72f)/65536-46.85f;       //公式:T= -46.85 + 175.72 * ST/2^16
				return Temperature;                             //返回值：temperature
			}
  return FAIL;
}
/*******************************************************************************
 * 函数名：SHT20_readTemAndHum
 * 功能描述：读取SHT20的温度和湿度测量值  
 * 作者：Jahol Fan  
 * 参数说明：  
 * 返回值说明：成功返回测量的结果，失败返回 1
 * 修改记录：
*******************************************************************************/

TempHumiValue_t * SHT20_readTemAndHum(void)
{
	temp_humi_Value.humidity = SHT20_readTemOrHum(READ_HUMI_COMD);//读取湿度
	temp_humi_Value.temperature = SHT20_readTemOrHum(READ_TEMP_COMD);//读取湿度
	return &temp_humi_Value;
}

