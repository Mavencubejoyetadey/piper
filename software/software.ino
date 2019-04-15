/*
   Additional Boards Manager URL:
   https://dl.espressif.com/dl/package_esp32_index.json

   Install Libraries:
    ArduinoJSON   5.13.5
    Painless Mesh 1.3.3
    TaskScheduler 3.0.2
    AsyncTCP      ac55171 (from Git)
*/

#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <painlessMesh.h>

// Define VS1053 parameters
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)
// Feather ESP32
#if defined(ESP32)
  #define VS1053_CS      32     // VS1053 chip select pin (output)
  #define VS1053_DCS     33     // VS1053 Data/command select pin (output)
  #define CARDCS         14     // Card chip select pin
  #define VS1053_DREQ    15     // VS1053 Data request, ideally an Interrupt pin
#endif

// Define pin numbers
#define  LED1     13
#define  LED2     21
#define  BUTTON1  34
#define  BUTTON2  39
#define  BUTTON3  36

// Define mesh network parameters
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"

// Callback method prototypes
void BroadCastHeartbeatCallback();
void onMeshMsgRecv( uint32_t fromNodeID, String &broadcastMsg);

// Scheduled tasks
Task BroadCastHeartbeat(10000, TASK_FOREVER, &BroadCastHeartbeatCallback);

// Global variables
uint32_t  nodeID;
painlessMesh  mesh;
Scheduler runner;
SimpleList <uint32_t> nodes;
File myFile;
uint32_t configVersion;

void setup()
{
  // Setup serial interface
  Serial.begin(115200);
  delay(1000);
  Serial.print("\n\n");

  // Setup I/O pins
  Serial.print("Setting up I/O ...          ");
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);   // External Button
  Serial.println("Done");

  // Setup SD card
  Serial.print("Verifying SD card ...       ");
  if (!SD.begin(CARDCS)) {
    Serial.println("Failed");
    digitalWrite(LED1, HIGH);
    while (1);
  }
  digitalWrite(LED1, LOW);
  Serial.println("Done");

  // Check if file exists
  Serial.print("Looking for config file ... ");
  if ( SD.exists("/config.json") )
  {
    Serial.println("Found");
    Serial.print("Getting version ...         ");

    myFile = SD.open("/config.json");
    if ( myFile )
    {
      while ( myFile.available() )
      {               
        int size = myFile.size();
        std::unique_ptr<char[]> buf(new char[size]);  
        DynamicJsonBuffer jsonBuffer; 
        JsonObject &root = jsonBuffer.parseObject(myFile);

        if ( !root.success() )
        {
          Serial.println("Failed");
          while(1);
        }
        configVersion = root["version"];
        myFile.close();     
      } 
    }
    Serial.println(configVersion);
  }
  else
  {
    Serial.println("Missing");
    Serial.print("Creating config ...         ");

    // Create temporary JSON buffer with example config file
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["version"] = 0;    
    myFile = SD.open("/config.json", FILE_WRITE);    
    if ( 0 == root.printTo(myFile) )
    {
      Serial.println("Failed");
      while(1);
    }
    myFile.close();
    Serial.println("Done");
  }

  // Setup Scheduler
  Serial.print("Setting up scheduler ...    ");
  runner.init();
  runner.addTask(BroadCastHeartbeat);
  delay(5000);
  BroadCastHeartbeat.enable();
  Serial.println("Done");

  // Setup Mesh Network
  Serial.print("Setting up mesh network ... ");
  mesh.init(MESH_SSID, MESH_PASSWORD);
  Serial.println("Done");

  nodeID = mesh.getNodeId();
  Serial.print("Getting node ID ...         ");
  Serial.println(nodeID);

  mesh.onReceive(&onMeshMsgRecv);
}

void loop()
{
  // Mesh Network Housekeeping
  runner.execute();
  mesh.update();
}

void BroadCastHeartbeatCallback()
{
  String broadcastMsg = "Hola";
  mesh.sendBroadcast(broadcastMsg);

  nodes = mesh.getNodeList();
  Serial.printf( "Nodes found: %d\n", nodes.size() );
}

void onMeshMsgRecv( uint32_t fromNodeID, String &broadcastMsg)
{
  Serial.print("Rx: ");
  Serial.print(broadcastMsg);
  Serial.print(" from ");
  Serial.println(fromNodeID);
}
