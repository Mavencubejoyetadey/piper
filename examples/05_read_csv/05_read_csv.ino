/******************************************************************
 * SD read via SPI Example
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

// Create a music player object
Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

File myFile;
int* playlist = NULL;  // pointer to an int, intiallly to nothing.

void setup()
{
  uint8_t trackCount = 0;
  
  // Kick of the serial communication
  Serial.begin(115200);

  while (!Serial) { delay(1); } //Wait for serial port to be opened

  Serial.println("Adafruit VS1053 Feather Test");
  
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
  
  if ( SD.begin(CARDCS) )
  {
    Serial.println("SD reader OK ...");
  }
  else
  {
    Serial.println("SD failed, or not present");
    while (1);  // don't do anything more
  }

  Serial.println();

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("/playlist.txt", FILE_READ);

  if (true == myFile)
  {
    Serial.print("Playlist:");

    // read from the file to determine track count
    if ( myFile.available() )
    {
      char N = myFile.read();
      char N10 = myFile.read();
      char N01 = myFile.read();

      if ( ('N' == N) && (-1 != N10) && (-1 != N01) && isDigit(N10) && isDigit(N01) )
      {
        String inString = (String)N10 + (String)N01;
        trackCount = inString.toInt();

        if ( trackCount > 0 )
        {
          playlist = new int[trackCount];








          
        }
        else
        {
          Serial.println("Can't read track count");
          while(1);
        } 
      }
      else
      {
        Serial.println("Can't read track count");
        while(1);
      }
    }
    else
    {
      Serial.println("Can't read file");
      while(1);
    }
    
    Serial.println("Track Count: ");
    Serial.print(trackCount,DEC);

    delete [] playlist;
    
    // close the file:
    myFile.close();    
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{
  // DO SOMETHING
}


