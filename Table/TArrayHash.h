#pragma once
#include "THashTable.h"

template<class TKey, class TValue>
class TArrayHash :
	public THashTable<TKey, TValue>
{
protected:
	size_t size, stepcount, currNum;
	TRecord<TKey, TValue> *arr;
	
public:
	TArrayHash(int _size = 100, int _step = 13);
	~TArrayHash();

	virtual bool Find(TKey key);
	virtual bool Delete(TKey key);
	virtual bool Insert(TRecord<TKey, TValue> tr);

	virtual void Reset();
	virtual bool isEnd();
	virtual void GoNext();

	virtual bool isFull();

	virtual TRecord<TKey, TValue> GetCurrent();
	virtual void SetCurrent(TValue);
};


template<class TKey, class TValue>
TArrayHash<TKey, TValue>::TArrayHash(int _size, int _step) : THashTable<TKey, TValue>()
{
	size = _size;
	stepcount = _step;
	currNum = 0;

	arr = new TRecord<TKey, TValue>[size];

	for (int i = 0; i < size; i++) {
		arr[i].key = " ";
	}

}


template<class TKey, class TValue>
TArrayHash<TKey, TValue>::~TArrayHash()
{
}


template<class TKey, class TValue>
bool TArrayHash<TKey, TValue>::Find(TKey key) {
	currNum = HashFunc(key) % size;
	int freepos = -1;

	for (int i = 0; i < size; i++) {
		eff++;

		if (arr[currNum].key == " ")
			if (freepos == -1)
				return false;
			else {
				currNum = freepos;
				return false;
			}

			if (arr[currNum].key == key)
				return true;

			if ((freepos == -1) && (arr[currNum].key == "&"))
				freepos = currNum;

			currNum = (currNum + stepcount) % size;
	}

	return false;
}

template<class TKey, class TValue>
bool TArrayHash<TKey, TValue>::Delete(TKey key) {
	if (!Find(key)) return false;
	
	arr[currNum].key = "&";
	dataCount--;

	return true;
}

template<class TKey, class TValue>
bool TArrayHash<TKey, TValue>::Insert(TRecord<TKey, TValue> tr) {
	if (!Find(tr.key)) {
		arr[currNum] = tr;
		dataCount++;

		return true;
	}
	return false;
}


template<class TKey, class TValue>
void TArrayHash<TKey, TValue>::Reset() {
	currNum = 0;
	while ((arr[currNum].key == "&") || (arr[currNum].key == " ")) {
		currNum++;
		if (currNum == size) break;
	}
}

template<class TKey, class TValue>
bool TArrayHash<TKey, TValue>::isEnd() {
	return currNum == size;
}

template<class TKey, class TValue>
void TArrayHash<TKey, TValue>::GoNext() {
	currNum++;
	if (currNum < size) {
		while ((arr[currNum].key == "&") || (arr[currNum].key == " ")) {
			currNum++;
			if (currNum >= size) break;
		}
	}
}


template<class TKey, class TValue>
bool TArrayHash<TKey, TValue>::isFull() {
	return dataCount == size;
}


template<class TKey, class TValue>
TRecord<TKey, TValue> TArrayHash<TKey, TValue>::GetCurrent() {
	return arr[currNum];
}

template<class TKey, class TValue>
void TArrayHash<TKey, TValue>::SetCurrent(TValue _value) {
	arr[currNum].value = _value;
}

