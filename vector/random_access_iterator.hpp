/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:20:34 by abiari            #+#    #+#             */
/*   Updated: 2021/09/15 16:42:36 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template< class T >
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
    		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
    		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
    		typedef T*	pointer;
    		typedef T&	reference;
			
			random_access_iterator() : m_ptr(nullptr) {}
			random_access_iterator(pointer ptr) : m_ptr(ptr) {}
			random_access_iterator(const random_access_iterator& src) : m_ptr(src.base()) {}
			virtual ~random_access_iterator() {}
			
			/** -------------------------------- ASSIGNMENT --------------------------------**/
			random_access_iterator&	operator=(const random_access_iterator& rhs)
			{
				this->m_ptr = rhs.base();
				return (*this);
			}
			random_access_iterator&	operator-=(difference_type n)
			{
				this->m_ptr -= n;
				return (*this);
			}
			random_access_iterator&	operator+=(difference_type n)
			{
				this->m_ptr += n;
				return (*this);
			}
			
			/** -------------------------------- MEMBER ACCESS --------------------------------**/
			reference	operator*() const { return (*m_ptr); }
			pointer		operator->() const { return &(operator*()); }
			reference	operator[](difference_type b) const { return (m_ptr[b]); }
			
			/** -------------------------------- INCREMENT/DECREMENT --------------------------------**/
			random_access_iterator&	operator++()
			{
				this->m_ptr += 1;
				return *this;
			}
			random_access_iterator	operator++(int)
			{
				random_access_iterator tmp = *this;
				this->m_ptr += 1;
				return tmp;
			}
			random_access_iterator&	operator--()
			{
				this->m_ptr -= 1;
				return *this;
			}
			random_access_iterator	operator--(int)
			{
				random_access_iterator tmp = *this;
				this->m_ptr -= 1;
				return tmp;
			}
			
			/** -------------------------------- ARITHMETIC --------------------------------**/
			random_access_iterator operator+(difference_type n)
			{
				random_access_iterator tmp(*this);
				tmp.m_ptr += n;
				return (tmp);
			}
			random_access_iterator operator-(difference_type n)
			{
				random_access_iterator tmp(*this);
				tmp.m_ptr -= n;
				return (tmp);
			}
			
			/** -------------------------------- GETTER --------------------------------**/
			pointer	base() const { return this->m_ptr; }

			// provide for implicit conversion from iterator to const_iterator
			operator	random_access_iterator<const value_type>() const
			{
				return random_access_iterator<const value_type>(m_ptr);
			}

		protected:
			pointer	m_ptr;
	};

	/** -------------------------------- ARITHMETIC --------------------------------**/
	template<class T>
	random_access_iterator<T>	operator+(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> rhs)
	{
		return (rhs.operator+(n));
	}
	template<class T>
	random_access_iterator<T>	operator-(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> rhs)
	{
		return (rhs.operator-(n));
	}
	template<class T>
	typename random_access_iterator<T>::difference_type	operator-(const random_access_iterator<T>& lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() - rhs.base();
	}

	/** -------------------------------- COMPARISON --------------------------------**/
	template<class T>
	bool	operator==(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template<class T>
	bool	operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template<class T>
	bool	operator>(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template<class T>
	bool	operator<(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template<class T>
	bool	operator>=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template<class T>
	bool	operator<=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
}

