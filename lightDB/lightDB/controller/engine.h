#pragma once
#include <string>
#include <map>
#include "../core/database.h"
using namespace std;

/*
	����ģ��
*/

class Engine {
	pDatabase currentDb;					//��ǰ��ѡ�����ݿ�
	map<string, pDatabase> databaseObjs;	//�������ݿ�
	vector<string> dbNames;					//������˳���������ݿ���
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
