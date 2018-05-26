#pragma once
#include <iostream>

template<class TKey, class TValue>
struct TRecord {
	TKey key;
	TValue value;
};

template<class TKey, class TValue>
class TTable
{
protected:
	int datacount;
	int eff;

public:
	TTable();
	~TTable();
	
	bool isEmpty();
	virtual bool isFull() = 0;
	
	virtual bool Find(TKey tk) = 0;
	virtual bool Insert(TRecord<TKey, TValue> tr) = 0;
	virtual bool Delete(TKey tk) = 0;
	
	virtual TRecord<TKey, TValue> GetCurrent() = 0;
	virtual void SetCurrent(TValue) = 0;

	virtual bool GoNext() = 0;
	virtual bool isEnd() = 0;
	virtual void Reset() = 0;

	void Print();
};


template<class TKey, class TValue>
TTable<TKey, TValue>::TTable()
{
	datacount = 0;
	eff = 0;
}

template<class TKey, class TValue>
TTable<TKey, TValue>::~TTable()
{
}

template<class TKey, class TValue>
void TTable<TKey, TValue>::Print() {
	TRecord<TKey, TValue> tmp;

	for (Reset(); !isEnd(); GoNext()) {
		tmp = GetCurrent();
	}

	std::cout << tmp.value << std::endl;
}

template<class TKey, class TValue>
bool TTable<TKey, TValue>::isEmpty() {
	return datacount == 0;
}




