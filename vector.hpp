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
	typedef value_type& 		reference;
	typedef const value_type	&const_reference;
	typedef value_type *		pointer;
	typedef size_t 				size_type;
	typedef ptrdiff_t 			difference_type;

private:
	pointer _arr;
	allocator_type _alloc;
	size_type _size;

	pointer createVector(size_type size, const_reference val) {
		pointer arr = _alloc.allocate(size);
		for (size_type i = 0; i < size; ++i)
			_alloc.construct(arr + i, val);
		return arr;
	}

public:
	/* Constructor */
	explicit vector (const allocator_type& alloc = allocator_type())
		: _alloc(alloc) { _arr = createVector(0, value_type()); };
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(n) { _arr = createVector(_size, val); };
	template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		: _alloc(alloc) {
		createVector(0, value_type());
		while (first != last) {
			push_back(*first);
			first++;
		}
	};

	vector (const vector& x) { *this = x; };

	/* Destructor */
	~vector() { clear(); };

	/* Assignation operator */
	vector& operator= (const vector& x) {
		if (_arr != nullptr)
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
		~iterator() { delete [] this->_it; };
		iterator & operator=(const iterator &it) {
			if (this->_it != nullptr)
				delete [] this->_it;
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
		iterator &operator+=(difference_type val) { _it += val; return *this; };
		iterator &operator-=(difference_type val) { _it = val; return *this; };
		const_reference operator[](const_reference ref) { return _it[ref]; };
		const_reference operator*() { return *this->_it; }
		pointer operator->() { return this->_it; }

		bool operator==(const iterator &other) const { return _it == other.getElem(); };
		bool operator!=(const iterator &other) const { return _it != other.getElem(); };
		bool operator<=(const iterator &other) const { return _it <= other.getElem(); };
		bool operator>=(const iterator &other) const { return _it >= other.getElem(); };
		bool operator<(const iterator &other) const { return _it < other.getElem(); };
		bool operator>(const iterator &other) const { return _it > other.getElem(); };
		pointer getElem() { return this->_it; }
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
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	/* Capacity */
	size_type size() const { return _size; };
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(pointer); };
	void resize (size_type n, value_type val = value_type());
	size_type capacity() const;
	bool empty() const { return _arr == nullptr; };
	void reserve (size_type n);

	/* Element access */
	reference operator[] (size_type n);
	const_reference operator[] (size_type n) const;
	reference at (size_type n);
	const_reference at (size_type n) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	/* Modifiers */
	template <class InputIterator> void assign (InputIterator first, InputIterator last);
	void assign (size_type n, const value_type& val);
	void push_back (const value_type& val);
	void pop_back();
	iterator insert (iterator position, const value_type& val);
	void insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last);
	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);
	void swap (vector& x);
	void clear() {
		for (size_type i = 0; i != size(); ++i)
			_alloc.destroy(_arr + i);
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
