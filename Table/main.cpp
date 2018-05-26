#include "TTreeTable.h"
#include "TScanTable.h"
#include "TSortTable.h"
#include "TArrayHash.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <vector>

using namespace std;

void loadFile(string filename, vector<string> &vec);
void test(TTable<string, int> *table, vector<string> &vec);
void tablePrint(TTable<string, int> *table);


void main() {
	vector<string> StringArray;
	//string s;
	setlocale(LC_ALL, "Russian");

	TTable<string, int> *tableTree = new TTreeTable<string, int>();
	TTable<string, int> *tableScan = new TScanTable<string, int>(400);
	TTable<string, int> *tableSort = new  TSortTable<string, int>(400);
	TTable<string, int> *tableHash = new TArrayHash<string, int>(400, 13);

	loadFile("kirkorbi4.txt", StringArray);
	test(tableTree, StringArray);
	test(tableScan, StringArray);
	test(tableHash, StringArray);
	test(tableSort, StringArray);
	//table->Print();

	//tablePrint(tableSort);
	
	cout << endl << endl;

	while (1) {
		string com;
		string key;
		int value;

		cout << "PRINT COMMAND: ";
		cin >> com;

		if (com == "KEY") {
			break;
		}

		if (com == "INSERT") {
			cout << "PRINT KEY: ";
			cin >> key;
			cout << "PRINT VALUE: ";
			cin >> value;
			
			tableTree->resetEff();
			tableTree->Insert({ key, value });
			cout << "(Tree)EFF = " << tableTree->getEff() << endl;

			tableScan->resetEff();
			tableScan->Insert({ key, value });
			cout << "(Scan)EFF = " << tableScan->getEff() << endl;

			tableSort->resetEff();
			tableSort->Insert({ key, value });
			cout << "(Sort)EFF = " << tableSort->getEff() << endl;

			tableHash->resetEff();
			tableHash->Insert({ key, value });
			cout << "(Hash)EFF = " << tableHash->getEff() << endl;
		}

		if (com == "DELETE") {
			cout << "PRINT KEY: ";
			cin >> key;

			tableTree->resetEff();
			tableTree->Delete(key);
			cout << "(Tree)EFF = " << tableTree->getEff() << endl;

			tableScan->resetEff();
			tableScan->Delete(key);
			cout << "(Scan)EFF = " << tableScan->getEff() << endl;

			tableSort->resetEff();
			tableSort->Delete(key);
			cout << "(Sort)EFF = " << tableSort->getEff() << endl;

			tableHash->resetEff();
			tableHash->Delete(key);
			cout << "(Hash)EFF = " << tableHash->getEff() << endl;
		}

		if (com == "FIND") {
			cout << "PRINT KEY: ";
			cin >> key;

			tableTree->resetEff();
			tableTree->Find(key);
			cout << "(Tree)EFF = " << tableTree->getEff() << endl;
			cout << "(Tree)KEY = " << tableTree->GetCurrent().key << " VALUE = " << tableTree->GetCurrent().value << endl;

			tableScan->resetEff();
			tableScan->Find(key);
			cout << "(Scan)EFF = " << tableScan->getEff() << endl;
			cout << "(Scan)KEY = " << tableScan->GetCurrent().key << " VALUE = " << tableScan->GetCurrent().value << endl;

			tableSort->resetEff();
			tableSort->Find(key);
			cout << "(Sort)EFF = " << tableSort->getEff() << endl;
			cout << "(Sort)KEY = " << tableSort->GetCurrent().key << " VALUE = " << tableSort->GetCurrent().value << endl;

			tableHash->resetEff();
			tableHash->Find(key);
			cout << "(Hash)EFF = " << tableHash->getEff() << endl;
			cout << "(Hash)KEY = " << tableHash->GetCurrent().key << " VALUE = " << tableHash->GetCurrent().value << endl;
		}

		if (com == "PRINT") {
			cout << "PRINT NAME OF TABLE: ";
			cin >> key;
			
			if (key == "sort") {
				tablePrint(tableSort);
			}

			if (key == "scan") {
				tablePrint(tableScan);
			}

			if (key == "tree") {
				tablePrint(tableTree);
			}

			if (key == "hash") {
				tablePrint(tableHash);
			}
		}
	}

	while (!getchar());
}

void loadFile(string filename, vector<string> &vec) {
	ifstream ifs;
	regex reg("([a-zA-Z]+)");
	smatch matches;
	string s;

	ifs.open(filename);
	getline(ifs, s, '\0');
	ifs.close();

	while (regex_search(s, matches, reg)) {
		string tmp = matches[0].str();
		
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		vec.push_back(tmp);
		s = matches.suffix().str();
	}
}

void test(TTable<string, int> *table, vector<string> &vec) {
	regex reg("([a-zA-Z]+)");
	smatch matches;

	for (auto tmp : vec) {
		if (table->Find(tmp)) {
			size_t tmpValLenNew = (to_string(table->GetCurrent().value + 1)).length();
			size_t tmpValLenOld = (to_string(table->GetCurrent().value)).length();
			if (tmpValLenNew > tmpValLenOld) table->setValueMaxLength(tmpValLenNew + 2);

			table->SetCurrent(table->GetCurrent().value + 1);
		}
		else {
			size_t tmpKeyLenNew = tmp.length() + 2;
			size_t tmpKeyLenOld = table->getKeyMaxLength();

			if (tmpKeyLenNew > tmpKeyLenOld) table->setKeyMaxLength(tmpKeyLenNew + 2);

			table->Insert({ tmp, 1 });
		}
	}
}

void tablePrint(TTable<string, int> *table) {
	TRecord<string, int> tmp;
	size_t tableKeyMaxLen = table->getKeyMaxLength();
	size_t tableValMaxLen = table->getValueMaxLength();
	size_t tableLen = tableKeyMaxLen + tableValMaxLen + 5;


	for (table->Reset(); !table->isEnd(); table->GoNext()) {
		tmp = table->GetCurrent();

		size_t currentKeyLen = tmp.key.length() + 2;
		size_t currentValLen = (to_string(tmp.value)).length() + 2;

		size_t leftKeyOffset = (tableKeyMaxLen - currentKeyLen) / 2;
		size_t rightKeyOffset = tableKeyMaxLen - leftKeyOffset - currentKeyLen + 1;

		size_t leftValOffset = (tableValMaxLen - currentValLen) / 2 + 1;
		size_t rightValOffset = tableLen - 1 - leftKeyOffset - rightKeyOffset - currentKeyLen - currentValLen - leftValOffset;

		cout << "||";
		
		for (int i = 0; i < leftKeyOffset; i++)
			cout << " ";

		cout << tmp.key;

		for (int i = 0; i < rightKeyOffset; i++)
			cout << " ";

		cout << "|";

		for (int i = 0; i < leftValOffset; i++)
			cout << " ";

		cout << tmp.value;

		for (int i = 0; i < rightValOffset; i++)
			cout << " ";

		cout << "||" << endl;

		for (int i = 0; i < tableLen; i++)
			cout << "=";

		cout << endl;
	}
}

