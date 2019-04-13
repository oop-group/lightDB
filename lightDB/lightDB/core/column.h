#pragma once

#include <vector>
#include <string>
#include "utils.h"
#include "../rename/rename.h"
#include "../os/serializable.h"

using namespace std;

/*
	一列视为一类，含有字段名、数据类型等成员
*/
class Column: public Serializable{
	ColumnType type;						//数据类型
protected:
	vector<ColumnConstraint> constraints;	//约束类型
	vector<pData> values;
public:
	Column(const ColumnType& ts, const vector<ColumnConstraint>& cs);
	Column(){}
	/*
		（可能没用的）私有成员访问接口
	*/
	int length() const { return values.size(); }
	vector<ColumnConstraint> getConstraints() const{ return constraints; }
	ColumnType getType() const{ return type; }
	/*
		增
	*/
	void add(pData data) {
		values.push_back(data);
		//rows++;
	}
	/*
		删
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		//rows--;
	}
	/*
		查
	*/
	pData getData(int index) const { return values[index]; }
	/*
		改
	*/
	void modify(int index, pData value) {
		values[index] = value;
	}
	/*
		打印
	*/
	friend ostream& operator<<(ostream& out, const Column& c) {
		int len = c.length();
		for (int i = 0; i < len; i++) {
			out << c.getData(i) << " ";
		}
		return out;
	}
	string Serialize();
    static pColumn Deserialize(const string& content);
};

