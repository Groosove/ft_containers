//
// ft_containers
//
// Created by Артур Лутфуллин on 03.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "gtest/gtest.h"
#include "deque.hpp"
#include <deque>

template <class T>
void	checkIfVectorsAreEqual(ft::deque<T> & f, std::deque<T> & s) {
	EXPECT_EQ(f.size(), s.size());
	EXPECT_EQ(f.empty(), s.empty());

	typename  ft::deque<T>::iterator itF = f.begin();
	typename  ft::deque<T>::iterator itFe = f.end();
	typename std::deque<T>::iterator itS = s.begin();
	typename std::deque<T>::iterator itSe = s.end();

	for (; itS != itSe; ) {
		EXPECT_EQ(*itS++, *itF++);
	}
	EXPECT_EQ(itF, itFe);
}

class DequeConstructorTest : public ::testing::Test {
protected:
	virtual void SetUp() { }
};

TEST_F(DequeConstructorTest, defaultConstructor) {
	ft::deque<int> f;
	std::deque<int> s;
	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeConstructorTest, valueConstructor1) {
	ft::deque<int> f(60);
	std::deque<int> s(60);
	checkIfVectorsAreEqual(f, s);
	ft::deque<std::string> f1(60);
	std::deque<std::string> s1(60);
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(DequeConstructorTest, valueConstructor2) {
	ft::deque<int> f(60,5);
	std::deque<int> s(60, 5);
	checkIfVectorsAreEqual(f, s);
	ft::deque<std::string> f1(60, "Hello World!");
	std::deque<std::string> s1(60, "Hello World!");
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(DequeConstructorTest, rangeConstructor) {
	std::deque<int> sample;
	sample.push_back(54);
	sample.push_back(42);
	sample.push_back(21);
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());
	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeConstructorTest, copyConstructor) {
	ft::deque<std::string> f1(60, "Hello World!");
	std::deque<std::string> s1(60, "Hello World!");
	ft::deque<std::string> f2(f1);
	std::deque<std::string> s2(s1);
	checkIfVectorsAreEqual(f2, s2);
	ft::deque<std::string> f3 = f2;
	std::deque<std::string> s3 = s2;
	checkIfVectorsAreEqual(f3, s3);
}

template <typename itFt, typename itFtEnd, typename itStd, typename itStdEnd>
void checkVectorsAreEqualIt(itFt itF, itFtEnd itFe, itStd itS, itStdEnd itSe) {
	for (; itS != itSe; ) {
		EXPECT_EQ(*itS++, *itF++);
	}
	EXPECT_EQ(itF, itFe);
};

template <typename ftIter, typename stdIter, typename ftIterTmp, typename stdIterTmp>
void	vectorIteratorTest(ftIter & fIt, ftIter & fIte, ftIterTmp & ftmpIt,
						   stdIter & sIt, stdIter & sIte, stdIterTmp & stmpIt)
{
	ftmpIt = fIt;
	stmpIt = sIt;
	EXPECT_EQ(ftmpIt, fIt) << "Assignation or operator== fails.";
	EXPECT_EQ(stmpIt, sIt);
	EXPECT_GE(fIt, ftmpIt) << "operator>= fails.";
	EXPECT_GE(sIt, stmpIt);
	EXPECT_LE(ftmpIt, fIt) << "operator<= fails.";
	EXPECT_LE(stmpIt, sIt);

	ASSERT_EQ(*fIt, *sIt) << "Dereference fails.";

	++fIt;
	++sIt;
	EXPECT_EQ(*fIt, *sIt) << "++operator fails.";

	EXPECT_NE(fIt, ftmpIt) << "operator!= fails.";
	EXPECT_NE(sIt, stmpIt);
	EXPECT_GT(fIt, ftmpIt) << "operator> fails.";
	EXPECT_GT(sIt, stmpIt);
	EXPECT_GE(fIt, ftmpIt) << "operator>= fails.";
	EXPECT_GE(sIt, stmpIt);
	EXPECT_LT(ftmpIt, fIt) << "operator< fails.";
	EXPECT_LT(stmpIt, sIt);
	EXPECT_LE(ftmpIt, fIt) << "operator<= fails.";
	EXPECT_LE(stmpIt, sIt);

	--fIt;
	--sIt;
	EXPECT_EQ(*fIt, *sIt) << "--operator fails.";

	EXPECT_EQ(fIt[3], sIt[3]) << "operator[] fails.";
	EXPECT_EQ(*(fIt + 3), *(sIt + 3)) << "operator+ fails.";
	EXPECT_EQ(sIt[3], *(sIt + 3)) << "operator+ or operator[] fails.";
	EXPECT_EQ(fIt[3], *(fIt + 3)) << "operator+ or operator[] fails.";

	ftmpIt = fIt++;
	stmpIt = sIt++;
	EXPECT_EQ(*fIt, *sIt) << "operator++ fails.";
	EXPECT_EQ(*stmpIt, *ftmpIt) << "operator++ fails.";

	ftmpIt = fIt--;
	stmpIt = sIt--;
	EXPECT_EQ(*fIt, *sIt) << "operator-- fails.";
	EXPECT_EQ(*stmpIt, *ftmpIt) << "operator-- fails.";

	fIt += 4;
	sIt += 4;
	EXPECT_EQ(*fIt, *sIt) << "operator+= fails.";

	EXPECT_EQ(fIt[-3], sIt[-3]) << "operator[] fails.";
	EXPECT_EQ(*(fIt - 3), *(sIt - 3)) << "operator- fails.";
	EXPECT_EQ(sIt[-3], *(sIt - 3)) << "operator- or operator[] fails.";
	EXPECT_EQ(fIt[-3], *(fIt - 3)) << "operator- or operator[] fails.";

	fIt -= 4;
	sIt -= 4;
	EXPECT_EQ(*fIt, *sIt) << "operator-= fails.";

	checkVectorsAreEqualIt(fIt, fIte, sIt, sIte);
}

class DequeIteratorTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		sample.push_back(54);
		sample.push_back(42);
		sample.push_back(21);
		sample.push_back(12);
		sample.push_back(99);
		sample.push_back(66);

	}
	std::deque<int> sample;
};

