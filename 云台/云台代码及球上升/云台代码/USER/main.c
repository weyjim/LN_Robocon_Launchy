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
	作者：裴富浩
	主控：STM32F103C8T6 库函娄版
	伺服电机：PB6-->云台转向 PB5-->爪子开合  PB7-->两个扶手舵机
	步进电机：PA0-->两个云台升降，PA1-->小球升降
	说明：bujin_claw_up(speed，time/2)爪子云台升 | bujin_claw_down(speed，time/2)爪子云台降 | bujin_ball_up(speed，time/2)球云台升 | bujin_ball_down(speed，time/2)球云台降
				duoji_claw_open()爪子开 | duoji_claw_close()爪子合|
********************************************************************************/



int main(void)
{
	KEY_Init();
	delay_init();
	uart_init(9600);
	printf("初始化成功\r\n");
	TIM4_PWM_Init(1999,719);//PWM频率=72000000/（719+1）/（1999+1）=50hz=20ms，设置周期为20ms
	TIM3_CH2_PWM_Init(1999,719);
	pwm_Init(9999,11);	//初始化时钟频率，TIM2_CH1-->PA0,TIM2_CH4-->PA3
	bujin_Init();
	while(1)
	{	
		bujin_claw_up(1950,1000);	//爪子云台升到最高	
		duoji_turn_front();
		duoji_claw_open();
		delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);	//初始化将PB0口拉高
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

