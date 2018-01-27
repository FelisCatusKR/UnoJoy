#include "UnoJoy.h"
#include <Psx.h>

#define dataPin 7
#define cmndPin 6
#define attPin 5
#define clockPin 4

Psx psx;
unsigned int data;

void setup(){
  setupUnoJoy();
  psx.setupPins(dataPin, cmndPin, attPin, clockPin, 1);
}

void loop(){
  // Always be getting fresh data
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

dataForController_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  data = psx.read();
  controllerData.dpadDownOn = data&psxDown;
  controllerData.dpadUpOn = data&psxUp;
  controllerData.squareOn = data&psxSqu;
  controllerData.l1On = data&psxL1;
  controllerData.crossOn = data&psxX;
  controllerData.r1On = data&psxR1;
  controllerData.circleOn = data&psxO;
  controllerData.l2On = data&psxL2;
  controllerData.dpadLeftOn = data&psxLeft;
  controllerData.selectOn = data&psxSlct;
  controllerData.startOn = data&psxStrt;
  
  // And return the data!
  return controllerData;
}
