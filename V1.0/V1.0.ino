//libraries
#include <dht.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <BH1750FVI.h>

//other
dht DHT;
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

//pins
#define DHT11_PIN 5//DHT pin
int ms = A0;//moisture sensore
int sv = 0;//sensore value

const int chipSelect = 4;//SD 

void setup(){
  Serial.begin(9600);
  Wire.begin();
  LightSensor.begin();  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    //don't do anything more:
    while (1);
  }  
  Serial.println("card initialized.");
  pinMode(8, OUTPUT);
}

void loop()
{
  //LED
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);  
  
  //DHT
  int chk = DHT.read11(DHT11_PIN);//read DHT 11
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);//print Temperature
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);//print humidity 
  
  //moisture 
  int sv = analogRead(ms);//read sensor
  Serial.print("Moisture is ");
  Serial.println(sv);

  //light sensor 
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.println(lux);

  //SD
  dataString = String(sv) + "," + String(DHT.temperature) + "," + String(DHT.humidity) + "," + String(lux);
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    //print to the serial port too:
    Serial.println(dataString);
  }
  //if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(5000);
}
