#include "key.h"
#include "sys.h" 
#include "delay.h"

void KEY_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// Input Pull Up
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			//Pull Down
	GPIO_Init(GPIOA,&GPIO_InitStructure);						
}
u8 KEY_Scan(u8 mode)							
{
	static u8 key_up=1;
	if(mode)
		key_up=1;								//支持连按（松手检测）的设置
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);
		key_up=0;								//key_up标志位，0时按下
		if(KEY0==0)
			return KEY0_PRES;
		else if(KEY1==0)
			return KEY1_PRES;
		else if(WK_UP==1)
			return WKUP_PRES;
	}
	else if(KEY0==1&&KEY1==1&&WK_UP==0)			//如果只写else，key_up=0,if不成立，Key_up又为1，进入又变0，反复循环，松手检测无效
		key_up=1;
	return 0;
}


