#include "../NodeUtility.hpp"

#include <gtest/gtest.h>

TEST(ExampleTests, BasicAssertions) {
    //EXPECT_EQ(Add(1, 2), 3);
    int ClassInstances[2] = {4, 5};
    float ExpectedGini = (4. / 9.) * (5. / 9.) + (5. / 9.) * (4. / 9.);
    EXPECT_FLOAT_EQ(GiniImpurity(2, ClassInstances), ExpectedGini);

    int ClassInstances2[2] = {5, 1};
    float ExpectedGini2 = 2. * (1. / 6.) * (5. / 6.);
    EXPECT_FLOAT_EQ(GiniImpurity(2, ClassInstances2), ExpectedGini2);

    int ClassInstances3[] = {5, 0, 5};
    float ExpectedGini3 = 2. * (5. / 10.) * (5. / 10.);
    EXPECT_FLOAT_EQ(GiniImpurity(3, ClassInstances3), ExpectedGini3);
}