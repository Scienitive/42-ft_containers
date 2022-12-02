/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:52:19 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/02 19:18:20 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# ifndef nullptr
#  define nullptr NULL
# endif

# include "iterator.hpp"

namespace ft
{

template<typename T>
class vector_iterator
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T *																iterator_type;
	typedef typename iterator_traits<iterator_type>::value_type				value_type;
	typedef typename iterator_traits<iterator_type>::reference				reference;
	typedef typename iterator_traits<iterator_type>::pointer				pointer;
	typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
	typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	pointer		m_Ptr;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	vector_iterator()
		:	m_Ptr(nullptr)
	{
	}

	vector_iterator(pointer ptr)
		:	m_Ptr(ptr)
	{
	}

	vector_iterator(const vector_iterator &it)
		:	m_Ptr(it.m_Ptr)
	{
	}

	vector_iterator &operator=(const vector_iterator &it)
	{
		if (this != &it)
			m_Ptr = it.m_Ptr;
		return (*this);
	}

	~vector_iterator()
	{
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	pointer base() const
	{
		return (m_Ptr);
	}

/* --------------- OPERATION OVERLOADS --------------- */
public:
	// When iterator casts as const_iterator this operator runs
	operator vector_iterator<const T>(void) const
	{
		return(m_Ptr);
	}

	vector_iterator &operator++(void)
	{
		m_Ptr++;

		return (*this);
	}

	vector_iterator operator++(int)
	{
		vector_iterator temp = *this;
		m_Ptr++;

		return (temp);
	}

	vector_iterator &operator--(void)
	{
		m_Ptr--;

		return (*this);
	}

	vector_iterator operator--(int)
	{
		vector_iterator temp = *this;
		m_Ptr--;

		return (temp);
	}

	pointer operator->(void) const
	{
		return (m_Ptr);
	}

	reference operator*(void) const
	{
		return (*m_Ptr);
	}

	vector_iterator operator+(difference_type n) const
	{
		vector_iterator temp(m_Ptr + n);

		return (temp);
	}

	vector_iterator operator-(difference_type n) const
	{
		vector_iterator temp(m_Ptr - n);

		return (temp);
	}

	vector_iterator &operator+=(difference_type n)
	{
		m_Ptr += n;

		return (*this);
	}

	vector_iterator &operator-=(difference_type n)
	{
		m_Ptr -= n;

		return (*this);
	}

	reference operator[](difference_type n)
	{
		return *(m_Ptr + n);
	}
};

/* --------------- OPERATION OVERLOADS (OUTSIDE CLASS) --------------- */

template<typename T>
bool operator==(const vector_iterator<T> &ItL, const vector_iterator<T> &ItR)
{
	return (ItL.base() == ItR.base());
}

template<typename T_L, typename T_R>
bool operator==(const vector_iterator<T_L> &ItL, const vector_iterator<T_R> &ItR)
{
	return (ItL.base() == ItR.base());
}

template<typename T>
bool operator!=(const vector_iterator<T> &ItL, const vector_iterator<T> &ItR)
{
	return (ItL.base() != ItR.base());
}

template<typename T_L, typename T_R>
bool operator!=(const vector_iterator<T_L> &ItL, const vector_iterator<T_R> &ItR)
{
	return (ItL.base() != ItR.base());
}

template<typename T>
bool operator<(const vector_iterator<T> &ItL, const vector_iterator<T> &ItR)
{
	return (ItL.base() < ItR.base());
}

template<typename T_L, typename T_R>
bool operator<(const vector_iterator<T_L> &ItL, const vector_iterator<T_R> &ItR)
{
	return (ItL.base() < ItR.base());
}

template<typename T>
bool operator<=(const vector_iterator<T> &ItL, const vector_iterator<T> &ItR)
{
	return (ItL.base() <= ItR.base());
}

template<typename T_L, typename T_R>
bool operator<=(const vector_iterator<T_L> &ItL, const vector_iterator<T_R> &ItR)
{
	return (ItL.base() <= ItR.base());
}

template<typename T>
bool operator>(const vector_iterator<T> &ItL, const vector_iterator<T> &ItR)
{
	return (ItL.base() > ItR.base());
}

template<typename T_L, typename T_R>
bool operator>(const vector_iterator<T_L> &ItL, const vector_iterator<T_R> &ItR)
{
	return (ItL.base() > ItR.base());
}

template<typename T>
bool operator>=(const vector_iterator<T> &ItL, const vector_iterator<T> &ItR)
{
	return (ItL.base() >= ItR.base());
}

template<typename T_L, typename T_R>
bool operator>=(const vector_iterator<T_L> &ItL, const vector_iterator<T_R> &ItR)
{
	return (ItL.base() >= ItR.base());
}

template<typename T>
vector_iterator<T>
operator+(typename vector_iterator<T>::difference_type n,
	const vector_iterator<T> &it)
{
	return (vector_iterator<T>(it.base() + n));
}

template<typename T>
typename vector_iterator<T>::difference_type
operator-(const vector_iterator<T> &ItL, const vector_iterator<T> &ItR)
{
	return (ItL.base() - ItR.base());
}

template<typename T_L, typename T_R>
typename vector_iterator<T_L>::difference_type
operator-(const vector_iterator<T_L> &ItL, const vector_iterator<T_R> &ItR)
{
	return (ItL.base() - ItR.base());
}

}

#endif