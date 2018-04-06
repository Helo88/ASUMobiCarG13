int m1a = 2;
int m1b = 3;
int m2a = 4;  //  
int m2b = 5;
int en1 =6;
int en2 = 9;
char val;

//Ultrasonic

int trigPin = 7;
int echoPin = 8;
long duration ;
int distance ;

void Forward()
{
  digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);
digitalWrite(en1, HIGH);
digitalWrite(en2, HIGH);
}
void Backward (){
  
digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);
digitalWrite(en1, HIGH);
digitalWrite(en2, HIGH);
}

void Left()
{
digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);
digitalWrite(en1, HIGH);
digitalWrite(en2, HIGH);
 }
   void Right ()
   {
digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);
digitalWrite(en1, HIGH);
digitalWrite(en2, HIGH);
    }
void Forward_right()
{
 digitalWrite(m1a, HIGH); 
digitalWrite(m1b, LOW); 
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);
analogWrite(en1, 100);
analogWrite(en2, 255);
}
void Forward_left(){
  digitalWrite(m1a, LOW); 
digitalWrite(m1b, HIGH); 
digitalWrite(m2a, LOW );
digitalWrite(m2b,HIGH);
analogWrite(en1, 100);
analogWrite(en2, 255);
} 
void Backward_right()
{
 digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);
analogWrite(en1, 255);
analogWrite(en2, 100); 
}
void Backward_left(){
  digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);
analogWrite(en1, 255);
analogWrite(en2, 100);
}
void Stop(){
  digitalWrite(m1a, LOW);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, LOW);
digitalWrite(en1, LOW);
digitalWrite(en2, LOW);

}
void setup(){
pinMode(en1, OUTPUT);
pinMode(en2, OUTPUT);
pinMode(m1a, OUTPUT);  
pinMode(m1b, OUTPUT);  
pinMode(m2a, OUTPUT); 
pinMode(m2b, OUTPUT); 
pinMode (trigPin,OUTPUT);
pinMode(echoPin,INPUT);                     
Serial.begin(9600);
}
void loop(){
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
   digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

if(Serial.available() > 0)
  {
      val= Serial.read();

    if(val == 'F' && distance > 20)
    {
      Forward();
    }
    else if(val == 'F' )
    {
      while(distance <= 20)
      {
         Right ();
        delay(500);
        digitalWrite(trigPin , LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin , HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin , LOW);
      duration = pulseIn(echoPin, HIGH);
     distance = (duration/2) / 29.1; 
      }
    }
 else if(val == 'B')
    {
      Backward();
    }
    else if(val == 'R')
    {
      Right();
    }
    else if(val == 'L')
    {
      Left();
    }

    else if(val == 'G')
    {
      Forward_left();
    }

    else if(val == 'I')
    {
      Forward_right();
    }

    else if(val == 'H')
    {
      Backward_left();
    }
    
    else if(val == 'J')
    {
      Backward_right();
    }
    else
    {
      Stop();
    }
  }
  
}















  

