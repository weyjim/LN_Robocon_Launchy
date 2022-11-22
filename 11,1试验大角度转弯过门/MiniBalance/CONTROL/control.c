#include "control.h"	
#include "filter.h"	
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
int Balance_Pwm,Velocity_Pwm,Turn_Pwm,TWO_DIAN_PWM,t1;
u8 Flag_Target;
u32 Flash_R_Count;
/*****************************走点PID*************************************/
//定位轮数据
extern float pos_x;   
extern float pos_y;   
extern float zangle;   
extern float xangle;   
extern float yangle;   
extern float w_z;
//#define ACT0  u3_printf("ACT0")清零没用
//pid变量定义及初始化
u32   err_last=0.0;            //x上一次位置差值
float err_x=0.0;                //x位置差值
float err_y=0.0;                //y位置差值
float err_xy=0.0;
float err_pid=0.0;            //y上一次位置差值
float left;
float right;
float omga=0.0;
float cta=0.0;   
float err_old;
extern float pos_x_1;
extern float pos_y_1;

/*********************到点的子函数************************/
float Pi;                               //-180<zangleErr<180 时对应PID参数
float left_err;
float right_err;

float zangleErr;                        //-360<zangleErr<-180时对应PID参数  
float zangle_pid;
float zangle_old;
float zangle_last;
float zangle_new;
float zangleErrErr=0.0;

float PI_v1;                            //-360<zangleErr<-180时对应PID参数  
float zangleErr_v1;
float zangle_old_v1;
float zangle_pid_v1;
float zangle_last_v1;
float zangleErrErr_v1;

float PI_v2;                            //180<zangleErr<360时对应PID参数
float zangleErr_v2;
float zangle_old_v2;
float zangle_pid_v2;
float zangle_last_v2;
float zangleErrErr_v2;


/**************************************************************************
函数功能：所有的控制代码都在这里面
         5ms定时中断由MPU6050的INT引脚触发
         严格保证采样和数据处理的时间同步				 
**************************************************************************/
int EXTI15_10_IRQHandler(void) 
{    
	 if(INT==0)		
	{   
		  EXTI->PR=1<<12;                                                      //清除中断标志位   
		   Flag_Target=!Flag_Target;
//		  if(delay_flag==1)
//			 {
//				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //给主函数提供50ms的精准延时
//			 }
		  if(Flag_Target==1)                                                  //5ms读取一次陀螺仪和加速度计的值，更高的采样频率可以改善卡尔曼滤波和互补滤波的效果
			{
			Get_Angle(Way_Angle);                                               //===更新姿态		
			return 0;	                                               
			}                                                                   //10ms控制一次，为了保证M法测速的时间基准，首先读取编码器数据
			Encoder_Left=Read_Encoder(2);                                       //===读取编码器的值
			Encoder_Right=Read_Encoder(4);                                      //===读取编码器的值
//			if(Stop==1)
//			{
				Get_Angle(Way_Angle);                                               //===更新姿态	                                     	
				Key();                                                              //===扫描按键状态 单击双击可以改变小车运行状态
				Balance_Pwm =balance(Angle_Balance,Gyro_Balance);                   //===平衡PID控制	
				Velocity_Pwm=velocity(Encoder_Left,Encoder_Right,Sudu);                  //===速度环PID控制	 记住，速度反馈是正反馈，就是小车快的时候要慢下来就需要再跑快一点
//				if(Stop==0)TWO_DIAN_PWM=TWO_DIAN_PD(1000,3000);
	// 	    Turn_Pwm    =turn(Encoder_Left,Encoder_Right,Gyro_Turn);            //===转向环PID控制     
				Moto1=Balance_Pwm+Velocity_Pwm-Turn_Pwm-TWO_DIAN_PWM;                            //===计算左轮电机最终PWM
				Moto2=Balance_Pwm+Velocity_Pwm+Turn_Pwm+TWO_DIAN_PWM;                            //===计算右轮电机最终PWM
				Xianfu_Pwm();                                                       //===PWM限幅                                                      //===如果被放下就启动电机
		    if(Turn_Off(Angle_Balance)==0)                              //===如果不存在异常
//					printf("dianji PWM \r\n");
				Set_Pwm(Moto1,Moto2);  //===赋值给PWM寄存器 
//			}				 
	}       	
	 return 0;	  
} 

