/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OLD_binary_search_tree.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:46:30 by alyasar           #+#    #+#             */
/*   Updated: 2023/01/03 16:25:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OLD_BINARY_SEARCH_TREE_HPP
# define OLD_BINARY_SEARCH_TREE_HPP

# include <cstddef> // BUNU EN SON SİL
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
	bool		is_smallest;
	bool		is_biggest;
	bool		is_end_node;

	value_type	value;
	bst_node	*left;
	bst_node	*right;
	bst_node	*parent;

/* --------------- CONSTRUCTORS --------------- */
	bst_node()
		:	is_smallest(false), is_biggest(false), is_end_node(false), left(nullptr), right(nullptr), parent(nullptr)
	{
	}

	bst_node(const value_type &val)
		:	is_smallest(false), is_biggest(false), is_end_node(false), value(val), left(nullptr), right(nullptr), parent(nullptr)
	{
	}

	bst_node(const value_type &val, const bst_node &other)
		:	is_smallest(other.is_smallest), is_biggest(other.is_biggest), is_end_node(other.is_end_node), value(val), left(other.left), right(other.right), parent(other.parent)
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
	typedef T															value_type;
	typedef Key															key_type;
	typedef Value														mapped_type;
	typedef Alloc														allocator_type;
	typedef value_type &												reference;
	typedef const value_type &											const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef typename allocator_type::size_type							size_type;
	typedef typename allocator_type::difference_type					difference_type;
	typedef bst_node<value_type>										node_type;
	typedef node_type *													node_pointer;
	typedef node_type &													node_reference;
	typedef typename allocator_type::template rebind<node_type>::other	node_alloc; // BU REBIND'I TAM ÇÖZ

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	Compare			m_Compare;
	node_pointer	m_Root_Node;
	node_pointer	m_End_Node;
	allocator_type	m_Value_Allocator;
	node_alloc		m_Node_Allocator;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	binary_search_tree()
		:	m_Compare(Compare()), m_Root_Node(nullptr), m_Value_Allocator(allocator_type()), m_Node_Allocator(node_alloc())
	{
		m_End_Node = m_Node_Allocator.allocate(1);
		m_Node_Allocator.construct(m_End_Node, node_type());
		m_End_Node->is_end_node = true;
	}

	explicit binary_search_tree(const Compare &comp, const allocator_type &alloc)
		:	m_Compare(comp), m_Root_Node(nullptr), m_Value_Allocator(alloc), m_Node_Allocator(node_alloc())
	{
		m_End_Node = m_Node_Allocator.allocate(1);
		m_Node_Allocator.construct(m_End_Node, node_type());
		m_End_Node->is_end_node = true;
	}

	binary_search_tree(const_reference value)
		:	m_Compare(Compare()), m_Root_Node(nullptr), m_Value_Allocator(allocator_type()), m_Node_Allocator(node_alloc())
	{
		m_End_Node = m_Node_Allocator.allocate(1);
		m_Node_Allocator.construct(m_End_Node, node_type());
		m_End_Node->is_end_node = true;
		add_node(value);
	}

	~binary_search_tree()
	{
		delete_tree(m_Root_Node);
		m_Node_Allocator.destroy(m_End_Node);
		m_Node_Allocator.deallocate(m_End_Node, 1);
	}

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:
	node_pointer	find_successor(node_pointer root) const
	{
		node_pointer node = root->right;

		while (node->left != nullptr)
			node = node->left;
		
		return (node);
	}

	void	print_tree_helper(node_pointer root, int space)
	{
		if (is_node_empty(root))
			return;

		space += 5;

		print_tree_helper(root->right, space);

		std::cout << std::endl;
		for (int i = 5; i < space; i++)
			std::cout << " ";
		std::cout << root->value.second << "\n";

		print_tree_helper(root->left, space);
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

	void	delete_tree(node_pointer node)
	{
		if (is_node_empty(node))
			return;

		delete_tree(node->left);
		delete_tree(node->right);

		if (node == m_Root_Node)
		{
			m_Root_Node = nullptr;
			m_End_Node->left = m_End_Node;
			m_End_Node->right = m_End_Node;
		}

		m_Node_Allocator.destroy(node);
		m_Node_Allocator.deallocate(node, 1);
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
	node_pointer	add_node(const_reference value)
	{
		node_pointer allocated = m_Node_Allocator.allocate(1);
		m_Node_Allocator.construct(allocated, node_type(value));

		if (m_Root_Node == nullptr)
		{
			m_Root_Node = allocated;
			end_node_connections(m_Root_Node);
			return (m_Root_Node);
		}

		node_pointer node = m_Root_Node;

		while (true)
		{
			if (value.first == node->value.first)
			{
				m_Node_Allocator.destroy(allocated);
				m_Node_Allocator.deallocate(allocated, 1);
				return (node);
			}
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
		return (allocated);
	}

	size_type	delete_node(const Key &key)
	{
		node_pointer node = m_Root_Node;

		while (!is_node_empty(node) && node->value.first != key)
		{
			if (m_Compare(key, node->value.first))
				node = node->left;
			else
				node = node->right;
		}

		if (is_node_empty(node))
			return (0);

		delete_node(node);
		del_end_node_connections();
		return (1);
	}

	void	delete_node(const_reference value)
	{
		node_pointer node = m_Root_Node;

		while (!is_node_empty(node) && node->value.first != value.first)
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
				else
				{
					m_Root_Node = nullptr;
					m_End_Node->left = m_End_Node;
					m_End_Node->right = m_End_Node;
				}

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);

				if (parent != nullptr && left_right)
					parent->left = nullptr;
				else if (parent != nullptr && !left_right)
					parent->right = nullptr;
			}
			else if (is_node_empty(node->left) && !is_node_empty(node->right))
			{
				if (is_node_empty(node->parent))
				{
					m_Root_Node = node->right;
					m_Root_Node->parent = nullptr;
				}
				else
				{
					if (node->parent->left == node)
					{				
						node->parent->left = node->right;
						node->right->parent = node->parent;
					}
					else if (node->parent->right == node)
					{
						node->parent->right = node->right;
						node->right->parent = node->parent;
					}
				}

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);
			}
			else if (!is_node_empty(node->left) && is_node_empty(node->right))
			{
				if (is_node_empty(node->parent))
				{
					m_Root_Node = node->left;
					m_Root_Node->parent = nullptr;
				}
				else
				{
					if (node->parent->left == node)
					{
						node->parent->left = node->left;
						node->left->parent = node->parent;
					}
					else if (node->parent->right == node)
					{
						node->parent->right = node->left;
						node->left->parent = node->parent;
					}
				}

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);
			}
			else
			{
				node_pointer successor = find_successor(node);
				node_pointer new_node = m_Node_Allocator.allocate(1);
				m_Node_Allocator.construct(new_node, node_type(successor->value, *node));
				if (!is_node_empty(node->parent))
				{
					if (node->parent->left == node)
						node->parent->left = new_node;
					else if (node->parent->right == node)
						node->parent->right = new_node;
				}
				if (!is_node_empty(node->left))
					node->left->parent = new_node;
				if (!is_node_empty(node->right))
					node->right->parent = new_node;

				if (m_Root_Node == node)
					m_Root_Node = new_node;

				m_Node_Allocator.destroy(node);
				m_Node_Allocator.deallocate(node, 1);
				
				delete_node(successor);
			}	
		}
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
		node_pointer node = find_smallest();

		if (node != nullptr)
			return (node);
		else
			return (get_end());
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

	size_type	max_size() const
	{
		return (m_Node_Allocator.max_size());
	}

	void	clear()
	{
		delete_tree(m_Root_Node);
	}

	bool	does_node_exist(const value_type &value) const
	{
		node_pointer node = m_Root_Node;

		if (is_node_empty(node))
			return (false);

		while (true)
		{
			if (value.first == node->value.first)
				return (true);
			if (m_Compare(value.first, node->value.first))
			{
				if (is_node_empty(node->left))
					return (false);
				else
					node = node->left;
			}
			else
			{
				if (is_node_empty(node->right))
					return (false);
				else
					node = node->right;
			}
		}
	}

	bool	does_node_exist(const Key &key) const
	{
		node_pointer node = m_Root_Node;

		if (is_node_empty(node))
			return (false);

		while (true)
		{
			if (key == node->value.first)
				return (true);
			if (m_Compare(key, node->value.first))
			{
				if (is_node_empty(node->left))
					return (false);
				else
					node = node->left;
			}
			else
			{
				if (is_node_empty(node->right))
					return (false);
				else
					node = node->right;
			}
		}
	}

	node_pointer	findptr(const Key &key) const
	{
		node_pointer node = m_Root_Node;

		if (is_node_empty(node))
			return (m_End_Node);

		while (true)
		{
			if (key == node->value.first)
				return (node);
			if (m_Compare(key, node->value.first))
			{
				if (is_node_empty(node->left))
					return (m_End_Node);
				else
					node = node->left;
			}
			else
			{
				if (is_node_empty(node->right))
					return (m_End_Node);
				else
					node = node->right;
			}
		}
	}

	void	swap(binary_search_tree &other)
	{
		std::swap(m_Compare, other.m_Compare);
		std::swap(m_Root_Node, other.m_Root_Node);
		std::swap(m_End_Node, other.m_End_Node);
	}

	node_pointer	closest_upper(const Key &key) const
	{
		node_pointer node = m_Root_Node;

		if (is_node_empty(node))
			return (m_End_Node);

		while (true)
		{
			if (key == node->value.first)
				return (node);
			if (m_Compare(key, node->value.first))
			{
				if (is_node_empty(node->left))
					return (node);
				else
					node = node->left;
			}
			else
			{
				if (is_node_empty(node->right))
				{
					while (!is_node_empty(node->parent) && node->parent->left != node)
						node = node->parent;
					if (is_node_empty(node->parent))
						return (m_End_Node);
					else
						return (node->parent);
				}
				else
					node = node->right;
			}
		}
	}

	void	clone(node_pointer node)
	{
		if (is_node_empty(node))
			return;

		add_node(node->value);
		clone(node->left);
		clone(node->right);
	}
};

}

#endif