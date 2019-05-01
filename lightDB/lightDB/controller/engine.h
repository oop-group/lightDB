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
	string currentName;						//当前被选中数据库的名字
	map<string, pDatabase> databaseObjs;	//所有数据库
	vector<string> dbNames;					//按插入顺序排列数据库名
	map<string, pExecuteFunc> actionMap;
	
public:
	Engine();
	~Engine();
	void run();				
	string execute(string& s);		
	vector<string> getNames() { return dbNames; }
	pDatabase getDbObj(string name) { return databaseObjs[name]; }
	void setCurrentDb(string&& dbname) { currentName = dbname; currentDb = databaseObjs[dbname]; }
	void addDatabase(string name, pDatabase db) { dbNames.push_back(name); databaseObjs[name] = db; }
	void createDatabase(string name) {dbNames.push_back(name);databaseObjs[name] = new Database;}
	void dropDatabase(string name);
	pDatabase getCurrentDb() { return currentDb; }
	string getCurrentDbName() { return currentName; }

	friend string einsert(pEngine, pAction);
	friend string edel(pEngine, pAction);
	friend string esearch(pEngine, pAction);
	friend string eupdate(pEngine, pAction);
	friend string ecreateTb(pEngine, pAction);

	friend string euse(pEngine, pAction);
	friend string eshow(pEngine, pAction);
	friend string eshowcol(pEngine, pAction);
	friend string eshowtable(pEngine, pAction);
	friend string edropDb(pEngine, pAction);
	friend string edropTb(pEngine, pAction);
	friend string ecreateDb(pEngine, pAction);
};

string einsert(pEngine, pAction);
string edel(pEngine, pAction);
string esearch(pEngine, pAction);
string eupdate(pEngine, pAction);
string ecreateTb(pEngine, pAction);

string euse(pEngine, pAction);
string edropDb(pEngine, pAction);
string edropTb(pEngine, pAction);
string eshow(pEngine, pAction);
string eshowcol(pEngine, pAction);
string eshowtable(pEngine, pAction);
string ecreateDb(pEngine, pAction);
