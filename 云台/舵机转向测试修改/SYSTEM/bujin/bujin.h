#ifndef __BUJIN_H
#define __BUJIN_H	

#include "sys.h"



#define EN PAout(4)
#define DIR PAout(5)

void bujin_Init(void);	//≥ı ºªØ
void pwm_Init(u16 arr,u16 psc);
void bujin_left(u16 crr);
void bujin_right(u16 crr);
#endif