TEST_F(DequeIteratorTest, IteratorInputInputTest) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	ft::deque<int>::iterator itf =		f.begin();
	ft::deque<int>::iterator itfe =	f.end();
	ft::deque<int>::iterator tmpf;

	std::deque<int>::iterator its =	s.begin();
	std::deque<int>::iterator itse =	s.end();
	std::deque<int>::iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(DequeIteratorTest, IteratorInputConstInputTest) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	ft::deque<int>::iterator itf =		f.begin();
	ft::deque<int>::iterator itfe =	f.end();
	ft::deque<int>::const_iterator tmpf;

	std::deque<int>::iterator its =	s.begin();
	std::deque<int>::iterator itse =	s.end();
	std::deque<int>::const_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(DequeIteratorTest, IteratorConstInputConstInputTest) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	ft::deque<int>::const_iterator itf = f.begin();
	ft::deque<int>::const_iterator itfe =	f.end();
	ft::deque<int>::const_iterator tmpf;

	std::deque<int>::const_iterator its =	s.begin();
	std::deque<int>::const_iterator itse =	s.end();
	std::deque<int>::const_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(DequeIteratorTest, IteratorReverseReverseTest) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	ft::deque<int>::reverse_iterator itf =		f.rbegin();
	ft::deque<int>::reverse_iterator itfe =	f.rend();
	ft::deque<int>::reverse_iterator tmpf;

	std::deque<int>::reverse_iterator its =	s.rbegin();
	std::deque<int>::reverse_iterator itse =	s.rend();
	std::deque<int>::reverse_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(DequeIteratorTest, IteratorReverseConstReverseTest) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	ft::deque<int>::reverse_iterator itf =		f.rbegin();
	ft::deque<int>::reverse_iterator itfe =	f.rend();
	ft::deque<int>::const_reverse_iterator tmpf;

	std::deque<int>::reverse_iterator its =	s.rbegin();
	std::deque<int>::reverse_iterator itse =	s.rend();
	std::deque<int>::const_reverse_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(DequeIteratorTest, IteratorConstReverseConstReverseTest) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	ft::deque<int>::const_reverse_iterator itf =		f.rbegin();
	ft::deque<int>::const_reverse_iterator itfe =	f.rend();
	ft::deque<int>::const_reverse_iterator tmpf;

	std::deque<int>::const_reverse_iterator its =	s.rbegin();
	std::deque<int>::const_reverse_iterator itse =	s.rend();
	std::deque<int>::const_reverse_iterator tmps;

	vectorIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

class DequeClearTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
};

TEST_F(DequeClearTest, capacityRemainsTheSame) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	s.clear();
	f.clear();

	EXPECT_EQ(0, f.size());
	EXPECT_EQ(0, s.size());
}

class DequeAssignationTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		sample.push_back(54);
		sample.push_back(42);
		sample.push_back(21);
		sample.push_back(12);
		sample.push_back(99);
		sample.push_back(66);
	}
	std::vector<int> sample;
};

TEST_F(DequeAssignationTest, emptyAssign) {
	std::deque<int> s;
	std::deque<int> s1;
	ft::deque<int> f;
	ft::deque<int> f1;

	s = s1;
	f = f1;
	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeAssignationTest, nonEmptyAssign) {
	std::deque<int> s(sample.begin(), sample.end());
	std::deque<int> s1;
	ft::deque<int> f(sample.begin(), sample.end());
	ft::deque<int> f1;

	s = s1;
	f = f1;
	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeAssignationTest, nonEmptyAssignCapacityCheck) {
	std::deque<int> s(sample.begin(), sample.end());
	std::deque<int> s1;
	ft::deque<int> f(sample.begin(), sample.end());
	ft::deque<int> f1;

	s1 = s;
	f1 = f;
	checkIfVectorsAreEqual(f, s);
}


class DequeAccessTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::vector<int> sample;
};

TEST_F(DequeAccessTest, operatorBrackets) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(f[i], s[i]) << "operator[] fails on " << i << " iteration";
	}
}

TEST_F(DequeAccessTest, at) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());
	int nouse = 0;

	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(f.at(i), s.at(i)) << "at() fails on " << i << " iteration";
	}
	EXPECT_THROW(nouse += s.at(10), std::out_of_range) << "at() does not throw std::out_of_range";
	EXPECT_THROW(nouse += f.at(10), std::out_of_range) << "at() does not throw std::out_of_range";
}

TEST_F(DequeAccessTest, frontBack) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	EXPECT_EQ(s.front(), f.front());
	EXPECT_EQ(s.back(), f.back());
}

class DequeInsertIntTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
	ft::deque<int>::iterator itf;
	ft::deque<int>::iterator itfe;
	ft::deque<int>::iterator itfret;
	std::deque<int>::iterator its;
	std::deque<int>::iterator itse;
	std::deque<int>::iterator itsret;
};

