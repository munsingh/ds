//Copyright ©2018, multics, Inc.All rights reserved.

#pragma once

#include "gtest/gtest.h"
#include "CyclicList.h"

class CyclicListTest : public ::testing::Test {
	protected:
		CyclicListTest() {};
		virtual ~CyclicListTest() {};
		virtual void SetUp() {
			5 >> m_oUnsortedList;
			2 >> m_oUnsortedList;
			3 >> m_oUnsortedList;
			1 >> m_oUnsortedList;
			7 >> m_oUnsortedList;
			9 >> m_oUnsortedList;
			0 >> m_oUnsortedList;
		};
		virtual void TearDown() {};

		CyclicList<int> m_oList1;
		CyclicList<int> m_oUnsortedList;
};

TEST_F(CyclicListTest, CreateCycle) {
	//Create Cycle at node with value 1, which is at 3rd Pos
	m_oUnsortedList.CreateCycle(3);
	
	ASSERT_EQ(m_oUnsortedList.GetCycleStart()->GetData(), 1) << "The cycle start node should be 1.";
}
