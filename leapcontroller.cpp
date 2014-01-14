#include "leapcontroller.h"

LeapController::LeapController()
{
  this->leapController = new Leap::Controller();
  this->leapListener = new LeapListener;
  this->leapController->addListener(*this->leapListener);
}

LeapController::~LeapController()
{
  this->leapController->removeListener(*this->leapListener);
  delete this->leapListener;
  delete this->leapController;
}
