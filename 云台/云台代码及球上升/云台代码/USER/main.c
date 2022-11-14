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
	�ŷ������PB6-->��̨ת�� PB5-->צ�ӿ���  PB7-->�������ֶ��
	���������PA0-->������̨������PA1-->С������
	˵����bujin_claw_up(speed��time/2)צ����̨�� | bujin_claw_down(speed��time/2)צ����̨�� | bujin_ball_up(speed��time/2)����̨�� | bujin_ball_down(speed��time/2)����̨��
				duoji_claw_open()צ�ӿ� | duoji_claw_close()צ�Ӻ�|
********************************************************************************/



int main(void)
{
	KEY_Init();
	delay_init();
	uart_init(9600);
	printf("��ʼ���ɹ�\r\n");
	TIM4_PWM_Init(1999,719);//PWMƵ��=72000000/��719+1��/��1999+1��=50hz=20ms����������Ϊ20ms
	TIM3_CH2_PWM_Init(1999,719);
	pwm_Init(9999,11);	//��ʼ��ʱ��Ƶ�ʣ�TIM2_CH1-->PA0,TIM2_CH4-->PA3
	bujin_Init();
	while(1)
	{	
		bujin_claw_up(1950,1000);	//צ����̨�������	
		duoji_turn_front();
		duoji_claw_open();
		delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);	//��ʼ����PB0������
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==1)
		{
			bujin_claw_down(1950,1000);
			duoji_claw_close();
			delay_ms(500);
			bujin_claw_up(1950,1000);
			duoji_turn_behind();
			delay_ms(500);
			duoji_claw_open();
			delay_ms(500);
			GPIO_SetBits(GPIOB,GPIO_Pin_9);
			delay_ms(50);
			GPIO_ResetBits(GPIOB,GPIO_Pin_9);
			duoji_turn_front();
		}
	}
}

