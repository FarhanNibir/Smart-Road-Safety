#include <Wire.h>
#include <LiquidCrystal_I2C.h>


const int trigPin1 = 10;
const int echoPin1= 9;
const int trigPin2 = 7;
const int echoPin2= 6;
int threshold = 20;

int buzz = 3;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // initialize the LCD display with the I2C address of 0x27

void setup() {
  pinMode(trigPin1, OUTPUT); // set trig pin for first sensor as output
  
  
  pinMode(echoPin1, INPUT); // set echo pin for second sensor as input
  
  pinMode(trigPin2, OUTPUT); // set trig pin for first sensor as output
  
  
  pinMode(echoPin2, INPUT); 

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT); // set pin for LED indicator as output

  lcd.init();
  lcd.backlight();
  Serial.begin(9600); // initialize serial communication at 9600 baud rate
}

int sensor1(){
  long duration1, distance1=0;
  digitalWrite(trigPin1, LOW); // set trig pin for first sensor to low
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH); // set trig pin for first sensor to high
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW); // set trig pin for first sensor to low
  duration1 = pulseIn(echoPin1, HIGH); // measure duration for first sensor
  distance1 = duration1 * 0.034 / 2; // calculate distance for first sensor in cm
  return distance1;
}
void speedforsensor1(){
  long distance1,distance2;
  distance1 = sensor1();
  delay(1000);
  distance2 = sensor1();

  int speedtrack_sensor1  = abs (distance1 - distance2) /1.0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("speed1: ");
  lcd.print(speedtrack_sensor1);

  // Serial.print("speed1 for sensor1: ");
  // Serial.print(speedtrack_sensor1);
  // Serial.print(" cm \n");

}
int sensor2(){
  long distance2 =0, duration2;
  digitalWrite(trigPin2, LOW); // set trig pin for first sensor to low
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); // set trig pin for first sensor to high
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW); // set trig pin for first sensor to low
  duration2 = pulseIn(echoPin2, HIGH); // measure duration for first sensor
  distance2 = duration2 * 0.034 / 2; // calculate distance for first sensor in cm
  return distance2;
}

void speedforsensor2(){
  long distance1,distance2;
  distance1 = sensor2();
  delay(1000);
  distance2 = sensor2();

  int speedtrack_sensor2  = abs (distance1 - distance2) /1.0;

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("speed2: ");
  lcd.print(speedtrack_sensor2);
}

void loop() {
  long distance1=0,distance2 =0;

  distance1 = sensor1();
  distance2 = sensor2();
  
if (distance1 < threshold && distance2 > threshold) { // check if vehicle passes through one side
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(2, LOW); // turn on LED indicator
  } else if(distance1 < threshold && distance2 < threshold){
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    
    tone(buzz, 2000);
    delay(100);
    noTone(buzz);
    delay(100);

    tone(buzz, 2000);
    delay(100);
    noTone(buzz);
    delay(100);

    tone(buzz, 2000);
    delay(100);
    noTone(buzz);
    delay(100);

    tone(buzz, 2000);
    delay(100);
    noTone(buzz);
    delay(100);
    }
  else if (distance1 > threshold && distance2 < threshold){
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(2, HIGH);
    
     // turn off LED indicator
  }
  else {
    digitalWrite(13, HIGH);
    digitalWrite(12,LOW );
    digitalWrite(8, LOW);
    digitalWrite(2, HIGH); // turn off LED indicator
  }  
  speedforsensor1();
  speedforsensor2();  
}
