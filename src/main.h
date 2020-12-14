#ifndef MAIN_H
#define MAIN_H

#include "mbed.h"
#include "LIS3DSH.h"
#include "LEDBLINK.h"
#include "USBSerial.h"
#include "FILTER.h"
#include "main.h"


#define LED_LIGHT_MASK 0x0000F000
#define LED_SHUTDOWN_MASK 0x00000000
#define MAX_COUNT 5
#define MAX_DEGREE 5


/**** define 4 kinds of exercises state ****/
typedef enum {
  SITUPS,
  PUSHUPS,
  JUMPINGJACKS,
  SQUATS
} WORKOUT;


/**** init objects ****/
FILTER filter;
LEDBLINK ledControl;
USBSerial logger;
Timer debounce;
Ticker ticker;
LIS3DSH acc(PA_7, PA_6, PA_5, PE_3); // accelerometer
PortOut portD(PortD); // 13 12 14 15  PD 0~15  
InterruptIn button(BUTTON1);


/**** Variables ****/
int16_t X, Y, Z; 
float angle, pitch, filter_angle;
volatile bool resetFlag = false;
volatile int switchExercise = 0;


/**** button Interrupt routine - is interrupt activated by a falling edge of button input ****/
void changeExercise (void) {
    if (debounce.read_ms()>20) {
      switchExercise = (switchExercise + 1) % 4;
    }
    debounce.reset(); 
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
  ledControl.blinkCircle(1); 
  debounce.start();
  button.fall(&changeExercise);
  ticker.attach(&getACCData, 0.1); //10hz
}


/**** situp routine  ****/
void situp_routine(int maxCount) {
  // 1. init value
  int count = 0;
  float last_angle = MAX_DEGREE; 

  // 2. detect sit up
  while (count < maxCount && switchExercise == SITUPS) {
    logger.printf("angle: %f count: %d \n",filter_angle, count);
    // detect
    if (last_angle < 19 && filter_angle > 44) {
      count = count +1;
      portD = 0U<<12; // each situp indication
    }
    // record previos angle
    last_angle = filter_angle;  
    wait(1.0);
    if(switchExercise != SITUPS) {
      break; 
    }
    wait(1.0);
    portD = 1U<<12; 
  }
  
  // 3. finish indication
  if (count == MAX_COUNT) {
    ledControl.blinkALL(2);
    ledControl.blinkCircle(2);
  }
}

#endif