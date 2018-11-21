#include <Arduino.h>

class spiffs{
    protected:
      static String getContentType(String filename); // convert the file extension to the MIME type
      static bool handleFileRead(String path);       // send the right file to the client (if it exists)
    public:  
      spiffs(const String server_name);
};
