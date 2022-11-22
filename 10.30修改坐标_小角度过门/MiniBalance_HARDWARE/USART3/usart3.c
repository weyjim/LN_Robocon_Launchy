#include "sys.h"
#include "usart3.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 


//串口接收缓存区 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//发送缓冲,最大USART3_MAX_SEND_LEN字节

//通过判断接收连续2个字符之间的时间差不大于10ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过10ms,则认为不是1次连续数据.也就是超过10ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
vu16 USART3_RX_STA=0;   	


float pos_x=0;
float pos_y=0;
float zangle=0;
float xangle=0;
float yangle=0;
float w_z=0;
float pos_x_1=0.0;
float pos_y_1=0.0;
float zangle_1=0.0;

void USART3_IRQHandler(void)
{  

    
	static uint8_t ch;
    static union
    {
     uint8_t data[24];
     float ActVal[6];
    }posture;
    static uint8_t count=0;
    static uint8_t i=0;	

   if(USART_GetITStatus(USART3, USART_IT_RXNE)==SET)   
    {
       USART_ClearITPendingBit( USART3,USART_IT_RXNE);
       ch=USART_ReceiveData(USART3);
        switch(count)
         {
             case 0:
                if(ch==0x0d)
                    count++;
                else
                    count=0;
                break;                 
             case 1:
                if(ch==0x0a)
                 {
                    i=0;
                    count++;
                 }
                else if(ch==0x0d);
                else
                    count=0;
                break;                 
             case 2:
                posture.data[i]=ch;
                 i++;
                if(i>=24)
                 {
                    i=0;
                    count++;
                 }
                break;                 
             case 3:
                if(ch==0x0a)
                    count++;
                 else
                    count=0;
                break;                 
             case 4:
                if(ch==0x0d)
                 {
									 zangle=posture.ActVal[0];
									 xangle=posture.ActVal[1];
									 yangle=posture.ActVal[2];
									 pos_x =posture.ActVal[3];
									 pos_y =posture.ActVal[4];
									 w_z   =posture.ActVal[5];
////										 zangle_1=zangle;
									 pos_x_1=pos_x;
							  	 pos_y_1=pos_y;
									 if(ZuoBiao_contrary==1){pos_x_1=-pos_x_1;pos_y_1=-pos_y_1;}
                 }
               count=0;

							
                break;   
              default:
                count=0;
              break;        
         }
     }
}








//void USART3_IRQHandler(void)
//{
//	u8 res;	      
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
//	{	 
//		res =USART_ReceiveData(USART3);		 
//		if((USART3_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
//		{ 
//			if(USART3_RX_STA<USART3_MAX_RECV_LEN)	//还可以接收数据
//			{
//				TIM_SetCounter(TIM7,0);//计数器清空          				//计数器清空
//				if(USART3_RX_STA==0) 				//使能定时器7的中断 
//				{
//					TIM_Cmd(TIM7,ENABLE);//使能定时器7
//				}
//				USART3_RX_BUF[USART3_RX_STA++]=res;	//记录接收到的值	 
//			}
//			else 
//			{
//				USART3_RX_STA|=1<<15;				//强制标记接收完成
//			} 
//		}
//	}  				 											 
//}   


//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //串口3时钟使能

 	USART_DeInit(USART3);  //复位串口3
		 //USART3_TX   PB10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
    //
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11
	
	USART_InitStructure.USART_BaudRate = bound;//波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART3, &USART_InitStructure); //初始化串口	3
  

	USART_Cmd(USART3, ENABLE);                    //使能串口 
	
	//使能接收中断
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断   
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
//	
//	TIM7_Int_Init(99,7199);		//10ms中断
	USART3_RX_STA=0;		//清零
//	TIM_Cmd(TIM7,DISABLE);			//关闭定时器7

}

////串口3,printf 函数
////确保一次发送数据不超过USART3_MAX_SEND_LEN字节
//void u3_printf(char* fmt,...)  
//{  
//	u16 i,j; 
//	va_list ap; 
//	va_start(ap,fmt);
//	vsprintf((char*)USART3_TX_BUF,fmt,ap);
//	va_end(ap);
//	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
//	for(j=0;j<i;j++)							//循环发送数据
//	{
//	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
//		USART_SendData(USART3,USART3_TX_BUF[j]); 
//	} 
//}



