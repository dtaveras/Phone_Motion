#ifndef LEAPCONTROLLER_H
#define LEAPCONTROLLER_H
#include "Leap.h"
#include "leaplistener.h"

class LeapController
{
public:
    LeapController();
    ~LeapController();
 private:
    LeapListener* leapListener;
    Leap::Controller* leapController;
};

#endif // LEAPCONTROLLER_H
