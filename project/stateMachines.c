#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
unsigned char p1val = P1IN;  
  
    switch (currentState) {
        case STATE_1:
            // Red LED on, Green LED off
            P1OUT |= LED_RED;        
            P1OUT &= ~LED_GREEN;      
            
            // Check for button presses to transition
            if (p1val & SW1) {
                currentState = STATE_1; 
            } else if (p1val & SW2) {
                currentState = STATE_2;  
            } else if (p1val & SW3) {
                currentState = STATE_3;  
            } else if (p1val & SW4) {
                currentState = STATE_4; 
            }
            break;
        
        case STATE_2:
            // Green LED on, Red LED off
            P1OUT |= LED_GREEN;      
            P1OUT &= ~LED_RED;        
            
            // Check for button presses to transition
            if (p1val & SW1) {
                currentState = STATE_1;  
            } else if (p1val & SW2) {
                currentState = STATE_2;  
            } else if (p1val & SW3) {
                currentState = STATE_3;  
            } else if (p1val & SW4) {
                currentState = STATE_4;  
            }
            break;

        case STATE_3:
            // Both LEDs off
            P1OUT &= ~LED_RED;        
            P1OUT &= ~LED_GREEN;      
            
            // Check for button presses to transition
            if (p1val & SW1) {
                currentState = STATE_1; 
            } else if (p1val & SW2) {
                currentState = STATE_2;  
            } else if (p1val & SW3) {
                currentState = STATE_3; 
            } else if (p1val & SW4) {
                currentState = STATE_4;  
            }
            break;

        case STATE_4:
            // Both LEDs on
            P1OUT |= LED_RED;         
            P1OUT |= LED_GREEN;       
            
            // Check for button presses to transition
            if (p1val & SW1) {
                currentState = STATE_1;  
            } else if (p1val & SW2) {
                currentState = STATE_2;  
            } else if (p1val & SW3) {
                currentState = STATE_3; 
            } else if (p1val & SW4) {
                currentState = STATE_4; 
            }
            break;
    }

}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}
