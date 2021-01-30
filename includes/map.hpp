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
	public:
		key_compare comp;

		value_compare(key_compare c) : comp(c) {};
	public:
		bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); };
	};


private:
	const static bool black = false;
	const static bool red = true;

	typedef struct Node {
		Node * left;
		Node * right;
		Node *parent;
		bool color;
		pointer content;
	}	_MapNode;

	typedef typename allocator_type::template rebind<_MapNode>::other allocator_rebind_type;

	_MapNode *_node;
	_MapNode *_end_node;
	_MapNode *_begin_node;
	size_type _size;
	key_compare _compare;

	allocator_rebind_type _allocator_rebind;
	allocator_type _alloc;

	_MapNode * createNode(Node *parent, const_reference val, bool color, size_type size) {
		Node *newNode = _allocator_rebind.allocate(1);
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->parent = parent;
		newNode->content = _alloc.allocate(1);
		_alloc.construct(newNode->content, val);
		newNode->color = color;
		_size += size;
		return newNode;
	}

	void destroyNode(_MapNode *node) {
		_alloc.destroy(node->content);
		_alloc.deallocate(node->content, 1);
		_allocator_rebind.deallocate(node, 1);
		--_size;
	}

	void createBeginAndEndNode() {
		_end_node = _allocator_rebind.allocate(1);
		_end_node->left = nullptr;
		_end_node->right = nullptr;
		_end_node->color = black;
		_end_node->content = nullptr;
		_begin_node = _allocator_rebind.allocate(1);
		_begin_node->left = nullptr;
		_begin_node->right = nullptr;
		_begin_node->color = black;
		_begin_node->content = nullptr;
	}

	inline void insertRightNode(_MapNode *insertNode, _MapNode *parent) {
		if (parent->right == _end_node) {
			insertNode->right = _end_node;
			_end_node->parent = insertNode;
		}
		parent->right = insertNode;
	}

	inline void insertLeftNode(_MapNode *insertNode, _MapNode *parent) {
		if (parent->left == _begin_node) {
			insertNode->left = _begin_node;
			_begin_node->parent = insertNode;
		}
		parent->left = insertNode;
	}

	std::pair<iterator, bool> _insertTree(_MapNode *node, const_reference val) {
		int comp = _compare(val.first, node->content->first) + _compare(node->content->first, val.first) * 2;

		if (comp == 0)
			return std::make_pair(iterator(node), false);
		else if (comp == 1 && node->left && node->left != _begin_node)
			return _insertTree(node->left, val);
		else if (comp == 2 && node->right && node->right != _end_node)
			return _insertTree(node->right, val);
		
		_MapNode *newNode = createNode(node, val, red, 1);
		(comp == 1) ? insertLeftNode(newNode, node) : insertRightNode(newNode, node);
//			treeBalance(node);
		return std::make_pair(iterator(newNode), true);
	}

	inline bool isRed(_MapNode *currentNode) { return (!currentNode) ? black : currentNode->color == red; }

	inline void linkRight(_MapNode *parent, _MapNode *right) {
		parent->right = right;
		if (right)
			right->parent = parent;
	}

	inline void linkLeft(_MapNode *parent, _MapNode *left) {
		parent->left = left;
		if (left)
			left->parent = parent;
	}

	_MapNode *rotateLeft(_MapNode* currentNode) {
		_MapNode *tmp = currentNode->right;
		if (currentNode->parent->right == currentNode)
			linkRight(currentNode->parent, tmp);
		else
			linkLeft(currentNode->parent, tmp);
		linkRight(currentNode, tmp->left);
		linkLeft(tmp, currentNode);

		tmp->color = currentNode->color;
		currentNode->color = red;
		return tmp;
	}

	_MapNode *rotateRight(_MapNode* currentNode) {
		_MapNode *tmp = currentNode->left;
		if (currentNode->parent->right == currentNode)
			linkRight(currentNode->parent, tmp);
		else
			linkLeft(currentNode->parent, tmp);
		linkRight(currentNode, tmp->right);
		linkLeft(tmp, currentNode);

		tmp->color = currentNode->color;
		currentNode->color = red;
		return tmp;
	}

	inline void invertColor(_MapNode *currentNode) {
		if (currentNode->right) currentNode->right->color = !currentNode->right->color;
		if (currentNode->left) currentNode->left->color = !currentNode->left->color;
		currentNode->color = !currentNode->color;
		if (_node == currentNode && isRed(_node))
			_node->color = !_node;
	}

	_MapNode *treeBalance(_MapNode* currentNode) {
		if (isRed(currentNode->right))
			currentNode = rotateLeft(currentNode);
		if (isRed(currentNode->left) && currentNode->left && isRed(currentNode->left->left))
			currentNode = rotateRight(currentNode);
		if (isRed(currentNode->left) && isRed(currentNode->right))
			invertColor(currentNode);
		return currentNode;
	}

	_MapNode *findLowNode(_MapNode *currentNode) {
		_MapNode *beginNode = currentNode;
		while (currentNode->left)
			currentNode = currentNode->left;
		if (currentNode->right && currentNode->right != _end_node && beginNode != currentNode)
			currentNode = findLowNode(currentNode->right);
		return currentNode;
	}

	_MapNode *findHighNode(_MapNode *currentNode) {
		_MapNode *beginNode = currentNode;
		while (currentNode->right)
			currentNode = currentNode->right;
		if (currentNode->left && currentNode->left != _begin_node && beginNode != currentNode)
			currentNode = findLowNode(currentNode->left);
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
		bool operator==(const iterator &it) const { return this->_it == it._it; };
		bool operator!=(const iterator &it) const { return this->_it != it._it; };

		bool operator==(const const_iterator &it) const { return this->_it == it.getNode(); };
		bool operator!=(const const_iterator &it) const { return this->_it != it.getNode(); };
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
			else if (currentNode->parent->right == currentNode)
				currentNode = currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->right == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->right;
			return tmp->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->left == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->left;
			return tmp->parent;
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
		bool operator==(const const_iterator &it) const { return this->_it == it._it; };
		bool operator!=(const const_iterator &it) const { return this->_it != it._it; };

		bool operator==(const iterator &it) const { return this->_it == it.getNode(); };
		bool operator!=(const iterator &it) const { return this->_it != it.getNode(); };
		value_type & operator*() const { return *(this->_it->content); };
		value_type * operator->() const { return this->_it->content; }

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
			else if (currentNode->parent->right == currentNode)
				currentNode = currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->right == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->right;
			return tmp->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->left == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->left;
			return tmp->parent;
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

		bool operator==(const reverse_iterator &it) const { return this->_it == it._it; };
		bool operator!=(const reverse_iterator &it) const { return this->_it != it._it; };

		bool operator==(const const_reverse_iterator &it) const { return this->_it == it.getNode(); };
		bool operator!=(const const_reverse_iterator &it) const { return this->_it != it.getNode(); };
		value_type & operator*() const { return *(this->_it->content); };
		value_type * operator->() const { return this->_it->content; }

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
			else if (currentNode->parent->right == currentNode)
				currentNode = currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->right == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->right;
			return tmp->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->left == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->left;
			return tmp->parent;
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

		bool operator==(const const_reverse_iterator &it) const { return this->_it == it._it; };
		bool operator!=(const const_reverse_iterator &it) const { return this->_it != it._it; };

		bool operator==(const reverse_iterator &it) const { return this->_it == it.getNode(); };
		bool operator!=(const reverse_iterator &it) const { return this->_it != it.getNode(); };
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
			else if (currentNode->parent->right == currentNode)
				currentNode = currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->right == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->right;
			return tmp->parent;
		}

		_MapNode *prevNode(_MapNode* currentNode) {
			if (currentNode->left)
				return findHighNode(currentNode->left);
			else if (currentNode->parent && currentNode->parent->right == currentNode)
				return currentNode->parent;
			_MapNode *tmp = currentNode;
			while (tmp->parent->left == tmp)
				if ((tmp = tmp->parent) == nullptr)
					return currentNode->left;
			return tmp->parent;
		}
	};

	/* Constructor */
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _node(nullptr), _size(0), _compare(comp), _alloc(alloc) { createBeginAndEndNode(); };

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0)
	: _node(nullptr), _size(0), _compare(comp), _alloc(alloc) {
		createBeginAndEndNode();
		insert(first, last);
	};

	/* Copy constructor */
	map (const map& x): _size(0), _allocator_rebind(x._allocator_rebind), _alloc(x._alloc) {
		createBeginAndEndNode();
		*this = x;
	};

	/* Assignation operator */
	map& operator= (const map& x) {
		clear();
		insert(x.begin(), x.end());
		return *this;
	};

	/* Destructor */
	~map() {
		clear();
		_allocator_rebind.deallocate(_begin_node, 1);
		_allocator_rebind.deallocate(_end_node, 1);
	};

	/* Iterators */
	iterator		begin() { return (_size != 0) ? iterator(_begin_node->parent) : iterator(_end_node); };
	const_iterator 	begin() const { return (_size != 0) ? const_iterator(_begin_node->parent) : const_iterator(_end_node); };
	iterator		end() { return iterator(_end_node); };
	const_iterator	end() const { return const_iterator(_end_node); };

	/* Reverse Iterators */
	reverse_iterator 		rbegin() { return (_size != 0) ? reverse_iterator(_end_node->parent) : reverse_iterator(_begin_node); };
	const_reverse_iterator	rbegin() const { return (_size != 0) ? const_reverse_iterator(_end_node->parent) : const_reverse_iterator(_begin_node); };
	reverse_iterator 		rend() { return reverse_iterator(_begin_node); };
	const_reverse_iterator	rend() const { return const_reverse_iterator(_begin_node); };

	/* Capacity */
	bool empty() const { return _size == 0; };
	size_type size() const { return _size; };
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_node); };

	/* Element access */
	mapped_type& operator[] (const key_type& k) { return insert(std::make_pair(k, mapped_type())).first->second; };

	/* Modifiers */
	std::pair<iterator, bool> insert (const_reference val) {
		if (_size == 0) {
			_node = createNode(nullptr, val, black, 1);
			_node->right = _end_node;
			_node->left = _begin_node;
			_end_node->parent = _node;
			_begin_node->parent = _node;
			return std::make_pair(iterator(_node), true);
		}
		return _insertTree(_node, val);
	};
	iterator insert (iterator position, const value_type& val) {
		(void)position;
		return insert(val).first;
	};
	template <class InputIterator> void insert (InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		for (; first != last; ++first)
			insert(*first);
	};
	void erase (iterator position) { erase(position->first); };


	size_type erase (const key_type& k) {
		if (_size == 0 || find(k) == end())
			return 0;
		_MapNode *node = find(k).getNode();
		if (node->right && _size != 1 && node->right != _end_node) {
			_MapNode *tmp = findLowNode(node->right);
			(_compare(tmp->content->first, tmp->parent->content->first)) ?
			tmp->parent->left = tmp->left : tmp->parent->right = tmp->right;
			linkLeft(tmp, node->left);
			linkRight(tmp, node->right);
			if (node != _node)
				(_compare(node->content->first, node->parent->content->first)) ?
				linkLeft(node->parent, tmp) : linkRight(node->parent, tmp);
			else {
				tmp->parent = nullptr;
				_node = tmp;
			}
		}
		else if (node->left && _size != 1 && node->left != _begin_node) {
			_MapNode *tmp = findHighNode(node->left);

			(_compare(tmp->content->first, tmp->parent->content->first)) ?
			tmp->parent->left = tmp->left : tmp->parent->right = tmp->right;
			linkLeft(tmp, node->left);
			linkRight(tmp, node->right);
			if (node != _node)
				(_compare(node->content->first, node->parent->content->first)) ?
				linkLeft(node->parent, tmp) : linkRight(node->parent, tmp);
			else {
				tmp->parent = nullptr;
				_node = tmp;
			}
		} else if (node->right == _end_node && _size != 1) {
			if (node->parent)
				linkRight(node->parent, _end_node);
		} else if (node->left == _begin_node && _size != 1) {
			if (node->parent)
				linkLeft(node->parent, _begin_node);
		}
		destroyNode(node);
		return 1;
	};
	void erase (iterator first, iterator last) {
		for (; first != last; ++first)
			erase(last->first);
	};

	void swap (map& x) {
		_MapNode *tmp = _node;
		_node = x._node;
		x._node = tmp;

		_MapNode *tmpBegin = _begin_node;
		_begin_node = x._begin_node;
		x._begin_node = tmpBegin;

		_MapNode *tmpEndNode = _end_node;
		_end_node = x._end_node;
		x._end_node = tmpEndNode;

		size_type tmp_size = _size;
		_size = x._size;
		x._size = tmp_size;
	};
	void clear() {
		while (_size != 0)
			erase(begin());
	};

	/* Observers */
	key_compare key_comp() const { return _compare; };
	value_compare value_comp() const { return value_compare(_compare); };


	/* Operations */
	iterator find (const key_type& k) {
		for (iterator it = begin(), ite = end(); it != ite; ++it)
			if (it->first == k)
				return it;
		return end();
	};
	const_iterator find (const key_type& k) const {
		for (const_iterator it = ++begin(), ite = end(); it != ite; ++it)
			if (it->first == k)
				return it;
		return end();
	};
	size_type count (const key_type& k) const {
		for (const_iterator it = begin(), ite = end(); it != ite; ++it)
			if (it->first == k)
				return 1;
		return 0;
	};
	iterator lower_bound (const key_type& k) {
		iterator it = begin();
		for (iterator ite = end(); it != ite && _compare(it->first, k); ++it) NULL;
		return it;
	};
	const_iterator lower_bound (const key_type& k) const {
		iterator it = begin();
		for (iterator ite = end(); it != ite && _compare(it->first, k); ++it) NULL;
		return it;
	};
	iterator upper_bound (const key_type& k) {
		iterator it = lower_bound(k);
		if (it != end() && !_compare(it->first, k) && !_compare(k, it->first))
			++it;
		return it;
	};
	const_iterator upper_bound (const key_type& k) const {
		const_iterator it = lower_bound(k);
		if (it != end() && !_compare(it->first, k) && !_compare(k, it->first))
			++it;
		return it;
	};
	std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const	{ return std::make_pair(lower_bound(k), upper_bound(k)); };
	std::pair<iterator,iterator>             equal_range (const key_type& k) 		{ return std::make_pair(lower_bound(k), upper_bound(k)); };
};
