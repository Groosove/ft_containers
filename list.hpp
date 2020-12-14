//
// Created by Fenix Lavon on 12/12/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "ft.hpp"
#include <list>
#include "iterators.hpp"
template <class T, class Alloc>
class ft::list {
public:
	typedef T 			value_type;
	typedef Alloc 		allocator_type;
	typedef T& 			reference;
	typedef const T& 	const_reference;
	typedef T* 			pointer;
	typedef const T* 	const_pointer;
	typedef size_t 		size_type;
	typedef ptrdiff_t 	difference_type;

	/* Constructor */
	explicit list(const allocator_type &alloc = allocator_type());
	explicit list (size_type n, const value_type &val = value_type());
	template<class InputIterator> list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	list (const list<value_type>&x);
	list &operator=(const list<value_type> &x);

	/* Destructor */
	~list() throw();

	/* iterator */
//	class iterator: public std::iterator<T, std::bidirectional_iterator_tag> {};

	typedef iterators<value_type , Alloc, size_t, value_type*, value_type& > iterator;

	/* Iterators */
	ft::list<T, allocator_type>::iterator begin();
	ft::list<T, allocator_type>::iterator end();
	ft::list<T, allocator_type>::iterator rend();
	ft::list<T, allocator_type>::iterator cbegin();
	ft::list<T, allocator_type>::iterator cend();
	ft::list<T, allocator_type>::iterator crbegin();
	ft::list<T, allocator_type>::iterator crend();

	/* Capacity */
	bool empty() const;
	size_type size() const;
	size_type max_size() const;

	/* Element access */
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last);
	void assign (size_type n, const value_type& val);
	void push_front (const value_type& val);
	void pop_front();
	void push_back (const value_type& val);
	void pop_back();
	iterator insert (iterator position, const value_type& val);
	void insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last);
	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);
	void swap (list& x);
	void resize (size_type n, value_type val = value_type());
	void clear();

	/* Operations */
	void splice (iterator position, list& x);
	void splice (iterator position, list& x, iterator i);
	void splice (iterator position, list& x, iterator first, iterator last);
	void remove (const value_type& val);
	template <class Predicate> void remove_if (Predicate pred);
	void unique();
	template <class BinaryPredicate> void unique (BinaryPredicate binary_pred);
	void merge (list& x);
	template <class Compare> void merge (list& x, Compare comp);
	void sort();
	template <class Compare> void sort (Compare comp);
	void reverse();

private:
	typedef struct Node {

	}				_list;
};

template <class T, class Alloc>
bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{return lhs._container == rhs._container; };

template <class T, class Alloc>
bool operator!= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container != rhs._container; };

template <class T, class Alloc>
bool operator<  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container < rhs._container; };

template <class T, class Alloc>
bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container <= rhs._container; };

template <class T, class Alloc>
bool operator>  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container > rhs._container; };

template <class T, class Alloc>
bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container >= rhs._container; };

#endif
