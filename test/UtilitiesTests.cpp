#include "../Utilities.hpp"

#include <gtest/gtest.h>

TEST(SumIntArray, UtilitiesTests) {
    // two positive values
    int NumClasses = 2;
    int ClassInstances[] = {4, 5};
    EXPECT_EQ(SumIntArray(NumClasses, ClassInstances), 9);

    // one negative value
    int ClassInstancesNeg[] = {4, -1};
    EXPECT_EQ(SumIntArray(NumClasses, ClassInstancesNeg), 3);
}