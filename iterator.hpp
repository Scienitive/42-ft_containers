/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:11:44 by alyasar           #+#    #+#             */
/*   Updated: 2022/11/29 18:51:56 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

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

}

#endif