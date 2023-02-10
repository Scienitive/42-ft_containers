/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:52:08 by alyasar           #+#    #+#             */
/*   Updated: 2023/02/09 15:18:40 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>

#include <map>
#include <stack>
#include <vector>
#include <list>

#if 0 // CREATE A REAL STL EXAMPLE
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int defaultMain(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
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
	sv.push_back(nmb);
	v.push_back(nmb);

	std::cout << "\n";

	std::cout << "Size of std::vector = " << sv.size() << std::endl;
	std::cout << "Size of ft::vector  = " << v.size() << std::endl;

	std::cout << "\n";

	int a = rand() % 1000;
	std::cout << a << "\'th index of std::vector = " << sv.at(a) << std::endl;
	std::cout << a << "\'th index of ft::vector  = " << v.at(a) << std::endl;

	std::cout << "\n";

	std::cout << sv.front() << std::endl;
	std::cout << v.front() << std::endl;
	std::cout << sv.back() << std::endl;
	std::cout << v.back() << std::endl;

	std::cout << "\n";

	sv.assign(5, 5);
	v.assign(5, 5);

	std::cout << "Context of std::vector \n";
	for (std::vector<int>::iterator it = sv.begin(); it != sv.end(); ++it)
		std::cout << *it << " ";

	std::cout << "\nContext of ft::vector \n";
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";

	std::cout << "\n\n";

	std::cout << "Size of std::vector = " << sv.size() << std::endl;
	std::cout << "Size of ft::vector  = " << v.size() << std::endl;

	std::cout << "\n";

	std::cout << "Capacity of std::vector = " << sv.capacity() << std::endl;
	std::cout << "Capacity of ft::vector  = " << v.capacity() << std::endl;

	std::cout << "\n";

	sv.reserve(2000);
	v.reserve(2000);

	std::cout << "Capacity of std::vector = " << sv.capacity() << std::endl;
	std::cout << "Capacity of ft::vector  = " << v.capacity() << std::endl;

	std::cout << "\n";

	sv.clear();
	v.clear();

	std::cout << "Is empty std::vector = " << sv.empty() << std::endl;
	std::cout << "Is empty ft::vector  = " << v.empty() << std::endl;

	std::cout << "\n";

	for (int i = 0; i < 1000; ++i)
	{
		int nmb = rand() % 100000;
		sv.push_back(nmb);
		v.push_back(nmb);
	}

	sv.insert(sv.begin() + 200, 99);
	v.insert(v.begin() + 200, 99);

	std::cout << "200th index of std::vector = " << sv[200] << std::endl;
	std::cout << "200th index of ft::vector  = " << v[200] << std::endl;

	std::cout << "\n";

	std::cout << "Size of std::vector = " << sv.size() << std::endl;
	std::cout << "Size of ft::vector  = " << v.size() << std::endl;

	std::cout << "\n";

	sv.insert(sv.begin() + 100, 3, 999);
	v.insert(v.begin() + 100, 3, 999);

	std::cout << "100th index of std::vector = " << sv[100] << std::endl;
	std::cout << "100th index of ft::vector  = " << v[100] << std::endl;
	std::cout << "101th index of std::vector = " << sv[101] << std::endl;
	std::cout << "101th index of ft::vector  = " << v[101] << std::endl;
	std::cout << "102th index of std::vector = " << sv[102] << std::endl;
	std::cout << "102th index of ft::vector  = " << v[102] << std::endl;

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

void map_test()
{
	std::map<int, int>	sm;
	ft::map<int, int>	m;
	
	srand(time(0));

	for (int i = 0; i < 1000; ++i)
	{
		int nmb = rand() % 100000;

		sm[i] = nmb;
		m[i] = nmb;
	}
	for (int i = 0; i < 1000; ++i)
	{
		if (sm[i] != m[i])
			std::cout << "ERROR!" << std::endl;
	}

	int nmb = rand() % 100000;

	sm.insert(std::make_pair(1000, nmb));
	m.insert(ft::make_pair(1000, nmb));

	std::cout << "\n";

	std::cout << "Size of std::map = " << sm.size() << std::endl;
	std::cout << "Size of ft::map  = " << m.size() << std::endl;

	std::cout << "\n";

	int a = rand() % 1000;
	std::cout << a << " key's value on std::map = " << sm.at(a) << std::endl;
	std::cout << a << " key's value on ft::map  = " << m.at(a) << std::endl;

	std::cout << "Insert function on std::map = " << sm.insert(std::make_pair(a, 9999)).second << std::endl;
	std::cout << "Insert function on ft::map  = " << m.insert(ft::make_pair(a, 9999)).second << std::endl;

	std::cout << a << " key's value on std::map = " << sm.at(a) << std::endl;
	std::cout << a << " key's value on ft::map  = " << m.at(a) << std::endl;

	std::cout << "\n";

	std::map<int, int>::iterator sit;
	ft::map<int, int>::iterator it;

	sit = sm.find(50);
	it = m.find(50);

	std::cout << "Key of std::map::iterator = " << sit->first << std::endl;
	std::cout << "Key of ft::map::iterator  = " << it->first << std::endl;
	std::cout << "Value of std::map::iterator = " << sit->second << std::endl;
	std::cout << "Value of ft::map::iterator  = " << it->second << std::endl;

	std::cout << "-------------------------------------" << std::endl;

	sm[2000] = 9999;
	m[2000] = 9999;
	sm.erase(500);
	m.erase(500);

	std::cout << "Key of std::map::iterator = " << sit->first << std::endl;
	std::cout << "Key of ft::map::iterator  = " << it->first << std::endl;
	std::cout << "Value of std::map::iterator = " << sit->second << std::endl;
	std::cout << "Value of ft::map::iterator  = " << it->second << std::endl;

	std::cout << "\n";

	ft::map<int, int>	m2;

	m2[1] = 1;
	m2[2] = 2;
	m2[3] = 3;

	std::cout << "Address of 1 Key on ft::map2 = " << &m2[1] << std::endl;
	m.swap(m2);
	std::cout << "Address of 1 Key on ft::map  = " << &m[1] << std::endl;

	std::cout << "\n";

	ft::map<int, int>::iterator it2 = m.find(1);
	ft::map<int, int>::const_iterator it3 = m.find(2);

	if (it2 != it3)
		std::cout << "const_iterator and iterator is comparable" << std::endl;

	std::cout << "\n";

	sm.clear();
	m.clear();

	std::cout << "Is empty std::map = " << sm.empty() << std::endl;
	std::cout << "Is empty ft::map  = " << m.empty() << std::endl;
}

void stack_test()
{
	std::stack<int> ss;
	ft::stack<int> s;

	std::stack<int, std::vector<int> > ssv;
	ft::stack<int, std::vector<int> > sv;

	std::stack<int, std::list<int> > ssl;
	ft::stack<int, std::list<int> > sl;

	std::stack<int, std::deque<int> > ssd;
	ft::stack<int, std::deque<int> > sd;

	ss.push(1);
	s.push(1);
	ss.push(2);
	s.push(2);
	ss.push(3);
	s.push(3);
	std::cout << "Top of the std::stack = " << ss.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << s.top() << std::endl;
	ss.pop();
	s.pop();
	ss.push(4);
	s.push(4);
	std::cout << "Top of the std::stack = " << ss.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << s.top() << std::endl;
	std::cout << "Size of the std::stack = " << ss.size() << std::endl;
	std::cout << "Size of the ft::stack  = " << s.size() << std::endl;

	std::cout << "\n";

	ssv.push(1);
	sv.push(1);
	ssv.push(2);
	sv.push(2);
	ssv.push(3);
	sv.push(3);
	std::cout << "Top of the std::stack = " << ssv.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << sv.top() << std::endl;
	ssv.pop();
	sv.pop();
	ssv.push(4);
	sv.push(4);
	std::cout << "Top of the std::stack = " << ssv.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << sv.top() << std::endl;
	std::cout << "Size of the std::stack = " << ssv.size() << std::endl;
	std::cout << "Size of the ft::stack  = " << sv.size() << std::endl;

	std::cout << "\n";

	ssl.push(1);
	sl.push(1);
	ssl.push(2);
	sl.push(2);
	ssl.push(3);
	sl.push(3);
	std::cout << "Top of the std::stack = " << ssl.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << sl.top() << std::endl;
	ssl.pop();
	sl.pop();
	ssl.push(4);
	sl.push(4);
	std::cout << "Top of the std::stack = " << ssl.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << sl.top() << std::endl;
	std::cout << "Size of the std::stack = " << ssl.size() << std::endl;
	std::cout << "Size of the ft::stack  = " << sl.size() << std::endl;

	std::cout << "\n";

	ssd.push(1);
	sd.push(1);
	ssd.push(2);
	sd.push(2);
	ssd.push(3);
	sd.push(3);
	std::cout << "Top of the std::stack = " << ssd.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << sd.top() << std::endl;
	ssd.pop();
	sd.pop();
	ssd.push(4);
	sd.push(4);
	std::cout << "Top of the std::stack = " << ssd.top() << std::endl;
	std::cout << "Top of the ft::stack  = " << sd.top() << std::endl;
	std::cout << "Size of the std::stack = " << ssd.size() << std::endl;
	std::cout << "Size of the ft::stack  = " << sd.size() << std::endl;
}

int main(int argc, char **argv)
{
	defaultMain(argc, argv);
	//vector_test();
	//map_test();
	//stack_test();

	return (0);
}

