#include "stm32f10x.h"
#include "pwm.h"
#include "delay.h"
#include "tongxin.h"
//#include "usart.h"
/************************************************
 ALIENTEK ��ӢSTM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK,.,,,,
************************************************/
 int main(void)
 {	
//	 	uart_init(115200);
		TongXin_Init();
		TIM4_PWM_Init(59999,23); //����Ƶ��Ϊ50Hz����ʽΪ�����ʱ��Tout����λ�룩=(arr+1)(psc+1)/Tclk	 20MS = (59999+1)*(23+1)/72000000
																//TclkΪͨ�ö�ʱ����ʱ�ӣ����APB1û�з�Ƶ�����Ϊϵͳʱ�ӣ�72MHZ
															//PWMʱ��Ƶ��=72000000/(59999+1)*(23+1) = 50HZ (20ms),�����Զ�װ��ֵ60000,Ԥ��Ƶϵ��24	
		service_Init();
	 //	 printf("1\r\n");
//		delay_ms(500); //�ϵ�ʱ�ȴ�������������
		Kuaizi_Init();
  while(1)
	{
				if(GetA8==1)
				{
						TIM_SetCompare1(TIM4,7500);					//��
						Kuaizi=1;
				}
				if(PutA11==1)
				{
						TIM_SetCompare1(TIM4,1500);					//��
						Kuaizi=0;
				}	
	}
	
 }
