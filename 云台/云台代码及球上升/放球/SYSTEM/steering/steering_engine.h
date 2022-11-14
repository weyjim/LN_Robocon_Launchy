#ifndef _STEERING_ENGINE_H_
#define _STEERING_ENGINE_H_

#include "stm32f10x.h"

void TIM4_PWM_Init(u16 arr,u16 psc);

void duoji_turn_behind(void);
void duoji_turn_front(void);	//��̨���ת����Ƴ���
void duoji_fushou_left_front(void);
void duoji_fushou_left_behind(void);
void duoji_fushou_right_front(void);
void duoji_fushou_right_behind(void);


#endif
