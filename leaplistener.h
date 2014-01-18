#ifndef LEAPLISTENER_H
#define LEAPLISTENER_H
#include <iostream>
#include "Leap.h"
#include <QObject>
#include "glwindow.h"
using namespace Leap;

class LeapListener: public Listener
{
public:
  LeapListener();
  LeapListener(GLWindow* glWindow);
  void onInit(const Controller&);
  void onConnect(const Controller&);
  void onDisconnect(const Controller&);
  void onExit(const Controller&);
  void onFrame(const Controller&);
  void onFocusGained(const Controller&);
  void onFocusLost(const Controller&);
  GLWindow* glWindow;
};

#endif // LEAPLISTENER_H
