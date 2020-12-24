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

private:

	typedef struct Node {
		value_type *content;
		Node* next;
		Node* prev;
	}				_List;
	typedef typename allocator_type::template rebind<_List>::other allocator_rebind_type;

	allocator_type _alloc;
	allocator_rebind_type _alloc_rebind;
	size_type _size;
	_List *_begin_node;
	_List *_end_node;

	void createList() {
		this->_end_node = this->_alloc_rebind.allocate(1);
		this->_end_node->content = this->_alloc.allocate(1);
		this->_end_node->next = this->_end_node;
		this->_end_node->prev = this->_end_node;
		this->_begin_node = this->_end_node;
		this->_size = 0;
	}

	void destroyNode(_List *node) {
		this->_alloc.destroy(node->content);
		this->_alloc.deallocate(node->content, 1);
		this->_alloc_rebind.deallocate(node, 1);
		this->_size -= 1;
		*this->_end_node->content = static_cast<value_type>(this->_size);
	}

	_List* createNode(const value_type &val) {
		_List *node = this->_alloc_rebind.allocate(1);
		node->content = this->_alloc.allocate(1);
		_alloc.construct(node->content, val);
		return node;
	}

public:
	/* iterator */
	class iterator: public ft::iterator<std::bidirectional_iterator_tag, value_type> {
	private:
		_List* _it;
	public:
		explicit iterator(_List* it = nullptr): _it(it) {};
		~iterator() {};
		iterator & operator=(const iterator &it) { this->_it = it._it; return *this; };
		iterator(const iterator &it) { *this = it; };
		iterator & operator++() { this->_it = _it->next; return *this; };
		iterator operator++(int) {
			iterator tmp(_it);
			this->_it = _it->next;
			return tmp;
		};
		iterator & operator--() { this->_it = _it->prev; return *this; };
		iterator operator--(int) {
			iterator tmp(_it);
			this->_it = _it->prev;
			return tmp;
		};
		bool operator==(const iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const iterator &it) const { return this->_it->content != it._it->content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }
	};

	/* const_iterator */
	class const_iterator: public ft::iterator<std::bidirectional_iterator_tag, value_type const > {
	private:
		_List* _it;
	public:
		explicit const_iterator(_List* it = nullptr) : _it(it) {};
		const_iterator(const const_iterator &it) { *this = it; };
		~const_iterator() {};
		const_iterator& operator=(const const_iterator &it)  { this->_it = it._it; return *this; };
		const_iterator & operator++() { this->_it = _it->next; return *this; };
		const_iterator operator++(int) {
			const_iterator tmp(_it);
			this->_it = _it->next;
			return tmp;
		};
		const_iterator & operator--() { this->_it = _it->prev; return *this; };
		const_iterator operator--(int) {
			const_iterator tmp(_it);
			this->_it = _it->prev;
			return tmp;
		};
		bool operator==(const const_iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const const_iterator &it) const { return this->_it->content != it._it->content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }
	};

	/* reverse_iterator */
	class reverse_iterator: public ft::reverse_iterator<list::iterator>{
	private:
		_List* _it;
	public:
		explicit reverse_iterator(_List* it = nullptr): _it(it) {};
		~reverse_iterator() {};
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
	class const_reverse_iterator: public ft::reverse_iterator<list::iterator> {
	private:
		_List* _it;
	public:
		explicit const_reverse_iterator(_List* it = nullptr): _it(it) {};
		~const_reverse_iterator() {};
		const_reverse_iterator & operator=(const const_reverse_iterator &it) { this->_it = it._it; return *this; };
		const_reverse_iterator(const const_reverse_iterator &it) { *this = it; };
		const_reverse_iterator & operator++() { this->_it = _it->prev; return *this; };
		const_reverse_iterator operator++(int) {
			const_reverse_iterator tmp(_it);
			this->_it = _it->prev;
			return tmp;
		};
		const_reverse_iterator & operator--() { this->_it = _it->next; return *this; };
		const_reverse_iterator operator--(int) {
			const_reverse_iterator tmp(_it);
			this->_it = _it->next;
			return tmp;
		};

		bool operator==(const const_reverse_iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const const_reverse_iterator &it) const { return this->_it->content != it._it->content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }
	};

	/* Constructor */
	explicit list(const allocator_type &alloc = allocator_type()): _alloc(alloc), _size(0) {
		createList();
	};

	explicit list (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()): _alloc(alloc) {
		createList();
		if (val != value_type())
			while(n--)
				this->push_back(val);
	};

	template<class InputIterator> list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _alloc(alloc) {
		createList();
		while (first != last) {
			this->push_back(*first);
			first++;
		}
	};

	list (const list<value_type>&x) { *this = x; };
	list &operator=(const list<value_type> &x) {
		if (this->empty())
			this->clear();
		createList();
		for (const_iterator it = x.begin(); it != x.end(); it++)
			this->push_back(*it);
		return *this;
	};

	/* Destructor */
	~list() throw() {};

	/* Iterators */
	iterator begin() { return iterator(this->_begin_node); };
	iterator end() { return iterator(this->_end_node); };

	const_iterator begin() const { return const_iterator(this->_begin_node); };
	const_iterator end() const { return const_iterator(this->_end_node); };

	reverse_iterator rbegin() { return reverse_iterator(this->_end_node); };
	reverse_iterator rend() { return reverse_iterator(this->_begin_node); };

	const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_end_node); };
	const_reverse_iterator rend() const { return const_reverse_iterator(this->_begin_node); };

	/* Capacity */
	bool empty() const { return !this->_size; };
	size_type size() const { return this->_size; };
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_List);};

	/* Element access */
	reference front() { return *this->_begin_node->content; };
	const_reference front() const { return *this->_begin_node->content; };
	reference back() { return *this->_end_node->prev->content; };
	const_reference back() const { return *this->_end_node->prev->content; };

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last) {
		while (first != last)
			push_back(*first++);
	};

	void assign (size_type n, const value_type& val) {
		if (!this->_size)
			this->clear();
		createList();
		for (u_long i = 0; i < n; ++i)
			push_back(val);
	};

	void push_front (const value_type& val) {
		_List *node = createNode(val);
		node->next = this->_begin_node;
		node->prev = this->_end_node;
		this->_begin_node->prev = node;
		this->_begin_node = node;
		this->_end_node->next = this->_begin_node;
		this->_size += 1;
		*this->_end_node->content = static_cast<value_type>(this->_size);
	};

	void push_back (const value_type& val) {
		_List *node = createNode(val);
		node->next = this->_end_node;
		node->prev = this->_end_node->prev;
		this->_end_node->prev->next = node;
		this->_end_node->prev = node;
		if (this->_size == 0) {
			this->_begin_node = node;
			this->_end_node->next = node;
			this->_end_node->prev = node;
		}
		this->_size += 1;
		*this->_end_node->content = static_cast<value_type>(this->_size);
	};

	void pop_front() {
		_List *node = this->_begin_node->next;
		destroyNode(this->_begin_node);
		this->_begin_node = node;
		this->_begin_node->prev = this->_end_node;
	};

	void pop_back() {
		_List *node = this->_end_node->prev;
		this->_end_node->prev->prev->next = this->_end_node;
		this->_end_node->prev = this->_end_node->prev->prev;
		destroyNode(this->_end_node->prev);
		this->_end_node->prev = node;
	};

	iterator insert (iterator position, const value_type& val) {
		_List *node = createNode(val);
		return position;
	};
	void insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last);
	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);
	void swap (list& x);
	void resize (size_type n, value_type val = value_type());
	void clear() {
		for (u_long i = 0; i < size(); ++i) {
			_List *node = _begin_node->next;
			destroyNode(this->_begin_node);
			_begin_node = node;
		}
	};

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
bool operator< (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container < rhs._container; };

template <class T, class Alloc>
bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container <= rhs._container; };

template <class T, class Alloc>
bool operator> (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container > rhs._container; };

template <class T, class Alloc>
bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{ return lhs._container >= rhs._container; };

#endif
