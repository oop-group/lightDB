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
public:
	void setType(string s) { type = s; }
	string getType() { return type; }
};

/*
	表操作
*/
class TableOpAction:public Action {
	string table;
	vector<vector<Condition>> conditions;
public:
	void setTable(string t) { table = t; }
	string getTable() { return table; }
	void setCondition(vector<vector<Condition>>&& cs) { conditions = cs; }
	vector<vector<Condition>> getCondition() { return conditions; }
};

class SelectAction :public TableOpAction{
	vector<string> columns;			//查询返回的列名
public:
	void setColumns(vector<string>&& s) { columns = s; }
	vector<string> getColumns() { return columns; }
};

class UpdateAction :public TableOpAction{
	map<string, pData> data;
public:
	void setData(string& colName, pData d) { data.insert(pair<string, pData>(colName, d)); }
	map<string, pData> getData() { return data; }
};

class DeleteAction :public TableOpAction{

};

class InsertAction :public TableOpAction{
	map<string, pData> data;
public:
	void setData(string& colName, pData d) { data.insert(pair<string, pData>(colName, d)); }
	map<string, pData> getData() { return data; }
};

class DatabaseOpAction :public Action {
	string database;
public:
	string getDbName() { return database; }
	void setDbName(string& str) { database = str; }
};

class CreateTbItem {
	string colName;
	ColumnType type;
	vector<ColumnConstraint> constraints;
public:
	CreateTbItem(const string& n, ColumnType&& t, vector<ColumnConstraint>&& c) { 
		colName = n; type = t; constraints = c; }
	CreateTbItem(){}
	void setColName(const string& name) { colName = name; }
	string getColName() { return colName; }
	void setType(ColumnType&& t) { type = t; }
	ColumnType getType() { return type; }
	void setConstraints(vector<ColumnConstraint>&& c) { constraints = c; }
	vector<ColumnConstraint> getConstraints() { return constraints; }
};


class CreateTbAction :public Action {
	vector<CreateTbItem> items;
	string keyname,table;
public:
	void addItem(const string& n, ColumnType&& t, vector<ColumnConstraint>&& c) {
		auto item = CreateTbItem();
		item.setColName(n);
		item.setType(std::move(t));
		item.setConstraints(std::move(c));
		items.push_back(item);
	}
	void setTable(string t) { table = t; }
	string getTable() { return table; }
	void setPrimaryKey(const string& name) { keyname = name; }
	string getKeyName() { return keyname; }
	vector<CreateTbItem> getItems() { return items; }
};

class UseAction :public DatabaseOpAction {
	
};

class ShowAction :public Action {
	vector<string> databaseNames;
	map<string, pDatabase> databaseObjs;
public:
	vector<string> getnames() { return databaseNames; }
	pDatabase getdbObj(const string& name) { return databaseObjs[name]; }
};

class DropDbAction :public DatabaseOpAction{
};

class ShowColAction :public TableOpAction {
};

class CreateDbAction :public DatabaseOpAction{
};