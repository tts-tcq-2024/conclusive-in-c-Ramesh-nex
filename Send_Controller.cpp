#include "BreachType.h"
// Function to simulate sending an alert to the controller
void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}
