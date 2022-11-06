# include "42bujin.h"
# include "delay.h"
//IO��ʼ��
int set_num;
int num;
int down_finish;
int up_finish;
void MOTOR_Init(void)
{
//  RCC->APB2ENR|=1<<3;
//  GPIOB->CRH&=0xff000000;
//  GPIOB->CRH|=0x00333333;
		
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);            //GPIO CLOCK ENABLE  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_12;  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		


}

void Received_order_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
 
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��

	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14|GPIO_Pin_15;//KEY0-KEY1
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//ϸ��
//  x==1 ȫ��
//  x==2 �벽 
//  x==4 1/4��
//  x==8 1/8��
//  x==16 1/16��

//����
//  dir:FALSE ��תTRUE��ת
//  period ����
//  step   ����
void Step_Control(u8 dir,u16 period,u32 steps)
{
    u32 i;
  for(i=0; i <= steps;i++)
  {
    PBout(9) = dir;
    PBout(8) = 1;
    delay_us(1);
    PBout(8) = 0;
    delay_us(period);//period??D?��?��a?��???����?2?��aD?����1000
  }
}
//�˺����ɱ���
//  0 ����
//  1 ����
//void Step_Enable()
//{
//    PBout(15) = 0;
//}

////////////////////////////////////////////////////////////////////////


//void low_ok()//���ط��˷��ߵ�ƽ�źţ���������
//{
//	close = 1;
//	middle_state = 0;
//	open = 0;
//}
//void middle_ok()//���ط��˷��ߵ�ƽ�źţ���������
//{
//	low_state = 0;
//	middle_state = 1;
//	high_state = 0;
//}
//void high_ok()//���ط��˷��ߵ�ƽ�źţ���������
//{
//	open = 0;
//	middle_state = 0;
//	close = 1;
//}
//void service_reset()//���������ĸߵ�ƽ�ź�
//{
//	close = 0;
//	middle_state = 0;
//	open = 0;
//	action_ok = 0;//������ϱ�־��λ;
//}
void up_num_step(int set_num)//����
{
	for(num=0;num < set_num;num++)
	{
		Step_Control(0,1600,200);//��ת

//Step_Enable();//����
//		delay_ms(50);
	}
	up_finish = 1;
//	open = 1;
//	delay_ms(3000);
}
void down_num_step(int set_num)//�½�
{
//	int down_finish = 0;
	for(num=0;num < set_num;num++)
	{
		Step_Control(1,1600,200);//��ת
		
//Step_Enable();//����
//		delay_ms(50);
	}	
	down_finish = 1;
}
