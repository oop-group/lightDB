#pragma once

#include <map>
#include "column.h"
#include "../rename/rename.h"

using namespace std;

/*
	���ݱ���
	������Ϊkey���ж���Ϊvalue�������ֵ��ʽ�洢����������
*/
class Table {
	map<string, pColumn> columnObjs;	//����-�ж���
	int rows;							//����
	vector<string> names;				//���ղ���˳�򱣴�������
	int getColumnLength(string name);	//ָ�������еļ�¼��
public:
	Table() :rows(0) {}

	void addColumn(string name,  pColumn c);
	pColumn getColumn(const string& name);
	int length() { return rows; }
	int cols() { return columnObjs.size(); }

	/*
		��ɾ���
	*/
	vector<vector<pair<string,Data*>>> search(vector<string> colNames);
	void del();
	void update(map<string,Data*>& datas);
	void insert(map<string, Data*>& datas);
};
