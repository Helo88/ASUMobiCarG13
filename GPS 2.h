
struct geoloc {
  float lat;
  float lon;
};

geoloc currentLoc;
geoloc homeLoc;
geoloc tagLoc;

void gps_setup() {
  Serial.println("GPS...");
  memset(&gpsInfo, 0, sizeof(GPSInfo));
}

unsigned long failures = 0;

void displayGPSInfo()
{
  Serial.print("Reads: ");
  Serial.print(gpsInfo.readCount);
  Serial.print("   Valid: ");
  Serial.print(gpsInfo.validCount);

  Serial.print("   Date: ");
  Serial.print(gpsInfo.year);
  Serial.print("/");
  Serial.print(gpsInfo.month);
  Serial.print("/");
  Serial.print(gpsInfo.day);

  Serial.print("   Time: ");
  Serial.print(gpsInfo.hour);
  Serial.print(":");
  Serial.print(gpsInfo.minute);
  Serial.print(":");
  Serial.print(gpsInfo.second);

  char buf[16];

  Serial.print("   Location: ");       
  dtostrf(gpsInfo.lat, 0, 7, buf);
  Serial.print(buf);
  Serial.print(", ");
  dtostrf(gpsInfo.lon, 0, 7, buf);
  Serial.print(buf);
  
  Serial.print("   Failures: ");
  Serial.print(failures);

  Serial.println();
}

float readLongFromI2C() {
  unsigned long tmp = 0;

  for (int i = 0; i < 4; i++) {
    unsigned long tmp2 = Wire.read();
    tmp |= tmp2 << (i*8);
  }
  
  return tmp;
}

float readFloatFromI2C() {
  
  float f = 0;
  byte* p = (byte*)&f;

  for (int i = 0; i < 4; i++) 
    p[i] = Wire.read();
  
  return f;
}

void gps_loop() {
  static unsigned long lastGPSRead = 0;
  unsigned long now = millis();
  if ( now - lastGPSRead > 1000 ) {
    lastGPSRead = now;

    static int delayTime = 5;

    Wire.beginTransmission(GPS_I2C_ADDRESS);
    Wire.write(GPS_COUNT);
    Wire.endTransmission();
    delay(delayTime);

    Wire.requestFrom(GPS_I2C_ADDRESS, 8);
    if (Wire.available() >= 8) {
      gpsInfo.readCount = readLongFromI2C();
      gpsInfo.validCount = readLongFromI2C();
    }
    else 
      failures++;

    Wire.beginTransmission(GPS_I2C_ADDRESS);
    Wire.write(GPS_DATE);
    Wire.endTransmission();
    delay(delayTime);

    Wire.requestFrom(GPS_I2C_ADDRESS, 4);
    if (Wire.available() >= 4) {
      gpsInfo.year = Wire.read();
      gpsInfo.year |= Wire.read() << 8;
      gpsInfo.month = Wire.read();
      gpsInfo.day = Wire.read();
    }
    else 
      failures++;

    Wire.beginTransmission(GPS_I2C_ADDRESS);
    Wire.write(GPS_TIME);
    Wire.endTransmission();
    delay(delayTime);

    Wire.requestFrom(GPS_I2C_ADDRESS, 3);
    if (Wire.available() >= 3) {
      gpsInfo.hour = Wire.read();
      gpsInfo.minute = Wire.read();
      gpsInfo.second = Wire.read();
    }
    else 
      failures++;

    Wire.beginTransmission(GPS_I2C_ADDRESS);
    Wire.write(GPS_LOCATION);
    Wire.endTransmission();
    delay(delayTime);

    Wire.requestFrom(GPS_I2C_ADDRESS, 8);
    if (Wire.available() >= 8) {
      gpsInfo.lat = readFloatFromI2C();
      gpsInfo.lon = readFloatFromI2C();
    }
    else 
      failures++;

    currentLoc.lat = gpsInfo.lat;
    currentLoc.lon = gpsInfo.lon;

    displayGPSInfo();
  }
}

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

float geoDistance(struct geoloc &a, struct geoloc &b) {
  const float R = 6371000; // km
  float p1 = a.lat * DEGTORAD;
  float p2 = b.lat * DEGTORAD;
  float dp = (b.lat-a.lat) * DEGTORAD;
  float dl = (b.lon-a.lon) * DEGTORAD;

  float x = sin(dp/2) * sin(dp/2) +
    cos(p1) * cos(p2) *
    sin(dl/2) * sin(dl/2);
  float y = 2 * atan2(sqrt(x), sqrt(1-x));

  return R * y;
}

float geoBearing(struct geoloc &a, struct geoloc &b) {
  float y = sin(b.lon-a.lon) * cos(b.lat);
  float x = cos(a.lat)*sin(b.lat) -
    sin(a.lat)*cos(b.lat)*cos(b.lon-a.lon);
  return atan2(y, x) * RADTODEG;
}





