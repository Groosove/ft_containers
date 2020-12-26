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

	typedef T 					value_type;
	typedef Alloc 				allocator_type;
	typedef value_type& 		reference;
	typedef const value_type	&const_reference;
	typedef value_type			*pointer;
	typedef const value_type	*const_pointer;
	typedef size_t 				size_type;
	typedef ptrdiff_t 			difference_type;

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
	_List *_end_node;

	void createList() {
		this->_end_node = this->_alloc_rebind.allocate(1);
		this->_end_node->content = this->_alloc.allocate(1);
		this->_end_node->next = this->_end_node;
		this->_end_node->prev = this->_end_node;
		this->_size = 0;
	}

	void destroyNode(_List *node) {
		this->_alloc.destroy(node->content);
		this->_alloc.deallocate(node->content, 1);
		this->_alloc_rebind.deallocate(node, 1);
		changeSize(-1);
	}

	_List* createNode(const value_type &val) {
		_List *node = this->_alloc_rebind.allocate(1);
		node->content = this->_alloc.allocate(1);
		_alloc.construct(node->content, val);
		changeSize(+1);
		return node;
	}

	inline void insertNode(_List *insertNode, _List *prevNode, _List *nextNode) {
		insertNode->prev = prevNode;
		insertNode->next = nextNode;
		prevNode->next = insertNode;
		nextNode->prev = insertNode;
	}

	inline void linkNode(_List *prevNode, _List *nextNode) {
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	};

	inline void changeSize(int value) {
		this->_size += value;
		*this->_end_node->content = static_cast<value_type>(this->_size);
	}

	inline size_type countSize() {
		size_type size = 0;
		for (iterator it = begin(); it != end(); ++it)
			size += 1;
		return size;
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
		T & operator*() const { return *(this->_it->content); }
		T * operator->() const { return this->it->content; }

		_List *getNode() const { return _it; }
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

		_List *getNode() const { return _it; }
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

		_List *getNode() const { return _it; }
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
		T & operator*() const { return *(this->_it->content); }
		T * operator->() const { return this->it->content; }

		_List *getNode() const { return _it; }
	};

	/* Constructor */
	explicit list(const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _size(0) { createList(); };
	explicit list (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _size(0) {
		createList();
		if (val != value_type())
			while(n--)
				this->push_back(val);
	};
	template<class InputIterator> list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(0) {
		createList();
		while (first != last) {
			this->push_back(*first);
			first++;
		}
	};

	/* Assignation operator */
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
	iterator 		begin() { return iterator(this->_end_node->next); };
	iterator 		end() { return iterator(this->_end_node); };
	const_iterator 	begin() const { return const_iterator(this->_end_node->next); };
	const_iterator 	end() const { return const_iterator(this->_end_node); };

	/* Reverse Iterators */
	reverse_iterator 		rbegin() { return reverse_iterator(this->_end_node); };
	reverse_iterator 		rend() { return reverse_iterator(this->_end_node->next); };
	const_reverse_iterator 	rbegin() const { return const_reverse_iterator(this->_end_node); };
	const_reverse_iterator	rend() const { return const_reverse_iterator(this->_end_node->next); };

	/* Capacity */
	bool 		empty() const { return !this->_size; };
	size_type 	size() const { return this->_size; };
	size_type 	max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_List);};

	/* Element access */
	reference 		front() { return *this->_end_node->next->content; };
	const_reference front() const { return *this->_end_node->next->content; };
	reference 		back() { return *this->_end_node->prev->content; };
	const_reference back() const { return *this->_end_node->prev->content; };

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last) {
		if (!this->_size)
			this->clear();
		createList();
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
		insertNode(node, this->_end_node, this->_end_node->next);
	};
	void push_back (const value_type& val) {
		_List *node = createNode(val);
		insertNode(node, this->_end_node->prev, this->_end_node);
	};
	void pop_front() {
		_List *node = this->_end_node->next;
		linkNode(node->prev, node->next);
		destroyNode(node);
	};
	void pop_back() {
		_List *node = this->_end_node->prev;
		linkNode(node->prev, node->next);
		destroyNode(node);
	};
	iterator insert (iterator position, const value_type& val) {
		_List *node = createNode(val);
		_List *list = position.getNode();
		insertNode(node, list->prev, list);
		return position;
	};
	void insert (iterator position, size_type n, const value_type& val) {
		while (n--)
			insert(position, val);
	};
	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last) {
		while (first != last)
			insert(position, *first++);
	};
	iterator erase (iterator position) {
		_List *node = position.getNode();
		linkNode(node->prev, node->next);
		destroyNode(node);
		return position;
	};
	iterator erase (iterator first, iterator last) {
		while (first != last)
			erase(first++);
		return last;
	};
	void swap (list<value_type>& x) {
		_List *end_node = this->_end_node;
		this->_end_node = x._end_node;
		x._end_node = end_node;

		size_type size = this->_size;
		this->_size = x.size();
		x._size = size;
	};
	void resize (size_type n, value_type val = value_type()) {
		for (; this->_size > n; )
			erase(iterator(this->_end_node->prev));
		for (; this->_size < n ; )
			push_back(val);
	};
	void clear() {
		while (_size != 0)
			pop_back();
		pop_back();
	};

	/* Operations */
	void splice (iterator position, list& x) {
		_List *node = position.getNode();
		_List *beginNode = x._end_node->next;
		_List *endNode = x._end_node;

		linkNode(node->prev, beginNode);
		linkNode(endNode->prev, node);
		linkNode(x._end_node, x._end_node);
		changeSize(countSize());
	};
	void splice (iterator position, list& x, iterator i);
//		_List *node = position.getNode();
//		insertNode(i.getNode(), node->prev, node->next);
	void splice (iterator position, list& x, iterator first, iterator last);
	void remove (const value_type& val);
	template <class Predicate> void remove_if (Predicate pred);
	void unique();
	template <class BinaryPredicate> void unique (BinaryPredicate binary_pred);
	void merge (list<value_type>& x);
	template <class Compare> void merge (list<value_type>& x, Compare comp);
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
