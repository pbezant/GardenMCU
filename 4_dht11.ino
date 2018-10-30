

void sendDHT()
{
  float h = dht.getHumidity();
  float t = dht.getTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

}

void setup_dht(int PIN)
{
//  Serial.begin(115200);
//  Serial.println();
 
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);

  // Autodetect is not working reliable, don't use the following line
  // dht.setup(14);
  // use this instead: 
  dht.setup(PIN, DHTesp::DHT11); // Connect DHT sensor to GPIO 14
}

void loop_dht()
{
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  if(dht.getStatusString() != "TIMEOUT"){
    Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
    Serial.print(dht.getStatusString());
    Serial.print("\t\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t");
    Serial.print(dht.toFahrenheit(temperature), 1);
    Serial.print("\t\t");
    Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
    Serial.print("\t");
    Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
  }
 //delay(dht.getMinimumSamplingPeriod());
}
