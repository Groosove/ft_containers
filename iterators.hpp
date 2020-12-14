//
// Created by Fenix Lavon on 12/15/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

#include "ft.hpp"

template <typename value_type>
class iterators:  public std::iterator<std::bidirectional_iterator_tag, value_type, size_t , value_type*, value_type&>  {
public:
	iterators();
	~iterators();
};

template <typename value_type>
class const_iterators:  public std::iterator<std::bidirectional_iterator_tag, value_type, size_t , value_type*, value_type&> {
public:
	const_iterators();
	~const_iterators();
};

#endif
