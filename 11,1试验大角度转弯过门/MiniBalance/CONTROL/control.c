#include "control.h"	
#include "filter.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
int Balance_Pwm,Velocity_Pwm,Turn_Pwm,TWO_DIAN_PWM,t1;
u8 Flag_Target;
u32 Flash_R_Count;
/*****************************�ߵ�PID*************************************/
//��λ������
extern float pos_x;   
extern float pos_y;   
extern float zangle;   
extern float xangle;   
extern float yangle;   
extern float w_z;
//#define ACT0  u3_printf("ACT0")����û��
//pid�������弰��ʼ��
u32   err_last=0.0;            //x��һ��λ�ò�ֵ
float err_x=0.0;                //xλ�ò�ֵ
float err_y=0.0;                //yλ�ò�ֵ
float err_xy=0.0;
float err_pid=0.0;            //y��һ��λ�ò�ֵ
float left;
float right;
float omga=0.0;
float cta=0.0;   
float err_old;
extern float pos_x_1;
extern float pos_y_1;

/*********************������Ӻ���************************/
float Pi;                               //-180<zangleErr<180 ʱ��ӦPID����
float left_err;
float right_err;

float zangleErr;                        //-360<zangleErr<-180ʱ��ӦPID����  
float zangle_pid;
float zangle_old;
float zangle_last;
float zangle_new;
float zangleErrErr=0.0;

float PI_v1;                            //-360<zangleErr<-180ʱ��ӦPID����  
float zangleErr_v1;
float zangle_old_v1;
float zangle_pid_v1;
float zangle_last_v1;
float zangleErrErr_v1;

float PI_v2;                            //180<zangleErr<360ʱ��ӦPID����
float zangleErr_v2;
float zangle_old_v2;
float zangle_pid_v2;
float zangle_last_v2;
float zangleErrErr_v2;


/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
         5ms��ʱ�ж���MPU6050��INT���Ŵ���
         �ϸ�֤���������ݴ����ʱ��ͬ��				 
**************************************************************************/
int EXTI15_10_IRQHandler(void) 
{    
	 if(INT==0)		
	{   
		  EXTI->PR=1<<12;                                                      //����жϱ�־λ   
		   Flag_Target=!Flag_Target;
//		  if(delay_flag==1)
//			 {
//				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //���������ṩ50ms�ľ�׼��ʱ
//			 }
		  if(Flag_Target==1)                                                  //5ms��ȡһ�������Ǻͼ��ٶȼƵ�ֵ�����ߵĲ���Ƶ�ʿ��Ը��ƿ������˲��ͻ����˲���Ч��
			{
			Get_Angle(Way_Angle);                                               //===������̬		
			return 0;	                                               
			}                                                                   //10ms����һ�Σ�Ϊ�˱�֤M�����ٵ�ʱ���׼�����ȶ�ȡ����������
			Encoder_Left=Read_Encoder(2);                                       //===��ȡ��������ֵ
			Encoder_Right=Read_Encoder(4);                                      //===��ȡ��������ֵ
//			if(Stop==1)
//			{
				Get_Angle(Way_Angle);                                               //===������̬	                                     	
				Key();                                                              //===ɨ�谴��״̬ ����˫�����Ըı�С������״̬
				Balance_Pwm =balance(Angle_Balance,Gyro_Balance);                   //===ƽ��PID����	
				Velocity_Pwm=velocity(Encoder_Left,Encoder_Right,Sudu);                  //===�ٶȻ�PID����	 ��ס���ٶȷ�����������������С�����ʱ��Ҫ����������Ҫ���ܿ�һ��
//				if(Stop==0)TWO_DIAN_PWM=TWO_DIAN_PD(1000,3000);
	// 	    Turn_Pwm    =turn(Encoder_Left,Encoder_Right,Gyro_Turn);            //===ת��PID����     
				Moto1=Balance_Pwm+Velocity_Pwm-Turn_Pwm-TWO_DIAN_PWM;                            //===�������ֵ������PWM
				Moto2=Balance_Pwm+Velocity_Pwm+Turn_Pwm+TWO_DIAN_PWM;                            //===�������ֵ������PWM
				Xianfu_Pwm();                                                       //===PWM�޷�                                                      //===��������¾��������
		    if(Turn_Off(Angle_Balance)==0)                              //===����������쳣
//					printf("dianji PWM \r\n");
				Set_Pwm(Moto1,Moto2);  //===��ֵ��PWM�Ĵ��� 
//			}				 
	}       	
	 return 0;	  
} 

