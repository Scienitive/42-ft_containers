/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:46:30 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/06 01:15:06 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# ifndef nullptr
#  define nullptr NULL
# endif

# include <memory>
# include <iostream>

namespace ft
{

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

	bool		is_smallest;
	bool		is_biggest;
	bool		is_end_node;

/* --------------- CONSTRUCTORS --------------- */
	bst_node()
		:	left(nullptr), right(nullptr), parent(nullptr), is_smallest(false), is_biggest(false), is_end_node(false)
	{
	}

	bst_node(const value_type &val)
		:	value(val), left(nullptr), right(nullptr), parent(nullptr), is_smallest(false), is_biggest(false), is_end_node(false)
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

template<typename T, typename Key, typename Value, typename Compare, typename Alloc = std::allocator<T> >
class binary_search_tree
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T											value_type;
	typedef Key											key_type;
	typedef Value										mapped_type;
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
	Compare			m_Compare;
	node_pointer	m_Root_Node;
	node_pointer	m_End_Node;
	node_alloc		m_Node_Allocator;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	binary_search_tree()
		:	m_Compare(Compare()), m_Root_Node(nullptr), m_Node_Allocator(node_alloc())
	{
	}

	explicit binary_search_tree(const Compare &comp)
		:	m_Compare(comp), m_Root_Node(nullptr), m_Node_Allocator(node_alloc())
	{
	}

	binary_search_tree(const_reference value)
		:	m_Compare(Compare()), m_Root_Node(nullptr), m_Node_Allocator(node_alloc())
	{
		add_node(value);
	}

	~binary_search_tree()
	{
		delete_tree(m_Root_Node);
		delete m_End_Node;
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

	void	delete_node(node_pointer node)
	{
		if (!is_node_empty(node))
		{
			if (is_node_empty(node->left) && is_node_empty(node->right))
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
			else if (is_node_empty(node->left) && !is_node_empty(node->right))
			{
				if (node->parent->left == node)
					node->parent->left = node->right;
				else if (node->parent->right == node)
					node->parent->right = node->right;

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);
			}
			else if (!is_node_empty(node->left) && is_node_empty(node->right))
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

	void	delete_tree(node_pointer node)
	{
		if (is_node_empty(node))
			return;

		delete_tree(node->left);
		delete_tree(node->right);

		delete node;
	}

	void	end_node_connections(node_pointer node)
	{
		if (node->parent == nullptr)
		{
			node->is_biggest = true;
			node->is_smallest = true;
			node->left = m_End_Node;
			node->right = m_End_Node;
			m_End_Node->left = node;
			m_End_Node->right = node;
		}
		else if (node->parent->is_smallest && node->parent->left == node)
		{
			node->parent->is_smallest = false;
			node->is_smallest = true;
			node->left = m_End_Node;
			m_End_Node->right = node;
		}
		else if (node->parent->is_biggest && node->parent->right == node)
		{
			node->parent->is_biggest = false;
			node->is_biggest = true;
			node->right = m_End_Node;
			m_End_Node->left = node;
		}
	}

	node_pointer	find_biggest(void) const
	{
		node_pointer node = m_Root_Node;

		if (!is_node_empty(node))
		{
			while (!is_node_empty(node->right))
				node = node->right;
		}

		return (node);
	}

	node_pointer	find_smallest(void) const
	{
		node_pointer node = m_Root_Node;

		if (!is_node_empty(node))
		{
			while (!is_node_empty(node->left))
				node = node->left;
		}

		return (node);
	}

	void	del_end_node_connections(void)
	{
		node_pointer node_s = find_smallest();
		node_pointer node_b = find_biggest();

		if (!is_node_empty(node_s) && !node_s->is_smallest)
		{
			node_s->is_smallest = true;
			node_s->left = m_End_Node;
			m_End_Node->right = node_s;
		}
		if (!is_node_empty(node_b) && !node_b->is_biggest)
		{
			node_b->is_biggest = true;
			node_b->right = m_End_Node;
			m_End_Node->left = node_b;
		}
	}

	bool	is_node_empty(node_pointer node) const
	{
		return (node == nullptr || node->is_end_node);
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	void	add_node(const_reference value)
	{
		node_pointer allocated = m_Node_Allocator.allocate(1);
		m_Node_Allocator.construct(allocated, node_type(value));

		if (m_Root_Node == nullptr)
		{
			m_End_Node = m_Node_Allocator.allocate(1);
			m_Node_Allocator.construct(m_End_Node, node_type());
			m_End_Node->is_end_node = true;
			m_Root_Node = allocated;
			end_node_connections(m_Root_Node);
			return;
		}

		node_pointer node = m_Root_Node;

		while (true)
		{
			if (m_Compare(value.first, node->value.first))
			{
				if (is_node_empty(node->left))
				{
					node->left = allocated;
					node->left->parent = node;
					break;
				}
				else
					node = node->left;
			}
			else
			{
				if (is_node_empty(node->right))
				{
					node->right = allocated;
					node->right->parent = node;
					break;
				}
				else
					node = node->right;
			}
		}
		end_node_connections(allocated);
	}

	void	delete_node(const_reference value)
	{
		node_pointer node = m_Root_Node;

		while (!is_node_empty(node) && node->value != value)
		{
			if (m_Compare(value.first, node->value.first))
				node = node->left;
			else
				node = node->right;
		}

		if (is_node_empty(node))
			return;

		delete_node(node);
		del_end_node_connections();
	}

	void	print_tree(void)
	{
		print_tree_helper(m_Root_Node, 0);
	}

	node_pointer	get_root(void) const
	{
		return (m_Root_Node);
	}

	node_pointer	get_start(void) const
	{
		return (find_smallest());
	}

	node_pointer	get_end(void) const
	{
		return (m_End_Node);
	}

	mapped_type	&find(const Key &key)
	{
		node_pointer node = m_Root_Node;

		if (is_node_empty(node))
			throw std::out_of_range("Exception: Key not found.");

		while (true)
		{
			if (key == node->value.first)
				return (node->value.second);
			if (m_Compare(key, node->value.first))
			{
				if (is_node_empty(node->left))
					throw std::out_of_range("Exception: Key not found.");
				else
					node = node->left;
			}
			else
			{
				if (is_node_empty(node->right))
					throw std::out_of_range("Exception: Key not found.");
				else
					node = node->right;
			}
		}
	}

	const mapped_type	&const_find(const Key &key) const
	{
		node_pointer node = m_Root_Node;

		if (is_node_empty(node))
			throw std::out_of_range("Exception: Key not found.");

		while (true)
		{
			if (key == node->value.first)
				return (node->value.second);
			if (m_Compare(key, node->value.first))
			{
				if (is_node_empty(node->left))
					throw std::out_of_range("Exception: Key not found.");
				else
					node = node->left;
			}
			else
			{
				if (is_node_empty(node->right))
					throw std::out_of_range("Exception: Key not found.");
				else
					node = node->right;
			}
		}
	}

	bool	is_empty() const
	{
		if (m_Root_Node == nullptr)
			return (true);
		return (false);
	}
};

}

#endif