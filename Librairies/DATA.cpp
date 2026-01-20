#include <Arduino.h>
#include <Arduino_RouterBridge.h>
#include "DATA.h"

DATA::DATA() = default;

void DATA::init() {
    Monitor.println("Initializing DATA logger...");
}

void DATA::save_data(unsigned long timestamp,
                     float latitude,
                     float longitude,
                     float heading,
                     float rudder_angle,
                     float awa,
                     float filtered_awa,
                     bool unmanned_status) {
    (void)timestamp;
    (void)latitude;
    (void)longitude;
    (void)heading;
    (void)rudder_angle;
    (void)awa;
    (void)filtered_awa;
    (void)unmanned_status;
}
