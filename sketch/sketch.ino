#include "COM.h"
#include "IMU.h"
#include "GPS.h"
#include "PILOTE.h"
#include "RUDDER.h"
#include "WINDSENSOR.h"
#include "DATA.h"
#include "CONFIG.h"
#include <Arduino_RouterBridge.h>

COM com;
IMU imu;
GPS gps;
PILOTE pilote;
RUDDER rudder;
WINDSENSOR windsensor;
DATA data;


void setup() {
  Bridge.begin();
  com.init();
  imu.init();
  gps.init();
  rudder.init();
  windsensor.init();
  data.init();
}

void loop() {
  
  update();
  save_data();
  if (com.is_unmanned())
  {
    rudder.set_rudder_angle(pilote.rudder_angle_set_value());
  }
  else
  {
    rudder.set_rudder_angle(com.get_com_rudder());
  }
}

void update() {
  com.update();
  imu.update();
  gps.update();
  windsensor.update();
  rudder.update();
}

void save_data() {
  GPScoord point = gps.get_point();
  float heading = imu.get_heading();
  float r_angle = rudder.get_rudder_angle();
  float awa = windsensor.get_awa();
  float f_awa = windsensor.get_filtered_awa();
  bool unmanned_status = com.is_unmanned();
  data.save_data(millis(), point.lat, point.lng, heading, r_angle, awa, f_awa, unmanned_status);
}
