/******************************************************************
 * GPS Start Example
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
 * This project reads the time from the GPS and turns on LED1 at the 
 * specified time.
 * *****************************************************************
 */

#include <Adafruit_GPS.h>
#include <TimeLib.h>


// Define pin numbers
#define  LED1     13

// Define serial interface with GPS
#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);

//Define variables
time_t startTimeRAW;
time_t deviceTimeRAW;
volatile bool gogogoFlag = 0;
volatile bool gogogoRunOnce = 0;

// Interrupt is called once a millisecond
SIGNAL(TIMER0_COMPA_vect) 
{  
  if ( (startTimeRAW == deviceTimeRAW) && (0 == gogogoRunOnce ) && (0 != deviceTimeRAW ) )
  {
    gogogoFlag = 1;
    gogogoRunOnce = 1;
  }
}

void setup()
{
  // Initialized GPIO pins
  pinMode(LED1,OUTPUT);
  
  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
     
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  
  // Turn on only the "minimum recommended" data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

  // Refresh rate from the GPS to microcontroller
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  // Refresh rate for the GPS fix
  GPS.sendCommand(PMTK_API_SET_FIX_CTL_1HZ);

  delay(1000);

  // Set the time the LED1 turns on
  TimeElements startTime;
  startTime.Year    = 2018-1970;  //gpsTime.Year wants years since 1970
  startTime.Month   = 5;
  startTime.Day     = 5;
  startTime.Hour    = 3;
  startTime.Minute  = 53;
  startTime.Second  = 0;
  
  startTimeRAW = makeTime(startTime);
}

void loop() // run over and over again
{   
  // read data from the GPS in the 'main loop'
  GPS.read();
  
  // if a sentence is received, we can check the checksum, parse it...
  if ( GPS.newNMEAreceived() )
  {
    GPS.parse( GPS.lastNMEA() );  
        
    TimeElements gpsTime;
    gpsTime.Second  = GPS.seconds;
    gpsTime.Minute  = GPS.minute;
    gpsTime.Hour    = GPS.hour;
    gpsTime.Day     = GPS.day;
    gpsTime.Month   = GPS.month;
    gpsTime.Year    = 30+GPS.year;  //GPS.year returns 2 digit year, gpsTime.Year wants years since 1970
        
    deviceTimeRAW = makeTime(gpsTime);
  }

  // If the time is reached it runs this section once
  if ( 1 == gogogoFlag )
  {
    gogogoFlag = 0;
       
    digitalWrite(LED1,HIGH);    // Turn on LED1 at specified time
  }
  else
  {
    digitalWrite(LED1,LOW);     // Turn off LED1 all other times
  }
}

