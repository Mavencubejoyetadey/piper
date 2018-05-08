/******************************************************************
 * Audio Out Example
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
 * Initializes the Adafruit VS1053, then plays tones and music files
 * from an SD card.
 * *****************************************************************
 */

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// These are the pins not used
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)

// Feather ESP32 specific pins
#define VS1053_CS      32     // VS1053 chip select pin (output)
#define VS1053_DCS     33     // VS1053 Data/command select pin (output)
#define CARDCS         14     // Card chip select pin
#define VS1053_DREQ    15     // VS1053 Data request, ideally an Interrupt pin

// setup the music player
Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

void setup()
{
  // Kick of the serial communication
  Serial.begin(115200);
  
  // Initialise the music player
  if ( musicPlayer.begin() )
  {
    Serial.println(F("Found the VS1053..."));
  }
  else
  {
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }  
  
  // Set volume for left, right channels. Lower numbers = Louder volume!
  musicPlayer.setVolume(10,10);

  // Make a tone to indicate VS1053 is working
  musicPlayer.sineTest(0x44, 500);    
  
  if ( SD.begin(CARDCS) )
  {
    Serial.println("SD reader OK ...");
  }
  else
  {
    Serial.println("SD failed, or not present");
    while (1);  // don't do anything more
  }

  musicPlayer.sineTest(0x22, 400);  
  
  // Play a file  
  Serial.println("Playing Track 002");
  musicPlayer.playFullFile("/track002.mp3");
  
  Serial.println("Playing Track 001");
  musicPlayer.playFullFile("/track001.mp3");
  
  Serial.println("Playing Track 003");
  musicPlayer.playFullFile("/track003.mp3");
  
  Serial.println("Playing Track 004");
  musicPlayer.playFullFile("/track004.mp3");
  
  Serial.println("Playing Track 005");
  musicPlayer.playFullFile("/track005.mp3");
}

void loop()
{
  // DO SOMETHING
}

