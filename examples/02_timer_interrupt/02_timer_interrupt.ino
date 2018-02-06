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

// Define pin numbers
#define  LED1     13
#define  LED2     21
#define  BUTTON1  34
#define  BUTTON2  39
#define  BUTTON3  36

// Define variables
volatile bool bInterruptFlag;                                       //Used by ISR to signal interrupt occurrance
hw_timer_t * snazzyTimer = NULL;                                    //Timer object declared and is filled in below

// Define functions
void onTimerInterrupt()                                             //Interrupt Service Routine (ISR) for the timer
{
  bInterruptFlag = 1;
}
 
void setup()
{
  // Initialized GPIO pins
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);   // External Button

  // Initilize interrupt
  snazzyTimer = timerBegin(0, 80, true);                            //Assigns values to timer object from earlier
                                                                    //  0 = timer number (there are 4; valid values are 0,1,2,and 3)
                                                                    //  80 = timer frequency in MHz
                                                                    //  true = timer type (true = upcount;false = downcount)
  timerAttachInterrupt(snazzyTimer, &onTimerInterrupt, true);       //Attaches the timer to the ISR "onTimerInterrupt"
                                                                    //  true = trigger type (true = edge;false = level)
  timerAlarmWrite(snazzyTimer, 1000000, true);                      //Specifies that the timer should trigger
                                                                    //  1,000,000 = number of microseconds between triggers
                                                                    //  true = reset, false = continue
  timerAlarmEnable(snazzyTimer);                                    //Enables timer 
}
 
void loop()
{ 
  if ( bInterruptFlag )
  {
    bInterruptFlag = 0;                                             // Clear the interrupt flag
    digitalWrite(LED1, !digitalRead(LED1));                         // Flip the value of indicator
    // DO SOMETHING (interrupt actions)
  }
  
  // DO SOMETHING
}

