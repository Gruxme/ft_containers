/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:42 by abiari            #+#    #+#             */
/*   Updated: 2021/10/22 17:47:20 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools.hpp"
#include <functional>
#include <memory>
#include <string>
#include <iostream>

template<typename Pair, typename Alloc, typename Comp>
class	RBTree
{
	public:
		typedef	typename	Pair::first_type	key_type;
	private:
		enum	Color {RED, BLACK, DBLACK};
		struct Node
		{
			Pair	*data;
			Node*	left;
			Node*	right;
			Node*	parent;
			bool	color ;
		};
		Node*	_newNode(Pair const &val)
		{
			Node*	node = _nodeAlloc.allocate(1);
			node->data = _alloc.allocate(1);
			_alloc.construct(node->data, val);
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
			node->color = RED;
			return node;
		}
		void	_deleteNode(Node* node)
		{
			_alloc.destroy(node->data);
			_alloc.deallocate(node->data, 1);
			_nodeAlloc.deallocate(node, 1);
		}
		void	_printTree(Node *root, std::string indent, bool last)
		{
			if (root != NULL)
			{
				std::cout << indent;
				if (last)
				{
					if(!root->parent)
					{
						std::cout << "|____";
						indent += "   ";
					}
					else
					{
						std::cout << "R----";
						indent += "   ";
					}
				}
				else
				{
					std::cout << "L----";
					indent += "|  ";
				}

				std::string sColor = root->color == RED ? "RED" : "BLACK";
				std::cout << " |" << root->data->first << " : " << root->data->second << "| " << "(" << sColor << ")" << std::endl;
				_printTree(root->left, indent, false);
				_printTree(root->right, indent, true);
			}
		}
		Node	*_BSTInsert(Node *root, Node* pt)
		{
			if (root == NULL)
				return pt;
			if (pt->data->first < root->data->first)
			{
				root->left = _BSTInsert(root->left, pt);
				root->left->parent = root;
			}
			else if (pt->data->first > root->data->first)
			{
				root->right = _BSTInsert(root->right, pt);
				root->right->parent = root;
			}
			return root;
		}
		void	_rotateLeft(Node *&pt)
		{
			Node	*pt_right = pt->right;
			
			pt->right = pt_right->left;
			if(pt->right != NULL)
				pt->right->parent = pt;
			
			pt_right->parent = pt->parent;
			if(pt->parent == NULL)
				_root = pt_right;
			else if (pt == pt->parent->left)
				pt->parent->left = pt_right;
			else
				pt->parent->right = pt_right;
			
			pt_right->left = pt;
			pt->parent = pt_right;
		}
		void	_rotateRight(Node *&pt)
		{
			Node	*pt_left = pt->left;
			
			pt->left = pt_left->right;
			if (pt->left != NULL)
				pt->left->parent = pt;
			
			pt_left->parent = pt->parent;
			if (pt->parent == NULL)
				_root = pt_left;
			else if (pt == pt->parent->left)
				pt->parent->left = pt_left;
			else
				pt->parent->right = pt_left;
			
			pt_left->right = pt;
			pt->parent = pt_left;
		}
		void	_postInsertRebalance(Node *&pt)
		{
			Node	*parent = NULL;
			Node	*grandParent = NULL;

			while((pt != _root) && (pt->color != BLACK) && (pt->parent->color == RED))
			{
				parent = pt->parent;
				grandParent = pt->parent->parent;
				/* Parent is left child of grand parent */
				if (parent == grandParent->left)
				{
					Node*	uncle = grandParent->right;
					/* uncle is red -> only recoloring */
					if ((uncle != NULL) && (uncle->color == RED))
					{
						grandParent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						pt = grandParent;
					}
					else
					{
						/* pt is right child of its parent -> left-rotation required */
						if (pt == parent->right)
						{
							_rotateLeft(pt),
							pt = parent;
							parent = pt->parent;
						}
						/* pt is left child of its parent -> right-rotation required*/
						_rotateRight(grandParent);
						std::swap(parent->color, grandParent->color);
						pt = parent;
					}
				}
				/* parent is right child of grand parent */
				else
				{
					Node*	uncle = grandParent->left;
					/* uncle is red -> recoloring */
					if((uncle != NULL) && (uncle->color == RED))
					{
						grandParent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						pt = grandParent;
					}
					else
					{
						/* pt is left child of its parent -> right-rotation required */
						if(pt == parent->left)
						{
							_rotateRight(parent);
							pt = parent;
							parent = pt->parent;
						}
						/* pt is right child of its parent -> left-rotation required */
						_rotateLeft(grandParent);
						std::swap(parent->color, grandParent->color);
						pt = parent;
					}
				}
			}
			_root->color = BLACK;
		}
		Node*	_min(Node* pt)
		{
			Node*	node = pt;
			while (node->left != NULL)
			{
				node = node->left;
			}
			return node;
		}
		Node*	_max(Node* pt)
		{
			Node*	node = pt;
			while (node->right != NULL)
			{
				node = node->right;
			}
			return node;
		}
		Node*	_inOrderSuccessor(Node*	pt)
		{
			if(pt->right != NULL)
				return _min(pt->right);
			Node*	node = pt;
			Node*	parent = node->parent;
			while(parent != NULL && node == parent->right)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}
		Node*	_inOrderPredecessor(Node* pt)
		{
			if(pt->left != NULL)
				return _max(pt->left);
			Node*	node = pt;
			Node*	parent = node->parent;
			while(parent != NULL && node == parent->left)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}
		/*------------------------------------ deletion functions here --------------------------*/
		void	_deleteChild(Node* node)
		{
			Node* parent = node->parent;
			if(node == parent->left)
			{
				_deleteNode(node);
				parent->left = NULL;
			}
			else
			{
				_deleteNode(node);
				parent->right = NULL;
			}
		}
		void	_remove(Node* first, Node* pt)
		{
			if(!pt)
				return ;
			if(!_comp(first->data->first, pt->data->first) && !_comp(pt->data->first, first->data->first))
			{
				if (!pt->right && !pt->left)
				{
					if (pt == _root)
					{
						_deleteNode(pt);
						_root = NULL;
						return;
					}
					_postDeleteRebalance(pt);
					_deleteChild(pt);
					pt = NULL;
				}
				else
				{
					if (pt->left)
					{
						Node *predecessor = _inOrderPredecessor(pt);
						_alloc.destroy(pt->data);
						_alloc.construct(pt->data, *(predecessor->data));
						_remove(pt, predecessor);
					}
					else
					{
						Node *successor = _inOrderSuccessor(pt);
						_alloc.destroy(pt->data);
						_alloc.construct(pt->data, *(successor->data));
						_remove(pt, successor);
					}
				}
				return ;
			}
			if(_comp(first->data->first, pt->data->first))
				_remove(first, pt->left);
			else
				_remove(first, pt->right);
		}
		void	_postDeleteRebalance(Node*	node)
		{
			if(node->color == RED)
				return ;
			if(node == _root)
			{
				node->color = BLACK;
				return ;
			}
			Node*	sibling = (node->parent->right == node) ? (sibling = node->parent->left) : (sibling = node->parent->right);
			if(sibling && sibling->color == BLACK)
			{
				// case 3: DB sibling is black and both sibling's childs are black
				/*
				1	remove db
				2	make sibling red
				3	if db parent is red make it black else make it double black
				4	if parent becomes db then recurse
			 	*/
				if((sibling->right == NULL || sibling->right->color == BLACK)
					&& (sibling->left == NULL || sibling->left->color == BLACK))
				{
					Node *parent = node->parent;
					node->color = BLACK;
					sibling->color = RED;
					parent->color = (parent->color == RED) ? BLACK : DBLACK;
					if (parent->color == DBLACK)
						_postDeleteRebalance(parent);
					return;
				}
				if (node->parent->left == node)
				{
					/* case4 sibling is black and nearest sibling child to db node is red
						1	swap sibling and red child colors
						2	rotate sibling in opposite direction of DB node
						3	will lead to case5 and get applied
			 		*/
					if ((sibling->left && sibling->left->color == RED) && (sibling->right == NULL || sibling->right->color == BLACK))
					{
						std::swap(sibling->color, sibling->left->color);
						_rotateRight(sibling);
					}
					/* case5 sibling is black and farthest child from db node is red
						1	swap parent and sibling colors
						2	rotate parent in direction of DB
						3	remove DB
						4	change sibling's far red child to black
					 */
					else if (sibling->right && sibling->right->color == RED)
					{
						node->color = BLACK;
						sibling->right->color = BLACK;
						std::swap(node->parent->color, sibling->color);
						_rotateLeft(node->parent);
						
					}
				}
				else
				{
					/* case4 sibling is black and nearest sibling child to db node is red
						1	swap sibling and red child colors
						2	rotate sibling in opposite direction of DB node
						3	will lead to case5 and get applied
			 		*/
					if(sibling->right->color == RED && (sibling->left == NULL || sibling->left->color == BLACK))
					{
						std::swap(sibling->color, sibling->right->color);
						_rotateLeft(sibling);
					}
					/* case5 sibling is black and farthest child from db node is red
						1	swap parent and sibling colors
						2	rotate parent in direction of DB
						3	remove DB
						4	change sibling's far red child to black
					 */
					else if(sibling->left->color == RED)
					{
						node->color = BLACK;
						sibling->left->color = BLACK;
						std::swap(node->parent->color, sibling->color);
						_rotateRight(node->parent);
					}
				}
			}
			/*	Sibling is red
				 swap sibling and parent colors
				 rotate parent is direction of DB node
				 recurse
			 */
			else if(sibling && sibling->color == RED)
			{
				std::swap(sibling->color, node->parent->color);
				if(node->parent->left == node)
					_rotateLeft(node->parent);
				else
					_rotateRight(node->parent);
				_postDeleteRebalance(node);
				return ;
			}
		}
		
	public:
		RBTree(): _root(nullptr) {}
		void	insert(Pair const &val)
		{
			Node*	pt = _newNode(val);
			if(!find(val.first))
			{
				_root = _BSTInsert(_root, pt);
				_postInsertRebalance(pt);
			}
		}
		Node*	find(typename Pair::first_type const &key) const
		{
			if (!_root)
				return NULL;
			Node*	root = _root;
			while(root != NULL)
			{
				if(root->data->first == key)
					return root;
				if(root->data->first > key)
					root = root->left;
				else
					root= root->right;
			}
			// std::cout << "key not found" << std::endl;
			return NULL;
		}
		void	remove(key_type const &key)
		{
			Node* toDelete = find(key);
			if (!toDelete)
				return ;
			_remove(toDelete, toDelete);
		}
		void	print()
		{
			if (_root)
			{
				_printTree(_root, "", true);
			}
		}
	private:
		typename	Alloc::template	rebind<Node>::other	_nodeAlloc;
		Node*	_root;
		Comp	_comp;
		Alloc	_alloc;
};
