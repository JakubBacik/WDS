#include <Arduino.h>
#include <CRC16.h>

struct Sensor{
  int trigPin;
  int echoPin;
  };

CRC16 crc;

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

/*
 * Funkcja tworzaca sume kontrolna
 */
unsigned short MakeFrame(String toCRC16){
  crc.setPolynome(0x1021);

  for(unsigned int i=0; i< toCRC16.length()-1; i++){
    crc.add(toCRC16[i]);
  }

  unsigned short toReturn = crc.getCRC();
  crc.restart();

  return toReturn;
}

/*
 * Funkcja pobierajaca dane z czujnikow ultradzwiekowych
 */
String GetDataFromSensor(){
  String dataString = "";
  dataString += "X";

  for(int i=0; i<4; i++){
    dataString += " "; 
    dataString += MeasureTheDistance(i);
  } 

  dataString += " ";

  return dataString;
}


void setup() {
  AddPinToTabOfSensor();
  Serial.begin(9600);
  InitSensor();

}

void loop() {
  String toPrint = GetDataFromSensor();
  unsigned short frame = MakeFrame(toPrint);
  Serial.print(toPrint);
  Serial.print(frame, HEX);
  Serial.print("\n");
  delay(100);
}