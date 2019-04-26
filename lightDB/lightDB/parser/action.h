#pragma once
#include <vector>
#include <map>
#include <string>
#include "../core/utils.h"

using namespace std;



/*
	����SQL������������صĶ���
*/
class Action {
protected:
	string type;			//"search","update",etc
public:
	void setType(string s) { type = s; }
	string getType() { return type; }
};

/*
	�����
*/
class TableOpAction:public Action {
	string table;
	vector<vector<Condition>> conditions;
public:
	void setTable(string t) { table = t; }
	string getTable() { return table; }
	void setCondition(vector<vector<Condition>> cs) { conditions = cs; }
	vector<vector<Condition>> getCondition() { return conditions; }
};

class SelectAction :public TableOpAction{
	vector<string> columns;			//��ѯ���ص�����
public:
	void setColumns(vector<string>& s);
	vector<string> getColumns();
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

struct CreateTbItem {
	string colName;
	ColumnType type;
	vector<ColumnConstraint> constraints;
	CreateTbItem(const string& n, const ColumnType& t, const vector<ColumnConstraint>& c) { colName = n; type = t; constraints = c; }
};


class CreateTbAction :public Action {
	vector<CreateTbItem> items;
	string keyname,table;
public:
	void addItem(const string& n, const ColumnType& t, const vector<ColumnConstraint>& c) {
		items.push_back(CreateTbItem(n, t, c));
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
	vector<string>& getnames() { return databaseNames; }
	pDatabase getdbObj(const string& name) { return databaseObjs[name]; }
};

class DropDbAction :public DatabaseOpAction{
};

class ShowColAction :public TableOpAction {
};

class CreateDbAction :public DatabaseOpAction{
};