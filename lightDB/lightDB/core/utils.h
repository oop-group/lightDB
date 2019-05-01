#pragma once

#include <iostream>
#include <string.h>
#include <sstream>
#include <map>
#include "../rename/rename.h"
#include "../os/serializable.h"
#include "../os/s_char.h"
#include "../os/s_double.h"
#include "../os/s_int.h"
#include "../parser/mystring.h"

using namespace std;

/*
	һЩ���õĹ�����ͺ���
*/

/*
	�ֶ�֧�ֵ��������ͼ���
*/
enum class ColumnType {
	INT,
	DOUBLE,
	CHAR,
};

/*
	�ֶ�Լ��
*/
enum class ColumnConstraint {
	NOT_NULL,	//�ǿ�Լ��
	UNIQUE,		//ΨһԼ��
	INCREMENT,	//����Լ��
	PRIMARY,	//����Լ��
};

/*
	���ݱ���һ���Ϊһ��Data
	֧���������͵�����
	��Data(3)��ʾ������Data(2.4)��ʾ������
*/
class Data: public Serializable{
	ColumnType type;
	int charLen;
	int precision;	//������С���������λ
	union {
		int intV;
		double doubleV;
		char* charV;
	};
public:
	Data():charLen(0){}
	Data(int v):intV(v),charLen(0),type(ColumnType::INT){}
	Data(double v):doubleV(v),charLen(0),precision(4),type(ColumnType::DOUBLE){}
	Data(const char* v);
	Data(const Data& d);
	~Data();

	void operator=(const Data&);
	friend ostream& operator<<(ostream& out, const Data& d);
	bool operator==(const Data& d1);
	bool operator!=(const Data& d1);
	bool operator<(const Data& d1);
	bool operator>(const Data& d1);
	bool operator>=(const Data& d);
	bool operator<=(const Data& d);

	int getIntV() const{ return intV; }
	double getDoubleV() const{ return doubleV; }
	int getPrecision()const { return precision; }
	char* getCharV() const{ return charV; }
	ColumnType getType() const{ return type; }

	string Serialize();				//д���ļ���ʽ
	friend string toString(pData d);				//���������̨��ʽ
	static pData Deserialize(const string& content);

};

class Record {
	map<string, pData> record;
	string key;
public:
	pData& operator[](string name) { return record[name]; }
	void setKey(string k) { key = k; }
	pData getKeyVal() const;
	bool operator<(const Record& other) const;
};

class MapClass {
public:
	static map<string, ColumnType> typeMap;
	static map<string, ColumnConstraint> constraintMap;
	static map<ColumnType, string> strMap;
	static int cnt;
};

ColumnType str2type(string& str);
string type2str(ColumnType&& type);
vector<ColumnConstraint> str2constraints(string& str);



