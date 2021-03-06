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
	vector<int> parseConditions(vector<vector<Condition>>&& condition);	
	string keyCol;
public:
	Table() :rows(0) { keyCol = ""; }
	~Table();
	void addColumn(string name,  pColumn c);
	pColumn getColumn(const string& name);
	int length() { return rows; }
	int cols() { return columnObjs.size(); }
	vector<string> getColNames() { return names; }
	void setKeyCol(string name) { keyCol = name; }	//设置主键列
	string getKeyCol() { return keyCol; }
	/*
		增删查改
	*/
	vector<Record> search(vector<string> colNames,vector<vector<Condition>>&&);
	void del(vector<vector<Condition>>&&);
	void update(map<string,pData>& datas,vector<vector<Condition>>&&);
	void insert(map<string, pData>& datas);
	string Serialize();
	static pTable Deserialize(const string& content);
};
