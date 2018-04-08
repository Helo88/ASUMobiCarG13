const byte Sensor=0;
float voltage,degree;

void setup() {
  // put your setup code here, to run once:
analogReference (INTERNAL);
Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
voltage = analogRead (Sensor);
voltage = voltage * 1100 / 1024;
degree = voltage / 10;

Serial.print(degree);

delay (1000);
}
