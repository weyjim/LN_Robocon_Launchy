#ifndef __TONGXIN_H
#define __TONGXIN_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

/*****F54 321没有用到********/
#define F1 PFout(1)
#define F2 PFout(2)	
#define F3 PFout(3)

#define SendGetF10 PFout(10)
#define SendPutF6 PFout(6)
#define KEY PFin(7)

#define Hong PFin(8)
#define Lan PFin(9)


void TongXinSend_Init(void);//初始化
void HongLan_Init(void);//初始化
void TongXinReceive_Init(void);	 				    
#endif
