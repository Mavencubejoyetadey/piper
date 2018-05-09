/******************************************************************
 * Piper Audio Player Software
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
 * This project reads the time from the GPS, reads a config file from 
 * and SD card, then plays a track based of the time specified in the
 * config file.  
 * *****************************************************************
 * Used ObjGen Live JSON Generator to create example
 * http://www.objgen.com/json/models/kJq
 * Epoch & Unix Timestamp Converstions (seconds since 1970 UTC)
 * https://www.epochconverter.com
 * *****************************************************************
 */

// include SPI, SD, and JSON libraries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>
#include <ArduinoJson.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>

//******************************
// GPIO Functions
//******************************

// Define pin numbers
#define  LED1     13

//******************************
// Communication Functions
//******************************

// Define serial interface with GPS
#define GPSSerial Serial2

// Define serial interface
HardwareSerial Serial2(2);

//******************************
// Timing Functions
//******************************

//******************************
// GPS Functions
//******************************

// Define whcih Serial the GPS should use
Adafruit_GPS GPS(&GPSSerial);

//******************************
// JSON Functions
//******************************   

// Max JSON file input size
#define MAX_FILE_SIZE     1024

// Jason Buffer Size
#define JSON_BUFFER_SIZE   512

//******************************
// SD Functions
//******************************

// SD card chip select pin
#define CARDCS              14  

//******************************
// MP3 Functions
//******************************

//******************************
// Time Functions
//******************************

//Define time tracking variables
//time_t startTimeRAW;
//time_t deviceTimeRAW;

//******************************
// Timer Functions
//******************************

// Flag which gets set every timer timer is triggered
volatile bool timerFlag;

//Timer object declared and is filled in below
hw_timer_t * snazzyTimer = NULL;

//Interrupt Service Routine (ISR) for the timer
void onTimerInterrupt()
{
  timerFlag = 1;
}

void setup()
{ 

  //******************************
  // GPIO Setup
  //******************************

  //******************************
  // Communication Setup
  //******************************
  
  // Kick off the serial communication
  Serial.begin(115200);
  delay(1000);

  Serial.print("Booting up ...");
  
  //******************************
  // Timing Setup
  //******************************
  
  //******************************
  // GPS Setup
  //******************************
     
  // 9600 NMEA is the default baud rate for GPS
  GPS.begin(9600);
  
  // Turn on only the "minimum recommended" data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

  // Refresh rate from the GPS to microcontroller
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  // Refresh rate for the GPS fix
  GPS.sendCommand(PMTK_API_SET_FIX_CTL_1HZ);

  // Delay while GPS gets setup
  delay(1000);
  
  //******************************
  // JSON Setup
  //******************************
  
  //******************************
  // SD Setup
  //******************************

  // Kick off the SD card access  
  if ( SD.begin(CARDCS) )
  {
    Serial.print("\r\nSD reader OK ...");
  }
  else
  {
    Serial.print("SD failed, or not present");
    while (1);  // don't do anything more
  }
  
  //******************************
  // MP3 Setup
  //******************************
  
  //******************************
  // Time Setup
  //******************************
  
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
  // Main Code
  //******************************

  // Get data from SD card, make sure file is not bigger than
  //  the MAX_FILE_SIZE
  char jsonText[MAX_FILE_SIZE];
  File myFile = SD.open("/config.json");

  int myFileSize = myFile.size();
  if ( myFileSize > MAX_FILE_SIZE)
  {
    Serial.print("\r\nFILE SIZE IS TOO LARGE!!!");
    Serial.print("\r\nMAX FILE SIZE IS ");
    Serial.print(MAX_FILE_SIZE);
    Serial.print(" AND FILE SIZE IS ");
    Serial.print(myFileSize);
    while(1);  // don't do anything more    
  }
  
  myFile.readBytes(jsonText, MAX_FILE_SIZE);
  myFile.close();  

  // Memory pool for JSON object tree.
  //
  // Inside the brackets is the size of the pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;

  // Root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.parseObject(jsonText);

  // Test if parsing succeeds.
  if (root.success())
  {
    Serial.print("\r\nParsing of JSON file succeded ...");
  }
  else
  {
    Serial.print("\r\nParsing of JSON file failed");
    while(1);
  }

  // Print values
  Serial.print("\r\n");
  Serial.print("\r\nProject: ");
  root["product"].printTo(Serial);
  
  Serial.print("\r\nVersion: ");
  root["version"].printTo(Serial);
  
  Serial.print("\r\nBuild Date: ");
  root["buildDate"].printTo(Serial);

  Serial.print("\r\nFile Size: ");
  Serial.print(myFileSize);
    
  JsonArray& tracks = root["tracks"];
  int trackCount = tracks.size();

  for (int i=0;i<trackCount;i++)
  {
    Serial.print("\r\n");
    Serial.print("\r\nTrack Title: ");
    tracks[i]["trackTitle"].printTo(Serial);
    
    Serial.print("\r\nTrack Start: ");
    tracks[i]["startTime"].printTo(Serial);    
  }
  
  Serial.print("\r\n");
  Serial.print("\r\nDate: ");
}

void loop()
{
  
  //******************************
  // Timer Actions
  //******************************
  
  if ( 1 == timerFlag )
  {
    timerFlag = 0;

    // DO SOMETHING
  }
  
  //******************************
  // GPS Actions
  //******************************

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
    if ( GPS.fix )
    {
      setTime( makeTime(gpsTime) );
    }
      
    Serial.print("\r\nDate: ");
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);

    Serial.print("  Time: ");
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.print('.');
    Serial.print(GPS.milliseconds);    
    
    Serial.print("  Fix: "); Serial.print((int)GPS.fix);

    Serial.print("  Epoch: ");
    Serial.print(now());    
  }
}

