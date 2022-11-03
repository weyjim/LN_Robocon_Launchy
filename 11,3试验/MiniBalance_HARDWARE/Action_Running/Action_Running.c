#include "control.h"	
#include "filter.h"	
#include "Action_Running.h"	


/************************************红场*********************************************/
void HWalk1(void)
{
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	
	TWO_DIAN_PD(0,400,30);
	TWO_DIAN_PD(-400,1000,30);			//停车要求720
	TWO_DIAN_PD(-610,1500,30);
	TWO_DIAN_PD(-730,3700,30);
	
	TWO_DIAN_PD(-740,4250,5);
	Motor_Stay=1;
	delay_ms(500);
}

void HWalkBack1(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	TWO_DIAN_PD(740,-4000,-30);			//335 3170
	TWO_DIAN_PD(740,-3200,-10);			//335 2370	
	Motor_Stay=1;
}


void HWalkBack(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	TWO_DIAN_PD(740,-4000,-30);			//335 3170
	TWO_DIAN_PD(740,-700,-30);			//335 2370
	TWO_DIAN_PD(740,-400,0);			//335 2370
	
	Motor_Stay=0;
}

//void HWalk2(void)
//{
//	ZuoBiao_contrary=0;//是否倒车 1倒车 0前进
//	Zhua_Stop=0; //是否停车 0 不停 1停车 抓取
//	Zhuan=0;//是否停车 1停 0不停 稳定体态的
//	Zou=1;//速度=-30 是否减速 1为减速 0为加速
//	TWO_DIAN_PD(0,250);
//	TWO_DIAN_PD(-650,2030);//y+30
//	//Zhuan=1;
//	Zou=1;
//  TWO_DIAN_PD(-699,3700);
//	TWO_DIAN_PD(-699,3900);
//	TWO_DIAN_PD(-729,4350);
//	TWO_DIAN_PD(-739,4400);
//	Zou=1;
//	Zhuan=1;
//	Zhua_Stop=1;

//}
//void HWalkBack2(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Zhua_Stop=0;
//	Zhuan=0;
////	Zou=0;//速度=30
//	TWO_DIAN_PD(0,-4000);
//	Zou=1;
//	TWO_DIAN_PD(0,-4100);
//	Zou=1;
//	Zhuan=1;
//	Zhua_Stop=1;
//}


//void HWalk2(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(0,500);
//	TWO_DIAN_PD(-335,4040);//y+30
//	Zhuan=1;
//	TWO_DIAN_PD(-335,4800);
//	Motor_Stay=1;

//}
//void HWalkBack2(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(335,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(335,-2370);
//	Motor_Stay=1;
//}
//void HWalk3(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(-710,4120);
//	Zhuan=1;
//	TWO_DIAN_PD(-710,4800);
//	Motor_Stay=1;

//}
//void HWalkBack3(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(710,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(710,-2370);
//	Motor_Stay=1;
//}
//void HWalk4(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(-1085,4120);
//	Zhuan=1;
//	TWO_DIAN_PD(-1085,4800);
//	Motor_Stay=1;

//}
//void HWalkBack4(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(1085,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(1085,-2370);
//	Motor_Stay=1;
//}
//void HWalk5(void)//最后y轴-20
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(-1430,4080);
//	Zhuan=1;
//	TWO_DIAN_PD(-1430,4800);
//	Motor_Stay=1;

//}
//void HWalkBack5(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(710,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(710,-2370);
//	Motor_Stay=1;
//}
///*************************************************************************************/
///************************************蓝场*********************************************/
//void LWalk1(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
////	TWO_DIAN_PD(100,500);
//	TWO_DIAN_PD(20,4050);
//	Zhuan=1;
//	TWO_DIAN_PD(20,4800);
//	Motor_Stay=1;

//}
//void LWalkBack1(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(-340,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(-340,-2370);
//	Motor_Stay=1;
//}
//void LWalk2(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(0,500);
//	TWO_DIAN_PD(340,4050);//Y+30
//	Zhuan=1;
//	TWO_DIAN_PD(340,4800);
//	Motor_Stay=1;

//}
//void LWalkBack2(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(-340,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(-340,-2370);
//	Motor_Stay=1;
//}
//void LWalk3(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(715,4100);
//	Zhuan=1;
//	TWO_DIAN_PD(715,4800);
//	Motor_Stay=1;

//}
//void LWalkBack3(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(-715,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(-715,-2370);
//	Motor_Stay=1;
//}
//void LWalk4(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(1090,4080);
//	Zhuan=1;
//	TWO_DIAN_PD(1090,4800);
//	Motor_Stay=1;

//}
//void LWalkBack4(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(-1090,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(-1090,-2370);
//	Motor_Stay=1;
//}
//void LWalk5(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//速度=-30
//	TWO_DIAN_PD(1400,4120);
//	Zhuan=1;
//	TWO_DIAN_PD(1400,4800);
//	Motor_Stay=1;

//}
//void LWalkBack5(void)
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=0;//速度=30
//	TWO_DIAN_PD(-715,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(-715,-2370);
//	Motor_Stay=1;
//}
///**************************************************/

