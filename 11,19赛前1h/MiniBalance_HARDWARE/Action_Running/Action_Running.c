#include "control.h"	
#include "filter.h"	
#include "Action_Running.h"	

int H_Move=10;

int L_Move=5;

void Arrived(void)
{
	SendGetF10=1;
	while(1)
		if(ReceiveF7==1)
		{
			delay_ms(50);
			if(ReceiveF7==1)
				break;
		}
	SendGetF10=0;	
}


/************************************红场*********************************************/
void HWalk1(void)
{

	ZuoBiao_contrary=0;
	Motor_Stay=0;
	
	TWO_DIAN_PD(0,400,30);
	TWO_DIAN_PD(-400,1000,30);			//停车要求720
	SendGetF10=0;
	TWO_DIAN_PD(-632,1550,30);			// -638
	SendGetF10=0;
	TWO_DIAN_PD(-726,3700,30);			//Move -730
	SendGetF10=0;
	TWO_DIAN_PD(-740+H_Move,3900,30);
	SendGetF10=0;
	TWO_DIAN_PD(-740+H_Move,4370,10);

	Motor_Stay=1;
	delay_ms(500);
}
void HWalkBack1(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(740,-4000,-30);			//335 3170
	TWO_DIAN_PD(740,-3750,-20);			//335 2370
	TWO_DIAN_PD(740,-3350,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void HWalk2(void)
{
 ZuoBiao_contrary=0;
 Motor_Stay=0;
 
 TWO_DIAN_PD(-740,3350,20);
 TWO_DIAN_PD(-570,3750,15);   //停车要求720
 TWO_DIAN_PD(-395+H_Move+10,3950,10);
 TWO_DIAN_PD(-395+H_Move+10,4150,10);
 TWO_DIAN_PD(-395+H_Move+10,4370,7);
	
 Motor_Stay=1;
 delay_ms(500);
}
void HWalkBack2(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(395,-4000,-30);			//335 3170
	TWO_DIAN_PD(485,-3750,-20);			//335 2370
	TWO_DIAN_PD(485,-3350,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void HWalk3(void)
{
 ZuoBiao_contrary=0;
 Motor_Stay=0;
 
	TWO_DIAN_PD(-485,3350,20);
	TWO_DIAN_PD(-285,3750,15);   //停车要求720
	TWO_DIAN_PD(-100,4050,15);
	TWO_DIAN_PD(-73+H_Move,4200,15);
	TWO_DIAN_PD(-73+H_Move,4370,5);
	
	Motor_Stay=1;
	delay_ms(500);
}
void HWalkBack3(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(70,-4000,-30);			//335 3170
	TWO_DIAN_PD(70,-3750,-20);			//335 2370
	TWO_DIAN_PD(120,-3000,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void HWalk4(void)
{
 ZuoBiao_contrary=0;
 Motor_Stay=0;
 
 TWO_DIAN_PD(-120,3000,30);
 TWO_DIAN_PD(-840,3250,15);   //停车要求720
 TWO_DIAN_PD(-1040,3950,20); 
 TWO_DIAN_PD(-1110+H_Move,4150,15);
 TWO_DIAN_PD(-1110+H_Move,4370,5);
	
 Motor_Stay=1;
 delay_ms(500);
}
void HWalkBack4(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(1110,-4000,-30);			//335 3170
	TWO_DIAN_PD(1110,-3750,-20);			//335 2370
	TWO_DIAN_PD(1110,-3350,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void HWalk5(void)
{
 ZuoBiao_contrary=0;
 Motor_Stay=0;
 
 TWO_DIAN_PD(-1110,3350,20);
 TWO_DIAN_PD(-1310+H_Move,3750,15);   //停车要求720
 TWO_DIAN_PD(-1470+H_Move,4150,7);
 TWO_DIAN_PD(-1470+H_Move,4355,4);
	
 Motor_Stay=1;
 delay_ms(500);
}


void LWalk1(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	
	
//	TWO_DIAN_PD(0,400,30);			
//	TWO_DIAN_PD(400,1000,30);		//第一步右转
//	TWO_DIAN_PD(606,1550,30);		//初步左转
//	TWO_DIAN_PD(655,1850,30);		//垂直矫正
//	TWO_DIAN_PD(700,3700,30);		//垂直过门
//	TWO_DIAN_PD(725,4000,30);		//减速节点
//	TWO_DIAN_PD(725,4382,5);		//24.80V
	
	TWO_DIAN_PD(0,400,30);
	TWO_DIAN_PD(400,1000,30);			//停车要求720
	TWO_DIAN_PD(606,1550,30);			//停车要求720
	TWO_DIAN_PD(659,1850,30);
	TWO_DIAN_PD(720,3700,30);
	TWO_DIAN_PD(725,3900,30);
	TWO_DIAN_PD(725,4370,10);	
	Motor_Stay=1;
	delay_ms(500);
}void LWalkBack1(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(-740,-4000,-30);			//335 3170
	TWO_DIAN_PD(-740,-3750,-20);			//335 2370
	TWO_DIAN_PD(-740,-3350,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void LWalk2(void)
{
 ZuoBiao_contrary=0;
 Motor_Stay=0;
 
 TWO_DIAN_PD(740,3350,20);
 TWO_DIAN_PD(570,3750,15);   //停车要求720
 TWO_DIAN_PD(355,3950,10);
 TWO_DIAN_PD(345-L_Move,4150,10);
 TWO_DIAN_PD(345-L_Move,4370,7);
	
 Motor_Stay=1;
 delay_ms(500);
}
void LWalkBack2(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(-345,-4000,-30);			//335 3170
	TWO_DIAN_PD(-485,-3750,-20);			//335 2370
	TWO_DIAN_PD(-485,-3350,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void LWalk3(void)
{
 ZuoBiao_contrary=0;
 Motor_Stay=0;
 
 TWO_DIAN_PD(485,3350,20);
 TWO_DIAN_PD(285,3750,15);   //停车要求720
 TWO_DIAN_PD(100,4050,15);
 TWO_DIAN_PD(45-L_Move,4200,15);
 TWO_DIAN_PD(42-L_Move,4380,7);
	
 Motor_Stay=1;
 delay_ms(500);
}
void LWalkBack3(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(-70,-4000,-30);			//335 3170
	TWO_DIAN_PD(-70,-3750,-20);			//335 2370
	TWO_DIAN_PD(-120,-3000,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void LWalk4(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
 
	TWO_DIAN_PD(120,3000,30);
	TWO_DIAN_PD(840,3250,15);   //停车要求720
	TWO_DIAN_PD(1040,3950,20); 
	TWO_DIAN_PD(1085-3,4150,15);
	TWO_DIAN_PD(1085-3,4385,7);
	
	Motor_Stay=1;
	delay_ms(500);
}
void LWalkBack4(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(-1110,-4000,-30);			//335 3170
	TWO_DIAN_PD(-1110,-3750,-20);			//335 2370
	TWO_DIAN_PD(-1110,-3350,-10);			//335 2370
	
	Motor_Stay=1;
	delay_ms(500);
}
void LWalk5(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;

	TWO_DIAN_PD(1110,3350,25);
	TWO_DIAN_PD(1250,3450,28);   //停车要求720
	TWO_DIAN_PD(1425-L_Move,4150,10);
	TWO_DIAN_PD(1425-L_Move,4393,5);
	
	Motor_Stay=1;
	delay_ms(500);
}
