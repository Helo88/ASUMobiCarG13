#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PWMServo.h>

#include "Data.h"
#include "Radio.h"
#include "GPS.h"
#include "Compass.h"

PWMServo throttleServo;
PWMServo steeringServo;

/**************************************************/

/**************************************************/

void setup() {

  Wire.begin();

  Serial.begin(9600);

  Serial.println("Starting...");
  
  gps_setup();
  compass_setup();
  radio_setup();

  throttleServo.attach(10);
  steeringServo.attach(9);
  throttleServo.write(90);
  steeringServo.write(90);

  initLocation();
  
  steeringServo.write(50);
  delay(750);
  steeringServo.write(130);
  delay(750);
  steeringServo.write(90);
}

/**************************************************/

void initLocation() {

#define HOME_LOCATION_READINGS 10

  Serial.println("Starting location init...");
  
  unsigned long count = gpsInfo.validCount;
  int numReadings = 0;
  float lat = 0;
  float lon = 0;
  while (numReadings < HOME_LOCATION_READINGS) {
    gps_loop();
    if ( gpsInfo.validCount > count ) {
      lat += gpsInfo.lat;
      lon += gpsInfo.lon;
      Serial.println("Got reading...");
      numReadings++;
      count = gpsInfo.validCount;
    }
  }
 
  float d = (1/(float)HOME_LOCATION_READINGS);
  currentLoc.lat = lat * d;
  currentLoc.lon = lon * d;
  
  homeLoc.lat = currentLoc.lat;
  homeLoc.lon = currentLoc.lon;

  /*******************/
  // carpark
  //currentLoc.lat = 35.620174;
  //currentLoc.lon = 139.614543;
  
  // river
  //targetLoc.lat = 35.615011;
  //targetLoc.lon = 139.612323;

  // shibuya
  //targetLoc.lat = 35.656882;
  //targetLoc.lon = 139.701172;
  /*******************/
  
  char buf[16];
  Serial.print("Home location set as: ");
  dtostrf(homeLoc.lat, 0, 7, buf);
  Serial.print(buf);
  Serial.print(", ");
  dtostrf(homeLoc.lon, 0, 7, buf);
  Serial.println(buf);
  
}

/**************************************************/

void autoControl() {

  if ( tagLoc.lat == 0 ) {
    throttleServo.write(90);
    steeringServo.write(90);
    return;
  }  

  static float autoThrottle = 90;
  int autoSteer = 90;
  
  float turn = bearing - heading;
  while (turn < -180) turn += 360;
  while (turn >  180) turn -= 360;

  autoSteer = map(turn, 180, -180, 0, 180);
  autoSteer = constrain(autoSteer, 40, 140);

  float angleError = abs(turn);

  /*
  // turn and stop
  int t = 95 + 0.4 * angleError;
  //if ( distance < 10 )
  //  t = 95;
  */
  
  // drive to location
  int t = 95 + 2 * distance;
  t = constrain(t, 95, 105);
  
  float d = t - autoThrottle;
  d = constrain(d, -0.01, 0.01);
  autoThrottle += d;
  
  autoThrottle = constrain(t, 95, 105);
  
  throttleServo.write(autoThrottle);
  steeringServo.write(autoSteer);
}

/**************************************************/

void manualControl() {
  int s = map(data.axis4, 0, 255, 50, 130);
  int t = map(data.axis1, 0, 255, 40, 140);
  throttleServo.write(t);
  steeringServo.write(s);
}

/**************************************************/

void loop() { // run over and over

  radio_loop();
  gps_loop();
  compass_loop();

  static bool wasAuto = false;
  bool isAuto = (data.switches & 0x01);
  if ( !wasAuto && isAuto ) 
    Serial.println("Switched to auto");
  else if ( wasAuto && !isAuto )
    Serial.println("Switched to manual");

  wasAuto = isAuto;

  if (data.switches & 0x01)
    autoControl();
  else
    manualControl();
    
}


