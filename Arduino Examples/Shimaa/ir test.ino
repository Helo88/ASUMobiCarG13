void setup() {
  // put your setup code here, to run once:
pinMode (6,INPUT);
;pinMode (7,INPUT)

void loop() {
  // put your main code here, to run repeatedly:
int ls = digitalRead(6);
int ls = digitalRead(7);.
if ((ls==LOW) && (rs == LOW))
//FORWARD
if ((ls==LOW) && (rs == HIGH))
//URN RIGHR

if ((ls==HIGH) && (rs == LOW))
// TURN LEFT
if ((ls==HIGH) && (rs == HIGH))
//STOP
}
