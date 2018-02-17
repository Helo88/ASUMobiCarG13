int input = A0; 
int reading ; 
float temp ; 

void setup() {
  pinMode(input , INPUT) ; 
  Serial.begin(9600);

}

void loop() {
  reading  = analogRead(input);
  temp = (reading * (5.0/1024))*100 - 2.5 ; 
  Serial.println(temp);
  //Serial.println(reading);
  delay(500) ;

}
