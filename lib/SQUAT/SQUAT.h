#ifndef SQUAT_H
#define SQUAT_H
 
#include "mbed.h"
#include "USBSerial.h"
#include "EXEC.h"

class SQUAT: public EXEC {
    public:
        SQUAT(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise);
        virtual void detect();

        typedef enum {
        standing,
        squating
        } state;
        state s = standing;
};  
#endif



