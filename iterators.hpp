//
// Created by Fenix Lavon on 12/16/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include "iostream"

namespace ft {
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
}

#endif //FT_CONTAINERS_ITERATORS_HPP
