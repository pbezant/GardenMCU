#ifndef _SETUP_h
#define _SETUP_h

#define LED 2
const String server_name= "esp8266";

const float volt_3 = 3.3;
const int volt_5 = 5;

// Measurement interval (minutes)
const float interval = 1;
//const float interval = 0.1;

//wifi settings
//const char* ssid = "Philbert Longbottom";
//const char* password = "2323EatShit";
const char* ssid;
const char* password;

const char* thingspeak_server = "api.thingspeak.com";
const char* api_key = "CZ4QYCRKVM2BBHK8";

#endif