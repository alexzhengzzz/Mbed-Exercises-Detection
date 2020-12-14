#include "EXEC.h"

EXEC::EXEC(USBSerial* logger, LEDBLINK* ledControl, PortOut* portD, int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise) {
    log = logger;
    led = ledControl;
    pd = portD;
    count = 0;
    x = X;
    y = Y;
    z = Z;
    ag = angle;
    sw = switchExercise;
}


void EXEC::finish() {
    led->blinkALL(2);
    led->blinkCircle(2);
}



