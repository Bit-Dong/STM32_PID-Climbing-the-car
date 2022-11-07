//#include "usart.h"
//#include "stdio.h"
//uint8_t USART1_RX_BUF[USART1_RCV_LEN];
//uint16_t USART1_RX_STA = 0;   //15：接收完成标志，14接收到0x0D   0-13位有效数据

//int fputc(int ch,FILE *p)
//{
//	USART_SendData(USART1,ch);
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
//	return ch;
//}


//void Usart_Init()
//{
//	
//	//(1)时钟使能
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
//	
//	//(2)GPIO初始化
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	//(3)初始化串口参数
//	USART_InitTypeDef USART_InitStructure;
//	USART_InitStructure.USART_BaudRate = 115200;  //串口波特率
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //收发模式
//	USART_InitStructure.USART_Parity = USART_Parity_No;   //无奇偶校验位
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //一个停止位
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //字长为8位数据格式
//	USART_Init(USART1,&USART_InitStructure);
//	
//	//(4)使能串口
//	USART_Cmd(USART1,ENABLE);
//	
//	//(5)设置串口中断类型
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//	
//	//(6)设置中断优先级，使能串口中断通道
//	
//	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_Init(&NVIC_InitStructure);
//	
//}

////void USART1_IRQHandler(void)
////{
////	uint8_t Recv;
////	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
////	{
////		Recv = USART_ReceiveData(USART1); //接收数据
////		
////		
////		if((USART1_RX_STA&0x8000) == 0)  //接收完成
////		{
////			if(USART1_RX_STA & 0x4000)  //接收到0X0D
////			{
////				if(Recv != 0x0a) USART1_RX_STA = 0;
////				else USART1_RX_STA |= 0x8000;
////			}
////			else
////			{
////				if(Recv == 0x0D) USART1_RX_STA |= 0x4000;
////				else
////				{
////					USART1_RX_BUF[USART1_RX_STA&0x3fff] = Recv;
////					USART1_RX_STA++;
////					if(USART1_RX_STA > (USART1_RCV_LEN -1))  USART1_RX_STA = 0;
////					
////				}
////			}
////		}
////		
////		
////		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
////	}
////}






//	



