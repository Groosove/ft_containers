//
// ft_containers
//
// Created by Артур Лутфуллин on 31.12.2020.
// Copyright (c) 2020 Артур Лутфуллин. All right reserved. 
//
#pragma once

#include "ft.hpp"
template <class T, class Alloc>
class ft::vector {
public:
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;
	typedef T 					value_type;
	typedef Alloc 				allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef size_t 				size_type;
	typedef ptrdiff_t 			difference_type;

private:
	pointer 		_arr;
	allocator_type	_alloc;
	size_type 		_size;
	size_type 		_capacity;

	pointer createVector(const_reference val) {
		pointer arr = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(arr + i, val);
		return arr;
	}

	void reallocVector(size_type range = 0) {
		pointer arr = _alloc.allocate((_size + range) * 2);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(arr + i, *(_arr + i));
		for (size_type i = 0; i != _size; ++i)
			_alloc.destroy(_arr + i);
		if (_capacity)
			_alloc.deallocate(_arr, _capacity);
		_capacity = (_size + range) * 2;
		_arr = arr;
	}

public:
	/* Constructor */
	explicit vector (const allocator_type& alloc = allocator_type())
		: _arr(nullptr), _alloc(alloc), _size(0), _capacity(0) {};

	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(n), _capacity(_size) { _arr = createVector(val); };

