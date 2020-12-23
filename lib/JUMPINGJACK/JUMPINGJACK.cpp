#include "JUMPINGJACK.h"

JUMPINGJACK::JUMPINGJACK(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise):EXEC(X, Y, Z, angle, switchExercise) {
}

void JUMPINGJACK::detect() {
    // detect
    switch (s)
    {
    case standing:
      if (*ag > 105) {
        state_count++;
        s = jumping;
        *pd = 1U<<14; // green
      }
      break;
    case jumping:
      if (*ag < 95) {
        state_count++;
        s = standing;
        *pd = 0U<<14; // green
      }
    default:
      break;
    }
    if (state_count == 2) {
      total_count++;
      state_count = 0;
    }
    log->printf("total_count: %d ag: %f \n", total_count, *ag);
}




