#include <vector>
#include "vector.hpp"
#include <iostream>

int	main(void)
{
	// std::vector<int>	std_new3;
	// ft::vector<int>		ft_new3;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	std_new3.push_back(i);
	// 	ft_new3.push_back(i);
	// }
	
	// std::vector<int>::iterator std_it3(std_new3.begin());
    // ft::vector<int>::iterator ft_it3(ft_new3.begin());

    // std::cout << *(4 + std_it3) << std::endl;
    // std::cout << *(4 + ft_it3) << std::endl;
    // std::cout << *std_it3++ << std::endl;
    // std::cout << *ft_it3++ << std::endl;
    // std::cout << *std_it3 << std::endl;
    // std::cout << *ft_it3 << std::endl;
	// 5 + std_it3;
	// 5 + ft_it3;
	// std::cout << *std_it3 << std::endl;
    // std::cout << *ft_it3 << std::endl;
	// std_it3 - 5;
	// ft_it3 - 5;
	// std::cout << *std_it3 << std::endl;
    // std::cout << *ft_it3 << std::endl;

	/*---------------------------asignement test------------------------------*/
	ft::vector<int>	vec1;
	// ft::vector<int>::iterator	it;
	ft::vector<int>::reverse_iterator rev_it;
	// ft::vector<int>	vec2(20, 42);
	for (size_t i = 1; i < 10; i++)
		vec1.push_back(i);
	for (size_t i = 0; i < vec1.size(); i++)
		std::cout << "vec1 value " << i << ": " << vec1[i] << std::endl;
	rev_it = vec1.rend();
	std::cout << rev_it[-8] << std::endl;
	// vec2 = vec1;
	// std::cout << std::endl;
	// for (size_t i = 0; i < vec2.capacity(); i++)
	// 	std::cout << "vec2 value " << i << ": " << vec2[i] << std::endl;
	return 0;
}
