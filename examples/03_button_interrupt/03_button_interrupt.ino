/******************************************************************
 * Button Interrupt Example
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
 * This project uses a GPIO interrupt to trigger when an indicator 
 * flips value.
 * *****************************************************************
 */

// Define pin numbers
#define  LED1     13
#define  BUTTON1  34

// Define variables
volatile bool bInterruptFlag;                                       //Used by ISR to signal interrupt occurrance

// Define functions
void onButtonInterrupt()                                            //Interrupt Service Routine (ISR) for the timer
{
  bInterruptFlag = 1;
}

void setup()
{
  // Initialized GPIO pins
  pinMode(LED1,OUTPUT);
  pinMode(BUTTON1,INPUT);

  // Initilize interrupt
  attachInterrupt(digitalPinToInterrupt(BUTTON1),onButtonInterrupt,FALLING);  //Attaches the onButtonInterrupt ISR to pin 
                                                                              //button and triggers on falling edges
}
 
void loop()
{
  if ( bInterruptFlag )
  {
    bInterruptFlag = 0;                                             // Clear the interrupt flag
    digitalWrite(LED1, !digitalRead(LED1));                         // Flip the value of indicator
  }
}

