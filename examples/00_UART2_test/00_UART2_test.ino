HardwareSerial Serial2(2);

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop()
{
  Serial.print("\r\nThis message is sent to USB Serial");
  Serial2.print("\r\nThis message is sent to UART2 Serial");
  delay(1000);
}
