#include "led.h"
#include "stm32f10x.h"

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;					//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//�����˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			//�ṹ���������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);					//���ṹ�����д���ʼ������
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);

//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOE,GPIO_Pin_5);					//��Щע�Ͷ������Լ�ע�ģ�ԭ�Ӹ�д�ˣ��ҷ��ֿ���ʡ��
}


