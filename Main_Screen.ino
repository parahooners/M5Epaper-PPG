void Mainscreen() {

  screenrefresh = 0;

  //-------------------Touch Screen---------------------------------------------



  if (M5.TP.avaliable()) {
    if (!M5.TP.isFingerUp()) {
      M5.TP.update();
      //  canvas.fillCanvas(0);
      bool is_update = false;
      for (int i = 0; i < 2; i++) {
        tp_finger_t FingerItem = M5.TP.readFinger(i);
        if ((point[i][0] != FingerItem.x) || (point[i][1] != FingerItem.y)) {
          is_update = true;
          point[i][0] = FingerItem.x;
          point[i][1] = FingerItem.y;

          Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y , FingerItem.size);


          if ((FingerItem.x > REDBUTTON_X) && (FingerItem.x < (REDBUTTON_X + REDBUTTON_W))) {
            if ((FingerItem.y > REDBUTTON_Y) && (FingerItem.y <= (REDBUTTON_Y + REDBUTTON_H))) {

              Serial.print("btn hit");

              activeScreen = 1;
              waypoints = 15 ;
              break;

            }
          }

          
          if ((FingerItem.x > REDBUTTON_X15) && (FingerItem.x < (REDBUTTON_X15 + REDBUTTON_W15))) {
            if ((FingerItem.y > REDBUTTON_Y15) && (FingerItem.y <= (REDBUTTON_Y15 + REDBUTTON_H15))) {

              Serial.print("BIG REFRESH BUTTON BEEN HIT");

              canvas.fillCanvas(0);
              canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
              canvas.drawJpgFile(SD, "/PPG1.jpg");
              canvas.pushCanvas(0, 0, UPDATE_MODE_GC16 );

            }
          }




        }
      }

    }
  }






  //-------------------Button controlls---------------------------------------------


  if (M5.BtnL.isPressed()) {    //If the button is pressed
    count_value++;
    Serial.println(count_value);
  }



  if (M5.BtnR.isPressed()) {    //If the button is pressed
    count_value--;
    Serial.println(count_value);

  }

  if (M5.BtnP.isPressed())  {


  }








  //---------------- Screen Update Areas ----------------------------------




  M5.update();
  M5.SHT30.UpdateData();


  //---------------- Bottom Right Box on Main screen  ----------------------------------

  canvas.setTextFont(1);
  canvas.setTextSize(3);
  canvas.setCursor(420, 879);
  canvas.print(voltage);

  //---------------- This draws the clock hand  ----------------------------------

  draw_minute(incomingRTH, 0);


  //------------------ Temprature -------------------------------------------------------

  canvas.setTextFont(4);
  canvas.setTextSize(2);
  canvas.setCursor(364, 450);
  canvas.println(M5.SHT30.GetTemperature(), 1);


  //------------------ BATTERY VOTAGE ---------------------------------------------------


  canvas.setTextFont(1);
  canvas.setTextSize(3);
  canvas.setCursor(54, 882);
  canvas.println(M5.getBatteryVoltage() / 1000.0000);


  //------------------ bottom main screen clock box ---------------------------------------------------

  datay = datatx; //conversion from float to int
  canvas.setTextFont(1);
  canvas.setTextSize(3);
  canvas.setCursor(240, 897);
  canvas.println(datay);

  //------------------ FUEL ---------------------------------------------------------



  fueline = fuel * 29 ;

  canvas.fillRoundRect(136, 332, 348, 60, 10, 0); // fill it all whitish grey first



  canvas.fillRoundRect(136, 332, fueline, 60, 10, 15); // then fill it black
  Serial.print("fueline    :");
  Serial.println(fueline);



  if (M5.TP.avaliable()) {
    if (!M5.TP.isFingerUp()) {
      M5.TP.update();
      //  canvas.fillCanvas(0);
      bool is_update = false;
      for (int i = 0; i < 2; i++) {
        tp_finger_t FingerItem = M5.TP.readFinger(i);
        if ((point[i][0] != FingerItem.x) || (point[i][1] != FingerItem.y)) {
          is_update = true;
          point[i][0] = FingerItem.x;
          point[i][1] = FingerItem.y;

          Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y , FingerItem.size);


          if ((FingerItem.x > REDBUTTON_X) && (FingerItem.x < (REDBUTTON_X + REDBUTTON_W))) {
            if ((FingerItem.y > REDBUTTON_Y) && (FingerItem.y <= (REDBUTTON_Y + REDBUTTON_H))) {

              Serial.print("btn hit");
              canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
              canvas.fillCanvas(0);
              canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
              canvas.drawJpgFile(SD, "/SETTINGS.jpg");
              canvas.pushCanvas(0, 0, UPDATE_MODE_GC16 );
              activeScreen = 1;
              waypoints = 15 ;
              screenrefresh = 1;


            }
          }



        }
      }

    }
  }


  //------------------ All for the fuel calculation ------------------------------------

  mlmath = 1000 / volt_value; ///

  ml = pulses * mlmath;

  fuel = count_value - (pulses / volt_value);

  Serial.print("fuel               ");
  Serial.println(fuel);
  //-------------------This is the esp now connettion------------------------------------

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    return;
  }
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  if (esp_now_init() != ESP_OK) {
    return;
  }
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    return;
  }








}



//-------------------THIS DRAWS THE RTH HAND -------------------------------------

void draw_minute(int minute, int mode) {

  canvas.fillCircle(clock_center_x, clock_center_y, 130, 0);// this wipes the old line


  y = (130 * cos(pi - (2 * pi) / 360 * minute)) + clock_center_y;
  x = (130 * sin(pi - (2 * pi) / 360 * minute)) + clock_center_x;



  if (mode == 1)canvas.drawLine(clock_center_x, clock_center_y, x, y, 7, 15); else canvas.drawLine(clock_center_x, clock_center_y, x, y, 7, 15);


}
