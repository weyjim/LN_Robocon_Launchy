#ifndef _42bujin_H_
#define _42bujin_H_
#include "sys.h"




#define getball_order  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����0
#define putball_order  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����1
#define close  PBout(11)//�ײ���λ��
#define middle_state  PBout(6)//�м�λ��
#define open  PBout(0)//��߼�λ��
#define action_ok PBout(12)//���ߵ��̶������


//ϸ�ֺ궨��


//#define Full_step {MS1 = 0;MS2 = 0;MS3 = 0;}                  
//#define Half_step {MS1 = 1;MS2 = 0;MS3 = 0;}
//#define Quarter_step {MS1 = 0;MS2 = 1;MS3 = 0;} 
//#define Eighth_step {MS1 = 1;MS2 = 1;MS3 = 0;}
//#define Sixteenth_step {MS1 = 1;MS2 = 1;MS3 = 1;} 

void MOTOR_Init(void);
//void Step_Micr(u16 x);
//void Step_Enable(void);
void Step_Control(u8 dir,u16 period,u32 steps);
void Received_order_init(void);
//void low_ok(void);
//void high_ok(void);
//void service_reset(void);
void up_num_step(int set_num);
void down_num_step(int set_num);

#endif 
