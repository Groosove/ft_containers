//
// Created by Fenix Lavon on 12/22/20.
// Copyright (c) 2020 All rights reserved.
//

#include "../ft.hpp"
#include "../list.hpp"

int main() {
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = _lst.begin();
		while (it != _lst.end())
			std::cout << *it++ << std::endl;
		std::cout << *it << std::endl;

//		std::cout << _lst.front() << std::endl;
//		std::cout << _lst.back() << std::endl;

		std::list<int> _oList;
		std::cout << _oList.max_size() << std::endl;
		std::cout << _lst.max_size() << std::endl;

		_oList.assign(7, 10);
		std::list<int>::iterator oIt = _oList.begin();
		while (oIt != _oList.end())
			std::cout << *oIt++ << std::endl;

}

