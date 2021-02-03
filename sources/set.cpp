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

class SetConstructionRange : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			sample.insert(std::to_string(i + 142));
		}
	}
	std::pair<ft::set<std::string>::iterator, bool> pf;
	std::pair<std::set<std::string>::iterator, bool> ps;

	ft::set<std::string>::iterator itf;
	std::set<std::string>::iterator its;
	ft::set<std::string>::iterator itfe;
	std::set<std::string>::iterator itse;

	std::set<std::string> sample;
};

TEST_F(SetConstructionRange, emptyRange) {
	ft::set<std::string> f(sample.begin(), sample.begin());
	std::set<std::string> s(sample.begin(), sample.begin());

	checkIfSetAreEqual(f, s);
}

TEST_F(SetConstructionRange, oneRange) {
	ft::set<std::string> f(sample.begin(), ++sample.begin());
	std::set<std::string> s(sample.begin(), ++sample.begin());

	checkIfSetAreEqual(f, s);
}

TEST_F(SetConstructionRange, oneHundredRange) {
	ft::set<std::string> f(sample.begin(), sample.end());
	std::set<std::string> s(sample.begin(), sample.end());

	checkIfSetAreEqual(f, s);
}

class SetFindTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s.insert(std::to_string(i - 50));
			f.insert(std::to_string(i - 50));
		}
	}

	std::set<std::string> s;
	ft::set<std::string> f;

	std::set<std::string>::iterator its;
	ft::set<std::string>::iterator itf;
	std::set<std::string>::iterator itse;
	ft::set<std::string>::iterator itfe;

	std::set<std::string>::const_iterator cits;
	ft::set<std::string>::const_iterator citf;
	std::set<std::string>::const_iterator citse;
	ft::set<std::string>::const_iterator citfe;
};

TEST_F(SetFindTest, notContain) {
	its = s.find("a");
	itf = f.find("a");

	EXPECT_EQ(its, s.end());
	EXPECT_EQ(itf, f.end());
}

TEST_F(SetFindTest, notContainEmpty) {
	std::set<std::string> sEmpty;
	ft::set<std::string> fEmpty;

	its = sEmpty.find("a");
	itf = fEmpty.find("a");

	EXPECT_EQ(its, sEmpty.end());
	EXPECT_EQ(itf, fEmpty.end());
	EXPECT_EQ(its, sEmpty.begin());
	EXPECT_EQ(itf, fEmpty.begin());
}

TEST_F(SetFindTest, findEach) {
	for (int i = -5; i < 105; ++i) {
		its = s.find(std::to_string(i - 50));
		itf = f.find(std::to_string(i - 50));

		checkSetAreEqualIt(itf, f.end(), its, s.end());
	}
}

TEST_F(SetFindTest, findEachConst) {
	for (int i = -5; i < 105; ++i) {
		cits = s.find(std::to_string(i - 50));
		citf = f.find(std::to_string(i - 50));

		checkSetAreEqualIt(citf, f.end(), cits, s.end());
	}
}

TEST_F(SetFindTest, count) {
	size_t cf;
	size_t cs;

	cf = f.count("1");
	cs = s.count("1");

	EXPECT_EQ(cs, cf);
	EXPECT_EQ(cs, 1);
	EXPECT_EQ(cf, 1);

	cf = f.count("a");
	cs = s.count("a");

	EXPECT_EQ(cs, cf);
	EXPECT_EQ(cs, 0);
	EXPECT_EQ(cf, 0);
}

class SetBoundTest : public testing::Test {
protected:
	virtual void SetUp() {
		step_iter = 0;
		for (int i = 0; i < 10; ++i) {
			s.insert(std::to_string(step_iter));
			f.insert(std::to_string(step_iter));
			step_iter += step / 2;
		}
	}

	const double step = 1.;
	double		 step_iter;

	std::set<std::string> s;
	ft::set<std::string> f;

	std::set<std::string>::iterator its;
	ft::set<std::string>::iterator itf;
	std::set<std::string>::iterator itse;
	ft::set<std::string> ::iterator itfe;

	std::set<std::string>::const_iterator cits;
	ft::set<std::string>::const_iterator citf;
	std::set<std::string>::const_iterator citse;
	ft::set<std::string>::const_iterator citfe;
};

