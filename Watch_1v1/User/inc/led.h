#ifndef LED_H
#define LED_H

#define LED_ON  GPIOA->ODR &=~(0x1<<7)
#define LED_OFF GPIOA->ODR |= (0x1<<7)


void LED_Init(void);

#endif


