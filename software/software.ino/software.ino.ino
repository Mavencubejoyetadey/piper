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

//******************************
// Communication Functions
//******************************

//******************************
// Timing Functions
//******************************

//******************************
// GPS Functions
//******************************

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
  
  
}

void loop()
{
  // DO SOMETHING  
}

