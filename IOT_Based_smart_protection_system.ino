#define trigPin 9  
#define echoPin 10
#define buzzer 8
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);//connect RX to pin 10 , connect TX to pin 9

void setup() 
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin (9600); 
  delay(100);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance < 100)
  {
    Serial.print("Distance ");
    Serial.print(distance);
    Serial.print("cm Train is detected");
    Serial.println();
    digitalWrite(buzzer,HIGH);
    tone(buzzer, 635);
    delay(500);
      
    mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);  
    mySerial.println("AT+CMGS=\"+917875087764\"\r"); 
    delay(1000);
    mySerial.println("Train is on the way. ");
    delay(100);
    mySerial.println((char)26);// ASCII code of CTRL+Z 
  }
  
  else
  {
    tone(buzzer, 3);
    delay(2000);
    Serial.print("Distance ");
    Serial.print(distance);
    Serial.print("cm Train is not detected");
    Serial.println();
    digitalWrite(buzzer,LOW);
  }
 delay(2000);
}
