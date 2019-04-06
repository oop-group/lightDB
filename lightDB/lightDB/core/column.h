#pragma once

#include <vector>
#include <string>
#include "utils.h"

using namespace std;

/*
	一列视为一类，含有字段名、数据类型等成员
*/
class Column {
	ColumnType type;						//数据类型	
protected:
	vector<ColumnConstraint> constraints;	//约束类型
	int rows;								//记录条数
public:
	Column(const ColumnType& ts, const vector<ColumnConstraint>& cs);
	Column(){}
	/*
		（可能没用的）私有成员访问接口
	*/
	int length() const { return rows; }
	vector<ColumnConstraint> getConstraints() const{ return constraints; }
	ColumnType getType() const{ return type; }
};

class IntColumn:public Column {
	vector<int> values;		//数据
public:
	IntColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs):Column(ts,cs) {}
	/*
		增
	*/
	void add(int data) {
		values.push_back(data);
		rows++;
	}
	/*
		删
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		rows--;
	}
	/*
		查
	*/
	int getData(int index) const{ return values[index]; }
	/*
		改
	*/
	void modify(int index, int value) {
		values[index] = value;
	}
	/*
		填充默认值
	*/
	void fill(int value = 0) {
		for (int i = 0; i < rows; i++) values[i] = value;
	}
	/*
		重载运算符
	*/
	friend ostream& operator<<(ostream& out, const IntColumn& c) {
		int len = c.length();
		for (int i = 0; i < len; i++) {
			out << c.getData(i) << " ";
		}
		return out;
	}
	void operator=(const IntColumn& c) {
		values.clear();
		for (int i = 0, len = c.length(); i < len; i++) values.push_back(c.values[i]);
		constraints.clear();
		for (int i = 0, len = c.getConstraints().size(); i < len; i++) constraints.push_back(c.getConstraints()[i]);
	}
};

class DoubleColumn :public Column {
	vector<double> values;		//数据
public:
	DoubleColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs) :Column(ts,cs){}
	/*
		增
	*/
	void add(double data) {
		values.push_back(data);
		rows++;
	}
	/*
		删
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		rows--;
	}
	/*
		查
	*/
	double getData(int index) const{ return values[index]; }
	/*
		改
	*/
	void modify(int index, double value) {
		values[index] = value;
	}
	/*
		填充默认值
	*/
	void fill(double value = 0) {
		for (int i = 0; i < rows; i++) values[i] = value;
	}
	/*
		重载运算符
	*/
	friend ostream& operator<<(ostream& out, const DoubleColumn& c) {
		int len = c.length();
		for (int i = 0; i < len; i++) {
			out << c.getData(i) << " ";
		}
		return out;
	}
};

class CharColumn:public Column {
	vector<string> values;		//数据
public:
	CharColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs):Column(ts,cs) {}
	/*
		增
	*/
	void add(string data) {
		values.push_back(data);
		rows++;
	}
	/*
		删
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		rows--;
	}
	/*
		查
	*/
	string getData(int index) const{ return values[index]; }
	/*
		改
	*/
	void modify(int index, string value) {
		values[index] = value;
	}
	/*
		填充默认值
	*/
	void fill(string value = "") {
		for (int i = 0; i < rows; i++) values[i] = value;
	}
	/*
		重载运算符
	*/
	friend ostream& operator<<(ostream& out, const CharColumn& c) {
		int len = c.length();
		for (int i = 0; i < len; i++) {
			out << c.getData(i) << " ";
		}
		return out;
	}
};