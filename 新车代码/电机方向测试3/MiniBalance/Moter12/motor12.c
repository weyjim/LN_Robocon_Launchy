#include "motor12.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
void motor12_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14;				 //电机1
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_15);						 //PB.5 输出高
 GPIO_SetBits(GPIOB,GPIO_Pin_14);						 //PB.5 输出高
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;	    		 //
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOA,GPIO_Pin_8); 						 //EN 输出高 
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	            //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOF, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
}
