# Watch

					watch原理图
![image](https://github.com/210843013/Watch/blob/master/watch.png)


##配置TIMx输出PWM注意事项：
				

![image](https://github.com/210843013/Watch/blob/master/afr.png)
			
			复用功能选择
			GPIOB->AFR[1] &=~((unsigned int)0xf<<8); //清零
			GPIOB->AFR[1] |= ((unsigned int)0x1<<8);   //复用成TIM2
			
			
##定时器2的通道3
			
![image](https://github.com/210843013/Watch/blob/master/ch.png)
			
			
				CCMRx的选择
			
![image](https://github.com/210843013/Watch/blob/master/ccmrx.png)
   
				当选择TIMx_ch1 TIMX_ch2时候，选择比较方式1和2即CCMR1
				
![image](https://github.com/210843013/Watch/blob/master/ccmr1.png)

				当选择TIMx_ch3 TIMX_ch4时候，选择比较方式3和4即CCMR2
				
![image](https://github.com/210843013/Watch/blob/master/ccmr2.png)
			
			
			//把通道配置为输出
			TIM2->CCMR2 &=~(0x3<<0);
			
			//选择是否打开影子功能
			TIM2->CCMR2 &=~(0x1<<3);
			
			//选择pwm波的输出模式
			TIM2->CCMR2 &=~(0x7<<4);
			TIM2->CCMR2 |=(0x6<<4);
			
			//选择通道的有效电平
			TIM2->CCER &=~(0x1<<9);
			
			//通道2输出使能
			TIM2->CCER |=(0x1<<8);
			
			//计数器使能
			TIM2->CR1  |=(0x1<<0);
			
##显示汉字字符串的注意点	

			注意：我是要在oled屏幕上显示三个汉字，结果。。看结果图
			
![image](https://github.com/210843013/Watch/blob/master/three.png)

			汉字串显示函数，调用单个字符串显示函数没毛病，匹配对应索引列表的汉字
			
			返回对应汉字字符所在的行，即汉字在自定义字库中的位置，调用WriteByte打印函数。

			![image](https://github.com/210843013/Watch/blob/master/hz.png)
			
			如结果图所示，显示6个汉字，多次试验汉字成倍显示，bug待修复。
			
![image](https://github.com/210843013/Watch/blob/master/pic.JPG)		
			
			
			
			
			
			
			
			
			
			
			

