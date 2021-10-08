
#include <vector>
#include <string>
#include "vector/vector.hpp"


int main()
{
    std::string str, ft_str;
	ft::vector<std::string>::size_type  s, ft_s;
	ft::vector<std::string>::size_type  c, ft_c;
	bool cond;
	std::vector<std::string>     v1(15, "hello");
            std::vector<std::string>    v(20, "string");
            ft::vector<std::string>     ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
	std::cout << (cond == true) << std::endl;
}
