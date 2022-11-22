#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "key.h"
//#include "usart.h"


int main(void)
{
	u8 wey=0;
	u16 cannonpwmval=1950;				//����٣��������ޣ���Ӧ����Ϊreset����
	
	delay_init();
	KEY_Init();
	LED_Init();
//	uart_init(9600);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED1=1;
	TIM3_PWM_Init(1999,719);						//����ֵ1w
	
	while(1)
	{
//		key=KEY_Scan(1);
		if(PAin(0)==1)
		{
			delay_ms(1000);
			delay_ms(1000);
			cannonpwmval=1860;
			
			wey=1;
		}
		else
		{
			cannonpwmval=1950;
			if(wey)
			{
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				wey=0;
			}
			
		}
//		cannonpwmval=1895;
//		TIM_SetCompare2(TIM3,cannonpwmval);			//�ı�TIM3�Ƚ�ֵ���Ӷ��ı�ռ�ձ�
//		delay_ms(1000);
//		delay_ms(1000);
//		cannonpwmval=1950;
		TIM_SetCompare2(TIM3,cannonpwmval);			//�ı�TIM3�Ƚ�ֵ���Ӷ��ı�ռ�ձ�
//		delay_ms(1000);
//		delay_ms(1000);
//		printf("%d\r\n",cannonpwmval);
	}
}
