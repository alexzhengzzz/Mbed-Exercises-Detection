#ifndef PUSHUP_H
#define PUSHUP_H
 
#include "mbed.h"
#include "USBSerial.h"
#include "EXEC.h"

class PUSHUP : public EXEC {
    public:
        PUSHUP(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise);
        virtual void detect();
       
        typedef enum {
        up,
        down
        } state;
        state s = up;
};  
#endif



