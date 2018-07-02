int m1a = 2;
int m1b = 3;
int m2a = 4;  //  
int m2b = 5;
int en1 =6;
int en2 = 9;
char val;
#define signalPin1 11 // righ
#define signalPin2 13 // left

void setup() 
{  
pinMode(en1, OUTPUT);
pinMode(en2, OUTPUT);
pinMode(m1a, OUTPUT);  // Digital pin 10 set as output Pin
pinMode(m1b, OUTPUT);  // Digital pin 11 set as output Pin
pinMode(m2a, OUTPUT);  // Digital pin 12 set as output Pin
pinMode(m2b, OUTPUT);  // Digital pin 13 set as output Pin
pinMode(signalPin1, INPUT);
pinMode(signalPin2, INPUT); 
Serial.begin(9600);
}

void loop()
{
while (Serial.available() > 0)
  {
val = Serial.read();
Serial.println(val);
  }

if(val == 'F') // Forward
    {
   
digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);

digitalWrite(en1, HIGH);

digitalWrite(en2, HIGH);

    }
else if(val == 'B') // Backward
    {
  
digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);

digitalWrite(en1, HIGH);

digitalWrite(en2, HIGH);

    }

else if(val == 'L') //Left
    {
digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);

digitalWrite(en1, HIGH);

digitalWrite(en2, HIGH);

    }

else if(val == 'R') //Right
    {
digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);

digitalWrite(en1, HIGH);

digitalWrite(en2, HIGH);

    }

else if(val == 'S') //Stop
    {
digitalWrite(m1a, LOW);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, LOW);

digitalWrite(en1, LOW);

digitalWrite(en2, LOW);

    }
else if (val == 'I') //forward right
    {

digitalWrite(m1a, HIGH); 

digitalWrite(m1b, LOW); 

digitalWrite(m2a, HIGH);

digitalWrite(m2b, LOW);

analogWrite(en1, 100);

analogWrite(en2, 255);

    }

else if( val == 'G')  //forward left
 {
digitalWrite(m1a, LOW); 

digitalWrite(m1b, HIGH); 

digitalWrite(m2a, LOW );

digitalWrite(m2b,HIGH);

analogWrite(en1, 100);

analogWrite(en2, 255);

}

else if(val == 'H') //backward right
    {
digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);

analogWrite(en1, 255);

analogWrite(en2, 100);

    }
else if(val == 'j') //Backward Left
    {
digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);

analogWrite(en1, 255);

analogWrite(en2, 100);

    }
else if (val=='W') //linefollower on
{
  while(true)
  {
  if(HIGH == digitalRead(signalPin1)&& HIGH == digitalRead(signalPin2)){
 Serial.println("black"); 
 digitalWrite(m1a, LOW);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, LOW);

digitalWrite(en1, LOW);

digitalWrite(en2, LOW);

 }
 delay(1000); 
 if(HIGH == digitalRead(signalPin1)&& LOW == digitalRead(signalPin2)){
   digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);

digitalWrite(en1, HIGH);

digitalWrite(en2, HIGH);
 }
 delay(1000); 
 if(LOW == digitalRead(signalPin1)&& LOW == digitalRead(signalPin2)){
  Serial.println("white");
  digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW); 

digitalWrite(en1, HIGH);

digitalWrite(en2, HIGH);
 
 }
 delay(1000); 
 if(LOW == digitalRead(signalPin1)&& HIGH == digitalRead(signalPin2)){
   digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);

digitalWrite(en1, HIGH);

digitalWrite(en2, HIGH);

 }
  delay(1000);
}

}

}

