#include <Arduino.h>
#include <Arduino_RouterBridge.h>
#include "PILOTE.h"

PILOTE::PILOTE() = default;

void PILOTE::init() {
    Monitor.println("Initializing PILOTE...");
}

int PILOTE::rudder_angle_set_value() {
    return 0;
}
