#pragma once

#include <vector>
#include <string>
#include <memory>
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
	pData defaultValue;	
	string extra;
	vector<pData> values;
public:
	Column(ColumnType&& ts, vector<ColumnConstraint>&& cs);
	Column() { defaultValue = nullptr; extra = ""; }
	~Column() {
		for (auto iter = values.begin(); iter != values.end(); iter++) {
			if (*iter != nullptr) {
				delete *iter;
				*iter = nullptr;
			}
		}
		values.clear();
	}
	void addConstraint(ColumnConstraint&& c) { constraints.push_back(c); }
	/*
		（可能没用的）私有成员访问接口
	*/
	int length() const { return values.size(); }
	vector<ColumnConstraint> getConstraints() const{ return constraints; }
	ColumnType getType() const{ return type; }
	pData getDefaultValue() { return defaultValue; }
	string getExtra() { return extra; }
	void setExtra(string s) { extra=s; }
	/*
		增
	*/
	void add(pData data) {
		values.push_back(data);
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

