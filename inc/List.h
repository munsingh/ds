//Copyright ©2018, multics, Inc.All rights reserved.
#pragma once

#include "Node.h"

template <class T> class List {
	public:
		//constructors
				List(bool bSorted = false)
					:m_pHead(nullptr), m_bSorted(bSorted) {};
				List(const List<T>& oList);

		//destructors
		virtual ~List();

		//overloaded operators
		List<T>& operator= (const List<T>& oList);

		//member functions
		virtual Node<T>*	AddHead(const T& oData);
		virtual Node<T>*	AddHead(Node<T>* oNode);
		virtual Node<T>*	AddNode(const T& oData);
		virtual Node<T>*	AddTail(const T& oData);
		virtual Node<T>*	AddTail(Node<T>* pNode);
		virtual Node<T>*	AddAt(const T& oData, size_t nPos);
		

		virtual Node<T>*	GetHead() const { return m_pHead; };
		virtual size_t		GetSize() const;
		virtual Node<T>*	GetTail() const;
		virtual Node<T>*	GetAt(size_t nPos) const;
		virtual Node<T>*	GetMid() const;
		virtual Node<T>*	GetNthLast(size_t nPos) const;

		virtual bool		DeleteNode(Node<T>* pNode);
		virtual void		EmptyList();
		virtual bool		IsSorted() const { return m_bSorted; };
		virtual bool		IsEmpty() const { return nullptr == GetHead(); };

		//Cyclic List related functions
		//Node<T>*	GetCycleStart(size_t& nCycleLength) const;
		static bool	IsCyclic(List<T>& oList, Node<T>*& oNodeInCycle);
		//overloaded operators

		//insertion operator
		//The idea is to write the contents of the list to the stdout

		//overload the extraction operator >> to add nodes to the list
		template< class T>
		friend List<T>& operator>> (const T&oData, List<T>& oList);

		//overloaded insertion operator
		template <class T>
		friend std::ostream& operator <<(std::ostream& out, const List<T>& oList);

	protected:
		//member attribues
		Node<T>* m_pHead = nullptr;
		bool	 m_bSorted = false;

		//member functions
		virtual void		SetHead(Node<T>* pNode) { m_pHead = pNode; };
		virtual void		CopyList(const List<T>& oList);

		virtual Node<T>*	AddAt(Node<T>* pNode, size_t nPos);
};

//Implementation

//destructor

template <class T> List<T>::~List() {
	EmptyList();
}

//constructors
template <class T> List<T>::List(const List<T>& oList) {
	//make a copy of the list
	CopyList(oList);
}

//overloaded operators
template <class T> List<T>& List<T>::operator= (const List<T>& oList) {
	if (this != &oList) {
		//Since we are assigning this list to be the same as another list
		//we need to fist empty this list
		EmptyList();
		CopyList(oList);
	}

	return *this;
}

//member functions
template <class T> Node<T>* List<T>::AddHead(const T& oData) {
	return AddHead(new Node<T>(oData, GetHead()));
}

template <class T> Node<T>* List<T>::AddHead(Node<T>* pNode) {
	SetHead(pNode);
	return GetHead();
}

template <class T> void List<T>::EmptyList() {
	Node<T>* pNode = nullptr;

	while (nullptr != (pNode = GetHead())) {
		SetHead(GetHead()->GetNext());
		delete pNode;
	}
}

template <class T> void List<T>::CopyList(const List<T>& oList) {
	Node<T>* pSourceNode = oList.GetHead();
	Node<T>* pPrev = nullptr;
	Node<T>* pNew = nullptr;

	while (nullptr != pSourceNode) {
		pNew = new Node<T>(pSourceNode->GetData());
		if (nullptr == GetHead()) {
			SetHead(pNew);
		}
		else {
			pPrev->SetNext(pNew);
		}
		pPrev = pNew;
		pSourceNode = pSourceNode->GetNext();
	}
}

