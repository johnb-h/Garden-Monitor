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
  Wire.begin();
  LightSensor.begin();  
  if (!SD.begin(chipSelect)) {
    while (1);
    }
}                                                                                                                                                              
void loop()
{
  //sd
  String dataString = "";
  //DHT
  int chk = DHT.read11(DHT11_PIN);
  //moisture 
  int sv = analogRead(ms);//read sensor
  //light sensor 
  uint16_t lux = LightSensor.GetLightIntensity();
  //SD
  dataString = String(sv) + "," + String(DHT.temperature) + "," + String(DHT.humidity) + "," + String(lux);
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  delay(5000);
}
