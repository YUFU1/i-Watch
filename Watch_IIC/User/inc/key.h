#ifndef KEY_H
#define KEY_H
void Key_Init(void);

#define Key_ON   (GPIOA->IDR &(0x1<<0))
#define Key_OFF  (GPIOA->IDR &(0x1<<0))

#endif

