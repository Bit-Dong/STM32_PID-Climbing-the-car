#include "stm32f10x.h"                  // Device header
#include "pwm.h"

void TIM1_PWM_Init(u16 per,u16 psc)
{
	/*ʹ��TIM4ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	/*ʹ��GPIO*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	/*ʹ��AFIO*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	/*����GPIO*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*������ӳ��*/
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//������ӳ��	
	
	/*��ʼ����ʱ������*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�ƵΪ1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//ѡ�����ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = per;//�������ڣ�ARR�Զ���װ����ֵ��
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//����PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�ظ���������ֵ���߼���������������
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	//TIM_ClearFlag(TIM4,TIM_FLAG_Update);//�������־λ������ճ�ʼ���ͽ����ж�
	
	/*��ʼ��PWM����*/
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;   //ѡ�����״̬�µķǹ���״̬ �͵�ƽ
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;  //ѡ�񻥲�����״̬�µķǹ���״̬ �͵�ƽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��PWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//������ԣ��ߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //����Ƚ�ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;  //��������Ƚ�ʹ��
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
	/*ʹ��TIMX��CCRX�ϵ�Ԥװ�ؼĴ���*/
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	/*ʹ��TIMX��ARR�ϵ�Ԥװ�ؼĴ�������λ*/
	//TIM_ARRPreloadConfig(TIM4,ENABLE);
	
	/*������ʱ��*/
	TIM_Cmd(TIM1,ENABLE);
}	


