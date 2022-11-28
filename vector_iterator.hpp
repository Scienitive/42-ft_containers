/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:52:19 by alyasar           #+#    #+#             */
/*   Updated: 2022/11/28 19:44:22 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft
{

template<typename T, typename Diff>
class vector_iterator
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T								value_type;
	typedef value_type &					reference;
	typedef value_type *					pointer;
	typedef Diff							difference_type;

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
	vector_iterator &operator=(const vector_iterator &it)
	{
		m_Ptr = it.m_Ptr;
		return (*this);
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

	vector_iterator operator+(difference_type n)
	{
		vector_iterator temp(m_Ptr + n);

		return (temp);
	}

	vector_iterator operator-(difference_type n)
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

template<typename T, typename Diff>
bool operator==(const vector_iterator<T, Diff> &ItL, const vector_iterator<T, Diff> &ItR)
{
	return (ItL.base() == ItR.base());
}

template<typename T_L, typename T_R, typename Diff>
bool operator==(const vector_iterator<T_L, Diff> &ItL, const vector_iterator<T_R, Diff> &ItR)
{
	return (ItL.base() == ItR.base());
}

template<typename T, typename Diff>
bool operator!=(const vector_iterator<T, Diff> &ItL, const vector_iterator<T, Diff> &ItR)
{
	return (ItL.base() != ItR.base());
}

template<typename T_L, typename T_R, typename Diff>
bool operator!=(const vector_iterator<T_L, Diff> &ItL, const vector_iterator<T_R, Diff> &ItR)
{
	return (ItL.base() != ItR.base());
}

template<typename T, typename Diff>
bool operator<(const vector_iterator<T, Diff> &ItL, const vector_iterator<T, Diff> &ItR)
{
	return (ItL.base() < ItR.base());
}

template<typename T_L, typename T_R, typename Diff>
bool operator<(const vector_iterator<T_L, Diff> &ItL, const vector_iterator<T_R, Diff> &ItR)
{
	return (ItL.base() < ItR.base());
}

template<typename T, typename Diff>
bool operator<=(const vector_iterator<T, Diff> &ItL, const vector_iterator<T, Diff> &ItR)
{
	return (ItL.base() <= ItR.base());
}

template<typename T_L, typename T_R, typename Diff>
bool operator<=(const vector_iterator<T_L, Diff> &ItL, const vector_iterator<T_R, Diff> &ItR)
{
	return (ItL.base() <= ItR.base());
}

template<typename T, typename Diff>
bool operator>(const vector_iterator<T, Diff> &ItL, const vector_iterator<T, Diff> &ItR)
{
	return (ItL.base() > ItR.base());
}

template<typename T_L, typename T_R, typename Diff>
bool operator>(const vector_iterator<T_L, Diff> &ItL, const vector_iterator<T_R, Diff> &ItR)
{
	return (ItL.base() > ItR.base());
}

template<typename T, typename Diff>
bool operator>=(const vector_iterator<T, Diff> &ItL, const vector_iterator<T, Diff> &ItR)
{
	return (ItL.base() >= ItR.base());
}

template<typename T_L, typename T_R, typename Diff>
bool operator>=(const vector_iterator<T_L, Diff> &ItL, const vector_iterator<T_R, Diff> &ItR)
{
	return (ItL.base() >= ItR.base());
}

template<typename T, typename Diff>
vector_iterator<T, Diff>
operator+(typename vector_iterator<T, Diff>::difference_type n,
	const vector_iterator<T, Diff> &it)
{
	return (vector_iterator<T, Diff>(it.base() + n));
}

template<typename T, typename Diff>
typename vector_iterator<T, Diff>::difference_type
operator-(const vector_iterator<T, Diff> &ItL, const vector_iterator<T, Diff> &ItR)
{
	return (ItL.base() - ItR.base());
}

template<typename T_L, typename T_R, typename Diff>
typename vector_iterator<T_L, Diff>::difference_type
operator-(const vector_iterator<T_L, Diff> &ItL, const vector_iterator<T_R, Diff> &ItR)
{
	return (ItL.base() - ItR.base());
}

}

#endif