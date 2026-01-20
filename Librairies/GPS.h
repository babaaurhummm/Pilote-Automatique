#ifndef GPS_H
#define GPS_H

struct GPScoord {
    float lat;
    float lng;
};

class GPS {
public:
    GPS();
    void init();
    void update();
    GPScoord get_point();
private:
    GPScoord point;
};

#endif
