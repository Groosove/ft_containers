//
// Created by Fenix Lavon on 12/12/20.
// Copyright (c) 2020 All rights reserved.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "ft.hpp"
#include <list>

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

private:
	typedef struct Node {
		T *content;
		Node* next;
		Node* prev;
	}				_List;

	_List* _list;
	allocator_type _alloc;
	size_type _size;
	value_type _type;

	/* iterator */
	class iterator: public std::iterator<T, std::bidirectional_iterator_tag> {
	private:
		_List* _it;
	public:
		explicit iterator(_List* it = nullptr): _it(it) {};
		~iterator() { delete _it; };
		iterator & operator=(const iterator &it) { this->_it = it; return *this; };
		iterator(const iterator &it) { this = it; };
		iterator & operator++() { this->_it = _it->next; return *this; };
		iterator operator++(int) {
			iterator tmp(_it);
			this->_it += _it->next;
			return tmp;
		};
		iterator & operator--() { this->_it = _it->prev; return *this; };
		iterator operator--(int) {
			iterator tmp(_it);
			this->_it = _it->prev;
			return tmp;
		};
		bool operator==(const iterator &it) const { return this->_it.content == it._it.content; };
		bool operator!=(const iterator &it) const { return this->_it.content != it._it.content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }
	};

	/* const_iterator */
	class const_iterator: public std::iterator<T, std::bidirectional_iterator_tag> {
	private:
		_List* _it;
	public:
		explicit const_iterator(_List* it = nullptr) : _it(it) {};
		explicit const_iterator(const const_iterator &it) { *this = it; };
		~const_iterator() {};
		const_iterator & operator=(const_iterator &it)  { this->_it = it; return *this; };
		const_iterator & operator++() { this->_it = _it->next; return *this; };
		const_iterator operator++(int) {
			const_iterator tmp(_it);
			this->_it += _it->next;
			return tmp;
		};
		const_iterator & operator--() { this->_it = _it->prev; return *this; };
		const_iterator operator--(int) {
			const_iterator tmp(_it);
			this->_it = _it->prev;
			return tmp;
		};
		bool operator==(const const_iterator &it) const { return this->_it.content == it._it.content; };
		bool operator!=(const const_iterator &it) const { return this->_it.content != it._it.content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }
	};

	/* reverse_iterator */
	class reverse_iterator: public std::iterator<T, std::bidirectional_iterator_tag> {
	private:
		_List* _it;
	public:
		explicit reverse_iterator(_List* it = nullptr): _it(it) {};
		~reverse_iterator() { delete _it; };
		reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it; return *this; };
		reverse_iterator(const reverse_iterator &it) { this = it; };
		reverse_iterator & operator++() { this->_it = _it->prev; return *this; };
		reverse_iterator operator++(int) {
			reverse_iterator tmp(_it);
			this->_it += _it->prev;
			return tmp;
		};
		reverse_iterator & operator--() { this->_it = _it->next; return *this; };
		reverse_iterator operator--(int) {
			reverse_iterator tmp(_it);
			this->_it = _it->next;
			return tmp;
		};

		bool operator==(const reverse_iterator &it) const { return this->_it.content == it._it.content; };
		bool operator!=(const reverse_iterator &it) const { return this->_it.content != it._it.content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }
	};

	/* const_reverse_iterator */
	class const_reverse_iterator: public std::iterator<T, std::bidirectional_iterator_tag> {
	private:
		_List* _it;
	public:
		explicit const_reverse_iterator(_List* it = nullptr): _it(it) {};
		~const_reverse_iterator() { delete _it; };
		const_reverse_iterator & operator=(const const_reverse_iterator &it) { this->_it = it; return *this; };
		const_reverse_iterator(const const_reverse_iterator &it) { this = it; };
		const_reverse_iterator & operator++() { this->_it = _it->prev; return *this; };
		const_reverse_iterator operator++(int) {
			const_reverse_iterator tmp(_it);
			this->_it += _it->prev;
			return tmp;
		};
		const_reverse_iterator & operator--() { this->_it = _it->next; return *this; };
		const_reverse_iterator operator--(int) {
			const_reverse_iterator tmp(_it);
			this->_it = _it->next;
			return tmp;
		};

		bool operator==(const const_reverse_iterator &it) const { return this->_it.content == it._it.content; };
		bool operator!=(const const_reverse_iterator &it) const { return this->_it.content != it._it.content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }
	};
public:

	/* Constructor */
	explicit list(const allocator_type &alloc = allocator_type()): _list(nullptr), _alloc(alloc), _type(0), _size(0) {};
	explicit list (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()): _size(n), _alloc(alloc), _type(val) {};
	template<class InputIterator> list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	list (const list<value_type>&x);
	list &operator=(const list<value_type> &x);

	/* Destructor */
	~list() throw();

	/* Iterators */
	iterator begin() { return iterator(_list->next->content); };
	iterator end() { return iterator(_list->prev->content); };

	const_iterator cbegin() const { return const_iterator(_list->next->content); };
	const_iterator cend() const { return const_iterator(_list->prev->content); };

	reverse_iterator rbegin() { return reverse_iterator(_list->prev->content); };
	reverse_iterator rend() { return reverse_iterator(_list->next->content); };

	const_reverse_iterator crbegin() const { return const_reverse_iterator(_list->prev->content); };
	const_reverse_iterator crend() const { return const_reverse_iterator(_list->next->content); };

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
