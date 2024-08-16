#include "typewise-alert.h"
#include <stdio.h>

const double COOLING_LIMITS[][2] = {
    {0.0, 35.0},  // PASSIVE_COOLING
    {0.0, 45.0},  // HI_ACTIVE_COOLING
    {0.0, 40.0}   // MED_ACTIVE_COOLING
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}
// Function to get temperature limits based on cooling type
void getTemperatureLimits(CoolingType coolingType, double* lowerLimit, double* upperLimit) {
  if (coolingType >= PASSIVE_COOLING && coolingType <= MED_ACTIVE_COOLING) {
    *lowerLimit = COOLING_LIMITS[coolingType][0];
    *upperLimit = COOLING_LIMITS[coolingType][1];
  } else {
    *lowerLimit = 0;
    *upperLimit = 0;
  }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  double lowerLimit, upperLimit;
  getTemperatureLimits(coolingType, &lowerLimit, &upperLimit);
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

// Function to check temperature and send appropriate alert
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  
  // Choose the appropriate alert function based on alertTarget
  if (alertTarget == TO_CONTROLLER) {
    sendToController(breachType);
  } else if (alertTarget == TO_EMAIL) {
    sendToEmail(breachType);
  }
}
