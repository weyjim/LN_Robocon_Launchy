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

/*****F54 321û���õ�********/
#define F1 PFout(1)
#define F2 PFout(2)	
#define F3 PFout(3)

#define SendGetF10 PFout(10)
#define SendPutF6 PFout(6)
#define KEY PFin(7)

#define Hong PFin(8)
#define Lan PFin(9)


void TongXinSend_Init(void);//��ʼ��
void HongLan_Init(void);//��ʼ��
void TongXinReceive_Init(void);	 				    
#endif
