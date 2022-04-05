#include <Arduino.h>

struct Sensor{
  int trigPin;
  int echoPin;
  };

struct Sensor pinsOfSensor[4];

/* Funkcja odpowiedzialna za dodanie numerów
 * pinów do struktury Sensor
 */
void AddPinToTabOfSensor(){
  for(int i=0; i<4; i++){
    pinsOfSensor[i].trigPin = 2*(i+1);
    pinsOfSensor[i].echoPin = ((2*(i+1))+1);
  }  
}

/* Funkcja odpowiedzialna za inicjalizacje 
 * odpiwednich pinów w strukturze
 */
void InitSensor(){
  for(int i=0; i<4; i++){
    pinMode(pinsOfSensor[i].trigPin, OUTPUT);
    pinMode(pinsOfSensor[i].echoPin, INPUT);
  }
}

/*
 * Funkcja odpowiedzilna za pomiar odległości 
 * dla czujnika wybranego poprzez argument
 * numberOfSensor
 */
int MeasureTheDistance(int numberOfSensor) {
  long duration, distance;
 
  digitalWrite(pinsOfSensor[numberOfSensor].trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pinsOfSensor[numberOfSensor].trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinsOfSensor[numberOfSensor].trigPin, LOW);
 
  duration = pulseIn(pinsOfSensor[numberOfSensor].echoPin, HIGH);
  distance = duration / 58;
 
  return distance;
}

void setup() {
  AddPinToTabOfSensor();
  Serial.begin(9600);
  InitSensor();

}

void loop() {
  Serial.print("!");
  
  for(int i=0; i<4; i++){
    Serial.print(", ");
    Serial.print(MeasureTheDistance(i));  
  } 
  
  Serial.print(",\n");
  Serial.flush();
  delay(1000);
}