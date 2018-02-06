/******************************************************************
 * Reads a CSV and pulls basic parameters
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
 * Read csv and pull parameters to dump to RTC clock
 * row for each temporal parameter
 * dump out a date string when run
 * https://github.com/adafruit/RTClib
 * *****************************************************************
 */
 
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

#define VS1053_RESET   -1                                                // VS1053 reset pin (not used!)
#define VS1053_CS      32                                                // VS1053 chip select pin (output)
#define VS1053_DCS     33                                                // VS1053 Data/command select pin (output)
#define CARDCS         14                                                // Card chip select pin
#define VS1053_DREQ    15                                                // VS1053 Data request, ideally an Interrupt pin

String hulkHogan [2];
String randySavage = "";

void setup() {
  Serial.begin(115200);

  while (!Serial) { delay(1); }                                          //Wait for serial port to be opened
  
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);                                                           //Don't do anything more if SD isn't there
  }
  
  //printDirectory(SD.open("/"), 0);                                     //Uncomment to list the files in the root directory (/)
  
File LIST;                                                               // Create a new file object called LIST
  LIST = SD.open("/parameters.csv");                                     // Open the file. The slash is necessary, look at the serial monitor

  if(LIST){                                                              // If the file is open
    while(LIST.available()){                                             // While there's more
      Serial.write(LIST.read());                                         // Read and write to the serial monitor
      //randySavage = randySavage + LIST.read();
    }
  }
  LIST.close();                                                          // Close the file
  Serial.print(randySavage);
}

void loop() {
  //DO SOMETHING
}

// Code to organize directory parsing (DO NOT DELETE) (should probably put this in a library or something...)
void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}



