
float heading = 0;
float bearing = 0;
float distance = 0;

void compass_setup() {
  // instruct chip we want to read it continuously (TODO: REPLACE WITH BETTER POWER SAVING MODE)
  Wire.beginTransmission(0x1e); // transmit to device 0x1e
  Wire.write(0x02); // sends one byte (select register to write to - MODE)
  Wire.write(0x00); // sends one byte (configure mode - continuous)
  Wire.endTransmission();
}

void displayCompassInfo()
{
  static unsigned long lastCompassDisplay = 0;
  unsigned long now = millis();
  if ( now - lastCompassDisplay > 1000 ) {
    lastCompassDisplay = now;
    Serial.print("Heading: ");
    Serial.print(heading);
    Serial.print("  Bearing: ");
    Serial.print(bearing);
    Serial.print("  Distance: ");
    Serial.print(distance);
    Serial.println();
  }
}

void compass_loop() {
  static unsigned long lastCompassRead = 0;
  unsigned long now = millis();
  if ( now - lastCompassRead > 50 ) {
    lastCompassRead = now;
    int x,y,z;

    Wire.beginTransmission(0x1e);
    Wire.write(0x03); //select register 3, X MSB register - to start read from
    Wire.endTransmission();
    //Read data from each axis, 2 registers per axis

    Wire.requestFrom(0x1e, 6);
    if (6 <= Wire.available()) {
      x = Wire.read()<<8; //X msb
      x |= Wire.read(); //X lsb
      z = Wire.read()<<8; //Z msb
      z |= Wire.read(); //Z lsb
      y = Wire.read()<<8; //Y msb
      y |= Wire.read(); //Y lsb

      heading = atan2(-x, -y) * RADTODEG;
      heading += 7.13333; // declination
      while (heading < -180) heading += 360;
      while (heading >  180) heading -= 360;

      distance = geoDistance(currentLoc, tagLoc);
      bearing = geoBearing(currentLoc, tagLoc);

      displayCompassInfo();
    }
  }
}