/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕȡ����ٶ�
����  ֵ��ֱ������PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int balance(float Angle,float Gyro)
{  
   float Bias;
	 int balance;
	 Bias=Angle-ZHONGZHI;                       //===���ƽ��ĽǶ���ֵ �ͻ�е���
	 balance=Balance_Kp*Bias+Gyro*Balance_Kd;   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
	 return balance;
}

/**************************************************************************
�������ܣ��ٶ�PI���� �޸�ǰ�������ٶȣ�����Target_Velocity�����磬�ĳ�60�ͱȽ�����
��ڲ��������ֱ����������ֱ�����
����  ֵ���ٶȿ���PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int velocity(int encoder_left,int encoder_right,int sudu)
{  
     static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Encoder_Integral,Target_Velocity;
	  //=============ң��ǰ�����˲���=======================// 
	  if(Bi_zhang==1&&Flag_sudu==1)  Target_Velocity=55;                 //����������ģʽ,�Զ��������ģʽ
    else 	                         Target_Velocity=110;                 
		if(1==Flag_Qian)    	Movement=-Target_Velocity/Flag_sudu;	         //===ǰ����־λ��1 
		else if(1==Flag_Hou)	Movement=Target_Velocity/Flag_sudu;         //===���˱�־λ��1
	  else  Movement=0;	
	  if(Bi_zhang==1&&Distance<500&&Flag_Left!=1&&Flag_Right!=1)        //���ϱ�־λ��1�ҷ�ң��ת���ʱ�򣬽������ģʽ
	  Movement=Target_Velocity/Flag_sudu;
   //=============�ٶ�PI������=======================//	
		Encoder_Least =(encoder_left+encoder_right)-sudu;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
		Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
		Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
		Encoder_Integral=Encoder_Integral-Movement;                       //===����ң�������ݣ�����ǰ������
		if(Encoder_Integral>20000)  	Encoder_Integral=20000;             //===�����޷�
		if(Encoder_Integral<-20000)	Encoder_Integral=-20000;              //===�����޷�	
		Velocity=Encoder*Velocity_Kp+Encoder_Integral*Velocity_Ki;        //===�ٶȿ���	
		if(Turn_Off(Angle_Balance)==1||Flag_Stop==1)   Encoder_Integral=0;      //===����رպ��������
	  return Velocity;
}

/**************************************************************************
�������ܣ�ת�����  �޸�ת���ٶȣ����޸�Turn_Amplitude����
��ڲ��������ֱ����������ֱ�������Z��������
����  ֵ��ת�����PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//ת�����
{
	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Turn_Amplitude=88/Flag_sudu,Kp=42,Kd=0;     
	  //=============ң��������ת����=======================//
  	if(1==Flag_Left||1==Flag_Right)                      //��һ������Ҫ�Ǹ�����תǰ���ٶȵ����ٶȵ���ʼ�ٶȣ�����С������Ӧ��
		{
			if(++Turn_Count==1)
			Encoder_temp=myabs(encoder_left+encoder_right);
			Turn_Convert=50/Encoder_temp;
			if(Turn_Convert<0.6)Turn_Convert=0.6;
			if(Turn_Convert>3)Turn_Convert=3;
		}	
	  else
		{
			Turn_Convert=0.9;
			Turn_Count=0;
			Encoder_temp=0;
		}			
		if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
		else if(1==Flag_Right)	     Turn_Target+=Turn_Convert; 
		else Turn_Target=0;
	
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===ת���ٶ��޷�
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
		if(Flag_Qian==1||Flag_Hou==1)  Kd=0.5;        
		else Kd=0;   //ת���ʱ��ȡ�������ǵľ��� �е�ģ��PID��˼��
  	//=============ת��PD������=======================//
		Turn=-Turn_Target*Kp-gyro*Kd;                 //===���Z�������ǽ���PD����
	  return Turn;
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
    	if(moto1>0)			AIN2=0,			AIN1=1;
			else 	          AIN2=1,			AIN1=0;
			PWMA=myabs(moto1);
		  if(moto2>0)	BIN1=0,			BIN2=1;
			else        BIN1=1,			BIN2=0;
			PWMB=myabs(moto2);	
}

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=13000;    //===PWM������7200 ������6900
//		if(Flag_Qian==1)  Moto1+=DIFFERENCE;  //DIFFERENCE��һ������ƽ��С������ͻ�е��װ�����һ��������ֱ���������������С�����и��õ�һ���ԡ�
//	  if(Flag_Hou==1)   Moto2-=DIFFERENCE;
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
}
/**************************************************************************
�������ܣ������޸�С������״̬ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Key(void)
{	
	if(KEY==0)Flag_Stop=0;
	else Flag_Stop=1;
}

/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������Ǻ͵�ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
u8 Turn_Off(float angle)
{
	    u8 temp;
			if(angle<-40||angle>40||1==Flag_Stop||Motor_Stay==1)//��ص�ѹ����11.1V�رյ��
			{	                                                 //===��Ǵ���40�ȹرյ��
      temp=1;                                            //===Flag_Stop��1�رյ��
			AIN1=0;                                            
			AIN2=0;
			BIN1=0;
			BIN2=0;
      }
			else
      temp=0;
      return temp;			
}
	
/**************************************************************************
�������ܣ���ȡ�Ƕ� �����㷨�������ǵĵ�У�����ǳ����� 
��ڲ�������ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
����  ֵ����
**************************************************************************/
void Get_Angle(u8 way)
{ 
	    float Accel_Y,Accel_Angle,Accel_Z,Gyro_X,Gyro_Z;
	    if(way==1)                           //===DMP�Ķ�ȡ�����ݲɼ��ж϶�ȡ���ϸ���ѭʱ��Ҫ��
			{	
					Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
					Angle_Balance=-Roll;             //===����ƽ�����
					Gyro_Balance=-gyro[0];            //===����ƽ����ٶ�
					Gyro_Turn=gyro[2];               //===����ת����ٶ�
				  Acceleration_Z=accel[2];         //===����Z����ٶȼ�
				
//					/**��**/	
//				  Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
//				  Angle_Balance=-Pitch;             //===����ƽ�����
////					Angle_Turn=-Yaw;
////					if(Angle_Turn<0)       Angle_Turn+=360;
//				  Gyro_Balance=-gyro[1];               //===����ת����ٶ�
//					Gyro_Turn=gyro[2];               //===����ת����ٶ�
//				  Acceleration_Z=accel[2];         //===����Z����ٶȼ�
			}			
      else
      {
			Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //��ȡY��������
			Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
		  Accel_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //��ȡX����ٶȼ�
	  	Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
		  if(Gyro_X>32768)  Gyro_X-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
			if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
	  	if(Accel_Y>32768) Accel_Y-=65536;                      //��������ת��
		  if(Accel_Z>32768) Accel_Z-=65536;                      //��������ת��
			Gyro_Balance=Gyro_X;                                  //����ƽ����ٶ�
	   	Accel_Angle=atan2(Accel_Y,Accel_Z)*180/PI;                 //�������	
			Gyro_X=Gyro_X/16.4;                                    //����������ת��	
      if(Way_Angle==2)		  	Kalman_Filter(Accel_Angle,Gyro_X);//�������˲�	
			else if(Way_Angle==3)   Yijielvbo(Accel_Angle,Gyro_X);    //�����˲�
	    Angle_Balance=angle;                                   //����ƽ�����
			Gyro_Turn=Gyro_Z;                                      //����ת����ٶ�
			Acceleration_Z=Accel_Z;                                //===����Z����ٶȼ�	
		}
}
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/*********************������Ӻ���***************************************/
//��λ�ֺ�������0-180���ұ�0--180.
//SetSpeed_x        Ŀ��x����
//SetSpeed_y        Ŀ��y����
//P                 ����P
//D                 ����D
/*********************������Ӻ���***************************************/
int TWO_DIAN_PD(float SetSpeed_x,float SetSpeed_y)
{
	int static TWO_DIAN_PD;
	if(Zhuan)
		Sudu=0;
	else if(Zou==1) 
		Sudu=-30;
	else 
		Sudu=30;
	while(1)
	{
//		if(KEY==0) break;
	  if((SetSpeed_x<pos_x_1+100)&&(SetSpeed_x>pos_x_1-100)&&(pos_x!=0))  //Ŀ�����Χ
		{				
				if((SetSpeed_y<pos_y_1+100)&&(SetSpeed_y>pos_y_1-100)&&(pos_y!=0))
				{	
					Sudu=0;
//					Stop=1;
//					return 0;
							break;	
				}
		}
		#define P2  30//1.8f   //3.2f    P         1.6     2.6             1.8
		#define P4  0//0.0f   //0.0f    I     Speed=150;  Speed=220      Speed=250
		#define P3  0//0.4f   //1.0f    D         0.5     0.8               0.4
	//Ŀ������������ڵĵ�ĽǶȲ�ֵcta��ͨ��arctan�����Ǻ������㡣
		 err_x=SetSpeed_x-pos_x_1;  //X���ֵ
		 err_y=SetSpeed_y-pos_y_1;  //y���ֵ
		 cta=atan(err_y/err_x)*57.29578;
	//Ŀ��Ƕ�omga�ļ���
		
		if((err_x>0)&&(err_y>0))
			omga=cta+0;  //��һ����ʱ
		else if((err_x<0)&&(err_y>0))
			omga=cta+180;  //�ڶ�����ʱ
		else if((err_x>0)&&(err_y<0))
			omga=cta+360;  //��������ʱ
		else if((err_x<0)&&(err_y<0))
			omga=cta+180;  //��������ʱ  
		
	//Ŀ��㺽�������ϵ���¶��壬����Ϊ0-360  ת���ɳ���ʹ������
		if(zangle>=-90&&zangle<180)
			 zangle_new=zangle+90;
		else if(zangle<-90&&zangle>=-180)
			 zangle_new=zangle+450;
		
		zangleErr=omga-zangle_new;
	//�ǶȲ�ֵȡֵ�ж�
		
		if(zangleErr>=-360&&zangleErr<-180)    
		{
			zangleErr_v1=-360-zangleErr;
		}
		if(zangleErr>180&&zangleErr<=360)     
		{
			zangleErr_v2=360-zangleErr;
		}

		zangle_last=zangleErr+zangle_last;                    //-180<zangleErr<180 ʱ��ӦPID
		Pi=P4*zangle_last;
		if(Pi>=20)     Pi=20;  //I�޷�
		zangleErrErr=zangleErr-zangle_old;//������Ĳ�
		zangle_old=zangleErr;
		zangle_pid=P2*zangleErr+Pi+P3*zangleErrErr;              

		zangle_last_v1=zangleErr_v1+zangle_last_v1;            //-360<zangleErr<-180ʱ��ӦPID  
		PI_v1=P4*zangle_last_v1;
		if(PI_v1 >=20)     PI_v1=20;  //I�޷�	
		zangleErrErr_v1=zangleErr_v1-zangle_old_v1;            
		zangle_old_v1=zangleErr_v1;
		zangle_pid_v1=P2*zangleErr_v1+PI_v1 +P3*zangleErrErr;    
		
		zangle_last_v2=zangleErr_v2+zangle_last_v2;             //180<zangleErr<360ʱ��ӦPID      
		PI_v2=P4*zangle_last_v2;
		if(PI_v2>=20)     PI_v2 =20;  //I�޷�	
		zangleErrErr_v2=zangleErr_v2-zangle_old_v2;             
		zangle_old_v2=zangleErr_v2;
		zangle_pid_v2=P2*zangleErr_v2+PI_v2 +P3*zangleErrErr;    

	//��Ӧ�ǶȲ�ת�������ٶ�	0�����ٶȿ������� //�̶���������Ҽ�
			if(zangleErr<=180&&zangleErr>=-180)       
			{
				TWO_DIAN_PD=-zangle_pid;
			}
			
			if(zangleErr<-180&&zangleErr>=-360)
			{
				TWO_DIAN_PD=zangle_pid_v1;		
			}
			
			if(zangleErr<=360&&zangleErr>180)
			{	
				TWO_DIAN_PD=zangle_pid_v2;			
			}
			TWO_DIAN_PWM=TWO_DIAN_PD;
			if(Zhuan)  
			{
				t1++;
				if(t1==30000) 
				{
					t1=0;
					break;
				}
			}
		}
	return 0;
}


























