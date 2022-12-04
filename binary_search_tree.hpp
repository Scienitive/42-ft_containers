/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:46:30 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/04 15:43:54 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# ifndef nullptr
#  define nullptr NULL
# endif

# include <memory>
# include <iostream>

template<typename T>
struct bst_node
{
/* --------------- TYPEDEFS --------------- */
	typedef T		value_type;

/* --------------- MEMBER ATTRIBUTES --------------- */
	value_type	value;
	bst_node	*left;
	bst_node	*right;
	bst_node	*parent;

/* --------------- CONSTRUCTORS --------------- */
	bst_node()
		:	left(nullptr), right(nullptr), parent(nullptr)
	{
	}

	bst_node(const value_type &val)
		:	value(val), left(nullptr), right(nullptr), parent(nullptr)
	{
	}

/* --------------- OPERATION OVERLOADS --------------- */
	bool	operator==(const bst_node &node)
	{
		if (value == node.value)
			return (true);
		return (false);
	}
};

template<typename T, typename Alloc = std::allocator<T> >
class binary_search_tree
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef value_type &								reference;
	typedef const value_type &							const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef bst_node<value_type>						node_type;
	typedef node_type *									node_pointer;
	typedef node_type &									node_reference;
	typedef std::allocator<node_type>					node_alloc;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	node_pointer	m_Root_Node;
	node_alloc		m_Node_Allocator;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	binary_search_tree()
		:	m_Root_Node(nullptr), m_Node_Allocator(node_alloc())
	{
	}

	binary_search_tree(const_reference value)
		:	m_Root_Node(nullptr), m_Node_Allocator(node_alloc())
	{
		add_node(value);
	}

	~binary_search_tree()
	{
		delete_tree(m_Root_Node);
	}

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:
	node_pointer	find_successor(node_pointer root)
	{
		node_pointer node = root->right;

		while (node->left != nullptr)
			node = node->left;
		
		return (node);
	}

	void	print_tree_helper(node_pointer root, int space)
	{
		if (root == nullptr)
			return;

		space += 5;

		print_tree_helper(root->right, space);

		std::cout << std::endl;
		for (int i = 5; i < space; i++)
			std::cout << " ";
		std::cout << root->value << "\n";

		print_tree_helper(root->left, space);
	}

	void	delete_tree(node_pointer node)
	{
		if (node == nullptr)
			return;

		delete_tree(node->left);
		delete_tree(node->right);

		delete node;
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	void	add_node(const_reference value)
	{
		node_pointer allocated = m_Node_Allocator.allocate(1);
		m_Node_Allocator.construct(allocated, node_type(value));

		if (m_Root_Node == nullptr)
		{
			m_Root_Node = allocated;
			return;
		}

		node_pointer node = m_Root_Node;

		while (true)
		{
			if (value < node->value)
			{
				if (node->left == nullptr)
				{
					node->left = allocated;
					node->left->parent = node;
					break;
				}
				else
					node = node->left;
			}
			else if (value > node->value)
			{
				if (node->right == nullptr)
				{
					node->right = allocated;
					node->right->parent = node;
					break;
				}
				else
					node = node->right;
			}
		}
	}

	void	delete_node(const_reference value)
	{
		node_pointer node = m_Root_Node;

		while (node != nullptr && node->value != value)
		{
			if (value < node->value)
				node = node->left;
			else if (value > node->value)
				node = node->right;
		}

		if (node == nullptr)
			return;

		delete_node(node);
	}

	void	delete_node(node_pointer node)
	{
		if (node != nullptr)
		{
			if (node->left == nullptr && node->right == nullptr)
			{
				node_pointer	parent = node->parent;
				bool			left_right; // left = true | right = false

				if (parent != nullptr && parent->left == node)
					left_right = true;
				else if (parent != nullptr && parent->right == node)
					left_right = false;

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);

				if (parent != nullptr && left_right)
					parent->left = nullptr;
				else if (parent != nullptr && !left_right)
					parent->right = nullptr;
			}
			else if (node->left == nullptr && node->right != nullptr)
			{
				if (node->parent->left == node)
					node->parent->left = node->right;
				else if (node->parent->right == node)
					node->parent->right = node->right;

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);
			}
			else if (node->left != nullptr && node->right == nullptr)
			{
				if (node->parent->left == node)
					node->parent->left = node->left;
				else if (node->parent->right == node)
					node->parent->right = node->left;

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);
			}
			else
			{
				node_pointer successor = find_successor(node);
				node->value = successor->value;
				delete_node(successor);
			}	
		}
	}

	void	print_tree(void)
	{
		print_tree_helper(m_Root_Node, 0);
	}
};

#endif