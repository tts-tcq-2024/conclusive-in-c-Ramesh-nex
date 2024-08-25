#include "typewise-alert.h"
#include <stdio.h>

const double COOLING_LIMITS[][2] = 
{
    {0.0, 35.0},  // PASSIVE_COOLING
    {0.0, 45.0},  // HI_ACTIVE_COOLING
    {0.0, 40.0}   // MED_ACTIVE_COOLING
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit)
{
  if(value < lowerLimit)
  {
    return TOO_LOW;
  }
  if(value > upperLimit)
  {
    return TOO_HIGH;
  }
  return NORMAL;
}


void getTemperatureLimits(CoolingType coolingType, double* lowerLimit, double* upperLimit)
{
  if (coolingType >= PASSIVE_COOLING && coolingType <= MED_ACTIVE_COOLING)
  {
    *lowerLimit = COOLING_LIMITS[coolingType][0];
    *upperLimit = COOLING_LIMITS[coolingType][1];
  } 
  else
  {
    *lowerLimit = 0;
    *upperLimit = 0;
  }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  double lowerLimit, upperLimit;
  getTemperatureLimits(coolingType, &lowerLimit, &upperLimit);
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}


void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  if (alertTarget == TO_CONTROLLER)
  {
    sendToController(breachType);
  }
  else if (alertTarget == TO_EMAIL) 
  {
    sendToEmail(breachType);
  }
}

void sendToController(BreachType breachType)
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}
void sendToEmail(BreachType breachType)
{
  const char* recipient = "a.b@c.com";
  if (breachType == TOO_LOW) 
  {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too low\n");
  }
  else if (breachType == TOO_HIGH) 
  {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too high\n");
  }
}
