#pragma once

#include <string>

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
	YES_NULL,		//��Լ��
	UNIQUE,		//ΨһԼ��
	INCREMENT,	//����Լ��
	PRIMARY,	//����Լ��
};

/*
	���ݱ���һ���Ϊһ��Data
	֧���������͵�����
	��Data(3)��ʾ������Data(2.4)��ʾ������
*/
class Data {
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
};


