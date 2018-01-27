#include "DoubleJoy.h"
#include <Psx.h>
#include <PS2X_lib.h>

#define dataPin 7
#define cmndPin 6
#define attPin 5
#define clockPin 4

#define PS2_DAT 11
#define PS2_CMD 9
#define PS2_SEL 8
#define PS2_CLK 10
#define pressures false
#define rumble false

Psx psx;
unsigned int data;

PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
  setupDoubleJoy();
  psx.setupPins(dataPin, cmndPin, attPin, clockPin, 1);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
}

void loop(){
  // Always be getting fresh data
  dataForController_t controller1Data = readController1();
  dataForController_t controller2Data = readController2();
  setControllerData(1, controller1Data);
  setControllerData(2, controller2Data);
}

dataForController_t readController1(void){
  
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

// Just like readController1, but with different pins
//  and 'Start' is activated by Cross and p1 start
dataForController_t readController2(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  ps2x.read_gamepad(false, vibrate);
  controllerData.dpadDownOn = ps2x.Button(PSB_PAD_DOWN);
  controllerData.dpadUpOn = ps2x.Button(PSB_PAD_UP);
  controllerData.squareOn = ps2x.Button(PSB_SQUARE);
  controllerData.l1On = ps2x.Button(PSB_L1);
  controllerData.crossOn = ps2x.Button(PSB_CROSS);
  controllerData.r1On = ps2x.Button(PSB_R1);
  controllerData.circleOn = ps2x.Button(PSB_CIRCLE);
  controllerData.l2On = ps2x.Button(PSB_L2);
  controllerData.dpadLeftOn = ps2x.Button(PSB_PAD_LEFT);
  controllerData.selectOn = ps2x.Button(PSB_SELECT);
  controllerData.startOn = ps2x.Button(PSB_START);
    
  // And return the data!
  return controllerData;
}

