#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF que acende LEDs conforme sequência de Gray
// Seleção por evento

typedef enum {estado_0, estado_1, estado_2, estado_3, estado_4, estado_5, estado_6, estado_7} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = estado_0; // estado inicial da MEF
  
  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
  
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    if(Evento){
      Evento = 0;
      switch(Estado){
        case estado_0: //000
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = estado_1;
          break;
        case estado_1: //001
          LEDOn(LED3);
          Estado = estado_2;
          break;
        case estado_2: //011
          LEDOn(LED2);
          Estado = estado_3;
          break;
        case estado_3: //010
          LEDOff(LED3);
          Estado = estado_4;
          break;
        case estado_4: //110
          LEDOn(LED1);
          Estado = estado_5;
          break;
        case estado_5: //111
          LEDOn(LED3);
          Estado = estado_6;
          break;
        case estado_6: //101
          LEDOff(LED2);
          Estado = estado_7;
          break;
        case estado_7: //100
          LEDOff(LED3);
          Estado = estado_0;
          break;
      } // switch
    } // if
  } // while
} // main
