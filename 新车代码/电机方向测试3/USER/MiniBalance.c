#include "stm32f10x.h"
#include "sys.h"
#include "control.h"
#include "motor12.h"
  /**************************************************************************
作者：董广辉
VX：17640682245
QQ: 1611860702
特别鸣谢:平衡小车之家
**************************************************************************/

/*定义了t,t1**/
u8 Way_Angle=1,Stop=1,Zou=1,ZuoBiao_contrary=0;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=0,Zhua_Stop=0;                 //停止标志位和 显示标志位 默认停止 显示打开 //Flag_Stop置1关闭电机
int Encoder_Left,Encoder_Right,Sudu,t,Zhuan=0;             //左右编码器的脉冲计数
int Moto1,Moto2;                            //电机PWM变量 应是Motor的 向Moto致敬	
int Temperature;                            //显示温度
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
float Show_Data_Mb;                         //全局显示变量，用于显示需要查看的数据
u32 Distance;                               //超声波测距
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send; //延时和调参等变量
float Acceleration_Z;                       //Z轴加速度计  
float Balance_Kp=420,Balance_Kd=0.7416,Velocity_Kp=150,Velocity_Ki=0.75;//PID参数     700  1.45   1.42
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash相关数组


int test_flag=0;

int main(void)
  {
		delay_init();	    	            //=====延时函数初始化	
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
		
		
//		uart_init(115200);	            //=====串口初始化为
//		JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
//		JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
//		TongXinSend_Init();                 //初始化
//		TongXinReceive_Init();
//		HongLan_Init();
//	  
//	  KEY_Init();                     //=====按键初始化
//		MY_NVIC_PriorityGroupConfig(2);	//=====设置中断分组
//    MiniBalance_PWM_Init(14399,0);   //=====初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口 
//		usart3_init(115200);               //=====串口3初始化
//    Encoder_Init_TIM2();            //=====编码器接口
//    Encoder_Init_TIM4();            //=====初始化编码器2
//    IIC_Init();                     //=====IIC初始化
//    MPU6050_initialize();           //=====MPU6050初始化	
//    DMP_Init();                     //=====初始化DMP 
//    OLED_Init();                    //=====OLED初始化	    
//	  MiniBalance_EXTI_Init();        //=====MPU6050 5ms定时中断初始化
	  
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

//		    if(Flag_Show==0)          //使用MiniBalance APP和OLED显示屏
//					{
//							oled_show();          //===显示屏打开
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
//					while(delay_flag);	     //通过MPU6050的INT中断实现的50ms精准延时		
//	   } 