/**************************************************************************
函数功能：直立PD控制
入口参数：角度、角速度
返回  值：直立控制PWM
作    者：平衡小车之家
**************************************************************************/
int balance(float Angle,float Gyro)
{  
   float Bias;
	 int balance;
	 Bias=Angle-ZHONGZHI;                       //===求出平衡的角度中值 和机械相关
	 balance=Balance_Kp*Bias+Gyro*Balance_Kd;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}

/**************************************************************************
函数功能：速度PI控制 修改前进后退速度，请修Target_Velocity，比如，改成60就比较慢了
入口参数：左轮编码器、右轮编码器
返回  值：速度控制PWM
作    者：平衡小车之家
**************************************************************************/
int velocity(int encoder_left,int encoder_right,int sudu)
{  
     static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Encoder_Integral,Target_Velocity;
	  //=============遥控前进后退部分=======================// 
	  if(Bi_zhang==1&&Flag_sudu==1)  Target_Velocity=55;                 //如果进入避障模式,自动进入低速模式
    else 	                         Target_Velocity=110;                 
		if(1==Flag_Qian)    	Movement=-Target_Velocity/Flag_sudu;	         //===前进标志位置1 
		else if(1==Flag_Hou)	Movement=Target_Velocity/Flag_sudu;         //===后退标志位置1
	  else  Movement=0;	
	  if(Bi_zhang==1&&Distance<500&&Flag_Left!=1&&Flag_Right!=1)        //避障标志位置1且非遥控转弯的时候，进入避障模式
	  Movement=Target_Velocity/Flag_sudu;
   //=============速度PI控制器=======================//	
		Encoder_Least =(encoder_left+encoder_right)-sudu;                    //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零） 
		Encoder *= 0.8;		                                                //===一阶低通滤波器       
		Encoder += Encoder_Least*0.2;	                                    //===一阶低通滤波器    
		Encoder_Integral +=Encoder;                                       //===积分出位移 积分时间：10ms
		Encoder_Integral=Encoder_Integral-Movement;                       //===接收遥控器数据，控制前进后退
		if(Encoder_Integral>20000)  	Encoder_Integral=20000;             //===积分限幅
		if(Encoder_Integral<-20000)	Encoder_Integral=-20000;              //===积分限幅	
		Velocity=Encoder*Velocity_Kp+Encoder_Integral*Velocity_Ki;        //===速度控制	
		if(Turn_Off(Angle_Balance)==1||Flag_Stop==1)   Encoder_Integral=0;      //===电机关闭后清除积分
	  return Velocity;
}

/**************************************************************************
函数功能：转向控制  修改转向速度，请修改Turn_Amplitude即可
入口参数：左轮编码器、右轮编码器、Z轴陀螺仪
返回  值：转向控制PWM
作    者：平衡小车之家
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//转向控制
{
	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Turn_Amplitude=88/Flag_sudu,Kp=42,Kd=0;     
	  //=============遥控左右旋转部分=======================//
  	if(1==Flag_Left||1==Flag_Right)                      //这一部分主要是根据旋转前的速度调整速度的起始速度，增加小车的适应性
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
	
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===转向速度限幅
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
		if(Flag_Qian==1||Flag_Hou==1)  Kd=0.5;        
		else Kd=0;   //转向的时候取消陀螺仪的纠正 有点模糊PID的思想
  	//=============转向PD控制器=======================//
		Turn=-Turn_Target*Kp-gyro*Kd;                 //===结合Z轴陀螺仪进行PD控制
	  return Turn;
}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
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
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=13000;    //===PWM满幅是7200 限制在6900
//		if(Flag_Qian==1)  Moto1+=DIFFERENCE;  //DIFFERENCE是一个衡量平衡小车电机和机械安装差异的一个变量。直接作用于输出，让小车具有更好的一致性。
//	  if(Flag_Hou==1)   Moto2-=DIFFERENCE;
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
}
/**************************************************************************
函数功能：按键修改小车运行状态 
入口参数：无
返回  值：无
**************************************************************************/
void Key(void)
{	
	if(KEY==0)Flag_Stop=0;
	else Flag_Stop=1;
}

