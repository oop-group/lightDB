#pragma once

#include <vector>
#include <string>
#include "utils.h"

using namespace std;

/*
	һ����Ϊһ�࣬�����ֶ������������͵ȳ�Ա
*/
class Column {
	ColumnType type;						//��������	
protected:
	vector<ColumnConstraint> constraints;	//Լ������
	int rows;								//��¼����
public:
	Column(const ColumnType& ts, const vector<ColumnConstraint>& cs);
	Column(){}
	/*
		������û�õģ�˽�г�Ա���ʽӿ�
	*/
	int length() const { return rows; }
	vector<ColumnConstraint> getConstraints() const{ return constraints; }
	ColumnType getType() const{ return type; }
};

class IntColumn:public Column {
	vector<int> values;		//����
public:
	IntColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs):Column(ts,cs) {}
	/*
		��
	*/
	void add(int data) {
		values.push_back(data);
		rows++;
	}
	/*
		ɾ
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		rows--;
	}
	/*
		��
	*/
	int getData(int index) const{ return values[index]; }
	/*
		��
	*/
	void modify(int index, int value) {
		values[index] = value;
	}
	/*
		���Ĭ��ֵ
	*/
	void fill(int value = 0) {
		for (int i = 0; i < rows; i++) values[i] = value;
	}
	/*
		���������
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
	vector<double> values;		//����
public:
	DoubleColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs) :Column(ts,cs){}
	/*
		��
	*/
	void add(double data) {
		values.push_back(data);
		rows++;
	}
	/*
		ɾ
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		rows--;
	}
	/*
		��
	*/
	double getData(int index) const{ return values[index]; }
	/*
		��
	*/
	void modify(int index, double value) {
		values[index] = value;
	}
	/*
		���Ĭ��ֵ
	*/
	void fill(double value = 0) {
		for (int i = 0; i < rows; i++) values[i] = value;
	}
	/*
		���������
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
	vector<string> values;		//����
public:
	CharColumn(const ColumnType& ts, const vector<ColumnConstraint>& cs):Column(ts,cs) {}
	/*
		��
	*/
	void add(string data) {
		values.push_back(data);
		rows++;
	}
	/*
		ɾ
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		rows--;
	}
	/*
		��
	*/
	string getData(int index) const{ return values[index]; }
	/*
		��
	*/
	void modify(int index, string value) {
		values[index] = value;
	}
	/*
		���Ĭ��ֵ
	*/
	void fill(string value = "") {
		for (int i = 0; i < rows; i++) values[i] = value;
	}
	/*
		���������
	*/
	friend ostream& operator<<(ostream& out, const CharColumn& c) {
		int len = c.length();
		for (int i = 0; i < len; i++) {
			out << c.getData(i) << " ";
		}
		return out;
	}
};