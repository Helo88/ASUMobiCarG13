//motorların tanımları
#include <AFMotor.h>
AF_DCMotor Sol_On_Motor(4);
AF_DCMotor Sag_On_Motor(3);
AF_DCMotor Sol_Arka_Motor(1);
AF_DCMotor Sag_Arka_Motor(2);
#include <Ultrasonic.h>
 
Ultrasonic ultrasonic_arka(40,41),ultrasonic_sol_arka(38,39),ultrasonic_sol_on(36,37),ultrasonic_on(34,35);
// ultrasomik sensörlerin tanımlamamalrı
 
#define Sol 0 //sol yön komutu
#define Sag 1 //sağ yön komutu
#define Ileri 2 //ileri yön komutu
#define Geri 3 //geri yön komutu
#define minimum_limit 15 //Arabanın genişliği (cm)
#define minimum_limit1 28 //arabanın uzunluğu (cm)
 
byte park_durumu = 0;
int sinyalpin = 21;
volatile int val;
 
int sayac = 0;
int guncel_durum = 0;
int onceki_durum = 0;
 
void say(int saydir)
{
for (int i = 0 ; i <= saydir; i+1)
{
val = digitalRead(sinyalpin);
if (val == LOW) {
 
guncel_durum = 0;
}
else {
 
guncel_durum = 1;
}
 
if(guncel_durum != onceki_durum)
{
if(guncel_durum == 1)
{
sayac = sayac + 1;
Serial.println(sayac);
i = i+1;
}
else
{
i = i ;
}
 
onceki_durum = guncel_durum;
 
}
if (i == saydir)
{
 
Sol_On_Motor.run(RELEASE);
Sag_On_Motor.run(RELEASE);
Sol_Arka_Motor.run(RELEASE);
Sag_Arka_Motor.run(RELEASE);
 
}
 
}
 
}
 
void motor_pinSetup()
{
 
Sol_On_Motor.run(RELEASE);
Sag_On_Motor.run(RELEASE);
Sol_Arka_Motor.run(RELEASE);
Sag_Arka_Motor.run(RELEASE);
}
 
// Hareket fonksiyonları
void Robot_Hareket(byte motor, byte spd)
{
if (motor == Ileri)
{
Sol_On_Motor.setSpeed(spd);
Sag_On_Motor.setSpeed(spd);
Sol_Arka_Motor.setSpeed(spd);
Sag_Arka_Motor.setSpeed(spd);
Sol_On_Motor.run(FORWARD);
Sag_On_Motor.run(FORWARD);
Sol_Arka_Motor.run(FORWARD);
Sag_Arka_Motor.run(FORWARD);
 
}
if (motor == Geri)
{
Sol_On_Motor.setSpeed(spd);
Sag_On_Motor.setSpeed(spd);
Sol_Arka_Motor.setSpeed(spd);
Sag_Arka_Motor.setSpeed(spd);
Sol_On_Motor.run(BACKWARD);
Sag_On_Motor.run(BACKWARD);
Sol_Arka_Motor.run(BACKWARD);
Sag_Arka_Motor.run(BACKWARD);
 
}
if (motor == Sol)
{
Sol_On_Motor.setSpeed(spd);
Sag_On_Motor.setSpeed(spd);
Sol_Arka_Motor.setSpeed(spd);
Sag_Arka_Motor.setSpeed(spd);
Sol_On_Motor.run(BACKWARD);
Sag_On_Motor.run(FORWARD);
Sol_Arka_Motor.run(BACKWARD);
Sag_Arka_Motor.run(FORWARD);
 
}
 
if (motor == Sag)
{
Sol_On_Motor.setSpeed(spd);
Sag_On_Motor.setSpeed(spd);
Sol_Arka_Motor.setSpeed(spd);
Sag_Arka_Motor.setSpeed(spd);
Sol_On_Motor.run(FORWARD);
Sag_On_Motor.run(BACKWARD);
Sol_Arka_Motor.run(FORWARD);
Sag_Arka_Motor.run(BACKWARD);
 
}
 
}
 
