/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:40:37 by abiari            #+#    #+#             */
/*   Updated: 2021/10/25 18:40:45 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
			reverse_iterator (const reverse_iterator& rev_it) { this->operator=(rev_it); }
			template<typename Iter>
			reverse_iterator (reverse_iterator<Iter> const& it): _iter(it.base()) {}
			reverse_iterator& operator=( const reverse_iterator& other )
			{
				this->_iter = other.base();
				return *this;
			}
			iterator_type	base() const { return _iter; }
			
			reference			operator*() const
			{
				iterator_type	tmp = _iter;
				return (*(--tmp));
			}
			pointer				operator->() const { return &(operator*()); }
			reference			operator[](difference_type n) const { return (_iter[-n - 1]); }
			reverse_iterator	operator+(difference_type n) const
			{
				reverse_iterator	tmp(this->_iter);
				tmp._iter -= n;
				return tmp; 
			}
			reverse_iterator&	operator++()
			{
				this->_iter--;
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
				tmp._iter += n;
				return (tmp);
				
			}
			reverse_iterator&	operator--()
			{
				this->_iter++;
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
		return (rhs.base() - lhs.base());
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
