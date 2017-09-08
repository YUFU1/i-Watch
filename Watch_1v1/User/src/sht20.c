#include "includes.h"  

/*******************************************************************************
 * 函数名：SHT20_softReset
 * 功能描述：SHT20软件复位，
 * 参数说明：  无
 * 返回值说明：无

*******************************************************************************/
void SHT20_softReset(void)                    
{
	IIC_Start();                      //start I2C
	MCU_IIC_Senddata(SHT20_WRITEADDR);  //I2C address + write
	//MCU等待接收应答信号
	if(MCU_IIC_Receiveack())
	{
		 //无应答
		 return  ;
	}
	//MCU发送复位指令
	MCU_IIC_Senddata(0xfe);                 //soft reset
	//MCU等待接收应答信号
	if(MCU_IIC_Receiveack())
	{
		 //无应答
		 return  ;
	}
	IIC_Stop();                       //stop I2C
}
 /*******************************************************************************
 * 函数名：SHT20_Init
 * 功能描述：对SHT20进行软复位初始化 
 * 参数说明：  
 * 返回值说明：无
 * 修改记录：
*******************************************************************************/
void SHT20_Init(void)
{
	SHT20_softReset();
}
 
/*******************************************************************************
 * 函数名：SHT20_setResolution
 * 功能描述：写寄存器，设置帧率
 * 参数说明：  
 * 返回值说明：
 * 修改记录：
*******************************************************************************/
void SHT20_setResolution(void)                    
{
  IIC_Start(); 	//Start I2C 
	MCU_IIC_Senddata(SHT20_WRITEADDR);  // I2C address + write
	//MCU等待接收应答信号
	if(MCU_IIC_Receiveack())
	{
		 //无应答
		 return  ;
	}
	MCU_IIC_Senddata(0xe6);  //写寄存器
	//MCU等待接收应答信号
	if(MCU_IIC_Receiveack())
	{
		 //无应答
		 return  ;
	}
	MCU_IIC_Senddata(0x83);  //设置分辨率  
	//MCU等待接收应答信号
	if(MCU_IIC_Receiveack())
	{
		 //无应答
		 return  ;
	}
  IIC_Stop();         //Stop I2C         
}
/*******************************************************************************
 * 函数名：SHT20_readTemOrHum
 * 功能描述：读取SHT20的温度或读取湿度测量值  
 * 参数说明：  
 * 返回值说明：成功返回测量的结果，
 * 修改记录：
*******************************************************************************/
float SHT20_readTemOrHum(u8 commod)
{
	float temp;                 //温度
	
	u8  MSB,LSB;              //温度、相对湿度的寄存器数据
	float Humidity,Temperature; //温湿度的转换结果

	SHT20_setResolution();           //设置帧率8bit,9bit,10 bit,11bit ,12bit,13bit,14bit
	IIC_Start();                 //iic开始信号
	MCU_IIC_Senddata(SHT20_WRITEADDR&0xfe);  //I2C address + write
	//MCU等待接收应答信号
	if(MCU_IIC_Receiveack())
	{
		 //无应答
		 return  0;
	}
	MCU_IIC_Senddata(commod);  //发送测量温度/湿度命令
	//MCU等待接收应答信号
	if(MCU_IIC_Receiveack())
	{
		 //无应答
		 return 0 ;
	}
	do
	{
		delay_us(6);         //延时
		IIC_Start();        //发送开始信号
		MCU_IIC_Senddata(SHT20_READADDR|0x01);
	}while(MCU_IIC_Receiveack());  //无应答则整形，还在测量中，如果有应答，则结束当前循环

	MSB = MCU_IIC_Receivedata();    //读Data(MSB)
	MCU_IIC_Sendack(0);      //给应答ACK
	
	LSB = MCU_IIC_Receivedata();  //读Data(LSB)
	MCU_IIC_Sendack(0);      //给应答ACK
	
	MCU_IIC_Receivedata();    //读Checksum ，
	MCU_IIC_Sendack(1); //不给应答NACK 
	
	IIC_Stop();                //Stop I2C
	LSB &= 0xfc;      //Data (LSB) 的后两位在进行物理计算前前须置‘0’ 
	temp = MSB*256 + LSB;           //十六进制转成十进制
           
	if (commod==((u8)READ_HUMI_COMD))  //命令为读取湿度的命令
	{        
	
		Humidity =(temp*125)/65536-6;                   //公式: RH%= -6 + 125 * SRH/2^16
		return Humidity;                                //返回值：humidity
	}                                                                                                  
	else if(commod==((u8)READ_TEMP_COMD))                     //命令为读取温度的命令
	{        
		 /*-- calculate temperature [°C] --*/
		Temperature = (temp*175.72)/65536-46.85;       //公式:T= -46.85 + 175.72 * ST/2^16
		return Temperature;                             //返回值：temperature
	}
   return 1;
}
 TempHumiValue_t temp_humi_Value;
TempHumiValue_t * SHT20_readTemAndHum(void)
{
	temp_humi_Value.humidity = SHT20_readTemOrHum(READ_HUMI_COMD);//读取湿度
	temp_humi_Value.temperature = SHT20_readTemOrHum(READ_TEMP_COMD);//读取湿度
	return &temp_humi_Value;
}