void Robot_Dur()
{
Sol_On_Motor.run(RELEASE);
Sag_On_Motor.run(RELEASE);
Sol_Arka_Motor.run(RELEASE);
Sag_Arka_Motor.run(RELEASE);
}
 
// Park yeri araması
bool Park_Yeri_Kontrol()
{
 
long on_Sensor = ultrasonic_on.Ranging(CM);
long sag_Sensor = ultrasonic_sol_on.Ranging(CM);
long sag_arka_Sensor =ultrasonic_sol_arka.Ranging(CM);
 
if( (sag_Sensor <= minimum_limit)&&(sag_arka_Sensor <= minimum_limit)&&(park_durumu == 0))
{
Robot_Hareket(Ileri, 100);
park_durumu = 1; Serial.println(park_durumu);
}
 
if((sag_Sensor > minimum_limit)&&(sag_Sensor < minimum_limit1)&&(sag_arka_Sensor > minimum_limit)&&(sag_arka_Sensor < minimum_limit1)&&(park_durumu == 1))
{
Robot_Hareket(Ileri, 100);
park_durumu = 2;Serial.println(park_durumu);
}
 
if((sag_Sensor >= minimum_limit1)&&(sag_arka_Sensor >= minimum_limit1)&&(park_durumu == 1))
{
/* Dik Park Etme Kararı */
Robot_Dur() ;
delay(500);
park_durumu = 10;Serial.println(park_durumu);
}
 
if((sag_Sensor <= minimum_limit)&&(sag_arka_Sensor <= minimum_limit)&&(park_durumu == 2))
{
/* Paralel Park Etme Kararı */
park_durumu = 3; Serial.println(park_durumu);
}
 
return park_durumu;
}
 
void Park_bul()
{
Park_Yeri_Kontrol();
if(park_durumu == 3 )
{
Robot_Dur();Serial.println(park_durumu);
delay(400);
park_durumu = 4;
}
if(park_durumu == 4 )
{
 
Robot_Hareket(Geri,120);
say(18);
Robot_Dur();Serial.println(park_durumu);
delay(500);
Robot_Hareket(Sag,150);
say(9);
Robot_Dur();
delay(500);
park_durumu = 5;
}
if(park_durumu == 5)
{
 
Robot_Hareket(Geri,120);
long arka_Sensor = ultrasonic_arka.Ranging(CM);Serial.println(arka_Sensor);
 
if(arka_Sensor>0 && arka_Sensor <= 13)
{
Robot_Dur();
delay(400);
park_durumu = 6;
}
return arka_Sensor;
}
 
if(park_durumu == 6)
{
Robot_Hareket(Sol,150);
long sag_Sensor = ultrasonic_sol_on.Ranging(CM); Serial.println(sag_Sensor);
long sag_arka_Sensor = ultrasonic_sol_arka.Ranging(CM); Serial.println(sag_arka_Sensor);
 
if(sag_Sensor == sag_arka_Sensor)
{
Robot_Dur();
park_durumu = 7;
}
 
return sag_Sensor,sag_arka_Sensor;
}
if(park_durumu == 7)
{
long on_Sensor = ultrasonic_on.Ranging(CM);
 
if(on_Sensor<=6)
{
Robot_Dur();
park_durumu = 8;
}
else
{
Robot_Hareket(Ileri,100);
}
return on_Sensor;
}
if (park_durumu ==10)
{
 
Robot_Hareket(Sol,180);
say(14);
Robot_Dur();
delay(500);
park_durumu = 7;
 
}
 
}
 
void setup()
{
Serial.begin(9600);
attachInterrupt(5, say, CHANGE);
pinMode (sinyalpin, INPUT) ;
 
motor_pinSetup();
}
 
void loop()
{
Park_bul();
}