//#include "usart3.h"
//  /**************************************************************************
//作者：平衡小车之家
//我的淘宝小店：http://shop114407458.taobao.com/
//**************************************************************************/
//u8 Usart3_Receive;

///**************************************************************************
//函数功能：串口3初始化
//入口参数： bound:波特率
//返回  值：无
//**************************************************************************/
//void uart3_init(u32 bound)
//{  	 
//	  //GPIO端口设置
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能UGPIOB时钟
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3时钟
//	//USART3_TX  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//   
//  //USART3_RX	  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  //Usart3 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//   //USART 初始化设置
//	USART_InitStructure.USART_BaudRate = bound;//串口波特率
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
//  USART_Init(USART3, &USART_InitStructure);     //初始化串口3
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
//  USART_Cmd(USART3, ENABLE);                    //使能串口3 
//}

///**************************************************************************
//函数功能：串口3接收中断
//入口参数：无
//返回  值：无
//**************************************************************************/
//void USART3_IRQHandler(void)
//{	
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收到数据
//	{	  
//	 static	int uart_receive=0;//蓝牙接收相关变量
//		static u8 Flag_PID,i,j,Receive[50];
//		static float Data;
//  	 uart_receive=USART_ReceiveData(USART3); 
//		Usart3_Receive=uart_receive;
//	
//		if(uart_receive==0x59)  Flag_sudu=2;  //低速挡（默认值）
//		if(uart_receive==0x58)  Flag_sudu=1;  //高速档
//		
//	  if(uart_receive>10)  //默认使用
//    {			
//			if(uart_receive==0x5A)	Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////刹车
//			else if(uart_receive==0x41)	Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////前
//			else if(uart_receive==0x45)	Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////后
//			else if(uart_receive==0x42||uart_receive==0x43||uart_receive==0x44)	
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //左
//			else if(uart_receive==0x46||uart_receive==0x47||uart_receive==0x48)	    //右
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
//			else Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////刹车
//  	}
//		if(uart_receive<10)     //备用app为：MiniBalanceV1.0  因为MiniBalanceV1.0的遥控指令为A~H 其HEX都小于10
//		{			
//			Flag_sudu=1;//切换至高速档
//			if(uart_receive==0x00)	Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////刹车
//			else if(uart_receive==0x01)	Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////前
//			else if(uart_receive==0x05)	Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////后
//			else if(uart_receive==0x02||uart_receive==0x03||uart_receive==0x04)	
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //左
//			else if(uart_receive==0x06||uart_receive==0x07||uart_receive==0x08)	    //右
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
//			else Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////刹车
//  	}	

//		
//		if(Usart3_Receive==0x7B) Flag_PID=1;   //APP参数指令起始位
//		if(Usart3_Receive==0x7D) Flag_PID=2;   //APP参数指令停止位

//		 if(Flag_PID==1)  //采集数据
//		 {
//			Receive[i]=Usart3_Receive;
//			i++;
//		 }
//		 if(Flag_PID==2)  //分析数据
//		 {
//			     if(Receive[3]==0x50) 	 PID_Send=1;
//					 else  if(Receive[3]==0x57) 	 Flash_Send=1;
//					 else  if(Receive[1]!=0x23) 
//					 {								
//						for(j=i;j>=4;j--)
//						{
//						  Data+=(Receive[j-1]-48)*pow(10,i-j);
//						}
//						switch(Receive[1])
//						 {
//							 case 0x30:  Balance_Kp=Data/100;break;
//							 case 0x31:  Balance_Kd=Data/100;break;
//							 case 0x32:  Velocity_Kp=Data/100;break;
//							 case 0x33:  Velocity_Ki=Data/100;break;
//							 case 0x34:  break; //预留
//							 case 0x35:  break; //预留
//							 case 0x36:  break; //预留
//							 case 0x37:  break; //预留
//							 case 0x38:  break; //预留
//						 }
//					 }				 
//					 Flag_PID=0;
//					 i=0;
//					 j=0;
//					 Data=0;
//					 memset(Receive, 0, sizeof(u8)*50);//数组清零
//		 } 
//	}  											 
//} 



