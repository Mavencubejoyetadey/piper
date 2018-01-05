# piedpiper
---
Install arduino IDE: https://www.arduino.cc/en/Main/Software


- It is recommended that thet following examples are stepped through in order, as they increase in complexity.

### board layout
---
Pin 13:     LED ("LED_BUILTIN" || topLED)
Pin 21:     LED ("bottomLED")
Pin 34:     Button ("topButton")
Pin 36:     Button ("bottomButton")
Pin 39:     Button ("externalButton")

### examples
---
##### (1) Button Blink
An LED is lit for each button pressed.

##### (2) Timer Blink
An LED lights up each second during a timer interrupt. The total number of interrupts is sent to a terminal via serial connection.

##### (3) ButtonInterrupt Blink
An LED lights up each second during a timer interrupt. In addition, an external interrupt is triggered for each rising edge of an external button press. Again, the total number of interrupts is sent to a terminal via serial connection.

##### (4) I2C Polling
A serial monitor updates with the Real-Time-Clock (RTC) time and date once per second. This will later be used to supply a base time after which a timer interrupt will manage time relative to music playing.