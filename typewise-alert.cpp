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
    if (value < lowerLimit) return TOO_LOW;
    if (value > upperLimit) return TOO_HIGH;
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