template <class T> size_t List<T>::GetSize() const {
	size_t		nSize = 0;
	Node<T>*	pNode = GetHead();

	while (nullptr != pNode) {
		++nSize;
		pNode = pNode->GetNext();
	}

	return nSize;
}

template <class T> Node<T>* List<T>::AddNode(const T& oData) {
	//If the list is sorted, then add data in a sorted manner
	//otherwise add the new node as the head
	if (IsSorted()) {
		Node<T>* pCurr = GetHead();
		Node<T>* pPrev = nullptr;

		while (pCurr && pCurr->GetData() < oData) {
			pPrev = pCurr;
			pCurr = pCurr->GetNext();
		}

		//We have found the pCurr node whose data is less than the 
		//given data
		//So we have to add the new node after pPrev and before pCurr
		Node<T>* pNewNode = new Node<T>(oData);
		if (nullptr == pPrev) {
			SetHead(pNewNode);
		}
		else {
			pNewNode->SetNext(pPrev->GetNext());
			pPrev->SetNext(pNewNode);
		}
		return pNewNode;
	}
	else
		return AddHead(oData);
}

template <class T> Node<T>* List<T>::AddTail(const T& oData) {
	return AddTail(new Node<T>(oData));
}

template <class T> Node<T>* List<T>::AddTail(Node<T>* pNode) {
	//Add Node at end
	Node<T>* pTail = GetTail();
	if (pTail) {
		pNode->SetNext(pTail->GetNext());
		pTail->SetNext(pNode);
	}
	else {
		AddHead(pNode);
	}

	return pNode;
}

template <class T> Node<T>* List<T>::GetTail() const {
	Node<T>* pTail = nullptr;
	Node<T>* pCurr = GetHead();

	while (pCurr) {
		pTail = pCurr;
		pCurr = pCurr->GetNext();
	}

	return pTail;
}

template <class T> Node<T>* List<T>::GetAt(size_t nPos) const {
	Node<T>* pCurr = GetHead();
	size_t   nCurrPos = 0;

	while (pCurr && nCurrPos++ < nPos) {
		pCurr = pCurr->GetNext();
	}

	return pCurr;
}

template <class T> Node<T>* List<T>::GetMid() const {
	//finds and returns the node at the mid location
	//Start with two pointers, move one pointer one node at
	//a time, where as the other pointer moves two nodes at
	//a time. The location of the first pointer when the second
	//pointer hits the end is the mid node

	Node<T>* pSlow = GetHead();
	Node<T>* pFast = GetHead();

	while (pFast) {
		pFast = pFast->GetNext();

		if (nullptr == pFast) {
			break;
		}
		else {
			pSlow = pSlow->GetNext();
			pFast = pFast->GetNext();
		}
	}

	return pSlow;
}

template <class T> Node<T>* List<T>::GetNthLast(size_t nNthLast) const {
	//Start with two pointers, move the 2nd one n spaces
	//and then start both of them together.
	//The point when 2nd pointer reaches last,
	//the first pointer will point to the nthLast.

	Node<T>* pFirst = GetHead();
	Node<T>* pSecond = GetHead();
	if (nNthLast == 0)
		nNthLast = 1;

	size_t nIndex = 0;
	while (pSecond) {
		pSecond = pSecond->GetNext();

		if (nIndex >= nNthLast) {
			pFirst = pFirst->GetNext();
		}
		else
			++nIndex;
 	}

	if (nullptr == pSecond && nNthLast > nIndex) {
		//out of bounds nthlast requested
		return nullptr;
	}
	else
		return pFirst;
}

template <class T> Node<T>* List<T>::AddAt(const T& oData, size_t nPos) {
	if (nPos > GetSize())
		return nullptr;
	return AddAt(new Node<T>(oData), nPos);
}

