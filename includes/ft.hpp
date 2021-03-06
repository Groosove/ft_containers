//
// Created by Fenix Lavon on 12/12/20.
// Copyright (c) 2020 All rights reserved.
//

#pragma once

#include <iostream>
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
	template <class T, class Alloc> bool operator==(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator!=(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator< (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator<=(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator> (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator>=(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
	template <class T, class Alloc> void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y);

	template <class T, class Container = ft::list<T> >
	class queue;
	template <class T, class Container> bool operator== (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs);
	template <class T, class Container> bool operator!= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs);
	template <class T, class Container> bool operator<  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs);
	template <class T, class Container> bool operator<= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs);
	template <class T, class Container> bool operator>  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs);
	template <class T, class Container> bool operator>= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs);

	template <class T, class Alloc = std::allocator<T> >
	class vector;
	template <class T, class Alloc> bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);
	template <class T, class Alloc> void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y);

	template <class T, class Container = ft::vector<T> >
	class stack;
	template <class T, class Container> bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs);
	template <class T, class Container> bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs);
	template <class T, class Container> bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs);
	template <class T, class Container> bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs);
	template <class T, class Container> bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs);
	template <class T, class Container> bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs);

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map;

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T > >
	class set;

	template <class T, class Alloc = std::allocator<T> >
	class deque;
	template <class T, class Alloc> bool operator==(const ft::deque<T,Alloc>& lhs, const ft::deque<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator!=(const ft::deque<T,Alloc>& lhs, const ft::deque<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator< (const ft::deque<T,Alloc>& lhs, const ft::deque<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator<=(const ft::deque<T,Alloc>& lhs, const ft::deque<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator> (const ft::deque<T,Alloc>& lhs, const ft::deque<T,Alloc>& rhs);
	template <class T, class Alloc> bool operator>=(const ft::deque<T,Alloc>& lhs, const ft::deque<T,Alloc>& rhs);
	template <class T, class Alloc> void swap (ft::deque<T,Alloc>& x, ft::deque<T,Alloc>& y);
}
