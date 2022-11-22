#ifndef __KEY_H
#define __KEY_H

#include"sys.h"

//#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
//#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
//#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)

#define KEY0 PEin(4)
#define KEY1 PEin(3)
#define WK_UP PAin(0)

#define KEY0_PRES 1
#define KEY1_PRES 2
#define WKUP_PRES 3

void KEY_Init(void);			//头文件中定义函数括号内要有void？？？(warning)
u8 KEY_Scan(u8);

#endif
