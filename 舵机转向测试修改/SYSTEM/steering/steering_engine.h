#ifndef _STEERING_ENGINE_H_
#define _STEERING_ENGINE_H_

#include "stm32f10x.h"

void TIM4_CH1_PWM_Init(u16 arr,u16 psc);

void TIM3_CH2_PWM_Init(u16 arr,u16 psc);

#endif
