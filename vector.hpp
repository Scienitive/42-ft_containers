/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:10:03 by alyasar           #+#    #+#             */
/*   Updated: 2022/11/28 21:28:35 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <stdexcept>
# include "vector_iterator.hpp"

namespace ft
{

template<typename T, typename Alloc = std::allocator<T> >
class vector
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T														value_type;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename allocator_type::size_type						size_type;
	typedef typename allocator_type::difference_type				difference_type;
	typedef ft::vector_iterator<value_type, difference_type>			iterator;
	typedef ft::vector_iterator<const value_type, difference_type>		const_iterator;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
	size_type		m_Capacity;		// Current capacity of the vector (allocated)
	pointer			m_Data;			// Pointer to the first index (start pointer)
	size_type		m_Size;			// Current constructed objects in the vector
	allocator_type	m_Allocator;	// The allocator object
	
/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
	vector()
		:	m_Capacity(0), m_Data(nullptr), m_Size(0), m_Allocator(allocator_type())
	{
	}

	vector(const vector &)
	{
	}

	vector	&operator=(const vector &)
	{
	}

	~vector()
	{
	}

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */	
private:
	void	constructRange(pointer dest, pointer src, size_type size)
	{
		for (size_type i = 0; i < size; i++)
			m_Allocator.construct(&dest[i], src[i]);
	}

	void	deAllocate()
	{
		for (size_type i = 0; i < m_Size; i++)
			m_Allocator.destroy(&m_Data[i]);
		m_Allocator.deallocate(m_Data, m_Capacity);
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	allocator_type	get_allocator() const
	{
		return (m_Allocator);
	}

	iterator	begin()
	{
		return (iterator(m_Data));
	}

	const_iterator	begin() const
	{
		return (const_iterator(m_Data));
	}

	iterator	end()
	{
		return (iterator(m_Data + m_Size));
	}

	const_iterator	end() const
	{
		return (const_iterator(m_Data + m_Size));
	}

	bool	empty() const
	{
		if (m_Size == 0)
			return (true);
		return (false);
	}

	size_type	size() const
	{
		return (m_Size);
	}

	size_type	max_size() const
	{
		return (m_Allocator.max_size());
	}

	void	reserve(size_type new_cap)
	{
		if (new_cap <= m_Capacity)
			return;
		else if (new_cap > this->max_size())
			throw std::length_error("Exception: New capacity can't be higher than max_size.");

		pointer newData = m_Allocator.allocate(new_cap);
		constructRange(newData, m_Data, m_Size);
		deAllocate();
		m_Data = newData;
		m_Capacity = new_cap;
	}

	size_type	capacity() const
	{
		return (m_Capacity);
	}

	void	clear()
	{
		for (size_type i = 0; i < m_Size; i++)
			m_Allocator.destroy(m_Data[i]);
		m_Size = 0;
	}

	/* INSERT FUNCTION */

	iterator	erase(iterator pos)
	{
		m_Allocator.destroy(&m_Data[begin() - pos]);

		if (pos != end() - 1)
		{
			for(iterator it = pos + 1; it != end(); it++)
				*(it - 1) = *it;
		}
		m_Size--;

		return (pos);
	}

	iterator	erase(iterator first, iterator last) // BITMEDI
	{
		for (iterator it = first; it != last; it++)
			m_Allocator.destroy(&m_Data[begin() - it]);

		if (last != end() - 1)
		{
			for(iterator it = last + 1; it != end(); it++)
				*(it - (last - first)) = *it;
		}
		m_Size -= last - first;

		return (pos);
	}

	void	push_back(const value_type &value)
	{
		if (m_Size >= m_Capacity)
		{
			size_type new_cap = (m_Size > 0) ? (m_Size + (m_Size / 2)) : 1;
			reserve(new_cap);
		}
		m_Allocator.construct(&m_Data[m_Size], value);
		m_Size++;
	}

	void	pop_back()
	{
		if (m_Size == 0)
			return;

		m_Allocator.destroy(m_Data[m_Size]);
		m_Size--;
	}

	void	resize(size_type count, const value_type &value)
	{
		
	}

	
};

}

#endif