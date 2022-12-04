/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:58:37 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/05 00:52:46 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP

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
		// Eğer sağın varsa sağının en soluna git
		// Yoksa parentina git o da parentina gitsin taa ki daha büyük valuelu bir şeyle karşılaşana kadar

		if (m_Node->right != nullptr)
		{
			m_Node = m_Node->right;
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
		// Eğer solun varsa solunun en sağına git
		// Yoksa parentina git o da parentina gitsin taa ki daha küçük valuelu bir şeyle karşılaşana kadar

		if (m_Node->left != nullptr)
		{
			m_Node = m_Node->left;
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
		return (*this);
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
		return (*this);
	}

	pointer	operator->(void) const
	{
		return (&m_Node->value);
	}

	reference	operator*(void) const
	{
		return (m_Node->value);
	}

	bool	operator==(const bst_iterator &it)
	{
		return (m_Node == it.m_Node);
	}

	bool	operator!=(const bst_iterator &it)
	{
		return (m_Node != it.m_Node);
	}
};

}

#endif