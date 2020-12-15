#include "SITUP.h"

SITUP::SITUP(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise):EXEC(X, Y, Z, angle, switchExercise) {
    last_angle = 360;
}

void SITUP::detect() {
    log->printf("angle: %f count: %d \n", *ag, count);
    // detect
    if (last_angle < 19 && *ag > 44) {
      count = count +1;
      *pd = 0U<<12; // green
      indicate(12, 0.2);
    }
    // record previos angle
    last_angle = *ag;  
}

void SITUP::reset() {
  last_angle = 360;
  count = 0;
}


