#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "typewise-alert.h"

// Mocking the global functions
class MockAlert {
public:
    MOCK_METHOD(void, sendToController, (BreachType), ());
    MOCK_METHOD(void, sendToEmail, (BreachType), ());
};

MockAlert mockAlert;

// These functions will call the mock functions
void sendToController(BreachType breachType) {
    mockAlert.sendToController(breachType);
}

void sendToEmail(BreachType breachType) {
    mockAlert.sendToEmail(breachType);
}

// Test Case for inferBreach
TEST(TemperatureTest, InferBreach) {
    EXPECT_EQ(inferBreach(20.0, 0.0, 35.0), NORMAL);
    EXPECT_EQ(inferBreach(-5.0, 0.0, 35.0), TOO_LOW);
    EXPECT_EQ(inferBreach(40.0, 0.0, 35.0), TOO_HIGH);
}

// Test Case for getTemperatureLimits
TEST(TemperatureTest, GetTemperatureLimits) {
    double lowerLimit, upperLimit;

    getTemperatureLimits(PASSIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_DOUBLE_EQ(lowerLimit, 0.0);
    EXPECT_DOUBLE_EQ(upperLimit, 35.0);

    getTemperatureLimits(HI_ACTIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_DOUBLE_EQ(lowerLimit, 0.0);
    EXPECT_DOUBLE_EQ(upperLimit, 45.0);

    getTemperatureLimits(MED_ACTIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_DOUBLE_EQ(lowerLimit, 0.0);
    EXPECT_DOUBLE_EQ(upperLimit, 40.0);

    getTemperatureLimits(static_cast<CoolingType>(999), &lowerLimit, &upperLimit);
    EXPECT_DOUBLE_EQ(lowerLimit, 0.0);
    EXPECT_DOUBLE_EQ(upperLimit, 0.0);
}

// Test Case for classifyTemperatureBreach
TEST(TemperatureTest, ClassifyTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -5.0), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 40.0), TOO_HIGH);

    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 30.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50.0), TOO_HIGH);

    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 20.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45.0), TOO_HIGH);
}

// Test Case for checkAndAlert
TEST(TemperatureTest, CheckAndAlert) {
    {
        InSequence seq;

        // Expectations for mock functions
        EXPECT_CALL(mockAlert, sendToController(TOO_LOW))
            .Times(1);
        EXPECT_CALL(mockAlert, sendToEmail(TOO_HIGH))
            .Times(1);

        BatteryCharacter batteryChar;
        batteryChar.coolingType = PASSIVE_COOLING;
        checkAndAlert(TO_CONTROLLER, batteryChar, -5.0); // Triggers sendToController
        checkAndAlert(TO_EMAIL, batteryChar, 40.0); // Triggers sendToEmail
    }
}
