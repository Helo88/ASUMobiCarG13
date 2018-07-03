#include <Wire.h> //I2C Arduino Library
#include <LiquidCrystal.h> //LCD Library
#define addr 0x1E //I2C Address for The HMC5883

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup(){
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.print("HMC5833L COMPASS SENSOR BEGIN");
  Serial.println();
  Wire.begin();
  
  
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
}


void loop(){
  
  int x,y,z; //triple axis data

  //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
 
 //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //MSB  x 
    x |= Wire.read(); //LSB  x
    z = Wire.read()<<8; //MSB  z
    z |= Wire.read(); //LSB z
    y = Wire.read()<<8; //MSB y
    y |= Wire.read(); //LSB y
  }
  
  // Show Values
  lcd.clear();
  lcd.print("X:");
  lcd.setCursor(2, 0);
  lcd.print(x);
  lcd.setCursor(8, 0);
  lcd.print("Y:");
  lcd.setCursor(10, 0);
  lcd.print(y);
  lcd.setCursor(0, 1);
  lcd.print("Z: ");
  lcd.setCursor(2, 1);
  lcd.print(z);
  
  Serial.print("X Value: ");
  Serial.println(x);
  Serial.print("Y Value: ");
  Serial.println(y);
  Serial.print("Z Value: ");
  Serial.println(z);
  Serial.println();

  delay(1000);
}

