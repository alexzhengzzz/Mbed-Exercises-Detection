#include "EXEC.h"

EXEC::EXEC(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise) {
    led = new LEDBLINK();
    pd = new PortOut(PortD);
    x = X;
    y = Y;
    z = Z;
    ag = angle;
    sw = switchExercise;
    state_count = 0;
    total_count = 0;
}

void EXEC::setLogger(USBSerial* logger) {
    log = logger;
}

void EXEC::indicate(int port, float time) {
    float sum = 0;
    while (sum < time) {
        *pd = 0U << port;
        wait(.1);
        *pd = 1U << port;
        wait(.1);
        sum = sum + 0.2; 
    }
    *pd = 0U << port; // reset
}

void EXEC::finish() {
    led->blinkALL(2);
    led->blinkCircle(2);
}

void EXEC::reset() {
  state_count = 0;
  total_count = 0;
}



