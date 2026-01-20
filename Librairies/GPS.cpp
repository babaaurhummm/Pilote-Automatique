#include <Arduino.h>
#include <Arduino_RouterBridge.h>
#include "GPS.h"

GPS::GPS() {
    point.lat = 0.0f;
    point.lng = 0.0f;
}

void GPS::init() {
    Monitor.println("Initializing GPS...");
}

void GPS::update() {
}

GPScoord GPS::get_point() {
    return point;
}
