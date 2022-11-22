#include "stm32f10x.h"
#include "delay.h"
#include "steering_engine.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "qufang.h"
#include "bujin.h"
//#include "timer.h"
/*******************************************************************************
	���ߣ��ḻ��
	���أ�STM32F103C8T6 �⺯¦��
	�ŷ������צ��--���270�㣬צ��ת��--180��
	���������
	˵����TIM4,PB1��ת����,PB3�ǰ�������˿�
	MG996R��360�ȶ��ֻ�ܿ���ת�ٺͷ��򣬸�ֵ����ǲ�����0.1ms��������ռ��������ø�����CRRֵ��
	ע��0.5ms��2.5ms�ǿ��Ʒ����
	TIM4_CH1����180�ȶ����TIM3_CH2����270�ȶ��
********************************************************************************/



int main(void)
{
	KEY_Init();
	delay_init();
	uart_init(9600);
	printf("��ʼ���ɹ�\r\n");
	TIM4_CH1_PWM_Init(1999,719);//PWMƵ��=72000000/��719+1��/��1999+1��=50hz=20ms����������Ϊ20ms
	TIM3_CH2_PWM_Init(1999,719);
	pwm_Init(9999,11);
	bujin_Init();
	while(1)
	{	
		EN=0;
		DIR=1;
		GPIO_SetBits(GPIOB,GPIO_Pin_0);	//��ʼ����PB3������
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==1)
		{
			bujin_left(1950);		//�󲽽����
			bujin_right(1950);		//�Ҳ������
			TIM_SetCompare1(TIM4,1750);	//ת180��
			delay_ms(200);
			TIM_SetCompare2(TIM3,1817);	//צ���ſ�
			delay_ms(200);
			TIM_SetCompare1(TIM4,1950);	//���ӳ�ʼλ�ã�180�ȶ��0��λ��
			TIM_SetCompare2(TIM3,1950);	//צ�ӹر�
		}
//		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	}
}

