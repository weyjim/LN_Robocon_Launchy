#ifndef __TONGXIN_H
#define __TONGXIN_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
//#define GetA8  PAin(8)
//#define PutA11 PAin(11)

#define GetA8  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//צ�ӱպ�ץ
#define PutA11  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)//צ���ſ���
#define Kuaizi PBout(5)

void TongXin_Init(void);//��ʼ��
void Kuaizi_Init(void);

		 				    
#endif
