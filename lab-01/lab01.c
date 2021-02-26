//==============================================================================
//Inclusao de cabeçalhos e bibliotecas
//==============================================================================
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"



//==============================================================================
// Definição de constantes
//==============================================================================

#define __CONFIG_CLOCK	  (SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480)     // Config do clock
#define __SYSTEM_CLOCK    (24000000UL)                                               // Freq do clock

uint8_t LED_D1 = 0;



//==============================================================================
// Código a ser executado
//==============================================================================

void main(void){
  //========================
  // Inicialização da GPIO
  //========================
  
  SysCtlClockFreqSet(__CONFIG_CLOCK, __SYSTEM_CLOCK);   // Configura a frequência de clock
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);          // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));   // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);      // LEDs D3 e D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0);            // LEDs D3 e D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  
  //========================
  // Loop de execução
  //========================
  
  while(1){
    SysCtlDelay(__SYSTEM_CLOCK/3);                              // Delay de 1 segundo (a função contém 3 instruções)
    
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 1)           // Testa estado do LED 4
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);             // Apaga LED D4
    else
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);    // Acende LED D4
  } // while
  
} // main