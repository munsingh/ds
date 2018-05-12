//Copyright ©2018, multics, Inc.All rights reserved.
#pragma once

#include "List.h"

template <class T> class CyclicList : public List<T> {
	public:
		//constructors
				CyclicList() : List(), m_pCycleStart( nullptr ) {};
				//CyclicList(const& CyclicList& oCyclicList);

		virtual ~CyclicList() { EmptyList(); };

		//overloaded operators
		//CyclicList<T>& operator= (const CyclicList& oCyclicList);
		//overloaded 
		void	 EmptyList();
		Node<T>* CreateCycle(size_t nCyclePos);
		Node<T>* CreateCycle(Node<T>* pCycleNode);
		Node<T>* GetCycleStart() const { return m_pCycleStart; };
	protected:
		Node<T>*	m_pCycleStart = nullptr;
};

template <class T> void CyclicList<T>::EmptyList() {
	Node<T>* pCurr = GetHead();
	Node<T>* pPrev = nullptr;
	bool bVisited = false;
	
	//empyting a cyclic list means not to delete
	//the cycle start node first time
	//but delete it when you runinto it again the 2nd time.

	while (nullptr != ( pCurr = GetHead())) {
		pPrev = pCurr;

		if (bVisited) {
			if (pPrev == m_pCycleStart) {
				SetHead(nullptr);
				delete pPrev;
			}
			else {
				SetHead(pCurr->GetNext());
				delete pPrev;
			}
			pPrev = nullptr;
		}
		else {
			SetHead(pCurr->GetNext());
			if (pPrev == m_pCycleStart) {
				bVisited = true;
			}
			else {
				delete pPrev;
				pPrev = nullptr;
			}
		}
	}
}

template <class T> Node<T>* CyclicList<T>::CreateCycle(size_t nCyclePos) {
	return CreateCycle(GetAt(nCyclePos));
}

template <class T> Node<T>* CyclicList<T>::CreateCycle(Node<T>* pCycleNode) {
	List<T>::GetTail()->SetNext(pCycleNode);
	m_pCycleStart = pCycleNode;
	return m_pCycleStart;
}




