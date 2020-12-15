#ifndef EXEC_H
#define EXEC_H
 
#include "mbed.h"
#include "USBSerial.h"
#include "LEDBLINK.h"


class EXEC {
  public:
    EXEC(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise);
    virtual void detect(){};
    virtual void reset(){};
    void setLogger(USBSerial* logger);
    void indicate(int port, float time); 
    void finish();

    USBSerial* log;
    LEDBLINK* led;
    PortOut* pd;

    int16_t* x;
    int16_t* y;
    int16_t* z;

    float* ag;
    int count;
    volatile int* sw;

    /**** define 4 kinds of exercises state ****/
    typedef enum {
      SITUPS,
      PUSHUPS,
      JUMPINGJACKS,
      SQUATS
    } WORKOUT;
};
#endif