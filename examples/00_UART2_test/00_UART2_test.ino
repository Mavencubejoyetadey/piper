/******************************************************************
 * Serial Output Test
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
 * This project outputs a test message on the default Serial
 * and Serial2 (UART2).  This can be used that messages are being
 * transmitted to the onboard serial port.
 * *****************************************************************
 */

// Use UART2 as Serial2
HardwareSerial Serial2(2);

void setup()
{
  // Kick of the serial communication  
  Serial.begin(115200);
  Serial2.begin(115200);

  // Delay 1 second for serial to get setup
  delay(1000);    
}

void loop()
{
  // Print test messages to each UART
  Serial.print("\r\nThis message is sent to USB Serial");
  Serial2.print("\r\nThis message is sent to UART2 Serial");
  
  // Delay 1 second between loops
  delay(1000);
}