	template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0)
		: _arr(nullptr), _alloc(alloc), _size(0), _capacity(0) {
		for (; first != last; ++first)
			push_back(*first);
	};

	/* copy construct */
	vector (const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity) {
		_arr = _alloc.allocate(_size);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(_arr + i, *(x._arr + i));
	};

	/* Destructor */
	~vector() {
		clear();
		if (_capacity)
			_alloc.deallocate(_arr, _capacity);
	};

	/* Assignation operator */
	vector& operator= (const vector& x) {
		clear();
		insert(begin(), x.begin(), x.end());
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
		iterator &operator-=(difference_type val) { _it -= val; return *this; };
		const_reference operator[](const_reference ref) { return _it[ref]; };
		reference operator*() { return *this->_it; }
		pointer operator->() { return this->_it; }

		bool operator==(const iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const iterator &other) const { return _it <= other.getElem(); };
		bool operator>=(const iterator &other) const { return _it >= other.getElem(); };
		bool operator<(const iterator &other) const { return _it < other.getElem(); };
		bool operator>(const iterator &other) const { return _it > other.getElem(); };

		bool operator==(const const_iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const const_iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const const_iterator &other) const { return _it <= other.getElem(); };
		bool operator>=(const const_iterator &other) const { return this->_it >= other.getElem(); };
		bool operator<(const const_iterator &other) const { return _it < other.getElem(); };
		bool operator>(const const_iterator &other) const { return _it > other.getElem(); };
		pointer getElem() const { return _it; }
	};

	/* const iterator */
	class const_iterator: public ft::iterator<std::random_access_iterator_tag, value_type const > {
	private:
		pointer _it;
	public:
		explicit const_iterator(pointer it = nullptr) : _it(it) {};
		~const_iterator() {};
		const_iterator & operator=(const_iterator const &it) {
			this->_it = it._it;
			return *this;
		}
		const_iterator & operator=(iterator const &it) {
			this->_it = it.getElem();
			return *this;
		}
		const_iterator(const_iterator const &it) { *this = it; }
		const_iterator(iterator const &it) { *this = it; }
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
		const_iterator &operator-=(difference_type val) { _it -= val; return *this; };
		difference_type operator+(iterator it) const { return _it - it._it; }
		difference_type operator-(iterator it) const { return _it - it._it; }
		const_reference operator[](const_reference ref) { return _it[ref]; };
		const_reference operator*() { return *this->_it; }
		const_pointer operator->() { return this->_it; }

		bool operator==(iterator const &other) const { return _it == other.getElem(); };
		bool operator!=(iterator const &other) const { return _it != other.getElem(); };
		bool operator<=(iterator const &other) const { return _it <= other.getElem(); };
		bool operator>=(iterator const &other) const { return _it >= other.getElem(); };
		bool operator<(iterator const &other) const { return _it < other.getElem(); };
		bool operator>(iterator const &other) const { return _it > other.getElem(); };

		bool operator==(const const_iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const const_iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const const_iterator &other) const { return _it <= other.getElem(); };
		bool operator>=(const const_iterator &other) const { return _it >= other.getElem(); };
		bool operator<(const const_iterator &other) const { return _it < other.getElem(); };
		bool operator>(const const_iterator &other) const { return _it > other.getElem(); };
		const_pointer getElem() const { return this->_it; }
	};

	/* reverse iterator */
	class reverse_iterator: public ft::reverse_iterator<iterator> {
	private:
		pointer _it;
	public:
		explicit reverse_iterator(pointer it = nullptr) : _it(it) {};
		~reverse_iterator() {};
		reverse_iterator & operator=(const iterator &it) {
			this->_it = it._it;
			return *this;
		}
		reverse_iterator(reverse_iterator const &it) { *this = it; }
		reverse_iterator & operator++() { this->_it = _it - 1; return *this; };
		reverse_iterator operator++(int) {
			reverse_iterator tmp(_it);
			this->_it = _it - 1;
			return tmp;
		};
		reverse_iterator & operator--() { this->_it = _it + 1; return *this; };
		reverse_iterator operator--(int) {
			reverse_iterator tmp(_it);
			this->_it = this->_it + 1;
			return tmp;
		};

		reverse_iterator operator+(difference_type val) const { return reverse_iterator(_it - val); };
		reverse_iterator operator-(difference_type val) const { return reverse_iterator(_it + val); };
		difference_type operator+(reverse_iterator &it) const { return _it - it._it; }
		difference_type operator-(reverse_iterator &it) const { return _it + it._it; }
		reverse_iterator &operator+=(difference_type val) { _it -= val; return *this; };
		reverse_iterator &operator-=(difference_type val) { _it += val; return *this; };
		const_reference operator[](const_reference ref) const { return *(_it - ref); };
		reference operator*() { return *this->_it; }
		pointer operator->() { return this->_it; }

		bool operator==(const reverse_iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const reverse_iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const reverse_iterator &other) const { return _it >= other.getElem(); };
		bool operator>=(const reverse_iterator &other) const { return _it <= other.getElem(); };
		bool operator<(const reverse_iterator &other) const { return _it > other.getElem(); };
		bool operator>(const reverse_iterator &other) const { return _it < other.getElem(); };

		bool operator==(const const_reverse_iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const const_reverse_iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const const_reverse_iterator &other) const { return _it >= other.getElem(); };
		bool operator>=(const const_reverse_iterator &other) const { return _it <= other.getElem(); };
		bool operator<(const const_reverse_iterator &other) const { return _it > other.getElem(); };
		bool operator>(const const_reverse_iterator &other) const { return _it < other.getElem(); };
		pointer getElem() const { return this->_it; }
	};

	/* const reverse iterator */
	class const_reverse_iterator: public ft::reverse_iterator<const_iterator> {
	private:
		pointer _it;
	public:
		explicit const_reverse_iterator(pointer it = nullptr) : _it(it) {};
		~const_reverse_iterator() {};
		const_reverse_iterator & operator=(const const_reverse_iterator &it) {
			this->_it = it._it;
			return *this;
		}
		const_reverse_iterator & operator=(const reverse_iterator &it) {
			this->_it = it.getElem();
			return *this;
		}
		const_reverse_iterator(reverse_iterator const &it) { *this = it; }
		const_reverse_iterator(const_reverse_iterator const &it) { *this = it; }
		const_reverse_iterator & operator++() { this->_it = _it - 1; return *this; };
		reverse_iterator operator++(int) {
			reverse_iterator tmp(_it);
			this->_it = _it - 1;
			return tmp;
		};
		const_reverse_iterator & operator--() { this->_it = _it + 1; return *this; };
		const_reverse_iterator operator--(int) {
			const_reverse_iterator tmp(_it);
			this->_it = this->_it + 1;
			return tmp;
		};

		const_reverse_iterator operator+(difference_type val) const { return const_reverse_iterator(_it - val); };
		const_reverse_iterator operator-(difference_type val) const { return const_reverse_iterator(_it + val); };
		difference_type operator+(const_reverse_iterator &it) const { return _it - it._it; }
		difference_type operator-(const_reverse_iterator &it) const { return _it + it._it; }
		const_reverse_iterator &operator+=(difference_type val) { _it -= val; return *this; };
		const_reverse_iterator &operator-=(difference_type val) { _it += val; return *this; };
		const_reference operator[](const_reference ref) { return *(_it - ref); };
		const_reference operator*() { return *this->_it; }
		const_pointer operator->() { return this->_it; }

		bool operator==(const reverse_iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const reverse_iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const reverse_iterator &other) const { return _it >= other.getElem(); };
		bool operator>=(const reverse_iterator &other) const { return _it <= other.getElem(); };
		bool operator<(const reverse_iterator &other) const { return _it > other.getElem(); };
		bool operator>(const reverse_iterator &other) const { return _it < other.getElem(); };

		bool operator==(const const_reverse_iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const const_reverse_iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const const_reverse_iterator &other) const { return _it >= other.getElem(); };
		bool operator>=(const const_reverse_iterator &other) const { return _it <= other.getElem(); };
		bool operator<(const const_reverse_iterator &other) const { return _it > other.getElem(); };
		bool operator>(const const_reverse_iterator &other) const { return _it < other.getElem(); };
		const_pointer getElem() const { return this->_it; }
	};

	/* iterators */
	iterator 		begin() { return iterator(this->_arr); };
	const_iterator 	begin() const { return const_iterator(this->_arr); };
	iterator 		end() { return iterator(this->_arr + this->_size); };
	const_iterator 	end() const { return const_iterator(this->_arr + this->_size); };

	reverse_iterator 		rbegin() { return reverse_iterator(this->_arr + this->_size - 1); };
	const_reverse_iterator 	rbegin() const { return const_reverse_iterator(this->_arr + this->_size - 1); };
	reverse_iterator 		rend() { return reverse_iterator(this->_arr - 1); };
	const_reverse_iterator 	rend() const { return const_reverse_iterator(this->_arr - 1); };

	/* Capacity */
	size_type 	size() const { return _size; };
	size_type 	max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_arr[0]); };
	void 		resize (size_type n, value_type val = value_type()) {
		while (this->_size != n)
			(_size > n) ? pop_back() : push_back(val);
	};
	size_type 	capacity() const { return _capacity; };
	bool 		empty() const { return _size == 0; };
	void 		reserve (size_type n) {
		if (_capacity > n)
			return;
		pointer arr = _alloc.allocate(n);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(arr + i, *(_arr + i));
		for (size_type i = 0; i != _size; ++i)
			_alloc.destroy(_arr + i);
		if (_capacity)
			_alloc.deallocate(_arr, _capacity);
		_capacity = n;
		_arr = arr;
	};

	/* Element access */
	reference operator[] (size_type n) { return _arr[n]; };
	const_reference operator[] (size_type n) const { return _arr[n]; };
	reference at (size_type n) {
		if (n >= _size)
			throw std::out_of_range("index out of range");
		return _arr[n];
	};
	const_reference at (size_type n) const {
		if (n >= _size)
			throw std::out_of_range("index out of range");
		return _arr[n];
	};
	reference front() { return *_arr; };
	const_reference front() const { return *_arr; };
	reference back() { return *(_arr + _size - 1); };
	const_reference back() const { return *(_arr + _size - 1); };

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last,
			typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		clear();
		for (; first != last; ++first)
			push_back(*first);
	};
	void assign (size_type n, const value_type& val) {
		clear();
		insert(begin(), n, val);
	};
	void push_back (const value_type& val) {
		if (_capacity == 0) {
			_size = 1;
			_capacity = 1;
			_arr = createVector(val);
		} else {
			if (_size == _capacity)
				reallocVector();
			_alloc.construct(_arr + _size, val);
			++_size;
		}
	};
	void pop_back() { _alloc.destroy(_arr + --_size); };
	iterator insert (iterator position, const value_type& val) {
		pointer pos = position.getElem();
		if (_size + 1  > _capacity)
			reallocVector();
		std::memmove(pos + 1, pos, static_cast<size_type>((end().getElem() - pos)) * sizeof(value_type));
		_alloc.construct(pos, val);
		_size += 1;
		return iterator(pos);
	};
	void insert (iterator position, size_type n, const value_type& val) {
		pointer pos = position.getElem();
		if (_size + n  > _capacity) {
			difference_type index = end().getElem() - pos;
			reallocVector(n);
			pos =  end().getElem() - index;
		}
		std::memmove(pos + n, pos, static_cast<size_type>((end().getElem() - pos)) * sizeof(value_type));
		for (size_type i = 0; i != n; ++i, ++_size)
			_alloc.construct(pos + i, val);
	};
	template <class InputIterator> void insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		size_type range = static_cast<size_type>(last.operator->() - first.operator->());
		pointer pos = position.getElem();
		if (_size + range  > _capacity) {
			difference_type index = end().getElem() - pos;
			reallocVector(range);
			pos =  end().getElem() - index;
		}
		std::memmove(pos + range, pos, static_cast<size_type>((end().getElem() - pos)) * sizeof(value_type));
		for (size_type i = 0; i != range; ++i, ++_size, ++first)
			_alloc.construct(pos + i, *first);
	};
	iterator erase (iterator position) {
		pointer pos = position.getElem();
		_alloc.destroy(pos);
		std::memmove(pos, pos + 1, static_cast<size_type>(abs(end().getElem() - pos - 1)) * sizeof(value_type));
		--this->_size;
		return iterator(pos);
	};
	iterator erase (iterator first, iterator last) {
		for (; first != last; )
			erase(--last);
		return last;
	};
	void swap (vector& x) {
		pointer arr = x._arr;
		size_type size = x._size;
		size_type capacity = x._capacity;
		allocator_type alloc = x._alloc;

		x._arr = _arr;
		x._size = _size;
		x._capacity = _capacity;
		x._alloc = _alloc;

		_arr = arr;
		_size = size;
		_capacity = capacity;
		_alloc = alloc;
	};
	void clear() {
		for (size_type i = 0; i != _size; ++i)
			_alloc.destroy(_arr + i);
		_size = 0;
	};

};

