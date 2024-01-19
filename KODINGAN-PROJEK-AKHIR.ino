#define BLYNK_TEMPLATE_ID "Nama template id blynk"
#define BLYNK_TEMPLATE_NAME "Isi Template Name"
#define BLYNK_AUTH_TOKEN "blnyk token"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Nama hostpot untuk menghubungkan boardnya";
char pass[] = "Sandi dari hostspotnya";
BlynkTimer timer;

#include<ESP32Servo.h>

const int TrigPin1 = 14; // Ultrasonic Trigpin di 14
const int EchoPin1 = 12; // Ultrasonic Echopin di 12
const int TrigPin2 = 13; // Ultrasonic ke 2 Trigpin di 13
const int EchoPin2 = 5;// Ultrasonic ke 2 Echopin di 14, Ultrasonic ke 2 digunakan untuk mendeteksi volume sampah
unsigned int duration1;
unsigned int jarak1 ;
unsigned int jarak2 ;
unsigned int duration2;


int binLevel = 0;
double x0,x1;
Servo myservo1 ;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass,"blynk.cloud",8080);
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  myservo1.attach(17); //Pin servonya 
  myservo1.write(0);
  delay(2000);
}

void Ultrasonic1() {
  digitalWrite(TrigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin1, LOW);
duration1 = pulseIn(EchoPin1, HIGH);
jarak1 = (duration1/2)/28.5; // Rumus jaraknya
Serial.print("jaraknya: ");
Serial.print(jarak1);
Serial.println("cm");
if (jarak1 <= 25){
  myservo1.write(0);
  delay(3000);
  Blynk.virtualWrite("Your Virtual Pin");
}
else{
  myservo1.write(90);
  delay(2000));
}
}

void Ultrasonic2(){
digitalWrite(TrigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin2, LOW);
duration2 = pulseIn(EchoPin2, HIGH);
jarak2 = (duration2/2)/28.5;
Serial.print("Jaraknya: ");
Serial.print(jarak2);
Serial.println("cm");
/* Variabel yang dimainkan */if (jarak2 <= 25){
Serial.println("Cetak ke serial monitor");
  Blynk.notify("Cetak ke serial monitor");
  x0 = 25-jarak2; //Line untuk kalkulasi persentase sampah
  binLevel = x0* 100/25; // Angka 10 harus sama dengan angka diatasnya
  Blynk.virtualWrite(Your Virtual pin, binLevel);
}
else{
  Serial.print("Jarak: ");
  Serial.println(digitalRead(jarak2));
}
 if (binLevel >=90){
    Blynk.email("your email","Warning" "Your warning message"); //Untuk mengirimkan ke email
    Blynk.logEvent("Your Virtual pin variabel on blynk","Your Virtual pin variabel on blynk" );
    
  }
  else{
    Serial.print("Sampah tidak penuh");
  }
}
void loop() {
  Blynk.run();
  timer.run();
  Ultrasonic1();
  Ultrasonic2();
}