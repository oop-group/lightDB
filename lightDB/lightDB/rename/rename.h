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
class Engine;

typedef Column* pColumn;
typedef Table* pTable;
typedef Data* pData;
typedef Database* pDatabase;
typedef Case* pCase;
typedef Action* pAction;
typedef vector<pair<string, Data*>> Record;
typedef Engine* pEngine;

typedef Action*(*pActionFunc)(string& input,pEngine engine);
typedef Case*(*pCaseFunc)(pData value);
typedef string(*pExecuteFunc)(pEngine,pAction action);



