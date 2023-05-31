#include "sys.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"
int main(void)
{	  
	int i;
	delay_init();				//延时函数初始化
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM3_Config();
	while(1)
	{
		for(i=100;i>0;i--)
		{
			TIM_SetCompare2(TIM3,i);
			delay_ms(10);
		}
		
		for(i=0;i<100;i++)
		{
			TIM_SetCompare2(TIM3,i);
			delay_ms(10);
		}
		
		
	}
}
