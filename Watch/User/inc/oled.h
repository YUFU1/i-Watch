#ifndef OLED_H
#define OLED_H
#include "stm32f4xx.h"


#define MAX_COLUMNC	128	
#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý
	


#define OLED_CS_SET  (GPIOB->BSRRL = 1<<7)  	//OLED_CS  PB7
#define OLED_CS_CLR  (GPIOB->BSRRH = 1<<7)  
	
#define OLED_RST_SET  (GPIOB->BSRRL = 1<<13)  //OLED_RES  PB13
#define OLED_RST_CLR  (GPIOB->BSRRH = 1<<13)  //OLED_RES  PB13

#define OLED_DC_SET  (GPIOA->BSRRL = 1<<15)  //OLED_DC  PA15
#define OLED_DC_CLR  (GPIOA->BSRRH = 1<<15)  


void OLED_Init(void);
u8 OLED_reset(void);
u8 OLED_pinInit(void);
void OLED_select(void);
void OLED_deSelect(void);
void OLED_writeByte(u8 dat, u8 cmd);
void OLED_clear(void) ;
void OLED_setPos(unsigned char x, unsigned char y) ;

void OLED_showCHinese(u8 x,u8 y,u8 no); 
void OLED_showHzString(u8 x,u8 y,char *buf);

void OLED_showChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_showChString(u8 x,u8 y,u8 *chr,u8 Char_Size);



#endif


