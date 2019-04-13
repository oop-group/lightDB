#pragma once
#include <vector>

using namespace std;


/*
	一些复杂数据结构的重命名
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


