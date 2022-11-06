/* ms1:0 ms2:0 ms3:1  每10次运动4.32cm
董广辉花费一块钱巨资购买
帅志鸿修改完善
2021-10-14 耻辱留念*/

#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "42bujin.h"
extern int down_finish;
extern int up_finish;
int main()
{
	delay_init();
	uart_init(115200);
	MOTOR_Init();
	Received_order_init();
	up_num_step(4);//上电后升到middle high
	down_finish  = 0;
	up_finish = 0;
	
	
//	   for(i=0;i<10;i++)
//    {
//        Step_Control(1,1600,200);//正转
//    delay_ms(1000);
//        Step_Control(0,1600,200);//反转
//    delay_ms(1000);
//    }
//    Step_Enable();//抱死

	while(1)
	{
//		delay_ms(500);//去噪声
		if (getball_order == 1)
		{
//			delay_ms(1000);
			action_ok = 0;
			down_num_step (4);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
			if (down_finish == 1)
			{
				close = 1;
				delay_ms(1000);
				delay_ms(1000);
//				delay_ms(500);
				down_finish  = 0;
//				down_num_step(4) = 0;
				close = 0;
				if(close == 0)
				{
					delay_ms(50);
					up_num_step (8);
					delay_ms(100);
//					delay_ms(1000);
//					delay_ms(1000);
					
					if(up_finish == 1)
					{
						up_finish  = 0;
						down_num_step(4);
						delay_ms(100);
//						up_finish  = 0;
						if (down_finish  == 1)
						{
							
							open = 1;
							delay_ms(1000);
							delay_ms(1000);
//							delay_ms(1000);
//							down_finish = 0;
							open = 0;
							down_finish  =  0;
							delay_ms (100);
							action_ok  = 1;
							delay_ms (100);
							action_ok  = 0;
						}
//							if(down_finish == 0)
//							{
//								action_ok  = 1;
//								down_num_step(4);
//								action_ok  = 0;
//								delay_ms(100);
////							delay_ms(1000);
////							delay_ms(1000);
////							delay_ms(1000);
//								if(down_finish  == 1)
//								{
////									action_ok  = 1;
									while(getball_order==1)
										{
											delay_ms(50);
										}
//									action_ok  = 0;
										down_finish  = 0;
							}
							
						}
					}
				}
			}


			
		}
		
		

	

	


