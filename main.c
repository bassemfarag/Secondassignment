/**
 * Program skeleton for the course "Programming embedded systems"
 */

#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "stm32f10x_conf.h"
#include "task.h"
#include "setup.h"

/*-----------------------------------------------------------*/

//void myTask(void *params) {
//  char *str = (char*)params;
		
//  for (;;) {
//    printf("%s\n", str);
//	vTaskDelay(100 / portTICK_RATE_MS);
//  }
//  assert(0);
//}
unsigned int Time;
 void vTaskFunction( void * pvParameters )
 {
  unsigned long xLastWakeTime;
 const int period = 1;
	 float printtime;
	 
     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();
     for( ;; )
     {
			 printtime= (float)Time;
			   printf("%f s \n", printtime/1000);
         // Wait for the next cycle.
         vTaskDelayUntil( &xLastWakeTime, period/1000);
				 Time = xTaskGetTickCount();
				   // this is redirected to USART 1    
			 }
		   assert(0);
 }
unsigned int *t= &Time;

/*
 * Entry point of program execution
 */
int main( void )
{
  prvSetupHardware();
	 xTaskCreate(vTaskFunction,   // pointer to task function
              "vTaskFunction",	// name of task
			  1000,      // size of stack: 100 words = 400 byte
			            // should be at least configMINIMAL_STACK_SIZE
			  t,     // task parameters
			  1,        // priority: number between
			            // 0 and (configMAX_PRIORITIES - 1)
			  NULL      // handle to the task
			  );
	
	
  vTaskStartScheduler();
  assert(0);
  return 0;                 // not reachable
}
/*-----------------------------------------------------------*/