TEST_F(SetBoundTest, emptyLower) {
	std::set<std::string> sEmpty;
	ft::set<std::string> fEmpty;

	its = sEmpty.lower_bound("a");
	itf = fEmpty.lower_bound("a");

	EXPECT_EQ(its, sEmpty.end());
	EXPECT_EQ(itf, fEmpty.end());
	EXPECT_EQ(its, sEmpty.begin());
	EXPECT_EQ(itf, fEmpty.begin());
}

TEST_F(SetBoundTest, emptyUpper) {
	std::set<std::string> sEmpty;
	ft::set<std::string> fEmpty;

	its = sEmpty.upper_bound("a");
	itf = fEmpty.upper_bound("a");

	EXPECT_EQ(its, sEmpty.end());
	EXPECT_EQ(itf, fEmpty.end());
	EXPECT_EQ(its, sEmpty.begin());
	EXPECT_EQ(itf, fEmpty.begin());
}

TEST_F(SetBoundTest, singleUpper) {
	std::set<std::string> s1;
	ft::set<std::string> f1;

	s1.insert("c");
	f1.insert("c");

	its = s1.upper_bound("c");
	itf = f1.upper_bound("c");
	EXPECT_EQ(its, s1.end());
	EXPECT_EQ(itf, f1.end());

	its = s1.upper_bound("a");
	itf = f1.upper_bound("a");
	EXPECT_EQ(its, s1.begin());
	EXPECT_EQ(itf, f1.begin());

	its = s1.upper_bound("d");
	itf = f1.upper_bound("d");
	EXPECT_EQ(its, s1.end());
	EXPECT_EQ(itf, f1.end());
}

TEST_F(SetBoundTest, singleLower) {
	std::set<std::string> s1;
	ft::set<std::string> f1;

	s1.insert("c");
	f1.insert("c");

	its = s1.lower_bound("c");
	itf = f1.lower_bound("c");
	EXPECT_EQ(its, s1.begin());
	EXPECT_EQ(itf, f1.begin());

	its = s1.lower_bound("a");
	itf = f1.lower_bound("a");
	EXPECT_EQ(its, s1.begin());
	EXPECT_EQ(itf, f1.begin());

	its = s1.lower_bound("d");
	itf = f1.lower_bound("d");
	EXPECT_EQ(its, s1.end());
	EXPECT_EQ(itf, f1.end());
}

TEST_F(SetBoundTest, multitest) {
	step_iter = 0;
	for (double i = -step / 2; i < 10.5; i += step) {

		its = s.lower_bound(std::to_string(i));
		itf = f.lower_bound(std::to_string(i));
		checkSetAreEqualIt(itf, f.end(), its, s.end());

		its = s.upper_bound(std::to_string(i));
		itf = f.upper_bound(std::to_string(i));
		checkSetAreEqualIt(itf, f.end(), its, s.end());
	}
}

TEST_F(SetBoundTest, multitestConst) {
	step_iter = 0;
	for (double i = -step / 2; i < 10.5; i += step) {

		cits = s.lower_bound(std::to_string(i));
		citf = f.lower_bound(std::to_string(i));
		checkSetAreEqualIt(citf, f.end(), cits, s.end());

		cits = s.upper_bound(std::to_string(i));
		citf = f.upper_bound(std::to_string(i));
		checkSetAreEqualIt(citf, f.end(), cits, s.end());
	}
}

class SetEqualRangeTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 200; ++i) {
			iter = static_cast<double>(i);
			sample.insert(std::to_string(iter));
		}
	}

	typedef std::set<std::string>::const_iterator const_iterator_s;
	typedef std::set<std::string>::iterator iterator_s;

	typedef ft::set<std::string>::const_iterator const_iterator_f;
	typedef ft::set<std::string>::iterator iterator_f;

	double iter;

	std::set<std::string> sample;

	std::set<std::string> s;
	ft::set<std::string> f;

	std::pair<const_iterator_s,const_iterator_s> cps;
	std::pair<iterator_s,iterator_s> ps;

	std::pair<const_iterator_f,const_iterator_f> cpf;
	std::pair<iterator_f,iterator_f> pf;
};

