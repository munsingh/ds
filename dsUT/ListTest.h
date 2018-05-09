//Copyright ©2018, multics, Inc.All rights reserved.

#pragma once

#include "gtest/gtest.h"
#include "List.h"

class ListTest : public ::testing::Test {
	protected:
				ListTest() {};
		virtual ~ListTest() {};
		virtual void SetUp() {
			2 >> m_oUnsortedList;
			3 >> m_oUnsortedList;
			1 >> m_oUnsortedList;
			7 >> m_oUnsortedList;
			9 >> m_oUnsortedList;
			0 >> m_oUnsortedList;
		};
		virtual void TearDown() {};

		List<int> m_oList1;
		List<int> m_oUnsortedList;
};

//TestCases

//This test cases checks the internal state of the member variables of
//an empty list
TEST_F(ListTest, DefaultConstructor) {
	ASSERT_EQ(m_oList1.GetHead(), nullptr) << "When constructed the Head should be null.";
	ASSERT_EQ(m_oList1.GetSize(), 0) << "When contstructed the linked list should be empty.";
	ASSERT_FALSE(m_oList1.IsSorted()) << "When constructed with default arguments, it should be a sorted list.";
}

TEST_F(ListTest, CopyConstructor) {
	List<int> oList(m_oUnsortedList);
	ASSERT_EQ(oList.GetSize(), 6) << "Size mismatch while copy constructing";
	
	//Dump the oList to a stringstream
	std::stringstream oStrStream;
	oStrStream << oList;

	ASSERT_STRCASEEQ(oStrStream.str().c_str(), "0->9->7->1->3->2->NULL") << "Copy constructor failed.";
}

TEST_F(ListTest, AssignmentOperator) {
	m_oList1 = m_oUnsortedList;
	
	ASSERT_EQ(m_oList1.GetSize(), 6) << "Size mismatch while copy constructing";

	//Dump the oList to a stringstream
	std::stringstream oStrStream;
	oStrStream << m_oList1;

	ASSERT_STRCASEEQ(oStrStream.str().c_str(), "0->9->7->1->3->2->NULL") << "Assignment constructor failed.";
}

TEST_F(ListTest, InsertionOperator) {
	2 >> m_oList1;
	ASSERT_EQ(m_oList1.GetSize(), 1) << "After inserting single data, the size should be 1";
	ASSERT_EQ(m_oList1.GetHead()->GetData(), 2) << "The Head node data should be 2";
}

TEST_F(ListTest, AddTail) {
	m_oUnsortedList.AddTail(6);
	std::stringstream oStrStream;
	oStrStream << m_oUnsortedList;
	ASSERT_STRCASEEQ(oStrStream.str().c_str(), "0->9->7->1->3->2->6->NULL") << "New node should be at the end.";
}

TEST_F(ListTest, AddTailEmptyList) {
	m_oList1.AddTail(2);

	ASSERT_EQ(m_oList1.GetSize(), 1) << "After inserting single data, the size should be 1";
	ASSERT_EQ(m_oList1.GetHead()->GetData(), 2) << "The Head node data should be 2";

	std::stringstream oStrStream;
	oStrStream << m_oList1;
	ASSERT_STRCASEEQ(oStrStream.str().c_str(), "2->NULL") << "New node should be the head node.";
}

TEST_F(ListTest, AddAt0) {
	m_oUnsortedList.AddAt(6, 0);
	ASSERT_EQ(m_oUnsortedList.GetHead()->GetData(), 6) << "The Head node data should be 6";

	std::stringstream oStrStream;
	oStrStream << m_oUnsortedList;
	ASSERT_STRCASEEQ(oStrStream.str().c_str(), "6->0->9->7->1->3->2->NULL") << "New node should be at the begining.";
}

TEST_F(ListTest, AddAtEnd) {
	m_oUnsortedList.AddAt(6, m_oUnsortedList.GetSize());
	std::stringstream oStrStream;
	oStrStream << m_oUnsortedList;
	ASSERT_STRCASEEQ(oStrStream.str().c_str(), "0->9->7->1->3->2->6->NULL") << "New node should be at the end.";
}

TEST_F(ListTest, AddAtPos3) {
	m_oUnsortedList.AddAt(6, 3);
	std::stringstream oStrStream;
	oStrStream << m_oUnsortedList;
	ASSERT_STRCASEEQ(oStrStream.str().c_str(), "0->9->7->6->1->3->2->NULL") << "New node should be at the end.";
}


