#include <mbed.h>
#include "LIS3DSH.h"
#include "LEDBLINK.h"
#include "USBSerial.h"
#include "FILTER.h"

#define LED_LIGHT_MASK 0x0000F000
#define LED_SHUTDOWN_MASK 0x00000000
#define MAX_COUNT 5

FILTER filter;
LIS3DSH acc(PA_7, PA_6, PA_5, PE_3); // accelerometer
PortOut portD(PortD); // 13 12 14 15  PD 0~15     
InterruptIn button(BUTTON1);
LEDBLINK ledControl;
USBSerial logger;
Timer debounce;
Ticker ticker;
int16_t X, Y, Z; 
float angle, pitch, filter_angle;
volatile bool resetFlag = false;
volatile int switchExercise = 0;


/**** define 4 kinds of exercises state ****/
typedef enum {
  SITUPS,
  PUSHUPS,
  JUMPINGJACKS,
  SQUATS
} WORKOUT;

/**** button Interrupt routine - is interrupt activated by a falling edge of button input ****/
void onUp (void) {
    if (debounce.read_ms()>20) {
      switchExercise = (switchExercise + 1) % 4;
    }
    debounce.reset(); // reset debounce timeer;
}

/**** use ticker to deal with angle  ****/
void getACCData()
{
    acc.ReadData(&X, &Y, &Z);
    acc.ReadAngles(&angle, &pitch); 
    filter_angle = filter.filterAngle(Z);
}

/**** Prepare Before Loop  ****/
void prepareBeforeLoop() {
  ledControl.blinkCircle(1); // check the device and connectivity
  debounce.start();
  button.fall(&onUp);
  ticker.attach(&getACCData, 0.1); //10hz
}

/**** situp routine  ****/
void situp_routine(int max) {
  int count = 0;
  float last_angle = 180; 
  while (count < max && switchExercise == SITUPS) {
    logger.printf("angle: %f count: %d \n",filter_angle, count);
    if (last_angle < 19 && filter_angle > 44) {
      count = count +1;
      portD = 0U<<12; // green
    }
    last_angle = filter_angle;
    wait(2.0);
    portD = 1U<<12; // green
  }
  if (count == MAX_COUNT) {
    ledControl.blinkALL(2);
    ledControl.blinkCircle(2);
  }
}

/**** main ****/
int main() {
  prepareBeforeLoop();
  while(1) {
    logger.printf("--------------------program is running------------------- \r\n");
    switch (switchExercise)
    {
      case SITUPS:
        portD = 1U<<12; // green
        situp_routine(MAX_COUNT);
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