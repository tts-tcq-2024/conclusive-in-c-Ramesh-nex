#include "typewise-alert.h"
#include <stdio.h>

const double PASSIVE_COOLING_LOWER_LIMIT = 0.0;
const double PASSIVE_COOLING_UPPER_LIMIT = 35.0;
const double HI_ACTIVE_COOLING_LOWER_LIMIT = 0.0;
const double HI_ACTIVE_COOLING_UPPER_LIMIT = 45.0;
const double MED_ACTIVE_COOLING_LOWER_LIMIT = 0.0;
const double MED_ACTIVE_COOLING_UPPER_LIMIT = 40.0;

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void getTemperatureLimits(CoolingType coolingType, double* lowerLimit, double* upperLimit) {
  switch (coolingType) {
    case PASSIVE_COOLING:
      *lowerLimit = PASSIVE_COOLING_LOWER_LIMIT;
      *upperLimit = PASSIVE_COOLING_UPPER_LIMIT;
      break;
    case HI_ACTIVE_COOLING:
      *lowerLimit = HI_ACTIVE_COOLING_LOWER_LIMIT;
      *upperLimit = HI_ACTIVE_COOLING_UPPER_LIMIT;
      break;
    case MED_ACTIVE_COOLING:
      *lowerLimit = MED_ACTIVE_COOLING_LOWER_LIMIT;
      *upperLimit = MED_ACTIVE_COOLING_UPPER_LIMIT;
      break;
    default:
      *lowerLimit = 0;
      *upperLimit = 0;
      break;
  }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  double lowerLimit, upperLimit;
  getTemperatureLimits(coolingType, lowerLimit, upperLimit);
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

// Function to simulate sending an alert to the controller
void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

// Function to simulate sending an alert via email
void sendToEmail(BreachType breachType) {
  const char* recipient = "a.b@c.com";
  switch (breachType) {
    case TOO_LOW:
      printf("To: %s\n", recipient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recipient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
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