/**************************************************************************
函数功能：异常关闭电机
入口参数：倾角和电压
返回  值：1：异常  0：正常
**************************************************************************/
u8 Turn_Off(float angle)
{
	    u8 temp;
			if(angle<-40||angle>40||1==Flag_Stop||Motor_Stay==1)//电池电压低于11.1V关闭电机
			{	                                                 //===倾角大于40度关闭电机
      temp=1;                                            //===Flag_Stop置1关闭电机
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
函数功能：获取角度 三种算法经过我们的调校，都非常理想 
入口参数：获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
返回  值：无
**************************************************************************/
void Get_Angle(u8 way)
{ 
	    float Accel_Y,Accel_Angle,Accel_Z,Gyro_X,Gyro_Z;
	    if(way==1)                           //===DMP的读取在数据采集中断读取，严格遵循时序要求
			{	
					Read_DMP();                      //===读取加速度、角速度、倾角
					Angle_Balance=-Roll;             //===更新平衡倾角
					Gyro_Balance=-gyro[0];            //===更新平衡角速度
					Gyro_Turn=gyro[2];               //===更新转向角速度
				  Acceleration_Z=accel[2];         //===更新Z轴加速度计
				
//					/**大车**/	
//				  Read_DMP();                      //===读取加速度、角速度、倾角
//				  Angle_Balance=-Pitch;             //===更新平衡倾角
////					Angle_Turn=-Yaw;
////					if(Angle_Turn<0)       Angle_Turn+=360;
//				  Gyro_Balance=-gyro[1];               //===更新转向角速度
//					Gyro_Turn=gyro[2];               //===更新转向角速度
//				  Acceleration_Z=accel[2];         //===更新Z轴加速度计
			}			
      else
      {
			Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //读取Y轴陀螺仪
			Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //读取Z轴陀螺仪
		  Accel_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //读取X轴加速度计
	  	Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //读取Z轴加速度计
		  if(Gyro_X>32768)  Gyro_X-=65536;                       //数据类型转换  也可通过short强制类型转换
			if(Gyro_Z>32768)  Gyro_Z-=65536;                       //数据类型转换
	  	if(Accel_Y>32768) Accel_Y-=65536;                      //数据类型转换
		  if(Accel_Z>32768) Accel_Z-=65536;                      //数据类型转换
			Gyro_Balance=Gyro_X;                                  //更新平衡角速度
	   	Accel_Angle=atan2(Accel_Y,Accel_Z)*180/PI;                 //计算倾角	
			Gyro_X=Gyro_X/16.4;                                    //陀螺仪量程转换	
      if(Way_Angle==2)		  	Kalman_Filter(Accel_Angle,Gyro_X);//卡尔曼滤波	
			else if(Way_Angle==3)   Yijielvbo(Accel_Angle,Gyro_X);    //互补滤波
	    Angle_Balance=angle;                                   //更新平衡倾角
			Gyro_Turn=Gyro_Z;                                      //更新转向角速度
			Acceleration_Z=Accel_Z;                                //===更新Z轴加速度计	
		}
}
/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/*********************到点的子函数***************************************/
//定位轮航向角左边0-180，右边0--180.
//SetSpeed_x        目标x坐标
//SetSpeed_y        目标y坐标
//P                 参数P
//D                 参数D
/*********************到点的子函数***************************************/
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
	  if((SetSpeed_x<pos_x_1+100)&&(SetSpeed_x>pos_x_1-100)&&(pos_x!=0))  //目标点误差范围
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
	//目标点与现在所在的点的角度差值cta，通过arctan反三角函数计算。
		 err_x=SetSpeed_x-pos_x_1;  //X轴差值
		 err_y=SetSpeed_y-pos_y_1;  //y轴差值
		 cta=atan(err_y/err_x)*57.29578;
	//目标角度omga的计算
		
		if((err_x>0)&&(err_y>0))
			omga=cta+0;  //第一象限时
		else if((err_x<0)&&(err_y>0))
			omga=cta+180;  //第二象限时
		else if((err_x>0)&&(err_y<0))
			omga=cta+360;  //第四象限时
		else if((err_x<0)&&(err_y<0))
			omga=cta+180;  //第三象限时  
		
	//目标点航向角坐标系重新定义，定义为0-360  转换成场地使用坐标
		if(zangle>=-90&&zangle<180)
			 zangle_new=zangle+90;
		else if(zangle<-90&&zangle>=-180)
			 zangle_new=zangle+450;
		
		zangleErr=omga-zangle_new;
	//角度差值取值判断
		
		if(zangleErr>=-360&&zangleErr<-180)    
		{
			zangleErr_v1=-360-zangleErr;
		}
		if(zangleErr>180&&zangleErr<=360)     
		{
			zangleErr_v2=360-zangleErr;
		}

		zangle_last=zangleErr+zangle_last;                    //-180<zangleErr<180 时对应PID
		Pi=P4*zangle_last;
		if(Pi>=20)     Pi=20;  //I限幅
		zangleErrErr=zangleErr-zangle_old;//误差量的差
		zangle_old=zangleErr;
		zangle_pid=P2*zangleErr+Pi+P3*zangleErrErr;              

		zangle_last_v1=zangleErr_v1+zangle_last_v1;            //-360<zangleErr<-180时对应PID  
		PI_v1=P4*zangle_last_v1;
		if(PI_v1 >=20)     PI_v1=20;  //I限幅	
		zangleErrErr_v1=zangleErr_v1-zangle_old_v1;            
		zangle_old_v1=zangleErr_v1;
		zangle_pid_v1=P2*zangleErr_v1+PI_v1 +P3*zangleErrErr;    
		
		zangle_last_v2=zangleErr_v2+zangle_last_v2;             //180<zangleErr<360时对应PID      
		PI_v2=P4*zangle_last_v2;
		if(PI_v2>=20)     PI_v2 =20;  //I限幅	
		zangleErrErr_v2=zangleErr_v2-zangle_old_v2;             
		zangle_old_v2=zangleErr_v2;
		zangle_pid_v2=P2*zangleErr_v2+PI_v2 +P3*zangleErrErr;    

	//对应角度差转换轮子速度	0代表速度可以设置 //固定设置左加右减
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
	Zou=1;//速度=-30
	TWO_DIAN_PD(0,500);
	TWO_DIAN_PD(-335,2040);//y+30
	Zhuan=1;
	TWO_DIAN_PD(-335,2800);
	Motor_Stay=1;

}	


/************************************红场*********************************************/
void HWalk1(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//速度=-30
	TWO_DIAN_PD(0,500);
	TWO_DIAN_PD(-650,2030);			//刹车要求720
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
	Zou=0;//速度=30
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
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
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
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
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
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
	TWO_DIAN_PD(1085,-3170);
	Zhuan=1;
	TWO_DIAN_PD(1085,-2370);
	Motor_Stay=1;
}
void HWalk5(void)//最后y轴-20
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
	TWO_DIAN_PD(710,-3170);
	Zhuan=1;
	TWO_DIAN_PD(710,-2370);
	Motor_Stay=1;
}
/*************************************************************************************/
/************************************蓝场*********************************************/
void LWalk1(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	Zhuan=0;
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
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
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
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
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
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
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
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
	Zou=1;//速度=-30
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
	Zou=0;//速度=30
	TWO_DIAN_PD(-715,-3170);
	Zhuan=1;
	TWO_DIAN_PD(-715,-2370);
	Motor_Stay=1;
}
/**************************************************/

