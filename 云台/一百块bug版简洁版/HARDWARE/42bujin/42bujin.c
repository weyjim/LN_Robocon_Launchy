# include "42bujin.h"
# include "delay.h"
//IO初始化
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
 
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟

	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14|GPIO_Pin_15;//KEY0-KEY1
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//细分
//  x==1 全步
//  x==2 半步 
//  x==4 1/4步
//  x==8 1/8步
//  x==16 1/16步

//参数
//  dir:FALSE 正转TRUE反转
//  period 周期
//  step   脉冲
void Step_Control(u8 dir,u16 period,u32 steps)
{
    u32 i;
  for(i=0; i <= steps;i++)
  {
    PBout(9) = dir;
    PBout(8) = 1;
    delay_us(1);
    PBout(8) = 0;
    delay_us(period);//period??D?￡?×a?ù???ì￡?2?òaD?óú1000
  }
}
//此函数可抱死
//  0 抱死
//  1 正常
//void Step_Enable()
//{
//    PBout(15) = 0;
//}

////////////////////////////////////////////////////////////////////////


//void low_ok()//到地方了发高电平信号，其他拉低
//{
//	close = 1;
//	middle_state = 0;
//	open = 0;
//}
//void middle_ok()//到地方了发高电平信号，其他拉低
//{
//	low_state = 0;
//	middle_state = 1;
//	high_state = 0;
//}
//void high_ok()//到地方了发高电平信号，其他拉低
//{
//	open = 0;
//	middle_state = 0;
//	close = 1;
//}
//void service_reset()//清楚给舵机的高电平信号
//{
//	close = 0;
//	middle_state = 0;
//	open = 0;
//	action_ok = 0;//动作完毕标志复位;
//}
void up_num_step(int set_num)//上升
{
	for(num=0;num < set_num;num++)
	{
		Step_Control(0,1600,200);//正转

//Step_Enable();//抱死
//		delay_ms(50);
	}
	up_finish = 1;
//	open = 1;
//	delay_ms(3000);
}
void down_num_step(int set_num)//下降
{
//	int down_finish = 0;
	for(num=0;num < set_num;num++)
	{
		Step_Control(1,1600,200);//反转
		
//Step_Enable();//抱死
//		delay_ms(50);
	}	
	down_finish = 1;
}
