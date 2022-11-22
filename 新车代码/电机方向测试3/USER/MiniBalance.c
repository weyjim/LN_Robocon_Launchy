#include "stm32f10x.h"
#include "sys.h"
#include "control.h"
#include "motor12.h"
  /**************************************************************************
���ߣ������
VX��17640682245
QQ: 1611860702
�ر���л:ƽ��С��֮��
**************************************************************************/

/*������t,t1**/
u8 Way_Angle=1,Stop=1,Zou=1,ZuoBiao_contrary=0;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0,Zhua_Stop=0;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ�� //Flag_Stop��1�رյ��
int Encoder_Left,Encoder_Right,Sudu,t,Zhuan=0;             //���ұ��������������
int Moto1,Moto2;                            //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Temperature;                            //��ʾ�¶�
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float Show_Data_Mb;                         //ȫ����ʾ������������ʾ��Ҫ�鿴������
u32 Distance;                               //���������
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send; //��ʱ�͵��εȱ���
float Acceleration_Z;                       //Z����ٶȼ�  
float Balance_Kp=420,Balance_Kd=0.7416,Velocity_Kp=150,Velocity_Ki=0.75;//PID����     700  1.45   1.42
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash�������


int test_flag=0;

int main(void)
  {
		delay_init();	    	            //=====��ʱ������ʼ��	
		MiniBalance_Motor_Init();
		while(1)
		{
			AIN1=1;
			AIN2=0;
			ENA=1;
			
			BIN1=0;
			BIN2=1;
			ENB=1;
		}
	}
		
		
//		uart_init(115200);	            //=====���ڳ�ʼ��Ϊ
//		JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
//		JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
//		TongXinSend_Init();                 //��ʼ��
//		TongXinReceive_Init();
//		HongLan_Init();
//	  
//	  KEY_Init();                     //=====������ʼ��
//		MY_NVIC_PriorityGroupConfig(2);	//=====�����жϷ���
//    MiniBalance_PWM_Init(14399,0);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� 
//		usart3_init(115200);               //=====����3��ʼ��
//    Encoder_Init_TIM2();            //=====�������ӿ�
//    Encoder_Init_TIM4();            //=====��ʼ��������2
//    IIC_Init();                     //=====IIC��ʼ��
//    MPU6050_initialize();           //=====MPU6050��ʼ��	
//    DMP_Init();                     //=====��ʼ��DMP 
//    OLED_Init();                    //=====OLED��ʼ��	    
//	  MiniBalance_EXTI_Init();        //=====MPU6050 5ms��ʱ�жϳ�ʼ��
	  
//	  test_flag=10;	  
//	  
//		while(pos_x==0&&pos_y==0)
//		{
//			printf("Wait \r\n");
//			test_flag=30;
//			
//		} 
//		test_flag=50;
//    while(1)
//	   {
//		  LWalk1();
//		   test_flag=80;
//		   while(1);
//			if(Hong==0)
//			{
//			 
//					HWalk2();
//				  SendGetF10=1;
//					while(ReceiveF7==0);
//					HWalkBack2();
//				 
//					HWalk3();
//					SendGetF10=1;
//					while(ReceiveF7==0);	
//					HWalkBack3();
//				 
//					HWalk4();
//				  SendGetF10=1;
//					while(ReceiveF7==0);
//					HWalkBack4();
//				 
//					HWalk5();
//					SendGetF10=1;
//					while(ReceiveF7==0);
//					HWalkBack5();
//				
//					HWalk1();
//					SendGetF10=1;
//					while(ReceiveF7==0);
//					HWalkBack1();
//			 
//					while(1);
//			}
//			if(Lan==0)
//			{

//			 
//				 LWalk2();
//				 SendGetF10=1;
//			   while(ReceiveF7==0);
//				 LWalkBack2();
//				 
//				 LWalk3();
//				 SendGetF10=1;
//				 while(ReceiveF7==0);
//				 LWalkBack3();
//				 
//				 LWalk4();
//				 SendGetF10=1;
//				 while(ReceiveF7==0);
//				 LWalkBack4();
//				 
//				 LWalk5();
//		     SendGetF10=1;
//				 while(ReceiveF7==0);
//				 LWalkBack5();
//				
//				 LWalk1();
//				 SendGetF10=1;
//				 while(ReceiveF7==0);
//				 LWalkBack1();
//				 
//				 while(1);
//			}

//		    if(Flag_Show==0)          //ʹ��MiniBalance APP��OLED��ʾ��
//					{
//							oled_show();          //===��ʾ����
//					}
//					printf("%f\r\n",Angle_Balance);
			 
//			 if(pos_x!=0&&pos_y!=0)
//			 {
//					t++;
//					if(t==200)
//					{
//						t=0;
//						Sudu=0;
//					}
//				}
			 
//				  delay_flag=1;	
//					delay_50=0;
//					while(delay_flag);	     //ͨ��MPU6050��INT�ж�ʵ�ֵ�50ms��׼��ʱ		
//	   } 

