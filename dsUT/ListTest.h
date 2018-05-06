//Copyright ©2018, multics, Inc.All rights reserved.

#pragma once

#include "gtest/gtest.h"
#include "List.h"

class ListTest : public ::testing::Test {
	protected:
				ListTest() {};
		virtual ~ListTest() {};
		virtual void SetUp() {};
		virtual void TearDown() {};

		List<int> m_oList1;
};

//TestCases
TEST_F(ListTest, DefaultConstructor) {
	size_t nSize = m_oList1.GetSize();

	EXPECT_EQ(nSize, 0) << "When contstructed the linked list should be empty.";
}
