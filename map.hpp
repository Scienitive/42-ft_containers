/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:35:00 by alyasar           #+#    #+#             */
/*   Updated: 2023/01/09 16:35:00 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "rb_tree.hpp"
# include "type_traits.hpp"

namespace ft
{

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
/* --------------- TYPEDEFS --------------- */
public:
    typedef Key                                                                     key_type;
    typedef T                                                                       mapped_type;
    typedef ft::pair<const Key, T>													value_type;
	typedef Compare																	key_compare;
	typedef Allocator																allocator_type;
	typedef typename allocator_type::size_type										size_type;
	typedef typename allocator_type::difference_type								difference_type;
	typedef value_type &															reference;
	typedef const value_type &														const_reference;
    typedef typename allocator_type::pointer										pointer;
	typedef typename allocator_type::const_pointer									const_pointer;

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

/* --------------- TYPEDEFS --------------- */
public:
    typedef rb_tree<value_type, value_compare, allocator_type>						tree_type;
	typedef typename tree_type::iterator											iterator;
	typedef typename tree_type::const_iterator										const_iterator;
	typedef typename tree_type::reverse_iterator									reverse_iterator;
	typedef typename tree_type::const_reverse_iterator								const_reverse_iterator;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	allocator_type	m_Allocator;
	key_compare		m_Compare;
	tree_type		m_Data;

/* --------------- CONSTRUCTORS AND DESTRUCTORS --------------- */
public:
	map()
		:	m_Allocator(allocator_type()), m_Compare(key_compare()), m_Data(tree_type(key_compare(), allocator_type()))
	{
	}

	explicit map(const key_compare &comp, const allocator_type &alloc = allocator_type())
		:	m_Allocator(alloc), m_Compare(comp), m_Data(comp, alloc)
	{
	}

	template<class InputIt>
	map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		:	m_Allocator(alloc), m_Compare(comp), m_Data(first, last, comp, alloc)
	{
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	allocator_type	get_allocator() const
	{
		return (m_Data.get_allocator());
	}

	size_type	size() const
	{
		return (m_Data.size());
	}

	size_type	max_size() const
	{
		return (m_Data.max_size());
	}

	bool	empty() const
	{
		return (m_Data.empty());
	}

	value_compare	value_comp() const
	{
		return (m_Data.value_comp());
	}

	key_compare		key_comp() const
	{
		return (m_Compare);
	}

	iterator	begin()
	{
		return (m_Data.begin());
	}

	iterator	end()
	{
		return(m_Data.end());
	}

	reverse_iterator	rbegin()
	{
		return (m_Data.rbegin());
	}

	reverse_iterator	rend()
	{
		return (m_Data.rend());
	}

	void	clear()
	{
		m_Data.clear();
	}

	ft::pair<iterator, bool>	insert(const value_type &value)
	{
		return (m_Data.insert(value));
	}

	iterator	insert(iterator hint, const value_type &value)
	{
		return (m_Data.insert(hint, value));
	}

	template<class InputIt>
	void	insert(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
	{
		m_Data.insert(first, last);
	}

	void	erase(iterator pos)
	{
		m_Data.erase(pos);
	}

	size_type	erase(const Key &key)
	{
		return (m_Data.erase(ft::make_pair(key, mapped_type())));
	}

	void	erase(iterator first, iterator last)
	{
		m_Data.erase(first, last);
	}

	iterator	find(const Key &key)
	{
		return (m_Data.find(ft::make_pair(key, mapped_type())));
	}

	size_type	count(const Key &key)
	{
		return (m_Data.count(ft::make_pair(key, mapped_type())));
	}

	void	swap(const map &other)
	{
		std::swap(m_Allocator, other.m_Allocator);
		std::swap(m_Compare, other.m_Compare);
		m_Data.swap(other.m_Data);
	}

	iterator	lower_bound(const key_type &key)
	{
		return (m_Data.lower_bound(ft::make_pair(key, mapped_type())));
	}

	iterator	upper_bound(const key_type &key)
	{
		return (m_Data.upper_bound(ft::make_pair(key, mapped_type())));
	}

	ft::pair<iterator, iterator>	equal_range(const key_type &key)
	{
		return (m_Data.equal_range(ft::make_pair(key, mapped_type())));
	}

	T	&at(const Key &key)
	{
		iterator res = m_Data.find(ft::make_pair(key, mapped_type()));
		if (res == m_Data.end())
			throw std::out_of_range("Exception: Key not found.");
		return (res->second);
	}

/* --------------- OPERATION OVERLOADS --------------- */
public:
	mapped_type	&operator[](const Key &key)
	{
		return ((*((insert(ft::make_pair(key, mapped_type()))).first)).second);
	}

/* --------------- FRIEND OPERATIONS --------------- */
public:
	template<class _Key, class _T, class _Compare, class _Alloc>
	friend bool operator==(const map<_Key, _T, _Compare, _Alloc> &lhs, const map<_Key, _T, _Compare, _Alloc> &rhs);

	template<class _Key, class _T, class _Compare, class _Alloc>
	friend bool operator<(const map<_Key, _T, _Compare, _Alloc> &lhs, const map<_Key, _T, _Compare, _Alloc> &rhs);
};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (lhs.m_Data == rhs.m_Data); 
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (!(lhs == rhs)); 
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (lhs.m_Data < rhs.m_Data);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (!(rhs < lhs));
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
	return (!(lhs < rhs));
}

}

namespace std
{
	template<class Key, class T, class Compare, class Alloc>
	void swap(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif