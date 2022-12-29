/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:58:37 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/29 17:13:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP

# include <cstddef> // BUNU EN SON SİL
# ifndef nullptr
#  define nullptr NULL
# endif

# include "binary_search_tree.hpp"

namespace ft
{

template<typename T, typename D>
class bst_iterator
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T									value_type;
	typedef T &									reference;
	typedef T *									pointer;
	typedef D									difference_type;
	typedef std::bidirectional_iterator_tag		iterator_category;
	typedef bst_node<value_type>				node_type;
	typedef node_type *							node_pointer;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	node_pointer	m_Node;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	bst_iterator()
		:	m_Node(nullptr)
	{
	}

	bst_iterator(node_pointer node)
		:	m_Node(node)
	{
	}

	bst_iterator(const bst_iterator &it)
		:	m_Node(it.m_Node)
	{
	}

	bst_iterator &operator=(const bst_iterator &it)
	{
		if (this != &it)
			m_Node = it.m_Node;
		return (*this);
	}

	~bst_iterator()
	{
	}

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:
	void	bst_increment(void)
	{
		// End_Node için özel durumlar
		// Eğer sağın varsa sağının en soluna git
		// Yoksa parentina git o da parentina gitsin taa ki daha büyük valuelu bir şeyle karşılaşana kadar

		if (m_Node->is_end_node)
		{
			m_Node = m_Node->right;
			return;
		}
		if (m_Node->right != nullptr)
		{
			m_Node = m_Node->right;
			if (m_Node->is_end_node)
				return;
			while (m_Node->left != nullptr)
				m_Node = m_Node->left;
		}
		else
		{
			while (m_Node != nullptr && m_Node->parent != nullptr && m_Node->parent->left != m_Node)
			{
				m_Node = m_Node->parent;
			}
			if (m_Node != nullptr && m_Node->parent != nullptr)
				m_Node = m_Node->parent;
			else
				m_Node = nullptr;
		}
	}

	void	bst_decrement(void)
	{
		// End_Node için özel durumlar
		// Eğer solun varsa solunun en sağına git
		// Yoksa parentina git o da parentina gitsin taa ki daha küçük valuelu bir şeyle karşılaşana kadar

		if (m_Node->is_end_node)
		{
			m_Node = m_Node->left;
			return;
		}
		if (m_Node->left != nullptr)
		{
			m_Node = m_Node->left;
			if (m_Node->is_end_node)
				return;
			while (m_Node->right != nullptr)
				m_Node = m_Node->right;
		}
		else
		{
			while (m_Node != nullptr && m_Node->parent != nullptr && m_Node->parent->right != m_Node)
			{
				m_Node = m_Node->parent;
			}
			if (m_Node != nullptr && m_Node->parent != nullptr)
				m_Node = m_Node->parent;
			else
				m_Node = nullptr;
		}
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	node_pointer	&base()
	{
		return (m_Node);
	}

	const node_pointer	&base() const
	{
		return (m_Node);
	}

/* --------------- OPERATION OVERLOADS --------------- */
public:
	bst_iterator	&operator++(void)
	{
		bst_increment();
		return (*this);
	}

	bst_iterator	operator++(int)
	{
		bst_iterator temp = *this;
		bst_increment();
		return (temp);
	}

	bst_iterator	&operator--(void)
	{
		bst_decrement();
		return (*this);
	}

	bst_iterator	operator--(int)
	{
		bst_iterator temp = *this;
		bst_decrement();
		return (temp);
	}

	pointer	operator->(void) const
	{
		return (&m_Node->value);
	}

	reference	operator*(void) const
	{
		return (m_Node->value);
	}

	bool	operator==(const bst_iterator &it) const
	{
		return (m_Node == it.m_Node);
	}

	bool	operator!=(const bst_iterator &it) const
	{
		return (m_Node != it.m_Node);
	}
};

template<typename T, typename D>
class const_bst_iterator
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T									value_type;
	typedef const T &							reference;
	typedef const T *							pointer;
	typedef D									difference_type;
	typedef std::bidirectional_iterator_tag		iterator_category;
	typedef bst_node<value_type>				node_type;
	typedef node_type *							node_pointer;
	typedef bst_iterator<T, D>					non_const_iterator;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	node_pointer	m_Node;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	const_bst_iterator()
		:	m_Node(nullptr)
	{
	}

	const_bst_iterator(node_pointer node)
		:	m_Node(node)
	{
	}

	const_bst_iterator(const const_bst_iterator &it)
		:	m_Node(it.m_Node)
	{
	}

	const_bst_iterator(const non_const_iterator &it)
		:	m_Node(it.base())
	{
	}

	const_bst_iterator &operator=(const const_bst_iterator &it)
	{
		if (this != &it)
			m_Node = it.m_Node;
		return (*this);
	}

	~const_bst_iterator()
	{
	}

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:
	void	bst_increment(void)
	{
		// End_Node için özel durumlar
		// Eğer sağın varsa sağının en soluna git
		// Yoksa parentina git o da parentina gitsin taa ki daha büyük valuelu bir şeyle karşılaşana kadar

		if (m_Node->is_end_node)
		{
			m_Node = m_Node->right;
			return;
		}
		if (m_Node->right != nullptr)
		{
			m_Node = m_Node->right;
			if (m_Node->is_end_node)
				return;
			while (m_Node->left != nullptr)
				m_Node = m_Node->left;
		}
		else
		{
			while (m_Node != nullptr && m_Node->parent != nullptr && m_Node->parent->left != m_Node)
			{
				m_Node = m_Node->parent;
			}
			if (m_Node != nullptr && m_Node->parent != nullptr)
				m_Node = m_Node->parent;
			else
				m_Node = nullptr;
		}
	}

	void	bst_decrement(void)
	{
		// End_Node için özel durumlar
		// Eğer solun varsa solunun en sağına git
		// Yoksa parentina git o da parentina gitsin taa ki daha küçük valuelu bir şeyle karşılaşana kadar

		if (m_Node->is_end_node)
		{
			m_Node = m_Node->left;
			return;
		}
		if (m_Node->left != nullptr)
		{
			m_Node = m_Node->left;
			if (m_Node->is_end_node)
				return;
			while (m_Node->right != nullptr)
				m_Node = m_Node->right;
		}
		else
		{
			while (m_Node != nullptr && m_Node->parent != nullptr && m_Node->parent->right != m_Node)
			{
				m_Node = m_Node->parent;
			}
			if (m_Node != nullptr && m_Node->parent != nullptr)
				m_Node = m_Node->parent;
			else
				m_Node = nullptr;
		}
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	node_pointer	&base()
	{
		return (m_Node);
	}

	const node_pointer	&base() const
	{
		return (m_Node);
	}

/* --------------- OPERATION OVERLOADS --------------- */
public:
	const_bst_iterator	&operator++(void)
	{
		bst_increment();
		return (*this);
	}

	const_bst_iterator	operator++(int)
	{
		const_bst_iterator temp = *this;
		bst_increment();
		return (temp);
	}

	const_bst_iterator	&operator--(void)
	{
		bst_decrement();
		return (*this);
	}

	const_bst_iterator	operator--(int)
	{
		const_bst_iterator temp = *this;
		bst_decrement();
		return (temp);
	}

	pointer	operator->(void) const
	{
		return (&m_Node->value);
	}

	reference	operator*(void) const
	{
		return (m_Node->value);
	}

	bool	operator==(const const_bst_iterator &it) const
	{
		return (m_Node == it.m_Node);
	}

	bool	operator!=(const const_bst_iterator &it) const
	{
		return (m_Node != it.m_Node);
	}
};

}

#endif