TEST_F(SetEqualRangeTest, empty) {
	std::set<std::string> sEmpty;
	ft::set<std::string> fEmpty;

	ps = s.equal_range("a");
	pf = f.equal_range("a");

	EXPECT_EQ(ps.first, s.end());
	EXPECT_EQ(ps.second, s.end());
	EXPECT_EQ(pf.first, f.end());
	EXPECT_EQ(pf.second, f.end());
}

TEST_F(SetEqualRangeTest, emptyConst) {
	std::set<std::string> sEmpty;
	ft::set<std::string> fEmpty;

	cps = s.equal_range("a");
	cpf = f.equal_range("a");

	EXPECT_EQ(cps.first, s.end());
	EXPECT_EQ(cps.second, s.end());
	EXPECT_EQ(cpf.first, f.end());
	EXPECT_EQ(cpf.second, f.end());
}

TEST_F(SetEqualRangeTest, single) {
	std::set<std::string> s1;
	ft::set<std::string> f1;

	s1.insert("c");
	f1.insert("c");

	ps = s1.equal_range("c");
	pf = f1.equal_range("c");
	EXPECT_EQ(ps.first, s1.begin());
	EXPECT_EQ(ps.second, s1.end());
	EXPECT_EQ(pf.first, f1.begin());
	EXPECT_EQ(pf.second, f1.end());

	ps = s1.equal_range("a");
	pf = f1.equal_range("a");
	EXPECT_EQ(ps.first, s1.begin());
	EXPECT_EQ(ps.second, s1.begin());
	EXPECT_EQ(pf.first, f1.begin());
	EXPECT_EQ(pf.second, f1.begin());

	ps = s1.equal_range("d");
	pf = f1.equal_range("d");
	EXPECT_EQ(ps.first, s1.end());
	EXPECT_EQ(ps.second, s1.end());
	EXPECT_EQ(pf.first, f1.end());
	EXPECT_EQ(pf.second, f1.end());
}

TEST_F(SetEqualRangeTest, singleConst) {
	std::set<std::string> s1;
	ft::set<std::string> f1;

	s1.insert("c");
	f1.insert("c");

	cps = s1.equal_range("c");
	cpf = f1.equal_range("c");
	EXPECT_EQ(cps.first, s1.begin());
	EXPECT_EQ(cps.second, s1.end());
	EXPECT_EQ(cpf.first, f1.begin());
	EXPECT_EQ(cpf.second, f1.end());

	cps = s1.equal_range("a");
	cpf = f1.equal_range("a");
	EXPECT_EQ(cps.first, s1.begin());
	EXPECT_EQ(cps.second, s1.begin());
	EXPECT_EQ(cpf.first, f1.begin());
	EXPECT_EQ(cpf.second, f1.begin());

	cps = s1.equal_range("d");
	cpf = f1.equal_range("d");
	EXPECT_EQ(cps.first, s1.end());
	EXPECT_EQ(cps.second, s1.end());
	EXPECT_EQ(cpf.first, f1.end());
	EXPECT_EQ(cpf.second, f1.end());
}

TEST_F(SetEqualRangeTest, multitest) {
	for (int i = -5; i < 205; ++i) {
		iter = static_cast<double>(i) * 0.5;

		ps = s.equal_range(std::to_string(iter));
		pf = f.equal_range(std::to_string(iter));
		checkSetAreEqualIt(pf.first, pf.second, ps.first, ps.second);
	}
}

TEST_F(SetEqualRangeTest, multitestConst) {
	for (int i = -5; i < 205; ++i) {
		iter = static_cast<double>(i) * 0.5;

		cps = s.equal_range(std::to_string(iter));
		cpf = f.equal_range(std::to_string(iter));
		checkSetAreEqualIt(cpf.first, cpf.second, cps.first, cps.second);
	}
}

class SetEraseSimpleTest : public testing::Test {
protected:
	virtual void SetUp() {
		s.insert("a");
		s.insert("b");
		s.insert("c");
		f.insert("a");
		f.insert("b");
		f.insert("c");
	}

	std::set<std::string> s;
	ft::set<std::string>  f;

};

