/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:04:55 by abiari            #+#    #+#             */
/*   Updated: 2021/10/09 14:24:26 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "random_access_iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "../tools.hpp"
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
				if (n)
					_data = _alloc.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&_data[i], val);
			}
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				size_t i = std::distance(first, last);
				_size = i;
				_capacity = i;
				if (i)
					_data = _alloc.allocate(i);
				for (size_t j = 0; j < i && first != last; ++j, ++first)
					_alloc.construct(&_data[j], *first);
			}
			vector (const vector& src): _capacity(0), _size(0), _data(nullptr) { this->operator=(src); }
			virtual ~vector()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_data[i]);
				_alloc.deallocate(_data, _size);
			}
			
			/** -------------------------------- ASSIGNMENT --------------------------------**/
			vector&	operator=(const vector& x)
			{
				_alloc = x.get_allocator();
				if (!_data)
				{
					_data = _alloc.allocate(x._capacity);
					for (size_t i = 0; i < x._size; i++)
						_alloc.construct(&_data[i], x._data[i]);
					_capacity = x._capacity;
					_size = x._size;
					return (*this);
					
				}
				if (_capacity == x._capacity)
				{
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(&_data[i]);
					for (size_t i = 0; i < x._size; i++)
						_alloc.construct(&_data[i], x._data[i]);
				}
				else
				{
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(&_data[i]);
					_alloc.deallocate(_data, _capacity);
					_data = _alloc.allocate(x._capacity);
					for (size_t i = 0; i < x._size; i++)
						_alloc.construct(&_data[i], x._data[i]);
				}
				_capacity = x._capacity;
				_size = x._size;
				return (*this);
			}

			/** -------------------------------- ITERATORS --------------------------------**/
			iterator				begin() { return (iterator(_data)); }
			const_iterator			begin() const { return (iterator(_data)); }
			iterator				end() { return (iterator(&_data[_size])); }
			const_iterator			end() const { return (iterator(&_data[_size])); }
			reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
			const_reverse_iterator	rbegin() const { return reverse_iterator(iterator(&_data[_size])); }
			reverse_iterator		rend() { return reverse_iterator(this->begin()); }
			const_reverse_iterator	rend() const { return reverse_iterator(iterator(_data)); }
			
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
						reserve(n);
					for (size_t i = _size; i < n; i++)
						_alloc.construct(&_data[i], val);
					_size = n;
				}
			}
			size_type	capacity() const { return _capacity; }
			bool		empty() const { return (_size == 0); }
			void		reserve(size_type n)
			{
				if (n > _capacity)
				{
					value_type *tmp = _alloc.allocate(n);
					for (size_t i = 0; i < _size; i++)
						_alloc.construct(tmp + i, _data[i]);
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
					_data = tmp;
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
				size_t	n = std::distance(first, last);
				_size = 0;
				if (n > _capacity)
						reserve(n);
				for (size_t i = 0; i < n; ++i)
				{
					_alloc.construct(&_data[i], *first);
					first++;
					_size++;
				}
			}
			void	assign(size_type n, const value_type& val)
			{
				if (n > _capacity)
						reserve(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(&_data[i], val);
				_size = n;
			}
			void	push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
				{
					if (_capacity == 0)
						reserve(1);
					else
						reserve(_capacity * 2);
				}
				_alloc.construct(&_data[_size], val);
				_size++;
			}
			void	pop_back() { _size--; }
			iterator	insert(iterator position, const value_type& val)
			{
				difference_type	positionIndex = std::distance(begin(), position);
				if (_size + 1 > _capacity)
				{
					if (_capacity == 0)
						reserve(1);
					else
						reserve(_capacity * 2);
				}
				for (difference_type i = _size - 1; i >= positionIndex; i--)
					_data[i + 1] = _data[i];
				_alloc.construct(&_data[positionIndex], val);
				_size++;
				return (iterator(_data + positionIndex));
			}
			void		insert(iterator position, size_type n, const value_type& val)
			{
				difference_type	positionIndex = std::distance(begin(), position);
				if(_size + n > _capacity)
				{
					if (n > _size)
						reserve(_size + n);
					else
						reserve(_capacity * 2);
				}
				for (difference_type i = _size - 1; i >= positionIndex; i--)
					_alloc.construct(&_data[i + n], _data[i]);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(&_data[positionIndex + i], val);
				_size += n;
			}
			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				difference_type	positionIndex = std::distance(begin(), position);
				size_t n = std::distance(first, last);
				if(_size + n > _capacity)
				{
					if (n > _size)
						reserve(_size + n);
					else
						reserve(_capacity * 2);
				}
				for (difference_type i = _size - 1; i >= positionIndex; i--)
					_alloc.construct(&_data[i + n], _data[i]);
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(&_data[positionIndex + i], *first);
					first++;
				}
				_size += n;
			}
			iterator erase (iterator position)
			{
				size_type	positionIndex = std::distance(begin(), position);
				for (size_type i = positionIndex; i < _size - 1; i++)
				{
					_data[i] = _data[i + 1];
				}
				_size--;
				return (iterator(_data + positionIndex));
			}
			iterator erase (iterator first, iterator last)
			{
				size_type	positionIndex = std::distance(begin(), first);
				size_type	n = std::distance(first, last);
				for (size_type i = positionIndex; i < _size - n; i++)
				{
					_data[i] = _data[i + n];
				}
				_size -= n;
				return (iterator(_data + positionIndex));
			}
			void		swap(vector& x)
			{
				size_type tmp = _size;
				_size = x._size;
				x._size = tmp;
				tmp = _capacity;
				_capacity = x._capacity;
				x._capacity = tmp;
				value_type *temp = _data;
				_data = x._data;
				x._data = temp;
			}
			void		clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_size = 0;
			}
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
	template < class T, class Alloc>
		bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			if(lhs.size() == rhs.size())
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			else
				return false;
		}
	template < class T, class Alloc>
		bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!ft::operator==(lhs, rhs));
		}
	template < class T, class Alloc>
 		bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
	template < class T, class Alloc>
 		bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (ft::operator<(rhs, lhs));
		}
	template < class T, class Alloc>
 		bool operator<=  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!ft::operator<(rhs, lhs));
		}
	template < class T, class Alloc>
 		bool operator>=  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!ft::operator<(lhs, rhs));
		}
	
	template <class T, class Alloc>
  		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}

