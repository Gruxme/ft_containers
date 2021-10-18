/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:50 by abiari            #+#    #+#             */
/*   Updated: 2021/10/16 14:38:52 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <type_traits>

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if {};
	
	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template <class T> struct is_integral { static const bool value = false; };
	template <> struct is_integral<bool> { static const bool value = true; };
	template <> struct is_integral<char> { static const bool value = true; };
	template <> struct is_integral<char16_t> { static const bool value = true; };
	template <> struct is_integral<char32_t> { static const bool value = true; };
	template <> struct is_integral<wchar_t> { static const bool value = true; };
	template <> struct is_integral<signed char> { static const bool value = true; };
	template <> struct is_integral<short int> { static const bool value = true; };
	template <> struct is_integral<int> { static const bool value = true; };
	template <> struct is_integral<long int> { static const bool value = true; };
	template <> struct is_integral<long long int> { static const bool value = true; };
	template <> struct is_integral<unsigned char> { static const bool value = true; };
	template <> struct is_integral<unsigned short int> { static const bool value = true; };
	template <> struct is_integral<unsigned int> { static const bool value = true; };
	template <> struct is_integral<unsigned long int> { static const bool value = true; };
	template <> struct is_integral<unsigned long long int> { static const bool value = true; };

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
									typename enable_if<!is_integral<InputIterator2>::value, InputIterator2>::type = InputIterator2(),
									typename enable_if<!is_integral<InputIterator1>::value, InputIterator1>::type = InputIterator1())
	{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return false;
				else if (*first1 < *first2)
					return true;
				++first1;
				++first2;
			}
			return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp,
									typename enable_if<!is_integral<InputIterator2>::value, InputIterator2>::type = InputIterator2(),
									typename enable_if<!is_integral<InputIterator1>::value, InputIterator1>::type = InputIterator1())
	{
			while (first1 != last1)
			{
				if (first2 == last2 || comp(*first2, *first1))
					return false;
				else if (comp(*first1, *first2))
					return true;
				++first1;
				++first2;
			}
			return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
	  			typename enable_if<!is_integral<InputIterator2>::value, InputIterator2>::type = InputIterator2(),
				typename enable_if<!is_integral<InputIterator1>::value, InputIterator1>::type = InputIterator1())
	{
		while (first1 != last1)
		{
			if(!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred,
	  			typename enable_if<!is_integral<InputIterator2>::value, InputIterator2>::type = InputIterator2(),
				typename enable_if<!is_integral<InputIterator1>::value, InputIterator1>::type = InputIterator1())
	{
		while (first1 != last1)
		{
			if(!pred(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}


	template <class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	first;
		second_type	second;

		pair(): first(T1()), second(T2()) {}
		pair (const first_type& a, const second_type& b): first(a), second(b) {}
		template<class U, class V>
		pair (const pair<U,V>& pr) { this->operator=(pr); }
		pair& operator= (const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}
	};
	template <class T1, class T2>
  	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }
	template <class T1, class T2>
  	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }
	template <class T1, class T2>
  	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }
	template <class T1, class T2>
  	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }
	template <class T1, class T2>
  	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }
	template <class T1, class T2>
  	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }
	
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{ return ( pair<T1,T2>(x,y) ); }
}