template <class T, class Alloc> bool ft::operator==
		(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
	typename ft::vector<T, Alloc>::const_iterator l_it = lhs.begin();
	typename ft::vector<T, Alloc>::const_iterator l_ite = lhs.end();
	typename ft::vector<T, Alloc>::const_iterator r_it = rhs.begin();
	typename ft::vector<T, Alloc>::const_iterator r_ite = rhs.end();

	if (lhs.size() != rhs.size()) return false;

	for (; l_it != l_ite; ++l_it, ++r_it) if (*l_it != *r_it) return false;

	return true;
};

template <class T, class Alloc> bool ft::operator!=
		(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(lhs == rhs); };

template <class T, class Alloc> bool ft::operator<
	(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
	typename ft::vector<T, Alloc>::const_iterator l_it = lhs.begin();
	typename ft::vector<T, Alloc>::const_iterator l_ite = lhs.end();
	typename ft::vector<T, Alloc>::const_iterator r_it = rhs.begin();
	typename ft::vector<T, Alloc>::const_iterator r_ite = rhs.end();

	for (; l_it != l_ite && r_it != r_ite; ++l_it, ++r_it)
		if (*l_it < *r_it) return true;

	if (l_it != l_ite) return false;

	return (r_it != r_ite);
};

template <class T, class Alloc> bool ft::operator<=
		(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(rhs < lhs); };

template <class T, class Alloc> bool ft::operator>
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) { return (rhs < lhs); };

template <class T, class Alloc> bool ft::operator>=
	(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) { return !(lhs < rhs); };

template <class T, class Alloc> void ft::swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) { x.swap(y); };