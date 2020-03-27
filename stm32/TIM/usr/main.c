#include "stm32f10x.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_InitTypeDef   EXTI_test;//外部中断使能
GPIO_InitTypeDef   GPIO_test;//GPIO端口
NVIC_InitTypeDef   NVIC_test;//中断控制器
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
/* Private function prototypes -----------------------------------------------*/
void EXTI0_Config(void)//此函数为A0上升沿触发中断
{
 //端口A0使能化
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_test.GPIO_Pin = GPIO_Pin_0;
  GPIO_test.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA,&GPIO_test);

  //时钟AFIO使能
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

 //外部中断来源于A0
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  EXTI_test.EXTI_Line = EXTI_Line0;
  EXTI_test.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_test.EXTI_Trigger = EXTI_Trigger_Rising; //触发方式--上升沿有效
  EXTI_test.EXTI_LineCmd = ENABLE;//外部中断线使能
  EXTI_Init(&EXTI_test);

	//中断控制器
  NVIC_test.NVIC_IRQChannel = EXTI0_IRQn;//EXTI0_IRQn中断引导程序的函数名
  NVIC_test.NVIC_IRQChannelPreemptionPriority = 0x0F;//中断通道优先级--抢占式优先级
  NVIC_test.NVIC_IRQChannelSubPriority = 0x0F;//响应优先级--同一优先级到来先运行数字小的
  NVIC_test.NVIC_IRQChannelCmd = ENABLE;//中断控制器使能
  NVIC_Init(&NVIC_test);
}


void EXTI15_10_Config(void)//此函数为C13下降沿触发中断
{
	
	

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_test.GPIO_Pin = GPIO_Pin_13;
  GPIO_test.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_test);


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);//外部中断来自于C13

  EXTI_test.EXTI_Line = EXTI_Line13;
  EXTI_test.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_test.EXTI_Trigger = EXTI_Trigger_Falling;//C13下降沿触发中断
  EXTI_test.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_test);

  NVIC_test.NVIC_IRQChannel = EXTI15_10_IRQn;//define EXTI15_10_IRQn 40
  NVIC_test.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_test.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_test.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_test);

}

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	
	GPIO_test.GPIO_Pin = GPIO_Pin_0;//B0
	GPIO_test.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB,&GPIO_test);
	
	GPIO_test.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;//C3/4
  GPIO_test.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_test);
	
	TIM_TimeBaseStructure.TIM_Period = 2000;
  TIM_TimeBaseStructure.TIM_Prescaler = 35999;//分频值
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//TIM_Cmd(TIM4,ENABLE)；//使能端先不打开，由中断服务子程序打开关闭
  EXTI0_Config();
  EXTI15_10_Config();
  EXTI_GenerateSWInterrupt(EXTI_Line0|EXTI_Line13);
  while (1)
  {
		if((TIM4->SR & 0x0001) == 0x0001)//定时器
		{
//			TIM4->SR &= 0xfffe;
//			GPIOC->ODR ^= 0x0010;
//			GPIO_ResetBits(GPIOA,GPIO_Pin_0);//设置A0为0;//A口置0
//			GPIO_SetBits(GPIOA,GPIO_Pin_0);//A0口置1产生上升沿，触发中断
		}

		if((TIM4->SR & 0x0001) == 0x0001)//定时器定时0.25s跟新标志位
		{
			TIM4->SR &= 0xfffe;
			GPIOC->ODR ^= 0x0010;//翻转C4端口
		}
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
