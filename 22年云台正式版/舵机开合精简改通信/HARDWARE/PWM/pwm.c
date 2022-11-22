#include "pwm.h"


//void TIM4_PWM_Init(u16 arr,u16 psc)
//{  //TIM4 PWM��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
//    GPIO_InitTypeDef     GPIO_InitStrue;
//    TIM_OCInitTypeDef     TIM_OCInitStrue;
//    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ��TIM4�����GPIOʱ��
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//ʹ��GPIOBʱ��(GPIOB_Pin_9)
//    
//    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;     // TIM4_CH4
//    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    // ��������
//    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
//    GPIO_Init(GPIOB,&GPIO_InitStrue);                //GPIO�˿ڳ�ʼ������
//	      
//    TIM_TimeBaseInitStrue.TIM_Period=arr;    //�����Զ���װ��ֵ
//    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //Ԥ��Ƶϵ��
//    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //�������������
//    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
//    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);        //TIM3��ʼ������(����PWM������)
//    
//    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
//    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
//    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
//    TIM_OC4Init(TIM4,&TIM_OCInitStrue);        //TIM4��ͨ��4 PWM ģʽ����

//    TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���
//    
//    TIM_Cmd(TIM4,ENABLE);        //ʹ��TIM4
//    
//}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH1  CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

  TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ  80K
  TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����     TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	

  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��  	
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
  TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM1  
}

void service_Init(void)
{
	TIM_SetCompare1(TIM4,1500);					//��
}
