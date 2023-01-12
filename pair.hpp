/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:53:36 by alyasar           #+#    #+#             */
/*   Updated: 2023/01/09 15:58:11 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{

template<class T1, class T2>
struct pair
{
/* --------------- TYPEDEFS --------------- */
	typedef T1	first_type;
	typedef T2	second_type;

/* --------------- MEMBER OBJECTS --------------- */
	first_type	first;
	second_type	second;

/* --------------- CONSTRUCTORS --------------- */
	pair()
		:	first(first_type()), second(second_type())
	{
	}

	pair(const first_type &f, const second_type &s)
		:	first(f), second(s)
	{
	}

	template<class U1, class U2>
	pair(const pair<U1, U2> &p)
		:	first(p.first), second(p.second)
	{
	}

	pair(const pair &other)
		:	first(other.first), second(other.second)
	{
	}

	pair &operator=(const pair &other)
	{
		if (*this != other)
		{
			first = other.first;
			second = other.second;
		}
		return (*this);
	}
};

/* --------------- NON-MEMBER FUNCTIONS FOR PAIR --------------- */
template<class T1, class T2>
pair<T1, T2>	make_pair(T1 t, T2 u)
{
	return (pair<T1, T2>(t, u));
}

template<class T1, class T2>
bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template<class T1, class T2>
bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (!(lhs == rhs));
}

template<class T1, class T2>
bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return ((lhs.first < rhs.first) || (lhs.first == rhs.first && lhs.second < rhs.second)); // BURA YANLIS OLABILIR BELKI
}

template<class T1, class T2>
bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (rhs < lhs);
}

template<class T1, class T2>
bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (!(rhs < lhs));
}

template<class T1, class T2>
bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (!(lhs < rhs));
}

}

#endif