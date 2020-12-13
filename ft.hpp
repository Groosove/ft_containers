//
// Created by Fenix Lavon on 12/12/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_FT_HPP
#define FT_CONTAINERS_FT_HPP

#include <iostream>
namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class list;

	template <class T, class Alloc = std::allocator<T> >
	class stack;

	template <class T, class Alloc = std::allocator<T> >
	class queue;

	template <class T, class Alloc = std::allocator<T> >
	class vector;

	template <class T, class Alloc = std::allocator<T> >
	class map;
}

#endif
