/**
 * Program skeleton for the course "Programming embedded systems"
 */

#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "stm32f10x_conf.h"
#include "task.h"
#include "setup.h"
#include "stm32f10x_gpio.h"
/*-----------------------------------------------------------*/
#define TimeA (200 / portTICK_RATE_MS)
#define TimeB (1800/ portTICK_RATE_MS)
#define delay_per (20/ portTICK_RATE_MS)

int i;
void myTask(void *params) {
   for (;;) {
      if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)) {
       while (i<TimeA) {
				if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)) {		
  	    vTaskDelay(delay_per);
					i=i+delay_per;	
				}
					GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
					vTaskDelay(20 / portTICK_RATE_MS);
				if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)) {
					i=0;
					break;
				}
			 }
		 }
			 if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)) {
					while (i<TimeB) {
						if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)) {		
						vTaskDelay(delay_per);
						i=i+delay_per;	
						}
							GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
              vTaskDelay(20 / portTICK_RATE_MS);
						if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)) {
						i=0;
						break;
						}
					}
				}
}
  }		
/*
 * Entry point of program execution
 */
 int main( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;

  prvSetupHardware();
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init( GPIOC, &GPIO_InitStructure );
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init( GPIOC, &GPIO_InitStructure );

  xTaskCreate(myTask, "GPIO reader", 100, NULL, 1, NULL);

  vTaskStartScheduler();
  assert(0);
  return 0;                 // not reachable
}
/*-----------------------------------------------------------*/


