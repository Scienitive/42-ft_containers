/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:52:08 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/05 23:07:36 by alyasar          ###   ########.fr       */
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

	ft::map<int, std::string>	map;
	ft::map<int, std::string>::iterator it;

	map.allah();

	for (it = map.begin(); it != map.end(); it++)
		std::cout << it->first << std::endl;
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;

	/*std::map<int, std::string>	map;

	map[1] = "asdasd";
	map[2] = "rar";
	map[3] = "asda";
	map[7] = "asda";
	map[8] = "asda";
	map[9] = "asda";
	map[10] = "asda";
	map[711] = "asda";

	std::map<int, std::string>::iterator it;
	std::map<int, std::string>::const_iterator it2;

	it = map.end();
	it2 = map.begin();

	std::cout << "Address: " << it._M_node << std::endl;
	it2--;
	std::cout << "Address: " << it2._M_node << std::endl;
	it--;
	std::cout << "Address: " << it._M_node << std::endl << "Value: " << it->first << " + " << "it->second" << std::endl;
	it--;
	std::cout << "Address: " << it._M_node << std::endl << "Value: " << it->first << " + " << it->second << std::endl;
	it--;
	std::cout << "Address: " << it._M_node << std::endl << "Value: " << it->first << " + " << it->second << std::endl;*/
}