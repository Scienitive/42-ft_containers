/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 00:35:22 by alyasar           #+#    #+#             */
/*   Updated: 2023/01/31 16:34:56 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{

template<class InputIt1, class InputIt2>
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	for (; first1 != last1; first1++, first2++)
	{
		if (*first1 != *first2)
			return (false);
	}
	return (true);
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
	for (; first1 != last1; first1++, first2++)
	{
		if (!p(*first1, *first2))
			return (false);
	}
	return (true);
}

template<class InputIt1, class InputIt2>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
	for (; (first1 != last1) && (first2 != last2); first1++, first2++)
	{
		if (*first1 < *first2)
			return (true);
		if (*first2 < *first1)
			return (false);
	}

	return ((first1 == last1) && (first2 != last2));
}

template<class InputIt1, class InputIt2, class Compare>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
	for (; (first1 != last1) && (first2 != last2); first1++, first2++)
	{
		if (comp(*first1, *first2))
			return (true);
		if (comp(*first2, *first1))
			return (false);
	}

	return ((first1 == last1) && (first2 != last2));
}

template<bool B, typename T = void>
struct enable_if
{
};

template<typename T>
struct enable_if<true, T>
{
	typedef T	type;
};


template<typename T, T v>
struct integral_constant
{
	typedef T						value_type;
	typedef integral_constant		type;

	static const value_type value = v;

	operator value_type() const
	{
		return value;
	}
};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template<typename>
struct is_integral : public false_type {};

template<>
struct is_integral<bool> : public true_type {};

template<>
struct is_integral<char> : public true_type {};

template<>
struct is_integral<signed char> : public true_type {};

template<>
struct is_integral<unsigned char> : public true_type {};

template<>
struct is_integral<wchar_t> : public true_type {};

template<>
struct is_integral<char16_t> : public true_type {};

template<>
struct is_integral<short int> : public true_type {};

template<>
struct is_integral<int> : public true_type {};

template<>
struct is_integral<long int> : public true_type {};

template<>
struct is_integral<long long> : public true_type {};

template<>
struct is_integral<unsigned short int> : public true_type {};

template<>
struct is_integral<unsigned int> : public true_type {};

template<>
struct is_integral<unsigned long int> : public true_type {};

template<>
struct is_integral<unsigned long long> : public true_type {};

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