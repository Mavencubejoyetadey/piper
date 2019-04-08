/*
   Additional Boards Manager URL:
   https://dl.espressif.com/dl/package_esp32_index.json

   Install Libraries:
    ArduinoJSON   6.10.0
    Painless Mesh 1.3.3
    TaskScheduler 3.0.2
    AsyncTCP      ac55171 (from Git)
*/

#include <painlessMesh.h>

#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"

// Callback method prototypes
void BroadCastHeartbeatCallback();
void onMeshMsgRecv( uint32_t fromNodeID, String &broadcastMsg);

// Scheduled tasks
Task BroadCastHeartbeat(3000, TASK_FOREVER, &BroadCastHeartbeatCallback);

// Global variables
uint32_t  nodeID;
painlessMesh  mesh;
Scheduler runner;
SimpleList <uint32_t> nodes;

void setup()
{

  // Setup serial interface
  Serial.begin(115200);
  Serial.print("\n\n");

  // Setup Scheduler
  Serial.print("Setting up scheduler ... ");
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
  Serial.print("Device NodeID is: ");
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
  Serial.printf("Num nodes: %d\n", nodes.size());
}

void onMeshMsgRecv( uint32_t fromNodeID, String &broadcastMsg)
{
  Serial.print("Rx: ");
  Serial.print(broadcastMsg);
  Serial.print(" from ");
  Serial.println(fromNodeID);
}
