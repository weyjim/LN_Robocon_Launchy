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
		key_up=1;								//֧�����������ּ�⣩������
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);
		key_up=0;								//key_up��־λ��0ʱ����
		if(KEY0==0)
			return KEY0_PRES;
		else if(KEY1==0)
			return KEY1_PRES;
		else if(WK_UP==1)
			return WKUP_PRES;
	}
	else if(KEY0==1&&KEY1==1&&WK_UP==0)			//���ֻдelse��key_up=0,if��������Key_up��Ϊ1�������ֱ�0������ѭ�������ּ����Ч
		key_up=1;
	return 0;
}


