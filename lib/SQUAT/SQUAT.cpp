#include "SQUAT.h"

SQUAT::SQUAT(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise):EXEC(X, Y, Z, angle, switchExercise) {
}

void SQUAT::detect() {
    // detect
    switch (s)
    {
    case standing:
      if (*z < 1420) {
        state_count++;
        s = squating;
        *pd = 1U<<15; // green
      }
      break;
    case squating:
      if (*z > 2360) {
        state_count++;
        s = standing;
        *pd = 1U<<15; // green
      }
    default:
      break;
    }
    if (state_count == 2) {
      total_count++;
      state_count = 0;
    }
    log->printf("total_count: %d z: %d \n", total_count, *z);
}




