#include "stack.hpp"
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
	ft::vector<int> v;
	ft::vector<int> v2;
	for (size_t i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for (size_t i = 10; i < 30; i++)
	{
		v2.push_back(i);
	}
	ft::stack<int> s(v);
	ft::stack<int> s2(v2);
	cout << (s == s2) << endl;
	cout << (s != s2) << endl;
	cout << (s > s2) << endl;
	cout << (s < s2) << endl;
	cout << (s >= s2) << endl;
	cout << (s <= s2) << endl;
	cout << "empty: " << s.empty() << endl;
	cout << "size: " << s.size() << endl;
	cout << "top: " << s.top() << endl;
	s.push(111);
	for (size_t i = 0; i < 11; i++)
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
	cout << "empty: " << s.empty() << endl;

/*-------------- STD -------------------*/
	std::cout << "--------------------------STD--------------------\n";
	std::vector<int> v_std;
	std::vector<int> v2_std;
	for (size_t i = 0; i < 10; i++)
	{
		v_std.push_back(i);
	}

	for (size_t i = 10; i < 30; i++)
	{
		v2_std.push_back(i);
	}
	std::stack<int, std::vector<int> > s_std(v_std);
	std::stack<int, std::vector<int> > s2_std(v2_std);
	cout << (s_std == s2_std) << endl;
	cout << (s_std != s2_std) << endl;
	cout << (s_std > s2_std) << endl;
	cout << (s_std < s2_std) << endl;
	cout << (s_std >= s2_std) << endl;
	cout << (s_std <= s2_std) << endl;
	cout << "empty: " << s_std.empty() << endl;
	cout << "size: " << s_std.size() << endl;
	cout << "top: " << s_std.top() << endl;
	s_std.push(111);
	for (size_t i = 0; i < 11; i++)
	{
		cout << s_std.top() << " ";
		s_std.pop();
	}
	cout << endl;
	cout << "empty: " << s_std.empty() << endl;


}
