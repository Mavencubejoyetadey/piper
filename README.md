# piedpiper
---
##### required Installations
- [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- [Drivers](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/using-with-arduino-ide)
- [Board](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/windows.md)

##### library documentation
- [Adafruit_VS1053.h](https://github.com/adafruit/Adafruit_VS1053_Library)
- [RTClib.h](https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/arduino-library)
- [SPI.h](https://www.arduino.cc/en/Reference/SPI)
- [SD.h](https://www.arduino.cc/en/Reference/SD)
- [Wire.h](https://www.arduino.cc/en/Reference/Wire)

### user-defined pins
---
    Pin 13:     LED ("LED_BUILTIN" || topLED)
    Pin 21:     LED ("bottomLED")
    Pin 34:     Button ("topButton")
    Pin 36:     Button ("bottomButton")
    Pin 39:     Button ("externalButton")

### examples
---
*It is recommended that thet following examples are stepped through in order, as they increase in complexity.*
##### (1) Button_Blink
- An LED is lit for each button pressed.

##### (2) Timer_Interrupt
- An LED lights up each second during a timer interrupt. The total number of interrupts is sent to a terminal via serial connection.

##### (3) Button_Interrupt
- An LED lights up each second during a timer interrupt. In addition, an external interrupt is triggered for each rising edge of an external button press. Again, the total number of interrupts is sent to a terminal via serial connection.

##### (4) I2C_RTC
- A serial monitor updates with the Real-Time-Clock (RTC) time and date once per second. This will later be used to supply a base time after which a timer interrupt will manage time relative to music playing.

##### (5) SPI_mp3
- A serial monitor displays all files on the SD card inserted in the Music Maker feather's SD card slot.
- Specified .mp3 files are played
    - *Note that the filename must be as displayed on the serial monitor*
- (Currently defunct) The serial monitor should take in inputs to stop and pause or play the music

##### (6) SPI_CSV
- Similar to the previous example, except it reads a csv file named "playlist".
    - *note that the .csv file is read line-by-line. Further documentation is included in the SD library documentation*

### software status
---
*Contains the working project .ino file*
- 1/10/2018
        --> Project is at a minimum
        --> Added necessary includes and definitions
        --> No functionality yet; ready to begin development
