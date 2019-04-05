#pragma once

#include <vector>
#include "utils.h"

using namespace std;

/*
	一列视为一类，含有字段名、数据类型等成员
*/
template<typename T>
class Column {
	vector<ColumnConstraint> constraints;	//约束类型
	ColumnType type;						//数据类型	
	vector<T> values;						//同一列的所有数据
public:
	Column(const ColumnType& ts, const vector<ColumnConstraint>& cs) {
		for (int i = 0, len = cs.size(); i < len; i++) constraints.push_back( cs[i]);
		type = ts;
	}
	/*
		增
	*/
	void add(const T& data){
		T newdata = data;
		values.push_back(newdata);
	}
	/*
		删
	*/
	void del(int index) {
		values.erase(values.begin() + index);
	}
	/*
		查
	*/
	T getData(int index) const{ return values[index]; }
	/*
		改
	*/
	void modify(int index,const T& value) {
		values[index] = value;
	}
	/*
		打印接口
	*/
	friend ostream& operator<<(ostream& out, const Column<T>& c) {
		int len = c.length();
		for (int i = 0; i < len; i++) {
			out << c.getData(i) << " ";
		}
		return out;
	}
	/*	
		（可能没用的）私有成员访问接口
	*/
	int length() const{ return values.size(); }	
	vector<ColumnConstraint>& getConstraints() const{ return constraints; }
	ColumnType getType() const{ return type; }
};

/*class IntColumn:public Column {
	vector<int> values;		//数据
public:
	IntColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs);
	int getData(int index);
	void add(int value);
};*/