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
	
void Delay(unsigned int ms)//��ʱ����
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
	//ʹ��APB2ʼ�����ߵ�GPIOA��GPIOB�ں�GPIOC��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	
	
	//��ʼ�����ƿ���K2��A0��
	GPIO_test.GPIO_Pin = GPIO_Pin_0;
	GPIO_test.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_test.GPIO_Mode = GPIO_Mode_IPU;//A0�ɿ��ؿ��ƣ�Mode����Ϊ�������룬���ذ���A0�ڱ�����Ϊ�͵�ƽ
	GPIO_Init(GPIOA,&GPIO_test);
	
	//��ʼ�����ƿ���LED��D2��B0��
	GPIO_test.GPIO_Pin = GPIO_Pin_0;
	GPIO_test.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_test.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_test);
	
	//��ʼ������LED�Ƶ�C3,C4��
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

		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0x00000000)//GPIOA���϶�ȡA0�ڵ�ֵ����A0�ڱ������ɵ͵�ƽʱ����B0���Ƶ�D2����˸
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);//����B0Ϊ0,������BRR--���B0�˿ڵ�0x00000001��
			Delay(1000);
			GPIO_SetBits(GPIOB,GPIO_Pin_0);//����B0Ϊ1,����BSRR--����B0�˿�Ϊ0x00000001��
			Delay(1000);
		}
//    /* Set PD0 and PD2 */
//    GPIOD->BSRR = 0x00000005;
//    /* Reset PD0 and PD2 */
//    GPIOD->BRR  = 0x00000005;
		else//���ز�����ʱ,��C3,C4���Ƶ�D3,D4����˸
		{
		  GPIO_ResetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_4);//����B0Ϊ0,������BRR--���B0�˿ڵ�0x00000001��
			Delay(1000);
			GPIO_SetBits(GPIOC,GPIO_Pin_3|GPIO_Pin_4);//����B0Ϊ1,����BSRR--����B0�˿�Ϊ0x00000001��
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
