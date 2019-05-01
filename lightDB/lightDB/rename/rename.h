#pragma once
#include <vector>
#include <map>

using namespace std;


/*
	一些复杂数据结构的重命名
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
typedef Engine* pEngine;
typedef pair<string, pCase> Condition;
typedef Condition* pCondition;
typedef vector<vector<pCondition>> pConditionsVec;

typedef Action*(*pActionFunc)(string& input,pEngine engine);
typedef Case*(*pCaseFunc)(pData value);
typedef string(*pExecuteFunc)(pEngine,pAction action);




