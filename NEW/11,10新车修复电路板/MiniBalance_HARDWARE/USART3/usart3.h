#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口3驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2015/3/29
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

#define USART3_MAX_RECV_LEN		6000//600					//最大接收缓存字节数
#define USART3_MAX_SEND_LEN		6000//600					//最大发送缓存字节数
#define USART3_RX_EN 			1					//0,不接收;1,接收.

extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern vu16 USART3_RX_STA;   						//接收数据状态

extern float pos_x;   //坐标X  
extern float pos_y;   //坐标Y
extern float zangle;  //Z轴角度
extern float xangle;  //X轴角度 
extern float yangle;  //Y轴角度
extern float w_z;     //航向角度

void usart3_init(u32 bound);				//串口2初始化 
//void u3_printf(char* fmt,...);

#endif




//#ifndef __USRAT3_H
//#define __USRAT3_H 
//#include "sys.h"	  	
//  /**************************************************************************
//作者：平衡小车之家
//我的淘宝小店：http://shop114407458.taobao.com/
//**************************************************************************/
//extern u8 Usart3_Receive;
//void uart3_init(u32 bound);
//void USART3_IRQHandler(void);
//#endif

