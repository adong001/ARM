#include "stm32f10x.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_InitTypeDef   EXTI_test;
GPIO_InitTypeDef   GPIO_test;
NVIC_InitTypeDef   NVIC_test;

/* Private function prototypes -----------------------------------------------*/
void EXTI0_Config(void);
void EXTI15_10_Config(void);


int main(void)
{
 
  EXTI0_Config();

  EXTI15_10_Config();

  EXTI_GenerateSWInterrupt(EXTI_Line0);
          
  while (1)
  {
		
  }
}


void EXTI0_Config(void)
{
 //初始化B0,C3,C4
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_test.GPIO_Pin = GPIO_Pin_0;
  GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_test.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB,&GPIO_test);
	
	GPIO_test.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_test.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC,&GPIO_test);


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

 
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  EXTI_test.EXTI_Line = EXTI_Line0;
  EXTI_test.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_test.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_test.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_test);

  NVIC_test.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_test.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_test.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_test.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_test);
}


void EXTI15_10_Config(void)
{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

  GPIO_test.GPIO_Pin = GPIO_Pin_13;
  GPIO_test.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_test);


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);//外部中断来自于C13


  EXTI_test.EXTI_Line = EXTI_Line13;
  EXTI_test.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_test.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_test.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_test);

  NVIC_test.NVIC_IRQChannel = EXTI15_10_IRQn;//define EXTI15_10_IRQn 40
  NVIC_test.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_test.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_test.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_test);

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
