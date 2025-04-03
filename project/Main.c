#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

int main() {
  configureClocks();
 
  buzzer_init();
  buzzer_set_period(1000);	/* start buzzing!!! 2MHz/1000 = 2kHz*/

  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;
  P1OUT &= ~LED_RED;
  P1OUT |= LED_GREEN;


  or_sr(0x18);          // CPU off, GIE on
}
