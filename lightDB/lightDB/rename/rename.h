#pragma once
#include <vector>
#include <string>
using namespace std;


/*
	һЩ�������ݽṹ��������
*/
class Column;
class Table;
class Data;
class Action;

typedef Column* pColumn;
typedef Table* pTable;
typedef Data* pData;
typedef Action*(*pActionFunc)(vector<string>&);

typedef vector<pair<string, Data*>> Record;


