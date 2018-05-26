#pragma once
#include "TArrayTable.h"

template<class TKey, class TValue>
class TScanTable :
	public TArrayTable<TKey, TValue>
{
public:
	TScanTable() : TArrayTable() {}
	~TScanTable() : ~TArrayTable() {}

	virtual bool Find(TKey tk);
	virtual bool Insert(TRecord<TKey, TValue> tr);
	virtual void Delete(TKey tk);
};

template<class TKey, class TValue>
bool TScanTable<TKey, TValue>::Find(TKey tk) {
	for (int i = 0; i < dataCount; i++) {
		eff++;

		if (arr[i]->key == tk) {
			currNum = i;
			return true;
		}
	}
	currNum = dataCount;
	return false;
}

template<class TKey, class TValue>
bool TScanTable<TKey, TValue>::Insert(TRecord<TKey, TValue> tr) {
	if (!Find(tr->key)) {
		arr[currNum] = tr;
		dataCount++;
		return true;
	}
	return false;
}

template<class TKey, class TValue>
void TScanTable<TKey, TValue>::Delete(TKey tk) {
	if (Find(tk)) {
		arr[currNum] = arr[dataCount - 1];
		dataCount--;
	}
}

