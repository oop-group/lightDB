#pragma once

#include <map>
#include "column.h"

using namespace std;

/*
	���ݱ���
	������Ϊkey���ж���Ϊvalue�������ֵ��ʽ�洢����������
*/
class Table {
	map<string, Column*> columnObjs;				//�����ж���
	int rows;						//����
	vector<string> names;			//������
public:
	Table() :rows(0) {}

	void addColumn(string name,  Column* c);
	Column& getColumn(const string& name);
	int length() { return rows; }
	int cols() { return columnObjs.size(); }

	/*
		��ɾ���
	*/
	vector<vector<pair<string,string>>> search(vector<string> colNames);
};
