/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:44 by abiari            #+#    #+#             */
/*   Updated: 2021/10/25 14:51:01 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools.hpp"
#include <memory>
#include <iterator>
#include <stdexcept>
#include <functional>
#include "RBTree.hpp"
#include "../iterators/RBT_iterator.hpp"
#include "../iterators/RBT_reverse_iterator.hpp"
#include "../iterators/iterator_traits.hpp"

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
		typedef				allocator_type::reference							reference;
		typedef				allocator_type::const_reference						const_reference;
		typedef				allocator_type::pointer								pointer;
		typedef				allocator_type::const_pointer						const_pointer;
		typedef				size_t												size_type;
		typedef	typename	ft::pair<const key_type, mapped_type>				value_type;
		typedef	typename	ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef				ft::RBT_iterator<value_type>						iterator;
		typedef				ft::RBT_iterator<const value_type>					const_iterator;
		typedef				ft::RBT_reverse_iterator<value_type>				reverse_iterator;
		typedef				ft::RBT_reverse_iterator<const value_type>			const_reverse_iterator;
		typedef	typename	ft::RBTree<value_type, Alloc, Compare>::Node*		RBT_node;
		typedef	class	value_compare
		{
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

		explicit	map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree() {}
		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()): _tree()
		{
			for (InputIterator i = first; i != last; i++)
			{
				_tree.insert(*first);
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
			_tree = src._tree;
		}
		
		/** -------------------------------- ITERATORS --------------------------------**/
		
		iterator				begin() { return iterator(_tree._min()); }
		const_iterator			begin() const { return iterator(_tree._min()); }
		iterator				end() { return iterator(NULL, _tree._max()); }
		const_iterator			end() const { return iterator(NULL, _tree._max()); }
		reverse_iterator		rbegin() { return iterator(_tree._max()); }
		const_reverse_iterator	rbegin() const { return iterator(_tree._max()); }
		reverse_iterator		rend() { return iterator(NULL, _tree._min()); }
		const_reverse_iterator	rend() const { return iterator(NULL, _tree._min()); }
		
		/** -------------------------------- CAPACITY --------------------------------**/
		
		bool		empty() const { return (_tree._size == 0); }
		size_type	size() const { return _tree._size; }
		size_type	max_size() const { return _alloc.max_size(); }
		/** -------------------------------- ELEMENT ACCESS --------------------------------**/
		mapped_type&	operator[](const key_type& k)
		{
			ft::pair<typename ft::RBTree<value_type, Alloc, Compare>::Node*, bool> ret;
			ret = _tree.insert(ft::make_pair(k, mapped_type()));
			return (ret.first)->data->second;
		}
		/** -------------------------------- MODIFIERS --------------------------------**/
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			ft::pair<RBT_node, bool> ret;
			ret  = _tree.insert(val);
			return ft::make_pair(iterator(ret.first), ret.second);
		}
		iterator	insert(iterator position, const value_type& val)
		{
			(void)position;
			return iterator(_tree.insert(val).first);
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
			for (iterator it = first; it != last; it++)
				_tree.remove(it->first);
		}
		void	swap(map& x)
		{
			std::swap(x._tree, _tree);
			std::swap(_alloc, x._alloc);
		}
		void	clear() { _tree.clear(); }
		/** -------------------------------- OBSERVERS --------------------------------**/
		key_compare		key_comp() const { return key_compare(); }
		value_compare	value_comp() const { return value_compare();}
		/** -------------------------------- OPERATIONS --------------------------------**/
		iterator		find(const key_type& k)
		{
			RBT_node	el = _tree.find(k);
			if (!el)
				return end();
			return iterator(_tree.find(k));
		}
		const_iterator	find(const key_type& k) const
		{
			RBT_node	el = _tree.find(k);
			if (!el)
				return end();
			return iterator(_tree.find(k));
		}
		size_type		count (const key_type& k) const
		{
			if(_tree.find(k))
				return 1;
			return 0;
		}
		iterator		lower_bound(const key_type& k)
		{
			RBT_node	pt = _tree.find(key);
			if(pt)
				return iterator(pt);
			else
				return iterator(_tree.findSuccessor(k));
		}
		const_iterator	lower_bound(const key_type& k) const
		{
			RBT_node	pt = _tree.find(key);
			if(pt)
				return iterator(pt);
			else
				return iterator(_tree.findSuccessor(k));
		}
		iterator upper_bound (const key_type& k) { return iterator(_tree.findSuccessor(k)); }
		const_iterator upper_bound (const key_type& k) const { return iterator(_tree.findSuccessor(k)); }
		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return ft::make_pair(lower_bound(k), upper_bound(k)); }
		ft::pair<iterator,iterator>             equal_range (const key_type& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); }
		/** -------------------------------- ALLOCATOR --------------------------------**/
		allocator_type get_allocator() const { return Alloc(); }
	private:
		ft::RBTree<value_type, Alloc, Compare>	_tree;
		Alloc		_alloc;
};
