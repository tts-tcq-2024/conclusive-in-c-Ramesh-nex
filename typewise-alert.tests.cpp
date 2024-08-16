#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test for inferBreach function
TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    // Testing normal cases
    EXPECT_EQ(inferBreach(30.0, 0.0, 35.0), NORMAL);
    EXPECT_EQ(inferBreach(36.0, 0.0, 35.0), TOO_HIGH);
    EXPECT_EQ(inferBreach(-1.0, 0.0, 35.0), TOO_LOW);
    
    EXPECT_EQ(inferBreach(40.0, 0.0, 45.0), NORMAL);
    EXPECT_EQ(inferBreach(46.0, 0.0, 45.0), TOO_HIGH);
    EXPECT_EQ(inferBreach(-1.0, 0.0, 45.0), TOO_LOW);
    
    EXPECT_EQ(inferBreach(39.0, 0.0, 40.0), NORMAL);
    EXPECT_EQ(inferBreach(41.0, 0.0, 40.0), TOO_HIGH);
    EXPECT_EQ(inferBreach(-1.0, 0.0, 40.0), TOO_LOW);
}

// Test for getTemperatureLimits function
TEST(TypeWiseAlertTestSuite, GetsTemperatureLimitsCorrectly) {
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

    // Test for out of range cooling types
    getTemperatureLimits(static_cast<CoolingType>(-1), &lowerLimit, &upperLimit);
    EXPECT_DOUBLE_EQ(lowerLimit, 0.0);
    EXPECT_DOUBLE_EQ(upperLimit, 0.0);

    getTemperatureLimits(static_cast<CoolingType>(10), &lowerLimit, &upperLimit);
    EXPECT_DOUBLE_EQ(lowerLimit, 0.0);
    EXPECT_DOUBLE_EQ(upperLimit, 0.0);
}

// Test for classifyTemperatureBreach function
TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreachCorrectly) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 30.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36.0), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1.0), TOO_LOW);
    
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46.0), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1.0), TOO_LOW);
    
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41.0), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1.0), TOO_LOW);
}

// Mocking the output functions
#include <gmock/gmock.h>
using ::testing::Exactly;

class MockAlert {
public:
    MOCK_METHOD(void, sendToController, (BreachType breachType), ());
    MOCK_METHOD(void, sendToEmail, (BreachType breachType), ());
};

// Test for checkAndAlert function
TEST(TypeWiseAlertTestSuite, CheckAndAlertSendsCorrectAlerts) {
    MockAlert mockAlert;
    
    // Set up expectations
    EXPECT_CALL(mockAlert, sendToController(TOO_LOW))
        .Times(Exactly(1));
    EXPECT_CALL(mockAlert, sendToEmail(TOO_HIGH))
        .Times(Exactly(1));
    
    // Call checkAndAlert function
    checkAndAlert(TO_CONTROLLER, {PASSIVE_COOLING}, -1.0);  // Expect sendToController
    checkAndAlert(TO_EMAIL, {HI_ACTIVE_COOLING}, 46.0);    // Expect sendToEmail
}
