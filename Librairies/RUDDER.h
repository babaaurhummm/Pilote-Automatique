#ifndef RUDDER_H
#define RUDDER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"

class RUDDER {
public:
    RUDDER();
    void init();
    void update();
    void set_rudder_angle(int angle);
    float get_rudder_angle();
private:
    float angle_rudder;
    int ADC_rudder_value;
    float k;
    void test_rudder_servo();
};

#endif 