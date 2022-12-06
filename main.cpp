/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:52:08 by alyasar           #+#    #+#             */
/*   Updated: 2022/12/06 18:47:31 by alyasar          ###   ########.fr       */
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
	std::map<int, std::string>	stdmap;
	std::map<int, std::string>::iterator stdit;
	std::map<int, std::string>::const_iterator cstdit;

	ft::map<int, std::string>	map;
	ft::map<int, std::string>::iterator it;
	ft::map<int, std::string>::const_iterator cit;

	/*map[50] = "50";
	map[40] = "40";
	map[60] = "60";
	map[70] = "70";
	map[10] = "10";
	map[45] = "45";
	//it = map.insert(ft::make_pair(50, "20")).first;

	//std::cout << it->first << std::endl;

	//map.clear();

	std::cout << map.size() << std::endl;

	it = map.begin();

	for (; it != map.end(); it++)
		std::cout << it->second << std::endl;*/

	stdmap[50] = "50";
	stdmap[40] = "40";
	stdmap[60] = "60";
	stdmap[70] = "70";
	stdmap[10] = "10";
	stdmap[45] = "45";
	bool a = stdmap.insert(std::make_pair(20, "20")).second;

	std::cout << a << std::endl;

	//stdmap.clear();

	std::cout << stdmap.size() << std::endl;

	stdit = stdmap.begin();

	for (; stdit != stdmap.end(); stdit++)
		std::cout << stdit->second << std::endl;

	//std::cout << map.size() << std::endl;

	//cstdit = stdmap.begin();

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