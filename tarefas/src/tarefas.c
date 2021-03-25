#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;

typedef struct  {
  uint32_t led;               // led que será utilizado na task
  uint32_t delay;             // período de delay da task
} thread_arg;

void thread(void *arg){       // Passagem dos parametros (struct) por ponteiro
  uint8_t state = 0;
  
  thread_arg *aux;
  aux = arg;
  
  uint8_t led = (uint8_t) aux->led;
  uint32_t delay = aux->delay;

  while(1){                   // Loop de execução da thread    
    state ^= led;
    LEDWrite(led, state);
    osDelay(delay);    
  } // while
} // thread


void main(void){
  LEDInit(LED4 | LED3 | LED2 | LED1);

  osKernelInitialize();
  
  thread_arg arg1 = {1,200};
  thread_arg arg2 = {2,300};
  thread_arg arg3 = {3,500};
  thread_arg arg4 = {4,700};
  
  thread1_id = osThreadNew(thread, (void *) &arg1, NULL);
  thread2_id = osThreadNew(thread, (void *) &arg2, NULL);
  thread3_id = osThreadNew(thread, (void *) &arg3, NULL);
  thread4_id = osThreadNew(thread, (void *) &arg4, NULL);
  
  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
