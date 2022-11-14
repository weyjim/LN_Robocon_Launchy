#include "stm32f10x.h"
#include "sys.h"
#include "control.h"
#include "Action_Running.h"
  /**************************************************************************
���ߣ�����Ԣ١�����Ե��
VX��17640682245��weyjim
QQ: 1611860702��772573480
�ر���л:ƽ��С��֮��
**************************************************************************/

/***��������***/
u8 Way_Angle=1,Stop=1,Zou=1,ZuoBiao_contrary=0;         //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����
u8 Flag_Stop=1,Flag_Show=0;                		//**ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ�� 
u8 Motor_Stay=0;								//�ƶ���־λ��1Ϊ�ƶ�
int Encoder_Left,Encoder_Right,Sudu,t,Zhuan=0;           //���ұ��������������
int Moto1,Moto2;                            	//���PWM����
int Temperature;                            	//**��ʾ�¶�
float Angle_Balance,Gyro_Balance,Gyro_Turn; 	//ƽ����� ƽ�������� ת��������
float Show_Data_Mb;                         	//**ȫ����ʾ������������ʾ��Ҫ�鿴������
u32 Distance;                               	//**���������
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send; //��ʱ�͵��εȱ���
float Acceleration_Z;                      		//Z����ٶȼ�  
float Balance_Kp=420,Balance_Kd=0.7416,Velocity_Kp=0,Velocity_Ki=0.75;	//PID����     700  1.45   1.42
u16 PID_Parameter[10],Flash_Parameter[10];  	//**Flash�������
//'**'���ΪԤ����־λ���壬����Ŀδʹ��

#define Red 1
#define Blue 2 

void MAIN_Init(void);

int main(void)
{	
	MAIN_Init();
//	while(pos_x==0&&pos_y==0)	//�ȴ���λ�ֳ�ʼ��
//	{
//		printf("Wait \r\n");
//	}
		
    while(1)
	{
		SendGetF10=0;
		if(Red_Field==0)
		{
			HWalk1(); //ȡ�м���
			Arrived();
			HWalkBack1();//ȡ�м��򵹳�
			
			HWalk2();//ȡ�Ҳ��һ����
			Arrived();
			HWalkBack2();//ȡ�Ҳ��һ���򵹳�
			
			HWalk3();//ȡ�Ҳ�ڶ�����
			Arrived();
			HWalkBack3();//ȡ�Ҳ�ڶ����򵹳�
			
			HWalk4();//ȡ����һ����
			Arrived();
			HWalkBack4();//ȡ����һ���򵹳�
			
			HWalk5();//ȡ���ڶ�����
			Arrived();
			while(1)
				printf("Finished\n");
		}
		else if(Blue_field==0)
		{
			LWalk1(); //ȡ�м���
			Arrived();
			LWalkBack1();//ȡ�м��򵹳�
			
			LWalk2();//ȡ�Ҳ��һ����
			Arrived();
			LWalkBack2();//ȡ�Ҳ��һ���򵹳�
			
			LWalk3();//ȡ�Ҳ�ڶ�����
			Arrived();
			LWalkBack3();//ȡ�Ҳ�ڶ����򵹳�
			
			LWalk4();//ȡ����һ����
			Arrived();
			LWalkBack4();//ȡ����һ���򵹳�
			
			LWalk5();//ȡ���ڶ�����
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
	delay_init();	    	            //=====��ʱ������ʼ��
	uart_init(115200);	            //=====���ڳ�ʼ��Ϊ
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	TongXinSend_Init();                 //��ʼ��
	TongXinReceive_Init();
	HongLan_Init();
	  
	KEY_Init();                     //=====������ʼ��
	MY_NVIC_PriorityGroupConfig(2);	//=====�����жϷ���
	MiniBalance_PWM_Init(14399,0);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� 
	usart3_init(115200);               //=====����3��ʼ��
	Encoder_Init_TIM2();            //=====�������ӿ�
	Encoder_Init_TIM4();            //=====��ʼ��������2
	IIC_Init();                     //=====IIC��ʼ��
	MPU6050_initialize();           //=====MPU6050��ʼ��	
	DMP_Init();                     //=====��ʼ��DMP 
	OLED_Init();                    //=====OLED��ʼ��	    
	MiniBalance_EXTI_Init();        //=====MPU6050 5ms��ʱ�жϳ�ʼ��
}
