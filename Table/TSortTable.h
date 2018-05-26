#pragma once
#include "TArrayTable.h"
#include "TScanTable.h"

template<class TKey, class TValue>
class TSortTable :
	public TArrayTable<TKey, TValue>
{
public:
	TSortTable(size_t size = 100);
	TSortTable(TScanTable<TKey, TValue>& st);
	~TSortTable();

	virtual bool Find(TKey tk);
	virtual bool Insert(TRecord<TKey, TValue> tr);
	virtual bool Delete(TKey tk);

	void Sort(int left, int right);
};

template<class TKey, class TValue>
TSortTable<TKey, TValue>::TSortTable(size_t size) : TArrayTable(size)
{
}

template<class TKey, class TValue>
TSortTable<TKey, TValue>::TSortTable(TScanTable<TKey, TValue>& st) : TArrayTable(st.size) {
	size = st.size;
	currNum = stCurrSum;
	dataCount = st.dataCount;

	for (int i = 0; i < dataCount; i++) {
		arr[i] = st.arr[i];
	}

	Sort(0, dataCount - 1);
}

template<class TKey, class TValue>
TSortTable<TKey, TValue>::~TSortTable()
{
}

template<class TKey, class TValue>
bool TSortTable<TKey, TValue>::Find(TKey tk) {
	int mid;
	int left = 0;
	int right = dataCount - 1;

	while (left <= right) {
		eff++;
		mid = (right + left) / 2;

		if (arr[mid].key == tk) {
			currNum = mid;
			return true;
		}

		if (arr[mid].key > tk) {
			right = mid - 1;
		}

		if (arr[mid].key < tk) {
			left = mid + 1;
		}
	}

	currNum = left;
	return false;
}

template<class TKey, class TValue>
bool TSortTable<TKey, TValue>::Insert(TRecord<TKey, TValue> tr) {
	if (!Find(tr.key)) {
		for (int i = dataCount; i > currNum; i--) {
			arr[i] = arr[i - 1];
			eff++;
		}
		arr[currNum] = tr;
		dataCount++;
		return true;
	}
	return false;
}

template<class TKey, class TValue>
bool TSortTable<TKey, TValue>::Delete(TKey tk) {
	if (Find(tk)) {
		for (int i = currNum; i < dataCount; i++) {
			arr[i] = arr[i + 1];
			eff++;
		}
		dataCount--;
		return true;
	}
	return false;
}

template<class TKey, class TValue>
void TSortTable<TKey, TValue>::Sort(int left, int right) {
	int mid = (left + right) / 2;
	TKey mkey = arr[mid].key;
	int i = 0, j = dataCount - 1;

	while (i <= j) {
		while (arr[i].key < mkey)
			i++;
		while (arr[j].key > mkey)
			j--;
		if (i <= j) {
			TRecord<TKey, TValue> tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}

	if (j > left) {
		return Sort(left, j);
	}

	if (i < right) {
		return Sort(i, right);
	}
}




