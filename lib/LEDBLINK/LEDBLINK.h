#ifndef LEDBLINK_H
#define LEDBLINK_H
 
#include "mbed.h"
 
class LEDBLINK {
  public:
    LEDBLINK();
    void blinkALL(int count);
    void blinkCircle(int count);
    void toggleOneLed(int count, int pin);
};
#endif