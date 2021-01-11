//
// Created by Fenix Lavon on 12/12/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_FT_HPP
#define FT_CONTAINERS_FT_HPP

#include <iostream>
#include <iterator>
#include <deque>

namespace ft {

	template<bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if <true, T> { typedef T type; };

	template<class Category,
			class T,
			class Distance = ptrdiff_t,
			class Pointer = T *,
			class Reference = T &>

	class iterator : public Category {
	public:
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template<class Iter>
	class reverse_iterator : public ft::iterator<
			typename Iter::iterator_category,
			typename Iter::value_type,
			typename Iter::difference_type,
			typename Iter::pointer,
			typename Iter::reference> {};
	
	template <class T, class Alloc = std::allocator<T> >
	class list;

	template <class T, class Container = ft::list<T> >
	class stack;

	template <class T, class Container = ft::list<T> >
	class queue;

	template <class T, class Alloc = std::allocator<T> >
	class vector;

	template <class T, class Alloc = std::allocator<T> >
	class map;
}

#endif
