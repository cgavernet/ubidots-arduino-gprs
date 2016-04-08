#include <Ubidots_Arduino_GPRS.h>
#include <SoftwareSerial.h>
#include <DHT.h>    //Libreria DTH
#define DHT_PIN 2
#define DHT_TYPE DHT22
#define LIGHT_SENSOR A0
#define APN "igprs.claro.com.ar" 
#define USER "clarogprs"  // If your apn doesnt have username just put ""
#define PASS "clarogprs999"  // If your apn doesnt have password just put ""
#define TOKEN "A4T2WIwYmGGkH7uDw5ZGq7H3p7Hcmv"  
// You can send 1 to 10 variable at the same time

DHT dht(DHT_PIN, DHT_TYPE);
Ubidots client(TOKEN);  
// Interval for Delay (milis)

long previousMillis = 0;
long interval = 60000; 

void setup() {
     Serial.begin(19200);
     client.powerUpOrDown();
     client.setApn(APN,USER,PASS);
}

void loop() {
  
  
  // Delay for Multitask
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   
    // ToDo
  float h = dht.readHumidity(); //Se lee la humedad
  float t = dht.readTemperature(); //Se lee la temperatura
  int l =  analogRead(LIGHT_SENSOR);
  
  float value = client.getValue("5706bda776254218107b8a3c");
  // For Debug purpouse Only
  Serial.print("Switch 1 Value:");
  Serial.println(value); 
  // Update
  client.add("5706b39776254245def49490", t, "", "");
  client.add("5706b39776254245131516f3", h, "", "");
  client.add("5707a39b7625423b93ef6cad", l, "", "");
  client.sendAll();  
  }
}

