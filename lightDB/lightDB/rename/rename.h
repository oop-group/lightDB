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

typedef Column* pColumn;
typedef Table* pTable;
typedef Data* pData;
typedef Database* pDatabase;

typedef vector<pair<string, Data*>> Record;


