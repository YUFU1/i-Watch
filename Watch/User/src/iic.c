#include "includes.h"

/******************************
函数名：IIC_SDA_Out
函数参数：无
函数返回值：无
函数功能：实现IIC总线SDA的输出配置
函数描述:IIC总线SDA对应的管脚配置为推挽输出
AT24C02 :SDA=PB9
*******************************/
void  IIC_SDA_Out(void)
{
	//打开PB的外设时钟
	RCC->AHB1ENR |=(1<<1);
	/***配置PB8为推挽输出模式***/
	//端口模式寄存器
	GPIOB->MODER &=~(0X3<<16);//清零
	GPIOB->MODER |=(1<<16); //配置为通用输出模式
	//输出类型
	GPIOB->OTYPER &=~(1<<8); //推挽输出
	//输出速率
	GPIOB->OSPEEDR &=~(0X3<<16); //清零
	GPIOB->OSPEEDR |=(0X2<<16); //输出速率50M
	
	//打开PB的外设时钟
	RCC->AHB1ENR |=(1<<1);
	/***配置PB9为推挽输出模式***/
	//端口模式寄存器
	GPIOB->MODER &=~(0X3<<18);//清零
	GPIOB->MODER |=(1<<18); //配置为通用输出模式
	//输出类型
	GPIOB->OTYPER &=~(1<<9); //推挽输出
	//输出速率
	GPIOB->OSPEEDR &=~(0X3<<18); //清零
	GPIOB->OSPEEDR |=(0X2<<18); //输出速率50M

}

/******************************
函数名：IIC_SDA_Int
函数参数：无
函数返回值：无
函数功能：实现IIC总线SDA的输入配置
函数描述:IIC总线SDA对应的管脚配置为浮空输出
AT24C02 :SDA=PB9
*******************************/
void  IIC_SDA_Int(void)
{
//打开PB的外设时钟
	RCC->AHB1ENR |=(1<<1);
	/***配置PB8为推挽输出模式***/
	//端口模式寄存器
	GPIOB->MODER &=~(0X3<<16);//清零
	GPIOB->MODER |=(1<<16); //配置为通用输出模式
	//输出类型
	GPIOB->OTYPER &=~(1<<8); //推挽输出
	//输出速率
	GPIOB->OSPEEDR &=~(0X3<<16); //清零
	GPIOB->OSPEEDR |=(0X2<<16); //输出速率50M
	
	//打开PB的外设时钟
	RCC->AHB1ENR |=(1<<1);
	/***配置PB9为浮空输入模式***/
	//端口模式寄存器
	GPIOB->MODER &=~(0X3<<18);//输入模式
	//上下拉
	GPIOB->PUPDR &=~(0X3<<18);//浮空	
}

/******************************
函数名：IIC_Start
函数返回值：无
函数功能：模拟IIC总线开始条件
函数描述:由主机产生
  数据线：输出
*******************************/
void IIC_Start(void)
{

   IIC_SDA_Out();//IO口
	 SCL_H; //时钟线为高
	 SDA_H; //数据线为高
	 Delay_us(1);//开始条件建立时间 0.6--2us
	 SDA_L; //数据线为低
	 SCL_H; //时钟线为高
	
	
	
	 Delay_us(1);//开始条件保持时间 0.6--2us
	 SCL_L; //时钟线为低
}

/******************************
函数名：IIC_Stop
函数返回值：无
函数功能：模拟IIC总线停止条件
函数描述:由主机产生
  数据线：输出
*******************************/
void IIC_Stop(void)
{
//	 IIC_SCL_Out();
   IIC_SDA_Out();
	
	
	 SDA_L; //数据线为低
	 SCL_H; //时钟线为高
	 Delay_us(1);//停止条件建立时间 0.6--2us
	 SDA_H; //数据线为高
	 SCL_H; //时钟线为高
}
/******************************
函数名：IIC_Senddate
函数参数：u8 date
函数功能：模拟IIC总线发送数据
函数描述:
  数据线：输出
*******************************/
void IIC_Senddate(u8 date)
{
	u8 i;
  IIC_SDA_Out();
	
	//循坏发送8位数据 MSB在前
	for(i=0;i<8;i++)
	{
		SCL_L; // 准备数据
		if(date &(0x80>>i))//1
		{
			 SDA_H;
		}
		else //0
		{
			 SDA_L;
		}
		Delay_us(2);//低电平宽度1.2--3us
		SCL_H; //传输数据
		Delay_us(1);//高电平宽度0.6--2us
	}
	 SCL_L; //时钟线为低	
}

/******************************
函数名：IIC_Receivedate
函数返回值：u8 date
函数功能：模拟IIC总线接收数据
函数描述:
  数据线：输入
*******************************/
u8  IIC_Receivedate(void)
{
	
   u8 i;
   u8 date=0;
   IIC_SDA_Int();
	 for(i=0;i<8;i++)
	 {
			SCL_L; //时钟线为低	
		  Delay_us(2);//低电平宽度1.2--3us
		  SCL_H; //传输数据//有数据
	 	//接收到数据
			if(GPIOB->IDR &(1<<9))//1
			{
				 date |= 0x80>>i;
			}
			Delay_us(1);//高电平宽度0.6--2us
		}
   SCL_L; //时钟线为低	
   return date;
}

/******************************
函数名：IIC_Sendack
函数参数：u8 ack
ack=1: 无应答
ack=0: 有应答
函数功能：模拟IIC总线发送应答
函数描述:
  数据线：输出
*******************************/
void IIC_Sendack(u8 ack)
{
   IIC_SDA_Out();
		//准备数据
		SCL_L;
		if(ack) //1
		{
			SDA_H;
		}
		else //0
		{
			 SDA_L;
		}
		Delay_us(2);//低电平宽度1.2--3us
		SCL_H; //传输数据
		Delay_us(1);//高电平宽度0.6--2us
		SCL_L;
}

/******************************
函数名：IIC_Receiveack
函数返回值：u8 ack
ack=1: 无应答
ack=0: 有应答
函数功能：模拟IIC总线接收应答
函数描述:
  数据线：输入
*******************************/
u8 IIC_Receiveack(void)
{
   u8 ack;
   IIC_SDA_Int();
	 SCL_L; //时钟线为低	
	 Delay_us(2);//低电平宽度1.2--3us
	 SCL_H; //传输数据//有数据
		//接收到数据
	 if(GPIOB->IDR &(1<<9))//1
	 {
	   ack=1;
	 }
	 else //0
	 {
		 ack=0;
	 } 
	 Delay_us(1);//高电平宽度0.6--2us
	 SCL_L;
	 return ack;
}


