//
// Created by Fenix Lavon on 1/12/21.
// Copyright (c) 2021 All rights reserved.
//

#ifndef FT_CONTAINERS_ITERATORMAP_HPP
#define FT_CONTAINERS_ITERATORMAP_HPP

template <class T>
class iterator: public std::iterator<std::bidirectional_iterator_tag, T> {

};

template <class T>
class const_iterator: public std::iterator<std::bidirectional_iterator_tag, T> {

};
#endif //FT_CONTAINERS_ITERATORMAP_HPP