void	SetEraseSimpleTestFunc(ft::set<std::string> & f, std::set<std::string> & s,
							   std::string s1, std::string s2, std::string s3) {
	size_t retf;
	size_t rets;

	rets = s.erase(s1 + s2 + s3);
	retf = f.erase(s1 + s2 + s3);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(*s.begin(), *f.begin());
	EXPECT_EQ(*--s.end(), *--f.end());
	checkIfSetAreEqual(f, s);

	rets = s.erase(s1);
	retf = f.erase(s1);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(*s.begin(), *f.begin());
	EXPECT_EQ(*--s.end(), *--f.end());
	checkIfSetAreEqual(f, s);

	rets = s.erase(s2);
	retf = f.erase(s2);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(*s.begin(), *f.begin());
	EXPECT_EQ(*--s.end(), *--f.end());
	checkIfSetAreEqual(f, s);

	rets = s.erase(s3);
	retf = f.erase(s3);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(s.begin(), s.end());
	EXPECT_EQ(f.begin(), f.end());
	checkIfSetAreEqual(f, s);

	rets = s.erase(s1);
	retf = f.erase(s1);
	EXPECT_EQ(retf, rets);
	EXPECT_EQ(s.begin(), s.end());
	EXPECT_EQ(f.begin(), f.end());
	checkIfSetAreEqual(f, s);
}

TEST_F(SetEraseSimpleTest, abc) {
	SetEraseSimpleTestFunc(f, s, "a", "b", "c");
}

TEST_F(SetEraseSimpleTest, acb) {
	SetEraseSimpleTestFunc(f, s, "a", "c", "b");
}

TEST_F(SetEraseSimpleTest, bac) {
	SetEraseSimpleTestFunc(f, s, "b", "a", "c");
}

TEST_F(SetEraseSimpleTest, bca) {
	SetEraseSimpleTestFunc(f, s, "b", "c", "a");
}

TEST_F(SetEraseSimpleTest, cab) {
	SetEraseSimpleTestFunc(f, s, "c", "a", "b");
}

TEST_F(SetEraseSimpleTest, cba) {
	SetEraseSimpleTestFunc(f, s, "c", "b", "a");
}

class SetClearTest : public testing::Test {
protected:
	virtual void SetUp() {

	}
	std::set<std::string> s;
	ft::set<std::string>  f;
};

TEST_F(SetClearTest, emptyClear) {
	s.clear();
	f.clear();

	checkIfSetAreEqual(f, s);
}

TEST_F(SetClearTest, nonEmptyClear) {
	for (int i = 0; i < 12; ++i) {
		s.insert(std::to_string(i));
		f.insert(std::to_string(i));
	}

	s.clear();
	f.clear();
	checkIfSetAreEqual(f, s);
}

class SetAssignationTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 13; ++i) {
			s.insert(std::to_string(i));
			f.insert(std::to_string(i));
		}
	}

	std::set<std::string> s;
	ft::set<std::string>  f;
	std::set<std::string> sEmpty;
	ft::set<std::string>  fEmpty;
	std::set<std::string> sTmp;
	ft::set<std::string>  fTmp;
};

TEST_F(SetAssignationTest, fromFullToEmpty) {
	sEmpty = s;
	fEmpty = f;
	checkIfSetAreEqual(fEmpty, sEmpty);
	checkIfSetAreEqual(f, s);

	sEmpty.insert("sf");
	fEmpty.insert("sf");
	checkIfSetAreEqual(fEmpty, sEmpty);
}

TEST_F(SetAssignationTest, fromEmtpyToFull) {
	s = sEmpty;
	f = fEmpty;
	checkIfSetAreEqual(fEmpty, sEmpty);
	checkIfSetAreEqual(f, s);

	s.insert("sf");
	f.insert("sf");
	checkIfSetAreEqual(f, s);
}

TEST_F(SetAssignationTest, fromEmtpyToEmpty) {
	sTmp = sEmpty;
	fTmp = fEmpty;
	checkIfSetAreEqual(fEmpty, sEmpty);
	checkIfSetAreEqual(fTmp, sTmp);

	sTmp.insert("sf");
	fTmp.insert("sf");
	checkIfSetAreEqual(fTmp, sTmp);
}

TEST_F(SetAssignationTest, fromFullToFull) {
	sEmpty.insert("sf");
	fEmpty.insert("sf");
	s = sEmpty;
	f = fEmpty;
	checkIfSetAreEqual(fEmpty, sEmpty);
	checkIfSetAreEqual(fTmp, sTmp);

	s.insert("sf");
	f.insert("sf");
	checkIfSetAreEqual(f, s);
}

class SetCopyConstructionTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s.insert(std::to_string(i));
			f.insert(std::to_string(i));
		}
	}

	std::set<std::string> s;
	ft::set<std::string>  f;
	std::set<std::string> sEmpty;
	ft::set<std::string>  fEmpty;

};

TEST_F(SetCopyConstructionTest, fromFull) {
	std::set<std::string> s1 = s;
	ft::set<std::string>  f1 = f;

	checkIfSetAreEqual(f1, s1);
	checkIfSetAreEqual(f, s);

	s1.insert("sf");
	f1.insert("sf");
	checkIfSetAreEqual(f1, s1);
}

TEST_F(SetCopyConstructionTest, fromEmtpy) {
	std::set<std::string> s1 = sEmpty;
	ft::set<std::string>  f1 = fEmpty;

	checkIfSetAreEqual(f1, s1);
	checkIfSetAreEqual(fEmpty, sEmpty);

	s1.insert("sf");
	f1.insert("sf");
	checkIfSetAreEqual(f1, s1);
}

class SetSwapTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 100; ++i) {
			s1.insert(std::to_string(i));
			f1.insert(std::to_string(i));
		}
	}

	std::set<std::string> s2, s1;
	ft::set<std::string>  f2, f1;
};

TEST_F(SetSwapTest, integrityFullEmpty) {
	s1.swap(s2);
	f1.swap(f2);

	checkIfSetAreEqual(f1, s1);
	checkIfSetAreEqual(f2, s2);
}

TEST_F(SetSwapTest, integrityEmptyFull) {
	s2.swap(s1);
	f2.swap(f1);

	checkIfSetAreEqual(f1, s1);
	checkIfSetAreEqual(f2, s2);
}

TEST_F(SetSwapTest, integrityFullFull) {
	s2.insert("std::to_string(i)");
	f2.insert("std::to_string(i)");

	s2.swap(s1);
	f2.swap(f1);

	checkIfSetAreEqual(f1, s1);
	checkIfSetAreEqual(f2, s2);
}

TEST_F(SetSwapTest, iteratorValidity) {
	std::set<std::string>::iterator its = ++s1.begin();
	ft::set<std::string>::iterator itf = ++f1.begin();

	s2.insert("std::to_string(i)");
	f2.insert("std::to_string(i)");

	s2.swap(s1);
	f2.swap(f1);

	checkIfSetAreEqual(f1, s1);
	checkIfSetAreEqual(f2, s2);
	checkSetAreEqualIt(itf, f2.end(), its, s2.end());
}

class SetEraseRangeTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 50; ++i) {
			sRef.insert(std::to_string(i));
			fRef.insert(std::to_string(i));
		}
	}

	std::set<std::string> sRef, s;
	ft::set<std::string>  fRef, f;

	std::set<std::string>::iterator its, jts, itse, itsdel1, itsdel2, itscheck, itschecke;
	ft::set<std::string>::iterator itfdel1, itfdel2, itfcheck, itfchecke;

	size_t retf;
	size_t rets;
};

TEST_F(SetEraseRangeTest, eraseSimpleTest) {
	itse = sRef.end();
	int i = 0;
	int j = 0;

	for (its = sRef.begin(); its != itse; ++its) {
		j = i;
		for (jts = its; true; ++jts) {
			f = fRef;
			s = sRef;
			checkIfSetAreEqual(f, s);
			itsdel1 = s.find(*its);
			itfdel1 = f.find(*its);
			itsdel2 = s.find(*jts);
			itfdel2 = f.find(*jts);
			s.erase(itsdel1, itsdel2);
			f.erase(itfdel1, itfdel2);

			EXPECT_EQ(f.size(), s.size()) << "from = " << i << " to = " << j;
			EXPECT_EQ(f.empty(), s.empty()) << "from = " << i << " to = " << j;
			itschecke = s.end();
			itfchecke = f.end();
			itfcheck = f.begin();
			for (itscheck = s.begin(); itscheck != itschecke; ) {
				EXPECT_EQ(*itscheck++, *itfcheck++) << "from = " << i << " to = " << j;
			}
			EXPECT_EQ(itfcheck, itfchecke) << "from = " << i << " to = " << j;
			if (jts == itse)
				break;
			j++;
		}
		i++;
	}
}

