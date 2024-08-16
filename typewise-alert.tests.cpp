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


