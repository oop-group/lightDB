#pragma once

#include <vector>
#include <string>
#include "utils.h"
#include "../rename/rename.h"
#include "../os/serializable.h"

using namespace std;

/*
	һ����Ϊһ�࣬�����ֶ������������͵ȳ�Ա
*/
class Column: public Serializable{
	ColumnType type;						//��������
protected:
	vector<ColumnConstraint> constraints;	//Լ������
	vector<pData> values;
public:
	Column(const ColumnType& ts, const vector<ColumnConstraint>& cs);
	Column(){}
	/*
		������û�õģ�˽�г�Ա���ʽӿ�
	*/
	int length() const { return values.size(); }
	vector<ColumnConstraint> getConstraints() const{ return constraints; }
	ColumnType getType() const{ return type; }
	/*
		��
	*/
	void add(pData data) {
		values.push_back(data);
		//rows++;
	}
	/*
		ɾ
	*/
	void del(int index) {
		values.erase(values.begin() + index);
		//rows--;
	}
	/*
		��
	*/
	pData getData(int index) const { return values[index]; }
	/*
		��
	*/
	void modify(int index, pData value) {
		values[index] = value;
	}
	/*
		��ӡ
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

