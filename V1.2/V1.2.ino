//libraries
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <BH1750FVI.h>
//other
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
//pins
#define DHTTYPE DHT11
#define DHTPIN 5//DHT pin
//int ms = A0;//moisture sensor
//int sv = 0;//sensore value
const int chipSelect = 4;//SD 

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Wire.begin();
  LightSensor.begin();  
  if (!SD.begin(chipSelect)) {
    while (1);
    }
  pinMode(8, OUTPUT);//set led pin
  dht.begin();
}                                                                                                                                                              
void loop()
{
  //LED blink
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);  
  //sd
  String dataString = "";
  //DHT
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  //moisture 
  //int sv = analogRead(ms);//read sensor
  //light sensor 
  uint16_t lux = LightSensor.GetLightIntensity();
  //SD
  dataString =  String(t) + "," + String(h) + "," + String(lux);//add for soil moisture String(sv) + "," 
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  delay(36000);//period
}
