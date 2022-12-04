/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:52:08 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/04 21:07:31 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <vector>
#include <list>
#include "vector.hpp"
#include <iostream>
#include <map>
#include "map.hpp"

int main()
{
	/*
	std::map<int, std::string>	map;

	map[1] = "asdasd";
	map[3] = "asda";
	map[2] = "rar";
	map.emplace(1, "sada");

	std::map<int, std::string>::iterator it;
	std::map<int, std::string>::const_iterator it2;


	for (it = map.begin(); it != map.end(); it++)
		std::cout << it->second << std::endl;
	it++;
	if (it == it2)
	{

	}
	std::cout << it->second << std::endl;
	*/

	ft::map<int, std::string>	map;
	ft::map<int, std::string>::iterator it;

	map.allah();
	it = map.begin();
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;
}