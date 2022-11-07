#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "pwm.h"
#include "encoder.h"
#include "timer.h"
#include "car.h"
#include "delay.h"
//#include "usart.h"
/*
	TIM1(高级定时器)：CH1-CH4: PWM输出控制四个电机  
		PA8    左前     
		PA9    左后     
		PA10   右前     
		PA11   右后

	TIM2:CH1-CH2: 左后轮编码器A、B相   PA0,PA1
	TIM3:CH1-CH2: 右后轮编码器A、B相   PA6,PA7
	TIM4:定时测速调速 
	
	红外输出：
	PA2：左
	PA3：中
  PA4: 右
	
	TB6612N逻辑输入：（正转  反转）
	PB12,PB13:左前	 通道1
	PB10,PB11:左后   通道2
	PB14,PB15:右前   通道3
	PB0,PB1:  右后	 通道4
*/


#define L GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define M GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define R GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)

//extern int spd_now1;
//extern int spd_now2;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组
//	Usart_Init();
	
	GPIOB_Init();
	
	TIM1_PWM_Init(100-1,72-1);
	TIM2_Init(65535,9);
	TIM3_Init(65535,9);
	TIM4_Init(5000,72-1); 
	int i;
	
	while(1)
	{
		if(L==0 && R==0)  i=0;
		
		if(L==1 && R==0)  i=1;
		
		if(L==0 && R==1)  i=3;
		
		if(L==1 && M==1 && R==1)  i=5;
		
		switch(i)
		{
			case 0:
				forward(4);
			  break;
			
			case 1:
				turn_left(5,16);	
			  break;

			case 3:
				turn_right(15,6);
			  break;

			case 5:
				stop();
				delay_ms(1000);
			  break;
		}		
	}
}


































/*串口中断服务函数*/
//void USART1_IRQHandler(void)
//{
//	u8 data = 0;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
//	{
//		data = USART_ReceiveData(USART1);
//		//USART_SendData(USART1,data);
//		switch(data)
//		{
//			case 0x00://0 停止
//				stop();
//				break;
//			case 0x01://1 前进
//				forward(target);
//				break;
//			case 0x02://2 后退
//				back(target);
//				break;
//			case 0x03://3 左转
//				turn_left(target_left,target_right);
//				break;
//			case 0x04://4 右转
//				turn_right(target_left,target_right);
//				break;
//			case 0x05://5 慢速
//				Change_Target(2,2);
//				target = 2;
//				break;
//			case 0x06://6 中速
//				Change_Target(8,8);
//				target = 8;
//				break;
//			case 0x07://7 快速
//				Change_Target(15,15);
//				target = 15;
//				break;
//		}
//	}
//}
