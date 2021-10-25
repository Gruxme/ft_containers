/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:36 by abiari            #+#    #+#             */
/*   Updated: 2021/10/23 16:44:36 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator_traits.hpp"
#include "../map/RBTree.hpp"

namespace ft
{
	template<typename Pair>
	class	RBT_reverse_iterator
	{
		private:
			/** -------------------------------- Successor/predecessor --------------------------------**/
			Node *_min(Node *pt)
			{
				Node *node = pt;
				while (node->left != NULL)
				{
					node = node->left;
				}
				return node;
			}
			Node *_max(Node *pt)
			{
				Node *node = pt;
				while (node->right != NULL)
				{
					node = node->right;
				}
				return node;
			}
			Node *_inOrderSuccessor(Node *pt)
			{
				if (pt->right != NULL)
					return _min(pt->right);
				Node *node = pt;
				Node *parent = node->parent;
				while (parent != NULL && node == parent->right)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
			Node *_inOrderPredecessor(Node *pt)
			{
				if (pt->left != NULL)
					return _max(pt->left);
				Node *node = pt;
				Node *parent = node->parent;
				while (parent != NULL && node == parent->left)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

		public:
			typedef typename	std::bidirectional_iterator_tag		iterator_category;
			typedef	typename	ft::RBTree<Pair>::Node				Node;
			typedef				Pair								value_type;
			typedef 			ptrdiff_t							difference_type;
			typedef				Pair*								pointer;
			typedef				Pair&								reference;

			RBT_reverse_iterator() : _nodePtr(nullptr), _first(nullptr) {}
			RBT_reverse_iterator(pointer node, pointer first = nullptr) : _nodePtr(node), _first(first) {}
			RBT_reverse_iterator(const RBT_reverse_iterator& src) : _nodePtr(src.base()), _first(src._first) {}
			template<typename Iter>
			RBT_reverse_iterator (RBT_reverse_iterator<Iter> const& it): _nodePtr(it._nodePtr), _first(it._first) {}
			virtual ~RBT_reverse_iterator() {}
			
			/** -------------------------------- ASSIGNMENT --------------------------------**/

			RBT_reverse_iterator	&operator=(const RBT_reverse_iterator &src)
			{
				_nodePtr = src.base();
				_first = src._first;
				return *this;
			}
			
			/** -------------------------------- MEMBER ACCESS --------------------------------**/
	
			reference	operator*() const { return _nodePtr->data;}
			pointer		operator->() const { return &(operator*()); }

			/** -------------------------------- INCREMENT/DECREMENT --------------------------------**/
			
			RBT_reverse_iterator	&operator++()
			{
				_nodePtr = _inOrderPredecessor(_nodePtr);
				return *this;
			}
			RBT_reverse_iterator	&operator--()
			{
				if(!_nodePtr && _first)
				{
					_nodePtr = _first;
					_first = null;
					return *this;
				}
				_nodePtr = _inOrderSuccessor(_nodePtr);
				return *this;
			}
			RBT_reverse_iterator	operator++(int)
			{
				RBT_reverse_iterator	tmp = *this;
				_nodePtr = _inOrderPredecessor(_nodePtr);
				return tmp;
			}
			RBT_reverse_iterator	operator--(int)
			{
				RBT_reverse_iterator	tmp = *this;
				if(!_nodePtr && _first)
				{
					_nodePtr = _first;
					_first = null;
					return *tmp;
				}
				_nodePtr = _inOrderSuccessor(_nodePtr);
				return tmp;
			}
			
			
			Node*	base() const { return _nodePtr; }
		protected:
			Node*	_nodePtr;
			Node*	_first;
	};
/** -------------------------------- EQUAL/NOT EQUAL --------------------------------**/
template<typename Pair>
bool	operator==(RBT_reverse_iterator<Pair> const &lhs, RBT_reverse_iterator<Pair> const &rhs)
{
	return lhs._nodePtr->first == rhs._nodePtr->first;
}
template<typename Pair>
bool	operator!=(RBT_reverse_iterator<Pair> const &lhs, RBT_reverse_iterator<Pair> const &rhs)
{
	return lhs._nodePtr->first != rhs._nodePtr->first;
}
}

