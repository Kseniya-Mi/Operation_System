#include "pch.h"
#include "D:\Program\creating_threads\creating_threads\Func.cpp"

TEST(MinMaxTest, ReturnsCorrectPlusMinMaxValue) 
{
	std::vector<int> vec = { 5, 2, 9, 1, 3 };
	int min, max;
    
	min_max(min, max, vec);
    
	ASSERT_EQ(min, 1);
	ASSERT_EQ(max, 9);
}

TEST(MinMaxTest, ReturnsCorrectMinusMinMaxValue) 
{
	std::vector<int> vec = { -5, -2, -9, -1, -3 };
	int min, max;
    
	min_max(min, max, vec);
    
	ASSERT_EQ(min, -9);
	ASSERT_EQ(max, -1);
}

TEST(MinMaxTest, MinMaxSameValueTest) 
{
	std::vector<int> vec = { 1,1,1 };
	int min, max;
    
	min_max(min, max, vec);
    
	ASSERT_EQ(min, 1);
	ASSERT_EQ(max, 1);
}

TEST(AverageTest, BasicTest) 
{
	std::vector<int> vec = { 3, 1, 4, 1, 5, 9 };
	int aver = 0;
    
	average(aver, vec);
    
	ASSERT_EQ(aver, 3);
}

TEST(AverageTest, LargeVectorTest) 
{
	std::vector<int> vec(10000, 5);
	int aver = 0;
    
	average(aver, vec);
    
	ASSERT_EQ(aver, 5);
}
