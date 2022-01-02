void gpsloop() {

  Serial.print("SATS  ");
  Serial.println(incomingSATS);
  Serial.print("DIS2  ");
  Serial.println(incomingDIS2);
  Serial.print("ALT1  ");
  Serial.println(incomingALT1);
  Serial.print("MPH1  ");
  Serial.println(incomingMPH1);
  Serial.print("pulses  ");
  Serial.println(pulses);

  Serial.println(incomingReadings.a) ;
  Serial.println(incomingReadings.b) ;
  Serial.println(incomingReadings.d) ;
  Serial.println(incomingReadings.d) ;
  Serial.println(incomingReadings.f) ;
  Serial.println(incomingReadings.g) ;
  Serial.println(incomingReadings.h) ;



  //------------------ No of satalities in view -----------------------------------------

  canvas.setTextFont(4);
  canvas.setTextSize(1);
  canvas.setCursor(354, 71);
  canvas.print(incomingSATS);


  //------------------ Distance to home --------------------------------------------------

  canvas.setTextFont(4);
  canvas.setTextSize(2);
  canvas.setCursor(318, 210);
  canvas.println(incomingDIS2);

  //------------------ Altutude in feet ------------------------------------------------

  canvas.setTextFont(4);
  canvas.setTextSize(2);
  canvas.setCursor(80, 210);
  canvas.println(incomingALT1);




  //------------------ MPH --------------------------------------------------------------

  canvas.setTextFont(4);
  canvas.setTextSize(2);
  canvas.setCursor(135, 450);
  canvas.println(incomingMPH1);

  


}
