#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"


int main() {
  configureClocks();
  enableWDTInterrupts();

  //Making sound
  buzzer_init();
  buzzer_set_period(1000);	

  //Toggling LEDs
  
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;
  P1OUT &= ~LED_RED;
  P1OUT |= LED_GREEN;


  or_sr(0x18);          // CPU off, GIE on
}

//State Machine
int secondCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount >= 250) { 	/* once each sec... */
    secondCount = 0;		/* reset count */
    P1OUT ^= LED_GREEN;		/* toggle green LED */
  }
} 
