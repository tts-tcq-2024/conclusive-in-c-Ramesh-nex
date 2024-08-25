#include "typewise-alert.h"
#include <stdio.h>

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
