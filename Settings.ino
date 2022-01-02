void Settings() {

  if (screenrefresh == 1) {
    canvas.fillCanvas(0);
    canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
    screenrefresh = 0;

    canvas.drawJpgFile(SD, "/SETTINGS.jpg");
    canvas.pushCanvas(0, 0, UPDATE_MODE_GC16 );
  }





  canvas.pushCanvas(0, 0, UPDATE_MODE_A2 );


  //-------------------Touch Screen settings and home buttion---------------------------------------------



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
              canvas.drawJpgFile(SD, "/PPG1.jpg");
              canvas.pushCanvas(0, 0, UPDATE_MODE_GC16 );
              activeScreen = 3;

            }
          }







          //----------------------------------This is the Up arrow Save button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X1) && (FingerItem.x < (REDBUTTON_X1 + REDBUTTON_W1))) {
            if ((FingerItem.y > REDBUTTON_Y1) && (FingerItem.y <= (REDBUTTON_Y1 + REDBUTTON_H1))) {


              canvas.setTextFont(1);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X1, REDBUTTON_Y1);
              canvas.print("✓");
              count_value++;


            }
          }

          //----------------------------------This is the Down arrow Save button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X2) && (FingerItem.x < (REDBUTTON_X2 + REDBUTTON_W2))) {
            if ((FingerItem.y > REDBUTTON_Y2) && (FingerItem.y <= (REDBUTTON_Y2 + REDBUTTON_H2))) {

              canvas.setTextFont(1);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X2, REDBUTTON_Y2);
              canvas.print("✓");
              count_value--;


            }
          }

          //----------------------------------This is the Home Point Save button--------------------------------------


          if ((FingerItem.x > REDBUTTON_X3) && (FingerItem.x < (REDBUTTON_X3 + REDBUTTON_W3))) {
            if ((FingerItem.y > REDBUTTON_Y3) && (FingerItem.y <= (REDBUTTON_Y3 + REDBUTTON_H3))) {
              moudlemode = 7 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));
              canvas.setTextFont(1);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X3, REDBUTTON_Y3);
              canvas.print("✓");



            }
          }


          //----------------------------------This is the Home Point Load button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X4) && (FingerItem.x < (REDBUTTON_X4 + REDBUTTON_W4))) {
            if ((FingerItem.y > REDBUTTON_Y4) && (FingerItem.y <= (REDBUTTON_Y4 + REDBUTTON_H4))) {
              moudlemode = 1 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));
              canvas.setTextFont(1);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X4, REDBUTTON_Y4);
              canvas.print("✓");


            }
          }

          //----------------------------------This is the Way Point1 Save button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X5) && (FingerItem.x < (REDBUTTON_X5 + REDBUTTON_W5))) {
            if ((FingerItem.y > REDBUTTON_Y5) && (FingerItem.y <= (REDBUTTON_Y5 + REDBUTTON_H5))) {
              moudlemode = 8 ;
              canvas.setTextFont(4);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X5, REDBUTTON_Y5);
              canvas.print("✓");
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));
            }
          }


          //----------------------------------This is the Way Point1 load button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X6) && (FingerItem.x < (REDBUTTON_X6 + REDBUTTON_W6))) {
            if ((FingerItem.y > REDBUTTON_Y6) && (FingerItem.y <= (REDBUTTON_Y6 + REDBUTTON_H6))) {
              moudlemode = 2 ;

              canvas.setTextFont(4);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X6, REDBUTTON_Y6);
              canvas.print("✓");
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));



            }
          }

          //----------------------------------This is the Way Point2 Save button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X7) && (FingerItem.x < (REDBUTTON_X7 + REDBUTTON_W7))) {
            if ((FingerItem.y > REDBUTTON_Y7) && (FingerItem.y <= (REDBUTTON_Y7 + REDBUTTON_H7))) {

              moudlemode = 9 ;
              canvas.setTextFont(4);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X7, REDBUTTON_Y7);
              canvas.print("✓");

              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));

            }
          }


          //----------------------------------This is the Way Point2 load button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X8) && (FingerItem.x < (REDBUTTON_X8 + REDBUTTON_W8))) {
            if ((FingerItem.y > REDBUTTON_Y8) && (FingerItem.y <= (REDBUTTON_Y8 + REDBUTTON_H8))) {

              moudlemode = 3 ;
              canvas.setTextFont(4);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X8, REDBUTTON_Y8);
              canvas.print("✓");
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));


            }
          }

          //----------------------------------This is the Way Point3 Save button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X9) && (FingerItem.x < (REDBUTTON_X9 + REDBUTTON_W9))) {
            if ((FingerItem.y > REDBUTTON_Y9) && (FingerItem.y <= (REDBUTTON_Y9 + REDBUTTON_H9))) {
              canvas.setTextFont(4);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X9, REDBUTTON_Y9);
              canvas.print("✓");
              moudlemode = 10 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));

            }
          }


          //----------------------------------This is the Way Point3 load button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X10) && (FingerItem.x < (REDBUTTON_X10 + REDBUTTON_W10))) {
            if ((FingerItem.y > REDBUTTON_Y10) && (FingerItem.y <= (REDBUTTON_Y10 + REDBUTTON_H10))) {
              canvas.setTextFont(4);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X10, REDBUTTON_Y10);
              canvas.print("✓");
              moudlemode = 4 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));



            }
          }


          //----------------------------------This is the Way Point4 Save button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X11) && (FingerItem.x < (REDBUTTON_X11 + REDBUTTON_W11))) {
            if ((FingerItem.y > REDBUTTON_Y11) && (FingerItem.y <= (REDBUTTON_Y11 + REDBUTTON_H11))) {
canvas.setTextFont(4);
              canvas.setTextSize(3);
              canvas.setCursor(REDBUTTON_X11, REDBUTTON_Y11);
              canvas.print("X");
              moudlemode = 11 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));



            }
          }

          //----------------------------------This is the Way Point4 load button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X12) && (FingerItem.x < (REDBUTTON_X12 + REDBUTTON_W12))) {
            if ((FingerItem.y > REDBUTTON_Y12) && (FingerItem.y <= (REDBUTTON_Y12 + REDBUTTON_H12))) {

              moudlemode = 5 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));


            }
          }


          //----------------------------------This is the Way Point5 Save button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X13) && (FingerItem.x < (REDBUTTON_X13 + REDBUTTON_W13))) {
            if ((FingerItem.y > REDBUTTON_Y6) && (FingerItem.y <= (REDBUTTON_Y6 + REDBUTTON_H6))) {
              moudlemode = 12 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));






            }
          }


          //----------------------------------This is the Way Point5 load button--------------------------------------

          if ((FingerItem.x > REDBUTTON_X14) && (FingerItem.x < (REDBUTTON_X14 + REDBUTTON_W14))) {
            if ((FingerItem.y > REDBUTTON_Y14) && (FingerItem.y <= (REDBUTTON_Y14 + REDBUTTON_H14))) {
              moudlemode = 6 ;
              esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &moudlemode, sizeof(moudlemode));;





            }
          }
        }
      }
    }

  }



  if (count_value > 11) {
    count_value = 12;
  }

  fueline = count_value * 29 ;



  canvas.fillRoundRect(136, 332, 348, 60, 10, 0); // fill it all whitish grey first



  canvas.fillRoundRect(136, 332, fueline, 60, 10, 15); // then fill it black




  Serial.print("fueline    :");
  Serial.println(fueline);

  Serial.println("now in settings screen");








}
