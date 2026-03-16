#include <iostream>
#include <vector>
#include <array>

#include "MyVector.hpp"




int main()
{

	MyVector<int> vec = { 1, 2, 5, 6 };

	std::array<int, 2> arr = { 1,2 };
	
	vec.insert(vec.begin() + 2, arr.begin(), arr.end());

	for (auto v : vec)
	{
		std::cout << v << std::endl;
	}


	return 0;
}