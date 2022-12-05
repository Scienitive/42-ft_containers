/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:11:23 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/05 23:33:25 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "pair.hpp"
# include "binary_search_tree.hpp"
# include "bst_iterator.hpp"

namespace ft
{

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef Key																		key_type;
	typedef T																		mapped_type;
	typedef typename ft::pair<const Key, T>											value_type;
	typedef Compare																	key_compare;
	typedef Allocator																allocator_type;
	typedef typename allocator_type::size_type										size_type;
	typedef typename allocator_type::difference_type								difference_type;
	typedef value_type &															reference;
	typedef const value_type &														const_reference;
	typedef typename allocator_type::pointer										pointer;
	typedef typename allocator_type::const_pointer									const_pointer;
	typedef ft::bst_iterator<value_type, difference_type>							iterator;
	typedef ft::binary_search_tree<value_type, key_type, mapped_type, key_compare>	tree;

/* --------------- MEMBER CLASSES --------------- */
public:
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map;

	/* --------------- MEMBER OBJECTS --------------- */
	protected:
		Compare	comp;

	/* --------------- CONSTRUCTORS --------------- */
	protected:
		value_compare(Compare c)
			:	comp(c)
		{
		}
	
	/* --------------- MEMBER FUNCTIONS --------------- */
	public:
		bool	operator()(const value_type &lhs, const value_type &rhs) const
		{
			return (comp(lhs.first, rhs.first));
		}
	};

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	value_compare	m_Compare;
	tree			m_Data;

/* --------------- CONSTRUCTORS AND DESTRUCTORS --------------- */
public:
	map()
		:	m_Compare(Compare()), m_Data(tree())
	{
	}

	explicit map(const key_compare &comp, const allocator_type &alloc = allocator_type())
		:	m_Compare(comp), m_Data(tree(comp))
	{
	}

	// BIR CONSTRUCTOR VAR

	map(const map &other)
		:	m_Compare(other.m_Compare), m_Data(other.m_Data)
	{
	}

	map	&operator=(const map &other)
	{
		if (*this != other)
		{
			m_Compare = other.m_Compare;
			m_Data = other.m_Data;
		}
		return (*this);
	}

	~map()
	{
	}

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:

	

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	void	allah()
	{
		m_Data.add_node(ft::pair<int, std::string>(50, "50"));
		m_Data.add_node(ft::pair<int, std::string>(40, "40"));
		m_Data.add_node(ft::pair<int, std::string>(60, "60"));
		m_Data.add_node(ft::pair<int, std::string>(70, "70"));
		m_Data.add_node(ft::pair<int, std::string>(80, "80"));
	}

	iterator begin()
	{
		return (iterator(m_Data.get_root()));
	}

	iterator end()
	{
		return (iterator(m_Data.get_end()));
	}

	allocator_type	get_allocator() const // Bu çalışmazsa private attribute olarak alloc yap
	{
		return (allocator_type());
	}

	T	&at(const Key &key)
	{
		return (m_Data.find(key));
	}

	const T	&at(const Key &key) const
	{
		return (m_Data.const_find(key));
	}
};

}

#endif