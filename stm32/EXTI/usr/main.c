#include "stm32f10x.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_InitTypeDef   EXTI_test;//外部中断使能
GPIO_InitTypeDef   GPIO_test;//GPIO端口
NVIC_InitTypeDef   NVIC_test;//中断控制器

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
void Delay(unsigned int ms)
{
	int i,j;
	for(i = 0;i < 3000;i++)
	{
		for(j = 0;j < ms; j++);
	}
}

int main(void)
{
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	
  GPIO_test.GPIO_Pin = GPIO_Pin_0;//B0
	GPIO_test.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB,&GPIO_test);
	
	GPIO_test.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;//C3/4
  GPIO_test.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_test);
	
  EXTI0_Config();

  EXTI15_10_Config();

  EXTI_GenerateSWInterrupt(EXTI_Line0);
          
  while (1)
  {
		//C4一直处于高低变化
		Delay(100);
		GPIOC->BRR = 0x0010;//C4清0
		Delay(100);
		GPIOC->BSRR = 0x0010;//C4置1
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
