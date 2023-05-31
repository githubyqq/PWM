#include "sys.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"
int main(void)
{	  
	int i;
	delay_init();				//��ʱ������ʼ��
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
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
