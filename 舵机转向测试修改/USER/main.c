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
	伺服电机：爪子--舵机270°，爪子转向--180°
	步进电机：
	说明：TIM4,PB1是转勺子,PB3是按键输入端口
	MG996R，360度舵机只能控制转速和方向，给值最好是不超过0.1ms，按周期占比来计算该给多少CRR值。
	注意0.5ms和2.5ms是控制方向的
	TIM4_CH1控制180度舵机，TIM3_CH2控制270度舵机
********************************************************************************/



int main(void)
{
	KEY_Init();
	delay_init();
	uart_init(9600);
	printf("初始化成功\r\n");
	TIM4_CH1_PWM_Init(1999,719);//PWM频率=72000000/（719+1）/（1999+1）=50hz=20ms，设置周期为20ms
	TIM3_CH2_PWM_Init(1999,719);
	pwm_Init(9999,11);
	bujin_Init();
	while(1)
	{	
		EN=0;
		DIR=1;
		GPIO_SetBits(GPIOB,GPIO_Pin_0);	//初始化将PB3口拉高
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==1)
		{
			bujin_left(1950);		//左步进电机
			bujin_right(1950);		//右步进电机
			TIM_SetCompare1(TIM4,1750);	//转180度
			delay_ms(200);
			TIM_SetCompare2(TIM3,1817);	//爪子张开
			delay_ms(200);
			TIM_SetCompare1(TIM4,1950);	//勺子初始位置，180度舵机0度位置
			TIM_SetCompare2(TIM3,1950);	//爪子关闭
		}
//		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	}
}