void wey_walk(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(0,500);
	TWO_DIAN_PD(-335,2040);//y+30
	Zhuan=1;
	TWO_DIAN_PD(-335,2800);
	Motor_Stay=1;

}	


/************************************�쳡*********************************************/
void HWalk1(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(0,500);
	TWO_DIAN_PD(-650,2030);			//ɲ��Ҫ��720
	TWO_DIAN_PD(-699,3700);
	Zhuan=1;
	TWO_DIAN_PD(-729,4350);
	Motor_Stay=1;
}
void HWalkBack1(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(729,-4000);			//335 3170
	Zhuan=1;
	TWO_DIAN_PD(729,-3400);			//335 2370
	Motor_Stay=1;
}

void HWalk2(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(0,500);
	TWO_DIAN_PD(-335,4040);//y+30
	Zhuan=1;
	TWO_DIAN_PD(-335,4800);
	Motor_Stay=1;

}
void HWalkBack2(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(335,-3170);
	Zhuan=1;
	TWO_DIAN_PD(335,-2370);
	Motor_Stay=1;
}
void HWalk3(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(-710,4120);
	Zhuan=1;
	TWO_DIAN_PD(-710,4800);
	Motor_Stay=1;

}
void HWalkBack3(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(710,-3170);
	Zhuan=1;
	TWO_DIAN_PD(710,-2370);
	Motor_Stay=1;
}
void HWalk4(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(-1085,4120);
	Zhuan=1;
	TWO_DIAN_PD(-1085,4800);
	Motor_Stay=1;

}
void HWalkBack4(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(1085,-3170);
	Zhuan=1;
	TWO_DIAN_PD(1085,-2370);
	Motor_Stay=1;
}
void HWalk5(void)//���y��-20
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(-1430,4080);
	Zhuan=1;
	TWO_DIAN_PD(-1430,4800);
	Motor_Stay=1;

}
void HWalkBack5(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(710,-3170);
	Zhuan=1;
	TWO_DIAN_PD(710,-2370);
	Motor_Stay=1;
}
/*************************************************************************************/
/************************************����*********************************************/
void LWalk1(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
//	TWO_DIAN_PD(100,500);
	TWO_DIAN_PD(20,4050);
	Zhuan=1;
	TWO_DIAN_PD(20,4800);
	Motor_Stay=1;

}
void LWalkBack1(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(-340,-3170);
	Zhuan=1;
	TWO_DIAN_PD(-340,-2370);
	Motor_Stay=1;
}
void LWalk2(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(0,500);
	TWO_DIAN_PD(340,4050);//Y+30
	Zhuan=1;
	TWO_DIAN_PD(340,4800);
	Motor_Stay=1;

}
void LWalkBack2(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(-340,-3170);
	Zhuan=1;
	TWO_DIAN_PD(-340,-2370);
	Motor_Stay=1;
}
void LWalk3(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(715,4100);
	Zhuan=1;
	TWO_DIAN_PD(715,4800);
	Motor_Stay=1;

}
void LWalkBack3(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(-715,-3170);
	Zhuan=1;
	TWO_DIAN_PD(-715,-2370);
	Motor_Stay=1;
}
void LWalk4(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(1090,4080);
	Zhuan=1;
	TWO_DIAN_PD(1090,4800);
	Motor_Stay=1;

}
void LWalkBack4(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(-1090,-3170);
	Zhuan=1;
	TWO_DIAN_PD(-1090,-2370);
	Motor_Stay=1;
}
void LWalk5(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//�ٶ�=-30
	TWO_DIAN_PD(1400,4120);
	Zhuan=1;
	TWO_DIAN_PD(1400,4800);
	Motor_Stay=1;

}
void LWalkBack5(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	Zhuan=0;
	Zou=0;//�ٶ�=30
	TWO_DIAN_PD(-715,-3170);
	Zhuan=1;
	TWO_DIAN_PD(-715,-2370);
	Motor_Stay=1;
}
/**************************************************/

