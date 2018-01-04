volatile int interruptCounter;                                      //Used by ISR to signal interrupt occurrance
int totalInterruptCounter;                                          //Used by loop to keep track of total interrupts
 
hw_timer_t * timer = NULL;                                          //Timer object declared and is filled in below
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;               //Defined here: http://esp32.info/docs/esp_idf/html/dc/d35/portmacro_8h_source.html
                                                                    //Used to synchronize the main loop and the ISR when modifying volatile variables
                                                                    
void onTimer() {                                                    //Interrupt Service Routine (ISR) for the timer
  portENTER_CRITICAL_ISR(&timerMux);                                //..  (points to the timer)
  interruptCounter++;                                               //..Toggles the LED
  portEXIT_CRITICAL_ISR(&timerMux);                                 //..
 
}
 
void setup() {
 
  Serial.begin(115200);                                             //Creates a serial object with baud 115200
 
  timer = timerBegin(0, 80, true);                                  //Assigns values to timer object from earlier
                                                                    //0 = timer number (there are 4; valid values are 0,1,2,and 3)
                                                                    //80 = timer frequency in MHz
                                                                    //true = timer type (true = upcount;false = downcount)
  timerAttachInterrupt(timer, &onTimer, true);                      //Attaches the timer to the ISR "onTimer"
                                                                    //true = trigger type (true = edge;false = level)
  timerAlarmWrite(timer, 1000000, true);                            //Specifies that the timer should trigger at 1,000,000 μs and reset (true = reset;false = continue)
  timerAlarmEnable(timer);                                          //Enables timer

  pinMode(LED_BUILTIN, OUTPUT); //Top LED (tied to built in LED)    //Pin settings
  pinMode(21,OUTPUT); //Bottom LED
  pinMode(39,INPUT); //External Button
  pinMode(34,INPUT); //Top Button
  pinMode(36,INPUT); //Bottom Button
 
}
 
void loop() {
 
  if (interruptCounter > 0) {                                       //Runs only after interruptCounter has incremented once by portENTER_CRITICAL_ISR
 
    portENTER_CRITICAL(&timerMux);                                  //These calls receive as an argument the address of the global variable timerMUX
    interruptCounter--;                                             //Resets interruptCounter to acknowledge that it has been executed
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;
 
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Serial.print("An interrupt has occurred. Total number: ");
    Serial.println(totalInterruptCounter);
 
  }
}

