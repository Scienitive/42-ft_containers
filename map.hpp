/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:11:23 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/04 21:04:52 by alyasar          ###   ########.fr       */
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
	typedef Key													key_type;
	typedef T													mapped_type;
	typedef typename ft::pair<const Key, T>						value_type;
	typedef Compare												key_compare;
	typedef Allocator											allocator_type;
	typedef typename allocator_type::size_type					size_type;
	typedef typename allocator_type::difference_type			difference_type;
	typedef value_type &										reference;
	typedef const value_type &									const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;
	typedef ft::bst_iterator<value_type, difference_type>		iterator;
	typedef ft::binary_search_tree<value_type>					tree;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	tree	m_Data;

/* --------------- MEMBER CLASSES --------------- */
public:
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		//friend class map; BELKI TYPEDEFLER GEREKEBILIR

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

/* --------------- CONSTRUCTORS AND DESTRUCTORS --------------- */
public:
	map()
	{
	}

	~map()
	{
	}

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
};

}

#endif