#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include "CONFIG.h"

class COM {
public:
    COM();
    void init();
    void update();
    int get_com_rudder();
    bool is_unmanned();
private:
    int rudder_value;
    int mode_control_value;
    int get_mode_control_value();
    bool unmanned_status = false;
};

#endif 