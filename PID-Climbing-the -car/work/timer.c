#include "stm32f10x.h"                  // Device header
#include "timer.h"

/*
	配置TIM2,TIM3的CH1、CH2作编码器的A、B相；
	电机转速不同，机械几何位移量转换成的脉冲也不同，使得单位时间内TIM计数值不同，可由此判断电机速度的变化
*/

void TIM2_Init(u16 per,u16 psc)
{
	/*开启通用定时器TIM2和GPIO时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频为1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数模式为向上计数
	/*
	定时频率 = 72M / (PSC+1) / (ARR+1)
	*/
	TIM_TimeBaseInitStructure.TIM_Period = per;//已知编码器线数：线数*4-1
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器的值，高级计数器才需配置
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	/*选择时钟源，配置正交解码*/
	TIM_ICInitTypeDef TIM_ICInitStructure;  
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,  TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//TI12:A、B项都计数
    TIM_ICStructInit(&TIM_ICInitStructure);//缺省输入
    TIM_ICInitStructure.TIM_ICFilter = 10;  //滤波器
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM2,0X7FFF); //TIM4->CNT=0X7FFF（65536的一半）
	/*启动定时器*/
	TIM_Cmd(TIM2,ENABLE);
}

void TIM3_Init(u16 per,u16 psc)
{
	/*开启通用定时器TIM2和GPIO时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频为1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数模式为向上计数
	/*
	定时频率 = 72M / (PSC+1) / (ARR+1)
	*/
	TIM_TimeBaseInitStructure.TIM_Period = per;//已知编码器线数：线数*4-1
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;

	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器的值，高级计数器才需配置
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	/*选择时钟源，配置正交解码*/
	TIM_ICInitTypeDef TIM_ICInitStructure;  
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);//TI12:A、B项都计数
    TIM_ICStructInit(&TIM_ICInitStructure);//缺省输入
    TIM_ICInitStructure.TIM_ICFilter = 0;  //滤波器
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM3,0X7FFF); //TIM4->CNT=0X7FFF（65536的一半）
	/*启动定时器*/
	TIM_Cmd(TIM3,ENABLE);
}



