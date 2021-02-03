//
// Created by Fenix Lavon on 1/12/21.
// Copyright (c) 2021 All rights reserved.
//

#include "gtest/gtest.h"
#include "set.hpp"
#include <set>
#include <string>
#include <stdexcept>

template <typename itFt, typename itFtEnd, typename itStd, typename itStdEnd>
void checkSetAreEqualIt(itFt itF, itFtEnd itFe, itStd itS, itStdEnd itSe) {
	for (; itS != itSe; ) {
		EXPECT_EQ(*itS++, *itF++);
	}
	EXPECT_EQ(itF, itFe);
}

template <class T>
void	checkIfSetAreEqual(ft::set<T> & f, std::set<T> & s, int i = 0) {
	EXPECT_EQ(f.size(), s.size()) << "i = " << i;
	EXPECT_EQ(f.empty(), s.empty()) << "i = " << i;

	typename  ft::set<T>::iterator itf = f.begin();
	typename  ft::set<T>::iterator itfe = f.end();
	typename std::set<T>::iterator its = s.begin();
	typename std::set<T>::iterator itse = s.end();

	for (; its != itse; ) {
		EXPECT_EQ(*its++, *itf++)  << "i = " << i;
	}
	EXPECT_EQ(itf, itfe)  << "i = " << i;
}

template <typename ftIter, typename stdIter, typename ftIterTmp, typename stdIterTmp>
void	setIteratorTest(ftIter & fIt, ftIter & fIte, ftIterTmp & ftmpIt,
						stdIter & sIt, stdIter & sIte, stdIterTmp & stmpIt) {
	ftmpIt = fIt;
	stmpIt = sIt;
	EXPECT_EQ(ftmpIt, fIt) << "Assignation or operator== fails.";
	EXPECT_EQ(stmpIt, sIt);

	ASSERT_EQ(*fIt, *sIt) << "Dereference fails.";

	++fIt;
	++sIt;
	EXPECT_EQ(*fIt, *sIt) << "++operator fails.";

	EXPECT_NE(fIt, ftmpIt) << "operator!= fails.";
	EXPECT_NE(sIt, stmpIt);

	--fIt;
	--sIt;
	EXPECT_EQ(*fIt, *sIt) << "--operator fails.";

	ftmpIt = fIt++;
	stmpIt = sIt++;
	EXPECT_EQ(*fIt, *sIt) << "operator++ fails.";
	EXPECT_EQ(*stmpIt, *ftmpIt) << "operator++ fails.";

	checkSetAreEqualIt(fIt, fIte, sIt, sIte);
}

class SetInsertSimpleTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			s.insert(std::to_string(i));
			f.insert(std::to_string(i));
		}
	}

	std::set<std::string> s;
	ft::set<std::string> f;

	std::set<std::string>::iterator it;
};

TEST_F(SetInsertSimpleTest, case1) {
	EXPECT_EQ(s.size(), f.size());
	EXPECT_EQ(s.empty(), f.empty());
}

TEST_F(SetInsertSimpleTest, case2) {
	s.insert("a");
	f.insert("a");

	EXPECT_EQ(s.size(), f.size());
	EXPECT_EQ(s.empty(), f.empty());
}

TEST_F(SetInsertSimpleTest, case3) {
	size_t ssize = s.size();
	size_t fsize = f.size();

	s.insert("1");
	f.insert("1");

	EXPECT_EQ(s.size(), ssize);
	EXPECT_EQ(f.size(), fsize);
	EXPECT_EQ(s.size(), f.size());
	EXPECT_EQ(s.empty(), f.empty());
}

TEST_F(SetInsertSimpleTest, case4) {
	std::set<std::string> s1;
	ft::set<std::string> f1;
	EXPECT_EQ(s1.size(), f1.size());
	EXPECT_EQ(s1.empty(), f1.empty());
}

class SetIteratorTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 11; ++i) {
			s.insert(std::to_string(i));
			f.insert(std::to_string(i));
		}
	}

	std::set<std::string> s;
	ft::set<std::string> f;
};

