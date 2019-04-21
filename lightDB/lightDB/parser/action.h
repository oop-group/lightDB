#pragma once
#include <vector>
#include <map>
#include <string>
#include "../core/utils.h"

using namespace std;

/*
	根据SQL语句解析结果返回的动作
*/
class Action {
protected:
	string type;			//"search","update",etc
	string table;
	map<string, pCase> conditions;
public:
	void setType(string s) { type = s; }
	string getType() { return type; }
	void setTable(string t) { table = t; }
	string getTable() { return table; }
	void addCondition(string colname, pCase c);
	map<string, pCase> getCondition() { return conditions; }
};

class SelectAction :public Action {
	vector<string> columns;			//查询返回的列名
public:
	void setColumns(vector<string>& s);
	vector<string> getColumns();
};

class UpdateAction :public Action {
	map<string, pData> data;
public:
	void setData(string& colName, pData d) { data.insert(pair<string, pData>(colName, d)); }
	map<string, pData> getData() { return data; }
};

class DeleteAction :public Action {

};

class InsertAction :public Action {
	map<string, pData> data;
public:
	void setData(string& colName, pData d) { data.insert(pair<string, pData>(colName, d)); }
	map<string, pData> getData() { return data; }
};

struct CreateTbItem {
	string colName;
	ColumnType type;
	vector<ColumnConstraint> constraints;
	CreateTbItem(const string& n, const ColumnType& t, const vector<ColumnConstraint>& c) { colName = n; type = t; constraints = c; }
};

class CreateTbAction :public Action {
	vector<CreateTbItem> items;
	string keyname;
public:
	void addItem(const string& n, const ColumnType& t, const vector<ColumnConstraint>& c) {
		items.push_back(CreateTbItem(n, t, c));
	}
	void setPrimaryKey(const string& name) { keyname = name; }
	string getKeyName() { return keyname; }
	vector<CreateTbItem> getItems() { return items; }
	string getTbName() { return table; }
};

class UseAction :public Action {
	string database;
public:
	string getDbName() { return database; }
	void setDbName(string& str) { database = str; }
};

class ShowAction :public Action {
	vector<string> databaseNames;
	map<string, pDatabase> databaseObjs;
public:
	vector<string>& getnames() { return databaseNames; }
	pDatabase getdbObj(const string& name) { return databaseObjs[name]; }
};

class DropDbAction :public Action {
	string dbname;
public:
	void setDbName(string& str) { dbname = str; }
	string getDbName() { return dbname; }
};

class CreateDbAction :public Action {
	string dbname;
public:
	void setDbName(string& str) { dbname = str; }
	string getDbName() { return dbname; }
};