#include "spiffs.h"

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <FS.h>

WiFiClient spiffs_client;
ESP8266WebServer spiffs_server(80);

spiffs::spiffs(const String server_name){
    const char* hostname = server_name.c_str();
    if (MDNS.begin(hostname))
    { // Start the mDNS responder for esp8266.local
        Serial.println(String("mDNS responder started:\t ") + server_name);
    }
    else
    {
        Serial.println("Error setting up MDNS responder!");
    }

    SPIFFS.begin(); // Start the SPI Flash Files System
    spiffs_server.on("/", HTTP_GET, []() {
        handleFileRead("/");
    });

    spiffs_server.onNotFound([]() {                                  // If the client requests any URI
        if (!handleFileRead(spiffs_server.uri()))                    // send it if it exists
            spiffs_server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
    });

    spiffs_server.begin(); // Actually start the server
    Serial.println("HTTP server started");
};

String spiffs::getContentType(String filename)
{
    if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    else if (filename.endsWith(".gz"))
        return "application/x-gzip";
    return "text/plain";
};

bool spiffs::handleFileRead(String path)
{ // send the right file to the client (if it exists)
    Serial.println("handleFileRead: " + path);
    if (path.endsWith("/"))
        path += "index.html";                  // If a folder is requested, send the index file
    String contentType = getContentType(path); // Get the MIME type
    String pathWithGz = path + ".gz";
    if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
    {                                                       // If the file exists, either as a compressed archive, or normal
        if (SPIFFS.exists(pathWithGz))                      // If there's a compressed version available
            path += ".gz";                                  // Use the compressed version
        File file = SPIFFS.open(path, "r");                 // Open the file
        size_t sent = spiffs_server.streamFile(file, contentType); // Send it to the client
        file.close();                                       // Close the file again
        Serial.println(String("\tSent file: ") + path);
        return true;
    }
    Serial.println(String("\tFile Not Found: ") + path);
    return false; // If the file doesn't exist, return false
};