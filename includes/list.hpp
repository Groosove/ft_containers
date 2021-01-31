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
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;
	typedef T 					value_type;
	typedef Alloc 				allocator_type;
	typedef value_type& 		reference;
	typedef const value_type	&const_reference;
	typedef value_type *		pointer;
	typedef size_t 				size_type;
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
		linkNode(prevNode, insertNode);
		linkNode(insertNode, nextNode);
	}

	inline void linkNode(_List *prevNode, _List *nextNode) {
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	};

	inline void changeSize(int value) {

		if (value == -1)
			--_size;
		else
			_size += static_cast<size_type>(value);
	}

	inline size_type countSize() {
		size_type size = 0;
		for (iterator it = begin(); it != end(); ++it)
			size += 1;
		return size;
	}

	inline static bool
		nonCompare(const value_type &first, const value_type& second) { return first < second; };
	inline static bool
		nonPredicate(const value_type &first, const value_type& second) { return first == second; };
	template < typename Compare > inline void
		listSort(_List * const curNode, Compare func) { recursiveSort(curNode, func); }

	_List *splitList(_List * const leftNode, _List * const rightNode) {
		if (leftNode->next == this->_end_node || leftNode->next->next == this->_end_node) {
			_List *tmp = rightNode->next;
			linkNode(rightNode, this->_end_node);
			return tmp;
		}
		return splitList(leftNode->next->next, rightNode->next);
	}

	template < typename Compare > _List *
		recursiveSort(_List * const currentNode, Compare func) {
		if (currentNode == this->_end_node || currentNode->next == this->_end_node)
			return currentNode;
		_List *secondNode = splitList(currentNode, currentNode);
		return mergeSort(recursiveSort(currentNode, func),
				   		recursiveSort(secondNode, func), func);
	}
	template < typename Compare > _List *
		mergeSort(_List * const firstList, _List * const secondList, Compare func) {
		if (firstList == this->_end_node) return secondList;
		if (secondList == this->_end_node) return firstList;
		if (!func(*secondList->content, *firstList->content)) {
			firstList->next = mergeSort(firstList->next, secondList, func);
			firstList->next->prev = firstList;
			linkNode(this->_end_node, firstList);
			return firstList;
		} else {
			secondList->next = mergeSort(firstList, secondList->next, func);
			secondList->next->prev = secondList;
			linkNode(this->_end_node, secondList);
			return secondList;
		}
	}

	void reverseList(_List *curNode) {
		_List *tmp = curNode->next;
		curNode->next = curNode->prev;
		curNode->prev = tmp;
		if (curNode == this->_end_node)
			return;
		reverseList(curNode->prev);
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

		bool operator==(const const_iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const const_iterator &it) const { return this->_it->content != it.getNode()->content; };
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
		const_iterator(const iterator &it) { *this = it; };
		~const_iterator() {};
		const_iterator& operator=(const const_iterator &it)  { this->_it = it._it; return *this; };
		const_iterator& operator=(const iterator &it)  { this->_it = it.getNode(); return *this; };
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

		bool operator==(const iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const iterator &it) const { return this->_it->content != it.getNode()->content; };
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
		reverse_iterator(const reverse_iterator &it) { *this = it; };
		reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it._it; return *this; };
		reverse_iterator & operator++() { this->_it = _it->prev; return *this; };
		reverse_iterator operator++(int) {
			reverse_iterator tmp(_it);
			this->_it = _it->prev;
			return tmp;
		};
		reverse_iterator & operator--() { this->_it = _it->next; return *this; };
		reverse_iterator operator--(int) {
			reverse_iterator tmp(_it);
			this->_it = _it->next;
			return tmp;
		};

		bool operator==(const reverse_iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const reverse_iterator &it) const { return this->_it->content != it._it->content; };

		bool operator==(const const_reverse_iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const const_reverse_iterator &it) const { return this->_it->content != it.getNode()->content; };
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
		const_reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it.getNode(); return *this; };
		const_reverse_iterator(const const_reverse_iterator &it) { *this = it; };
		const_reverse_iterator(const reverse_iterator &it) { *this = it; };
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

		bool operator==(const reverse_iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const reverse_iterator &it) const { return this->_it->content != it.getNode()->content; };
		reference operator*() const { return *(this->_it->content); }
		pointer operator->() const { return this->it->content; }

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
	template<class InputIterator> list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0)
		: _alloc(alloc), _size(0) {
		createList();
		for (; first != last; ++first)
			this->push_back(*first);
	};

	/* Assignation operator */
	list (const list<value_type>&x) : _alloc(x._alloc), _size(0) {
		createList();
		*this = x;
	};

	list &operator=(const list<value_type> &x) {
		if (!this->empty()) {
			clear();
		}
		for (const_iterator it = x.begin(); it != x.end(); it++)
			this->push_back(*it);
		return *this;
	};

	/* Destructor */
	~list() throw() {
		clear();
		_alloc.deallocate(_end_node->content, 1);
		_alloc_rebind.deallocate(_end_node, 1);
	};

	/* Iterators */
	iterator 		begin() { return iterator(this->_end_node->next); };
	const_iterator 	begin() const { return const_iterator(this->_end_node->next); };
	iterator 		end() { return iterator(this->_end_node); };
	const_iterator 	end() const { return const_iterator(this->_end_node); };

	/* Reverse Iterators */
	reverse_iterator 		rbegin() { return reverse_iterator(this->_end_node->prev); };
	const_reverse_iterator 	rbegin() const { return const_reverse_iterator(this->_end_node->prev); };
	reverse_iterator 		rend() { return reverse_iterator(this->_end_node); };
	const_reverse_iterator	rend() const { return const_reverse_iterator(this->_end_node); };

	/* Capacity */
	bool 		empty() const { return this->_size == 0; };
	size_type 	size() const { return this->_size; };
	size_type 	max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_List);};

	/* Element access */
	reference 		front() { return *this->_end_node->next->content; };
	const_reference front() const { return *this->_end_node->next->content; };
	reference 		back() { return *this->_end_node->prev->content; };
	const_reference back() const { return *this->_end_node->prev->content; };

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		clear();
		for (; first != last; ++first)
			push_back(*first);
	};
	void assign (size_type n, const value_type& val) {
		clear();
		for (u_long i = 0; i < n; ++i)
			push_back(val);
	};
	void push_front (const value_type& val) { insertNode(createNode(val), this->_end_node, this->_end_node->next); };
	void push_back (const value_type& val) { insertNode(createNode(val), this->_end_node->prev, this->_end_node); };
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
		return iterator(node);
	};
	void insert (iterator position, size_type n, const value_type& val) {
		while (n--) insert(position, val);
	};
	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		for (;first != last; ++first)
			insert(position, *first);
	};
	iterator erase (iterator position) {
		_List *node = position.getNode();
		_List *tmp = node->next;
		linkNode(node->prev, node->next);
		destroyNode(node);
		return iterator(tmp);
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
	};

	/* Operations */
	void splice (iterator position, list<value_type> &x) {
		splice(position, x, x.begin(), x.end());
	};
	void splice (iterator position, list<value_type> &x, iterator i) {
		(void) x;
		_List *toNode = i.getNode();
		_List *node = position.getNode();
		linkNode(toNode->prev, toNode->next);
		insertNode(toNode, node->prev, node);
		x.changeSize(-1);
		changeSize(+1);
	};
	void splice (iterator position, list<value_type> &x, iterator first, iterator last) {
		_List *node = position.getNode();
		_List *firstNode = first.getNode();
		_List *lastNode = last.getNode();
		_List *tmp2 = firstNode->prev;

		linkNode(node->prev, firstNode);
		linkNode(lastNode->prev, node);
		linkNode(tmp2, lastNode);
		changeSize(static_cast<int>(countSize() - _size));
		x.changeSize(static_cast<int>(x.countSize() - x.size()));
	}
	void remove (const value_type& val) {
		for (iterator it = begin(); it != end(); ++it)
			if (*it == val)
				erase(it);
	};
	template <class Predicate> void remove_if (Predicate pred) {
		for (iterator it = begin(); it != end(); ++it)
			if (pred(*it))
				erase(it);
	};
	void unique() { unique(nonPredicate); };
	template <class BinaryPredicate> void unique (BinaryPredicate binary_pred) {
		iterator it = begin();
		iterator nextIt = ++begin();
		iterator ite = end();
		while (nextIt != ite) {
			if (binary_pred(*it, *nextIt))
				nextIt = erase(nextIt);
			else {
				++it;
				++nextIt;
			}
		}
	};
	void merge (list<value_type>& x) { merge(x, nonCompare); };
	template <class Compare> void merge (list<value_type>& x, Compare comp) {
		iterator itX = x.begin();
		iterator iteX = x.end();
		iterator itThis = begin();
		iterator iteThis = end();

		while (itX != iteX) {
			while (itThis != iteThis && comp(*itX, *itThis) == 0)
				++itThis;
			splice(itThis, x, itX++);
		}
	};
	void sort() { sort(nonCompare); };
	template <class Compare> void sort (Compare comp) {
		listSort(_end_node->next, comp);
		_List *node = _end_node->next;
		while (node->next != _end_node) node = node->next;
		_end_node->prev = node;
	};
	void reverse() { reverseList(this->_end_node->next); };

};

