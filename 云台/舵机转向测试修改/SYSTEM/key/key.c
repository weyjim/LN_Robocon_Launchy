#include "key.h"
#include "stm32f10x.h"


void KEY_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //端口PB1
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //下拉输入
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.1
	 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //端口PB3
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.2 
	 
}

