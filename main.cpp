/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:52:08 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/04 15:45:11 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <vector>
#include <list>
#include "vector.hpp"
#include <iostream>
#include <map>

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

	std::vector<int>::reverse_iterator it3;
	std::vector<int>::reverse_iterator it4;

	ft::vector<int>::reverse_iterator iter3;
	ft::vector<int>::reverse_iterator iter4;

	a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	a.push_back(40);
	a.push_back(50);
	a.push_back(60);
	a.push_back(70);
	a.push_back(80);

	b.push_back(10);
	b.push_back(20);
	b.push_back(30);
	b.push_back(40);
	b.push_back(50);
	b.push_back(60);
	b.push_back(70);
	b.push_back(80);

	it3 = a.rbegin();
	it4 = a.rend();

	iter3 = b.rbegin();
	iter4 = b.rend();

	std::cout << *it3 << std::endl;
	std::cout << *iter3 << std::endl;
	std::cout << *(it4 - 1) << std::endl;
	std::cout << *(iter4 - 1) << std::endl;
}