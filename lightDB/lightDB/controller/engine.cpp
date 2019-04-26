#include <iostream>
#include <algorithm>
#include "engine.h"
#include "../parser/parser.h"
#include "../core/utils.h"

using namespace std;

Engine::Engine() {
	actionMap["insert"] = einsert;
	actionMap["delete"] = edel;
	actionMap["search"] = esearch;
	actionMap["update"] = eupdate;
	actionMap["use"] = euse;
	actionMap["show"] = eshow;
	actionMap["showcol"] = eshowcol;
	actionMap["dropdb"] = edropDb;
	actionMap["createdb"] = ecreateDb;
	actionMap["createtb"] = ecreateTb;
}

/*
	接受用户输入，执行sql语句，打印结果
*/
void Engine::run() {
	string input;
	string ret;
	while (getline(cin,input)) {
		if (input != "") {
			if (input != "exit" && input != "quit") {
				ret = execute(input);
				cout << ret;
			}
			else exit(0);
		}
		else break;
	}
}

/*
	接受字符串，将其作为Sql解析
	如果是select请求，返回请求结果
	其他请求，返回空
*/
string Engine::execute(string& str) {
	Action* action = Parser(this).parse(str);
	string ret=actionMap[action->getType()](this,action);
	return ret;
}

string einsert(pEngine engine,pAction action) {
	InsertAction* iaction = static_cast<InsertAction*>(action);
	string tableStr = iaction->getTable();
	auto data = iaction->getData();
	auto table = engine->getCurrentDb()->getTable(tableStr);
	table->insert(data);
	return "";
}

string edel(pEngine engine,pAction action) {
	DeleteAction* daction = static_cast<DeleteAction*>(action);
	string tableStr = daction->getTable();
	auto condition = daction->getCondition();
	auto table = engine->getCurrentDb()->getTable(tableStr);
	table->del(condition);
	return "";
}

string esearch(pEngine engine,pAction action) {
	SelectAction* saction = static_cast<SelectAction*>(action);
	string tableStr = saction->getTable();
	auto table = engine->getCurrentDb()->getTable(tableStr);
	auto colnames=saction->getColumns();
	auto condition = saction->getCondition();
	vector<Record> ret= table->search(colnames,condition);
	if (ret.size() == 0) return "";
	string retStr;
	char tmpint[10], tmpfloat[100];
	int i = 0,len=colnames.size();
	for (; i < len; i++) {
		retStr += colnames[i];
		retStr += '\t';
	}
	retStr[retStr.size() - 1] = '\n';
	i = 0;
	len = ret.size();
	for (; i < len; i++) {	//一条记录
		auto it = ret[i].begin();
		while (it != ret[i].end()) {	//一个字段
			//retStr += it->first;
			//retStr.push_back('\t');
			switch (table->getColumn(it->first)->getType())
			{
			case ColumnType::INT:
				sprintf(tmpint, "%d", it->second->getIntV());
				retStr += tmpint;
				break;
			case ColumnType::DOUBLE:
				sprintf(tmpfloat, "%f", it->second->getDoubleV());
				retStr += tmpfloat;
				break;
			case ColumnType::CHAR:
				retStr += string(it->second->getCharV());
				break;
			default:
				break;
			}
			retStr.push_back('\t');	
			it++;
		}
		retStr[retStr.size() - 1] = '\n';
	}
	return retStr;
}

string eupdate(pEngine engine,pAction action) {
	UpdateAction* uaction = static_cast<UpdateAction*>(action);
	string tableStr = uaction->getTable();
	auto table = engine->getCurrentDb()->getTable(tableStr);
	auto data = uaction->getData();
	auto condition = uaction->getCondition();
	table->update(data,condition);
	return "";
}

string ecreateTb(pEngine engine, pAction action) {
	CreateTbAction* caction = static_cast<CreateTbAction*>(action);
	if (engine->getCurrentDb() == nullptr) return "";
	pTable table = new Table;
	auto items = caction->getItems();
	for (auto item : items) {
		pColumn c = new Column(item.type, item.constraints);
		table->addColumn(item.colName,c);
	}
	string keyname = caction->getKeyName();
	auto c = table->getColumn(keyname);
	c->addConstraint(ColumnConstraint::PRIMARY);
	engine->getCurrentDb()->createTable(caction->getTable(), table);
	return "";
}

string euse(pEngine engine,pAction action) {
	UseAction* uaction = static_cast<UseAction*>(action);
	engine->setCurrentDb(engine->databaseObjs[uaction->getDbName()]);
	return "";
}

//show columns
string eshowcol(pEngine engine, pAction action) {
	string tbname = static_cast<ShowColAction*>(action)->getTable();
	auto table = engine->getCurrentDb()->getTable(tbname);
	string ret = "Field\tType\tNull\tKey\tDefault\tExtra\n";
	auto names= table->getColNames();
	for (int i = 0, len = names.size(); i < len; i++) {
		string name = names[i];
		auto col = table->getColumn(name);
		ret += name + '\t';
		ret += type2str(col->getType())+"\t";
		auto css = col->getConstraints();
		auto it = find(css.begin(), css.end(), ColumnConstraint::NOT_NULL);
		ret += (it != css.end()) ? "NO" : "YES";
		ret+='\t';
		it = find(css.begin(), css.end(), ColumnConstraint::PRIMARY);
		ret += (it != css.end()) ? "PRI" : "";
		ret+='\t';
		/*
			default和extra暂时用不到，所以没有写
		*/
		ret+="NULL";	//default
		ret += "\t\n";	//extra
		
	}
	return ret;
}

//show databases
string eshow(pEngine engine, pAction action) {
	vector<string> names = engine->getNames();
	string ret;
	ret += "Database\n";
	for (int i = names.size() - 1; i >= 0; i--) {
		string name = names[i];
		ret += name + '\n';	//数据库名
		pDatabase db = engine->getDbObj(name);
		vector<string> tbnames = db->getNames();
		if (tbnames.size()) {
			ret += "Table";
			for (string tbname : tbnames) {
				ret += tbname + '\n';	//表名
			}
		}
	}
	return ret;
}

string edropDb(pEngine engine, pAction action) {
	DropDbAction* daction = static_cast<DropDbAction*>(action);
	engine->dropDatabase(daction->getDbName());
	return "";
}

string ecreateDb(pEngine engine, pAction action) {
	CreateDbAction* caction = static_cast<CreateDbAction*>(action);
	engine->createDatabase(caction->getDbName());
	return "";
}