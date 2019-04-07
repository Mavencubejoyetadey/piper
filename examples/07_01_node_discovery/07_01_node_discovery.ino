/*
 * Additional Boards Manager URL:
 * https://dl.espressif.com/dl/package_esp32_index.json
 * 
 * Install Libraries:
 *  ArduinoJSON   6.10.0
 *  Painless Mesh 1.3.3
 *  TaskScheduler 3.0.2
 *  AsyncTCP      ac55171 (from Git)
 */

#include <painlessMesh.h>

#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"

void onMeshNewConn( uint32_t newNodeID );

painlessMesh  mesh;
uint32_t  nodeID;

void setup()
{
  // Setup serial interface
  Serial.begin(115200);
  Serial.print("\n\n");
  Serial.println("Creating Mesh Network");
  
  //Setup Mesh Network
  mesh.init(MESH_SSID, MESH_PASSWORD);
  nodeID = mesh.getNodeId();
  Serial.print("Device NodeID is: ");
  Serial.println(nodeID);
  
  mesh.onNewConnection(&onMeshNewConn);

}

void loop()
{  
  // Mesh Network Housekeeping
  mesh.update();
}

void onMeshNewConn( uint32_t newNodeID )
{
  Serial.print("Found new NodeID: ");
  Serial.println(newNodeID);
}
