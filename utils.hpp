/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 00:35:22 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/07 00:50:20 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

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
bool	lexicographcial_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
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
bool	lexicographcial_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
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


}

#endif