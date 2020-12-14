#include "main.h"

int main() {
  prepareBeforeLoop();
  while(1) {
    logger.printf("--------------------program is running------------------- \r\n");
    switch (switchExercise)
    {
      case SITUPS:
        portD = 1U<<12; // green
        detect(&sp, 5, SITUPS, 1.0, 12);
        break;
      case PUSHUPS:
        portD = 1U<<13; //orange
        break;
      case JUMPINGJACKS:
        portD = 1U<<14; //red
        break;
      case SQUATS:
        portD = 1U<<15; //blue
        break;
      default:
        logger.printf("something wrong happened or exercise not start");
        break;
    }
    // logger.printf("3-axis: %d, %d, %d\n", X, Y, Z);
    // logger.printf("angle: %f\n", angle);
  }
}