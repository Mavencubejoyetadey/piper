/******************************************************************
 * SD Read Config Example
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
 * Initializes the Adafruit VS1053, then reads a text file
 * from an SD card.
 * *****************************************************************
 * Used ObjGen Live JSON Generator to create example
 * http://www.objgen.com/json/models/kJq
 * Epoch & Unix Timestamp Converstions
 * https://www.epochconverter.com
 */

// include SPI, SD, and JSON libraries
#include <ArduinoJson.h>

void setup()
{
  // Kick of the serial communication
  Serial.begin(115200);

  // Memory pool for JSON object tree.
  //
  // Inside the brackets, 200 is the size of the pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonBuffer<400> jsonBuffer;

  // StaticJsonBuffer allocates memory on the stack, it can be
  // replaced by DynamicJsonBuffer which allocates in the heap.
  //
  // DynamicJsonBuffer  jsonBuffer(400);

  // JSON input string.
  //
  // It's better to use a char[] as shown here.
  // If you use a const char* or a String, ArduinoJson will
  // have to make a copy of the input in the JsonBuffer.
  char json[] =
      "{\"product\":\"piper\",\"version\":\"1.0.0\",\"buildDate\":1525813722,\"tracks\":[{\"trackTitle\":\"track001.mp3\",\"startTime\":1525813722},{\"trackTitle\":\"track002.mp3\",\"startTime\":1525813722}]}";

  // Root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.parseObject(json);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  // Print values.
  root["product"].printTo(Serial);
  Serial.print("\n");
  root["version"].printTo(Serial);
  Serial.print("\n");
  root["buildDate"].printTo(Serial);
    
  JsonArray& tracks = root["tracks"];
  
  Serial.print("\n");
  Serial.print("\n");
  tracks[0]["trackTitle"].printTo(Serial);
  Serial.print("\n");
  tracks[0]["startTime"].printTo(Serial);

  Serial.print("\n");
  Serial.print("\n");
  tracks[1]["trackTitle"].printTo(Serial);
  Serial.print("\n");
  tracks[1]["startTime"].printTo(Serial);
}

void loop()
{
  // not used in this example
}
