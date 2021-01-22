//
// Created by Fenix Lavon on 1/12/21.
// Copyright (c) 2021 All rights reserved.
//

#pragma once

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
	typedef value_type &								reference;
	typedef const value_type &							const_reference;
	typedef value_type *								pointer;
	typedef const value_type *							const_pointer;
	typedef size_t 										size_type;
	typedef ptrdiff_t 									difference_type;

	class value_compare : public std::binary_function<value_type, value_type, bool> {
	protected:
		key_compare comp;

		explicit value_compare(key_compare &c) : comp(c) {};
	public:
		bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); };
	};


private:
	const static bool black = true;
	const static bool red = false;

	typedef struct Node {
		Node * left;
		Node * right;
		Node *parent;
		bool color;
		pointer content;
	}	_MapNode;

	typedef typename allocator_type::template rebind<_MapNode>::other allocator_rebind_type;

	_MapNode *_node;
	size_type _size;
	key_compare _compare;

	allocator_rebind_type _allocator_rebind;
	allocator_type _alloc;

	_MapNode * createNode(Node *parent, const_reference val, bool color) {
		Node *newNode = _allocator_rebind.allocate(1);
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->parent = parent;
		newNode->content = _alloc.allocate(1);
		_alloc.construct(newNode->content, val);
		newNode->color = color;
		return newNode;
	}

	std::pair<iterator, bool> _insertTree(Node *node, const_reference val) {
		std::pair<iterator, bool> ret;
		if (_size == 0) {
			_node = createNode(nullptr, val, black);
			++_size;
			return std::pair<iterator, bool>(begin(), true);
		}
		int comp = _compare(val.first, node->content->first) + _compare(node->content->first, val.first) * 2;
		if (comp == 0) return std::make_pair(node, false);
		else if (comp == 1 && node->left == nullptr) {
			Node *newNode = createNode(node, val, red);
			node->left = newNode;
			ret = std::make_pair(newNode, true);
			++_size;
		}
		else if (comp == 2 && node->right == nullptr) {
			Node *newNode = createNode(node, val, red);
			node->right = newNode;
			ret = std::make_pair(newNode, true);
			++_size;
		}
		if (comp == 1)
			return _insertTree(node->left, val);
		else if (comp == 2)
			return _insertTree(node->right, val);
		return ret;
	}

	_MapNode *getMinNode(Node *currentNode) {
		if (currentNode->left)
			return getMinNode(currentNode->left);
		return currentNode;
	}

	_MapNode *getMaxNode(Node *currentNode) {
		if (currentNode->right)
			return getMaxNode(currentNode->right);
		return currentNode;
	}

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
			_it = nextNode(_it);
			return *this;
		};
		iterator operator++(int) {
			iterator tmp(_it);
			operator++();
			return tmp;
		};
		iterator & operator--() { _it = prevNode(_it); return *this; };
		iterator operator--(int) {
			iterator tmp(_it);
			operator--();
			return tmp;
		};
		bool operator==(const iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const iterator &it) const { return this->_it->content != it._it->content; };

		bool operator==(const const_iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const const_iterator &it) const { return this->_it->content != it.getNode()->content; };
		reference operator*() const { return *(this->_it->content); }
		pointer operator->() const { return this->_it->content; }

		_MapNode *getNode() const { return _it; }

	private:
		_MapNode *findLowNode(_MapNode *currentNode) {
			if (currentNode->left)
				return findLowNode(currentNode->left);
			return currentNode;
		}

		_MapNode *findHighNode(_MapNode *currentNode) {
			if (currentNode->right)
				return findHighNode(currentNode->right);
			return currentNode;
		}

		_MapNode *nextNode(_MapNode* currentNode) {
			if (currentNode->right)
				return findLowNode(currentNode->right);
			else if (currentNode->parent && currentNode->parent->left == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}
	};

	/* const_iterator */
	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type const> {
	private:
		_MapNode * _it;
	public:
		explicit const_iterator(_MapNode* it = nullptr) : _it(it) {};
		const_iterator(const const_iterator &it) { *this = it; };
		const_iterator(const iterator &it) { *this = it; };
		~const_iterator() {};
		const_iterator& operator=(const const_iterator &it)  { this->_it = it._it; return *this; };
		const_iterator& operator=(const iterator &it)  { this->_it = it.getNode(); return *this; };
		const_iterator & operator++() { _it = nextNode(_it); return *this; };
		const_iterator operator++(int) {
			const_iterator tmp(_it);
			operator++();
			return tmp;
		};
		const_iterator & operator--() { _it = prevNode(_it); return *this; };
		const_iterator operator--(int) {
			const_iterator tmp(_it);
			operator--();
			return tmp;
		};
		bool operator==(const const_iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const const_iterator &it) const { return this->_it->content != it._it->content; };

		bool operator==(const iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const iterator &it) const { return this->_it->content != it.getNode()->content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }

		_MapNode *getNode() const { return _it; }
	private:
		_MapNode *findLowNode(_MapNode *currentNode) {
			if (currentNode->left)
				return findLowNode(currentNode->left);
			return currentNode;
		}

		_MapNode *findHighNode(_MapNode *currentNode) {
			if (currentNode->right)
				return findHighNode(currentNode->right);
			return currentNode;
		}

		_MapNode *nextNode(_MapNode* currentNode) {
			if (currentNode->right)
				return findLowNode(currentNode->right);
			else if (currentNode->parent && currentNode->parent->left == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}
	};

	/* reverse_iterator */
	class reverse_iterator : public std::reverse_iterator<iterator> {
	private:
		_MapNode* _it;
	public:
		explicit reverse_iterator(_MapNode* it = nullptr): _it(it) {};
		~reverse_iterator() {};
		reverse_iterator(const reverse_iterator &it) { *this = it; };
		reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it._it; return *this; };
		reverse_iterator & operator++() { _it = prevNode(_it); return *this; };
		reverse_iterator operator++(int) {
			reverse_iterator tmp(_it);
			operator++();
			return tmp;
		};
		reverse_iterator & operator--() { _it = nextNode(_it); return *this; };
		reverse_iterator operator--(int) {
			reverse_iterator tmp(_it);
			operator--();
			return tmp;
		};

		bool operator==(const reverse_iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const reverse_iterator &it) const { return this->_it->content != it._it->content; };

		bool operator==(const const_reverse_iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const const_reverse_iterator &it) const { return this->_it->content != it.getNode()->content; };
		T & operator*() const { return *(this->_it->content); };
		T * operator->() const { return this->it->content; }

		_MapNode *getNode() const { return _it; }
	private:
		_MapNode *findLowNode(_MapNode *currentNode) {
			if (currentNode->left)
				return findLowNode(currentNode->left);
			return currentNode;
		}

		_MapNode *findHighNode(_MapNode *currentNode) {
			if (currentNode->right)
				return findHighNode(currentNode->right);
			return currentNode;
		}

		_MapNode *nextNode(_MapNode* currentNode) {
			if (currentNode->right)
				return findLowNode(currentNode->right);
			else if (currentNode->parent && currentNode->parent->left == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}
	};

	/* const_reverse_iterator */
	class const_reverse_iterator : public std::reverse_iterator<iterator> {
	private:
		_MapNode* _it;
	public:
		explicit const_reverse_iterator(_MapNode* it = nullptr): _it(it) {};
		~const_reverse_iterator() {};
		const_reverse_iterator & operator=(const const_reverse_iterator &it) { this->_it = it._it; return *this; };
		const_reverse_iterator & operator=(const reverse_iterator &it) { this->_it = it.getNode(); return *this; };
		const_reverse_iterator(const const_reverse_iterator &it) { *this = it; };
		const_reverse_iterator(const reverse_iterator &it) { *this = it; };
		const_reverse_iterator & operator++() { _it = prevNode(_it); return *this; };
		const_reverse_iterator operator++(int) {
			const_reverse_iterator tmp(_it);
			operator++();
			return tmp;
		};
		const_reverse_iterator & operator--() { _it = nextNode(_it); return *this; };
		const_reverse_iterator operator--(int) {
			const_reverse_iterator tmp(_it);
			operator--();
			return tmp;
		};

		bool operator==(const const_reverse_iterator &it) const { return this->_it->content == it._it->content; };
		bool operator!=(const const_reverse_iterator &it) const { return this->_it->content != it._it->content; };

		bool operator==(const reverse_iterator &it) const { return this->_it->content == it.getNode()->content; };
		bool operator!=(const reverse_iterator &it) const { return this->_it->content != it.getNode()->content; };
		reference operator*() const { return *(this->_it->content); }
		pointer operator->() const { return this->it->content; }

		_MapNode *getNode() const { return _it; }

	private:
		_MapNode *findLowNode(_MapNode *currentNode) {
			if (currentNode->left)
				return findLowNode(currentNode->left);
			return currentNode;
		}

		_MapNode *findHighNode(_MapNode *currentNode) {
			if (currentNode->right)
				return findHighNode(currentNode->right);
			return currentNode;
		}

		_MapNode *nextNode(_MapNode* currentNode) {
			if (currentNode->right)
				return findLowNode(currentNode->right);
			else if (currentNode->parent && currentNode->parent->left == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			return currentNode->parent->parent;
		}
	};

	/* Constructor */
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _compare(comp), _alloc(alloc) {};

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0)
	: _compare(comp), _alloc(alloc) { for (; first != last; ++first) insert(first); };

	/* Copy constructor */
	map (const map& x);

	/* Assignation operator */
	map& operator= (const map& x);

	/* Destructor */
	~map() {};

	/* Iterators */
	iterator		begin() { return iterator(getMinNode(_node)); };
	const_iterator 	begin() const { return const_iterator(getMinNode(_node)); };
	iterator		end() { return iterator(getMaxNode(_node)); };
	const_iterator	end() const { return const_iterator(getMaxNode(_node)); };

	/* Reverse Iterators */
	reverse_iterator 		rbegin() { return reverse_iterator(getMaxNode(_node)); };
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(getMaxNode(_node)); };
	reverse_iterator 		rend() { return reverse_iterator(getMinNode(_node)); };
	const_reverse_iterator	rend() const { return const_reverse_iterator(getMinNode(_node)); };

	/* Capacity */
	bool empty() const { return _size == 0; };
	size_type size() const { return _size; };
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_node); };

	/* Element access */
	mapped_type& operator[] (const key_type& k);
	mapped_type& at (const key_type& k);
	const mapped_type& at (const key_type& k) const;

	/* Modifiers */

	std::pair<iterator, bool> insert (const_reference val) { return _insertTree(_node, val); };
	iterator insert (iterator position, const value_type& val);
	template <class InputIterator> void insert (InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);
	void erase (iterator position);
	size_type erase (const key_type& k);
	void erase (iterator first, iterator last);
	void swap (map& x);
	void clear();

	/* Observers */

	key_compare key_comp() const { return _compare; };
	value_compare value_comp() const { return value_comp(_compare); };


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
