/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:44 by abiari            #+#    #+#             */
/*   Updated: 2021/10/27 14:15:53 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools.hpp"
#include <memory>
#include <iterator>
#include <stdexcept>
#include <functional>
#include "../vector/vector.hpp"
#include "RBTree.hpp"
#include "../iterators/RBT_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../iterators/iterator_traits.hpp"

namespace	ft
{
template <	typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Alloc = std::allocator<ft::pair<const Key, T> >
>	class	map
{
	public:
		typedef				Key													key_type;
		typedef				T													mapped_type;
		typedef				Compare												key_compare;
		typedef				Alloc												allocator_type;
		typedef	typename	allocator_type::reference							reference;
		typedef	typename	allocator_type::const_reference						const_reference;
		typedef	typename	allocator_type::pointer								pointer;
		typedef	typename	allocator_type::const_pointer						const_pointer;
		typedef				size_t												size_type;
		typedef	typename	ft::pair<const key_type, mapped_type>				value_type;
		typedef	typename	ft::RBTree<value_type, Alloc, Compare>::iterator					iterator;
		typedef	typename	ft::RBTree<value_type, Alloc, Compare>::const_iterator				const_iterator;
		typedef	typename	ft::RBTree<value_type, Alloc, Compare>::reverse_iterator			reverse_iterator;
		typedef	typename	ft::RBTree<value_type, Alloc, Compare>::const_reverse_iterator		const_reverse_iterator;
		typedef	typename	ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef	typename	ft::RBTree<value_type, Alloc, Compare>::Node*		RBT_node;
		typedef	class	value_compare
		{
			friend class map;
			protected:
				Compare comp;
				value_compare(Compare c): comp(c) {}
			public:
				typedef	bool		result_type;
				typedef	value_type	first_argument_type;
				typedef	value_type	second_argument_type;
				bool	operator() (const value_type& x, const value_type& y) const
				{ return comp(x.first, y.first); }
		} value_compare;

		explicit	map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(), _comp(comp), _alloc(alloc)
		{
			_tree.init(comp, alloc);
		}
		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()): _tree(), _comp(comp), _alloc(alloc)
		{
			_tree.init(comp, alloc);
			for (InputIterator i = first; i != last; ++i)
			{
				_tree.insert(*i);
			}
		}
		map(const map& src): _tree()
		{
			this->operator=(src);
		}
		virtual	~map()
		{
			_tree.~RBTree();
		}
		
		/** -------------------------------- ASSIGNMENT --------------------------------**/
		
		map&	operator=(const map& src)
		{
			_alloc = src._alloc;
			_comp = src._comp;
			_tree = src._tree;
			return *this;
		}
		
		/** -------------------------------- ITERATORS --------------------------------**/
		
		iterator				begin() { return _tree.begin(); }
		const_iterator			begin() const { return _tree.begin(); }
		iterator				end() { return _tree.end(); }
		const_iterator			end() const { return _tree.end(); }
		reverse_iterator		rbegin() { return _tree.rbegin(); }
		const_reverse_iterator	rbegin() const { return _tree.rbegin(); }
		reverse_iterator		rend() { return _tree.rend(); }
		const_reverse_iterator	rend() const { return _tree.rend(); }
		
		/** -------------------------------- CAPACITY --------------------------------**/
		
		bool		empty() const { return (_tree.size() == 0); }
		size_type	size() const { return _tree.size(); }
		size_type	max_size() const { return _alloc.max_size(); }
		/** -------------------------------- ELEMENT ACCESS --------------------------------**/
		mapped_type&	operator[](const key_type& k)
		{
			return (_tree.insert(ft::make_pair(k, mapped_type())).first)->second;
		}
		/** -------------------------------- MODIFIERS --------------------------------**/
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			return _tree.insert(val);
		}
		iterator	insert(iterator position, const value_type& val)
		{
			(void)position;
			return _tree.insert(val).first;
		}
		template<class InputIterator>
			void	insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				for (InputIterator it = first; it != last; it++)
					_tree.insert(*it);
			}
		void		erase(iterator position) { _tree.remove(position->first); }
		size_type	erase(const key_type& k) { return _tree.remove(k); }
		void		erase(iterator first, iterator last)
		{
			difference_type	n = std::distance(first, last);
			ft::vector<key_type> keys;
			keys.reserve(n);
			for(iterator it = first; it != last; ++it)
				keys.push_back(it->first);
			for (typename ft::vector<key_type>::iterator it = keys.begin(); it != keys.end(); ++it)
				_tree.remove(*it);
		}
		void	swap(map& x)
		{
			_tree.swap(x._tree);
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
		}
		void	clear() { _tree.clear(); }
		/** -------------------------------- OBSERVERS --------------------------------**/
		key_compare		key_comp() const { return _comp; }
		value_compare	value_comp() const { return value_compare(_comp);}
		/** -------------------------------- OPERATIONS --------------------------------**/
		iterator		find(const key_type& k)	{	return _tree.find(k);	}
		const_iterator	find(const key_type& k) const	{	return _tree.find(k);	}

		size_type		count (const key_type& k) const
		{
			if(find(k) != end())
				return 1;
			return 0;
		}
		iterator		lower_bound(const key_type& k)
		{
			iterator	pt;
			if((pt = _tree.find(k)) != end())
				return pt;
			return _tree.findSuccessor(k);
		}
		const_iterator	lower_bound(const key_type& k) const
		{
			const_iterator	pt;
			if((pt = _tree.find(k)) != end())
				return pt;
			return _tree.findSuccessor(k);
		}
		iterator upper_bound (const key_type& k) { return _tree.findSuccessor(k); }
		const_iterator upper_bound (const key_type& k) const { return _tree.findSuccessor(k); }
		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return ft::make_pair(lower_bound(k), upper_bound(k)); }
		ft::pair<iterator,iterator>             equal_range (const key_type& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); }
		/** -------------------------------- ALLOCATOR --------------------------------**/
		allocator_type get_allocator() const { return Alloc(); }
	private:
		ft::RBTree<value_type, Alloc, Compare>	_tree;
		Compare		_comp;
		Alloc		_alloc;
};
template <class Key, class T, class Compare, class Alloc>
  bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  if(lhs.size() == rhs.size())
		  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	  return false;
  }
template <class Key, class T, class Compare, class Alloc>
  bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return !(lhs == rhs);
  }
template <class Key, class T, class Compare, class Alloc>
  bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }
template <class Key, class T, class Compare, class Alloc>
  bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return !(rhs < lhs);
  }
template <class Key, class T, class Compare, class Alloc>
  bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return (rhs < lhs);
  }
template <class Key, class T, class Compare, class Alloc>
  bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
  {
	  return !(lhs < rhs);
  }
template <class Key, class T, class Compare, class Alloc>
  void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
  {
	  x.swap(y);
  }
}
