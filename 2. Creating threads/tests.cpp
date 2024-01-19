#include "pch.h"
#include "D:\Program\creating_threads\creating_threads\main.cpp"

TEST(MinimValueTest1, ReturnsCorrectMinValue)
{
    int array[5] = { 5, 2, 9, 1, 3 };

    int result = minim_value(array);

    EXPECT_EQ(1, result);
}

TEST(MinimValueTest2, ReturnsCorrectMinValue)
{
    int array[5] = { -5, -2, -9, -1, -3 };

    int result = minim_value(array);

    EXPECT_EQ(-9, result);
}

TEST(MaximValueTest1, ReturnsMaximumValue)
{
    int array[5] = { 10, 5, 8, 12, 3 };

    int result = maxim_value(array);

    EXPECT_EQ(result, 12); 
}

TEST(MaximValueTest2, ReturnsMaximumValue)
{
    int array[] = { -10, -5, -8, -12, -3 };

    int result = maxim_value(array);

    EXPECT_EQ(result, -3); 
}