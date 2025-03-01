// MASTER

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <LED.h>

// Define the array of leds
CRGB leds[NUM_LEDS];

// Global variable to store the slave's and masters MAC address
uint8_t MasterMacAddress[6] = {0};
uint8_t SlaveMacAddress[6] = {0};
uint8_t BroadcastMacAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Global variable to store the pairing status
bool pairingMode = false;

// Global variable to store the peer information
esp_now_peer_info_t peerInfo;

enum MessageType
{
  PAIRING,
  DATA,
};
MessageType messageType;

typedef struct struct_message
{
  uint8_t msgType;
  uint8_t id;
  const char *dataText;
  uint8_t dataValue;
} struct_message;

typedef struct struct_pairing
{ // new structure for pairing
  uint8_t msgType;
  uint8_t macAddr[6];
  uint8_t pairingCycle;
  const char *pairingText;
} struct_pairing;

// Create 2 struct_message
struct_message sendingData;   // data to send
struct_message recievingData; // data received
struct_pairing pairingData;   // pairing data

uint8_t localPairingCycle = 0;

// Function prototypes
void initESPNow();
void startPairingProcess();
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len);

void setup()
{
  Serial.begin(115200);

  // Initialize ESP-NOW
  initESPNow();

  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);

  // Save the MAC address of the master to the global variable
  esp_read_mac(MasterMacAddress, ESP_MAC_WIFI_STA);
  Serial.print("Master MAC Address: ");
  for (int i = 0; i < 6; i++)
  {
    Serial.printf("%02X", MasterMacAddress[i]);
    if (i < 5)
      Serial.print(":");
  }

  // Broadcast the master’s MAC address
  startPairingProcess();
}

void loop()
{
  // Main loop can be empty or include other tasks

  static unsigned long lastEventTime = millis();
  static const unsigned long EVENT_INTERVAL_MS = 5000;

  // Wait for the slave to respond
  // If the pairing mode is not set to "Paired", keep sending the master’s MAC address every 5 seconds.
  while (pairingMode == true)
  {
    // Reset pairing if 5 seconds have passed.
    if ((millis() - lastEventTime) > EVENT_INTERVAL_MS)
    {
      Serial.println("Pairing cycle timeout, restarting pairing process");

      lastEventTime = millis();

      // Reset the pairing process and start back at the beginning.
      startPairingProcess();
    }
  }


}

// Function to initialize ESP-NOW
void initESPNow()
{
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("ESP-NOW initialization failed");
    ESP.restart();
  }
  // esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_recv_cb(OnDataRecv);
}

// Function to broadcast the master’s MAC address
void startPairingProcess()
{
  // Set the pairing mode to true
  pairingMode = true;

  //Turn LED to BLUE indicate pairing mode
  RGB_LED(true, 0, 0, 255);

  // Set pairing cycle to 1.
  localPairingCycle = 1;

  // Send pairing request to the slave
  pairingData.msgType = PAIRING;
  pairingData.pairingCycle = localPairingCycle;
  memcpy(pairingData.macAddr, MasterMacAddress, sizeof(pairingData.macAddr));

  // Send pairing broadcast
  memcpy(peerInfo.peer_addr, BroadcastMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);

  // Send to global address
  esp_now_send(BroadcastMacAddress, (const uint8_t *)&pairingData, sizeof(pairingData));

  Serial.println("Pairing cycle 1: Master MAC Address broadcasted");

  // Set localPairingCycle to 2
  localPairingCycle++;
}

// Callback function to handle incoming data
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
{
  Serial.print(len);
  Serial.println(" bytes of new data received.");

  uint8_t type = incomingData[0]; // first message byte is the type of message

  switch (type)
  {
  case DATA: // the message is data type
    memcpy(&recievingData, incomingData, sizeof(recievingData));

    Serial.println("Data received from slave:");
    Serial.print("Data Text: ");
    Serial.println(recievingData.dataText);
    Serial.print("Data Value: ");
    Serial.println(recievingData.dataValue);

    //Send data back to the slave
    sendingData.msgType = DATA;
    sendingData.dataText = "Data received:";
    sendingData.dataValue = recievingData.dataValue;

    esp_now_send(SlaveMacAddress, (const uint8_t *)&sendingData, sizeof(sendingData));
    break;

  case PAIRING:
    // Master:
    //  Cycle 1: Send the pairing request to the slave (Done in Setup)
    //  Cycle 2: Receive the slave's MAC address and send OK response
    //  Cycle 3: Receive the final OK response from the slave
    //  Cycle 4: Pairing complete
    memcpy(&pairingData, incomingData, sizeof(pairingData));

    // Check the pairing cycle
    // Receive the slave's MAC address and send OK response
    if (pairingData.pairingCycle == 1 && localPairingCycle == 2)
    {
      Serial.print("Pairing cycle ");
      Serial.print(localPairingCycle);
      Serial.println(": Slave MAC Address received");

      // Save the MAC address of the slave
      memcpy(SlaveMacAddress, pairingData.macAddr, 6);

      // Remove the global broadcast peer
      esp_now_del_peer(BroadcastMacAddress);

      // Add the new peer with the slave's MAC address
      memcpy(peerInfo.peer_addr, SlaveMacAddress, 6);
      peerInfo.channel = 0; // Use the current Wi-Fi channel
      peerInfo.encrypt = false;

      // Add the peer
      esp_now_add_peer(&peerInfo);

      Serial.println("Changed peer to Slave's MAC address");

      // Send OK response to slave using the pairing data together with the next pairing cycle and text.
      pairingData.msgType = PAIRING;
      pairingData.pairingCycle = localPairingCycle;
      memcpy(pairingData.macAddr, MasterMacAddress, 6);

      // Send the OK response to the slave
      esp_now_send(SlaveMacAddress, (const uint8_t *)&pairingData, sizeof(pairingData));

      Serial.println("Pairing cycle 2: OK response sent to slave and MAC address saved");
      Serial.println("\n\n");

      // Add one to the localPairingCycle to 3.
      localPairingCycle++;
    }
    // Receive the final OK response from the slave, send back "OK" and set pairing mode to "Paired"
    else if (pairingData.pairingCycle == 2 && localPairingCycle == 3)
    {
      Serial.print("Pairing cycle ");
      Serial.print(localPairingCycle);
      Serial.println(": Final OK response received from slave");

      // Send last pairing message to the slave
      pairingData.msgType = PAIRING;
      pairingData.pairingCycle = localPairingCycle;
      memcpy(pairingData.macAddr, MasterMacAddress, 6);
      esp_now_send(SlaveMacAddress, (const uint8_t *)&pairingData, sizeof(pairingData));

      // Set pairing mode to "Paired"
      pairingMode = false;

      // Turn LED to GREEN indicate pairing mode
      RGB_LED(true, 0, 255, 0);

      Serial.println("Pairing cycle 3: Final Pairing response send and set pairingMode to true.");
    }
    break;
  }
}