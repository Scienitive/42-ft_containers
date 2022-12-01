/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:04:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/01 20:59:37 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include "vector.hpp"
#include <iostream>

int main()
{
	std::vector<int> a;
	std::vector<int> t;

	ft::vector<int> b;
	ft::vector<int> s;

	std::vector<int>::iterator it;
	std::vector<int>::iterator it2;

	ft::vector<int>::iterator iter;
	ft::vector<int>::iterator iter2;

	std::list<int>::iterator it3;
	std::list<int>::iterator it4;

	

	a.push_back(10);
	t.push_back(10);

	std::cout << (a < t) << std::endl << std::endl;

	b.push_back(10);
	s.push_back(10);

	std::cout << (b < s) << std::endl;

	/*std::cout << a.capacity() << std::endl;
	a.assign(a.begin()+2, a.begin() + 5);
	for (it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << std::endl;
	}*/

	/*a.insert(a.end(), a.begin() + 3, a.begin() + 3);
	for (it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	
	std::cout << "\n\n-------------------------------\n\n";

	b.insert(b.end(), 10, 5);
	for (iter = b.begin(); iter != b.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}*/
}