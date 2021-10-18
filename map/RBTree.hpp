/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:42 by abiari            #+#    #+#             */
/*   Updated: 2021/10/18 15:57:02 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools.hpp"
#include <functional>
#include <memory>
#include <string>
#include <iostream>

template<typename Pair, typename Alloc/* , typename Comp */>
class	RBTree
{
	private:
		enum	Color {RED, BLACK};
		struct Node
		{
			Pair	*data;
			Node*	left;
			Node*	right;
			Node*	parent;
			bool	color;
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
		void	_rebalance(Node *&pt)
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
	public:
		RBTree(): _root(nullptr) {}
		void	insert(Pair const &val)
		{
			Node*	pt = _newNode(val);
			_root = _BSTInsert(_root, pt);
			_rebalance(pt);
		}
		void	printTree()
		{
			if (_root)
			{
				_printTree(_root, "", true);
			}
		}
	private:
		typename	Alloc::template	rebind<Node>::other	_nodeAlloc;
		Node*	_root;
		// Comp	_comp;
		Alloc	_alloc;
};
