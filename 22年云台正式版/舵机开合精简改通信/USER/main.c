#include "stm32f10x.h"
#include "pwm.h"
#include "delay.h"
#include "tongxin.h"
//#include "usart.h"
/************************************************
 ALIENTEK 精英STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK,.,,,,
************************************************/
 int main(void)
 {	
//	 	uart_init(115200);
		TongXin_Init();
		TIM4_PWM_Init(59999,23); //设置频率为50Hz，公式为：溢出时间Tout（单位秒）=(arr+1)(psc+1)/Tclk	 20MS = (59999+1)*(23+1)/72000000
																//Tclk为通用定时器的时钟，如果APB1没有分频，则就为系统时钟，72MHZ
															//PWM时钟频率=72000000/(59999+1)*(23+1) = 50HZ (20ms),设置自动装载值60000,预分频系数24	
		service_Init();
	 //	 printf("1\r\n");
//		delay_ms(500); //上电时等待其他器件就绪
		Kuaizi_Init();
  while(1)
	{
				if(GetA8==1)
				{
						TIM_SetCompare1(TIM4,7500);					//合
						Kuaizi=1;
				}
				if(PutA11==1)
				{
						TIM_SetCompare1(TIM4,1500);					//开
						Kuaizi=0;
				}	
	}
	
 }
