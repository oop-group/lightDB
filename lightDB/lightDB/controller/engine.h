#pragma once
#include <string>
#include <map>
#include "../core/database.h"
using namespace std;

/*
	����ģ��
*/

class Engine {
	pDatabase currentDb;	//��ǰ��ѡ�����ݿ�

	map<string, pExecuteFunc> actionMap;
	static vector<Record> insert(pAction,pDatabase);
	static vector<Record> del(pAction,pDatabase);
	static vector<Record> search(pAction,pDatabase);
	static vector<Record> update(pAction,pDatabase);
public:
	Engine();
	void run();				
	vector<Record> execute(string& s);		
	void setCurrentDb(pDatabase db) { currentDb = db; }
	pDatabase getCurrentDb() { return currentDb; }
};
