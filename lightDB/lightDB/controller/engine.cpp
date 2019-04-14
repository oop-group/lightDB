#include <iostream>
#include "engine.h"
#include "../parser/parser.h"

using namespace std;

Engine::Engine() {
	actionMap.insert(pair<string, pExecuteFunc>("insert", this->insert));
	actionMap.insert(pair<string, pExecuteFunc>("delete", this->del));
	actionMap.insert(pair<string, pExecuteFunc>("search", this->search));
	actionMap.insert(pair<string, pExecuteFunc>("update", this->update));
}

/*
	接受用户输入，执行sql语句，打印结果
*/
void Engine::run() {
	string input;
	vector<Record> ret;
	while (1) {
		getline(cin, input);
		ret = execute(input);
	}
}

/*
	接受字符串，将其作为Sql解析
	如果是select请求，返回请求结果
	其他请求，返回空
*/
vector<Record> Engine::execute(string& str) {
	Action* action = Parser(this).parse(str);
	auto ret=actionMap[action->getType()](action,currentDb);
	return ret;
}

vector<Record> Engine::insert(pAction action,pDatabase db) {
	InsertAction* iaction = static_cast<InsertAction*>(action);
	string tableStr = iaction->getTable();
	auto data = iaction->getData();
	
	auto table = db->getTable(tableStr);
	table->insert(data);
	return vector<Record>{};
}

vector<Record> Engine::del(pAction action,pDatabase db) {
	DeleteAction* daction = static_cast<DeleteAction*>(action);
	string tableStr = daction->getTable();
	auto condition = daction->getCondition();
	auto table = db->getTable(tableStr);
	table->del(condition);
	return vector<Record>{};
}

vector<Record> Engine::search(pAction action,pDatabase currentDb) {
	SelectAction* saction = static_cast<SelectAction*>(action);
	string tableStr = saction->getTable();
	auto table = currentDb->getTable(tableStr);
	auto colnames=saction->getColumns();
	auto condition = saction->getCondition();
	return table->search(colnames,condition);
}

vector<Record> Engine::update(pAction action,pDatabase db) {
	UpdateAction* uaction = static_cast<UpdateAction*>(action);
	string tableStr = uaction->getTable();
	auto table = db->getTable(tableStr);
	auto data = uaction->getData();
	auto condition = uaction->getCondition();
	table->update(data,condition);
	return vector < Record > {};
}