//
// Created by Fenix Lavon on 1/12/21.
// Copyright (c) 2021 All rights reserved.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "ft.hpp"
#include <map>

template <class Key, class T, class Compare, class Alloc>
class ft::map {
public:
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef std::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	class value_compare : public std::binary_function<value_type, value_type, bool> {
	protected:
		key_compare comp;

		explicit value_compare(key_compare &c) : comp(c) {};
	public:
		bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); };
	};

private:
	typedef struct Node {
		Node * left;
		Node * right;
		Node *parent;
		int color;
		pointer content;
	}	_MapNode;

	typedef typename allocator_type::template rebind<_MapNode>::other allocator_rebind_type;
	_MapNode *_node;
	size_type _size;

	allocator_rebind_type allocator_rebind;
	allocator_type alloc;

public:

	/* iterator */
	class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
	private:
		_MapNode* _it;
	public:
		explicit iterator(_MapNode* it = nullptr): _it(it) {};
		~iterator() {};
		iterator & operator=(const iterator &it) { this->_it = it._it; return *this; };
		iterator(const iterator &it) { *this = it; };
		iterator & operator++() {
			if (_it->right) { _it = _it->right; return *this; }

		};
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

		_MapNode *getNode() const { return _it; }
	};

	/* const_iterator */
	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type const> {

	};

	/* reverse_iterator */
	class reverse_iterator : public std::reverse_iterator<iterator> {

	};

	/* const_reverse_iterator */
	class const_reverse_iterator : public std::reverse_iterator<iterator> {

	};

	/* Constructor */
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	template <class InputIterator> map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {

	};

	/* Copy constructor */
	map (const map& x) { *this = x; };

	/* Assignation operator */
	map& operator= (const map& x) {

	};

	/* Destructor */
	~map() {};

	/* Iterators */
	iterator		begin() { return iterator(); };
	const_iterator 	begin() const;
	iterator		end();
	const_iterator	end() const;
	const_iterator 	cbegin() const;
	const_iterator 	cend() const;
	reverse_iterator rbegin();

	/* Reverse Iterators */
	const_reverse_iterator	rbegin() const;
	reverse_iterator 		rend();
	const_reverse_iterator	rend() const;
	const_reverse_iterator	crbegin() const;
	const_reverse_iterator	crend() const;

	/* Capacity */

	bool empty() const;
	size_type size() const;
	size_type max_size() const;

	/* Element access */

	mapped_type& operator[] (const key_type& k);
	mapped_type& at (const key_type& k);
	const mapped_type& at (const key_type& k) const;

	/* Modifiers */

	std::pair<iterator, bool> insert (const value_type& val);
	iterator insert (iterator position, const value_type& val);
	template <class InputIterator> void insert (InputIterator first, InputIterator last);
	void erase (iterator position);
	size_type erase (const key_type& k);
	void erase (iterator first, iterator last);
	void swap (map& x);
	void clear();

	/* Observers */

	key_compare key_comp() const;
	value_compare value_comp() const;


	/* Operations */
	iterator find (const key_type& k);
	const_iterator find (const key_type& k) const;
	size_type count (const key_type& k) const;
	iterator lower_bound (const key_type& k);
	const_iterator lower_bound (const key_type& k) const;
	iterator upper_bound (const key_type& k);
	const_iterator upper_bound (const key_type& k) const;
	std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
	std::pair<iterator,iterator>             equal_range (const key_type& k);
};
#endif //FT_CONTAINERS_MAP_HPP
