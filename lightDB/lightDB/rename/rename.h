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

typedef Column* pColumn;
typedef Table* pTable;
typedef Data* pData;
typedef Database* pDatabase;

typedef Action*(*pActionFunc)(vector<string>& str,string& input);

typedef vector<pair<string, Data*>> Record;


