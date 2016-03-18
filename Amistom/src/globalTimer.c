#include "globalTimer.h"


void GlobalTimerInit(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//APB1_PrescalerValue = (RCC_Clocks.PCLK1_Frequency/1000000) - 1;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //����� � ������������
	TIM_TimeBaseStructure.TIM_Prescaler = 100;  //��������� �����������
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���� �����
	TIM_TimeBaseStructure.TIM_Period = 850;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //��������
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //���������� ������ ��������
	TIM_UpdateRequestConfig  (TIM5, TIM_UpdateSource_Global);
	TIM_UpdateDisableConfig (TIM5,DISABLE);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); //���������� ���������� �� �������

	TIM_Cmd(TIM5, ENABLE);  //��������� �������
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM5_IRQHandler(void)
{
	++cntr1;
	++cntr_laser;
	++cntr_imp;
	++cntr_emit_wd;
	++cntr_diaph;
	//++systick_ms;
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}

void delay_ms(uint32_t ms)
{
	volatile uint32_t nCount; 					//�������
	RCC_ClocksTypeDef RCC_Clocks; 				//������� ������� 168���
	RCC_GetClocksFreq (&RCC_Clocks);
	nCount = (RCC_Clocks.HCLK_Frequency/12000)*ms; //�� -> �����
	for (; nCount!=0; nCount--);
}

void delay_us (uint16_t us)
{
	volatile uint32_t nCount; 						//���������� ��� �����
	RCC_ClocksTypeDef RCC_Clocks; 					//���������� ��� ���������� ������� �������
	RCC_GetClocksFreq (&RCC_Clocks); 				//������� �������� �������

	nCount=(RCC_Clocks.HCLK_Frequency/1200000)*us; 	//��� -> �����
	for (; nCount!=0; nCount--);
}

void delay(int count) {
    	while(--count);
}
