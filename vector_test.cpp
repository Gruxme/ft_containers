#include <vector>
#include "vector.hpp"
#include <iostream>

int	main(void)
{
	std::vector<int>	defaultV;
	std::vector<int>	fillV(10, 5);
	ft::vector<int>		defaultC;
	ft::vector<int>		fillC(10, 5);

	// for (size_t i = 0; i < 20; i++)
	// {
	// 	fillV.push_back(i);
	// 	std::cout << "Vector size: " << fillV.size() << std::endl;
	// 	std::cout << "Vector capacity: " << fillV.capacity() << std::endl;
	// }
	std::cout << "Vector size: " << fillC.size() << std::endl;
	std::cout << "Vector capacity: " << fillC.capacity() << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << "Value " << i << ": " << fillC[i] << std::endl;
	}
	// fillV.resize(40, 5);
	// std::cout << "Vector size: " << fillV.size() << std::endl;
	// std::cout << "Vector capacity: " << fillV.capacity() << std::endl;
	// fillV.resize(10);
	// std::cout << "Vector size: " << fillV.size() << std::endl;
	// std::cout << "Vector capacity: " << fillV.capacity() << std::endl;
	// fillV.reserve(50);
	// std::cout << "Vector size: " << fillV.size() << std::endl;
	// std::cout << "Vector capacity: " << fillV.capacity() << std::endl;
	// std::cout << "Vector size: " << defaultV.size() << std::endl;
	// std::cout << "Vector capacity: " << defaultV.capacity() << std::endl;
	// std::cout << "Vector max size: " << defaultV.max_size() << std::endl;

	// std::cout << "Vector size: " << fillV.size() << std::endl;
	// std::cout << "Vector capacity: " << fillV.capacity() << std::endl;
	// std::cout << "Vector max size: " << fillV.max_size() << std::endl;
}
