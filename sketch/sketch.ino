#include "COM.h"
#include "IMU.h"
#include "GPS.h"
#include "RUDDER.h"
#include "WINDSENSOR.h"
#include "DATA.h"
#include "CONFIG.h"


void setup() {
  COM.init();
  IMU.init();
  GPS.init();
  RUDDER.init();
  WINDSENSOR.init();
  DATA.init();
}

void loop() {
  
  update();
  save_data();
  if (COM.is_unmanned())
  {
    RUDDER.set_rudder_angle(PILOTE.rudder_angle_set_value()));
  }
  else
  {
    RUDDER.set_rudder_angle(COM.get_com_rudder());
  }
}

void update() {
  COM.update();
  IMU.update();
  GPS.update();
  WINDSENSOR.update();
  RUDDER.update();
}

void save_data() {
  GPScoord point = GPS.get_point();
  float heading = imu.get_heading();
  float r_angle = nav.get_rudder_angle();
  float awa = WINDSENSOR.get_awa();
  float f_awa = WINDSENSOR.get_filtered_awa();
  bool unmanned_status = COM.is_unmanned();
  DATA.save_data(millis(), point.lat, point.lng, heading, r_angle, awa, f_awa, unmanned_status);
}
