/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:04:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/11/28 19:36:16 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include "vector.hpp"
#include <iostream>

int main()
{
	std::vector<int> a;
	std::list<int> e;

	ft::vector<int> b;

	std::vector<int>::iterator it;
	std::vector<int>::iterator it2;

	ft::vector<int>::iterator iter;
	ft::vector<int>::iterator iter2;

	std::list<int>::iterator it3;
	std::list<int>::iterator it4;

	

	a.push_back(10);
	a.push_back(20);
	b.push_back(10);
	b.push_back(20);
	e.push_back(10);
	e.push_back(20);


	for (iter = b.begin(); iter != b.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
}