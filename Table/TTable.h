#pragma once
#include <iostream>
#include <string>

template<class TKey, class TValue>
struct TRecord {
	TKey key;
	TValue value;
};

template<class TKey, class TValue>
class TTable
{
protected:
	int dataCount;
	int eff;

	size_t KeyMaxLength, ValueMaxLength;

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

	virtual void GoNext() = 0;
	virtual bool isEnd() = 0;
	virtual void Reset() = 0;

	int getEff() const;
	void resetEff();

	size_t getKeyMaxLength();
	void setKeyMaxLength(size_t len);
	size_t getValueMaxLength();
	void setValueMaxLength(size_t len);

	void Print();
};


template<class TKey, class TValue>
TTable<TKey, TValue>::TTable()
{
	dataCount = 0;
	eff = 0;

	KeyMaxLength = 3;
	ValueMaxLength = 3;
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
		cout << tmp.key << " | " << tmp.value << endl;
	}
}

template<class TKey, class TValue>
bool TTable<TKey, TValue>::isEmpty() {
	return datacount == 0;
}

template<class TKey, class TValue>
int TTable<TKey, TValue>::getEff() const {
	return eff;
}

template<class TKey, class TValue>
void TTable<TKey, TValue>::resetEff() {
	eff = 0;
}

template<class TKey, class TValue>
size_t TTable<TKey, TValue>::getKeyMaxLength() {
	return KeyMaxLength;
}

template<class TKey, class TValue>
void TTable<TKey, TValue>::setKeyMaxLength(size_t len) {
	KeyMaxLength = len;
}

template<class TKey, class TValue>
size_t TTable<TKey, TValue>::getValueMaxLength() {
	return ValueMaxLength;
}

template<class TKey, class TValue>
void TTable<TKey, TValue>::setValueMaxLength(size_t len) {
	ValueMaxLength = len;
}





