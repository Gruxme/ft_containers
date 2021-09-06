#include <vector>
#include "vector.hpp"
#include <iostream>

int	main(void)
{
	std::vector<int>	def;
	std::vector<int>	fill(10, 5);
	std::vector<int>	iter_construct(fill.begin(), fill.end());
	std::vector<int>::iterator	it;
	std::vector<int>::reverse_iterator	rev_it;


	ft::vector<int>		my_def;
	ft::vector<int>		my_fill(10, 5);
	ft::vector<int>		my_iter_construct(my_fill.begin(), my_fill.end());
	ft::vector<int>::iterator	my_it;
	ft::vector<int>::reverse_iterator	my_rev_it;

	rev_it = fill.rbegin();
	rev_it -= 3;
	std::cout << "rev_It value: " << *rev_it << " on address: " << std::endl;
	std::cout << "size: " << fill.size() << " capacity: " << fill.capacity() << std::endl;
	try
	{
		std::cout << "element at index 9: " << fill.at(1) << std::endl;
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	my_rev_it = my_fill.rbegin();
	my_rev_it -= 3;
	std::cout << "My rev_It value: " << *my_rev_it << " on address: " << std::endl;
	std::cout << "My size: " << fill.size() << " My capacity: " << fill.capacity() << std::endl;
	try
	{
		std::cout << "element at index 9: " << my_fill.at(1) << std::endl;
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << '\n';
	}
}
