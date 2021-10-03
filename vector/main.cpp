#include <iostream>
#include <vector>
#include "vector.hpp"

// bool mycomp (char c1, char c2)
// { return std::tolower(c1)<std::tolower(c2); }

int main()
{

// 	std::cout << "FT VECTOR \n";
// 	ft::vector<int> myvector;
// 	ft::vector<int>::iterator it;

// 	for (size_t i = 0; i < 10; i++)
// 	{
// 		myvector.push_back(i);
// 	}
// 	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;

// 	for (size_t i = 0; i < 11; i++)
// 	{
// 		std::cout << myvector[i] << " ";
// 	}

// 	std::cout << std::endl;
// 	std::cout << std::endl;

// 	it = myvector.begin() + 4;
// 	it = myvector.insert(it, 200);
// 	std::cout << myvector.size() << " " << myvector.capacity() << std::endl;

// 	it = myvector.begin() + 2;
// 	// myvector.insert(it, 5,200);
// 	// std::cout << myvector.size() << " " << myvector.capacity() << std::endl;

// 	ft::vector<int> other (3, 400);
// 	myvector.insert(it, other.begin(), other.end());

// 	for (size_t i = 0; i < 20; i++)
// 	{
// 		std::cout << myvector[i] << " ";
// 	}
// 	std::cout << std::endl;

// /*---------------------------STD----------------------------------*/

// 	std::cout << "STD VECTOR \n";
// 	std::vector<int> stdVector;
// 	std::vector<int>::iterator std_it;

// 	for (size_t i = 0; i < 10; i++)
// 	{
// 		stdVector.push_back(i);
// 	}
// 	std::cout << stdVector.size() << " " << stdVector.capacity() << std::endl;

// 	for (size_t i = 0; i < 11; i++)
// 	{
// 		std::cout << stdVector[i] << " ";
// 	}

// 	std::cout << std::endl;
// 	std::cout << std::endl;

// 	std_it = stdVector.begin() + 4;
// 	std_it = stdVector.insert(std_it, 200);
// 	std::cout << stdVector.size() << " " << stdVector.capacity() << std::endl;

// 	std_it = stdVector.begin() + 2;
// 	// std_it = stdVector.insert(std_it, 5, 200);
// 	// std::cout << stdVector.size() << " " << stdVector.capacity() << std::endl;

// 	std::vector<int> stdOther (3, 400);
// 	stdVector.insert(std_it, stdOther.begin(), stdOther.end());

// 	for (size_t i = 0; i < 20; i++)
// 	{
// 		std::cout << stdVector[i] << " ";
// 	}
// 	std::cout << std::endl;

// 	char foo[]="Apple";
//  	char bar[]="apartment";

// 	std::cout << std::boolalpha;

//   std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

//   std::cout << "Using default comparison (operator<): ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
//   std::cout << '\n';

//   std::cout << "Using mycomp as comparison object: ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
//   std::cout << '\n';

	// ft::vector<int> foo (3,100);
	// ft::vector<int> bar (2,200);

	// if (foo==bar) std::cout << "foo and bar are equal\n";
  	// if (foo!=bar) std::cout << "foo and bar are not equal\n";
  	// if (foo< bar) std::cout << "foo is less than bar\n";
  	// if (foo> bar) std::cout << "foo is greater than bar\n";
  	// if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  	// if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	
	// ft::vector<int> foo (5, 300);
	// ft::vector<int> bar (3, 400);

	// std::cout << "size : " << foo.size() << ", " << bar.size() << std::endl; 
	// std::cout << "capacity : " << foo.capacity() << ", " << bar.capacity() << std::endl;
	// for (size_t i = 0; i < foo.size(); i++)
	// 	std::cout << &(foo[i]) << " : " << foo[i] << " ";
	// std::cout << std::endl;
	// for (size_t i = 0; i < bar.size(); i++)
	// 	std::cout << &(bar[i]) << " : " << bar[i] << " ";
	// std::cout << std::endl;

	// ft::swap(foo, bar);

	// std::cout << "size : " << foo.size() << ", " << bar.size() << std::endl; 
	// std::cout << "capacity : " << foo.capacity() << ", " << bar.capacity() << std::endl;
	// for (size_t i = 0; i < foo.size(); i++)
	// 	std::cout << &(foo[i]) << " : " << foo[i] << " ";
	// std::cout << std::endl;
	// for (size_t i = 0; i < bar.size(); i++)
	// 	std::cout << &(bar[i]) << " : " << bar[i] << " ";
	// std::cout << std::endl;

	std::vector<int> foo;
	for (size_t i = 0; i < 10; i++)
		foo.push_back(i);
	for (size_t i = 0; i < 20; i++)
		std::cout << foo[i] << " ";
	std::cout << std::endl;

	foo.erase(foo.begin() + 2, foo.begin() + 5);
	for (size_t i = 0; i < 20; i++)
		std::cout << foo[i] << " ";
	std::cout << std::endl;
	return 0;
}
