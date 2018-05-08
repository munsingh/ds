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
		Node<T>*	AddHead(const T& oData);
		Node<T>*	AddHead(Node<T>* oNode);
		Node<T>*	GetHead() const { return m_pHead; };

		Node<T>*	AddNode(const T& oData);
		size_t		GetSize() const;

		void		EmptyList();
		bool		IsSorted() const { return m_bSorted; };

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
		void		SetHead(Node<T>* pNode) { m_pHead = pNode; };
		void		CopyList(const List<T>& oList);
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
	if (*this != oList) {
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