/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
//#include "stm32_eval.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

GPIO_InitTypeDef GPIO_test;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
void Delay(unsigned int ms)//延时函数
{
	unsigned int i,j;
	for(i = ms; i > 0; i--)
	{
		for(j = 110;j > 0; j--);
	}
}
	
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
       
  /* GPIOD Periph clock enable */
	//使用APB2始终总线的GPIOA，GPIOB口和GPIOC口
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	
	
	//初始化控制开关K2的A0口
	GPIO_test.GPIO_Pin = GPIO_Pin_0;
	GPIO_test.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_test.GPIO_Mode = GPIO_Mode_IPU;//A0由开关控制，Mode设置为上拉输入，开关按下A0口被下拉为低电平
	GPIO_Init(GPIOA,&GPIO_test);
	
	//初始化控制开关LED灯D2的B0口
	GPIO_test.GPIO_Pin = GPIO_Pin_0;
	GPIO_test.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_test);
	
	//初始化控制LED灯的C3,C4口
	GPIO_test.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_test.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_test);

	
  /* Configure PD0 and PD2 in output pushpull mode */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PD0 or PD2 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */
	while (1)
  {

		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0x00000000)//GPIOA不断读取A0口的值，当A0口被下拉成低电平时，让B0控制的D2灯闪烁
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);//设置B0为0,灯亮（BRR--清除B0端口的0x00000001）
			Delay(1000);
			GPIO_SetBits(GPIOB,GPIO_Pin_0);//设置B0为1,灯灭（BSRR--设置B0端口为0x00000001）
			Delay(1000);
		}
//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;
		else//开关不按下时,让C3,C4控制的D3,D4灯闪烁
		{
		  GPIO_ResetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_4);//设置B0为0,灯亮（BRR--清除B0端口的0x00000001）
			Delay(1000);
			GPIO_SetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_4);//设置B0为1,灯灭（BSRR--设置B0端口为0x00000001）
			Delay(1000);
		}

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;

//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;
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
