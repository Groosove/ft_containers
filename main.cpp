//
// Created by Fenix Lavon on 12/12/20.
// Copyright (c) 2020 All rights reserved.
//

#include "list.hpp"
#include "stack.hpp"
int main() {
	{
		std::stack<int> tmp2;
		ft::stack<int> tmp;

		std::cout << "Original stack method empty(): " << tmp2.empty()
				  << std::endl;
		std::cout << "My realization stack method empty(): " << tmp.empty()
				  << std::endl;

		tmp2.push(5);
		tmp.push(5);

		std::cout << "Original stack method size():" << tmp2.size() << std::endl;
		std::cout << "My realization method size():" << tmp.size() << std::endl;

		std::cout << "Original stack method top():" << tmp2.top() << std::endl;
		std::cout << "My realization method top():" << tmp.top() << std::endl;

		std::cout << "Original stack method pop():" << std::endl; tmp2.pop();
		std::cout << "My realization method pop():" << std::endl; tmp.pop();

		std::cout << "Original stack method size():" << tmp2.size() << std::endl;
		std::cout << "My realization method size():" << tmp.size() << std::endl;
		for (int i = 0; i < 10; ++i) { tmp2.push(i); tmp.push(i); }

		std::cout << "Original stack method top():" << tmp2.top() << std::endl;
		std::cout << "My realization method top():" << tmp.top() << std::endl;
		std::cout << "Original stack method size():" << tmp2.size() << std::endl;
		std::cout << "My realization method size():" << tmp.size() << std::endl;
	}
	return 0;
}