TEST_F(DequeInsertIntTest, insertIntInPosition1) { // insert into begin with reallocation
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itfret = f.insert(f.begin(), 42);
	itsret = s.insert(s.begin(), 42);

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeInsertIntTest, insertIntInPosition3) { // insert into mid with reallocation
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itfret = f.insert(++++f.begin(), 42);
	itsret = s.insert(++++s.begin(), 42);
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeInsertIntTest, insertIntInPosition5) { // insert into end with reallocation
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

//	itf = --f.end(); itfe = f.end();
//	its = --s.end(); itse = s.end();

	itfret = f.insert(f.end(), 42);
	itsret = s.insert(s.end(), 42);
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeInsertIntTest, insertIntRangeN4) {	// insert into begin without reallocation, greater then size
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	f.insert(f.begin(), 15, 42);
	s.insert(s.begin(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertIntTest, insertIntRangeN11) {	// insert into end with reallocation, greater then size
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	f.insert(f.end(), 15, 42);
	s.insert(s.end(), 15,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertIntTest, insertIntRangeNMultiReallocation) {
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	f.insert(f.end(), 15000, 42);
	s.insert(s.end(), 15000,42);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertIntTest, insertIntIterator1) {	// insert into begin with reallocation, less then size
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	f.insert(f.begin(), sample.begin(), ++++++sample.begin());
	s.insert(s.begin(), sample.begin(), ++++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}


TEST_F(DequeInsertIntTest, insertIntIterator5) {	// insert into mid with reallocation, less then size
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	f.insert(++++f.begin(), sample.begin(), ++++sample.begin());
	s.insert(++++s.begin(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}


TEST_F(DequeInsertIntTest, insertIntIterator9) {	// insert into end with reallocation, less then size
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

class DequeInsertStrTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(std::to_string(i));
		}
	}
	std::deque<std::string> sample;
	ft::deque<std::string>::iterator itf;
	ft::deque<std::string>::iterator itfe;
	ft::deque<std::string>::iterator itfret;
	std::deque<std::string>::iterator its;
	std::deque<std::string>::iterator itse;
	std::deque<std::string>::iterator itsret;
};

TEST_F(DequeInsertStrTest, insertIntInPosition1) { // insert into begin with reallocation
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	itfret = f.insert(f.begin(), std::to_string(42));
	itsret = s.insert(s.begin(), std::to_string(42));

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}


TEST_F(DequeInsertStrTest, insertIntInPosition3) { // insert into mid with reallocation
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

//	itf = f.begin(); itfe = f.end();
//	its = s.begin(); itse = s.end();

	itfret = f.insert(++++f.begin(), std::to_string(42));
	itsret = s.insert(++++s.begin(), std::to_string(42));
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}


TEST_F(DequeInsertStrTest, insertIntInPosition5) { // insert into end with reallocation
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

//	itf = --f.end(); itfe = f.end();
//	its = --s.end(); itse = s.end();

	itfret = f.insert(f.end(), std::to_string(42));
	itsret = s.insert(s.end(), std::to_string(42));
	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeInsertStrTest, insertIntRangeN3) {	// insert into begin with reallocation, greater then size
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	f.insert(f.begin(), 15, std::to_string(42));
	s.insert(s.begin(), 15,std::to_string(42));

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertStrTest, insertIntRangeN7) {	// insert into mid n with reallocation, greater then size
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	f.insert(++++f.begin(), 15, std::to_string(42));
	s.insert(++++s.begin(), 15,std::to_string(42));

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertStrTest, insertIntRangeN11) {	// insert into end with reallocation, greater then size
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	f.insert(f.end(), 15, std::to_string(42));
	s.insert(s.end(), 15,std::to_string(42));

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertStrTest, insertIntRangeNMultiReallocation) {
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	f.insert(f.end(), 15000, std::to_string(42));
	s.insert(s.end(), 15000,std::to_string(42));

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertStrTest, insertIntIterator1) {	// insert into begin with reallocation, less then size
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	f.insert(f.begin(), sample.begin(), ++++++sample.begin());
	s.insert(s.begin(), sample.begin(), ++++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertStrTest, insertIntIterator5) {	// insert into mid with reallocation, less then size
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	f.insert(++++f.begin(), sample.begin(), ++++sample.begin());
	s.insert(++++s.begin(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequeInsertStrTest, insertIntIterator9) {	// insert into end with reallocation, less then size
	ft::deque<std::string> f(sample.begin(), sample.end());
	std::deque<std::string> s(sample.begin(), sample.end());

	f.insert(f.end(), sample.begin(), ++++sample.begin());
	s.insert(s.end(), sample.begin(), ++++sample.begin());

	checkIfVectorsAreEqual(f, s);
}

class DequeEraseTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
	ft::deque<int>::iterator itf;
	ft::deque<int>::iterator itfe;
	ft::deque<int>::iterator itfret;
	std::deque<int>::iterator its;
	std::deque<int>::iterator itse;
	std::deque<int>::iterator itsret;
};

TEST_F(DequeEraseTest, erasePos1) {		// erase from begin
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itfret = f.erase(f.begin());
	itsret = s.erase(s.begin());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeEraseTest, erasePos2) {		// erase from mid
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(----f.end());
	itsret = s.erase(----s.end());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeEraseTest, erasePos3) {		// erase from end
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(--f.end());
	itsret = s.erase(--s.end());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeEraseTest, eraseIterator1) { // erase from begin
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itfret = f.erase(f.begin(), ----f.end());
	itsret = s.erase(s.begin(), ----s.end());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeEraseTest, eraseIterator2) { // erase from begin full
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itfret = f.erase(f.begin(), f.end());
	itsret = s.erase(s.begin(), s.end());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeEraseTest, eraseIterator3) { // erase from mid
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(++++++f.begin(), ----f.end());
	itsret = s.erase(++++++s.begin(), ----s.end());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeEraseTest, eraseIterator4) { // erase from mid till end
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());

	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(++++++f.begin(), f.end());
	itsret = s.erase(++++++s.begin(), s.end());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

TEST_F(DequeEraseTest, eraseIterator5) { // erase end, noting should happen
	ft::deque<int> f(sample.begin(), sample.end());
	std::deque<int> s(sample.begin(), sample.end());


	itf = ++++f.begin();
	its = ++++s.begin();

	itfret = f.erase(f.end(), f.end());
	itsret = s.erase(s.end(), s.end());

	checkIfVectorsAreEqual(f, s);
	checkVectorsAreEqualIt(itf, f.end(), its, s.end());
	checkVectorsAreEqualIt(itfret, f.end(), itsret, s.end());
}

class DequePushBackTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
	ft::deque<int>::iterator itf;
	ft::deque<int>::iterator itfe;
	ft::deque<int>::iterator itfret;
	std::deque<int>::iterator its;
	std::deque<int>::iterator itse;
	std::deque<int>::iterator itsret;
};

TEST_F(DequePushBackTest, toEmpty) { // to empty with reallocation
	std::deque<int> es;
	ft::deque<int> ef;

	es.push_back(42);
	ef.push_back(42);

	checkIfVectorsAreEqual(ef, es);
}


TEST_F(DequePushBackTest, withRealloc) { // to empty with reallocation
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	s.push_back(42);
	f.push_back(42);

	checkIfVectorsAreEqual(f, s);
}

class DequePopBackTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
	ft::deque<int>::iterator itf;
	ft::deque<int>::iterator itfe;
	ft::deque<int>::iterator itfret;
	std::deque<int>::iterator its;
	std::deque<int>::iterator itse;
	std::deque<int>::iterator itsret;
};

TEST_F(DequePopBackTest, single) {
	std::deque<int> s(sample.begin(), ++sample.begin());
	ft::deque<int> f(sample.begin(), ++sample.begin());

	s.pop_back();
	f.pop_back();

	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(f.size(), 0);
	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequePopBackTest, simple) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	s.pop_back();
	f.pop_back();

	EXPECT_EQ(s.size(), 9);
	EXPECT_EQ(f.size(), 9);
	checkIfVectorsAreEqual(f, s);
}

class DequePushFrontTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
	ft::deque<int>::iterator itf;
	ft::deque<int>::iterator itfe;
	ft::deque<int>::iterator itfret;
	std::deque<int>::iterator its;
	std::deque<int>::iterator itse;
	std::deque<int>::iterator itsret;
};

TEST_F(DequePushFrontTest, toEmpty) { // to empty with reallocation
	std::deque<int> es;
	ft::deque<int> ef;

	es.push_front(42);
	ef.push_front(42);

	checkIfVectorsAreEqual(ef, es);
}


TEST_F(DequePushFrontTest, withRealloc) { // to empty with reallocation
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	s.push_front(42);
	f.push_front(42);

	checkIfVectorsAreEqual(f, s);
}

class DequePopFrontTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
	ft::deque<int>::iterator itf;
	ft::deque<int>::iterator itfe;
	ft::deque<int>::iterator itfret;
	std::deque<int>::iterator its;
	std::deque<int>::iterator itse;
	std::deque<int>::iterator itsret;
};

TEST_F(DequePopFrontTest, single) {
	std::deque<int> s(sample.begin(), ++sample.begin());
	ft::deque<int> f(sample.begin(), ++sample.begin());

	s.pop_front();
	f.pop_front();

	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(f.size(), 0);
	checkIfVectorsAreEqual(f, s);
}

TEST_F(DequePopFrontTest, simple) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	s.pop_front();
	f.pop_front();

	EXPECT_EQ(s.size(), 9);
	EXPECT_EQ(f.size(), 9);
	checkIfVectorsAreEqual(f, s);
}

class DequeAssignTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			sample.push_back(i);
		}
	}
	std::deque<int> sample;
	ft::deque<int>::iterator itf;
	ft::deque<int>::iterator itfe;
	ft::deque<int>::iterator itfret;
	std::deque<int>::iterator its;
	std::deque<int>::iterator itse;
	std::deque<int>::iterator itsret;
};

TEST_F(DequeAssignTest, toEmpty) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	std::deque<int> s1;
	ft::deque<int> f1;

	s1.assign(s.begin(), s.end());
	f1.assign(f.begin(), f.end());
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(DequeAssignTest, toNotEmpty) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	std::deque<int> s1(s);
	ft::deque<int> f1(f);

	s1.assign(++++s.begin(), --s.end());
	f1.assign(++++f.begin(), --f.end());
	checkIfVectorsAreEqual(f1, s1);
}

TEST_F(DequeAssignTest, toNotEmptyN) {
	std::deque<int> s(sample.begin(), sample.end());
	ft::deque<int> f(sample.begin(), sample.end());

	std::deque<int> s1(s);
	ft::deque<int> f1(f);

	s1.assign(42, 42);
	f1.assign(42, 42);
	checkIfVectorsAreEqual(f1, s1);
}

class DequeSwapTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s1.push_back(std::to_string(i));
			f1.push_back(std::to_string(i));
		}
	}

	std::deque<std::string> s2, s1;
	ft::deque<std::string>  f2, f1;
};

