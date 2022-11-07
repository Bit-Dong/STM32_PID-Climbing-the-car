#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "timer.h"
#include "car.h"
#include "encoder.h"
/*
红外输出：
	PA2：左
	PA3：中
  PA4: 右
																													

TB6612N逻辑输入：（正转，反转）
	PB0,PB1:  右后	 通道1
	PB14,PB15:右前   通道3
	PB12,PB13:左前	 通道2
	PB10,PB11:左后   通道4
*/

void GPIOB_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	/*红外out引脚：PA2,PA3,PA4*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	/*初始为低电平*/
	GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

}


void forward(int t)
{
	Change_Target(t,t);
	GPIO_SetBits(GPIOB,GPIO_Pin_1| GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0| GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_14);
}

void back(int t)
{
	Change_Target(t,t);
	GPIO_SetBits(GPIOB,GPIO_Pin_0| GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1| GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
}

//  PB0,PB1:  右后	 通道1
//	PB14,PB15:右前   通道3
//	PB12,PB13:左前	 通道2
//	PB10,PB11:左后   通道4

void turn_left(int t_l,int t_r)
{
	Change_Target(t_l,t_r);
	GPIO_SetBits(GPIOB,GPIO_Pin_1| GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0| GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14);
}

void turn_right(int t_l,int t_r)
{
	Change_Target(t_l,t_r);
	GPIO_SetBits(GPIOB,GPIO_Pin_0| GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1| GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15);
}

void stop(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}




