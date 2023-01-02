/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:10:03 by alyasar           #+#    #+#             */
/*   Updated: 2023/01/02 20:00:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef> // BUNU EN SON SİL
# include <iostream> // BUNU DA
# ifndef nullptr
#  define nullptr NULL
# endif

# include <memory>
# include <limits>
# include <stdexcept>
# include "vector_iterator.hpp"
# include "type_traits.hpp"
# include "utils.hpp"

namespace ft
{

template<typename T, typename Alloc = std::allocator<T> >
class vector
{
/* --------------- TYPEDEFS --------------- */
public:
	typedef T													value_type;
	typedef Alloc												allocator_type;
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;
	typedef typename allocator_type::size_type					size_type;
	typedef typename allocator_type::difference_type			difference_type;
	typedef ft::vector_iterator<value_type>						iterator;
	typedef ft::vector_iterator<const value_type>				const_iterator;
	typedef ft::reverse_iterator<iterator>						reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

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

	vector(const vector &other)
		:	m_Capacity(other.m_Capacity), m_Data(nullptr), m_Size(other.m_Size), m_Allocator(other.m_Allocator)
	{
		m_Data = m_Allocator.allocate(m_Capacity);
		for (size_type i = 0; i < m_Size; i++)
			m_Allocator.construct(m_Data + i, other.m_Data[i]);
	}

	explicit vector(const Alloc &alloc)
		:	m_Capacity(0), m_Data(nullptr), m_Size(0), m_Allocator(alloc)
	{
	}

	explicit vector(size_type count, const value_type &value = value_type(), const allocator_type &alloc = allocator_type())
		:	m_Capacity(0), m_Data(nullptr), m_Size(0), m_Allocator(alloc)
	{
		if (count == 0)
			return;
		sizeCheck(count);

		m_Data = m_Allocator.allocate(count);
		for (size_type i = 0; i < count; i++)
			push_back(value);
	}

	template<class InputIt>
	vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last, const Alloc &alloc = Alloc())
		:	m_Capacity(0), m_Data(nullptr), m_Size(0), m_Allocator(alloc)
	{
		m_Data = m_Allocator.allocate(m_Capacity);
		for (; first != last; first++)
			push_back(*first);
	}

	vector	&operator=(const vector &rhs)
	{
		if (this != &rhs)
			assign(rhs.begin(), rhs.end());

		return (*this);
	}

	~vector()
	{
		if (m_Data != nullptr)
			deAllocate();
	}

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */	
private:
	void	constructRange(pointer dest, pointer src, size_type size)
	{
		for (size_type i = 0; i < size; i++)
			m_Allocator.construct(&dest[i], src[i]);
	}

	template<typename It>
	void	constructRange(pointer dest, It start, It end, size_type &size)
	{
		for (; start != end; dest++, (void)start++)
		{
			m_Allocator.construct(dest, *start);
			size++;
		}
	}

	void	constructRange(pointer dest, pointer end, const_reference value, size_type &size)
	{
		for (; dest != end; dest++)
		{
			m_Allocator.construct(dest, value);
			size++;
		}
	}

	void	deAllocate()
	{
		for (size_type i = 0; i < m_Size; i++)
			m_Allocator.destroy(&m_Data[i]);
		m_Allocator.deallocate(m_Data, m_Capacity);
	}

	void	sizeCheck(size_type size) const
	{
		if (size > max_size())
			throw std::length_error("Exception: New capacity can't be higher than max_size.");
	}

	void	destroyFromEnd(pointer pos)
	{
		int	i = 0;

		for (; pos != m_Data + m_Size; pos++)
		{
			m_Allocator.destroy(pos);
			i++;
		}
		m_Size -= i;
	}

	size_type calculate_growth(size_type extra) const
	{
		const size_type max = max_size();
		const size_type cap = capacity();
		if (max - cap < extra)
			throw std::length_error("Exception.");

		// kapasite max / 2 den buyukse cap * 2 maxi gecicegi icin max i donduruyorum
		if (cap >= max / 2) {
			return max;
		}

		return std::max(size() + extra, cap * 2);
	}

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
	reference	at(size_type pos)
	{
		if (pos >= m_Size)
			throw std::out_of_range("Exception: Index is out of vectors range.");

		return ((*this)[pos]);
	}

	const_reference	at(size_type pos) const
	{
		if (pos >= m_Size)
			throw std::out_of_range("Exception: Index is out of vectors range.");

		return ((*this)[pos]);
	}

	reference	front()
	{
		return (*begin());
	}

	const_reference	front() const
	{
		return (*begin());
	}

	reference	back()
	{
		return (*(end() - 1));
	}

	const_reference	back() const
	{
		return (*(end() - 1));
	}

	pointer	data()
	{
		return (m_Data);
	}

	const_pointer	data() const
	{
		return (m_Data);
	}

	void	assign(size_type count, const value_type &value)
	{
		if (count > m_Capacity)
			reserve(count);
		if (count < m_Size)
			erase(begin() + count, end());

		m_Size = count;

		std::fill(begin(), end(), value);
	}

	// The reason why we use enable_if here is if we try to use the assign func above compiler can confuse it with the above one becuase InputIT is just a template and it can accept integral values
	template<typename InputIt>
	void	assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
	{
		size_type dist = static_cast<size_type>(std::distance(first, last));

		if (dist > m_Capacity)
			reserve(dist);

		std::copy(first, last, begin());

		erase(begin() + dist, end());

		m_Size = dist;
	}

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

	reverse_iterator	rbegin()
	{
		return (reverse_iterator(end()));
	}

	const_reverse_iterator	rbegin() const
	{
		return (const_reverse_iterator(end()));
	}

	iterator	end()
	{
		return (iterator(m_Data + m_Size));
	}

	const_iterator	end() const
	{
		return (const_iterator(m_Data + m_Size));
	}

	reverse_iterator	rend()
	{
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator	rend() const
	{
		return (const_reverse_iterator(begin()));
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
		sizeCheck(new_cap);

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
			m_Allocator.destroy(&m_Data[i]);
		m_Size = 0;
	}

	iterator	insert(iterator pos, const value_type &value)
	{
		size_type dist = pos - begin();

		insert(pos, 1, value);

		return (iterator(m_Data + dist));
	}

	void	insert(iterator pos, size_type count, const value_type &value)
	{
		/*if (count <= 0) {return;}

		size_type dist = pos - begin();
		size_type old_size = m_Size;

		resize(m_Size + count);
		std::copy_backward(m_Data + dist, m_Data + old_size, m_Data + old_size + count);
		std::fill(m_Data + dist, m_Data + dist + count, value);*/
		
		pointer _end = m_Data + m_Size;

		if (count != 0)
		{
			if (m_Capacity - m_Size >= count)
			{
				const size_type elems_after = end() - pos;
				pointer old_end = _end;

				if (elems_after > count)
				{
					constructRange(_end, _end - count, _end, m_Size);
					std::copy_backward(pos.base(), old_end - count, old_end);
					std::fill_n(pos, count, value);
				}
				else
				{
					constructRange(_end, _end + (count - elems_after), value, m_Size);
					constructRange(_end, pos.base(), old_end, m_Size);
					std::fill(pos.base(), old_end, value);
				}
			}
			else
			{
				const size_type new_cap = calculate_growth(count);
				pointer new_start = m_Allocator.allocate(new_cap);
				size_type new_size = 0;

				constructRange(new_start, m_Data, pos.base(), new_size);
				std::cout << new_size << std::endl;
				constructRange(new_start + new_size, new_start + new_size + count, value, new_size);
				constructRange(new_start + new_size, pos.base(), _end, new_size);

				deAllocate();
				m_Data = new_start;
				m_Size = new_size;
				m_Capacity = new_cap;
			}
		}
	}

	template<class InputIt>
	void	insert(iterator pos, InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
	{
		if (first == last)
			return;
		else if (static_cast<size_type>(std::distance(first, last)) <= 0)
			throw std::length_error("Exception: Range is not valid.");

		size_type dist = pos - begin();
		size_type range = static_cast<size_type>(std::distance(first, last));
		size_type old_size = m_Size;

		resize(m_Size + range);
		std::copy_backward(m_Data + dist, m_Data + old_size, m_Data + old_size + range);
		std::copy(first, last, m_Data + dist);
	}

	iterator	erase(iterator pos)
	{
		if (pos != end() - 1)
			std::copy(pos + 1, end(), pos);
		m_Size--;

		m_Allocator.destroy(end().base());

		return (pos);
	}

	iterator	erase(iterator first, iterator last)
	{
		if (last != end())
			std::copy(last, end(), first);
		m_Size -= last - first;

		for (difference_type i = 0; i < last - first; i++)
			m_Allocator.destroy(end().base() + i);

		return (first);
	}

	void	push_back(const value_type &value)
	{
		if (m_Size >= m_Capacity)
		{
			size_type new_cap = (m_Size > 0) ? (m_Size * 2) : 1;
			reserve(new_cap);
		}
		m_Allocator.construct(&m_Data[m_Size], value);
		m_Size++;
	}

	void	pop_back()
	{
		if (m_Size == 0)
			return;

		m_Allocator.destroy(&m_Data[m_Size]);
		m_Size--;
	}

	void	resize(size_type count, value_type value = value_type())
	{
		size_type len = size();
		if (count > len)
		{
			reserve(count);
			for (; len < count; len++)
				push_back(value);
		}
		else if (count < len)
			destroyFromEnd(m_Data + count);
	}

	void	swap(vector &other)
	{
		std::swap(m_Capacity, other.m_Capacity);
		std::swap(m_Data, other.m_Data);
		std::swap(m_Size, other.m_Size);
	}

/* --------------- OPERATION OVERLOADS --------------- */
public:
	reference	operator[](size_type pos)
	{
		return (*(m_Data + pos));
	}

	const_reference	operator[](size_type pos) const
	{
		return (*(m_Data + pos));
	}
};

template<typename T, typename Alloc>
bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
			return (false);
	}
	return (true);
}

template<typename T, typename Alloc>
bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (!(lhs == rhs));
}

template<typename T, typename Alloc>
bool	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (ft::lexicographcial_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<typename T, typename Alloc>
bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (rhs < lhs);
}

template<typename T, typename Alloc>
bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (!(rhs < lhs));
}

template<typename T, typename Alloc>
bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (!(lhs < rhs));
}

}

#endif