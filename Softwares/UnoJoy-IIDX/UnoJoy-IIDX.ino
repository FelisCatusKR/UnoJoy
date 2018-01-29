#include <PSXPad.h>
#include "UnoJoy.h"

// You can change digital pin for Attention at here
byte lbAttPinNos[] = {2};
PSXPad_KeyState_t tKeyState;

void setup(){
  setupUnoJoy();
  PSXPads.begin(1, lbAttPinNos);
}

void loop(){
  // Always be getting fresh data
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

dataForController_t getControllerData(void){
  // Set up a place for our controller data
  // Use the getBlankDataForController() function, since
  // just declaring a fresh dataForController_t tends
  // to get you one filled with junk from other, random
  // values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  PSXPads.pool();
  PSXPads.lpcPads[0]->getKeyState(&tKeyState);
  controllerData.dpadDownOn = tKeyState.bD;
  controllerData.dpadUpOn = tKeyState.bU;
  controllerData.squareOn = tKeyState.bSqr;
  controllerData.l1On = tKeyState.bL1;
  controllerData.crossOn = tKeyState.bCrs;
  controllerData.r1On = tKeyState.bR1;
  controllerData.circleOn = tKeyState.bCir;
  controllerData.l2On = tKeyState.bL2;
  controllerData.dpadLeftOn = tKeyState.bL;
  controllerData.selectOn = tKeyState.bSel;
  controllerData.startOn = tKeyState.bStt;
  // And return the data!
  return controllerData;
}
