#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_map.h"
#include "task.h"
#include "setup.h"
#define delay_per (20/ portTICK_RATE_MS)

/*-----------------------------------------------------------*/

/*
 * Entry point of program execution
 */
 	u8 i=0;
void task(void *params) {
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );
        /* Initialise data. */
        TIM_DeInit( TIM3 );
        TIM_TimeBaseStructInit( &TIM_TimeBaseStructure );
        TIM_TimeBaseStructure.TIM_Period = ( unsigned portSHORT ) 10000;
        TIM_TimeBaseStructure.TIM_Prescaler = 719;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure ); 
        TIM_ClearFlag(TIM3, TIM_FLAG_Update);	 
	
        TIM_Cmd( TIM3, ENABLE );
	 while(1) {		        
		       TIM_ClearFlag(TIM3, TIM_FLAG_Update);	    	
	    	   while (!TIM_GetFlagStatus(TIM3, TIM_FLAG_Update));
		 	     printf("%.4f s has passed\n", i*0.1001);
		       i++;
   }
        TIM_Cmd( TIM3, DISABLE );
	
  for (;;);
}

/* Entry point of program execution
 */
int main( void )
{
  prvSetupHardware();
  xTaskCreate(task, "timer", 100, NULL, 1, NULL);

  vTaskStartScheduler();
  assert(0);
  return 0;                 // not reachable
}
/*-----------------------------------------------------------*/


