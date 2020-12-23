#include "LEDBLINK.h"
#define LED_LIGHT_MASK 0x0000F000 // set all led to 1
#define LED_SHUTDOWN_MASK 0x00000000 // set all led to 0
int PIN_BASE = 12; 
PortOut p(PortD); // led is at PD12 PD13 PD14 PD15
DigitalOut led3(LED3);
DigitalOut led4(LED4);
DigitalOut led5(LED5);
DigitalOut led6(LED6);

LEDBLINK::LEDBLINK() {
}

// blink all led
void LEDBLINK::blinkALL(int count) {
    while (count >= 0) {
        p = LED_LIGHT_MASK;
        wait(1.0);
        p = LED_SHUTDOWN_MASK;
        wait(1.0);
        count--;
    }
    p = LED_SHUTDOWN_MASK; // reset
}

void LEDBLINK::blinkCircle(int count) {
    while (count >= 0) {
        p = 1U<<12;
        wait(.2);
        p = 1U<<13;
        wait(.2);
        p = 1U<<14;
        wait(.2);
        p = 1U<<15;
        wait(.2);
        count--;
    }
    p = LED_SHUTDOWN_MASK; // reset
}

void LEDBLINK::toggleOneLed(int count, int pin) {
    int pinNumber = PIN_BASE + pin;
    while (count > 0) {
        p = 1U << pinNumber;
        wait(.5);
        p = 0U << pinNumber;
        wait(.5);
        count--;
    }
    p = 0U << pinNumber; // reset
}

void LEDBLINK::showAllRoutineResult(int sitUpNum, int pushUpNum, int jumpNum, int SquatNum) {
    if (isRoutineFinished(sitUpNum)) led3 = 1;
    if (isRoutineFinished(pushUpNum)) led4 = 1;
    if (isRoutineFinished(jumpNum)) led5 = 1;
    if (isRoutineFinished(SquatNum)) led6 = 1;
    wait_ms(3000);
    p = LED_SHUTDOWN_MASK;
}

bool LEDBLINK::isRoutineFinished(int num) {
    if (num != 0 && num % 15 == 0) {
        return true;
    }
    return false;
}




