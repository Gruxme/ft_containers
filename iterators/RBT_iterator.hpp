/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:36 by abiari            #+#    #+#             */
/*   Updated: 2021/10/25 19:57:33 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator_traits.hpp"
#include "../map/RBTree.hpp"

namespace ft
{
	template<typename Pair, typename Node, typename Tree>
	class	RBT_iterator
	{
		public:
			typedef typename	std::bidirectional_iterator_tag		iterator_category;
			typedef				Pair								value_type;
			typedef 			ptrdiff_t							difference_type;
			typedef				Pair*								pointer;
			typedef				Pair&								reference;
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
			RBT_iterator() : _nodePtr(NULL), _ob(NULL) {}
			RBT_iterator(Node* node, Tree const *ob) : _nodePtr(node), _ob(ob) {}
			RBT_iterator(const RBT_iterator& src) : _nodePtr(src.base()), _ob(src._ob) {}
			virtual ~RBT_iterator() {}
			
			/** -------------------------------- ASSIGNMENT --------------------------------**/

			RBT_iterator	&operator=(const RBT_iterator &src)
			{
				_nodePtr = src.base();
				_ob = src._ob;
				return *this;
			}
			
			/** -------------------------------- MEMBER ACCESS --------------------------------**/
	
			reference	operator*() const { return *(_nodePtr->data);}
			pointer		operator->() const { return &(operator*()); }

			/** -------------------------------- INCREMENT/DECREMENT --------------------------------**/
			
			RBT_iterator	&operator++()
			{
				_nodePtr = _inOrderSuccessor(_nodePtr);
				return *this;
			}
			RBT_iterator	&operator--()
			{
				if(!_nodePtr && _ob)
				{
					_nodePtr = _ob->max();
					return *this;
				}
				_nodePtr = _inOrderPredecessor(_nodePtr);
				return *this;
			}
			RBT_iterator	operator++(int)
			{
				RBT_iterator	tmp = *this;
				++(*this);
				return tmp;
			}
			RBT_iterator	operator--(int)
			{
				RBT_iterator	tmp = *this;
				--(*this);
				return tmp;
			}
			
			
			Node*	base() const { return _nodePtr; }
			
			// provide for implicit conversion from iterator to const_iterator
			operator	RBT_iterator<const value_type, Node, Tree>() const
			{
				return RBT_iterator<const value_type, Node, Tree>(_nodePtr, _ob);
			}
			friend bool	operator==(RBT_iterator const &lhs, RBT_iterator const &rhs)	{	return lhs._nodePtr == rhs._nodePtr;	}
			friend bool	operator!=(RBT_iterator const &lhs, RBT_iterator const &rhs)	{	return lhs._nodePtr != rhs._nodePtr;	}

		protected:
			Node*		_nodePtr;
			Tree const *_ob;
	};
}

