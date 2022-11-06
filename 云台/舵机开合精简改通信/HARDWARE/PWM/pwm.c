#include "pwm.h"


//void TIM4_PWM_Init(u16 arr,u16 psc)
//{  //TIM4 PWM初始化 arr重装载值 psc预分频系数
//    GPIO_InitTypeDef     GPIO_InitStrue;
//    TIM_OCInitTypeDef     TIM_OCInitStrue;
//    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能TIM4和相关GPIO时钟
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//使能GPIOB时钟(GPIOB_Pin_9)
//    
//    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;     // TIM4_CH4
//    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    // 复用推挽
//    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
//    GPIO_Init(GPIOB,&GPIO_InitStrue);                //GPIO端口初始化设置
//	      
//    TIM_TimeBaseInitStrue.TIM_Period=arr;    //设置自动重装载值
//    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //预分频系数
//    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //计数器向上溢出
//    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
//    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);        //TIM3初始化设置(设置PWM的周期)
//    
//    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWM模式1:CNT < CCR时输出有效电平
//    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// 设置极性-有效电平为：高电平
//    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// 输出使能
//    TIM_OC4Init(TIM4,&TIM_OCInitStrue);        //TIM4的通道4 PWM 模式设置

//    TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);        //使能预装载寄存器
//    
//    TIM_Cmd(TIM4,ENABLE);        //使能TIM4
//    
//}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能
   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH1  CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

  TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值  80K
  TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据     TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	

  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能  	
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
  TIM_Cmd(TIM4, ENABLE);  //使能TIM1  
}

void service_Init(void)
{
	TIM_SetCompare1(TIM4,1500);					//开
}
