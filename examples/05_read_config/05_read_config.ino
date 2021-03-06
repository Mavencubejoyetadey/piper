/******************************************************************
 * SD Read Config Example
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
 * Initializes the Adafruit VS1053, then reads a text file
 * from an SD card.
 * *****************************************************************
 * Used ObjGen Live JSON Generator to create example
 * http://www.objgen.com/json/models/kJq
 * Epoch & Unix Timestamp Converstions (seconds since 1970 UTC)
 * https://www.epochconverter.com
 * 
 * Test JSON File ('config.json') should look like:
{
  "product": "piper",
  "version": "1.0.0",
  "buildDate": 1525813722,
  "tracks": [
    {
      "trackTitle": "track001.mp3",
      "startTime": 1525813723
    },
    {
      "trackTitle": "track002.mp3",
      "startTime": 1525813724
    }
  ]
} 
  */

// include SPI, SD, and JSON libraries
#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>

#define CARDCS         14     // SD card chip select pin

#define MAX_FILE_SIZE     1024
#define JSON_BUFFER_SIZE   400

void setup()
{
  // Kick off the serial communication
  Serial.begin(115200);
  delay(1000);

  // Kick off the SD card access  
  if ( SD.begin(CARDCS) )
  {
    Serial.print("SD reader OK ...\r\n");
  }
  else
  {
    Serial.print("SD failed, or not present");
    while (1);  // don't do anything more
  }

  // Get data from SD card, make sure file is not bigger than
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
  // Inside the brackets, 200 is the size of the pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;

  // StaticJsonBuffer allocates memory on the stack, it can be
  // replaced by DynamicJsonBuffer which allocates in the heap.
  //
  // DynamicJsonBuffer  jsonBuffer(400);

  // Root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.parseObject(jsonText);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  // Print values
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
  // not used in this example
}
