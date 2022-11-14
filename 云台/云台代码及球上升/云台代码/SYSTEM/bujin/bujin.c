#include "bujin.h"
#include "usart.h"
#include "delay.h"
//TIM2 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
//TIM2用来控制步进电机
/*TIM2_CH1-->PA0（1号步进电机）,TIM2_CH4-->PA3（2号步进电机），1号步进电机为两个步进用来升降云台，2号步进电机用来升降小球*/
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
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);//PWM 通道3设置
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);//PWM 通道4设置
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); //使能预装载寄存器
	TIM_Cmd(TIM2, ENABLE); //使能 TIM2
}
void bujin_claw_up(u16 crr,u16 ms)		//第二个参数为步进电机的转速，第三个参数为转动时间
{
	EN0=0;
	DIR0=0;
	TIM_SetCompare1(TIM2,crr);
	delay_ms(ms);
	delay_ms(ms);
	delay_ms(ms);
	EN0=1;
}

void bujin_claw_down(u16 crr,u16 ms)
{
	EN0=0;
	DIR0=1;
	TIM_SetCompare1(TIM2,crr);
	delay_ms(ms);
	delay_ms(ms);
	delay_ms(ms);
	EN0=1;
}

void bujin_ball_up(u16 crr,u16 ms)
{
	EN1=0;
	DIR1=0;
	TIM_SetCompare4(TIM2,crr);
	delay_ms(ms);
	delay_ms(ms);
	delay_ms(ms);
	EN1=1;
}

void bujin_ball_down(u16 crr,u16 ms)
{
	EN1=0;
	DIR1=1;
	TIM_SetCompare4(TIM2,crr);
	delay_ms(ms);
	delay_ms(ms);
	delay_ms(ms);
	EN1=1;
}

void bujin_Init()	//步进电机初始化EN,DIR
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5|GPIO_Pin_1|GPIO_Pin_2;				 //LED0-->PB.5 端口配置,,,PB6--DIR,,,PB7--EN
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
}
