#include "bujin.h"
#include "usart.h"

//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
/*TIM3_CH1-->PA0（1号步进）,TIM3_CH4-->PA3（2号步进）*/
void pwm_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_Init_A;//GPIOA初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//定时器初始化
	TIM_OCInitTypeDef TIM_OCInitStruct;//PWM 通道1设置
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//APB1时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIOA时钟使能
	
	GPIO_Init_A.GPIO_Mode= GPIO_Mode_AF_PP;
	GPIO_Init_A.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init_A.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_A);//GPIOA初始化
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=arr;//设置自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//设置预分频值
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//定时器参数初始化,设置自动重装值，分频系数，计数方式等
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);//PWM 通道1设置
//	TIM_OC2Init(TIM2,&TIM_OCInitStruct);//PWM 通道1设置
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);//PWM 通道1设置
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);//PWM 通道1设置
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); //使能预装载寄存器
	TIM_Cmd(TIM2, ENABLE); //使能 TIM2
}
void bujin_left(u16 crr)
{
	TIM_SetCompare1(TIM2,crr);
}


void bujin_right(u16 crr)
{
	TIM_SetCompare4(TIM2,crr);
} 


void bujin_Init()	//步进电机初始化EN,DIR
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;				 //LED0-->PB.5 端口配置,,,PB6--DIR,,,PB7--EN
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
}
