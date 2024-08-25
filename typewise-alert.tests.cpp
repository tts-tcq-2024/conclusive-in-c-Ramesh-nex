#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "typewise-alert.h"

using namespace testing;

// Mock class to replace the alert functions
class MockAlert {
public:
    MOCK_METHOD(void, sendToController, (BreachType), ());
    MOCK_METHOD(void, sendToEmail, (BreachType), ());
};

// Create a global mock object
MockAlert mockAlert;

// Set the function pointers to use the mock implementations
SendToControllerFunc sendToControllerFunc = [](BreachType breachType) {
    mockAlert.sendToController(breachType);
};
SendToEmailFunc sendToEmailFunc = [](BreachType breachType) {
    mockAlert.sendToEmail(breachType);
};

// Test for normal temperature in passive cooling
TEST(TemperatureTest, NormalTemperatureInPassiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(NORMAL)).Times(0);
    EXPECT_CALL(mockAlert, sendToEmail(NORMAL)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, 25.0); // Should not trigger any alert
    checkAndAlert(TO_EMAIL, batteryChar, 25.0);     // Should not trigger any alert
}

// Test for too high temperature in passive cooling
TEST(TemperatureTest, TooHighTemperatureInPassiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(TOO_HIGH)).Times(1);
    EXPECT_CALL(mockAlert, sendToEmail(TOO_HIGH)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, 36.0); // Triggers sendToController
    checkAndAlert(TO_EMAIL, batteryChar, 36.0);     // No email alert
}

// Test for too low temperature in passive cooling
TEST(TemperatureTest, TooLowTemperatureInPassiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(TOO_LOW)).Times(1);
    EXPECT_CALL(mockAlert, sendToEmail(TOO_LOW)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, -1.0); // Triggers sendToController
    checkAndAlert(TO_EMAIL, batteryChar, -1.0);     // No email alert
}

// Test for normal temperature in hi-active cooling
TEST(TemperatureTest, NormalTemperatureInHiActiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(NORMAL)).Times(0);
    EXPECT_CALL(mockAlert, sendToEmail(NORMAL)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = HI_ACTIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, 30.0); // Should not trigger any alert
    checkAndAlert(TO_EMAIL, batteryChar, 30.0);     // Should not trigger any alert
}

// Test for too high temperature in hi-active cooling
TEST(TemperatureTest, TooHighTemperatureInHiActiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(TOO_HIGH)).Times(1);
    EXPECT_CALL(mockAlert, sendToEmail(TOO_HIGH)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = HI_ACTIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, 46.0); // Triggers sendToController
    checkAndAlert(TO_EMAIL, batteryChar, 46.0);     // No email alert
}

// Test for too low temperature in hi-active cooling
TEST(TemperatureTest, TooLowTemperatureInHiActiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(TOO_LOW)).Times(1);
    EXPECT_CALL(mockAlert, sendToEmail(TOO_LOW)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = HI_ACTIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, -1.0); // Triggers sendToController
    checkAndAlert(TO_EMAIL, batteryChar, -1.0);     // No email alert
}

// Test for normal temperature in med-active cooling
TEST(TemperatureTest, NormalTemperatureInMedActiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(NORMAL)).Times(0);
    EXPECT_CALL(mockAlert, sendToEmail(NORMAL)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = MED_ACTIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, 35.0); // Should not trigger any alert
    checkAndAlert(TO_EMAIL, batteryChar, 35.0);     // Should not trigger any alert
}

// Test for too high temperature in med-active cooling
TEST(TemperatureTest, TooHighTemperatureInMedActiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(TOO_HIGH)).Times(1);
    EXPECT_CALL(mockAlert, sendToEmail(TOO_HIGH)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = MED_ACTIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, 41.0); // Triggers sendToController
    checkAndAlert(TO_EMAIL, batteryChar, 41.0);     // No email alert
}

// Test for too low temperature in med-active cooling
TEST(TemperatureTest, TooLowTemperatureInMedActiveCooling) {
    EXPECT_CALL(mockAlert, sendToController(TOO_LOW)).Times(1);
    EXPECT_CALL(mockAlert, sendToEmail(TOO_LOW)).Times(0);

    BatteryCharacter batteryChar;
    batteryChar.coolingType = MED_ACTIVE_COOLING;

    checkAndAlert(TO_CONTROLLER, batteryChar, -1.0); // Triggers sendToController
    checkAndAlert(TO_EMAIL, batteryChar, -1.0);     // No email alert
}
