/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Set web server port number to 80
//WiFiServer server(80);

// Variable to store the HTTP request
String header;



void setup_WifiManager() {
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;  
  
  // Uncomment and run it once, if you want to erase all the stored information
 //wifiManager.resetSettings();
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
}

void loop_WiFiManager(){
   
}
