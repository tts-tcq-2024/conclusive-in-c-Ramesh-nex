#pragma once

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

typedef void (*SendToControllerFunc)(BreachType breachType);
typedef void (*SendToEmailFunc)(BreachType breachType);

extern SendToControllerFunc sendToControllerFunc;
extern SendToEmailFunc sendToEmailFunc;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void getTemperatureLimits(CoolingType coolingType, double* lowerLimit, double* upperLimit);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void defaultSendToController(BreachType breachType);
void defaultSendToEmail(BreachType breachType);
