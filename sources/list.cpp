//
// Created by Fenix Lavon on 12/22/20.
// Copyright (c) 2020 All rights reserved.
//

#include "../ft.hpp"
#include "../list.hpp"
int main() {
	{
		ft::list<int> _lst(10);
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		ft::list<int>::iterator it = _lst.begin();
		std::cout << *it << std::endl;
		it++;
		std::cout << *it << std::endl;
	}
}

