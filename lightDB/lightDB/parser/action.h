#pragma once
#include <vector>
#include <string>

using namespace std;

/*
	根据SQL语句解析结果返回的动作
*/
class Action {
	string type;			//"search","update",etc
	string table;
public:
	void setType(string s) { type = s; }
	string getType() { return type; }
	void setTable(string t) { table = t; }
	string getTable() { return table; }
};

class SelectAction :public Action {
	vector<string> columns;			//查询返回的列名
public:
	void setColumns(vector<string>& s);
	vector<string> getColumns() { return columns; }
};
