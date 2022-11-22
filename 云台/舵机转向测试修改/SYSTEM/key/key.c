#include "key.h"
#include "stm32f10x.h"


void KEY_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //�˿�PB1
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //��������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.1
	 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //�˿�PB3
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.2 
	 
}

