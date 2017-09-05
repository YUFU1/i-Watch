#ifndef SHT20_H
#define SHT20_H

#include "stm32f4xx.h"

#define SHT20_WRITEADDR       0x80   //SHT20写地址
#define SHT20_READADDR       0x81    //SHT20读地址
#define READ_TEMP_COMD  0xf3         //读取温度命令
#define READ_HUMI_COMD  0xf5         //读取湿度命令

typedef struct
{
	float temperature; //湿度
	float humidity;    //温度
}TempHumiValue_t;
 

void SHT20_Init(void);
void SHT20_softReset(void);
void SHT20_setResolution(void);
float SHT20_readTemOrHum(u8 commod);
TempHumiValue_t * SHT20_readTemAndHum(void);
#endif /* SHT20_H */
