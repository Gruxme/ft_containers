#pragma once
#include "../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class	stack
	{
		public:
			typedef	T			value_type;
			typedef	Container	container_type;
			typedef	size_t		size_type;

			explicit			stack (const container_type& ctnr = container_type()) : c(ctnr) {}
			bool				empty() const { return c.empty(); }
			size_type			size() const { return c.size(); }
			value_type& 		top() { return c.back(); }
			const value_type&	top() const { return c.back(); }
			void				push(const value_type& val) { return c.push_back(val); }
			void				pop() {return c.pop_back(); }
			template <class type, class cntr>
  				friend bool operator== (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs);
			template <class type, class cntr>
				friend bool operator!= (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs);
			template <class type, class cntr>
				friend bool operator<  (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs);
			template <class type, class cntr>
				friend bool operator<= (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs);
			template <class type, class cntr>
				friend bool operator>  (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs);
			template <class type, class cntr>
				friend bool operator>= (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs);
		protected:
			container_type	c;
	};
	template <class type, class cntr>
  		bool operator== (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs)
		{
			return	lhs.c == rhs.c;
		}
	template <class type, class cntr>
		bool operator!= (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs)
		{
			return lhs.c != rhs.c;
		}
	template <class type, class cntr>
		bool operator<  (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs)
		{
			return lhs.c < rhs.c;
		}
	template <class type, class cntr>
		bool operator<= (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs)
		{
			return lhs.c <= rhs.c;
		}
	template <class type, class cntr>
		bool operator>  (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs)
		{
			return lhs.c > rhs.c;
		}
	template <class type, class cntr>
		bool operator>= (const stack<type,cntr>& lhs, const stack<type,cntr>& rhs)
		{
			return lhs.c >= rhs.c;
		}
}
