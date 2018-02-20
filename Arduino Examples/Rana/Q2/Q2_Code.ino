void setup(){
}
void loop(){

for ( int i=4 ;i<=7 ; i++){

digitalWrite(i, HIGH);
delay(1000);
digitalWrite(i, LOW);
delay(1000);

}
for(int i=7; i>5 ; i--){

digitalWrite(i-1, HIGH);
delay(1000);
digitalWrite(i-1, LOW);
delay(1000);

}
}
