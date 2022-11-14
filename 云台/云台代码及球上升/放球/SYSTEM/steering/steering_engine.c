#include "steering_engine.h"

//TIM4 PWM��ʼ��
/*TIM4_CH2�����ֶ����TIM4_CH1��̨ת��*/
void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	
	//TIM3������ӳ��
	/*
	*�鿴�����ֲᣬ���ŵĶ�ʱ��ͨ������ȫӳ�䣬���ǲ���ӳ��
	*���ߵ��ò�������ͬ
	*��ȫӳ�� ��GPIO_FullRemap_TIM4
	*����ӳ�� ��GPIO_PartialRemap_TIM4
	*/
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4,ENABLE);
	
	//���ø�����Ϊ�����������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//��ʼ��TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//��װ��ֵ 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//Ԥ��Ƶֵ 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //ʱ�ӷ�Ƶ1��2��4��Ƶ	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ü���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//��ʼ������Ƚϲ���
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ������arr��ֵʱΪ��Ч��ƽ
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//�������,�ߵ�ƽ��Ч
	TIM_OC1Init(TIM4,&TIM_OCInitTypeStruct); //����TIMX�Ĳ����趨��ʼ������ TIMX OC2,TIMX OC3....
	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //����TIMX�Ĳ����趨��ʼ������ TIMX OC2,TIMX OC3....
	TIM_OC3Init(TIM4,&TIM_OCInitTypeStruct); //����TIMX�Ĳ����趨��ʼ������ TIMX OC2,TIMX OC3....
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4,ENABLE);
}
void duoji_turn_behind(void)
{
	TIM_SetCompare1(TIM4,1750);
}

void duoji_turn_front(void)
{
	TIM_SetCompare1(TIM4,1950);
}

void duoji_fushou_left_front(void)
{
	TIM_SetCompare2(TIM4,1950);
}

void duoji_fushou_left_behind(void)
{
	TIM_SetCompare2(TIM4,1884);
}

void duoji_fushou_right_front(void)
{
	TIM_SetCompare3(TIM4,1950);
}

void duoji_fushou_right_behind(void)
{
	TIM_SetCompare3(TIM4,1884);
}

