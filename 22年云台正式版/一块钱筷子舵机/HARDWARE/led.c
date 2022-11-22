#include "led.h"
#include "stm32f10x.h"

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//两个端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			//结构体变量设置
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);					//讲结构体变量写入初始化函数
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);

//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOE,GPIO_Pin_5);					//这些注释都是我自己注的，原子哥写了，我发现可以省略
}


