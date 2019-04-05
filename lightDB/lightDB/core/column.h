#pragma once

#include <vector>
#include "utils.h"

using namespace std;

/*
	һ����Ϊһ�࣬�����ֶ������������͵ȳ�Ա
*/
template<typename T>
class Column {
	vector<ColumnConstraint> constraints;	//Լ������
	ColumnType type;						//��������	
	vector<T> values;						//ͬһ�е���������
public:
	Column(const ColumnType& ts, const vector<ColumnConstraint>& cs) {
		for (int i = 0, len = cs.size(); i < len; i++) constraints.push_back( cs[i]);
		type = ts;
	}
	/*
		��
	*/
	void add(const T& data){
		T newdata = data;
		values.push_back(newdata);
	}
	/*
		ɾ
	*/
	void del(int index) {
		values.erase(values.begin() + index);
	}
	/*
		��
	*/
	T getData(int index) const{ return values[index]; }
	/*
		��
	*/
	void modify(int index,const T& value) {
		values[index] = value;
	}
	/*
		��ӡ�ӿ�
	*/
	friend ostream& operator<<(ostream& out, const Column<T>& c) {
		int len = c.length();
		for (int i = 0; i < len; i++) {
			out << c.getData(i) << " ";
		}
		return out;
	}
	/*	
		������û�õģ�˽�г�Ա���ʽӿ�
	*/
	int length() const{ return values.size(); }	
	vector<ColumnConstraint>& getConstraints() const{ return constraints; }
	ColumnType getType() const{ return type; }
};

/*class IntColumn:public Column {
	vector<int> values;		//����
public:
	IntColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs);
	int getData(int index);
	void add(int value);
};*/