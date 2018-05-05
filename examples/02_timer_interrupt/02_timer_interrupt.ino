/******************************************************************
 * Timer Interrupt Example
 * Developed by Sevun Scientific, Inc.
 * http://sevunscientific.com
 * *****************************************************************
 *
 *    _____/\\\\\\\\\\\_______/\\\\\\\\\\\____/\\\\\\\\\\\_
 *     ___/\\\/////////\\\___/\\\/////////\\\_\/////\\\///__
 *      __\//\\\______\///___\//\\\______\///______\/\\\_____
 *       ___\////\\\___________\////\\\_____________\/\\\_____
 *        ______\////\\\___________\////\\\__________\/\\\_____
 *         _________\////\\\___________\////\\\_______\/\\\_____
 *          __/\\\______\//\\\___/\\\______\//\\\______\/\\\_____
 *           _\///\\\\\\\\\\\/___\///\\\\\\\\\\\/____/\\\\\\\\\\\_
 *            ___\///////////_______\///////////_____\///////////__
 *
 * *****************************************************************
 * This project uses a timer interrupt to trigger when an indicator
 * flips value.
 * https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/
 * *****************************************************************
 */
 
#include <TimerOne.h> 

// Define pin numbers
#define  LED1     13
//#define  LED2     21
#define  BUTTON1  A2
#define  BUTTON2  A3
#define  BUTTON3  A4

// Define variables
volatile bool bInterruptFlag;                                       //Used by ISR to signal interrupt occurrance

// Define functions
void onTimerInterrupt()                                             //Interrupt Service Routine (ISR) for the timer
{
  bInterruptFlag = 1;
}
 
void setup()
{
  // Initialized GPIO pins
  pinMode(LED1,OUTPUT);
//  pinMode(LED2,OUTPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);   // External Button

  Timer1.initialize(1000000);                                       // Initalized the timer to 1 second (in microseconds)
  Timer1.attachInterrupt(onTimerInterrupt);                         // blinkLED to run every 0.15 seconds
}
 
void loop()
{ 
  if ( bInterruptFlag )
  {
    bInterruptFlag = 0;                                             // Clear the interrupt flag
    digitalWrite(LED1, !digitalRead(LED1));                         // Flip the value of indicator
  }
  
  // DO SOMETHING
}

