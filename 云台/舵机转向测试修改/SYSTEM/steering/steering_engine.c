#include "steering_engine.h"

//TIM4 PWM初始化
void TIM4_CH1_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	//要开启复用功能的时钟才能重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	
	//TIM3部分重映射
	/*
	*查看数据手册，引脚的定时器通道是完全映射，还是部分映射
	*二者调用参数不相同
	*完全映射 ：GPIO_FullRemap_TIM4
	*部分映射 ：GPIO_PartialRemap_TIM4
	*/
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4,ENABLE);
	
	//设置该引脚为复用输出功能
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//重装载值 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//预分频值 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //时钟分频1、2、4分频	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//初始化输出比较参数
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式，大于arr的值时为有效电平
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性,高电平有效
	TIM_OC1Init(TIM4,&TIM_OCInitTypeStruct); //根据TIMX的参数设定初始化外设 TIMX OC2,TIMX OC3....
	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //根据TIMX的参数设定初始化外设 TIMX OC2,TIMX OC3....
	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	//使能定时器
	TIM_Cmd(TIM4,ENABLE);
}

