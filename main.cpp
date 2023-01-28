/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:52:08 by alyasar           #+#    #+#             */
/*   Updated: 2023/01/28 21:45:27 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <vector>
#include <list>
#include "vector.hpp"
#include <iostream>
#include <map>
#include "map.hpp"

#include "pair.hpp"

#include <iomanip>
#include <chrono> // C++11

std::chrono::high_resolution_clock::time_point	start, end; // C++11

void set_time()
{
	start = std::chrono::high_resolution_clock::now();
}

void get_time(const char *str)
{
	end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	printf("%s Time measured: %ldns\n", str, elapsed.count());
}

void vector_test()
{
	std::vector<int>	sv;
	ft::vector<int>		v;
	
	srand(time(0));

	for (int i = 0; i < 1000; ++i)
	{
		int nmb = rand() % 100000;
		sv.push_back(nmb);
		v.push_back(nmb);
	}
	for (int i = 0; i < 1000; ++i)
	{
		if (sv[i] != v[i])
			std::cout << "ERROR!" << std::endl;
	}

	int nmb = rand() % 100000;
	set_time();
	sv.push_back(nmb);
	get_time("std::vector");

	set_time();
	v.push_back(nmb);
	get_time("ft::vector");

	std::cout << "\n";

	set_time();
	std::cout << "Size of std::vector = " << sv.size() << std::endl;
	get_time("std::vector");

	set_time();
	std::cout << "Size of ft::vector =  " << v.size() << std::endl;
	get_time("ft::vector");

	std::cout << "\n";

	int a = rand() % 1000;
	std::cout << a << "\'th index of std::vector = " << sv.at(a) << std::endl;
	std::cout << a << "\'th index of ft::vector =  " << v.at(a) << std::endl;

	std::cout << "\n";

	std::cout << sv.front() << std::endl;
	std::cout << v.front() << std::endl;
	std::cout << sv.back() << std::endl;
	std::cout << v.back() << std::endl;

	std::cout << "\n";

	set_time();
	sv.assign(5, 5);
	get_time("std::vector");

	set_time();
	v.assign(5, 5);
	get_time("ft::vector");

	std::cout << "Context of std::vector \n";
	for (std::vector<int>::iterator it = sv.begin(); it != sv.end(); ++it)
		std::cout << *it << " ";

	std::cout << "\nContext of ft::vector \n";
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";

	std::cout << "\n\n";

	std::cout << "Size of std::vector = " << sv.size() << std::endl;
	std::cout << "Size of ft::vector =  " << v.size() << std::endl;

	std::cout << "\n";

	std::cout << "Capacity of std::vector = " << sv.capacity() << std::endl;
	std::cout << "Capacity of ft::vector =  " << v.capacity() << std::endl;

	std::cout << "\n";

	set_time();
	sv.reserve(2000);
	get_time("std::vector");

	set_time();
	v.reserve(2000);
	get_time("ft::vector");

	std::cout << "\nCapacity of std::vector = " << sv.capacity() << std::endl;
	std::cout << "Capacity of ft::vector =  " << v.capacity() << std::endl;

	std::cout << "\n";

	sv.clear();
	v.clear();

	std::cout << "Is empty std::vector = " << sv.empty() << std::endl;
	std::cout << "Is empty ft::vector =  " << v.empty() << std::endl;

	std::cout << "\n";

	for (int i = 0; i < 1000; ++i)
	{
		int nmb = rand() % 100000;
		sv.push_back(nmb);
		v.push_back(nmb);
	}

	set_time();
	sv.insert(sv.begin() + 200, 99);
	get_time("std::vector");

	set_time();
	v.insert(v.begin() + 200, 99);
	get_time("ft::vector");

	std::cout << "\n200th index of std::vector = " << sv[200] << std::endl;
	std::cout << "200th index of ft::vector =  " << v[200] << std::endl;

	std::cout << "\n";

	std::cout << "Size of std::vector = " << sv.size() << std::endl;
	std::cout << "Size of ft::vector =  " << v.size() << std::endl;

	std::cout << "\n";

	std::cout << "Max size of std::vector = " << sv.max_size() << std::endl;
	std::cout << "Max size of ft::vector =  " << v.max_size() << std::endl;

	std::cout << "\n";

	set_time();
	sv.insert(sv.begin() + 100, 3, 999);
	get_time("std::vector");

	set_time();
	v.insert(v.begin() + 100, 3, 999);
	get_time("ft::vector");

	std::cout << "\n100th index of std::vector = " << sv[100] << std::endl;
	std::cout << "100th index of ft::vector =  " << v[100] << std::endl;
	std::cout << "101th index of std::vector = " << sv[101] << std::endl;
	std::cout << "101th index of ft::vector =  " << v[101] << std::endl;
	std::cout << "102th index of std::vector = " << sv[102] << std::endl;
	std::cout << "102th index of ft::vector =  " << v[102] << std::endl;

	std::cout << "\n";

	sv.insert(sv.begin(), sv.begin() + 10, sv.begin() + 15);
	v.insert(v.begin(), v.begin() + 10, v.begin() + 15);

	std::cout << "Context of std::vector \n";
	for (std::vector<int>::iterator it = sv.begin() + 10; it != sv.begin() + 15; ++it)
		std::cout << *it << " ";

	std::cout << "\nContext of std::vector \n";
	for (std::vector<int>::iterator it = sv.begin(); it != sv.begin() + 5; ++it)
		std::cout << *it << " ";

	std::cout << "\nContext of ft::vector \n";
	for (ft::vector<int>::iterator it = v.begin() + 10; it != v.begin() + 15; ++it)
		std::cout << *it << " ";

	std::cout << "\nContext of ft::vector \n";
	for (ft::vector<int>::iterator it = v.begin(); it != v.begin() + 5; ++it)
		std::cout << *it << " ";

	std::cout << "\n\n";
	
	ft::vector<int> v1;
	ft::vector<int> v2;

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(10);
	v2.push_back(20);
	v2.push_back(30);

	ft::vector<int>::iterator it1 = v1.begin() + 1;
	ft::vector<int>::iterator it2 = v2.begin() + 1;

	std::cout << *it1 << std::endl;
	std::cout << *it2 << std::endl;

	v1.swap(v2);

	std::cout << *it1 << std::endl;
	std::cout << *it2 << std::endl;

	it1++;
	it2++;

	std::cout << *it1 << std::endl;
	std::cout << *it2 << std::endl;

	ft::vector<int>::const_iterator cit = v2.begin() + 2;

	if (it1 == cit)
		std::cout << "\nconst_iterator and iterator is comparable.\n";
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

void	printSize(ft::map<int, std::string> const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename ft::map<int, std::string>::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

static int iter = 0;

template<typename U, typename V>
void	ft_erase(ft::map<int, std::string> &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}

template<typename U>
void	ft_erase(ft::map<int, std::string> &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

void	custom_test()
{
	std::list<ft::pair<const int, std::string>> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::make_pair(i, std::string((lst_size - i), i + 65)));
	ft::map<int, std::string> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_erase(mp, ++mp.begin());
}

int main()
{
	/*std::list<ft::pair<const int, std::string>> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::make_pair(i, std::string((lst_size - i), i + 65)));
	ft::map<int, std::string> mp(lst.begin(), lst.end());*/

	ft::map<int, std::string> mp;

	mp[0] = "AAAAAAAAAA";
	mp[1] = "BBBBBBBBB";
	mp[2] = "CCCCCCCC";
	mp[3] = "DDDDDDD";
	mp[4] = "EEEEEE";
	mp[5] = "FFFFF";
	mp[6] = "GGGG";
	mp[7] = "HHH";
	mp[8] = "II";
	mp[9] = "J";

	std::cout << (mp.lower_bound(5))->first;
	std::cout << (mp.upper_bound(3))->first;
	/*std::cout << mp.begin()->second << std::endl;
	std::cout << (++mp.begin())->second << std::endl << std::endl;

	mp.erase(++mp.begin());*/

	//custom_test();
	//vector_test();
}

