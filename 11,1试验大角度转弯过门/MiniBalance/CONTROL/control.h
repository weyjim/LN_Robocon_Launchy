#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
#define ZHONGZHI 1
#define DIFFERENCE 100
extern	int Balance_Pwm,Velocity_Pwm,Turn_Pwm,TWO_DIAN_PWM;
int EXTI15_10_IRQHandler(void);
int balance(float angle,float gyro);
int velocity(int encoder_left,int encoder_right,int sudu);
int turn(int encoder_left,int encoder_right,float gyro);
int TWO_DIAN_PD(float SetSpeed_x,float SetSpeed_y);
void Set_Pwm(int moto1,int moto2);
void Key(void);
void Xianfu_Pwm(void);
u8 Turn_Off(float angle);
void Get_Angle(u8 way);
int myabs(int a);

void wey_walk(void);

void HWalk1(void);              //���з�1
void HWalk2(void);
void HWalk3(void);
void HWalk4(void);
void HWalk5(void);

void HWalkBack1(void);//����
void HWalkBack2(void);//����
void HWalkBack3(void);//����
void HWalkBack4(void);//����
void HWalkBack5(void);//����

void LWalk1(void);              //���з�1
void LWalk2(void);
void LWalk3(void);
void LWalk4(void);
void LWalk5(void);

void LWalkBack1(void);//����
void LWalkBack2(void);//����
void LWalkBack3(void);//����
void LWalkBack4(void);//����
void LWalkBack5(void);//����

#endif
