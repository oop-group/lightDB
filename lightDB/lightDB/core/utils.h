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
	一些常用的功能类和函数
*/

/*
	字段支持的数据类型集合
*/
enum class ColumnType {
	INT,
	DOUBLE,
	CHAR,
};

/*
	字段约束
*/
enum class ColumnConstraint {
	NOT_NULL,	//非空约束
	UNIQUE,		//唯一约束
	INCREMENT,	//自增约束
	PRIMARY,	//主键约束
};

/*
	数据表中一格称为一个Data
	支持任意类型的数据
	如Data(3)表示整数，Data(2.4)表示浮点数
*/
class Data: public Serializable{
	ColumnType type;
	int charLen;
	union {
		int intV;
		double doubleV;
		char* charV;
	};
public:
	Data():charLen(0){}
	Data(int v):intV(v),charLen(0),type(ColumnType::INT){}
	Data(double v):doubleV(v),charLen(0),type(ColumnType::DOUBLE){}
	Data(const char* v);
	Data(const Data& d);
	~Data();
	void operator=(const Data&);
	friend ostream& operator<<(ostream& out, const Data& d);
	int getIntV() const{ return intV; }
	double getDoubleV() const{ return doubleV; }
	char* getCharV() const{ return charV; }
	ColumnType getType() const{ return type; }
	string Serialize();
	static pData Deserialize(const string& content);
	bool operator==(const Data& d1);
	bool operator!=(const Data& d1);
	bool operator<(const Data& d1);
	bool operator>(const Data& d1);
	bool operator>=(const Data& d);
	bool operator<=(const Data& d);

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



