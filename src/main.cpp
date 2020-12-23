#include "main.h"

int main() {
  prepareBeforeLoop();
  while(1) {
    //logger.printf("--------------------program is running------------------- %d \r\n", switchExercise);
    switch (switchExercise)
    {
      case SITUPS:
        portD = 1U<<12; // green
        detect(&sp, MAX_COUNT, SITUPS, 0.5, 12);// (situp, max_count, situp enum, delay, led port)
        break;
      case PUSHUPS:
        portD = 1U<<13; //orange
        detect(&pp, MAX_COUNT, PUSHUPS, 0.1, 13);
        break;
      case JUMPINGJACKS:
        portD = 1U<<14; //red
        detect(&jj, MAX_COUNT, JUMPINGJACKS, 0.1, 14);
        break;
      case SQUATS:
        portD = 1U<<15; //blue
        detect(&st, MAX_COUNT, SQUATS, 0.1, 15);
        break;
      default:
        break;
    }
  }
}