//Copyright ©2018, multics, Inc.All rights reserved.
#pragma once

#include "Node.h"

template <class T> class List {
	public:
		//constructors
				List(bool bSorted = false)
					:m_pHead(nullptr), m_pSorted(bSorted) {};
				List(const List<T>& oList);

		//destructors
		virtual List();

		//overloaded operators
		List<T>& operator= (const List<T>& oList);

		//member functions
		Node<T>*	AddHead(const T& oData);
		Node<T>*	AddHead(const Node<T>* oNode);
		Node<T>*	GetHead() const { return m_pHead; };

		void		EmptyList();
	protected:
		//member attribues
		Node<T>* m_pHead = nullptr;
		bool	 m_pSorted(false);

		//member functions
		void		SetHead(const Node<T>* pNode) { m_pHead = pNode; };
		void		CopyList(const List<T>& oList);
};

//Implementation

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
	return AddHead(new Node<T>(oData, GetHead());
}

template <class T> Node<T>* List<T>::AddHead(const Node<T>* oNode) {
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
