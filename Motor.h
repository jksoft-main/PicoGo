#ifndef Motor_h
#define Motor_h
#include "Arduino.h"

class Motor
{
  public:

  Motor();
  void begin();
  void control(int right,int left);
  void stop();
};

#endif