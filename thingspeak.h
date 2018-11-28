#include <WiFiClient.h>

void postData(float temperatureF, float temperatureC, float humidity, float heatIndex, float light, float groundMoisture, float tmp36_tempF){
  // Send data to ThingSpeak
  WiFiClient client;
  
  if (client.connect(thingspeak_server,80)) {
  Serial.println("Connect to ThingSpeak - OK"); 

  String dataToThingSpeak = "";
  dataToThingSpeak+="GET /update?api_key=";
  dataToThingSpeak+=api_key;
   
  dataToThingSpeak+="&field1=";
  dataToThingSpeak+=String(temperatureF);
  
  dataToThingSpeak+="&field2=";
  dataToThingSpeak+=String(temperatureC);

  dataToThingSpeak+="&field3=";
  dataToThingSpeak+=String(humidity);

  dataToThingSpeak+="&field4=";
  dataToThingSpeak+=String(heatIndex);

  dataToThingSpeak+="&field5=";
  dataToThingSpeak+=String(light);

  dataToThingSpeak+="&field6=";
  dataToThingSpeak+=String(groundMoisture);

  dataToThingSpeak+="&field7=";
  dataToThingSpeak+=String(tmp36_tempF);
   
  dataToThingSpeak+=" HTTP/1.1\r\nHost: a.c.d\r\nConnection: close\r\n\r\n";
  dataToThingSpeak+="";
  client.print(dataToThingSpeak);

  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println("Error: Client Timeout!");
      client.stop();
      return;
    }
  }
}
 while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}