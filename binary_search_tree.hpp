/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:46:30 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/03 01:10:39 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# ifndef nullptr
#  define nullptr NULL
# endif

# include <memory>

template<typename T>
struct bst_node
{
/* --------------- TYPEDEFS --------------- */
	typedef T		value_type;

/* --------------- MEMBER ATTRIBUTES --------------- */
	value_type	value;
	bst_node	*parent;
	bst_node	*left;
	bst_node	*right;

/* --------------- CONSTRUCTORS --------------- */
	bst_node()
		:	parent(nullptr), left(nullptr), right(nullptr)
	{
	}

	bst_node(const value_type &val)
		:	value(val), parent(nullptr), left(nullptr), right(nullptr)
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
};

#endif