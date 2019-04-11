#pragma once
#include <vector>
#include <string>

using namespace std;

/*
	����SQL������������صĶ���
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
	vector<string> columns;			//��ѯ���ص�����
public:
	void setColumns(vector<string>& s);
	vector<string> getColumns() { return columns; }
};
