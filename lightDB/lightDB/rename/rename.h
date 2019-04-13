#pragma once
#include <vector>

using namespace std;


/*
	һЩ�������ݽṹ��������
*/
class Column;
class Table;
class Data;
class Database;
class Action;
class Case;

typedef Column* pColumn;
typedef Table* pTable;
typedef Data* pData;
typedef Database* pDatabase;
typedef Case* pCase;
typedef Action* pAction;

typedef Action*(*pActionFunc)(string& input);

typedef Case*(*pCaseFunc)(pData value);

typedef vector<pair<string, Data*>> Record;


