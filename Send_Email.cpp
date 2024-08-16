
void sendToEmail(BreachType breachType) {
  const char* recipient = "a.b@c.com";

  // Prepare and print the message based on the breach type
  if (breachType == TOO_LOW) {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too low\n");
  } else if (breachType == TOO_HIGH) {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too high\n");
  }
}
