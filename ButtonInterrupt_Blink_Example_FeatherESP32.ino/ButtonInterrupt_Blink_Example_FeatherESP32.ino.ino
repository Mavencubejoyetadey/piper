volatile bool timerinterruptCounter = false;                                //Flag for timer interrupts
volatile bool externalinterruptCounter = false;                             //Flag for button interrupts
int totalInterruptCounter;                                                  //Total number of interrupt occurrances

const byte topButton = 34;                                                  //Define some pin names (numbers found on bottom of ESP32)
const byte topLED = 13;
const byte bottomButton = 39;
const byte bottomLED = 21;
const byte externalButton = 36;

hw_timer_t * timer = NULL;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
                                                                    
void onTimer() {                                                            //ISR for timer interrupts
  portENTER_CRITICAL_ISR(&mux);
  timerinterruptCounter = true;                                             //Set flag
  portEXIT_CRITICAL_ISR(&mux); 
}

void onButton() {                                                           //ISR for button interrupts
  portENTER_CRITICAL_ISR(&mux);
  externalinterruptCounter = true;                                          //Set flag
  portEXIT_CRITICAL_ISR(&mux);
}

void setup() {
 
  Serial.begin(115200);                                                     //Create a serial monitor
 
  timer = timerBegin(0, 80, true);                                          //Set up timer object
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);                                                  //Enable timer

  pinMode(topLED, OUTPUT);                                                  //Pin I/O muxing and setup
  pinMode(bottomLED,OUTPUT);
  pinMode(bottomButton,INPUT);
  pinMode(topButton,INPUT);
  pinMode(externalButton,INPUT);
  attachInterrupt(digitalPinToInterrupt(externalButton),onButton,FALLING);  //Attaches the onButton ISR to pin 
                                                                            //"external button" and triggers on
                                                                            //falling edges
 
}
 
void loop() {
 
  if (timerinterruptCounter) {                                              //Code to execute on timer interrupts
    
    portENTER_CRITICAL(&mux);
    timerinterruptCounter = false;                                          //Reset flag
    portEXIT_CRITICAL(&mux);
 
    totalInterruptCounter++;                                                //Upcount total interrupts
 
    digitalWrite(topLED, !digitalRead(topLED));                             //Toggle top LED (and built-in LED)
    Serial.print("A timer interrupt has occurred. Total number: ");         //Output information to serial monitor
    Serial.println(totalInterruptCounter);
 
  }

  if(externalinterruptCounter) {                                            //Code to execute on button interrupts

    portENTER_CRITICAL(&mux);
    externalinterruptCounter = false;                                       //Reset flag
    portEXIT_CRITICAL(&mux);
    
    totalInterruptCounter++;                                                //Upcount total interrupts

    digitalWrite(bottomLED, !digitalRead(bottomLED));                       //Toggle bottom LED
    Serial.print("An external interrupt has occurred. Total number: ");     //Output information to serial monitor
    Serial.println(totalInterruptCounter);
  }
}

