//
// ft_containers
//
// Created by Артур Лутфуллин on 31.12.2020.
// Copyright (c) 2020 Артур Лутфуллин. All right reserved. 
//

#ifndef FT_CONTAINERS_VECTOR_HPP
# define FT_CONTAINERS_VECTOR_HPP

#include <vector>
#include "ft.hpp"
template <class T, class Alloc>
class ft::vector {
public:
	typedef T 					value_type;
	typedef Alloc 				allocator_type;
	typedef value_type& 		reference;
	typedef const value_type	&const_reference;
	typedef size_t 				size_type;

private:
	value_type *_arr;
	allocator_type _alloc;
	size_type _size;

public:
	/* Constructor */
	explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	vector (const vector& x);

	/* Destructor */
	~vector();

	/* Assignation operator */
	vector& operator= (const vector& x);

	/* iterator */
	class iterator: public ft::iterator<std::random_access_iterator_tag, value_type> {};

	/* const iterator */
	class const_iterator: public ft::iterator<std::random_access_iterator_tag, value_type> {};

	/* reverse iterator */
	class reverse_iterator: public ft::reverse_iterator<iterator> {};

	/* const reverse iterator */
	class const_reverse_iterator: public ft::reverse_iterator<const_iterator> {};

	/* iterators */
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	/* Capacity */
	size_type size() const;
	size_type max_size() const;
	void resize (size_type n, value_type val = value_type());
	size_type capacity() const;
	bool empty() const;
	void reserve (size_type n);

	/* Element access */
	reference operator[] (size_type n);
	const_reference operator[] (size_type n) const;
	reference at (size_type n);
	const_reference at (size_type n) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last);
	void assign (size_type n, const value_type& val);
	void push_back (const value_type& val);
	void pop_back();
	iterator insert (iterator position, const value_type& val);
	void insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last);
	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);
	void swap (vector& x);
	void clear();

};

template <class T, class Alloc> bool operator==
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator!=
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator<
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator<=
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator>
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator>=
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> void
	swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y);
#endif
