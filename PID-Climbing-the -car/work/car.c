#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "timer.h"
#include "car.h"
#include "encoder.h"
/*
���������
	PA2����
	PA3����
  PA4: ��
																													

TB6612N�߼����룺����ת����ת��
	PB0,PB1:  �Һ�	 ͨ��1
	PB14,PB15:��ǰ   ͨ��3
	PB12,PB13:��ǰ	 ͨ��2
	PB10,PB11:���   ͨ��4
*/

void GPIOB_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����out���ţ�PA2,PA3,PA4*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	/*��ʼΪ�͵�ƽ*/
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

//  PB0,PB1:  �Һ�	 ͨ��1
//	PB14,PB15:��ǰ   ͨ��3
//	PB12,PB13:��ǰ	 ͨ��2
//	PB10,PB11:���   ͨ��4

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




