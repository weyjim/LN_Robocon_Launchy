#ifndef __MOTOR12_H
#define __MOTOR12_H
#include <sys.h>	 
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define IN1 PBout(15)//电机1 IN1---PB15
#define IN2 PBout(14)//电机1 IN2---PB14
#define AAAA PFin(8)
void motor12_Init(void);//初始化
#endif
