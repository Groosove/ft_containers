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
void check_vector(T &my_vector, STD &orig_vector) {
	size_t size = my_vector.size();
	for (size_t i = 0; i != size; ++i)
		if (my_vector[i] != orig_vector[i])
			std::cout << "KO" << std::endl;
	std::cout << "OK" << std::endl;
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
	/* size, capacity, max_size check */
	{
		ft::vector<int> my_vector;
		std::vector<int> orig_vector;
		for (int i = 1; i < 100; ++ i) {
			my_vector.push_back(i);
			orig_vector.push_back(i);
		}
		check_vector(my_vector, orig_vector);
		std::cout << "My capacity: " << my_vector.capacity() << std::endl;
		std::cout << "Orig capacity: " << orig_vector.capacity() << std::endl;
		std::cout << "My size: " << my_vector.size() << std::endl;
		std::cout << "Orig size: " << orig_vector.size() << std::endl;
		std::cout << "My max_size: " << my_vector.max_size() << std::endl;
		std::cout << "Orig max_size: " << orig_vector.max_size() << std::endl;
	}
	/* iterators check */
	{
		ft::vector<int> my_vector;
		std::vector<int> orig_vector;
		for (int i = 1; i < 100; ++ i) {
			my_vector.push_back(i);
			orig_vector.push_back(i);
		}
		ft::vector<int>::iterator ite = my_vector.end();
		ft::vector<int>::iterator it = my_vector.begin();

		std::cout << (it <= ite ? "OK" : "KO") << std::endl;
		std::cout << (it < ite ? "OK" : "KO") << std::endl;
		std::cout << (it >= ite ? "OK" : "KO") << std::endl;
		std::cout << (it > ite ? "OK" : "KO") << std::endl;
		std::cout << (it == ite ? "OK" : "KO") << std::endl;
		std::cout << (it != ite ? "OK" : "KO") << std::endl;

		it += my_vector.size();
		std::cout << (it == ite ? "OK" : "KO") << std::endl;
		std::cout << (it - my_vector.size() == my_vector.begin() ? "OK" : "KO") << std::endl;\
		std::cout << (it - my_vector.size() == my_vector.begin() ? "OK" : "KO") << std::endl;
	}
	/* clear check */
	{
		std::cout << std::endl << "CLEAR CHECK: " << std::endl;
		ft::vector<int> my_vector;
		std::cout << (my_vector.empty() ? "OK" : "KO") << std::endl;
		my_vector.push_back(0);
		std::cout << (my_vector.empty() ? "OK" : "KO") << std::endl;
		for (int i = 1; i < 100; ++ i)
			my_vector.push_back(i);
		std::cout << (my_vector.empty() ? "OK" : "KO") << std::endl;
		my_vector.clear();
		std::cout << (my_vector.empty() ? "OK" : "KO") << std::endl;
	}

//	/* resize check */
//	{
//		std::cout << std::endl << "RESIZE CHECK: " << std::endl;
//		std::vector<int> myvector;
//		for (int i = 1;i < 10; ++i)
//			myvector.push_back(i);
//		myvector.resize(5);
//		myvector.resize(8,100);
//		myvector.resize(12);
//		std::cout << "myvector contains:"; print_vector(myvector);
//	}
//	{
//		ft::vector<int> myvector;
//		for (int i = 1;i < 10; ++i)
//			myvector.push_back(i);
//		myvector.resize(5);
//		myvector.resize(8,100);
//		myvector.resize(12);
//		std::cout << "myvector contains:"; print_vector(myvector);
//	}

	/* insert check */
	{
		std::vector<int> myvector (3,100);
		std::vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		myvector.insert (it,2,300);
		it = myvector.begin();
//		std::vector<int> anothervector (2,400);
//		myvector.insert (it+2,anothervector.begin(),anothervector.end());
//		int myarray [] = { 501,502,503 };
//		myvector.insert (myvector.begin(), myarray, myarray+3);

		std::cout << "myvector contains:"; print_vector(myvector);
	}
	{
		size_t size = 3;
		ft::vector<int> myvector (size,100);
		ft::vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		size = 2;
		myvector.insert (it, size, 300);
		it = myvector.begin();
//		std::vector<int> anothervector (2,400);
//		myvector.insert (it + 2, anothervector.begin(), anothervector.end());
//		int myarray [] = { 501,502,503 };E
//		myvector.insert (myvector.begin(), myarray, myarray+3);
		std::cout << "myvector contains:"; print_vector(myvector);
	}
	return 0;
}