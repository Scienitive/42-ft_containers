/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:07:16 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/01 15:00:11 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

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

template<typename T>
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
struct is_integral<short int> : public true_type {};

template<>
struct is_integral<int> : public true_type {};

template<>
struct is_integral<long int> : public true_type {};

template<>
struct is_integral<unsigned short int> : public true_type {};

template<>
struct is_integral<unsigned int> : public true_type {};

template<>
struct is_integral<unsigned long int> : public true_type {};

}

#endif