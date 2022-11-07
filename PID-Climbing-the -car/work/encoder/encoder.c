#include "stm32f10x.h"                  // Device header
#include "encoder.h"
#include "stdlib.h"
/*
	���ö�ʱ�ж����̣�
		1.RCC����ʱ�ӣ���ʱ����׼ʱ�Ӻ����蹤��ʱ�ӣ�
		2.ѡ��ʱ����Ԫ��ʱ��Դ�����ڶ�ʱ�жϣ�ѡ���ڲ�ʱ��Դ��
		3.����ʱ����Ԫ������PSCԤ��Ƶ����ARR�Զ���װ����CNT��������
		4.��������жϿ��ƣ�ʹ�ܸ����жϣ���������ж������NVIC
		5.����NVIC���򿪶�ʱ��ͨ�������������ȼ�
		6.���п��ƣ�ʹ�ܼ�����
*/

void TIM4_Init(u16 per,u16 psc)
{
	/*1������ͨ�ö�ʱ��TIM4ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	/*2��ѡ��ʱ��ԴΪ�ڲ�ʱ��*/
	//TIM_InternalClockConfig(TIM4);//Ĭ��Ϊ�ڲ�ʱ��
	
	/*3������ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�ƵΪ1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//ѡ�����ģʽΪ���ϼ���
	/*
	��ʱƵ�� = 72M / (PSC+1) / (ARR+1)
	*/
	TIM_TimeBaseInitStructure.TIM_Period = per;//�������ڣ�ARR�Զ���װ����ֵ��
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//����PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	/*4��ʹ�ܸ����ж�*/
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	/*5������NVIC*/
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//ѡ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);	
	
	/*6��������ʱ��*/
	TIM_Cmd(TIM4,ENABLE);
}

float Kp=0.5;
float Ki=0.4;
float Kd= 0.1;
int target_left=0;
int target_right=0;

int err_now1=0;
int err_now2=0;
int err_last1=0;
int err_last2=0;
int err_last_last1=0;
int err_last_last2=0;
int spd_now1=0;
int spd_now2=0;
int jisuan1=0;
int jisuan2=0;
int out_left=0;
int out_right=0;

void Change_Target(int t_l,int t_r)
{
	target_left = t_l;
	target_right = t_r;
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		int cnt_left,cnt_right;
		cnt_left = abs((TIM2->CNT)-0X7FFF);
		cnt_right = abs((TIM3->CNT)-0X7FFF);
		
		TIM2->CNT = 0X7FFF;
		TIM3->CNT = 0X7FFF;

		
		//����	
		spd_now1 = cnt_left;
		err_now1 = target_left - spd_now1;
		jisuan1 = Kp*(err_now1-err_last1) + Ki*err_now1 + Kd*(err_now1+err_last_last1-2*err_last1);
		out_left += jisuan1;
		if(out_left<0)
			out_left = 0;
		if(out_left>100) 
			out_left = 100; 
		TIM_SetCompare1(TIM1,out_left);	   //��ǰ
		TIM_SetCompare2(TIM1,out_left-2);	  
		err_last_last1 = err_last1;
		err_last1 = err_now1;
		
		//�ҵ��
		spd_now2 = cnt_right;
		err_now2 = target_right - spd_now2;
		jisuan2 = Kp*(err_now2-err_last2) + Ki*err_now2 + Kd*(err_now2+err_last_last2-2*err_last2);
		out_right += jisuan2;
		if(out_right<0)
			out_right = 0;
		if(out_right>100) 
			out_right = 100; 	
		TIM_SetCompare3(TIM1,out_right);	 //��ǰ��
		TIM_SetCompare4(TIM1,out_right+2);
		err_last_last2 = err_last2;
		err_last2 = err_now2; 
		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
 
}

