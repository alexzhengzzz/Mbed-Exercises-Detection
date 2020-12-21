#include "main.h"

int main() {
  prepareBeforeLoop();
  while(1) {
    logger.printf("--------------------program is running------------------- %d \r\n", switchExercise);
    
    switch (switchExercise)
    {
      case SITUPS:
        portD = 1U<<12; // green
        sitUpNum += detect(&sp, 5, SITUPS, 0.5, 12);
        break;
      case PUSHUPS:
        portD = 1U<<13; //orange
        pushUpNum += detect(&pp, 5, PUSHUPS, 0.1, 15);
        break;
      case JUMPINGJACKS:
        portD = 1U<<14; //red
        jumpNum += detect(&jj, 10, JUMPINGJACKS, 0.1, 15);
        break;
      case SQUATS:
        portD = 1U<<15; //blue
        squatNum += detect(&st, 5, SQUATS, 0.1, 15);
        break;
      default:
        logger.printf("something wrong happened or exercise not start");
        break;
    }
    // logger.printf("3-axis: %d, %d, %d\n", X, Y, Z);
    // logger.printf("angle: %f\n", angle);
  }
}