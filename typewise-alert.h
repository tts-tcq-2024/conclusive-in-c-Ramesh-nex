#pragma once
#include <functional> // Include this for std::function

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;


BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void getTemperatureLimits(CoolingType coolingType, double* lowerLimit, double* upperLimit);

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC,
                    std::function<void(BreachType)> sendController,
                    std::function<void(BreachType)> sendEmail);
