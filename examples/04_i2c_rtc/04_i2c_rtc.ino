/******************************************************************
 * Real Time Clock (RTC) using I2C Example
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
 * Initilizes the RTC and displays the time on the serial monitor
 * https://github.com/adafruit/RTClib
 * *****************************************************************
 */

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

// Define variables
RTC_PCF8523 timeywimey;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup ()
{
  // Kick of the serial communication
  Serial.begin(115200);

  // Verify RTC is available
  if ( timeywimey.begin() )
  {
    Serial.println("I found the RTC ...");
  }
  else
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Verify RTC is initialized, else initilize
  if ( timeywimey.initialized() )
  {
    Serial.println("RTC is initialized already ...");
  }
  else
  {
    Serial.println("RTC is NOT initialized, starting now ...");
    
    //Uncomment this line to set the RTC with an explicit date & time.
    //  For example, to set January 21, 2014 at 3am you would call:
    //timeywimey.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    
    //The following line sets the RTC to the date & time this sketch
    //  was compiled based of the computer time.  The initialized time
    //  is held as long as the battery lasts.
    timeywimey.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop ()
{
    DateTime now = timeywimey.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(1000);      //Delay 1000 milliseconds
}
