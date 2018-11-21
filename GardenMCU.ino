#include "setup.h"

#include <FirmataDefines.h>
#include <FirmataConstants.h>
#include <Boards.h>
#include <Firmata.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

#include <Wire.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

WiFiClient client;
ESP8266WebServer server(80);

//wifimanager
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
//#include <DNSServer.h> 

#include "sensors.h"

//dht11
#include <DHTesp.h>
DHTesp dht;
#define TEMP D4

#include "OTA.h"
OTA ota(server_name);

//spiffs
// #include "spiffs.h"
// spiffs spiff(server_name);

#include "thingspeak.h"

void setup_WifiManager() {
  const char* hostname = server_name.c_str();
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;  
  
  // Uncomment and run it once, if you want to erase all the stored information
  // wifiManager.resetSettings();
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  
  wifiManager.autoConnect(hostname);

  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();

  if (!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }
  WiFi.begin();
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());   
}

void setup(){
  
  Serial.begin(115200);
  Wire.begin();

  pinMode(LED, OUTPUT);
  //digitalWrite(LED, HIGH);
  setup_WifiManager();
  
  while (WiFi.status() != WL_CONNECTED) {
    // Blink LED when connecting to wifi
     digitalWrite(LED, LOW);
     delay(1000);
     digitalWrite(LED, HIGH);
     delay(5000);
  }
  dht.setup(TEMP, DHTesp::DHT11); // Connect DHT sensor to GPIO 12
  
//   }

// // main loop
// void loop(){
  
  server.handleClient();
  Serial.println();

  //sensor readings
  //digitalWrite(LED, HIGH);
  
  tmp36_read();

  //DHT11 Temp/Humidity

  float humidity = dht.getHumidity();
  float temperatureC = dht.getTemperature();
  float temperatureF = dht.toFahrenheit(temperatureC);
  float heatIndex = dht.computeHeatIndex(dht.toFahrenheit(temperatureC), humidity, true);
  float light = lightPercentage;

  //digitalWrite(LED, HIGH);
  //end sensor reading

  Serial.println();
  Serial.println();
  
  //check analog signals

  for (int chan=0; chan<8; chan++) {
    Serial.print("["); Serial.print(chan); Serial.print("]");Serial.print("\t");
    Serial.println(adc.readADC(chan)); 
  }
  Serial.println("---");

  ota.loop();
  postData(temperatureF, temperatureC, humidity, heatIndex, light, groundMoisture, tmp36_tempF);

  // delay(interval * 60000);
  ESP.deepSleep(interval * 60000);
}

void loop(){}
