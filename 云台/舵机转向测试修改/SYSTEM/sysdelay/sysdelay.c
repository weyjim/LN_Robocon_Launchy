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
//    TIM4->CNT = nus - 1; // �������װҪ�ݼ�����������0��ᴥ����ʱ����TIM_FLAG_UpDate��־λ
//    TIM4->CR1 |= TIM_CR1_CEN; // ʹ�ܼ������� ��������ʼ�ݼ�
//    while((TIM4->SR & TIM_FLAG_Update) != SET); // �ȵ�����������0
//    TIM4-CR1 &= (~TIM_CR1_CEN); //�رռ�����
//    TIM4->SR &= ~TIM_FLAG_UpDate; // �����ʱ����Ϊ0�ı�־λ
//}

//void Sys_delay_ms(unsigned int nms)
//{
//    Sys_delay_us(nms * 1000);
//}

