/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:04:55 by abiari            #+#    #+#             */
/*   Updated: 2021/09/06 16:59:21 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "random_access_iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "tools.hpp"
#include <memory>
#include <iterator>
#include <stdexcept>

namespace ft
{
	template< class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef	T														value_type;
			typedef	Alloc 													allocator_type;
			typedef	typename allocator_type::reference						reference;
			typedef	typename allocator_type::const_reference				const_reference;
			typedef	typename allocator_type::pointer						pointer;
			typedef	typename allocator_type::const_pointer					const_pointer;
			typedef	ft::random_access_iterator<value_type>					iterator;
			typedef	ft::random_access_iterator<const value_type>			const_iterator;
			typedef	ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef	size_t													size_type;
			
			
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(0), _size(0), _data(nullptr) {}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(n), _size(n)
			{
				_data = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_data + i, val);
			}
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : _alloc(alloc)
			{
				size_t i = 0;
				_size = 0;
				for (InputIterator it = first; it < last; it++)
					i++;
				_capacity = i;
				_data = _alloc.allocate(_capacity);
				for (size_t j = 0; j < i; j++)
				{
					_alloc.construct(_data + j, *(first + j));
					_size++;
				}
			}
			vector (const vector& src) { this->operator=(src); }
			virtual ~vector()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _size);
			}
			
			/** -------------------------------- ASSIGNMENT --------------------------------**/
			vector&	operator=(const vector& x)
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_data = _alloc.allocate(x._capacity);
				for (size_t i = 0; i < x._size; i++)
					_alloc.construct(_data + i, *(x._data + i));
				_alloc = x.get_allocator();
				_size = x.size();
				_capacity = x.capacity();
			}

			/** -------------------------------- ITERATORS --------------------------------**/
			iterator				begin() { return (iterator(_data)); }
			const_iterator			begin() const { return (const_iterator(_data)); }
			iterator				end() { return (iterator(_data + _size)); }
			const_iterator			end() const { return (const_iterator(_data + _size)); }
			reverse_iterator		rbegin()
			{
				iterator it(_data + (_size - 1));
				return (reverse_iterator(it - 1)); 
			}
			const_reverse_iterator	rbegin() const
			{
				iterator it(_data + (_size - 1));
				return (reverse_iterator(it - 1)); 
			}
			reverse_iterator		rend()
			{
				iterator it(_data);
				return (reverse_iterator(it - 1));
			}
			const_reverse_iterator	rend() const
			{
				iterator it(_data);
				return (reverse_iterator(it - 1));
			}
			
			/** -------------------------------- CAPACITY --------------------------------**/
			size_type	size() const { return _size; }
			size_type	max_size() const { return _alloc.max_size(); }
			void 		resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					for (size_t i = _size - n; i < _size; i++)
						_alloc.destroy(_data + i);
					_size = n;
				}
				if (n > _size)
				{
					if (n > _capacity)
					{
						value_type *_temp = _alloc.allocate(_capacity * 2);
						for (size_t i = 0; i < _size; i++)
							_alloc.construct(_temp + i, *(_data + i));
						for (size_t i = 0; i < _size; i++)
							_alloc.destroy(_data + i);
						_alloc.deallocate(_data, _capacity);
						_data = _temp;
						for (size_t i = _size; i < n; i++)
							_alloc.construct(_data + i, val);
						_size = n;
						_capacity = n;
					}
					else
					{
						for (size_t i = _size; i < n; i++)
							_alloc.construct(_data + i, val);
					}
				}
			}
			size_type	capacity() const { return _capacity; }
			bool		empty() const { return (_size == 0); }
			void		reserve(size_type n)
			{
				if (n > _capacity)
				{
					_data = _alloc.allocate(n, _data);
					_capacity = n;
				}
			}
			
			/** -------------------------------- ELEMENT ACCESS --------------------------------**/
			reference		operator[](size_type n) { return *(_data + n); }
			const_reference	operator[](size_type n) const { return _data[n]; }
			reference		at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("element is out of range");
				else
					return _data[n];
			}
			const_reference	at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("element is out of range");
				else
					return _data[n];
			}
			reference		front() { return _data[0]; }
			const_reference	front() const { return _data[0]; }
			reference		back() { return _data[_size - 1]; }
			const_reference	back() const { return _data[_size - 1]; }
			
			/** -------------------------------- MODIFIERS --------------------------------**/
			// template <class InputIterator>
			// void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			// {
			// 	;
			// }
			// void	assign(size_type n, const value_type& val)
			// {
			// 	_alloc.destroy(_data);
			// 	_alloc.deallocate(_data, _capacity);
				
			// }
			
			
			/** -------------------------------- GETTERS --------------------------------**/
			allocator_type	get_allocator() const
			{
				allocator_type	tmp(this->_alloc);
				return tmp;
			}
		private:
			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;
			value_type		*_data;
	};
}
