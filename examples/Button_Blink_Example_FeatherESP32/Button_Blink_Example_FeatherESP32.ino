                                                        // the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);                         //Top LED (tied to built in LED)
  pinMode(21,OUTPUT);                                   //Bottom LED
  pinMode(39,INPUT);                                    //External Button
  pinMode(34,INPUT);                                    //Top Button
  pinMode(36,INPUT);                                    //Bottom Button
}

                                                        // the loop function runs over and over again forever
void loop() {
  if(digitalRead(36) == LOW)                            //EXTERNAL BUTTON
  {
    //DO NOTHING
  }
  if(digitalRead(34) == LOW)                            //WHEN TOP BUTTON
  {
  digitalWrite(LED_BUILTIN, HIGH);                      //TOP LED ON
  delay(10);
  digitalWrite(LED_BUILTIN,LOW);
  }
  if(digitalRead(39) == LOW)
  {
  digitalWrite(21,HIGH);                                //WHEN BOTTOM LED ON 
  delay(10);
  digitalWrite(21,LOW);                                 //BOTTOM LED ON 
  }
}
