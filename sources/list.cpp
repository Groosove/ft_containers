//
// Created by Fenix Lavon on 12/22/20.
// Copyright (c) 2020 All rights reserved.
//

#include "../ft.hpp"
#include "../list.hpp"
#include <vector>
int main() {
	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_front(i);
		ft::list<int>::iterator it = _lst.begin();
		while (it != _lst.end())
			std::cout << *it++ << std::endl;

		std::cout << std::endl << _lst.front() << std::endl;
		std::cout << _lst.back() << std::endl << std::endl;

		std::list<int> _oList;
		std::cout << _oList.max_size() << std::endl;
		std::cout << _lst.max_size() << std::endl << std::endl;

		_oList.assign(7, 10);
		std::list<int>::iterator oIt = _oList.begin();
		while (oIt != _oList.end())
			std::cout << *oIt++ << std::endl;
		std::cout << *oIt++ << std::endl;

		std::cout << std::endl;
		ft::list<int> _aList;
		const int value = 10;
		const size_t size = 7;
		_aList.assign(size, value);
		ft::list<int>::iterator _aIt = _aList.begin();
		while (_aIt != _aList.end())
			std::cout << *_aIt++ << std::endl;
		std::cout << *_aIt++ << std::endl;
		std::cout << std::endl;
	}
	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = _lst.begin();
		std::cout << *it << std::endl;
		_lst.pop_front();
		it++;
		std::cout << *it << std::endl;
		it--;
		std::cout << *it << std::endl << std::endl;
	}
	{
		std::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		std::list<int>::iterator it = _lst.begin();
		std::cout << *it << std::endl;
		_lst.pop_front();
		it++;
		std::cout << *it << std::endl;
		it--;
		std::cout << *it << std::endl << std::endl;
	}

	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = _lst.end();
		std::cout << *--it << std::endl;
		_lst.pop_back();
		std::cout << *it << std::endl << std::endl;
	}
	{
		std::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		std::list<int>::iterator it = _lst.end();
		std::cout << *--it << std::endl;
		_lst.pop_back();
		std::cout << *it << std::endl;
		std::cout << std::endl;
	}
	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = ++_lst.begin();
		_lst.insert(it, 50);
		for (it = _lst.begin(); it != _lst.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << std::endl;
	}
	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = ++_lst.begin();
		const size_t val = 50;
		_lst.insert(it, 2, val);
		for (it = _lst.begin(); it != _lst.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << std::endl;
	}
	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = ++_lst.begin();
		std::vector<int> vr(5, 30);
		_lst.insert(it, vr.begin(), vr.end());
		for (it = _lst.begin(); it != _lst.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << std::endl;
	}
	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = _lst.begin();
		ft::list<int>::iterator ite = _lst.begin();
		for (int i = 0; i < 3; ++i)
			ite++;
		_lst.erase(it, ite);
		for (it = _lst.begin(); it != _lst.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << std::endl;
	}
	{
		std::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		std::list<int>::iterator it = _lst.begin();
		std::list<int>::iterator ite = _lst.begin();
		for (int i = 0; i < 3; ++i)
			ite++;
		_lst.erase(it, ite);
		for (it = _lst.begin(); it != _lst.end(); ++it)
			std::cout << *it << std::endl;
		std::cout << std::endl;
	}

}

