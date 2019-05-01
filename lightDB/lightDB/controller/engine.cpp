#include <iostream>
#include <algorithm>
#include "engine.h"
#include "../parser/parser.h"
#include "../core/utils.h"

using namespace std;

void Engine::dropDatabase(string name) {
	if (databaseObjs[name] == currentDb) {
		currentDb = nullptr;
	}
	databaseObjs.erase(name);
	for (auto iter = dbNames.begin(); iter != dbNames.end(); iter++) {
		if (*iter == name) {
			dbNames.erase(iter);
			break;
		}
	}
}

Engine::Engine() {
	actionMap["insert"] = einsert;
	actionMap["delete"] = edel;
	actionMap["search"] = esearch;
	actionMap["update"] = eupdate;
	actionMap["use"] = euse;
	actionMap["show"] = eshow;
	actionMap["showcol"] = eshowcol;
	actionMap["showtable"] = eshowtable;
	actionMap["dropdb"] = edropDb;
	actionMap["droptb"] = edropTb;
	actionMap["createdb"] = ecreateDb;
	actionMap["createtb"] = ecreateTb;
}

Engine::~Engine() {
	for (auto iter = databaseObjs.begin(); iter != databaseObjs.end(); iter++) {
		if (iter->second != nullptr) {
			delete iter->second;
			iter->second = nullptr;
		}
	}
	databaseObjs.clear();
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
	delete action;
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
	table->del(std::move(condition));
	return "";
}

string esearch(pEngine engine,pAction action) {
	SelectAction* saction = static_cast<SelectAction*>(action);
	string tableStr = saction->getTable();
	auto table = engine->getCurrentDb()->getTable(tableStr);
	auto colnames=saction->getColumns();
	auto condition = saction->getCondition();
	vector<Record> ret= table->search(colnames,std::move(condition));
	if (ret.size() == 0) return "";
	string retStr;
	char tmpint[15], tmpfloat[60];
	int i = 0,len=colnames.size();
	for (; i < len; i++) {
		retStr += colnames[i];
		retStr += '\t';
	}
	retStr[retStr.size() - 1] = '\n';
	i = 0;
	int len1 = ret.size();
	//将record按照主键排序
	sort(ret.begin(), ret.end());

	for (; i < len1; i++) {	
		Record record = ret[i];		//返回结果中第i条记录
		for (int j=0;j<len;j++){		//结果中的一列
			switch (table->getColumn(colnames[j])->getType())
			{
			case ColumnType::INT:
				if (record[colnames[j]] == nullptr) retStr += "NULL";
				else {
					snprintf(tmpint, 15, "%d", record[colnames[j]]->getIntV());
					retStr += tmpint;
				}
				break;
			case ColumnType::DOUBLE:
				if (record[colnames[j]] == nullptr) retStr += "NULL";
				else {
					snprintf(tmpfloat, 60, "%.4f", record[colnames[j]]->getDoubleV());
					retStr += tmpfloat;
				}
				break;
			case ColumnType::CHAR:
				if (record[colnames[j]] == nullptr) retStr += "NULL";
				else  retStr += string(record[colnames[j]]->getCharV());
				break;
			default:
				break;
			}
			retStr.push_back('\t');	
		}
		retStr[retStr.size() - 1] = '\n';
	}
	return retStr;
	return "";
}

string eupdate(pEngine engine,pAction action) {
	UpdateAction* uaction = static_cast<UpdateAction*>(action);
	string tableStr = uaction->getTable();
	auto table = engine->getCurrentDb()->getTable(tableStr);
	auto data = uaction->getData();
	auto condition = uaction->getCondition();
	table->update(data,std::move(condition));
	return "";
}

string ecreateTb(pEngine engine, pAction action) {
	CreateTbAction* caction = static_cast<CreateTbAction*>(action);
	if (engine->getCurrentDb() == nullptr) return "";
	pTable table = new Table;
	auto items = caction->getItems();
	for (auto item : items) {
		pColumn c = new Column(item.getType(), item.getConstraints());
		table->addColumn(item.getColName(),c);
	}
	string keyname = caction->getKeyName();
	table->setKeyCol(keyname);
	auto c = table->getColumn(keyname);
	c->addConstraint(ColumnConstraint::PRIMARY);
	engine->getCurrentDb()->createTable(caction->getTable(), table);
	return "";
}

string euse(pEngine engine,pAction action) {
	UseAction* uaction = static_cast<UseAction*>(action);
	engine->setCurrentDb(uaction->getDbName());
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

string eshowtable(pEngine engine, pAction action) {
	string ret = "Tables_in_";
	ret+= engine->getCurrentDbName();
	ret+= '\n';
	auto tables = engine->getCurrentDb()->getNames();
	sort(tables.begin(), tables.end());
	for (auto table : tables) {
		ret+= table;
		ret+= '\n';
	}
	return ret;
}

//show databases
string eshow(pEngine engine, pAction action) {
	vector<string> names = engine->getNames();
	string ret;
	ret += "Database\n";
	//按照字典序输出表名
	sort(names.begin(), names.end());
	for (int i=0,len=names.size();i<len;i++){
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

string edropTb(pEngine engine, pAction action) {
	DropTbAction* taction = static_cast<DropTbAction*>(action);
	engine->getCurrentDb()->dropTable(taction->getTable());
	return "";
}

string ecreateDb(pEngine engine, pAction action) {
	CreateDbAction* caction = static_cast<CreateDbAction*>(action);
	engine->createDatabase(caction->getDbName());
	return "";
}