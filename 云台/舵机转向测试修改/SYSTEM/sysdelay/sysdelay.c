//#include "sysdelay.h"
//#include "sys.h"
//void TIM3_Init()
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

//	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
//	TIM_TimeBaseInitStructure.TIM_Period = 1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
//}
//void Sys_delay_us(unsigned int nus)
//{
//    TIM4->CNT = nus - 1; // 向计数器装要递减的数，减到0后会触发定时器的TIM_FLAG_UpDate标志位
//    TIM4->CR1 |= TIM_CR1_CEN; // 使能计数器， 计数器开始递减
//    while((TIM4->SR & TIM_FLAG_Update) != SET); // 等到计数器减到0
//    TIM4-CR1 &= (~TIM_CR1_CEN); //关闭计数器
//    TIM4->SR &= ~TIM_FLAG_UpDate; // 清除定时器变为0的标志位
//}

//void Sys_delay_ms(unsigned int nms)
//{
//    Sys_delay_us(nms * 1000);
//}

