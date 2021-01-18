//
// Created by Fenix Lavon on 1/18/21.
// Copyright (c) 2021 All rights reserved.
//

#include <map>
#include <iostream>

int main() {
	std::map<std::string, int> _map;

	_map.insert(std::pair<std::string, int>("a", 0));
	_map.insert(std::pair<std::string, int>("g", -1));
	_map.insert(std::pair<std::string, int>("c", 2));
	_map.insert(std::pair<std::string, int>("k", -4));
	_map.insert(std::pair<std::string, int>("b", 1));
	_map.insert(std::pair<std::string, int>("f", 5));
	_map.insert(std::pair<std::string, int>("j", -3));
	_map.insert(std::pair<std::string, int>("d", 3));
	_map.insert(std::pair<std::string, int>("h", -2));
	_map.insert(std::pair<std::string, int>("e", 4));
	_map.insert(std::pair<std::string, int>("l", -5));

	std::map<std::string, int>::iterator _it = _map.begin();
	for (int i = 0; i < 11; ++i, ++_it) {
		std::cout << _it->first << " " << _it->second << std::endl;
	}
}