#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

constexpr int PIN_COM_RUDDER = 2;
constexpr int PIN_MODE_CONTROL = 3;

constexpr int pwm_mode_treshold = 1500;
constexpr int pwm_rudder_center = 1500;

constexpr int ADC_rudder_center = 512;
constexpr int ADC_rudder_range = 1023;
constexpr float rudder_max_angle = 30.0f;

constexpr int max_pulse_rudder = 600;
constexpr int min_pulse_rudder = 150;

constexpr int PIN_WINDSENSOR = A0;
constexpr int PIN_RUDDER_ADC = A1;
constexpr int RUDDER_CHANNEL = 0;

constexpr bool EMAfilter = true;
constexpr float alpha_EMA = 0.2f;

#endif
