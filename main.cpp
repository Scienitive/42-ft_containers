/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:04:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/11/27 21:02:36 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "vector.hpp"
#include <iostream>

int main()
{
	std::vector<int> a;

	ft::vector<int> b;

	a.push_back(10);
	a.push_back(20);
	b.push_back(10);
	b.push_back(20);

	std::cout << a.max_size() << std::endl;
	std::cout << b.max_size() << std::endl;
}