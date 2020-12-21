#include "SITUP.h"

SITUP::SITUP(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise):EXEC(X, Y, Z, angle, switchExercise) {
}

void SITUP::detect() {
    // detect
    switch (s)
    {
    case lying:
      if (*ag > 70) {
        state_count++;
        s = sitting;
        *pd = 0U<<12; // green
        indicate(12, 0.2);
      }
      break;
    case sitting:
      if (*ag < 19) {
        state_count++;
        s = lying;
        *pd = 1U<<12; // green
        indicate(12, 0.2);
      }
    default:
      break;
    }
    if (state_count == 2) {
      total_count++;
      state_count = 0;
    }
    log->printf("angle: %f total_count: %d \n", *ag, total_count);
}



