#include <stdio.h>
#include "FreeRTOS.h"
#include "stm32f10x_conf.h"
#include "task.h"
#include "semphr.h"
#include "setup.h"
//#include "assert.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_map.h"

/*-----------------------------------------------------------*/

xSemaphoreHandle interruptSignal;

/**
 * Immediate interrupt handler
 */
void vTimer2IntHandler(void) {
  portBASE_TYPE higherPrio;
  xSemaphoreGiveFromISR(interruptSignal, &higherPrio);

  // Clear pending-bit of interrupt
  TIM_ClearITPendingBit( TIM2, TIM_IT_Update );

  // FreeRTOS macro to signal the end of ISR
  portEND_SWITCHING_ISR(higherPrio);
}


void scheduledInterruptTask (void* params) {
  for (;;) {
    xSemaphoreTake(interruptSignal, portMAX_DELAY);
	printf("Timer interrupt!\n");
  }
}

/*
 * Entry point of program execution
 */
int main( void )
{
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;

  prvSetupHardware();

  vSemaphoreCreateBinary(interruptSignal);
  // empty the semaphore (initially, no interrupt has occurred)
  xSemaphoreTake(interruptSignal, portMAX_DELAY);

  xTaskCreate(scheduledInterruptTask, "scheduled interrupt task",
              100, NULL, 1, NULL);

  /* Enable timer clocks */
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );

  /* Initialise data. */
  TIM_DeInit( TIM2 );
  TIM_TimeBaseStructInit( &TIM_TimeBaseStructure );

  /* Configuration of timer 2. This timer will generate an
     overflow/update interrupt (TIM2_IRQChannel) every 0.1s */
  TIM_TimeBaseStructure.TIM_Period = ( unsigned portSHORT ) ( 9999 );
  TIM_TimeBaseStructure.TIM_Prescaler = 719;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );
  TIM_ARRPreloadConfig( TIM2, ENABLE );
        
  /* Configuration of the interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init( &NVIC_InitStructure );       
  TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );

  TIM_Cmd( TIM2, ENABLE );

  printf("Setup complete\n");  // this is redirected to USART 1

  vTaskStartScheduler();
  assert(0);
  return 0;                 // not reachable
}