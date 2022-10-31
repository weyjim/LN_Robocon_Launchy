#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����3��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2015/3/29
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

#define USART3_MAX_RECV_LEN		6000//600					//�����ջ����ֽ���
#define USART3_MAX_SEND_LEN		6000//600					//����ͻ����ֽ���
#define USART3_RX_EN 			1					//0,������;1,����.

extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern vu16 USART3_RX_STA;   						//��������״̬

extern float pos_x;   //����X  
extern float pos_y;   //����Y
extern float zangle;  //Z��Ƕ�
extern float xangle;  //X��Ƕ� 
extern float yangle;  //Y��Ƕ�
extern float w_z;     //����Ƕ�

void usart3_init(u32 bound);				//����2��ʼ�� 
//void u3_printf(char* fmt,...);

#endif




//#ifndef __USRAT3_H
//#define __USRAT3_H 
//#include "sys.h"	  	
//  /**************************************************************************
//���ߣ�ƽ��С��֮��
//�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
//**************************************************************************/
//extern u8 Usart3_Receive;
//void uart3_init(u32 bound);
//void USART3_IRQHandler(void);
//#endif

