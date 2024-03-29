/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:58:00 by alyasar           #+#    #+#             */
/*   Updated: 2023/01/09 15:58:00 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE ITERATOR_HPP

# include "utility.hpp"

namespace ft
{

template<typename T>
struct rbt_node
{
/* --------------- TYPEDEFS --------------- */
	typedef T		    value_type;
    typedef rbt_node *  pointer;   

/* --------------- MEMBER ATTRIBUTES --------------- */
	value_type  *value;
    pointer     parent;
    pointer     left;
    pointer     right;
    bool        is_black;
    bool        is_nil;

/* --------------- CONSTRUCTORS --------------- */
	rbt_node(value_type *val = 0)
		:	 value(val), parent(nullptr), left(nullptr), right(nullptr),is_black(false), is_nil(false)
	{
	}

	rbt_node(const rbt_node &other)
		:	value(other.value), parent(other.parent), left(other.left), right(other.right), is_black(other.is_black), is_nil(other.is_nil)
	{
	}

    rbt_node &operator=(const rbt_node &other)
    {
        value = other.value;
        parent = other.parent;
        left = other.left;
        right = other.right;
        is_black = other.is_black;
        is_nil = other.is_nil;
        return (*this);
    }
};

template<typename T, typename Diff>
class const_rb_tree_iterator;

template<typename T, typename Diff>
class rb_tree_iterator
{
/* --------------- TYPEDEFS --------------- */
public:
    typedef T                                        value_type;
    typedef T &                                      reference;
    typedef T *                                      pointer;
    typedef Diff                                     difference_type;
    typedef std::bidirectional_iterator_tag          iterator_category;
    typedef rbt_node<T> *                            node_pointer;
    typedef const_rb_tree_iterator<T, Diff>          const_iterator;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
    node_pointer    m_Node;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
    rb_tree_iterator()
        :   m_Node(nullptr)
    {
    }

    rb_tree_iterator(node_pointer node)
        :   m_Node(node)
    {
    }

    rb_tree_iterator &operator=(const rb_tree_iterator &other)
    {
        m_Node = other.node();
        return (*this);
    }

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:
    node_pointer    tree_min(node_pointer n) const
    {
        while(n->left != nullptr && !n->left->is_nil)
            n = n->left;
        return (n);
    }

    node_pointer    tree_max(node_pointer n) const
    {
        while(!n->right->is_nil)
            n = n->right;
        return (n);
    }

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
    node_pointer    node() const
    {
        return (m_Node);
    }

/* --------------- OPERATION OVERLOADS --------------- */
public:
    reference   operator*() const
    {
        return (*(m_Node->value));
    }

    pointer     operator->() const
    {
        return (m_Node->value);
    }

    rb_tree_iterator    &operator++()
    {
        if (m_Node->right && !m_Node->right->is_nil)
            m_Node = tree_min(m_Node->right);
        else
        {
            node_pointer y = m_Node->parent;
            while (y != nullptr && m_Node == y->right)
            {
                m_Node = y;
                y = y->parent;
            }
            m_Node = y;
        }
        return (*this);
    }

    rb_tree_iterator    operator++(int)
    {
        rb_tree_iterator temp = *this;
        this->operator++();
        return (temp);
    }

    rb_tree_iterator    &operator--()
    {
        if (m_Node->left && !m_Node->left->is_nil)
            m_Node = tree_max(m_Node->left);
        else
        {
            node_pointer y = m_Node->parent;
            while (y != nullptr && m_Node == y->left)
            {
                m_Node = y;
                y = y->parent;
            }
            m_Node = y;
        }
        return (*this);
    }

    rb_tree_iterator    operator--(int)
    {
        rb_tree_iterator temp = *this;
        this->operator--();
        return (temp);
    }

    bool operator==(const rb_tree_iterator &other) const
    {
        return (m_Node == other.m_Node);
    }

    bool operator==(const const_iterator &other) const
    {
        return (m_Node == other.node());
    }

    bool operator!=(const rb_tree_iterator &other) const
    {
        return (!(*this == other));
    }

    bool operator!=(const const_iterator &other) const
    {
        return (!(*this == other));
    }
};

template<typename T, typename Diff>
class const_rb_tree_iterator
{
/* --------------- TYPEDEFS --------------- */
public:
    typedef T                                                   value_type;
    typedef const T &                                           reference;
    typedef const T *                                           pointer;
    typedef Diff                                                difference_type;
    typedef std::bidirectional_iterator_tag                     iterator_category;
    typedef rbt_node<T> *                                       node_pointer;
    typedef rb_tree_iterator<T, Diff>                           normal_iterator;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
    node_pointer    m_Node;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
    const_rb_tree_iterator()
        :   m_Node(nullptr)
    {
    }

    const_rb_tree_iterator(node_pointer node)
        :   m_Node(node)
    {
    }

    const_rb_tree_iterator(normal_iterator it)
        :   m_Node(it.node())
    {
    }

    const_rb_tree_iterator &operator=(const const_rb_tree_iterator &other)
    {
        m_Node = other.node();
        return (*this);
    }

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:
    node_pointer    tree_min(node_pointer n) const
    {
        while(n->left != nullptr && !n->left->is_nil)
            n = n->left;
        return (n);
    }

    node_pointer    tree_max(node_pointer n) const
    {
        while(!n->right->is_nil)
            n = n->right;
        return (n);
    }

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
    node_pointer    node() const
    {
        return (m_Node);
    }

/* --------------- OPERATION OVERLOADS --------------- */
public:
    reference   operator*() const
    {
        return (*(m_Node->value));
    }

    pointer     operator->() const
    {
        return (m_Node->value);
    }

    const_rb_tree_iterator    &operator++()
    {
        if (m_Node->right && !m_Node->right->is_nil)
            m_Node = tree_min(m_Node->right);
        else
        {
            node_pointer y = m_Node->parent;
            while (y != nullptr && m_Node == y->right)
            {
                m_Node = y;
                y = y->parent;
            }
            m_Node = y;
        }
        return (*this);
    }

    const_rb_tree_iterator    operator++(int)
    {
        const_rb_tree_iterator temp = *this;
        this->operator++();
        return (temp);
    }

    const_rb_tree_iterator    &operator--()
    {
        if (m_Node->left && !m_Node->left->is_nil)
            m_Node = tree_max(m_Node->left);
        else
        {
            node_pointer y = m_Node->parent;
            while (y != nullptr && m_Node == y->left)
            {
                m_Node = y;
                y = y->parent;
            }
            m_Node = y;
        }
        return (*this);
    }

    const_rb_tree_iterator    operator--(int)
    {
        const_rb_tree_iterator temp = *this;
        this->operator--();
        return (temp);
    }

    bool operator==(const const_rb_tree_iterator &other) const
    {
        return (m_Node == other.m_Node);
    }

    bool operator==(const normal_iterator &other) const
    {
        return (m_Node == other.node());
    }

    bool operator!=(const const_rb_tree_iterator &other) const
    {
        return (!(*this == other));
    }

    bool operator!=(const normal_iterator &other) const
    {
        return (!(*this == other));
    }
};

}

#endif