#pragma once
#include "TTable.h"

template<class TKey, class TValue>
class THashTable : public TTable<TKey, TValue>
{
protected:
	size_t HashFunc(TKey key) {
		size_t pos = 0;

		for (size_t i = 0; i < key.length(); i++) {
			pos += key[i] << i;
		}
		return pos;
	}

public:
	THashTable() : TTable() {}
	~THashTable() {}
};
