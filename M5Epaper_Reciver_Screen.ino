// This code was made for the M5 Epaper screen and recives data from the TTGO T Energy board via epsnow 

#include <M5EPD.h>

int screenrefresh = 0;

M5EPD_Canvas canvas(&M5.EPD);



#define SMOOTH_FONT
int loops = 0;
int screenupdate = 0;
int backlight = 0 ;
int vref = 1100;
int takeoff = 0 ;
long lastTime123 = 0;
long minutes123 = 0;
long hours123 = 0;
int datatransfer = 0;
int count1 = 0;
int point[2][2];
int logger = 0;

double HOMELAT1;
double HOMELON1;



//-----------------------Touch Screen bit-----------------------------------------------------


//-----------------------Prefrecnces Button loaction-----------------------------------------------------
#define FRAME_X 417
#define FRAME_Y 26
#define FRAME_W 200
#define FRAME_H 200

#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W/2)
#define REDBUTTON_H FRAME_H

//-----------------------UP Button loaction-----------------------------------------------------
#define FRAME_X1 202
#define FRAME_Y1 193
#define FRAME_W1 100
#define FRAME_H1 100

#define REDBUTTON_X1 FRAME_X1
#define REDBUTTON_Y1 FRAME_Y1
#define REDBUTTON_W1 (FRAME_W1/2)
#define REDBUTTON_H1 FRAME_H1

//-----------------------Down Button loaction-----------------------------------------------------
#define FRAME_X2 343
#define FRAME_Y2 187
#define FRAME_W2 100
#define FRAME_H2 100

#define REDBUTTON_X2 FRAME_X2
#define REDBUTTON_Y2 FRAME_Y2
#define REDBUTTON_W2 (FRAME_W2/2)
#define REDBUTTON_H2 FRAME_H2

//-----------------------Home point save Button loaction-----------------------------------------------------
#define FRAME_X3 101
#define FRAME_Y3 519
#define FRAME_W3 50
#define FRAME_H3 50

#define REDBUTTON_X3 FRAME_X3
#define REDBUTTON_Y3 FRAME_Y3
#define REDBUTTON_W3 (FRAME_W3/2)
#define REDBUTTON_H3 FRAME_H3

//-----------------------Home Point Load Button loaction-----------------------------------------------------
#define FRAME_X4 414
#define FRAME_Y4 522
#define FRAME_W4 50
#define FRAME_H4 50

#define REDBUTTON_X4 FRAME_X4
#define REDBUTTON_Y4 FRAME_Y4
#define REDBUTTON_W4 (FRAME_W4/2)
#define REDBUTTON_H4 FRAME_H4

//-----------------------Way point 1 Save Button loaction-----------------------------------------------------
#define FRAME_X5 101
#define FRAME_Y5 590
#define FRAME_W5 50
#define FRAME_H5 50

#define REDBUTTON_X5 FRAME_X5
#define REDBUTTON_Y5 FRAME_Y5
#define REDBUTTON_W5 (FRAME_W5/2)
#define REDBUTTON_H5 FRAME_H5
//-----------------------Way point 1 Load Button loaction-----------------------------------------------------
#define FRAME_X6 414
#define FRAME_Y6 586
#define FRAME_W6 50
#define FRAME_H6 50

#define REDBUTTON_X6 FRAME_X6
#define REDBUTTON_Y6 FRAME_Y6
#define REDBUTTON_W6 (FRAME_W6/2)
#define REDBUTTON_H6 FRAME_H6

//-----------------------Way point 2 Save Button loaction-----------------------------------------------------
#define FRAME_X7 101
#define FRAME_Y7 652
#define FRAME_W7 50
#define FRAME_H7 50

#define REDBUTTON_X7 FRAME_X7
#define REDBUTTON_Y7 FRAME_Y7
#define REDBUTTON_W7 (FRAME_W7/2)
#define REDBUTTON_H7 FRAME_H7


//-----------------------Way point 2 Load Button loaction-----------------------------------------------------
#define FRAME_X8 417
#define FRAME_Y8 652
#define FRAME_W8 50
#define FRAME_H8 50

#define REDBUTTON_X8 FRAME_X8
#define REDBUTTON_Y8 FRAME_Y8
#define REDBUTTON_W8 (FRAME_W8/2)
#define REDBUTTON_H8 FRAME_H8


//-----------------------Waypoint 3 Save Button loaction-----------------------------------------------------
#define FRAME_X9 101
#define FRAME_Y9 713
#define FRAME_W9 50
#define FRAME_H9 50

#define REDBUTTON_X9 FRAME_X9
#define REDBUTTON_Y9 FRAME_Y9
#define REDBUTTON_W9 (FRAME_W9/2)
#define REDBUTTON_H9 FRAME_H9

//-----------------------Waypoint 3 Load Button loaction-----------------------------------------------------
#define FRAME_X10 417
#define FRAME_Y10 713
#define FRAME_W10 50
#define FRAME_H10 50

#define REDBUTTON_X10 FRAME_X10
#define REDBUTTON_Y10 FRAME_Y10
#define REDBUTTON_W10 (FRAME_W10/2)
#define REDBUTTON_H10 FRAME_H10


//-----------------------Waypoint 4 Save Button loaction-----------------------------------------------------
#define FRAME_X11 101
#define FRAME_Y11 792
#define FRAME_W11 50
#define FRAME_H11 50