template <class T> Node<T>* List<T>::AddAt(Node<T>* pNode, size_t nPos) {
	//Add the node at the desired position nPos
	Node<T>* pCurr = GetHead();
	Node<T>* pPrev = nullptr;
	size_t   nCurrPos = 0;
	
	while (pCurr && nCurrPos < nPos) {
		pPrev = pCurr;
		pCurr = pCurr->GetNext();
		++nCurrPos;
	}

	if (pPrev) {
		pNode->SetNext(pPrev->GetNext());
		pPrev->SetNext(pNode);
	}
	else {
		//pPrev is null, which means that we have to add at begining
		pNode->SetNext(GetHead());
		SetHead(pNode);
	}

	return pNode;
}

template <class T> bool List<T>::DeleteNode(Node<T>* pNode) {
	//If last node then the delete operation will be O(n) otherwise i
	//it is O(1)

	if (IsEmpty())
		return false;

	//Check whether this is last node
	Node<T>* pNext = nullptr;
	if (nullptr == (pNext = pNode->GetNext())) {
		//last node
		Node<T>* pCurr = GetHead();
		Node<T>* pPrev = nullptr;

		while (pCurr && pCurr != pNode) {
			pPrev = pCurr;
			pCurr = pCurr->GetNext();
		}

		if (pCurr) {
			//pCurr is the node to be deleted
			pPrev->SetNext(pCurr->GetNext());

			if (pCurr == GetHead()) {
				SetHead(pCurr->GetNext());
			}

			delete pCurr;
			pCurr = nullptr;
		}
		else
			return false;
	}
	else {
		//in between node
		//so take on the contents of the next node
		//point this node to next node's next node
		//and then delete the next node

		pNode->SetData(pNext->GetData());
		pNode->SetNext(pNext->GetNext());
		delete pNext;
		pNext = nullptr;
	}

	return true;
}

//This function finds out whether a list is cyclic and if yes,
//also makes availale a node within the cycle.
template <class T> bool List<T>::IsCyclic(List<T>& oList, Node<T>*& oNodeInCycle) {
	bool bIsCycle = false;
	Node<T>* pFast = oList.GetHead();
	Node<T*> pSlow = oList.GetHead();

	while (pFast && pSlow) {
		pFast = pFast->GetNext();
		if (pSlow == pFast) {
			bCycle = true;
			break;
		}

		if (nullptr == pFast) {
			break;//not a cycle
		}

		pFast = pFast->GetNext();
		if (pSlow == pFast) {
			bCycle = true;
			break;
		}

		pSlow = pSlow->GetNext();
	}

	oNodeInCycle = bCycle ? pSlow : nullptr;
	return bCycle;
}

//template <class T> Node<T>* List<T>::GetCycleStart(size_t& nCycleLength) const; {
//	//We figure out whether the list is cyclic 
//	//if it is then get the length of the cycle.
//	Node<T>* pNodeInCycle = nullptr;
//	bool	 bCyclic = List<T>::IsCyclic( *this, &pNodeInCycle );
//	if (!bCyclic) {
//		nCycleLength = 0;
//		return nullptr;
//	}
//
//	//There is a cycle, so calculate the length of the cycle.
//	Node<T>* pNode1 = pNodeInCycle;
//	Node<T>* pNode2 = pNodeInCycle->GetNext();
//
//	while (pNode1 != pNode2) {
//		pNode2 = pNode2->GetNext();
//		++nCycleLength;
//	}
//
//	//Now we know the cyclelength
//	//to get the cycle start
//	//
//	
//}


//overloaded operators
template <class T> List<T>& operator>>(const T& oData, List<T>& oList) {
	oList.AddNode(oData);
	return oList;
}

template <class T> std::ostream& operator <<(std::ostream& out, const List<T>& oList) {
	//we iterate over the list and dump its contents to the ostream
	Node<T>* pCurrNode = oList.GetHead();
	while (pCurrNode) {
		out << pCurrNode;
		pCurrNode = pCurrNode->GetNext();
	}

	return out;
}