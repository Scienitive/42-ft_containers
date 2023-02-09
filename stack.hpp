/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:44:10 by alyasar           #+#    #+#             */
/*   Updated: 2023/02/09 13:51:46 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef typename Container::value_type			value_type;
	typedef typename Container::size_type			size_type;
	typedef typename Container::reference			reference;
	typedef typename Container::const_reference		const_reference;
	typedef Container								container_type;

/* --------------- MEMBER ATTRIBUTES --------------- */
protected:
	container_type	c;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	explicit stack(const Container &cont = Container())
		:	c(cont)
	{
	}

	stack(const stack &other)
		:	c(other.c)
	{
	}

	stack &operator=(const stack &other)
	{
		if (this != &other)
			c = other.c;
		return (*this);
	}

	~stack()
	{
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	reference	top()
	{
		return (c.back());
	}

	const_reference	top() const
	{
		return (c.back());
	}

	bool	empty() const
	{
		return (c.empty());
	}

	size_type	size() const
	{
		return (c.size());
	}

	void	push(const value_type &value)
	{
		c.push_back(value);
	}

	void	pop()
	{
		c.pop_back();
	}

/* --------------- OPERATION OVERLOADS --------------- */
	template<class T1, class Container1>
	friend bool	operator==(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);

	template<class T1, class Container1>
	friend bool	operator<(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);

};

template<class T, class Container>
bool	operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
	return (lhs.c == rhs.c);
}

template<class T, class Container>
bool	operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
	return (!(lhs == rhs));
}

template<class T, class Container>
bool	operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
	return (lhs.c < rhs.c);
}

template<class T, class Container>
bool	operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
	return (rhs < lhs);
}

template<class T, class Container>
bool	operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
	return (!(rhs < lhs));
}

template<class T, class Container>
bool	operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
	return (!(lhs < rhs));
}

}

#endif