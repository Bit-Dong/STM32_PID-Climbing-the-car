#include "stm32f10x.h"                  // Device header
#include "timer.h"

/*
	����TIM2,TIM3��CH1��CH2����������A��B�ࣻ
	���ת�ٲ�ͬ����е����λ����ת���ɵ�����Ҳ��ͬ��ʹ�õ�λʱ����TIM����ֵ��ͬ�����ɴ��жϵ���ٶȵı仯
*/

void TIM2_Init(u16 per,u16 psc)
{
	/*����ͨ�ö�ʱ��TIM2��GPIOʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*����ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�ƵΪ1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//ѡ�����ģʽΪ���ϼ���
	/*
	��ʱƵ�� = 72M / (PSC+1) / (ARR+1)
	*/
	TIM_TimeBaseInitStructure.TIM_Period = per;//��֪����������������*4-1
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�ظ���������ֵ���߼���������������
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	/*ѡ��ʱ��Դ��������������*/
	TIM_ICInitTypeDef TIM_ICInitStructure;  
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,  TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//TI12:A��B�����
    TIM_ICStructInit(&TIM_ICInitStructure);//ȱʡ����
    TIM_ICInitStructure.TIM_ICFilter = 10;  //�˲���
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM2,0X7FFF); //TIM4->CNT=0X7FFF��65536��һ�룩
	/*������ʱ��*/
	TIM_Cmd(TIM2,ENABLE);
}

void TIM3_Init(u16 per,u16 psc)
{
	/*����ͨ�ö�ʱ��TIM2��GPIOʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*����ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�ƵΪ1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//ѡ�����ģʽΪ���ϼ���
	/*
	��ʱƵ�� = 72M / (PSC+1) / (ARR+1)
	*/
	TIM_TimeBaseInitStructure.TIM_Period = per;//��֪����������������*4-1
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;

	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�ظ���������ֵ���߼���������������
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	/*ѡ��ʱ��Դ��������������*/
	TIM_ICInitTypeDef TIM_ICInitStructure;  
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);//TI12:A��B�����
    TIM_ICStructInit(&TIM_ICInitStructure);//ȱʡ����
    TIM_ICInitStructure.TIM_ICFilter = 0;  //�˲���
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM3,0X7FFF); //TIM4->CNT=0X7FFF��65536��һ�룩
	/*������ʱ��*/
	TIM_Cmd(TIM3,ENABLE);
}



