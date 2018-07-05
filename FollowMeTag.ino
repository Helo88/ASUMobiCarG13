#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"

const uint64_t pipeOut = 0xE8E8F0F0E1LL;

RF24 radio(9, 10);

// The sizeof this struct should not exceed 32 bytes
struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte switches;
  float lat;
  float lon;
};

MyData data;

#define F(string_literal) string_literal

static const int RXPin = 2, TXPin = 4;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);

char buffer[32];
  
void displayln(const char* format, ...)
{  
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  
  Serial.print(buffer);
}

void setup()
{
  Serial.begin(GPSBaud);
  //ss.begin(GPSBaud);

  printf_begin();
  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);

  radio.openWritingPipe(pipeOut);
  
  //radio.printDetails();

  memset(&data, 0, sizeof(MyData));
  data.throttle = 128;
  data.yaw = 128;
  data.pitch = 128;
  data.roll = 128;
  radio.write(&data, sizeof(MyData));
  
  displayln("Starting...\n");
  delay(200);
}

unsigned long lastSend = 0;

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  boolean haveGPSInfo = false;
  while (Serial.available() > 0) {
    byte b = Serial.read();
    //Serial.print((char)b);
    if (gps.encode(b)) {
      haveGPSInfo = true;
      //Serial.println();
      //Serial.println(gps.failedChecksum());
      //Serial.println();
    }
  }
  
  if ( haveGPSInfo ) {
    displayInfo();
    if (gps.location.isValid()) {
      data.switches |= 0x1;
      data.lat = gps.location.lat();
      data.lon = gps.location.lng();
    }
  }
  
  unsigned long now = millis();
  if (now > 5000 && gps.charsProcessed() < 10)
  {
    displayln("No GPS detected.");
    while(true);
  }
  
  //if ( now - lastSend > 100 ) {    
    radio.write(&data, sizeof(MyData));
  //  lastSend = now;
  //}

}

unsigned long readCount = 0;

void displayInfo()
{
  readCount++;
  
  char buf[16];

  if (gps.time.isValid())
    displayln("%02d:%02d:%02d ", gps.time.hour(), gps.time.minute(), gps.time.second());
  
  if (gps.location.isValid())
  {    
    dtostrf(gps.location.lat(), 0, 7, buf);    
    displayln(" Lat: %s", buf);
    dtostrf(gps.location.lng(), 0, 7, buf);        
    displayln(" Lon: %s", buf);
    data.switches |= 0x1;
    data.lat = gps.location.lat();
    data.lon = gps.location.lng();
  }
  
  //dtostrf(gps.altitude.meters(), 0, 1, buf);    
  //displayln("%s m", buf);
  
  if ( gps.satellites.isValid() )
    displayln(" Sats: %d", gps.satellites.value());
    
  displayln(" Reads: %d", readCount);
  
  Serial.println();
}
