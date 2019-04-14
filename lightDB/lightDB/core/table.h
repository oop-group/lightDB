#pragma once

#include <map>
#include "column.h"
#include "../rename/rename.h"
#include "../os/serializable.h"

using namespace std;

/*
	数据表类
	以列名为key，列对象为value，按照字典格式存储表中所有列
*/
class Table: public Serializable{
	map<string, pColumn> columnObjs;	//列名-列对象
	int rows;							//行数
	vector<string> names;				//按照插入顺序保存列名称

	int getColumnLength(string name);	//指定名称列的记录数
	vector<int> parseConditions(map<string,pCase>& condition);	
public:
	Table() :rows(0) {}

	void addColumn(string name,  pColumn c);
	pColumn getColumn(const string& name);
	int length() { return rows; }
	int cols() { return columnObjs.size(); }
	vector<string> getColNames() { return names; }

	/*
		增删查改
	*/
	vector<Record> search(vector<string> colNames,map<string,pCase>& condition);
	void del(map<string,pCase>& condition);
	void update(map<string,pData>& datas,map<string,pCase>& condition);
	void insert(map<string, pData>& datas);
	string Serialize();
	static pTable Deserialize(const string& content);
};
