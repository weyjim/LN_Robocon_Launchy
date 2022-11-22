#include "sys.h"
#include "usart3.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 


//���ڽ��ջ����� 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
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
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
//	{	 
//		res =USART_ReceiveData(USART3);		 
//		if((USART3_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
//		{ 
//			if(USART3_RX_STA<USART3_MAX_RECV_LEN)	//�����Խ�������
//			{
//				TIM_SetCounter(TIM7,0);//���������          				//���������
//				if(USART3_RX_STA==0) 				//ʹ�ܶ�ʱ��7���ж� 
//				{
//					TIM_Cmd(TIM7,ENABLE);//ʹ�ܶ�ʱ��7
//				}
//				USART3_RX_BUF[USART3_RX_STA++]=res;	//��¼���յ���ֵ	 
//			}
//			else 
//			{
//				USART3_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
//			} 
//		}
//	}  				 											 
//}   


//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //����3ʱ��ʹ��

 	USART_DeInit(USART3);  //��λ����3
		 //USART3_TX   PB10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
   
    //
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11
	
	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART3, &USART_InitStructure); //��ʼ������	3
  

	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
	
	//ʹ�ܽ����ж�
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�   
	
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
//	
//	TIM7_Int_Init(99,7199);		//10ms�ж�
	USART3_RX_STA=0;		//����
//	TIM_Cmd(TIM7,DISABLE);			//�رն�ʱ��7

}

////����3,printf ����
////ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
//void u3_printf(char* fmt,...)  
//{  
//	u16 i,j; 
//	va_list ap; 
//	va_start(ap,fmt);
//	vsprintf((char*)USART3_TX_BUF,fmt,ap);
//	va_end(ap);
//	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
//	for(j=0;j<i;j++)							//ѭ����������
//	{
//	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
//		USART_SendData(USART3,USART3_TX_BUF[j]); 
//	} 
//}



//#include "usart3.h"
//  /**************************************************************************
//���ߣ�ƽ��С��֮��
//�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
//**************************************************************************/
//u8 Usart3_Receive;

///**************************************************************************
//�������ܣ�����3��ʼ��
//��ڲ����� bound:������
//����  ֵ����
//**************************************************************************/
//void uart3_init(u32 bound)
//{  	 
//	  //GPIO�˿�����
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��UGPIOBʱ��
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��
//	//USART3_TX  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//   
//  //USART3_RX	  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  //Usart3 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//   //USART ��ʼ������
//	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
//  USART_Init(USART3, &USART_InitStructure);     //��ʼ������3
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
//  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 
//}

///**************************************************************************
//�������ܣ�����3�����ж�
//��ڲ�������
//����  ֵ����
//**************************************************************************/
//void USART3_IRQHandler(void)
//{	
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //���յ�����
//	{	  
//	 static	int uart_receive=0;//����������ر���
//		static u8 Flag_PID,i,j,Receive[50];
//		static float Data;
//  	 uart_receive=USART_ReceiveData(USART3); 
//		Usart3_Receive=uart_receive;
//	
//		if(uart_receive==0x59)  Flag_sudu=2;  //���ٵ���Ĭ��ֵ��
//		if(uart_receive==0x58)  Flag_sudu=1;  //���ٵ�
//		
//	  if(uart_receive>10)  //Ĭ��ʹ��
//    {			
//			if(uart_receive==0x5A)	Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
//			else if(uart_receive==0x41)	Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ǰ
//			else if(uart_receive==0x45)	Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////��
//			else if(uart_receive==0x42||uart_receive==0x43||uart_receive==0x44)	
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //��
//			else if(uart_receive==0x46||uart_receive==0x47||uart_receive==0x48)	    //��
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
//			else Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
//  	}
//		if(uart_receive<10)     //����appΪ��MiniBalanceV1.0  ��ΪMiniBalanceV1.0��ң��ָ��ΪA~H ��HEX��С��10
//		{			
//			Flag_sudu=1;//�л������ٵ�
//			if(uart_receive==0x00)	Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
//			else if(uart_receive==0x01)	Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ǰ
//			else if(uart_receive==0x05)	Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////��
//			else if(uart_receive==0x02||uart_receive==0x03||uart_receive==0x04)	
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //��
//			else if(uart_receive==0x06||uart_receive==0x07||uart_receive==0x08)	    //��
//														Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
//			else Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
//  	}	

//		
//		if(Usart3_Receive==0x7B) Flag_PID=1;   //APP����ָ����ʼλ
//		if(Usart3_Receive==0x7D) Flag_PID=2;   //APP����ָ��ֹͣλ

//		 if(Flag_PID==1)  //�ɼ�����
//		 {
//			Receive[i]=Usart3_Receive;
//			i++;
//		 }
//		 if(Flag_PID==2)  //��������
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
//							 case 0x34:  break; //Ԥ��
//							 case 0x35:  break; //Ԥ��
//							 case 0x36:  break; //Ԥ��
//							 case 0x37:  break; //Ԥ��
//							 case 0x38:  break; //Ԥ��
//						 }
//					 }				 
//					 Flag_PID=0;
//					 i=0;
//					 j=0;
//					 Data=0;
//					 memset(Receive, 0, sizeof(u8)*50);//��������
//		 } 
//	}  											 
//} 



