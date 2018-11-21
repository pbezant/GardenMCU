#ifndef _OTA_h
#define _OTA_h

#include <Arduino.h>
#include <ArduinoOTA.h>


class OTA {
  protected:
  public:
    OTA(const String server_name);
    static void loop();
};

#endif