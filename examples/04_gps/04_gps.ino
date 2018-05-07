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
#define  LED2     21
#define  BUTTON1  34
#define  BUTTON2  39
#define  BUTTON3  36

#define TIMEZONE_OFFSET -5

// Define serial interface with GPS
#define GPSSerial Serial2

// Define serial interface
HardwareSerial Serial2(2);
Adafruit_GPS GPS(&GPSSerial);

//Define variables
time_t startTimeRAW;
time_t deviceTimeRAW;
volatile bool gogogoEvent;
hw_timer_t * snazzyTimer = NULL;                                    //Timer object declared and is filled in below


// Define functions
void onTimerInterrupt()                                             //Interrupt Service Routine (ISR) for the timer
{
  if ( (startTimeRAW == now()) && (0 == gogogoEvent) )
  {
    gogogoEvent = 1;
  }
  else
  {
    gogogoEvent = 0;  
  }
}
 
void setup()
{
  // Initialized GPIO pins
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);   // External Button

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  //******************************
  // Timer Setup
  //******************************

  // Initilize interrupt
  snazzyTimer = timerBegin(0, 80, true);                            //Assigns values to timer object from earlier
                                                                    // 0 = timer number (there are 4; valid values are 0,1,2,and 3)
                                                                    // 80 = timer frequency in MHz
                                                                    // true = timer type (true = upcount;false = downcount)
  timerAttachInterrupt(snazzyTimer, &onTimerInterrupt, true);       //Attaches the timer to the ISR "onTimerInterrupt"
                                                                    // true = trigger type (true = edge;false = level)
  timerAlarmWrite(snazzyTimer, 1000, true);                         //Specifies that the timer should trigger
                                                                    // 1,000,000 = number of microseconds between triggers
                                                                    // true = reset, false = continue
  timerAlarmEnable(snazzyTimer);                                    //Enables timer

  //******************************
  // GPS Setup
  //******************************
     
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
  startTime.Day     = 6;
  startTime.Hour    = 23;
  startTime.Minute  = 15;
  startTime.Second  = 0;
  
  startTimeRAW = makeTime(startTime);
}
 
void loop()
{
  // If the time is reached it runs this section once
  if ( 1 == gogogoEvent )
  {
    gogogoEvent = 0;
    
    digitalWrite(LED1,HIGH);      
  }
  
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

    // Update the time if the GPS has a fix
    if (GPS.fix)
    {
      setTime( makeTime(gpsTime) );
      adjustTime(TIMEZONE_OFFSET * 3600);
    }
    
    Serial.print("\nDate: ");
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);

    Serial.print("\nTime: ");
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.print('.');
    Serial.print(GPS.milliseconds);    
    
    Serial.print("\nFix: "); Serial.print((int)GPS.fix);
    Serial.print(" Quality: "); Serial.println((int)GPS.fixquality);
    
    if (GPS.fix)
    {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
}
