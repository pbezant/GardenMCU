
#include <FirmataDefines.h>
#include <FirmataConstants.h>
#include <Boards.h>
#include <Firmata.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>


#include <Wire.h>

#include <ESP8266WiFi.h>

//wifimanager
//#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

//ArduionoOTA
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

//dht11
#include <DHTesp.h>
DHTesp dht;


//wifi settings
//const char* ssid = "Philbert Longbottom";
//const char* password = "2323EatShit";
const char* ssid;
const char* password;

WiFiClient client;


// Measurement interval (seconds)
const int interval = 5;
const int volt_3 = 3.3;
const int volt_5 = 5;

#define TEMP D5
#define LED 2
//#define LED D8

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  
  pinMode(LED, OUTPUT);
  setup_WifiManager();
  
  while (WiFi.status() != WL_CONNECTED) {
    // Blink LED when connecting to wifi
    digitalWrite(LED, LOW);
    delay(1000);
    digitalWrite(LED, HIGH);
    delay(1000);
  }

  
  setup_ota();
  
//  webServer_setup();
  setup_dht(TEMP);
  setup_multiplexer();

}

// main loop
void loop()
{
  loop_ota();
 // webServer_loop();
  digitalWrite(LED, LOW);
  
  //sensor readings
 
  //photoresistor
  int lightSensorValue = readSensor(1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float lightVoltage = lightSensorValue * (volt_3 / 1023.0);
  float lightPercentage = (lightSensorValue / 1023.0)*100;
  // print out the value you read:
  Serial.print("light Sensor\t");
  Serial.print(lightVoltage);
  Serial.print("light %");
  Serial.println(lightPercentage);

  
  //DHT11 Temp/Humidity
  //loop_dht();
  //end sensor reading
  float humidity = dht.getHumidity();
  float temperatureC = dht.getTemperature();
  float temperatureF = dht.toFahrenheit(temperatureC);
  float heatIndex = dht.computeHeatIndex(dht.toFahrenheit(temperatureC), humidity, true);
  int light = lightSensorValue;
  
  postData(temperatureF, temperatureC, humidity, heatIndex, lightPercentage);
  
  digitalWrite(LED, HIGH);


  delay(interval * 1000);
  Serial.println();

}
