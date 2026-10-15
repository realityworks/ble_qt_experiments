#include <gtest/gtest.h>

class SampleTest : public ::testing::Test
{
};

TEST_F(SampleTest, ExampleTest)
{
    // Given
    int a = 5;
    int b = 10;

    // When
    int sum = a + b;

    // Then
    EXPECT_EQ(sum, 15);
}