TEST_F(DequeSwapTest, integrityFullEmpty) {
	s1.swap(s2);
	f1.swap(f2);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
}

TEST_F(DequeSwapTest, integrityEmptyFull) {
	s2.swap(s1);
	f2.swap(f1);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
}

TEST_F(DequeSwapTest, integrityFullFull) {
	s2.push_back("std::to_string(i)");
	f2.push_back("std::to_string(i)");

	s2.swap(s1);
	f2.swap(f1);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
}

TEST_F(DequeSwapTest, iteratorValidity) {
	std::deque<std::string>::iterator its = ++s1.begin();
	ft::deque<std::string>::iterator itf = ++f1.begin();

	s2.push_back("std::to_string(i)");
	f2.push_back("std::to_string(i)");

	s2.swap(s1);
	f2.swap(f1);

	checkIfVectorsAreEqual(f1, s1);
	checkIfVectorsAreEqual(f2, s2);
	checkVectorsAreEqualIt(itf, f2.end(), its, s2.end());
}

class DequeComprasionTest : public ::testing::Test {
protected:
	virtual void SetUp() {

	}
	std::deque<std::string> s1, s2;
	ft::deque<std::string> f1, f2;
};

TEST_F(DequeComprasionTest, equalSimple) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");
	s1.push_back("d"); f1.push_back("d");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("c"); f2.push_back("c");
	s2.push_back("d"); f2.push_back("d");

	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
}

TEST_F(DequeComprasionTest, equalSingleElem) {
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("a"); f2.push_back("a");

	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
}

TEST_F(DequeComprasionTest, equalEmpty) {
	ft::deque<int> sample;
	ft::deque<int> sample2;
	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
}

TEST_F(DequeComprasionTest, lessSizeLess) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("c"); f2.push_back("c");
	s2.push_back("d"); f2.push_back("d");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(DequeComprasionTest, lessOneElem) {
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("d"); f2.push_back("d");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(DequeComprasionTest, lessCase1) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("cc"); f2.push_back("cc");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(DequeComprasionTest, lessCase2) {
	s1.push_back("a1"); f1.push_back("a1");
	s1.push_back("b"); f1.push_back("b");
	s1.push_back("c"); f1.push_back("c");

	s2.push_back("a9"); f2.push_back("a9");
	s2.push_back("b"); f2.push_back("b");
	s2.push_back("c"); f2.push_back("c");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(DequeComprasionTest, justCase1) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(DequeComprasionTest, justCase2) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");
	s2.push_back("a"); f2.push_back("a");

	EXPECT_EQ(false, s1 < s2);
	EXPECT_EQ(false, f1 < f2);
	EXPECT_EQ(true, s1 == s2);
	EXPECT_EQ(true, f1 == f2);
}

TEST_F(DequeComprasionTest, justCase3) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("z"); f2.push_back("z");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(DequeComprasionTest, justCase4) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
}

TEST_F(DequeComprasionTest, justCase5) {
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");
	s1.push_back("a"); f1.push_back("a");

	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");
	s2.push_back("z"); f2.push_back("z");

	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(false, s1 == s2);
	EXPECT_EQ(false, f1 == f2);
	EXPECT_EQ(false, s1 > s2);
	EXPECT_EQ(false, f1 > f2);
	EXPECT_EQ(false, s1 >= s2);
	EXPECT_EQ(false, f1 >= f2);
	EXPECT_EQ(true, s1 < s2);
	EXPECT_EQ(true, f1 < f2);
	EXPECT_EQ(true, s1 <= s2);
	EXPECT_EQ(true, f1 <= f2);
}