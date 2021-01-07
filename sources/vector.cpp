//
// ft_containers
//
// Created by Артур Лутфуллин on 31.12.2020.
// Copyright (c) 2020 Артур Лутфуллин. All right reserved. 
//

#include "../ft.hpp"
#include "../vector.hpp"

template <class T>
void print_vector(T & vector) {
	size_t size = vector.size();
	for (size_t i = 0; i != size; ++i)
		std::cout << ' ' << vector[i];
	std::cout << std::endl;
}

template <class T, class STD>
bool check_vector(T &my_vector, STD &orig_vector) {
	size_t size = my_vector.size();
	for (size_t i = 0; i != size; ++i)
		if (my_vector[i] != orig_vector[i])
			return (false);
	return (true);
}

int main() {
	{
		std::vector<int> orig_vect;
		ft::vector<int> ft_vect;
	}
}