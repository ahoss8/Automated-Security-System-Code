#include <LiquidCrystal_74HC595.h> // Importing LCD 74HC595 Library
#include <Servo.h>
Servo myServo;

const int latchPin = 7; // Shift Register Latch Pin 
const int clockPin = 13; // Shift Register Clock Pin For Coordinating The Timing of Data Transfer
const int dataPin = 11; // Shift Register Serial Data Input Pin
LiquidCrystal_74HC595 lcd(dataPin, clockPin, latchPin, 1, 3, 4, 5, 6, 7); // Creating LCD Object From LCD Class


int trigPin = 6;
int echoPin = 5;
int pingTravelTime;
float pingTravelDistance;
float distance;

int servoPin = 9;
int pos;
int increment = 2;

bool servoCont;

int ledPin1 = 8;
int ledPin2 = 4;
int photoPin = A1;
int lightVoltage;
float brightness;


int buzzPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(photoPin, INPUT);

  pinMode(buzzPin, OUTPUT);

  lcd.begin(16,2);
}


void loop() {  
  lightControl();
  detector();

}


void detector() {
  
  for (pos = 0; pos <= 150; pos += 2) {
    servoCont = true;
    while (servoCont) {
  
      myServo.write(pos);
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(10);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    
      pingTravelTime = pulseIn(echoPin, HIGH);
      pingTravelDistance = (pingTravelTime * 765. * 5280. * 12.) / (3600. * 1000000);
      distance = pingTravelDistance / 2;
      Serial.println(distance);
      delay(75);
      if (distance < 0) {
        distance = 90;
      }
      
      if (distance >= 10) {
        myServo.write(pos);
        servoCont = false;  
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Security System");
        lcd.setCursor(0,1);
        lcd.print("Coast Is Clear");      
      }
      else if (distance <= 3 && distance >= 0) {
        servoCont = true;
        digitalWrite(buzzPin, HIGH);
        delay(100);
        digitalWrite(buzzPin, LOW);
        delay(50);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Object Detected");
        lcd.setCursor(0,1);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("in");
      }
      else if (distance <= 6 && distance >= 0) {
        servoCont = true;
        digitalWrite(buzzPin, HIGH);
        delay(300);
        digitalWrite(buzzPin, LOW);
        delay(100);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Object Detected");
        lcd.setCursor(0,1);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("in");
      }
      else if (distance < 10 && distance >= 0) {
        servoCont = true;
        digitalWrite(buzzPin, HIGH);
        delay(500);
        digitalWrite(buzzPin, LOW);
        delay(400);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Object Detected");
        lcd.setCursor(0,1);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("in");
      }

    }
  }

  for (pos = 150; pos >= 0; pos -= 2) {
    servoCont = true;
    while (servoCont) {
      myServo.write(pos);
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(10);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    
      pingTravelTime = pulseIn(echoPin, HIGH);
      pingTravelDistance = (pingTravelTime * 765. * 5280. * 12.) / (3600. * 1000000);
      distance = pingTravelDistance / 2;
      Serial.println(distance);
      
      delay(75);
      if (distance < 0) {
        distance = 90;
      }

      if (distance >= 10) {
        myServo.write(pos);
        servoCont = false;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Security System");
        lcd.setCursor(0,1);
        lcd.print("Coast Is Clear"); 
      }
      else if (distance <= 3 && distance >= 0) {
        servoCont = true;
        digitalWrite(buzzPin, HIGH);
        delay(100);
        digitalWrite(buzzPin, LOW);
        delay(50);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Object Detected");
        lcd.setCursor(0,1);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("in");
      }
      else if (distance <= 6 && distance >= 0) {
        servoCont = true;
        digitalWrite(buzzPin, HIGH);
        delay(300);
        digitalWrite(buzzPin, LOW);
        delay(100);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Object Detected");
        lcd.setCursor(0,1);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("in");
      }
      else if (distance < 10 && distance >= 0) {
        servoCont = true;
        digitalWrite(buzzPin, HIGH);
        delay(500);
        digitalWrite(buzzPin, LOW);
        delay(400);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Object Detected");
        lcd.setCursor(0,1);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("in");
        
      }

    }
  }
    
}


void lightControl() {
  lightVoltage = analogRead(photoPin);

  if (lightVoltage >= 100) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);      
  }

  else {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
  }
  
}
