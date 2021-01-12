//
// ft_containers
//
// Created by Артур Лутфуллин on 14.12.2020.
// Copyright (c) 2020 Артур Лутфуллин. All right reserved. 
//
#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include <stack>
#include "ft.hpp"
template <class T, class Container>
class ft::stack {
public:

	typedef Container	container_type;
	typedef T			value_type;
	typedef size_t		size_type;

	/* Constructor */
	explicit stack (const container_type& container = container_type()) { this->_container = container; }

	/* Destructor */

	~stack() { };

	/* Member functions */
	bool empty() const { return this->_container.empty(); };
	size_type size() const { return this->_container.size(); };
	value_type & top() { return this->_container.back(); };
	const value_type & top() const { return this->_container.back(); };
	void push(const value_type& val) { this->_container.push_back(val); };
	void pop() { this->_container.pop_back(); };
	container_type getContainer() const { return _container; }

private:
	container_type _container;
};

template <class T, class Container> bool ft::operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.getContainer() == rhs.getContainer(); };
template <class T, class Container> bool ft::operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.getContainer() != rhs.getContainer(); };
template <class T, class Container> bool ft::operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.getContainer() < rhs.getContainer(); };
template <class T, class Container> bool ft::operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.getContainer() <= rhs.getContainer(); };
template <class T, class Container> bool ft::operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.getContainer() > rhs.getContainer(); };
template <class T, class Container> bool ft::operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs.getContainer() >= rhs.getContainer(); };

#endif
