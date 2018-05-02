int m1a = 2;
int m1b = 3;
int m2a = 4;  //  
int m2b = 5;
int en1 =6;
int en2 = 9;
int Si =0; //speed
int state=0;
//sensor
int  sensorLR=10;
int sensorCR=11;
int sensorRR=12;

void setup(){
pinMode(en1, OUTPUT);
pinMode(en2, OUTPUT);
pinMode(m1a, OUTPUT); 
pinMode(m1b, OUTPUT);  
pinMode(m2a, OUTPUT); 
pinMode(m2b, OUTPUT); 
 //sensor
 pinMode (sensorLR ,INPUT);
 pinMode (sensorCR ,INPUT);
 pinMode (sensorRR ,INPUT); 
 }
void Right( int s)
{
digitalWrite(m1a, LOW);
digitalWrite(m1b, LOW);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);
analogWrite(en1, s);
analogWrite(en2, s);
}
void Left (int s){
  
digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, LOW);
digitalWrite(m2b, LOW);
analogWrite(en1, s);
analogWrite(en2, s);
}

void Backward( int s)
{
digitalWrite(m1a, HIGH);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, HIGH);
analogWrite(en1, s);
analogWrite(en2,s);
 }
   void Forward (int s )
   {
digitalWrite(m1a, LOW);
digitalWrite(m1b, HIGH);
digitalWrite(m2a, HIGH);
digitalWrite(m2b, LOW);
analogWrite(en1, s);
analogWrite(en2, s);
    }
    void Stop()
    {
  digitalWrite(m1a,LOW);
digitalWrite(m1b, LOW);
digitalWrite(m2a, LOW);
digitalWrite(m2b, LOW);
digitalWrite(en1, LOW);
digitalWrite(en2, LOW);
    }
 void loop(){
   if ((digitalRead(sensorLR))&&(digitalRead(sensorCR))&&(digitalRead(sensorRR)))
   {
    Si=150;
    Forward(Si);
   }
  else if (!(digitalRead(sensorLR))&&!(digitalRead(sensorCR))&&(digitalRead(sensorRR)))
   {
    Si=145;
    Right(Si); 
    state=1;
   }
    if (!(digitalRead(sensorLR))&&(digitalRead(sensorCR))&&!(digitalRead(sensorRR)))
    {
      Si=90;
    Forward(Si);
    }
   else if ((digitalRead(sensorLR))&&!(digitalRead(sensorCR))&&!(digitalRead(sensorRR)))
    {
         Si=145;
    Left(Si);
    state=2;
    }
   else if ((digitalRead(sensorLR))&&(digitalRead(sensorCR))&&!(digitalRead(sensorRR)))
    {
       Si=90;
      Left(Si);
      state=2;
    }
    else if (!(digitalRead(sensorLR))&&(digitalRead(sensorCR))&&(digitalRead(sensorRR)))
     {
      Si=90;
      Right(Si);
      state=1;
     }
   else  if (!(digitalRead(sensorLR))&&!(digitalRead(sensorCR))&&!(digitalRead(sensorRR))&&state==1)
     {
      //Stop();
      Si=170;
      Right(Si);
      
     }
     else  if (!(digitalRead(sensorLR))&&!(digitalRead(sensorCR))&&!(digitalRead(sensorRR))&&state==2)
     {
      //Stop();
      Si=170;
      Left(Si);
      
     }
 }


