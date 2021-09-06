/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:40:37 by abiari            #+#    #+#             */
/*   Updated: 2021/09/06 16:41:09 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "iterator_traits.hpp"

namespace	ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator 												iterator_type;
			typedef	typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef	typename iterator_traits<Iterator>::value_type			value_type;
			typedef	typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef	typename iterator_traits<Iterator>::pointer				pointer;
			typedef	typename iterator_traits<Iterator>::reference			reference;
			
			reverse_iterator() : _iter() {}
			explicit reverse_iterator (iterator_type it) : _iter(it) {}
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) { this->operator=(rev_it); }
			template< class Iter >
			reverse_iterator& operator=( const reverse_iterator<Iter>& other )
			{
				this->_iter = other.base();
				return *this;
			}
			iterator_type	base() const { return _iter; }
			
			reference			operator*() const { return (*_iter); }
			pointer				operator->() const { return &(operator*()); }
			reference			operator[](difference_type n) const { return (operator*(_iter + n)); }
			reverse_iterator	operator+(difference_type n) const
			{
				reverse_iterator	tmp(this->_iter);
				tmp._iter -= n;
				return tmp; 
			}
			reverse_iterator&	operator++()
			{
				this->_iter -= 1;
				return (*this);
			}
			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp = *this;
				++(*this);
				return tmp;
			}
			reverse_iterator&	operator+=(difference_type n)
			{
				this->_iter -= n;
				return (*this);
			}
			reverse_iterator	operator-(difference_type n) const
			{
				reverse_iterator	tmp(this->_iter);
				tmp->_iter += n;
				return (tmp);
				
			}
			reverse_iterator&	operator--()
			{
				this->_iter += 1;
				return (*this);
			}
			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp = *this;
				--(*this);
				return tmp;
			}
			reverse_iterator&	operator-=(difference_type n)
			{
				this->_iter += n;
				return (*this);
			}
			operator	reverse_iterator<const iterator_type>() const
			{
				return reverse_iterator<const iterator_type>(_iter);
			}
		private:
			iterator_type	_iter;
	};
	template <class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}
	
	template <class Iterator>
	bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
}
