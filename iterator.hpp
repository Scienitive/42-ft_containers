/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:11:44 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/02 19:31:40 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# ifndef nullptr
#  define nullptr NULL
# endif

# include <iterator>

namespace ft
{

template<typename T>
struct iterator_traits
{
	typedef typename T::value_type				value_type;
	typedef typename T::pointer					pointer;
	typedef typename T::reference				reference;
	typedef typename T::difference_type			difference_type;
	typedef typename T::iterator_category		iterator_category;
};

template<typename T>
struct iterator_traits<T*>
{
	typedef T									value_type;
	typedef T *									pointer;
	typedef T &									reference;
	typedef std::ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag		iterator_category;
};

template<typename T>
struct iterator_traits<const T*>
{
	typedef T									value_type;
	typedef const T *							pointer;
	typedef const T &							reference;
	typedef std::ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag		iterator_category;
};

template<typename It>
class reverse_iterator
: public std::iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type, typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer, typename iterator_traits<It>::reference>
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef It																iterator_type;
	typedef typename iterator_traits<iterator_type>::value_type				value_type;
	typedef typename iterator_traits<iterator_type>::reference				reference;
	typedef typename iterator_traits<iterator_type>::pointer				pointer;
	typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
	typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	iterator_type m_Iterator;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	reverse_iterator()
		:	m_Iterator(nullptr)
	{
	}

	reverse_iterator(const reverse_iterator &other)
		:	m_Iterator(other.m_Iterator)
	{
	}

	explicit reverse_iterator(iterator_type it)
		:	m_Iterator(it)
	{
	}

	template<typename Iter>
	reverse_iterator (const reverse_iterator<Iter> &other)
		:	m_Iterator(other.base())
	{
	}

	reverse_iterator &operator=(const reverse_iterator &other)
	{
		if (this != &other)
			m_Iterator = other.m_Iterator;
		return (*this);
	}

	~reverse_iterator()
	{
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	iterator_type	base() const
	{
		return (m_Iterator);
	}

/* --------------- OPERATION OVERLOADS --------------- */
public:
	template<typename T>
	reverse_iterator	&operator=(const reverse_iterator<T> &other)
	{
		m_Iterator = other.base();

		return (*this);
	}

	reference	operator*() const
	{
		iterator_type temp = m_Iterator;
		--temp;

		return (*temp);
	}

	pointer	operator->() const
	{
		return (&(operator*()));
	}

	reference	operator[](difference_type n) const
	{
		return (*(*this + n));
	}

	reverse_iterator	operator+(difference_type n) const
	{
		return (reverse_iterator(m_Iterator - n));
	}

	reverse_iterator	operator+=(difference_type n)
	{
		m_Iterator -= n;
		return (*this);
	}

	reverse_iterator	operator-(difference_type n) const
	{
		return (reverse_iterator(m_Iterator + n));
	}

	reverse_iterator	operator-=(difference_type n)
	{
		m_Iterator += n;
		return (*this);
	}

	reverse_iterator	&operator++()
	{
		--m_Iterator;
		return (*this);
	}

	reverse_iterator	&operator--()
	{
		++m_Iterator;
		return (*this);
	}

	reverse_iterator	operator++(int)
	{
		reverse_iterator temp = *this;
		--m_Iterator;
		return (temp);
	}

	reverse_iterator	operator--(int)
	{
		reverse_iterator temp = *this;
		++m_Iterator;
		return (temp);
	}
};

/* --------------- OPERATION OVERLOADS (OUTSIDE CLASS) --------------- */
template<typename It>
bool operator==(const reverse_iterator<It> &ItL, const reverse_iterator<It> &ItR)
{
	return (ItL.base() == ItR.base());
}

template<typename It_L, typename It_R>
bool operator==(const reverse_iterator<It_L> &ItL, const reverse_iterator<It_R> &ItR)
{
	return (ItL.base() == ItR.base());
}

template<typename It>
bool operator!=(const reverse_iterator<It> &ItL, const reverse_iterator<It> &ItR)
{
	return (ItL.base() != ItR.base());
}

template<typename It_L, typename It_R>
bool operator!=(const reverse_iterator<It_L> &ItL, const reverse_iterator<It_R> &ItR)
{
	return (ItL.base() != ItR.base());
}

template<typename It>
bool operator<(const reverse_iterator<It> &ItL, const reverse_iterator<It> &ItR)
{
	return (ItL.base() > ItR.base());
}

template<typename It_L, typename It_R>
bool operator<(const reverse_iterator<It_L> &ItL, const reverse_iterator<It_R> &ItR)
{
	return (ItL.base() > ItR.base());
}

template<typename It>
bool operator<=(const reverse_iterator<It> &ItL, const reverse_iterator<It> &ItR)
{
	return (ItL.base() >= ItR.base());
}

template<typename It_L, typename It_R>
bool operator<=(const reverse_iterator<It_L> &ItL, const reverse_iterator<It_R> &ItR)
{
	return (ItL.base() >= ItR.base());
}

template<typename It>
bool operator>(const reverse_iterator<It> &ItL, const reverse_iterator<It> &ItR)
{
	return (ItL.base() < ItR.base());
}

template<typename It_L, typename It_R>
bool operator>(const reverse_iterator<It_L> &ItL, const reverse_iterator<It_R> &ItR)
{
	return (ItL.base() < ItR.base());
}

template<typename It>
bool operator>=(const reverse_iterator<It> &ItL, const reverse_iterator<It> &ItR)
{
	return (ItL.base() <= ItR.base());
}

template<typename It_L, typename It_R>
bool operator>=(const reverse_iterator<It_L> &ItL, const reverse_iterator<It_R> &ItR)
{
	return (ItL.base() <= ItR.base());
}

template<typename It>
reverse_iterator<It>
operator+(typename reverse_iterator<It>::difference_type n,
	const reverse_iterator<It> &it)
{
	return (reverse_iterator<It>(it.base() - n));
}

template<typename It>
typename reverse_iterator<It>::difference_type
operator-(const reverse_iterator<It> &ItL, const reverse_iterator<It> &ItR)
{
	return (ItR.base() - ItL.base());
}

template<typename It_L, typename It_R>
typename reverse_iterator<It_L>::difference_type
operator-(const reverse_iterator<It_L> &ItL, const reverse_iterator<It_R> &ItR)
{
	return (ItR.base() - ItL.base());
}

}

#endif