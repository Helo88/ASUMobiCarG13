int MicPin=A2; 
int LED =4;


void setup() 
{
  pinMode (MicPin,INPUT);
  pinMode (LED,OUTPUT);
  
  // put your setup code here, to run once:

}

void loop()
{
int  MicValue1 = analogRead(MicPin); // read pin value 
  Serial.println(MicValue1);
  delay(1); 
int  MicValue2 = analogRead(MicPin);
  Serial.println(MicValue2);
  if (MicValue1 - MicValue2 > 1 || MicValue2 - MicValue1 > 1)
  { digitalWrite(LED, HIGH); //  turn lights on 
  
  }
  else{
  digitalWrite(LED, LOW); } 
    delay(120);
}
    
     
  // put your main code here, to run repeatedly:

