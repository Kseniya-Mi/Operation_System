#include <iostream>
#include <vector>

void min_max(int& min_value, int& max_value, std::vector<int> vec)
{
	max_value = vec[0];
	min_value = vec[0];

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] <= min_value)
		{
			min_value = vec[i];
		}

		if (vec[i] >= max_value)
		{
			max_value = vec[i];
		}

	}

}


void average(int& average, std::vector<int> vec)
{
	int sum_of_elements = 0;

	for (int i = 0; i < vec.size(); i++)
	{
		sum_of_elements += vec[i];
	}

	average = sum_of_elements / vec.size();

}