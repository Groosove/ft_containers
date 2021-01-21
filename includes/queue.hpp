//
// Created by Fenix Lavon on 12/14/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_QUEUE_HPP
#define FT_CONTAINERS_QUEUE_HPP

#include "ft.hpp"
#include <queue>
template <class T, class Container>
class ft::queue {
public:
	typedef Container				container_type;
	typedef T						value_type;
	typedef value_type &			reference;
	typedef const value_type &		const_reference;
	typedef size_t					size_type;

	/* Constructor */
	explicit queue (const container_type& container = container_type()) { this->_container = container; }

	/* Destructor */
	~queue() {};

	/* Member functions */
	bool empty() const	{ return this->_container.empty(); };
	size_type size() const { return this->_container.size(); };
	value_type& front() { return this->_container.front(); };
	const value_type& front() const	{ return this->_container.front(); };
	value_type& back() 	{ return this->_container.back(); };
	const value_type& back() const { return this->_container.back(); };
	void push (const value_type& val) { this->_container.push_back(val); };
	void pop() { this->_container.pop_front(); };
	container_type getContainer() const { return _container; }

private:
	container_type _container;
};

template <class T, class Container> bool ft::operator== (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) { return lhs.getContainer() == rhs.getContainer(); };
template <class T, class Container> bool ft::operator!= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) { return lhs.getContainer() != rhs.getContainer(); };
template <class T, class Container> bool ft::operator<  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) { return lhs.getContainer() < rhs.getContainer(); };
template <class T, class Container> bool ft::operator<= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) { return lhs.getContainer() <= rhs.getContainer(); };
template <class T, class Container> bool ft::operator>  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) { return lhs.getContainer() > rhs.getContainer(); };
template <class T, class Container> bool ft::operator>= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) { return  lhs.getContainer() >= rhs.getContainer(); };

#endif
