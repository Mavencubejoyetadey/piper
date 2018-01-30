# Piper
---
##### Required Installations
- [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- [Drivers](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/using-with-arduino-ide)
- [Board](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/windows.md)

##### Library Documentation
- [Adafruit_VS1053.h](https://github.com/adafruit/Adafruit_VS1053_Library)
- [RTClib.h](https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/arduino-library)
- [SPI.h](https://www.arduino.cc/en/Reference/SPI)
- [SD.h](https://www.arduino.cc/en/Reference/SD)
- [Wire.h](https://www.arduino.cc/en/Reference/Wire)

### User Defined Pins
---
    Pin 13:     LED1 (LED_BUILTIN)
    Pin 21:     LED2
    Pin 34:     BUTTON1
    Pin 36:     BUTTON3 (External Button)
    Pin 39:     BUTTON2

When reading the buttons, they normally read HIGH.  When a button is pressed they read LOW.

### examples
---
*It is recommended that thet following examples are stepped through in order, as they increase in complexity.*
##### 01_button_blink.ino
This project polls the button input values and displays the button status on the LED.  The logic for the buttons is inverted.  The button reads a HIGH normally and reads LOW when pressed.

##### 02_timer_interrupt.ino
This project uses a timer interrupt to trigger when an indicator flips value.  See the basis for the example at [techtotorialsx](https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/).

##### 03_button_interrupt.ino
This project uses a GPIO interrupt to trigger when an indicator flips value.

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
