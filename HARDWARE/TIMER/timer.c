#include "timer.h"
#include "led.h"
#include "usart.h"


//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数

//定时器3配置
void TIM3_Config(void)
{	
	static GPIO_InitTypeDef				GPIO_InitStructure;
	static TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	static TIM_OCInitTypeDef       		TIM_OCInitStructure;
	
	//1.使能定时器3时钟和GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	//2.TIM3部分重映射
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5  
	
	//3.配置GPIO引脚为复用功能
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;//选择GPIOB组的第0根引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//选择引脚为复用推挽功能
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//选择引脚速度	
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化GPIO
	
	
	//4.配置定时器3的频率,包括：分频值、计数值等
	TIM_TimeBaseStructure.TIM_Period=99;		//计数值
	TIM_TimeBaseStructure.TIM_Prescaler=0;			//分频值
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);  //初始化定时器
	
	
	//5.配置定时器3的通道2占空比
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//打开或者关闭脉冲输出
	TIM_OCInitStructure.TIM_Pulse = 50;	//比较值
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //有效电平设置为高状态		
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//初始化定时器通道2
		
	//6.使能定时器3工作
	TIM_Cmd(TIM3,ENABLE);

}

