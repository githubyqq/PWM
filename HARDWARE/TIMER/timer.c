#include "timer.h"
#include "led.h"
#include "usart.h"


//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��

//��ʱ��3����
void TIM3_Config(void)
{	
	static GPIO_InitTypeDef				GPIO_InitStructure;
	static TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	static TIM_OCInitTypeDef       		TIM_OCInitStructure;
	
	//1.ʹ�ܶ�ʱ��3ʱ�Ӻ�GPIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	//2.TIM3������ӳ��
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5  
	
	//3.����GPIO����Ϊ���ù���
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;//ѡ��GPIOB��ĵ�0������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//ѡ������Ϊ�������칦��
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//ѡ�������ٶ�	
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��GPIO
	
	
	//4.���ö�ʱ��3��Ƶ��,��������Ƶֵ������ֵ��
	TIM_TimeBaseStructure.TIM_Period=99;		//����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler=0;			//��Ƶֵ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);  //��ʼ����ʱ��
	
	
	//5.���ö�ʱ��3��ͨ��2ռ�ձ�
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//�򿪻��߹ر��������
	TIM_OCInitStructure.TIM_Pulse = 50;	//�Ƚ�ֵ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //��Ч��ƽ����Ϊ��״̬		
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//��ʼ����ʱ��ͨ��2
		
	//6.ʹ�ܶ�ʱ��3����
	TIM_Cmd(TIM3,ENABLE);

}

