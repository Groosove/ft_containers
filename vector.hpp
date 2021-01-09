//
// ft_containers
//
// Created by Артур Лутфуллин on 31.12.2020.
// Copyright (c) 2020 Артур Лутфуллин. All right reserved. 
//

#ifndef FT_CONTAINERS_VECTOR_HPP
# define FT_CONTAINERS_VECTOR_HPP

#include <vector>
#include "ft.hpp"

template <class T, class Alloc>
class ft::vector {
public:
	typedef T 					value_type;
	typedef Alloc 				allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef size_t 				size_type;
	typedef ptrdiff_t 			difference_type;

private:
	pointer _arr;
	allocator_type _alloc;
	size_type _size;
	size_type _capacity;

	pointer createVector(const_reference val) {
		pointer arr = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(arr + i, val);
		return arr;
	}

	void reallocVector() {
		_capacity = _size * 2;
		pointer arr = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(arr + i, *(_arr + i));
		for (size_type i = 0; i != _size; ++i)
			_alloc.destroy(_arr + i);
		_arr = arr;
	}

public:
	/* Constructor */
	explicit vector (const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(0), _capacity(1) { _arr = createVector(value_type()); };
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(n), _capacity(_size) { _arr = createVector(val); };
	template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(0), _capacity(1) {
		_arr = createVector(value_type());
		while (first != last) {
			push_back(*first);
			first++;
		}
	};

	vector (const vector& x) : _alloc(x._alloc), _size(x._size) {
		_arr = _alloc.allocate(_size);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(_arr + i, *(x._arr + i));
	};

	/* Destructor */
	~vector() { clear(); };

	/* Assignation operator */
	vector& operator= (const vector& x) {
		if (_size != 0)
			clear();
		_size = x._size;
		_alloc = x._alloc;
		_arr = _alloc.allocate(_size);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(_arr + i, *(x._arr + i));
		return *this;
	};

	/* iterator */
	class iterator: public ft::iterator<std::random_access_iterator_tag, value_type> {
	private:
		pointer _it;
	public:
		explicit iterator(pointer it = nullptr) : _it(it) {};
		~iterator() {};
		iterator & operator=(const iterator &it) {
			this->_it = it._it;
			return *this;
		}
		iterator(const iterator &it) { *this = it; }
		iterator & operator++() { this->_it = _it + 1; return *this; };
		iterator operator++(int) {
			iterator tmp(_it);
			this->_it = _it + 1;
			return tmp;
		};
		iterator & operator--() { this->_it = _it - 1; return *this; };
		iterator operator--(int) {
			iterator tmp(_it);
			this->_it = this->_it - 1;
			return tmp;
		};

		iterator operator+(difference_type val) const { return iterator(_it + val); };
		iterator operator-(difference_type val) const { return iterator(_it - val); };
		difference_type operator+(iterator &it) const { return _it + it._it; }
		difference_type operator-(iterator &it) const { return _it - it._it; }
		iterator &operator+=(difference_type val) { _it += val; return *this; };
		iterator &operator-=(difference_type val) { _it = val; return *this; };
		const_reference operator[](const_reference ref) { return _it[ref]; };
		reference operator*() { return *this->_it; }
		pointer operator->() { return this->_it; }

		bool operator==(const iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const iterator &other) const { return _it <= other.getElem(); };
		bool operator>=(const iterator &other) const { return _it >= other.getElem(); };
		bool operator<(const iterator &other) const { return _it < other.getElem(); };
		bool operator>(const iterator &other) const { return _it > other.getElem(); };
		pointer getElem() const { return this->_it; }
	};

	/* const iterator */
	class const_iterator: public ft::iterator<std::random_access_iterator_tag, value_type> {
	private:
		pointer _it;
	public:
		explicit const_iterator(pointer it = nullptr) : _it(it) {};
		~const_iterator() { delete [] this->_it; };
		const_iterator & operator=(const iterator &it) {
			if (this->_it != nullptr)
				delete [] this->_it;
			this->_it = it._it;
			return *this;
		}
		const_iterator(const const_iterator &it) { *this = it; }
		const_iterator & operator++() { this->_it = _it + 1; return *this; };
		const_iterator operator++(int) {
			const_iterator tmp(_it);
			this->_it = _it + 1;
			return tmp;
		};
		const_iterator & operator--() { this->_it = _it - 1; return *this; };
		const_iterator operator--(int) {
			iterator tmp(_it);
			this->_it = this->_it - 1;
			return tmp;
		};

		const_iterator operator+(difference_type val) const { return const_iterator(_it + val); };
		const_iterator operator-(difference_type val) const { return const_iterator(_it - val); };
		const_iterator &operator+=(difference_type val) { _it += val; return *this; };
		const_iterator &operator-=(difference_type val) { _it = val; return *this; };
		difference_type operator+(iterator it) const { return _it - it._it; }
		difference_type operator-(iterator it) const { return _it - it._it; }
		const_reference operator[](const_reference ref) { return _it[ref]; };
		const_reference operator*() { return *this->_it; }
		pointer operator->() { return this->_it; }

		bool operator==(const_iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const_iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const_iterator &other) const { return _it <= other.getElem(); };
		bool operator>=(const_iterator &other) const { return _it >= other.getElem(); };
		bool operator<(const_iterator &other) const { return _it < other.getElem(); };
		bool operator>(const_iterator &other) const { return _it > other.getElem(); };
		pointer getElem() { return this->_it; }
	};

	/* reverse iterator */
	class reverse_iterator: public ft::reverse_iterator<iterator> {};

	/* const reverse iterator */
	class const_reverse_iterator: public ft::reverse_iterator<const_iterator> {};

	/* iterators */
	iterator begin() { return iterator(this->_arr); };
	const_iterator begin() const { return const_iterator(this->_arr); };
	iterator end() { return iterator(this->_arr + this->_size); };
	const_iterator end() const { return const_iterator(this->_arr + this->_size); };
	reverse_iterator rbegin() { return reverse_iterator(this->_arr + this->_size - 1); };
	const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_arr + this->_size - 1); };
	reverse_iterator rend() { reverse_iterator(this->_arr); };
	const_reverse_iterator rend() const { const_reverse_iterator(this->_arr); };

	/* Capacity */
	size_type size() const { return _size; };
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_arr[0]); };
	void resize (size_type n, value_type val = value_type());
	size_type capacity() const { return _capacity; };
	bool empty() const { return _size == 0; };
	void reserve (size_type n);

	/* Element access */
	reference operator[] (size_type n) {
		return *(_arr + n);
	};
	const_reference operator[] (size_type n) const {
		return *(_arr + n);
	};
	reference at (size_type n) {
		if (n >= _size)
			std::out_of_range("index out of range");
		return *(_arr + n);
	};
	const_reference at (size_type n) const {
		if (n >= _size)
			std::out_of_range("index out of range");
		return *(_arr + n);
	};
	reference front() { return *_arr; };
	const_reference front() const { return *_arr; };
	reference back() { return *(_arr + _size - 1); };
	const_reference back() const { return *(_arr + _size - 1); };

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last);
	void assign (size_type n, const value_type& val);
	void push_back (const value_type& val) {
		if (_size == _capacity)
			reallocVector();
		_alloc.construct(_arr + _size, val);
		_size++;
	};
	void pop_back() {
		_alloc.destroy(_arr + _size - 1);
		--_size;
	};
	iterator insert (iterator position, const value_type& val) {
		if (_size + 1 == _capacity)
			reallocVector();
		size_type ite = end().getElem() - _arr;
		size_type pos = position.getElem() - _arr;
		for (size_type i = pos; i != ite; ++i)
			_arr[i + 1] = _arr[i];
		_alloc.construct(_arr + pos, val);
		_size += 1;
		return position;
	};
	void insert (iterator position, size_type n, const value_type& val) {
		if (_size + 1 == _capacity)
			reallocVector();
		size_type ite = end().getElem() - _arr + n;
		size_type pos = position.getElem() - _arr;
		for (size_type i = pos; i != ite; ++i)
			_arr[i + 1] = _arr[i];
		for (size_type i = 0; i != pos; ++i)
			_alloc.construct(&_arr[i], val);
		_size += n;
	};
	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last);
	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);
	void swap (vector& x);
	void clear() {
		for (size_type i = 0; i != _size; ++i)
			_alloc.destroy(_arr + i);
		_size = 0;
	};

};

template <class T, class Alloc> bool operator==
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator!=
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator<
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator<=
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator>
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> bool operator>=
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs);

template <class T, class Alloc> void
	swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y);
#endif