template <class T, class Alloc> bool ft::operator==
		(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) {
	typename ft::list<T, Alloc>::const_iterator l_it = lhs.begin();
	typename ft::list<T, Alloc>::const_iterator l_ite = lhs.end();
	typename ft::list<T, Alloc>::const_iterator r_it = rhs.begin();

	if (lhs.size() != rhs.size()) return false;

	for (; l_it != l_ite; ++l_it, ++r_it) if (*l_it != *r_it) return false;

	return true;
};

template <class T, class Alloc> bool ft::operator!=
		(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return !(lhs == rhs); };

template <class T, class Alloc> bool ft::operator<
		(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) {
	typename ft::list<T, Alloc>::const_iterator l_it = lhs.begin();
	typename ft::list<T, Alloc>::const_iterator l_ite = lhs.end();
	typename ft::list<T, Alloc>::const_iterator r_it = rhs.begin();
	typename ft::list<T, Alloc>::const_iterator r_ite = rhs.end();

	for (; l_it != l_ite && r_it != r_ite; ++l_it, ++r_it)
		if (*l_it < *r_it) return true;

	if (l_it != l_ite) return false;

	return (r_it != r_ite);

};

template <class T, class Alloc> bool ft::operator<=
		(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return !(rhs < lhs); };

template <class T, class Alloc> bool ft::operator>
		(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return (rhs < lhs); };

template <class T, class Alloc> bool ft::operator>=
		(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) { return !(lhs < rhs); };

template <class T, class Alloc> void ft::swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y) { x.swap(y); };

#endif