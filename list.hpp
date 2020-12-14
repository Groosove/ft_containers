//
// Created by Fenix Lavon on 12/12/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "ft.hpp"

template <class T, class Alloc>
class ft::list {
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	// Constructor
	explicit list(const allocator_type &alloc = allocator_type());
	explicit list (size_type n, const value_type &val = value_type());
	template<class InputIterator> list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	list (const list<T>&x);
	list &operator=(const list<T> &x);
	~list() throw(); // Destructor

	class iterator: public std::iterator<T, std::bidirectional_iterator_tag> {};

	ft::list<T, allocator_type>::iterator begin();
	ft::list<T, allocator_type>::iterator end();
	ft::list<T, allocator_type>::iterator rend();
	ft::list<T, allocator_type>::iterator cbegin();
	ft::list<T, allocator_type>::iterator cend();
	ft::list<T, allocator_type>::iterator crbegin();
	ft::list<T, allocator_type>::iterator crend();
};

#endif
