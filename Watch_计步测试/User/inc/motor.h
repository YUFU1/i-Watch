#ifndef MOTOR_H
#define MOTOR_H

void Motor_Init(void);

#define Motor_ON    GPIOB->ODR |= (0x1<<10);
#define Motor_OFF   GPIOB->ODR &=~(0x1<<10);

#endif


