/******************************************************************
 * Button Blink Example
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
 * This project polls the button input values and displays the button
 * status on the LED.  The logic for the buttons is inverted.  The
 * button reads a HIGH normally and reads LOW when pressed.
 * *****************************************************************
 */

// Define pin numbers
#define  LED1     13
//#define  LED2     21
#define  BUTTON1  A2
#define  BUTTON2  A3
#define  BUTTON3  A4

// The setup function runs once when you press reset or power the board
void setup()
{
  // Initialized GPIO pins
  pinMode(LED1,OUTPUT);
//  pinMode(LED2,OUTPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);   // External Button
}

// The loop function runs over and over again forever
void loop()
{  
  if( digitalRead(BUTTON1) )
  {
    digitalWrite(LED1,LOW);
  }
  else
  {
    digitalWrite(LED1,HIGH);
  }
  
  if( digitalRead(BUTTON2) )
  {
//    digitalWrite(LED2,LOW);
  }
  else
  {
//    digitalWrite(LED2,HIGH);
  }
  
  if( digitalRead(BUTTON3) )
  {
    // DO SOMETHING
  }
  else
  {
    // DO SOMETHING
  }
}
