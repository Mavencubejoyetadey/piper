#include <Adafruit_VS1053.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
  
// Define button & LED pin names
const byte topButton = 34;
const byte topLED = 13;
const byte bottomButton = 39;
const byte bottomLED = 21;
const byte externalButton = 36;

// Define timer object and port mux
hw_timer_t * timer = NULL;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

// Define interrupt flags
volatile bool timerinterruptCounter = false;
volatile bool externalinterruptCounter = false;   

// Define I2C - Real Time Clock and basic time definitions
RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define SPI - SD pins
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)
#define VS1053_CS      32     // VS1053 chip select pin (output)
#define VS1053_DCS     33     // VS1053 Data/command select pin (output)
#define CARDCS         14     // Card chip select pin
#define VS1053_DREQ    15     // VS1053 Data request, ideally an Interrupt pin

// Define SPI - Music Player
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

// Define Interrupt Service Routines
void onTimer() {
  portENTER_CRITICAL_ISR(&mux);
  timerinterruptCounter = true;
  portEXIT_CRITICAL_ISR(&mux); 
}
void onButton() {
  portENTER_CRITICAL_ISR(&mux);
  externalinterruptCounter = true;
  portEXIT_CRITICAL_ISR(&mux);
}


void setup() {

// Set up serial port and wait for it to open
  Serial.begin(115200);
  while (!Serial) { delay(1); }

// Initialize RTC if necessary
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
// Set up button/led pin modes, attach interrupt
  pinMode(topLED, OUTPUT); 
  pinMode(bottomLED,OUTPUT);
  pinMode(bottomButton,INPUT);
  pinMode(topButton,INPUT);
  pinMode(externalButton,INPUT);
  attachInterrupt(digitalPinToInterrupt(externalButton),onButton,FALLING);

// Set up timer, attach interrupt
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 10000000, true);
  timerAlarmEnable(timer); 

// Initialize Music Player if necessary
  if (! musicPlayer.begin()) {
     Serial.println(F("Could not find VS_1053 - is the MusicMaker feather attached?"));
     while (1);
  }

// Check for an SD card
if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);
  }

// Print SD root for ease of debugging
  printDirectory(SD.open("/"), 0);

// Attach interrupt to the Music Player
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

// Specify the .csv file to be read and print contents to serial monitor
  File playlist = SD.open("/playlist.csv");
  if(playlist){
    while(playlist.available()){
      playlist.read();  // Reads character by character for each pass.
    }
  playlist.close();
  }
  Serial.println(F("Playing /AC_GuitarFX120D-01.mp3"));
  musicPlayer.playFullFile("/AC_GuitarFX120D-01.mp3");  // Place file names here to play in order. Conditional loops may go here.
  
  Serial.println(F("Playing /WA_BeatLoopD-125.mp3"));
  musicPlayer.playFullFile("/WA_BeatLoopD-125.mp3");

  Serial.println(F("Playing /WA_GamerLead-136-A.mp3"));
  musicPlayer.playFullFile("/WA_BeatLoopD-125.mp3");

  Serial.println(F("Playing /WA_Wobbulous-160-A.mp3"));
  musicPlayer.playFullFile("/WA_Wobbulous-160-A.mp3");

  Serial.println(F("Playing /AC_GuitarMix85C-06.mp3"));
  musicPlayer.playFullFile("/AC_GuitarMix85C-06.mp3");

  Serial.println(F("Playing /AC_12Str85F-01.mp3"));
  musicPlayer.playFullFile("/AC_12Str85F-01.mp3");

  Serial.println(F("Playing /AC_GuitarMix120F-05.mp3"));
  musicPlayer.playFullFile("/AC_GuitarMix120F-05.mp3");
}

void loop() {

// Timer Interrupt Code
  if (timerinterruptCounter) {
    portENTER_CRITICAL(&mux);
    timerinterruptCounter = false;
    portEXIT_CRITICAL(&mux); 

    // Write timer interrupt code here
  }
  
// Button Interrupt Counter
  if(externalinterruptCounter) {
    portENTER_CRITICAL(&mux);
    externalinterruptCounter = false;
    portEXIT_CRITICAL(&mux);

    // Write button interrupt code here
  }

// Condition for stopping
  if (musicPlayer.stopped()) {
  Serial.println("Done playing music");
  while (1) {
    delay(10);  // we're done! do nothing...
    }
  }
}

// Code for properly listing the root directory (don't modify)
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
