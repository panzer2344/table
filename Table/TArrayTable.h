#pragma once
#include "TTable.h"

template<class TKey, class TValue>
class TArrayTable :
	public TTable<TKey, TValue>
{
protected:
	TRecord<TKey, TValue> *arr;
	size_t size, currNum;

public:
	TArrayTable(size_t _size = 100);
	~TArrayTable();

	virtual TRecord<TKey, TValue> GetCurrent();
	virtual void SetCurrent(TValue val);
	
	virtual void Reset();
	virtual void GoNext();
	virtual bool isEnd();

	virtual bool isFull();
};


template<class TKey, class TValue>
TArrayTable<TKey, TValue>::TArrayTable(size_t _size) {
	size = _size;
	arr = new TRecord<TKey, TValue>[size];
	currNum = 0;
}

template<class TKey, class TValue>
TArrayTable<TKey, TValue>::~TArrayTable() {
	delete[] arr;
}

template<class TKey, class TValue>
TRecord<TKey, TValue> TArrayTable<TKey, TValue>::GetCurrent() {
	return arr[currNum];
}

template<class TKey, class TValue>
void TArrayTable<TKey, TValue>::SetCurrent(TValue val) {
	arr[currNum].value = val;
}

template<class TKey, class TValue>
void TArrayTable<TKey, TValue>::Reset() {
	currNum = 0;
}

template<class TKey, class TValue>
void TArrayTable<TKey, TValue>::GoNext() {
	currNum++;
}

template<class TKey, class TValue>
bool TArrayTable<TKey, TValue>::isEnd() {
	return currNum == dataCount;
}

template<class TKey, class TValue>
bool TArrayTable<TKey, TValue>::isFull() {
	return dataCount == size;
}


