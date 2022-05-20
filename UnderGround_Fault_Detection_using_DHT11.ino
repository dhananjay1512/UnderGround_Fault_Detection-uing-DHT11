#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
//LiquidCrystal lcd(12,11,5,4,3,2);
#include<Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define sensor A0  

#define relay1 8
#define relay2 9
#define relay3 10

#define buzzer 13  

int read_ADC;
int distance;

byte symbol[8] = {
        B00000,
        B00100,
        B00100,
        B00100,
        B11111,
        B01110,
        B00100,
        B00000};

void setup() {
pinMode(sensor,INPUT); 

pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);

pinMode(buzzer, OUTPUT);
  //Serial.begin(9600);
  lcd.begin(16,2);
  //Serial.println("DHT11 test!");
  dht.begin();

lcd.createChar(1, symbol);
    
//lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0); // set the cursor to column 0, line 2
lcd.print("Welcome to Cable");
lcd.setCursor(0, 1); // set the cursor to column 0, line 2
lcd.print("Fault  Detection");
delay(2000);
lcd.clear();
}

void loop(){
   //delay(2000);
lcd.setCursor(1,0);
lcd.print("R");
lcd.write(1);  

lcd.setCursor(7,0);
lcd.print("Y");
lcd.write(1); 

lcd.setCursor(13,0);
lcd.print("B");
lcd.write(1); 
        
digitalWrite(relay1,HIGH);
digitalWrite(relay2,LOW);
digitalWrite(relay3,LOW);  
delay(500);

data();
lcd.setCursor(0,1);
if(distance>0){lcd.print(distance); lcd.print("KM  ");}
else{lcd.print(" NF ");}

digitalWrite(relay1,LOW);
digitalWrite(relay2,HIGH);
digitalWrite(relay3,LOW);  
delay(500);

data();

lcd.setCursor(6,1);
if(distance>0){lcd.print(distance); lcd.print("KM  ");}
else{lcd.print(" NF ");}

digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);
digitalWrite(relay3,HIGH);  
delay(500);

data();

lcd.setCursor(12,1);
if(distance>0){lcd.print(distance); lcd.print("KM  ");}
else{lcd.print(" NF ");
}

data();
lcd.clear();
float h= dht.readHumidity();
  float t= dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("Hum:");
  lcd.print(h);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.print(t);
  delay(1000);
  data();
  lcd.clear();

 

}//lcd.clear();



void data(){
read_ADC = analogRead(sensor);  
distance = read_ADC/100;

if(distance>9)distance = 0;

if(distance>0){
digitalWrite(buzzer,HIGH);
delay(200);
digitalWrite(buzzer,LOW);  
delay(200);
 }
}
