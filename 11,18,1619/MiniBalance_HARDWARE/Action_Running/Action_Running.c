#include "control.h"	
#include "filter.h"	
#include "Action_Running.h"	

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


/************************************�쳡*********************************************/
void HWalk1(void)
{

	ZuoBiao_contrary=0;
	Motor_Stay=0;
	
	TWO_DIAN_PD(0,400,30);
	TWO_DIAN_PD(-400,1000,30);			//ͣ��Ҫ��720
	TWO_DIAN_PD(-638,1550,30);			//ͣ��Ҫ��720
	TWO_DIAN_PD(-730,3700,30);
	TWO_DIAN_PD(-740,3900,30);
	TWO_DIAN_PD(-740,4370,10);
	
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
 TWO_DIAN_PD(-570,3750,15);   //ͣ��Ҫ��720
 TWO_DIAN_PD(-395,3950,10);
 TWO_DIAN_PD(-395,4150,10);
 TWO_DIAN_PD(-395,4370,7);
	
 Motor_Stay=1;
 delay_ms(500);
}
void HWalkBack2(void)
{
	ZuoBiao_contrary=1;
	Motor_Stay=0;
	
	TWO_DIAN_PD(485,-4000,-30);			//335 3170
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
	TWO_DIAN_PD(-285,3750,15);   //ͣ��Ҫ��720
	TWO_DIAN_PD(-100,4050,15);
	TWO_DIAN_PD(-70,4200,15);
	TWO_DIAN_PD(-70,4370,5);
	
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
 TWO_DIAN_PD(-840,3250,15);   //ͣ��Ҫ��720
 TWO_DIAN_PD(-1040,3950,20); 
 TWO_DIAN_PD(-1110,4150,15);
 TWO_DIAN_PD(-1110,4370,7);
	
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
 
 TWO_DIAN_PD(-1110,3350,30);
 TWO_DIAN_PD(-1310,3750,20);   //ͣ��Ҫ��720
 TWO_DIAN_PD(-1470,4150,15);
 TWO_DIAN_PD(-1470,4370,0);
	
 Motor_Stay=1;
 delay_ms(500);
}


void LWalk1(void)
{
	SendGetF10=0;
	ZuoBiao_contrary=0;
	Motor_Stay=0;
	
	
	TWO_DIAN_PD(0,400,30);
	TWO_DIAN_PD(400,1000,30);			//ͣ��Ҫ��720
	TWO_DIAN_PD(606,1550,30);			//ͣ��Ҫ��720
	TWO_DIAN_PD(720,3700,30);
	TWO_DIAN_PD(725,3900,30);
	TWO_DIAN_PD(725,4370,10);
	
	Motor_Stay=1;
	delay_ms(500);
}
void LWalkBack1(void)
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
 TWO_DIAN_PD(570,3750,15);   //ͣ��Ҫ��720
 TWO_DIAN_PD(355,3950,10);
 TWO_DIAN_PD(345,4150,10);
 TWO_DIAN_PD(345,4370,7);
	
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
 TWO_DIAN_PD(285,3750,15);   //ͣ��Ҫ��720
 TWO_DIAN_PD(100,4050,15);
 TWO_DIAN_PD(45,4200,15);
 TWO_DIAN_PD(45,4380,7);
	
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
	TWO_DIAN_PD(840,3250,15);   //ͣ��Ҫ��720
	TWO_DIAN_PD(1040,3950,20); 
	TWO_DIAN_PD(1085,4150,15);
	TWO_DIAN_PD(1085,4385,7);
	
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

	TWO_DIAN_PD(1110,3350,30);
	TWO_DIAN_PD(1250,3450,20);   //ͣ��Ҫ��720
	TWO_DIAN_PD(1430,4150,15);
	TWO_DIAN_PD(1430,4380,0);
	
	Motor_Stay=1;
	delay_ms(500);
}
//void LWalkBack5(void)//�ؼҵ���
//{
//	ZuoBiao_contrary=1;
//	Motor_Stay=0;
//	
//	TWO_DIAN_PD(-1400,-4000,-30);			//335 3170
//	TWO_DIAN_PD(-100,-3500,-15);		//335 2370
//	TWO_DIAN_PD(-150,-3350,-7);			//335 2370
//	Motor_Stay=1;
//	delay_ms(500);
//}
//void LWalk6(void)//�ؼҷ���
//{
//	SendGetF10=0;
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	
//	TWO_DIAN_PD(150,2800,30);			//ͣ��Ҫ��720
//	TWO_DIAN_PD(621,2700,30);			//ͣ��Ҫ��720
//	TWO_DIAN_PD(616,800,15);
//	TWO_DIAN_PD(630,500,7);

//	
//	Motor_Stay=1;
//	delay_ms(500);
//}
//void HWalk2(void)
//{
//	ZuoBiao_contrary=0;//�Ƿ񵹳� 1���� 0ǰ��
//	Zhua_Stop=0; //�Ƿ�ͣ�� 0 ��ͣ 1ͣ�� ץȡ
//	Zhuan=0;//�Ƿ�ͣ�� 1ͣ 0��ͣ �ȶ���̬��
//	Zou=1;//�ٶ�=-30 �Ƿ���� 1Ϊ���� 0Ϊ����
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
////	Zou=0;//�ٶ�=30
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
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
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
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
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
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
//	TWO_DIAN_PD(1085,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(1085,-2370);
//	Motor_Stay=1;
//}
//void HWalk5(void)//���y��-20
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
//	TWO_DIAN_PD(710,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(710,-2370);
//	Motor_Stay=1;
//}
///*************************************************************************************/
///************************************����*********************************************/
//void LWalk1(void)
//{
//	ZuoBiao_contrary=0;
//	Motor_Stay=0;
//	Zhuan=0;
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
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
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
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
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
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
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
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
//	Zou=1;//�ٶ�=-30
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
//	Zou=0;//�ٶ�=30
//	TWO_DIAN_PD(-715,-3170);
//	Zhuan=1;
//	TWO_DIAN_PD(-715,-2370);
//	Motor_Stay=1;
//}
///**************************************************/
