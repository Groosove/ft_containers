//
// Created by Fenix Lavon on 1/18/21.
// Copyright (c) 2021 All rights reserved.
//

#include <map>
#include <iostream>
#include "map.hpp"

int main() {
//	{
//		std::map<int, std::string> _map;
//		_map.insert(std::pair<int, std::string>(13, "a"));
//		_map.insert(std::pair<int, std::string>(6, "c"));
//		_map.insert(std::pair<int, std::string>(11, "d"));
//		_map.insert(std::pair<int, std::string>(22, "e"));
//		_map.insert(std::pair<int, std::string>(27, "b"));
//		_map.insert(std::pair<int, std::string>(25, "f"));
//		_map.insert(std::pair<int, std::string>(1, "g"));
//		_map.insert(std::pair<int, std::string>(15, "h"));
//		_map.insert(std::pair<int, std::string>(17, "i"));
//		_map.insert(std::pair<int, std::string>(8, "j"));
//
//		std::map<int, std::string>::iterator _it = _map.begin();
//		std::map<int, std::string>::iterator _ite = _map.end();
//		for (; _it != _ite ;  ++_it)
//			std::cout << _it->first << " " << _it->second << std::endl;
//
//		std::cout << std::endl;
//	}
	{
		ft::map<int, std::string> _map;
		_map.insert(std::pair<int, std::string>(13, "a"));
		_map.insert(std::pair<int, std::string>(6, "c"));
		_map.insert(std::pair<int, std::string>(22, "e"));
		_map.insert(std::pair<int, std::string>(11, "d"));
		_map.insert(std::pair<int, std::string>(27, "b"));
		_map.insert(std::pair<int, std::string>(25, "f"));
		_map.insert(std::pair<int, std::string>(1, "g"));
		_map.insert(std::pair<int, std::string>(15, "h"));
		_map.insert(std::pair<int, std::string>(17, "i"));
		_map.insert(std::pair<int, std::string>(8, "j"));

		ft::map<int, std::string>::iterator _it = _map.begin();
		ft::map<int, std::string>::iterator _ite = _map.end();
		for (; _it != _ite ;  ++_it)
			std::cout << _it->first << " " << _it->second << std::endl;
	}

	return 0;
}