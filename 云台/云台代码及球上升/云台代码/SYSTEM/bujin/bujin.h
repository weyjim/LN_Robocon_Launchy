#ifndef __BUJIN_H
#define __BUJIN_H	

#include "sys.h"


/*��һ������� EN DIR*/
#define EN0 PAout(4)
#define DIR0 PAout(5)
/*�ڶ���������� EN DIR*/
#define EN1	PAout(1)
#define DIR1 PAout(2)

void bujin_Init(void);	//��ʼ��
void pwm_Init(u16 arr,u16 psc);
void bujin_claw_up(u16 crr,u16 ms);
void bujin_claw_down(u16 crr,u16 ms);
void bujin_ball_up(u16 crr,u16 ms);
void bujin_ball_down(u16 crr,u16 ms);

#endif

