#include "bujin.h"
#include "usart.h"
#include "delay.h"
//TIM2 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//TIM2�������Ʋ������
/*TIM2_CH1-->PA0��1�Ų��������,TIM2_CH4-->PA3��2�Ų����������1�Ų������Ϊ������������������̨��2�Ų��������������С��*/
void pwm_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_Init_A;//GPIOA��ʼ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//��ʱ����ʼ��
	TIM_OCInitTypeDef TIM_OCInitStruct;//PWM ͨ��1����
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//APB1ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIOAʱ��ʹ��
	
	GPIO_Init_A.GPIO_Mode= GPIO_Mode_AF_PP;
	GPIO_Init_A.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init_A.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_A);//GPIOA��ʼ��
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period=arr;//�����Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//����Ԥ��Ƶֵ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//��ʱ��������ʼ��,�����Զ���װֵ����Ƶϵ����������ʽ��
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);//PWM ͨ��1����
//	TIM_OC2Init(TIM2,&TIM_OCInitStruct);//PWM ͨ��1����
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);//PWM ͨ��3����
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);//PWM ͨ��4����
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
	TIM_Cmd(TIM2, ENABLE); //ʹ�� TIM2
}
void bujin_claw_up(u16 crr,u16 ms)		//�ڶ�������Ϊ���������ת�٣�����������Ϊת��ʱ��
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

void bujin_Init()	//���������ʼ��EN,DIR
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5|GPIO_Pin_1|GPIO_Pin_2;				 //LED0-->PB.5 �˿�����,,,PB6--DIR,,,PB7--EN
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
}
