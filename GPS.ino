void getgps() {

  smartDelay(50);
  float sensorValue = analogRead(35);
  float voltage = sensorValue * (7.2 / 4095.0);

  if (gps.encode(ss.read()))



    if (ss.overflow()) {
      ss.read();
      Serial.println("SoftwareSerial overflow! GPS LOOP");

    }


  float distanceKmToLondon =
    (float)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      HOMELAT1,
      HOMELON1) / 1000.00;

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      HOMELAT1,
      HOMELON1);




  DEG2 = courseToLondon;

  GPSC = gps.course.deg();

  

  BME280Readings.MPH1 = gps.speed.mph();
  BME280Readings.ALT1 = gps.altitude.feet();
  BME280Readings.DIS2 = distanceKmToLondon;
  BME280Readings.RTH = DEG2 - GPSC;
  BME280Readings.SATS = gps.satellites.value();
  BME280Readings.FlowCounter = FlowCounter;
  BME280Readings.voltage = voltage;
  BME280Readings.datatx = looptx;




  Serial.println(voltage);





  Serial.print("HDOP       Fix Age=");
  Serial.print(gps.hdop.age());
  Serial.print("ms raw=");
  Serial.print(gps.hdop.value());
  Serial.print(" hdop=");
  Serial.println(gps.hdop.hdop());


  Serial.print("gps.altitude.feet()");

  Serial.println(gps.altitude.feet());

  Serial.print("courseToLondon");

  Serial.println(courseToLondon);

  Serial.print("distanceKmToLondon");
  
  Serial.println(distanceKmToLondon);

  Serial.print("gps.satellites.value()");

  Serial.println(gps.satellites.value());

  Serial.print("gps.course.deg()");

  Serial.println(gps.course.deg());

  Serial.print("gps.speed.mph()");

  Serial.println(gps.speed.mph());


  if (gps.charsProcessed() < 10)
    Serial.println(F("WARNING: No GPS data.  Check wiring."));



}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
