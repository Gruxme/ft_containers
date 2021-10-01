/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:04:55 by abiari            #+#    #+#             */
/*   Updated: 2021/09/15 16:29:08 by abiari           ###   ########.fr       */
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
					*(_data + i) = val;
			}
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : _alloc(alloc)
			{
				size_t i = 0;
				_size = 0;
				for (InputIterator it = first; it != last; it++)
					i++;
				_capacity = i;
				_data = _alloc.allocate(_capacity);
				for (size_t j = 0; j < i; j++)
				{
					*(_data + j) = *(first + j);
					_size++;
				}
			}
			vector (const vector& src) { this->operator=(src); }
			virtual ~vector()
			{
				_alloc.deallocate(_data, _size);
			}
			
			/** -------------------------------- ASSIGNMENT --------------------------------**/
			vector&	operator=(const vector& x)
			{
				if (x.capacity() > _capacity)
				{
					_alloc.deallocate(_data, _capacity);
					_data = _alloc.allocate(x.capacity());
				}
				for (size_t i = 0; i < x._size; i++)
					*(_data + i) = *(x._data + i);
				_alloc = x.get_allocator();
				_size = x.size();
				_capacity = x.capacity();
				return *this;
			}

			/** -------------------------------- ITERATORS --------------------------------**/
			iterator				begin() { return (iterator(_data)); }
			const_iterator			begin() const { return (const_iterator(_data)); }
			iterator				end() { return (iterator(_data + _size)); }
			const_iterator			end() const { return (const_iterator(_data + _size)); }
			reverse_iterator		rbegin()
			{
				if (_capacity != 0)
					return reverse_iterator(this->end());
				return (reverse_iterator()); 
			}
			const_reverse_iterator	rbegin() const
			{
				if (_capacity != 0)
					return reverse_iterator(this->end());
				return (reverse_iterator()); 
			}
			reverse_iterator		rend()
			{
				if (_capacity != 0)
					return reverse_iterator(this->begin());
				return (reverse_iterator()); 
			}
			const_reverse_iterator	rend() const
			{
				if (_capacity != 0)
					return reverse_iterator(this->begin());
				return (reverse_iterator()); 
			}
			
			/** -------------------------------- CAPACITY --------------------------------**/
			size_type	size() const { return _size; }
			size_type	max_size() const { return _alloc.max_size(); }
			void 		resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
					_size = n;
				if (n > _size)
				{
					if (n > _capacity)
					{
						value_type *_temp;
						size_type newCapacity = _capacity;
						while (n > newCapacity)
							newCapacity *= 2;
						_temp = _alloc.allocate(newCapacity);
						for (size_t i = 0; i < _size; i++)
							*(_temp + i) = *(_data + i);
						_alloc.deallocate(_data, _capacity);
						_data = _temp;
						for (size_t i = _size; i < n; i++)
							*(_data + i) = val;
						_size = n;
						_capacity = newCapacity;
					}
					else
					{
						for (size_t i = _size; i < n; i++)
							*(_data + i) = val;
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
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				size_t	n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				if (n > _capacity)
				{
					_size = 0;
					_alloc.deallocate(_data, _capacity);
					while (n > _capacity)
						_capacity *= 2;
					_data = _alloc.allocate(_capacity);
					for (size_t i = 0; i < n; i++)
					{
						*(_data + n) = first[n];
						_size++;
					}
				}
				else
				{
					_size = 0;
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					for (size_t i = 0; i < n; i++)
					{
						*(_data + n) = first[n];
						_size++;
					}
				}
			}
			void	assign(size_type n, const value_type& val)
			{
				if (n > _capacity)
				{
					_size = 0;
					_alloc.deallocate(_data, _capacity);
					while (n > _capacity)
						_capacity *= 2;
					_data = _alloc.allocate(_capacity);
					for (size_t i = 0; i < n; i++)
					{
						*(_data + i) = val;
						_size++;
					}
				}
				else
				{
					_size = 0;
					for (size_t i = 0; i < n; i++)
					{
						*(_data + i) = val;
						_size++;
					}
				}
			}
			void	push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
				{
					size_type newCapacity = _capacity * 2;
					if (newCapacity == 0)
						newCapacity += 1;
					value_type *_temp = _alloc.allocate(newCapacity);
					for (size_t i = 0; i < _size; i++)
						*(_temp + i) = *(_data + i);
					_alloc.deallocate(_data, _capacity);
					_data = _temp;
					*(_data + _size) = val;
					_size += 1;
					_capacity = newCapacity;
				}
				else
				{
					*(_data + _size) = val;
					_size += 1;
				}
			}
			void	pop_back() { _size--; }
			// iterator	insert(iterator position, const value_type& val)
			// {
			// 	size_t	positionIndex = 0;
			// 	for (iterator it = this->begin(); it != position; it++)
			// 		positionIndex++
				
			// 	if (_size + 1 > _capacity)
			// 	{
			// 		size_type newCapacity = _capacity * 2;
			// 		value_type *_temp = _alloc.allocate(newCapacity);
			// 		for (size_t i = 0; i < _size; i++)
			// 			_alloc.construct(_temp + i, *(_data + i));
			// 		for (size_t i = 0; i < _size; i++)
			// 			_alloc.destroy(_data + i);
			// 		_alloc.deallocate(_data, _capacity);
					
			// 	}
			// 	else
			// 	{
					
			// 	}
			// }
			// void		insert(iterator position, size_type nm const value_type& val)
			// {
				
			// }
			// template <class InputIterator>
			// void		insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			// {
				
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
