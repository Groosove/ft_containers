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
	/* constuctor check */
	{
		size_t size = 5;
		ft::vector<int> vector1(size, 10);
		ft::vector<int> vector2(vector1);
		print_vector(vector2);
		ft::vector<double> vector3;
		ft::vector<double> vector4;
		vector4 = vector3;
		ft::vector<int>::iterator it = vector1.begin();
		ft::vector<int>::iterator ite = vector1.end();
		ft::vector<int> vector5(it, ite);
		print_vector(vector5);
	}
	{
		ft::vector<int> my_vector;
		std::vector<int> orig_vector;
		for (int i = 1; i < 100; ++ i)
			my_vector.push_back(i);
		for (int i = 1; i < 100; ++ i)
			orig_vector.push_back(i);
		if (check_vector(my_vector, orig_vector))
			std::cout << "OK" << std::endl;
		std::cout << "My capacity: " << my_vector.capacity() << std::endl;
		std::cout << "Orig capacity: " << orig_vector.capacity() << std::endl;
	}
}