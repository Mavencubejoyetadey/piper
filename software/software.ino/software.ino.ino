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
 * *****************************************************************
 * 
 */

// include SPI, SD, and JSON libraries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>
#include <ArduinoJson.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>

void setup()
{
  
}

void loop()
{
  
}

