#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>






#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int screenrefresh = 0;


static const int RXPin = 21, TXPin = 25;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);





#include <Preferences.h>
double HOMELAT1;
double HOMELON1;

Preferences preferences;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 10000; /// this send GPS data every 10 seconds , this is dont to keep the flow wheel tracking as much as possible during flight



int FlowState = 0;         // current state of the flow sensor

int LastFlowState = 0;     // previous state of the flow sensor

int startFlowCounter = 0; // to works out liter per min

int o = 1;


float DEG2 ;

float GPSC ;

int FlowCounter ;

int looptx;




unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 10000;


uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t mac_addr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


// Define variables to store readings to be sent------------------------------------




// Define variables to store incoming readings------------------------------------------------

int moudlemode = 14;


// Variable to store if sending data was successful-----------------------------------------


String success;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {

  float MPH1;
  float ALT1;
  float DIS2;
  float RTH ;
  float SATS ;
  float FlowCounter;
  float voltage;
  float datatx;



} struct_message;

typedef struct struct_message1 {

  int MPH10;



} struct_message1;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message BME280Readings;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

// Create a struct_message to hold incoming sensor readings
struct_message1 incomingReadings1;


const int  FlowPin = 23;



void callback() {
  //placeholder callback function
}
// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) {
    success = "Delivery Success :)";
  }
  else {
    success = "Delivery Fail :(";
  }
}


// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings1, incomingData, sizeof(incomingReadings1));
  Serial.print("Bytes received: ");
  Serial.println(len);
  moudlemode = incomingReadings1.MPH10;

}


esp_now_peer_info_t peerInfo;

void setup() {

  Serial.begin(250000);
  ss.begin(9600);
  WiFi.mode(WIFI_STA);
  preferences.begin("my-app", false);
  pinMode(12, OUTPUT);


  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;


  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }



  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }


}



void loop() {







  switch (moudlemode)
  {
    case 1:
      HOMELAT1 = preferences.getDouble("HOMELAT", 0);
      HOMELON1 = preferences.getDouble("HOMELON", 0);
      Serial.print("Home Point 1 loaded");
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      moudlemode = 13 ;
      break;
    case 2:
      HOMELAT1 = preferences.getDouble("WAYPOINTLAT1", 0);
      HOMELON1 = preferences.getDouble("WAYPOINTLON1", 0);
      Serial.print("Way Point 1 loaded");
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      moudlemode = 13 ;
      break;
    case 3:
      HOMELAT1 = preferences.getDouble("WAYPOINTLAT2", 0);
      HOMELON1 = preferences.getDouble("WAYPOINTLON2", 0);
      Serial.print("Way Point 2 loaded");
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 13 ;
      break;
    case 4:
      HOMELAT1 = preferences.getDouble("WAYPOINTLAT3", 0);
      HOMELON1 = preferences.getDouble("WAYPOINTLON3", 0);
      Serial.print("Way Point 3 loaded");
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 13 ;
      break;
    case 5:
      HOMELAT1 = preferences.getDouble("WAYPOINTLAT4", 0);
      HOMELON1 = preferences.getDouble("WAYPOINTLON4", 0);
      Serial.print("Way Point 4 loaded");
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 13 ;
      break;
    case 6:
      HOMELAT1 = preferences.getDouble("WAYPOINTLAT5", 0);
      HOMELON1 = preferences.getDouble("WAYPOINTLON5", 0);
      Serial.print("Way Point 5 loaded");
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 13 ;
      break;

    case 7:
      (gps.encode(ss.read()));
      preferences.putDouble("HOMELON", gps.location.lng());
      preferences.putDouble("HOMELAT", gps.location.lat());
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 14 ;
      break;
    case 8:
      if (gps.encode(ss.read()));
      preferences.putDouble("WAYPOINTLAT1", gps.location.lng());
      preferences.putDouble("WAYPOINTLON1", gps.location.lat());
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 14 ;
      break;
    case 9:
      if (gps.encode(ss.read()));
      preferences.putDouble("WAYPOINTLAT2", gps.location.lng());
      preferences.putDouble("WAYPOINTLON2", gps.location.lat());
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 14 ;
      break;
    case 10:
      if (gps.encode(ss.read()));
      preferences.putDouble("WAYPOINTLAT3", gps.location.lng());
      preferences.putDouble("WAYPOINTLON3", gps.location.lat());
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 14 ;
      break;
    case 11:
      if (gps.encode(ss.read()));
      preferences.putDouble("WAYPOINTLAT4", gps.location.lng());
      preferences.putDouble("WAYPOINTLON4", gps.location.lat());
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 14 ;
      break;
    case 12:
      if (gps.encode(ss.read()));
      preferences.putDouble("WAYPOINTLAT5", gps.location.lng());
      preferences.putDouble("WAYPOINTLON5", gps.location.lat());
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW

      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      smartDelay(500);
      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
      smartDelay(500);                       // wait for a second
      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
      moudlemode = 14 ;
      break;

    case 13:
      Serial.println("loaded");
      Serial.println("loaded");
      Serial.println("loaded");
      Serial.println("loaded");
      Serial.println("loaded");
      Serial.println("loaded");

      moudlemode = 15;
      break;

    case 14:
      Serial.println("Saved");
      Serial.println("Saved");
      Serial.println("Saved");
      Serial.println("Saved");
      Serial.println("Saved");
      Serial.println("Saved");

      moudlemode = 15 ;
      break;

    case 15:
      if (gps.encode(ss.read()))

        FlowState = digitalRead(FlowPin);

      // compare the buttonState to its previous state
      if (FlowState != LastFlowState) {
        // if the state has changed, increment the counter
        if (FlowState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          FlowCounter++;
          Serial.println("");
          Serial.print("Flow pulse: "); // use this to see how many pulses to 1000lm then set the int Variable to this amount
          Serial.println(FlowCounter);

        } else {
          Serial.println("no pulses");

        }

      }
      // save the current state as the last state, for next time through the loop
      LastFlowState = FlowState;
      //   Serial.println("This is the main loop :-)");

      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
       
      
        senddata();


      }




    getgps();


      break;



  }
}
