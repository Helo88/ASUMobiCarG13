#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 2, TXPin = 4;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void gps_setup() {
  memset(&gpsInfo, 0, sizeof(GPSInfo));
  ss.begin(GPSBaud);
}

bool gps_loop() {
  boolean haveGPSInfo = false;
  while (ss.available() > 0) {
    if (gps.encode(ss.read()))
      haveGPSInfo = true;
  }

  if ( haveGPSInfo ) {
    storeGPSInfo();
    displayGPSInfo();
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected.");
    while(true);
  }
  
  return haveGPSInfo;
}

void storeGPSInfo() {
  gpsInfo.readCount++;
  if (gps.date.isValid()) {
    gpsInfo.year = gps.date.year();
    gpsInfo.month = gps.date.month();
    gpsInfo.day = gps.date.day();
  }
  if (gps.time.isValid()) {
    gpsInfo.hour = gps.time.hour();
    gpsInfo.minute = gps.time.minute();
    gpsInfo.second = gps.time.second();
  }
  if (gps.location.isValid()) {
    gpsInfo.lat = gps.location.lat();
    gpsInfo.lon = gps.location.lng();
    gpsInfo.validCount++;
  }
}

void displayGPSInfo()
{
  Serial.print("Reads: ");
  Serial.print(gpsInfo.readCount);
  Serial.print("   Valid: ");
  Serial.print(gpsInfo.validCount);

  if (gps.date.isValid())
  {
    Serial.print("   Date: ");
    Serial.print(gpsInfo.year);
    Serial.print("/");
    Serial.print(gpsInfo.month);
    Serial.print("/");
    Serial.print(gpsInfo.day);
  }

  if (gps.time.isValid())
  {
    Serial.print("   Time: ");
    Serial.print(gpsInfo.hour);
    Serial.print(":");
    Serial.print(gpsInfo.minute);
    Serial.print(":");
    Serial.print(gpsInfo.second);
  }

  if (gps.location.isValid())
  { 
    char buf[16];

    Serial.print("   Location: ");       
    dtostrf(gpsInfo.lat, 0, 7, buf);
    Serial.print(buf);
    Serial.print(", ");
    dtostrf(gpsInfo.lon, 0, 7, buf);
    Serial.print(buf);
  }

  Serial.println();
}

