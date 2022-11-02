#include "control.h"	
#include "filter.h"	
#include "Action_Running.h"


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

#define Speed_num -30			//Sudu=Speed_num	目标速度的值。sudu=0即松油门滑行

/************************************红场*********************************************/
void HWalk1(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
	Sudu=Speed_num;
	TWO_DIAN_PD(0,350);
	TWO_DIAN_PD(-650,2030);			//停车要求720
	TWO_DIAN_PD(-699,3700);
//	Zhuan=1;
	Sudu=0;
	TWO_DIAN_PD(-729,4350);
	Motor_Stay=1;
}
void HWalkBack1(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
	Sudu=-Speed_num;
	TWO_DIAN_PD(729,-4000);			//335 3170
//	Zhuan=1;
	Sudu=0;
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

