#include "stm32f10x.h"
#include "sys.h"
#include "control.h"
#include "Action_Running.h"
  /**************************************************************************
作者：董广辉①、王恩缘②
VX：17640682245、weyjim
QQ: 1611860702、772573480
特别鸣谢:平衡小车之家
**************************************************************************/

/***参数定义***/
u8 Way_Angle=1,Stop=1,Zou=1,ZuoBiao_contrary=0;         //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //蓝牙
u8 Flag_Stop=1,Flag_Show=0;                		//**停止标志位和 显示标志位 默认停止 显示打开 
u8 Motor_Stay=0;								//制动标志位。1为制动
int Encoder_Left,Encoder_Right,Sudu,t,Zhuan=0;           //左右编码器的脉冲计数
int Moto1,Moto2;                            	//电机PWM变量
int Temperature;                            	//**显示温度
float Angle_Balance,Gyro_Balance,Gyro_Turn; 	//平衡倾角 平衡陀螺仪 转向陀螺仪
float Show_Data_Mb;                         	//**全局显示变量，用于显示需要查看的数据
u32 Distance;                               	//**超声波测距
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send; //延时和调参等变量
float Acceleration_Z;                      		//Z轴加速度计  
float Balance_Kp=420,Balance_Kd=0.7416,Velocity_Kp=0,Velocity_Ki=0.75;	//PID参数     700  1.45   1.42
u16 PID_Parameter[10],Flash_Parameter[10];  	//**Flash相关数组
//'**'标记为预留标志位定义，本项目未使用

#define Red 1
#define Blue 2 

void MAIN_Init(void);

int main(void)
{	
	MAIN_Init();
//	while(pos_x==0&&pos_y==0)	//等待定位轮初始化
//	{
//		printf("Wait \r\n");
//	}
		
    while(1)
	{
		SendGetF10=0;
		if(Red_Field==0)
		{
			HWalk1(); //取中间球
			Arrived();
			HWalkBack1();//取中间球倒车
			
			HWalk2();//取右侧第一个球
			Arrived();
			HWalkBack2();//取右侧第一个球倒车
			
			HWalk3();//取右侧第二个球
			Arrived();
			HWalkBack3();//取右侧第二个球倒车
			
			HWalk4();//取左侧第一个球
			Arrived();
			HWalkBack4();//取左侧第一个球倒车
			
			HWalk5();//取左侧第二个球
			Arrived();
			while(1)
				printf("Finished\n");
		}
		else if(Blue_field==0)
		{
			LWalk1(); //取中间球
			Arrived();
			LWalkBack1();//取中间球倒车
			
			LWalk2();//取右侧第一个球
			Arrived();
			LWalkBack2();//取右侧第一个球倒车
			
			LWalk3();//取右侧第二个球
			Arrived();
			LWalkBack3();//取右侧第二个球倒车
			
			LWalk4();//取左侧第一个球
			Arrived();
			LWalkBack4();//取左侧第一个球倒车
			
			LWalk5();//取左侧第二个球
			Arrived();
			while(1)
				printf("Finished\n");
		}
		else
			printf("Waiting Field\n");
	}
	
}




void MAIN_Init()
{
	delay_init();	    	            //=====延时函数初始化
	uart_init(115200);	            //=====串口初始化为
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
	TongXinSend_Init();                 //初始化
	TongXinReceive_Init();
	HongLan_Init();
	  
	KEY_Init();                     //=====按键初始化
	MY_NVIC_PriorityGroupConfig(2);	//=====设置中断分组
	MiniBalance_PWM_Init(14399,0);   //=====初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口 
	usart3_init(115200);               //=====串口3初始化
	Encoder_Init_TIM2();            //=====编码器接口
	Encoder_Init_TIM4();            //=====初始化编码器2
	IIC_Init();                     //=====IIC初始化
	MPU6050_initialize();           //=====MPU6050初始化	
	DMP_Init();                     //=====初始化DMP 
	OLED_Init();                    //=====OLED初始化	    
	MiniBalance_EXTI_Init();        //=====MPU6050 5ms定时中断初始化
}
