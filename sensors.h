#include <Arduino.h>

#include <MCP3008.h>
// define pin connections
#define CLOCK_PIN 14
#define MOSI_PIN 13
#define MISO_PIN 12
#define CS_PIN 15
MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

float tmp36_tempF;
float tmp36_tempC;

void tmp36_read()
{
    //tmp36 temp sensor
    int tmp36Value = adc.readADC(0);
    //int tempValue = adc.readADC(0);
    Serial.print("tmp36 value: ");
    Serial.println(tmp36Value);
    // converting that reading to voltage, for 3.3v arduino use 3.3
    float tmp36Voltage = tmp36Value * volt_3;
    tmp36Voltage /= 1024.0;
    // print out the voltage
    Serial.print(tmp36Voltage);
    Serial.println(" volts");
    // now print out the temperature
    tmp36_tempC = (tmp36Voltage - volt_3) * 100; //converting from 10 mv per degree wit 500 mV offset
                                                 //to degrees ((voltage - 500mV) times 100)
    Serial.print(tmp36_tempC);
    Serial.println(" degrees C");
    // now convert to Fahrenheit
    tmp36_tempF = (tmp36_tempC * 9.0 / volt_3) + 32.0;
    Serial.print(tmp36_tempF);
    Serial.println(" degrees F");
};

//photoresistor
float lightPercentage;
void read_lightSensor()
{
    float lightSensorValue = adc.readADC(7);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float lightVoltage = lightSensorValue * (volt_3 / 1023.0);
    lightPercentage = 100 - (lightVoltage / volt_3) * 100;
    // print out the value you read:
    Serial.print("light Sensor: Value:");
    Serial.print(lightSensorValue);
    Serial.print("\t Voltage: ");
    Serial.print(lightVoltage);
    Serial.print("\t light %:");
    Serial.println(lightPercentage);
    Serial.println();
};

 //ground moistor
float groundMoisture;
 void read_GroundMoisture(){
  int groundMoistureValue = adc.readADC(3);
  Serial.print("Ground Moisture\t");
  Serial.println(groundMoistureValue);
  groundMoisture = groundMoistureValue;
 }
