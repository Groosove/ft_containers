//
// Created by Fenix Lavon on 12/22/20.
// Copyright (c) 2020 All rights reserved.
//

#include "../ft.hpp"
#include "../list.hpp"
#include <vector>
#include <cmath>

template< class T >
void print_list(T & list) {
	for (typename T::iterator it = list.begin(); it != list.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
	bool operator()(const int &value) { return (value % 2) == 1; }
};

bool same_integral_part (double first, double second) { return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
	bool operator() (double first, double second) { return (fabs(first-second)<5.0); }
};

bool mycomparison (double first, double second) { return ( int(first)<int(second) ); }

int main() {
	{
		ft::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_front(i);
		print_list(_lst);

		std::cout << std::endl << _lst.front() << std::endl;
		std::cout << _lst.back() << std::endl << std::endl;

		std::list<int> _oList;
		std::cout << _oList.max_size() << std::endl;
		std::cout << _lst.max_size() << std::endl << std::endl;

		_oList.assign(7, 10);
		print_list(_oList);

		std::cout << std::endl;
		ft::list<int> _aList;
		const int value = 10;
		const size_t size = 7;
		_aList.assign(size, value);
		print_list(_aList);
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
		std::cout << *it << std::endl;
		_lst.pop_back();
		std::cout << *it << std::endl << std::endl;
	}
	{
		std::list<int> _lst;
		for (int i = 0; i < 10; ++i)
			_lst.push_back(i);
		std::list<int>::iterator it = _lst.end();
		std::cout << *++it << std::endl;
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
	{
		std::list<int> first(3, 100);   // three ints with a value of 100
		std::list<int> second(5, 200);  // five ints with a value of 200

		first.swap(second);

		std::cout << "first contains:";
		for (std::list<int>::iterator it = first.begin(); it != first.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "second contains:";
		for (std::list<int>::iterator it = second.begin(); it != second.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		size_t size = 3;
		ft::list<int> first(size, 100);   // three ints with a value of 100
		size = 5;
		ft::list<int> second(size, 200);  // five ints with a value of 200

		first.swap(second);

		std::cout << "first contains:";
		for (ft::list<int>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "second contains:";
		for (ft::list<int>::iterator it = second.begin(); it != second.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	{
		std::list<int> mylist;
		for (int i = 1; i < 10; ++i) mylist.push_back(i);
		mylist.resize(5);
		mylist.resize(8, 100);
		mylist.resize(12);
		std::cout << "mylist contains:";
		for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		ft::list<int> mylist;
		for (int i = 1; i < 10; ++i)
			mylist.push_back(i);
		mylist.resize(5);
		mylist.resize(8, 100);
		mylist.resize(12);
		std::cout << "mylist contains:";
		for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		mylist.clear();
		mylist.push_back(100);
		std::cout << mylist.size() << std::endl;
	}


	{
		std::list<int> mylist1, mylist2;
		std::list<int>::iterator it;

		for (int i = 1; i <= 4; ++i)
			mylist1.push_back(i);

		for (int i = 1; i <= 3; ++i)
			mylist2.push_back(i * 10);

		it = mylist1.begin();
		++it;

		mylist1.splice(it, mylist2);

		mylist2.splice(mylist2.begin(), mylist1, it);
		it = mylist1.begin();
		std::advance(it, 3);

		mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
		std::cout << "mylist1 contains:";
		for (it = mylist1.begin(); it != mylist1.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
		std::cout << "myList1 size: " << mylist1.size() << std::endl;

		std::cout << "mylist2 contains:";
		for (it = mylist2.begin(); it != mylist2.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
		std::cout << "myList2 size: " << mylist2.size() << std::endl << std::endl;
	}
	{
		ft::list<int> mylist1, mylist2;
		ft::list<int>::iterator it;

		for (int i = 1; i <= 4; ++i)
			mylist1.push_back(i);

		for (int i = 1; i <= 3; ++i)
			mylist2.push_back(i * 10);

		it = mylist1.begin();
		++it;

		mylist1.splice(it, mylist2);

		mylist2.splice(mylist2.begin(), mylist1, it);
		it = mylist1.begin();
		std::advance(it, 3);

		mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
		std::cout << "mylist1 contains:";
		for (it = mylist1.begin(); it != mylist1.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
		std::cout << "myList1 size: " << mylist1.size() << std::endl;

		std::cout << "mylist2 contains:";
		for (it = mylist2.begin(); it != mylist2.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
		std::cout << "myList2 size: " << mylist2.size() << std::endl << std::endl;
	}

	{
		int myints[] = {17, 89, 7, 14, 89};
		std::list<int> mylist(myints, myints + 4);

		mylist.remove(89);

		std::cout << "mylist contains:";
		for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		int myints[] = {17, 89, 7, 14, 89};
		ft::list<int> mylist(myints, myints + 4);

		mylist.remove(89);

		std::cout << "mylist contains:";
		for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	{
		int myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
		std::list<int> mylist(myints, myints + 8);   // 15 36 7 17 20 39 4 1

		mylist.remove_if(single_digit);           // 15 36 17 20 39

		mylist.remove_if(is_odd());               // 36 20

		std::cout << "mylist contains:";
		for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	{
		int myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
		ft::list<int> mylist(myints, myints + 8);   // 15 36 7 17 20 39 4 1

		mylist.remove_if(single_digit);           // 15 36 17 20 39

		mylist.remove_if(is_odd());               // 36 20

		std::cout << "mylist contains:";
		for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl << std::endl;
	}
	{
		double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
							 12.77, 73.35, 72.25, 15.3,  72.25 };
		std::list<double> mylist (mydoubles,mydoubles+10);

		mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
									// 15.3,  72.25, 72.25, 73.0,  73.35

		mylist.unique();           //  2.72,  3.14, 12.15, 12.77
									// 15.3,  72.25, 73.0,  73.35

		mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
											// 15.3,  72.25, 73.0

		mylist.unique (is_near());           //  2.72, 12.15, 72.25

		std::cout << "mylist contains:";
		for (std::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
							 12.77, 73.35, 72.25, 15.3,  72.25 };
		ft::list<double> mylist (mydoubles,mydoubles+10);

		mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
									// 15.3,  72.25, 72.25, 73.0,  73.35

		mylist.unique();          			 //  2.72,  3.14, 12.15, 12.77
											// 15.3,  72.25, 73.0,  73.35

		mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
											// 15.3,  72.25, 73.0

		mylist.unique (is_near());           //  2.72, 12.15, 72.25

		std::cout << "mylist contains:";
		for (ft::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n' << std::endl;
	}
	{
		std::list<double> first, second;

		first.push_back (3.1);
		first.push_back (2.2);
		first.push_back (2.9);

		second.push_back (3.7);
		second.push_back (7.1);
		second.push_back (1.4);

		first.sort();
		second.sort();

		first.merge(second);

		// (second is now empty)

		second.push_back (2.1);

		first.merge(second,mycomparison);

		std::cout << "first contains: ";
		print_list(first);
	}
	{
		ft::list<double> first, second;

		first.push_back (3.1);
		first.push_back (2.2);
		first.push_back (2.9);

		second.push_back (3.7);
		second.push_back (7.1);
		second.push_back (1.4);

		first.sort();
		second.sort();

		first.merge(second);

		// (second is now empty)

		second.push_back (2.1);

		first.merge(second, mycomparison);

		std::cout << "first contains: ";
		print_list(first);
	}
	{
		std::list<int> mylist;

		for (int i=1; i<10; ++i) mylist.push_back(i);

		mylist.reverse();

		std::cout << "mylist contains: ";
		print_list(mylist);
	}
	{
		ft::list<int> mylist;

		for (int i=1; i<10; ++i) mylist.push_back(i);

		mylist.reverse();

		std::cout << "mylist contains:";
		for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
			std::cout << ' ' << *it;

		std::cout << '\n';
	}
	return 0;
}
