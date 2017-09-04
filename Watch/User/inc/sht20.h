#ifndef SHT20_H
#define SHT20_H
#include "stm32f4xx.h"

#define SHT20ADDR       0x80         //SHT20写地址
#define ACK             0            //应答信号
#define NACK            1            //非应答信号
#define FAIL            1            //读取温湿度失败的返回值。
#define READ_TEMP_COMD  0xf3         //读取温度命令
#define READ_HUMI_COMD  0xf5         //读取湿度命令

typedef struct
{
	float temperature; //湿度
	float humidity;    //温度
}TempHumiValue_t;
 
void SHT20_Init(void);
TempHumiValue_t * SHT20_readTemAndHum(void);



static void SHT20_setResolution(void); 
static void SHT20_softReset(void);
void SHT20_Init(void);

 
#endif


