/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:04:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/11/29 19:23:20 by alyasar          ###   ########.fr       */
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
	a.push_back(30);
	a.push_back(40);
	a.push_back(50);
	a.push_back(60);
	a.push_back(70);
	a.push_back(80);
	a.push_back(90);

	b.push_back(10);
	b.push_back(20);
	b.push_back(30);
	b.push_back(40);
	b.push_back(50);
	b.push_back(60);
	b.push_back(70);
	b.push_back(80);
	b.push_back(90);

	e.push_back(10);
	e.push_back(20);

	it = a.erase(a.begin() + 2, a.begin() + 5);

	std::cout << *it << std::endl << std::endl;

	iter2 = b.erase(b.begin() + 2, b.begin() + 5);

	std::cout << *iter2 << std::endl << std::endl;

	for (iter = b.begin(); iter != b.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
}