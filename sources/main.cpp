//
// ft_containers
//
// Created by Артур Лутфуллин on 11.01.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "gtest/gtest.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	int result = RUN_ALL_TESTS();

	return result;
}