#define REDBUTTON_X11 FRAME_X11
#define REDBUTTON_Y11 FRAME_Y11
#define REDBUTTON_W11 (FRAME_W11/2)
#define REDBUTTON_H11 FRAME_H11


//-----------------------Waypoint 4 load Button loaction-----------------------------------------------------
#define FRAME_X12 412
#define FRAME_Y12 792
#define FRAME_W12 50
#define FRAME_H12 50

#define REDBUTTON_X12 FRAME_X12
#define REDBUTTON_Y12 FRAME_Y12
#define REDBUTTON_W12 (FRAME_W12/2)
#define REDBUTTON_H12 FRAME_H12


//-----------------------Way point 5 Save Button loaction-----------------------------------------------------
#define FRAME_X13 101
#define FRAME_Y13 845
#define FRAME_W13 50
#define FRAME_H13 50

#define REDBUTTON_X13 FRAME_X13
#define REDBUTTON_Y13 FRAME_Y13
#define REDBUTTON_W13 (FRAME_W13/2)
#define REDBUTTON_H13 FRAME_H13


//-----------------------Waypoint 5 Load Button loaction-----------------------------------------------------
#define FRAME_X14 417
#define FRAME_Y14 845
#define FRAME_W14 50
#define FRAME_H14 50

#define REDBUTTON_X14 FRAME_X14
#define REDBUTTON_Y14 FRAME_Y14
#define REDBUTTON_W14 (FRAME_W14/2)
#define REDBUTTON_H14 FRAME_H14

//-----------------------RADAR SREEN BUTTON-----------------------------------------------------
#define FRAME_X15 209
#define FRAME_Y15 650
#define FRAME_W15 300
#define FRAME_H15 300

#define REDBUTTON_X15 FRAME_X15
#define REDBUTTON_Y15 FRAME_Y15
#define REDBUTTON_W15 (FRAME_W15)
#define REDBUTTON_H15 FRAME_H15



#include <esp_now.h>

#include <WiFi.h>

#include <Wire.h>

int ledflag = 0;

const float pi = 3.14159267 ;
const int clock_center_x = 267;
const int clock_center_y = 735;

const int clock_center_xf = 140;
const int clock_center_yf = 655;

int o = 1;

// variables used to calculate coordinates of points on the circle
int x;
int y;
int x1;

int xf;
int yf;
int x1f;
//int y1;

float mlmath ; ///

float ml ;

float fuel ;


// indicates the active screen
int activeScreen = 3;

int waypoints = 0;



float count_value = 7;
float volt_value = 1900;
int pulses ;
int pulsestime ;
float TXVOLT = 0.00;

int minutes ;

float FlowCounter ;

int fueline  ;

unsigned long previousMillis = 0;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;

const long interval = 10000; /// this send GPS data every 10 seconds , this is dont to keep the flow wheel tracking as much as possible during flight


uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8_t mac_addr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//---------------------------------------Reciving information store po--------------------------------


// Define variables to store readings to be sent

int moudlemode ;

// Define variables to store incoming readings

int incomingMPH1 ;
int incomingALT1 ;
float incomingDIS2 ;
int incomingDEG2 ;
int incomingSATS ;
int incomingGPSC ;
int incomingRTH ;
float voltage;
float datatx;
int datay; //this is done as the data from esp now need to be stored as a float firstly then converted

// Variable to store if sending data was successful

String success;

//Structure example to send data
//Must match the receiver structure

typedef struct struct_message {

  float  a ;
  float  b ;
  float  d ;
  float  e ;
  float  f ;
  float  g ;
  float  h ;
  float  i ;


} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message BME280Readings;

// Create a struct_message called myData
struct_message incomingReadings;

//---------------------------------------Sending information and structure--------------------------------





//---------------------------------------------------------------------------------------------------------------------------





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



void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {

  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);

  incomingMPH1  = incomingReadings.a ;
  incomingALT1  = incomingReadings.b ;
  incomingDIS2 =  incomingReadings.d ;
  incomingRTH  = incomingReadings.e ;
  incomingSATS = incomingReadings.f  ;
  pulses =  incomingReadings.g ;
  voltage =  incomingReadings.h ;
  datatx =  incomingReadings.i ;



}





esp_now_peer_info_t peerInfo;

void setup() {

  M5.begin(true, true, false, true, true);

  Serial.begin(250000);

  M5.EPD.SetRotation(90);
  M5.TP.SetRotation(90);
  M5.EPD.Clear(true);
  M5.SHT30.Begin();
  M5.BatteryADCBegin();
  canvas.createCanvas(540, 960);

  canvas.drawJpgFile(SD, "/PPG1.jpg");
  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16 );






  WiFi.mode(WIFI_STA);


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

void loop()
{


  switch (activeScreen)
  {
    case 1:



      Settings();
      break;
    case 2:
      //Screen3();
      break;
    case 3:
      Mainscreen();
      screenupdate++;
      Serial.print("Screen update   :");
      Serial.println(screenupdate);


      if (screenupdate > 500) {




        screenupdate = 0;

        gpsloop() ;
        canvas.pushCanvas(0, 0, UPDATE_MODE_A2 );


      }





      break;
    case 4:
      ;
      break;
    case 5:
      ;
      break;
    case 6:
      //Screen2();
      break;


  }
}
