#ifndef LEAPCONTROLLER_H
#define LEAPCONTROLLER_H
#include "Leap.h"
#include "leaplistener.h"
#include "glwindow.h"

class LeapController
{
public:
    LeapController(GLWindow* glWindow);
    LeapController();
    ~LeapController();
 private:
    LeapListener* leapListener;
    Leap::Controller* leapController;
};

#endif // LEAPCONTROLLER_H
