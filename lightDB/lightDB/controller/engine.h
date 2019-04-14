#pragma once
#include <string>
#include <map>
#include "../core/database.h"
using namespace std;

/*
	调度模块
*/

class Engine {
	pDatabase currentDb;					//当前被选中数据库
	map<string, pDatabase> databaseObjs;	//所有数据库
	vector<string> dbNames;					//按插入顺序排列数据库名
	map<string, pExecuteFunc> actionMap;
	
public:
	Engine();
	void run();				
	string execute(string& s);		
	void setCurrentDb(pDatabase db) { currentDb = db; }
	void addDatabase(string name, pDatabase db) { dbNames.push_back(name); databaseObjs[name] = db; }
	pDatabase getCurrentDb() { return currentDb; }
	friend string einsert(pEngine, pAction);
	friend string edel(pEngine, pAction);
	friend string esearch(pEngine, pAction);
	friend string eupdate(pEngine, pAction);
	friend string euse(pEngine, pAction);
};

string einsert(pEngine, pAction);
string edel(pEngine, pAction);
string esearch(pEngine, pAction);
string eupdate(pEngine, pAction);
string euse(pEngine, pAction);
string edrop(pEngine, pAction);
