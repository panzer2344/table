#pragma once
#include "TTable.h"
#include "stack.h"

template<class TKey, class TValue>
struct TNode {
	TRecord<TKey, TValue> rec;
	TNode *pLeft, *pRight;
	int bal;
};

template<class TKey, class TValue>
class TTreeTable :
	public TTable<TKey, TValue>
{
protected:
	TNode<TKey, TValue> *pRoot, *pCurr, **pRes;
	Stack<TNode<TKey, TValue>* > st;
	int position;

public:
	TTreeTable();
	~TTreeTable();

	virtual bool isFull();

	virtual bool Find(TKey tk);
	virtual bool Insert(TRecord<TKey, TValue> tr);
	virtual bool Delete(TKey tk);

	virtual TRecord<TKey, TValue> GetCurrent();
	virtual void SetCurrent(TValue);

	virtual void GoNext();
	virtual bool isEnd();
	virtual void Reset();
};

template<class TKey, class TValue>
TTreeTable<TKey, TValue>::TTreeTable() {
	pRoot = NULL;
	pCurr = NULL;
	pRes = NULL;
}

template<class TKey, class TValue>
TTreeTable<TKey, TValue>::~TTreeTable() {
}

template<class TKey, class TValue>
bool TTreeTable<TKey, TValue>::isFull() {
	return false;
}

template<class TKey, class TValue>
bool TTreeTable<TKey, TValue>::Find(TKey key) {
	pRes = &pRoot;
	while (*pRes != NULL) {
		eff++;

		if ((*pRes)->rec.key == key) {
			pCurr = *pRes;
			return true;
		}

		if ((*pRes)->rec.key < key)
			pRes = &((*pRes)->pRight);
		else pRes = &((*pRes)->pLeft);
	}
	pCurr = *pRes;
	return false;
}

template<class TKey, class TValue>
bool TTreeTable<TKey, TValue>::Insert(TRecord<TKey, TValue> rec) {
	if (!Find(rec.key)) {
		*pRes = new TNode<TKey, TValue>;
		(*pRes)->rec = rec;
		(*pRes)->pRight = NULL;
		(*pRes)->pLeft = NULL;

		if (pRoot == NULL) pRoot = *pRes;
		dataCount++;

		return true;
	}
	return false;
}

template<class TKey, class TValue>
bool TTreeTable<TKey, TValue>::Delete(TKey key) {
	if (Find(key)) {
		TNode<TKey, TValue> *temp = *pRes;

		if (temp->pLeft == NULL) {
			*pRes = temp->pRight;
		}
		else if (temp->pRight == NULL) {
			*pRes = temp->pLeft;
		}
		else {
			TNode<TKey, TValue> *p = temp->pLeft;
			TNode<TKey, TValue> **pPrev = &(temp->pLeft);
			while (p->pRight != NULL) {
				eff++;

				pPrev = &(p->pRight);
				p = p->pRight;
			}

			temp->rec.value = p->rec.value;
			temp->rec.key = p->rec.key;
			temp = p;
			*pPrev = p->pLeft;
		}
		delete temp;
		dataCount--;

		return true;
	}
	return false;
}


template<class TKey, class TValue>
TRecord<TKey, TValue> TTreeTable<TKey, TValue>::GetCurrent() {
	if (pCurr != NULL)
		return pCurr->rec;
	else
		return{ string("undifined"), -1 };
}


template<class TKey, class TValue>
void TTreeTable<TKey, TValue>::SetCurrent(TValue _value) {
	pCurr->rec.value = _value;
}

template<class TKey, class TValue>
void TTreeTable<TKey, TValue>::GoNext() {
	st.pop();

	if (pCurr->pRight != NULL) {
		pCurr = pCurr->pRight;
		while (pCurr->pLeft != NULL) {
			st.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		st.push(pCurr);
	}
	else {
		if (!st.isEmpty()) {
			pCurr = st.top();
		}
	}

	position++;
}

template<class TKey, class TValue>
bool TTreeTable<TKey, TValue>::isEnd() {
	return dataCount == position;
}

template<class TKey, class TValue>
void TTreeTable<TKey, TValue>::Reset() {
	position = 0;

	st.clear();
	pCurr = pRoot;

	while (pCurr->pLeft != NULL) {
		st.push(pCurr);
		pCurr = pCurr->pLeft;
	}
	st.push(pCurr);
}