TEST_F(SetIteratorTest, IteratorInputInputTest) {
	ft::set<std::string>::iterator itf =	f.begin();
	ft::set<std::string>::iterator itfe =	f.end();
	ft::set<std::string>::iterator tmpf;

	std::set<std::string>::iterator its =	s.begin();
	std::set<std::string>::iterator itse =	s.end();
	std::set<std::string>::iterator tmps;

	setIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(SetIteratorTest, IteratorInputConstInputTest) {
	ft::set<std::string>::iterator itf =	f.begin();
	ft::set<std::string>::iterator itfe =	f.end();
	ft::set<std::string>::const_iterator tmpf;

	std::set<std::string>::iterator its =	s.begin();
	std::set<std::string>::iterator itse =	s.end();
	std::set<std::string>::const_iterator tmps;

	setIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(SetIteratorTest, IteratorConstInputConstInputTest) {
	ft::set<std::string>::const_iterator itf =		f.begin();
	ft::set<std::string>::const_iterator itfe =	f.end();
	ft::set<std::string>::const_iterator tmpf;

	std::set<std::string>::const_iterator its =	s.begin();
	std::set<std::string>::const_iterator itse =	s.end();
	std::set<std::string>::const_iterator tmps;

	setIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(SetIteratorTest, IteratorReverseReverseTest) {
	ft::set<std::string>::reverse_iterator itf =		f.rbegin();
	ft::set<std::string>::reverse_iterator itfe =	f.rend();
	ft::set<std::string>::reverse_iterator tmpf;

	std::set<std::string>::reverse_iterator its =	s.rbegin();
	std::set<std::string>::reverse_iterator itse =	s.rend();
	std::set<std::string>::reverse_iterator tmps;

	setIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(SetIteratorTest, IteratorReverseConstReverseTest) {
	ft::set<std::string>::reverse_iterator itf =		f.rbegin();
	ft::set<std::string>::reverse_iterator itfe =	f.rend();
	ft::set<std::string>::const_reverse_iterator tmpf;

	std::set<std::string>::reverse_iterator its =	s.rbegin();
	std::set<std::string>::reverse_iterator itse =	s.rend();
	std::set<std::string>::const_reverse_iterator tmps;

	setIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}

TEST_F(SetIteratorTest, IteratorConstReverseConstReverseTest) {
	ft::set<std::string>::const_reverse_iterator itf =		f.rbegin();
	ft::set<std::string>::const_reverse_iterator itfe =	f.rend();
	ft::set<std::string>::const_reverse_iterator tmpf;

	std::set<std::string>::const_reverse_iterator its =	s.rbegin();
	std::set<std::string>::const_reverse_iterator itse =	s.rend();
	std::set<std::string>::const_reverse_iterator tmps;

	setIteratorTest(itf, itfe, tmpf, its, itse, tmps);
}


class SetInsertTest : public testing::Test {
protected:
	virtual void SetUp() {
		itf =	f.begin();
		itfe =	f.end();

		its =	s.begin();
		itse =	s.end();
	}
	std::pair<ft::set<std::string>::iterator, bool> pf;
	std::pair<std::set<std::string>::iterator, bool> ps;

	ft::set<std::string> f;
	std::set<std::string> s;

	ft::set<std::string>::iterator itf;
	std::set<std::string>::iterator its;
	ft::set<std::string>::iterator itfe;
	std::set<std::string>::iterator itse;
};

TEST_F(SetInsertTest, insertValCaseSingle) {
	pf = f.insert("a");
	ps = s.insert("a");

	EXPECT_EQ(pf.second, ps.second);

	checkSetAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, insertValCaseOverride) {
	pf = f.insert("a");
	pf = f.insert("a");
	ps = s.insert("a");
	ps = s.insert("a");

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, f.begin());
	EXPECT_EQ(ps.first, s.begin());

	checkSetAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, insertValCaseDouble1) {
	pf = f.insert("a");
	ps = s.insert("a");

	pf = f.insert("a");
	ps = s.insert("a");

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, --f.end());
	EXPECT_EQ(ps.first, --s.end());

	checkSetAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, insertValCaseDouble2) {
	pf = f.insert("b");
	ps = s.insert("b");

	pf = f.insert("b");
	ps = s.insert("b");

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, f.begin());
	EXPECT_EQ(ps.first, s.begin());

	checkSetAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, insertValCaseTriple1) {
	pf = f.insert("b");
	ps = s.insert("b");

	pf = f.insert("a");
	ps = s.insert("a");

	pf = f.insert("c");
	ps = s.insert("c");

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, --f.end());
	EXPECT_EQ(ps.first, --s.end());

	checkSetAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, insertValCaseTriple2) {
	pf = f.insert("b");
	ps = s.insert("b");

	pf = f.insert("c");
	ps = s.insert("c");

	pf = f.insert("a");
	ps = s.insert("a");

	EXPECT_EQ(pf.second, ps.second);
	EXPECT_EQ(pf.first, f.begin());
	EXPECT_EQ(ps.first, s.begin());

	checkSetAreEqualIt(pf.first, f.end(), ps.first, s.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, ultimative) {
	srand(1);
	int gen_key;
	const int keys_limit = 500;

	for (int i = 0; i < keys_limit * 2; ++i) {
		gen_key = rand() % keys_limit;
		ps = s.insert(std::to_string(gen_key));
		pf = f.insert(std::to_string(gen_key));

		EXPECT_EQ(pf.second, ps.second);

		checkSetAreEqualIt(pf.first, f.end(), ps.first, s.end());
		checkIfSetAreEqual(f, s);
	}
}

TEST_F(SetInsertTest, insertPosVal1) {
	itf = f.insert(f.begin(), "123");
	its = s.insert(s.begin(), "123");

	checkSetAreEqualIt(itf, f.end(), its, s.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, insertPosVal2) {
	const int times = 100;

	for (int i = 0; i < times; ++i) {
		its = s.insert(s.begin(),std::to_string(i + 10));
		itf = f.insert(f.begin(),std::to_string(i + 10));

		checkSetAreEqualIt(itf, f.end(), its, s.end());
		checkIfSetAreEqual(f, s);
	}
}

TEST_F(SetInsertTest, insertRangeSameMap) {
	const int times = 100;

	for (int i = 0; i < times; ++i) {
		its = s.insert(s.begin(),std::to_string(i + 10));
		itf = f.insert(f.begin(), std::to_string(i + 10));
	}

	s.insert(s.begin(), s.end());
	f.insert(f.begin(), f.end());

	checkIfSetAreEqual(f, s);
}

TEST_F(SetInsertTest, insertAnotherRange) {
	const int times = 100;
	std::set<std::string> sample;

	for (int i = 0; i < times; ++i) {
		sample.insert(std::to_string(i + 10));
	}

	its = sample.begin();
	std::advance(its, 30);

	s.insert(its, sample.end());
	f.insert(its, sample.end());

	checkIfSetAreEqual(f, s);
}
