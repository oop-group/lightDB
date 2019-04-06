#pragma once

#include <map>
#include "column.h"

using namespace std;

/*
	数据表类
	以列名为key，列对象为value，按照字典格式存储表中所有列
*/
class Table {
	map<string, Column*> columnObjs;				//所有列对象
	int rows;						//行数
	vector<string> names;			//列名称
public:
	Table() :rows(0) {}

	void addColumn(string name,  Column* c);
	Column& getColumn(const string& name);
	int length() { return rows; }
	int cols() { return columnObjs.size(); }

	/*
		增删查改
	*/
	vector<vector<pair<string,string>>> search(vector<string> colNames);
};
